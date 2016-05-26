/*#include <p32xxxx.h>
#include <sys/attribs.h>

# define PROCESS 42
# define TRUE 1
# define FALSE 0
# define INPUT 1
# define OUTPUT 0
# define VCC 1
# define GND 0

# define MONTANT    0
# define DESCENDANT 1

# define CARRE      1
# define TRIANGLE   2
# define SAWTOOTH   3
# define SINUSOID   4

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


static void      lcd_printnbr(u16 value)
{
    int x = 0;

    if (value >= 10)
        lcd_printnbr(value / 10);
    lcd_command((value % 10) + '0', 1);
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


u16             oscillator(u8 onde, u16 value)
{
    static u8   mode = 0;
    static u16  beat = 0xFFFF;
    static u16  pwm = 0x0000;

    if (onde == TRIANGLE) {
        if (mode == MONTANT) {
            if (value < beat - 910) {
                value += 910;               // Fait monter la tension courante
            }
            else {
                value = beat;
                mode = DESCENDANT;          // Quand la tension arrive à beat
                beat = 0x0000;              // on inverse beat
            }
        }
        else if (mode == DESCENDANT) {
            if (value > beat + 910) {
                value -= 910;               // Fait descendre la tension
            }
            else {
                value = beat;
                mode = MONTANT;             // Quand la tension arrive à beat
                beat = 0xFFFF;              // on inverse beat
            }
        }
    }

    else if (onde == CARRE) {
        if (mode == MONTANT) {
            if (pwm < beat - 910) {         // Incrémente un compteur
                pwm += 910;                 // jusqu'à beat
            }
            else {                          // Quand le compteur arrive à beat
                mode = DESCENDANT;          // on inverse la tension courante
                value = 0x0000;
                beat = 0x0000;
                pwm = 0xFFFF;
            }
        }
        else if (mode == DESCENDANT) {
            if (pwm > beat + 910) {         // Décrémente un compteur
                pwm -= 910;                 // jusqu'à beat
            }
            else {                          // Quand le compteur arrive à beat
                mode = MONTANT;             // on inverse la tension courante
                value = 0xFFFF;
                beat = 0xFFFF;
                pwm = 0x0000;
            }
        }
    }

    else if (onde == SAWTOOTH) {
      //  if (mode == MONTANT) {
            if (pwm < beat - 910) {         // Incrémente un compteur
                pwm += 910;                 // jusqu'à beat
            }
            else {                          // Quand le compteur arrive à beat
                pwm = 0x0000;               // on inverse le compteur
            }
      //  }
      //  else if (mode == DESCENDANT) { // REVERSE SAWTOOTH
      //      if (pwm > beat) {               // Décrémente un compteur
      //          pwm -= 910;                 // jusqu'à beat
      //      }
      //      else if (pwm <= beat) {         // Quand le compteur arrive à beat
      //          pwm = 0xFFFF;               // on inverse le compteur
      //      }
      //  }
        value = pwm;
    }

    return (value);
}

u16         value = 0;
u8          onde = SAWTOOTH;

void __ISR(_TIMER_3_VECTOR, IPL1AUTO) Freq_48kHz(void)
{
    value = oscillator(onde, value);

    IFS0bits.T3IF = FALSE;
}


static void         print_onde(void)
{
    lcd_goto(9, 1);
    value = 0;
    if (onde == CARRE)
        lcd_print("CARRE   ");
    else if (onde == SAWTOOTH)
        lcd_print("SAWTOOTH");
    else if (onde == TRIANGLE)
        lcd_print("TRIANGLE");
}

static void      init_interrupt(void)
{
    //----- INTERRUPT -----
    INTCONbits.MVEC = TRUE;             //Multi-vector mode

    //-----   FLAG   -----
    IEC0bits.T3IE = TRUE;               //Autorise interruption timer2
    IFS0bits.T3IF = FALSE;              //Flag à NO (Attend signal pour blink)
    IPC3bits.T3IP = 1;                  //Passe en priorité basse
    IPC3bits.T3IS = 1;                  //Sous-priorité osef'

    asm volatile("ei");                 //Autorise les macro-ASM (interruptions)
}


static void         init_oscil(void)
{
    T3CON = 0;
    T2CON = 0;
    T2CONbits.T32 = TRUE;
    TMR2 = 0;
    PR2 = 50000;
    //PR2 = 633;
    T2CONbits.ON = TRUE;
}


int             main(void) {
    u8          status;
    u8          prev_status;

    TRISFbits.TRISF1 = OUTPUT;          //RF1 = Led verte
    LATFbits.LATF1 = 0;               //Etat initial = éteint
    TRISDbits.TRISD8 = INPUT;

    init_interrupt();
    init_lcd();
    init_oscil();

    lcd_goto(1, 1);
    lcd_print("Oscillo:");
    print_onde();

    while(PROCESS) {

        status = PORTDbits.RD8;
        if (!status && prev_status)
        {
            if (onde < 3)
                onde++;
            else
                onde = 1;
            print_onde();
        }
        prev_status = status;

        lcd_goto(1, 2);
        lcd_print("Tension: ");
        lcd_printnbr(value);
        lcd_print("      ");

        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
}
*/
