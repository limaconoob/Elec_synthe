/* 
 * File:   Main.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:16 AM
 */

#include "SynthyTwo.h"

u16     cursor = 1;   // Donne la cadence d'augmentation de la tension
u16     pitch = 1;
u8      pitch_adjust = 1;
u8      reste = 1;
u8      phase = 1;
u16     phi = 1;

u16     DAC_value = 1;

u8          cur_env = 0;            // mode courant (ATK, DEC, SUS, REL)
u16         compteur = 0;

u16         seuil_max = 0x3FFF;         // seuil_max coté bas => 0x7FFF / 2 = 0x3FFF
                                        // seuil_max coté haut => 0xFFFF / 2 = 0xBFFF
u16         cur_seuil = 0;              // seuil_bas = cur_seuil ; seuil_haut = 0xFFFF - cur_seuil

u16         amplitude_max = 0x7FFF;     // seuil_max coté bas => 0x7FFF / 2 = 0x3FFF
                                        // seuil_max coté haut => 0xFFFF / 2 = 0xBFFF
u16         cur_amplitude = 0;          // seuil_bas = cur_seuil ; seuil_haut = 0xFFFF - cur_seuil

u16         env_reste = 0;

u8          presetAtk = 0b0001;          // en secondes
u8          presetDec = 0b0001;          // en secondes
u8          presetRel = 0b0001;          // en secondes
//u8          presetSus = 0b0110;          // en seuil -> limite pour le DAC
u16         presetSus = 0x2000;
u8          presetOnde =  TRIANGLE;

void    init(void)
{
    INTCONbits.MVEC = TRUE;           //Multi-vector interrupt mode
    asm volatile("ei");               //Autorise les macro-ASM (interruptions)

    phi = 0;

    create_tab_period();                        // Remplit le tableau avec les périodes
    init_lcd();
    init_oscil();
    init_MIDI();
    init_dac();
}

int     main(int argc, char** argv)
{
    init();

    lcd_print("Synthy two V0.1");

    while(PROCESS)
    {
        processMIDIBuffer();
//        fillAudioBuffer();
//        fillAudioBuffer();
//        fillAudioBuffer();
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }


}

