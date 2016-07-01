/*
 * File:   Display.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

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

void      waitXticks(u32 x)
{
    u32 i = 0;
    while (i < x)
        i++;
    return;
}

void      lcd_pulse(void)
{
    _E = 0;
    waitXticks(1);
    _E = 1;
    waitXticks(1);        //enable pulse lasts 100us
    _E = 0;
    waitXticks(1);
    return;
}

void      write4bits(u8 value)
{
    _DB4 = (value & 0x01);
    _DB5 = ((value >> 1) & 0x01);
    _DB6 = ((value >> 2) & 0x01);
    _DB7 = ((value >> 3) & 0x01);
    lcd_pulse();
    return;
}

void      lcd_command(u8 value, u8 rs)
{
    static u8 pulseSent = 0;     //protection octet non transmis

    if (pulseSent)
    {
        lcd_pulse();
        pulseSent = 0;
    }

    if (rs)                  //set RS to write or read
        _RS = 1;
    else
        _RS = 0;
    write4bits(value >> 4);
    pulseSent = 1;
    write4bits(value);
    pulseSent = 0;

    return;
}


void      lcd_printnbr(u16 value)
{
    if (value >= 10)
        lcd_printnbr(value / 10);
    lcd_command((value % 10) + '0', 1);
    return;
}


void      lcd_print(char *str)
{
    int x = 0;

    while (str[x])
    {
        lcd_command(str[x], 1);
        x++;
    }
    return;
}


void      lcd_goto(u8 col, u8 line)
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

void      init_lcd(void)
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
