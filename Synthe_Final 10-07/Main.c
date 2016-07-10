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

    u8          saveLoad = 0;
u8      cursor_pos = 0;

//------------------  ONDES  ---------------------
u16             tab_car[1420];
u16             tab_saw[1420];
u16             tab_tri[1420];
u16             tab_sin[1420];



unsigned int pagebuff[1024];
unsigned int databuff[128];

#define NVM_PROGRAM_PAGE 0xbd000000
#define NVM_PAGE_SIZE	4096
#include <plib.h>



int main(int argc, char** argv) {

/*
    --------------------- FLASH ------------------------
    int x;

	for(x =0; x < sizeof(databuff); x++)
		databuff[x] = 'A';

//    NVMUnlock();
   NVMProgram((void *)(NVM_PROGRAM_PAGE + NVM_PAGE_SIZE), (const void *)databuff, sizeof(databuff), (void*) pagebuff);

	for(x =0; x < sizeof(databuff); x++)
		databuff[x] = 'B';
   TRISDbits.TRISD8 = 1;

    while(1)
    {
        if (PORTDbits.RD8 == 0)
           NVMProgram((void *)(NVM_PROGRAM_PAGE + NVM_PAGE_SIZE), (const void *)databuff, sizeof(databuff), (void*) pagebuff);

        lcd_print((void *)(NVM_PROGRAM_PAGE + NVM_PAGE_SIZE));
        processMIDIBuffer();
//      scan_boutons();
//      scan_encodeurs();
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
*/

    INTCONbits.MVEC = TRUE;           //Multi-vector interrupt mode
    asm volatile("ei");               //Autorise les macro-ASM (interruptions)

    init_Menus();
    init_pins();
    init_lcd();
    init_preset();
    create_tab_env();
    create_tab_frequenz();
    create_tab_period();
    init_MIDI();
    init_pwm();
    init_dac();
    update_menu();

    while (42) {
        boutons();
        processEncodeur();
        WDTCONbits.WDTCLR = 1;
    }
    return (0);
}

