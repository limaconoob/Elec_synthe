/* 
 * File:   Main.c
 * Author: JPEPZ
 *
 * Created on June 28, 2016, 8:00 PM
 */

#include "SynthyTwo.h"

t_osc       OSC1;
t_osc       OSC2;

u16     DAC_value = 1;


//----------------  ENCODEURS  -------------------
    u8          status = 0;
    u8          prev_status = 0;
//------------------------------------------------


//------------------  ONDES  ---------------------
u16             tab_car[1420];
u16             tab_saw[1420];
u16             tab_tri[1420];
u16             tab_sin[1420];
//------------------------------------------------


int main(int argc, char** argv) {

    init_pins();
    init_preset();
    init_lcd();
    lcd_print("EA  EB  EC  ED  ");
    lcd_print("SynthyTwo");
    lcd_goto(1, 2);
//    lcd_print("Coming Soon...");
    while (42)
        processEncodeur();
    return (0);
}

