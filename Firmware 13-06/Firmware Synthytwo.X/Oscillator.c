/*
 * File:   Oscillator.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

void         init_oscil(void)
{
    IEC0bits.T2IE = TRUE;
    IFS0bits.T2IF = FALSE;
    IPC2bits.T2IP = 4;                //Priorité basse
    IPC2bits.T2IS = 1;

    T2CON = 0;
    TMR2 = 0;
    PR2 = 767;
//    PR2 = 1536;
    T2CONbits.ON = TRUE;
}

u16     value = 1;       // VALUE EST LA TENSION (1 à F FFF) QUI VA AU DAC !
u16     cursor;   // Donne la cadence d'augmentation de la tension
u8      reste = 0;
u16     pitch;
u8      pitch_adjust;
u8      phase = 1;
u16     phi = 0;



/*
u32             read_period_preset(void)
{
    u32         cur_periode;
    s8          cur_message;
    u32         centieme;

    cur_message = midi_note;
    cur_message += 1 * 12 * 12; //Preset octave    // Une octave de plus
    cur_message -= 3;        // Preset_demi_ton    // Trois demi-tons de moins
    if (cur_message - 21 > 0) {
        cur_message -= 21;
        cur_periode = tab_period[cur_message];
        centieme = tab_period[cur_message - 1] - tab_period[cur_message];
        centieme /= 100;
        if (!centieme)
            centieme = 1;
        cur_periode += 10 * centieme; // preset_centieme * centieme
        return (cur_periode);
    }
    else if (cur_message - 21 == 0) {
        cur_message -= 21;
        cur_periode = tab_period[cur_message];
        centieme = tab_period[cur_message] - tab_period[cur_message + 1];
        centieme /= 100;
        if (!centieme)
            centieme = 1;
        cur_periode += 10 * centieme // preset_centieme * centieme
        return (cur_periode);
    }
    return (tab_period[midi_note] - 21]);
}
*/

void         onde_triangle(void)
{
    static u8   mode = 0;
    u16         adj;    // Sert à ajuster la valeur pour garder la bonne fréquence

    adj = cursor/2 - 50;
    if (mode == DESCENDANT)
    {
        if ((value <= 0xFFFF - (2*cursor + adj) && value > 0x7FFF) || value <= 0x7FFF - (2*cursor + adj)) {
            value += (2*cursor + adj);
        }
        else if (value >= 0xFFFF - (2*cursor + adj)) {
            value = 0x0000;
        }
        else if (value >= 0x7FFF - (2*cursor + adj)) {
            value = 0x7FFF;
            mode = MONTANT;
        }
    }
    else
    {
        if ((value >= 0x0000 + (2*cursor + adj) && value < 0x8000) || value >= 0x8000 + (2*cursor + adj)) {
            value -= (2*cursor + adj);
        }
        else if (value <= 0x0000 + (2*cursor + adj)) {
            value = 0xFFFF;
        }
        else if (value <= 0x8000 + (2*cursor + adj)) {
            value = 0x8000;
            mode = DESCENDANT;
        }
    }
}


void         onde_sawtooth(void)
{
    u16         adj;    // Sert à ajuster la valeur pour garder la bonne fréquence

    adj = 1;
    if ((value >= (cursor + adj) && value < 0x8000) || value >= 0x8000 + (cursor + adj))
        value -= (cursor + adj);
    else if (value <= (cursor + adj))
        value = 0xFFFF;
    else if (value <= 0x8000 + (cursor + adj))
        value = 0x7FFF;
}

void            onde_carre()
{
    if (phase == 1)
        value = 0x7FFF;
    else
        value = 0x8000;
}

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) sampleClock(void)
{
    static u8       boool = 1;

    if (!boool)
    {
       if (notesON)
        {
            if (phi)
                phi--;
            else
            {
                if (reste < 100)
                {
                    phi = pitch - 1;
                    cursor = (0x8000 / pitch);
                }
                else
                {
                    reste -= 100;
                    phi = pitch;
                    cursor = (0x8000 / (pitch + 1));
                }
                reste += pitch_adjust;
           }

           if (phi == 1)
               phase = (!phase);

        onde_sawtooth();
//        onde_carre();
//        onde_triangle();

            if (value == 0)
               value = 1;
       }
       else
       {
          phi = 0;
          value = 1;
          reste = 0;
        }
    }
    boool = !boool;
    processMIDIBuffer();
    IFS0bits.T2IF = FALSE;
}
