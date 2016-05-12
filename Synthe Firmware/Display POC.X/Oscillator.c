/*#include <p32xxxx.h>
#include <sys/attribs.h>

# define PROCESS 42
# define TRUE 1
# define FALSE 0
# define INPUT 1
# define OUTPUT 0
# define VCC 1
# define GND 0

# define CARRE    1
# define TRIANGLE 2
# define SAWTOOTH 3
# define SINUSOID 4

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


static void      init_interrupt(void)
{
    //----- INTERRUPT -----
    INTCONbits.MVEC = TRUE;             //Multi-vector mode
    INTCONbits.INT1EP = 0;              //Prend INT1 au front descendant

    //-----   FLAG   -----
    IEC0bits.T2IE = TRUE;               //Autorise interruption timer2
    IFS0bits.T2IF = FALSE;              //Flag à NO (Attend signal pour blink)
    IPC2bits.T2IP = 1;                  //Passe en priorité basse
    IPC2bits.T2IS = 1;                  //Sous-priorité osef'

    asm volatile("ei");                 //Autorise les macro-ASM (interruptions)
}


static void         init_oscil(void)
{
    T2CON = 0;
    T2CONbits.ON = TRUE;
    TMR2 = 0;
    PR2 = 633;
}


u16             oscillator(u8 onde)
{
    u16         cur_tension;
    static u8   mode = 0;
    static u16  beat = 0xFFFF;
    static u16  pwm = 0x0000;

    if (onde == TRIANGLE) {
        if (mode == 0) {
            if (pwm < beat) {
                pwm += 910;                 // Fait monter la tension courante
                cur_tension = pwm;          // jusqu'à beat
            }
            else if (pwm >= beat) {
                cur_tension = beat;
                mode = 1;                   // Quand la tension arrive à beat
                beat = !(beat & 0xFFFF);    // on inverse beat
            }
        }
        else {
            if (pwm > beat) {
                pwm -= 910;                 // Fait descendre la tension
                cur_tension = pwm;          // courante jusqu'à beat
            }
            else if (pwm <= beat) {
                cur_tension = beat;
                mode = 0;                   // Quand la tension arrive à beat
                beat = !(beat & 0xFFFF);    // on inverse beat
            }
        }
    }

    else if (onde == CARRE) {
        if (mode == 0) {
            if (pwm < beat) {               // Incrémente un compteur
                pwm += 910;                 // jusqu'à beat
            }
            else if (pwm >= beat) {         // Quand le compteur arrive à beat
                mode = 1;                   // on inverse la tension courante
                cur_tension = !(cur_tension & 0xFFFF);
            }
        }
        else {
            if (pwm > beat) {               // Décrémente un compteur
                pwm -= 910;                 // jusqu'à beat
            }
            else if (pwm <= beat) {         // Quand le compteur arrive à beat
                mode = 0;                   // on inverse la tension courante
                cur_tension = !(cur_tension & 0xFFFF);
            }
        }
    }

    else if (onde == SAWTOOTH) {
        if (mode == 0) {
            if (pwm < beat) {               // Incrémente un compteur
                pwm += 910;                 // jusqu'à beat
            }
            else if (pwm >= beat) {         // Quand le compteur arrive à beat
                pwm = !(pwm & 0xFFFF);      // on inverse le compteur
            }
        }
        else {
            if (pwm > beat) {               // Décrémente un compteur
                pwm -= 910;                 // jusqu'à beat
            }
            else if (pwm <= beat) {         // Quand le compteur arrive à beat
                pwm = !(pwm & 0xFFFF);      // on inverse le compteur
            }
        }
        cur_tension = pwm;
    }

    return (cur_tension);
}


void __ISR(_TIMER_2_VECTOR, IPL1AUTO) Freq_48kHz(void)
{
    lcd_goto(1, 2);
    lcd_print("Tension: ");
    lcd_print(lcd_printnbr(oscillator(TRIANGLE)));
    IFS0bits.T2IF = FALSE;
}


int             main(void) {
    TRISFbits.TRISF1 = OUTPUT;          //RF1 = Led verte
    LATFbits.LATF1 = 0;               //Etat initial = éteint

    init_interrupt();
    init_lcd();
    init_oscil();

    lcd_print("Oscillateur");
    lcd_goto(1, 2);
    lcd_print("Tension:     0");

    while(PROCESS) {
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
}*/
