/*
 * File:   AudioBuffer.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

u16     processOSC(t_osc *OSC)
{
    if (notesON || (*OSC).Env.cur_env == REL)
    {
 /*       if (!(*OSC).phi) {
            (*OSC).phase = (!(*OSC).phase);
                (*OSC).phi = (*OSC).pitch; }
        if (!(*OSC).phi)
        {
            (*OSC).phase = (!(*OSC).phase);

            if ((*OSC).reste < 100)
                (*OSC).phi = (*OSC).pitch;
            else
            {
                (*OSC).reste -= 100;
                (*OSC).phi = (*OSC).pitch + 1;
            }
    //        (*OSC).cursor = (((*OSC).Env.amplitude_max - (*OSC).Env.cur_amplitude) / (*OSC).phi);
            (*OSC).reste += (*OSC).pitch_adjust;
        }
*/
//        generateur_enveloppe(&((*OSC).Env));
//        (*OSC).Env.cur_amplitude = 0x3FFF;

        if ((*OSC).presetOnde == SQU)
            return (tab_car[(*OSC).pos]);
        else if ((*OSC).presetOnde == TRI)
            return (tab_tri[(*OSC).pos]);
        else if ((*OSC).presetOnde == SAW)
            return (tab_saw[(*OSC).pos]);
//            return (onde_carre((*OSC).phase, (*OSC).Env.cur_amplitude));
/*        else if (presetOnde1 == SAW)
            return (onde_sawtooth());
        else if (presetOnde1 == TRI)
            return (onde_triangle());
*/    }
    (*OSC).reste = 0;
    return (0);
}

u16     generateAudioSample(void)
{
    u16     mix_sample = 1;
    u16     osc1_sample = 0;
    u16     osc2_sample = 0;
    u16     noise_sample = 0;

    osc1_sample = processOSC(&OSC1);
//    osc2_sample = processOSC(&OSC2);
//    noise_sample = processNoise();

//    if ((OSC1.phase && OSC2.phase) || (!OSC1.phase && !OSC2.phase))

/*  ---- OK ----
    if (OSC1.phase && OSC2.phase)
        mix_sample = (0xFFFF - ((0xFFFF - osc1_sample) + (0xFFFF - osc2_sample)));// + noise_sample;
    else if (!(OSC1.phase) && !(OSC2.phase))
        mix_sample = osc1_sample + osc2_sample;
    else if (!(OSC1.phase))
        mix_sample = (osc1_sample < 0xFFFF - osc2_sample ? 0xFFFF - (osc2_sample - osc1_sample) : osc1_sample - (0xFFFF - osc2_sample));
    else
        mix_sample = (0xFFFF - osc1_sample < osc2_sample ? 0xFFFF - (osc1_sample - osc2_sample) : osc2_sample - (0xFFFF - osc1_sample));
    ---- OK ----  */
    
    mix_sample = osc1_sample;

/*
    else if (OSC1.phase && (0xFFFF - osc1_sample > osc2_sample))
        mix_sample = 0xFFFF - (0xFFFF - osc1_sample + osc2_sample);
    else if (OSC1.phase && (0xFFFF - osc1_sample <= osc2_sample))
        mix_sample = (0xFFFF - osc1_sample) + osc2_sample;
    else if (OSC2.phase && (0xFFFF - osc2_sample > osc1_sample))
        mix_sample = 0xFFFF - (0xFFFF - osc2_sample + osc1_sample);
    else if (OSC2.phase && (0xFFFF - osc2_sample <= osc1_sample))
        mix_sample = (0xFFFF - osc2_sample) + osc1_sample;
*/

/*    if (osc1_sample >= 0x8000 && osc2_sample >= 0x8000)
        mix_sample = 0xFFFF - osc1_sample - osc2_sample;
    else if (osc1_sample <= 0x7FFF && osc2_sample <= 0x7FFF)
        mix_sample = osc2_sample + osc1_sample;
    else if (osc1_sample <= 0x7FFF && osc2_sample >= 0x8000)
        mix_sample = osc1_sample + (0xFFFF - osc2_sample);
    else if (osc1_sample >= 0x8000 && osc2_sample <= 0x7FFF)
        mix_sample = (0xFFFF - osc1_sample) + osc2_sample;*/
    if (mix_sample == 0)
        mix_sample = 1;

    return (mix_sample);
}


void __ISR(_TIMER_2_VECTOR, IPL4AUTO) sampleClock(void)
{
    if (notesON || OSC1.Env.cur_env == REL)// || OSC2.Env.cur_env == REL)
        DAC_value = generateAudioSample();
    else
        DAC_value = 1;
    

    IFS0bits.T2IF = FALSE;
}
