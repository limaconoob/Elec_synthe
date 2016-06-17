/*
 * File:   AudioBuffer.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

u16     generateAudioSample(void)
{
    u16     cur_sample = 1;
    static u8   osc = 1;

    //-------------- OSCILLATEUR 1 ------------------
    if ((notesON || cur_env1 == REL) && osc)
    {
        if (!phi1)
        {
            phase1 = (!phase1);

            if (reste < 100)
                phi1 = pitch;
            else
            {
                reste -= 100;
                phi1 = pitch + 1;
            }
            cursor1 = ((seuil_min1 - cur_amplitude1) / phi1);
            reste += pitch_adjust;
        }

        generateur_enveloppe();

        if (presetOnde1 == CARRE)
            cur_sample = onde_carre();
        else if (presetOnde1 == SAWTOOTH)
            cur_sample = onde_sawtooth();
        else if (presetOnde1 == TRIANGLE)
            cur_sample = onde_triangle();

        if (cur_sample == 0)
            cur_sample = 1;

        if (!(cur_env2 == ATK && cur_env1 == REL))
            osc = 0;
    }

    //-------------- OSCILLATEUR 2 ------------------
    else if ((notesON || cur_env2 == REL) && !osc)
    {
        if (!phi2)
        {
            phase2 = (!phase2);

            if (reste < 100)
                phi2 = pitch;
            else
            {
                reste -= 100;
                phi2 = pitch + 1;
            }
            cursor2 = ((seuil_min2 - cur_amplitude2) / phi2);
            reste += pitch_adjust;
        }

        generateur_enveloppe2();

        if (presetOnde2 == CARRE)
            cur_sample = onde_carre2();
        else if (presetOnde2 == SAWTOOTH)
            cur_sample = onde_sawtooth2();
        else if (presetOnde2 == TRIANGLE)
            cur_sample = onde_triangle2();

        if (cur_sample == 0)
            cur_sample = 1;

        if (!(cur_env1 == ATK && cur_env2 == REL))
            osc = 1;
    }

    //----------------- RESET ----------------------
    else
    {
         cur_sample = 1;
         reste = 0;
    }
    return (cur_sample);
}


void __ISR(_TIMER_2_VECTOR, IPL4AUTO) sampleClock(void)
{
    if (notesON || cur_env1 == REL || cur_env2 == REL)
        DAC_value = generateAudioSample();
    else
        DAC_value = 1;
    IFS0bits.T2IF = FALSE;
}
