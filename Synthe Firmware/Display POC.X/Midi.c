/*
**
**
**
*/

#include <p32xxxx.h>
#include <sys/attribs.h>

# define PROCESS 42
# define TRUE 1
# define FALSE 0
# define INPUT 1
# define OUTPUT 0
# define VCC 1
# define GND 0
# define RISING_EDGE 1
# define FALLING_EDGE 0
# define NOTE_MAX 0b01101100
# define NOTE_MIN 0b00010101
# define ON_EVENT 0b1000
# define OFF_EVENT 0b1001

typedef unsigned        char u8;
typedef unsigned        short u16;
typedef unsigned        long u32;
typedef signed          char s8;
typedef signed          short s16;
typedef signed          long s32;


# define TRIS_RS TRISBbits.TRISB10
# define TRIS_E TRISBbits.TRISB11
# define TRIS_DB4 TRISBbits.TRISB12
# define TRIS_DB5 TRISBbits.TRISB13
# define TRIS_DB6 TRISBbits.TRISB14
# define TRIS_DB7 TRISBbits.TRISB15

# define _RS LATBbits.LATB10
# define _E LATBbits.LATB11
# define _DB4 LATBbits.LATB12
# define _DB5 LATBbits.LATB13
# define _DB6 LATBbits.LATB14
# define _DB7 LATBbits.LATB15


# define TRIS_A0 TRISDbits.TRISD0
# define TRIS_A1 TRISDbits.TRISD1

# define _A0 LATDbits.LATD0
# define _A1 LATDbits.LATD1


static void      waitXticks(u32 x)
{
    u32 i = 0;
    while (i < x)
        i++;
    return;
}

static void      lcd_pulse(void)
{
    _E = 0;
    waitXticks(1);
    _E = 1;
    waitXticks(100);        //enable pulse lasts 100us
    _E = 0;
    waitXticks(10);        //wait 20us for enable to settle down
    return;
}

static void      write4bits(u8 value)
{
    _DB4 = (value & 0x01);
    _DB5 = ((value >> 1) & 0x01);
    _DB6 = ((value >> 2) & 0x01);
    _DB7 = ((value >> 3) & 0x01);
    lcd_pulse();
    return;
}

static void      lcd_command(u8 value, u8 rs)
{
    if (rs)                  //set RS to write or read
        _RS = 1;
    else
        _RS = 0;

    write4bits(value >> 4);
    write4bits(value);

    return;
}

static void      lcd_print(char *str)
{
    int x = 0;

    while (str[x])
    {
        lcd_command(str[x], 1);
        x++;
    }
    return;
}

static void      lcd_goto(u8 col, u8 line)
{
    u8 x;
    if (line == 1)
        x = 0b10000000;
    else if (line == 2)
        x = 0b11000000;
    else
        return;
    if (col >= 1 && col <= 16)
    {
        x |= col - 1;
        lcd_command(x, 0);
    }
}

static void      init_lcd(void)
{
    LATFbits.LATF1 = 1;

    //-----  PAD IO  ----
    TRIS_RS = OUTPUT;          //RS is output
    TRIS_E = OUTPUT;           //E is output
    TRIS_DB4 = OUTPUT;         //DB4 is output
    TRIS_DB5 = OUTPUT;         //DB5 is output
    TRIS_DB6 = OUTPUT;         //DB6 is output
    TRIS_DB7 = OUTPUT;         //DB7 is output

    _RS = 0;
    _E = 0;
    _DB4 = 0;
    _DB5 = 0;
    _DB6 = 0;
    _DB7 = 0;

    waitXticks(3000);         //Wait 3s for LCD to power up to 5V
    LATFbits.LATF1 = 0;
    write4bits(0b0010);          //Set 4 bit mode
    waitXticks(1000);
    lcd_command(0b00101000, 0);  //Set 4bit mode, 2line display, 5*8 char
    waitXticks(1000);
    lcd_command(0b00000110, 0);  //Set DDRam incrementation, Display Shift OFF
    waitXticks(1000);
    lcd_command(0b00000001, 0);  //Clear display
    waitXticks(5000);
    lcd_command(0b00001100, 0);  //Set Diplay ON, Cursor OFF, Blinking OFF
    waitXticks(1000);

    return;
}


static void         init_interrupt(void)
{
    IEC0bits.U1RXIE = TRUE;
    IFS0bits.U1RXIF = FALSE;
    IPC6bits.U1IP = 7;
    IPC6bits.U1IS = 1;
}

static void         init_uart(void)
{
    //----- INTERRUPT -----
    INTCONbits.MVEC = TRUE;             //Multi-vector mode

    //------  UART  -------
    // UART pour la réception MIDI IN et envoi de MIDI THRU
    // BaudRate MIDI = 31250;
    U1BRG = 19;                         // Set Baud rate
    U1STA = 0;
    U1MODE = 0;
    U1STAbits.URXISEL = 0;
    U1STAbits.URXEN = TRUE;
    U1STAbits.UTXEN = TRUE;
    U1MODEbits.ON = TRUE;               // Enable UART for 8-bit data
}

static char     *ft_itoa(u8 value)
{
    char        str[3];
    u8          i;

    str[2] = '\0';
    value -= 21;
    if (value == 0) {
        str[0] = '0';
        str[1] = '0';
    }
    else {
        i = 1;
        while (value > 0) {
            str[i--] = (value % 10) + '0';
            value /= 10;
        }
        if (value == 0 && i == 0)
            str[0] = '0';
    }
    return (str);
}

void __ISR(_UART_1_VECTOR, IPL7AUTO) ft_uart(void)
{
    u8              octet_recu;
    static u8       mode = 0;
    static u8       cur_note;
    static u8       key_pressed = 0;

    octet_recu = U1RXREG;         // U1RXREG est le buffer de réception UART
    if (mode == 3 && octet_recu == cur_note) {
        lcd_goto(1, 2);
        lcd_print("Note OFF: ");  // La note courante a été relachée
        mode = 2;
        key_pressed = 0;
    }
    else if (mode == 3)
        mode = 0;             // Signal OFF d'une autre note que celle courante
    else if (mode == 2)
        mode = 0;                       // Lecture de la vélocité = osef
    else if (mode == 1 && octet_recu <= NOTE_MAX && octet_recu >= NOTE_MIN) {
        cur_note = octet_recu;          // Stock la note courante
        lcd_print(ft_itoa(cur_note));   // Print note courante
        mode = 2;
    }
    else if (mode == 1) {
        lcd_goto(1, 2);
        lcd_print("Wrong note");        // Note jouée n'est pas définie sur 88
        mode = 0;
    }
    else if (mode == 0 && !((octet_recu >> 4) & ON_EVENT)) {
        lcd_goto(1, 2);
        lcd_print("Note ON : ");        // Signal ON, prochain octet = note
        mode = 1;
        key_pressed = 1;
    }
    else if (mode == 0 && key_pressed && !((octet_recu >> 4) & OFF_EVENT)) {
        mode = 3;                       // Signal OFF, prochain octet = note
    }

    IFS0bits.U1RXIF = FALSE;
}


int             main(void) {
    TRISFbits.TRISF1 = OUTPUT;          //RF1 = Led verte
    LATFbits.LATF1 = 0;               //Etat initial = éteint

    init_interrupt();
    init_lcd();
    init_uart();

    lcd_print("Midi UART");
    lcd_goto(1, 2);
    lcd_print("Note OFF ");

    while(PROCESS) {
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
}
