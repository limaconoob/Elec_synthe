/*#include <p32xxxx.h>
#include <sys/attribs.h>

# define PROCESS 42
# define TRUE 1
# define FALSE 0
# define INPUT 1
# define OUTPUT 0
# define VCC 1
# define GND 0

typedef unsigned    char u8;
typedef unsigned    short u16;
typedef unsigned    long u32;
typedef signed      char s8;
typedef signed      short s16;
typedef signed      long s32;

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

static void      init_multiplexer(void)
{
    TRIS_A0 = OUTPUT;
    TRIS_A1 = OUTPUT;

    _A0 = 0;
    _A1 = 0;
}

static void      init_interrupt(void)
{
    //----- INTERRUPT -----
    INTCONbits.MVEC = TRUE;             //Multi-vector mode
    INTCONbits.INT1EP = 0;              //Prend INT1 au front descendant

    //-----   FLAG   -----
    IEC0bits.T3IE = TRUE;               //Autorise interruption timer2
    IFS0bits.T3IF = FALSE;              //Flag à NO (Attend signal pour blink)
    IPC3bits.T3IP = 1;                  //Passe en priorité basse
    IPC3bits.T3IS = 1;                  //Sous-priorité osef'

    IEC0bits.INT1IE = TRUE;             //Autorise interruption bouton
    IFS0bits.INT1IF = FALSE;            //Met le Flag à NO (attend bouton)
    IPC1bits.INT1IP = 2;                //Passe en priorité haute
    IPC1bits.INT1IS = 1;                //Sous-priorité osef'

    asm volatile("ei");                 //Autorise les macro-ASM (interruptions)
}

    u8 multiplex_status = 1;

void __ISR(_EXTERNAL_1_VECTOR, IPL2AUTO) note_pressed(void)
{
    multiplex_status++;
    if (multiplex_status == 5)
        multiplex_status = 1;

    if (multiplex_status == 1)
    {
        _A0 = 0;
        _A1 = 0;
        lcd_goto(1, 2);
        lcd_print("LED 1");

    }
    else if (multiplex_status == 2)
    {
        _A0 = 1;
        _A1 = 0;
        lcd_goto(1, 2);
        lcd_print("LED 2");
    }
    else if (multiplex_status == 3)
    {
        _A0 = 0;
        _A1 = 1;
        lcd_goto(1, 2);
        lcd_print("LED 3");
    }
    else if (multiplex_status == 4)
    {
        _A0 = 1;
        _A1 = 1;
        lcd_goto(1, 2);
        lcd_print("LED 4");
    }

    IFS0bits.INT1IF = FALSE;
}

int             main(void) {
    TRISFbits.TRISF1 = OUTPUT;          //RF1 = Led verte
    LATFbits.LATF1 = 0;               //Etat initial = éteint

    init_interrupt();
    init_lcd();
    init_multiplexer();

    lcd_print("4:1 Multiplexer");
    lcd_goto(1, 2);
    lcd_print("LED 1");

    while(PROCESS) {
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
}*/
