/* 
 * File:   Main.c
 * Author: JPEPZ
 *
 * Created on June 28, 2016, 8:00 PM
 */

#include "SynthyTwo.h"

t_osc       OSC1;
t_osc       OSC2;
t_preset    cur_preset;
char        *print_menu[8];


u16     DAC_value = 1;
u16	coeff = 0;

u16     arpeg = 0;


//----------------  ENCODEURS  -------------------
    u8          status_ec = 0;
    u8          prev_status_ec = 0;
//------------------------------------------------

//-----------------  BOUTONS  --------------------
    u8          status_bt = 0;
    u8          prev_status_bt = 0;
    u8          cur_menu = 0;
//------------------------------------------------

    u8          saveLoad = 0;
u8      cursor_pos = 0;

//------------------  ONDES  ---------------------
u16             tab_car[1420];
u16             tab_saw[1420];
u16             tab_tri[1420];
u16             tab_sin[1420];
u16             tab_noi[1000];

u32             flash_adress;

#include <plib.h>

int main(int argc, char** argv) {

//    BMXPUPBA = BMXPFMSZ - 0x4000;

//  sizeof(presets) = 17820 bits
//  0x5000 = 20480

    INTCONbits.MVEC = TRUE;           //Multi-vector interrupt mode
    asm volatile("ei");               //Autorise les macro-ASM (interruptions)

//    memcpy(&presets, flash_adress, sizeof(presets));

    init_Menus();
    init_pins();
    init_lcd();
    init_preset();
    create_tab_env();
    create_tab_frequenz();
    create_tab_period();
    init_MIDI();
//    init_pwm();
    init_dac();
    update_menu();

    while (42)
    {
        boutons();
        processEncodeur();
        WDTCONbits.WDTCLR = 1;
    }
    return (0);
}

