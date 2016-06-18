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

            if (reste1 < 100)
                phi1 = pitch1;
            else
            {
                reste1 -= 100;
                phi1 = pitch1 + 1;
            }
            cursor1 = ((seuil_min1 - cur_amplitude1) / phi1);
            reste1 += pitch_adjust1;
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

            if (reste2 < 100)
                phi2 = pitch2;
            else
            {
                reste2 -= 100;
                phi2 = pitch2 + 1;
            }
            cursor2 = ((seuil_min2 - cur_amplitude2) / phi2);
            reste2 += pitch_adjust2;
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
         reste1 = 0;
         reste2 = 0;
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
