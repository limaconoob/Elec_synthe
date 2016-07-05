
#include "SynthyTwo.h"

void            clear_leds()
{
_LED0 = GND;
_LED1 = GND;
_LED2 = GND;
_LED3 = GND;
_LED4 = GND;
_LED5 = GND;
_LED6 = GND;
_LED7 = GND;
_LED8 = GND;
}

void            init_pins()
{
//-----------  SWITCH  -------------
TRIS_SW1 = INPUT;
TRIS_SW2 = INPUT;
TRIS_SW3 = INPUT;
TRIS_SW4 = INPUT;
TRIS_SW5 = INPUT;

//------------  LEDS  -------------
TRIS_LED0 = OUTPUT;
TRIS_LED1 = OUTPUT;
TRIS_LED2 = OUTPUT;
TRIS_LED3 = OUTPUT;
TRIS_LED4 = OUTPUT;
TRIS_LED5 = OUTPUT;
TRIS_LED6 = OUTPUT;
TRIS_LED7 = OUTPUT;
TRIS_LED8 = OUTPUT;
clear_leds();

//---------  Encodeurs  -------------
AD1PCFG = 0xFFFF;       //Tous les modules AN sont bypass
TRIS_EAA = INPUT;
TRIS_EAB = INPUT;
TRIS_EBA = INPUT;
TRIS_EBB = INPUT;
TRIS_ECA = INPUT;
TRIS_ECB = INPUT;
TRIS_EDA = INPUT;
TRIS_EDB = INPUT;

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


//----------  MULTIPLEX  -----------
TRIS_MULT0 = OUTPUT;
TRIS_MULT1 = OUTPUT;
_MULT0 = 1;
_MULT1 = 0;
}
