/*
 * File:   AudioBuffer.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

u16     multiplySample(u16 value, u8 x, u8 base)
{
    if (value <= 0x7FFF)
        return ((value * x) / base);
    else
        return (0xFFFF - (((0xFFFF - value) * x) / base));
}

u16     processOSC(t_osc *OSC)
{
    if ((*OSC).Env.cur_env)
    {
        if ((*OSC).presetOnde == SQU)
            return (tab_car[(*OSC).pos]);
        else if ((*OSC).presetOnde == TRI)
            return (tab_tri[(*OSC).pos]);
        else if ((*OSC).presetOnde == SAW)
            return (tab_saw[(*OSC).pos]);
        else if ((*OSC).presetOnde == SIN)
            return (tab_sin[(*OSC).pos]);
    }
    return (1);
}

u16     addSamples(u32 sample1, u32 sample2)
{
    u16     mix_sample = 1;

    if (sample1 > 0x7FFF && sample2 > 0x7FFF)
        mix_sample = 0xFFFF - (((0xFFFF - sample1) + (0xFFFF - sample2)) / 2);
    else if (sample1 <= 0x7FFF && sample2 <= 0x7FFF)
        mix_sample = (sample1 + sample2) / 2;
    else if (sample1 <= 0x7FFF)
    {
        if (sample2 < 0xFFFF - sample1)
            mix_sample = (sample2 / 2 - (0xFFFF - sample1) / 2);
        else
            mix_sample = 0xFFFF  - ((0xFFFF - sample2) / 2 - (sample1 / 2));
     }
    else
    {
        if (sample1 < 0xFFFF - sample2)
            mix_sample = (sample1 / 2 - (0xFFFF - sample2) / 2);
        else
            mix_sample = 0xFFFF  - ((0xFFFF - sample1) / 2 - (sample2 / 2));
    }
    return (mix_sample);
}

u16     generateAudioSample(void)
{
    u16     mix_sample = 1;
    u16     osc1_sample = 1;
    u16     osc2_sample = 1;
    u16     noise_sample = 0;
    static u16    noise = 0;

    if (cur_preset.ARPG_Type && notesON > 1)
        arpeggios();

    OSC1.Env.compteur++;
    osc1_sample = processOSC(&OSC1);
    osc1_sample = generateur_enveloppe(osc1_sample, &OSC1.Env);
    osc1_sample = multiplySample(osc1_sample, cur_preset.MIX_VCO1, 100);

    OSC2.Env.compteur++;
    osc2_sample = processOSC(&OSC2);
    osc2_sample = generateur_enveloppe(osc2_sample, &OSC2.Env);
    osc2_sample = multiplySample(osc2_sample, cur_preset.MIX_VCO2, 100);

    if (noise)
        noise--;
    else
        noise = 1000;
    cur_preset.Env.compteur++;
    noise_sample = tab_noi[noise];
    noise_sample = (noise_sample > 0x7FFF ? noise_sample - 0x4000 : noise_sample + 0x4000);
    noise_sample = generateur_enveloppe(noise_sample, &cur_preset.Env);
    noise_sample = multiplySample(noise_sample, cur_preset.MIX_NOIS, 100);
/*
    osc1_sample = addSamples(osc1_sample, noise_sample);
    osc2_sample = addSamples(osc2_sample, noise_sample);
    mix_sample = addSamples(osc1_sample, osc2_sample);
 */
    mix_sample = addSamples(addSamples(osc1_sample, osc2_sample), noise_sample);

    mix_sample = (mix_sample ? mix_sample : 1);

    return (mix_sample);
}

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) sampleClock(void)
{
    processMIDIBuffer();
    if (OSC1.Env.cur_env || OSC2.Env.cur_env)
        DAC_value = generateAudioSample();
    else
        DAC_value = 1;
    
    IFS0bits.T2IF = FALS;
}
