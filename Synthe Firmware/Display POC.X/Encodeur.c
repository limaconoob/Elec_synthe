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

# define _RD4       PORTDbits.RD4
# define _RD5       PORTDbits.RD5
# define LEFT       1
# define RIGHT      2

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

    waitXticks(30000);         //Wait 3s for LCD to power up to 5V
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

static void     init_things(void)
{
    TRISFbits.TRISF1 = OUTPUT;          //RF1 = Led circuit verte
    LATFbits.LATF1 = GND;               //Etat initial = éteint

    TRISDbits.TRISD8 = INPUT;           // Bouton Reset LCD
    TRISDbits.TRISD4 = INPUT;           // Pin A Encodeur
    TRISDbits.TRISD5 = INPUT;           // Pin B Encodeur
}

static void     print_value(s8 i)
{
    static u16  valeur = 0;

    valeur += i;
    if (valeur & 0x8000) {
        lcd_print("-");
        lcd_printnbr((valeur ^ 0xFFFF) + 1);
    }
    else
        lcd_printnbr(valeur);
    lcd_print("       ");
}

int             main(void) {

    u8          stock = _RD4;
    u8          prev_status = !(_RD4 ^ _RD5);
    u8          status;


    init_things();
    init_lcd();
    lcd_goto(1, 1);
    lcd_print("Encodeur :");


    while(PROCESS) {

        // RESET
        if (!PORTDbits.RD8) {
            lcd_command(0b00000001, 0);  //Clear display
            waitXticks(5000);
            lcd_command(0b00000000, 0);  //Set Diplay OFF
            waitXticks(1000);
        }
        // RESET



        status = _RD4 ^ _RD5;
        if (prev_status != status)
        {
            if (stock ^ _RD5) {
                lcd_goto(1, 2);
                lcd_print("Droite : ");
                print_value(1);
            }

            else {
                lcd_goto(1, 2);
                lcd_print("Gauche : ");
                print_value(-1);
            }

            stock = _RD4;

            prev_status = status;
        }

        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
}
*/