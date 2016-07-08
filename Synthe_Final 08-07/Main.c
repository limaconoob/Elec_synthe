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


//----------------  ENCODEURS  -------------------
    u8          status_ec = 0;
    u8          prev_status_ec = 0;
//------------------------------------------------

//-----------------  BOUTONS  --------------------
    u8          status_bt = 0;
    u8          prev_status_bt = 0;
    u8          cur_menu = 0;
//------------------------------------------------


//------------------  ONDES  ---------------------
u16             tab_car[1420];
u16             tab_saw[1420];
u16             tab_tri[1420];
u16             tab_sin[1420];
//------------------------------------------------


int main(int argc, char** argv) {

    INTCONbits.MVEC = TRUE;           //Multi-vector interrupt mode
    asm volatile("ei");               //Autorise les macro-ASM (interruptions)
/*    U1OTGIR = 0;
    U1OTGIE = 0;
    U1OTGSTAT = 0;*/
    init_pins();
    init_lcd();
    create_tab_env();
    create_tab_frequenz();
    create_tab_period();
    init_preset();
    init_Menus();
    init_MIDI();
    init_pwm();

    init_dac();
/*    PMCON = 0;
    PMAEN = 0;
    PMMODE = 0;
    PMADDR = 0;
    PMSTAT = 0;
    PMDIN = 0;
    PMDOUT = 0;
    AD1CON1 = 0;
    AD1CON2 = 0;
    AD1CON3 = 0;
    AD1CHS = 0;
    AD1CSSL = 0;
    U2STA = 0;
    U2MODE = 0;*/
    update_menu();

//    lcd_print("Coming Soon...");
    while (42) {
        boutons();
        processEncodeur();
    }
    return (0);
}

