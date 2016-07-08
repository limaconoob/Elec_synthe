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
    return (0);
}

u16     generateAudioSample(void)
{
    u16     mix_sample = 1;
    u16     osc1_sample = 0;
    u16     osc2_sample = 0;
    u16     noise_sample = 0;
	static u16 noise = 0;

    OSC1.Env.compteur++;
    osc1_sample = processOSC(&OSC1);
    osc1_sample = generateur_enveloppe(osc1_sample, &OSC1.Env);
    osc1_sample = multiplySample(osc1_sample, cur_preset.MIX_VCO1, 100);

    OSC2.Env.compteur++;
    osc2_sample = processOSC(&OSC2);
    osc2_sample = generateur_enveloppe(osc2_sample, &OSC2.Env);
    osc2_sample = multiplySample(osc2_sample, cur_preset.MIX_VCO2, 100);

    noise = (noise == 1000 ? 0 : noise);
    noise_sample = tab_noi[noise++];


    if (osc1_sample > 0x7FFF && osc2_sample > 0x7FFF)
        mix_sample = 0xFFFF - (((0xFFFF - osc1_sample) + (0xFFFF - osc2_sample)) / 2);
    else if (osc1_sample <= 0x7FFF && osc2_sample <= 0x7FFF)
        mix_sample = (osc1_sample + osc2_sample) / 2;
    else if (osc1_sample <= 0x7FFF)
    {
        if (osc1_sample < 0xFFFF - osc2_sample)
            mix_sample = 0xFFFF - ((0xFFFF - osc2_sample) / 2 + osc1_sample / 2);
        else
            mix_sample = osc1_sample / 2 + (0xFFFF - osc2_sample) / 2;
    }
    else
    {
        if (osc2_sample < 0xFFFF - osc1_sample)
            mix_sample = 0xFFFF - ((0xFFFF - osc1_sample) / 2 + osc2_sample / 2);
        else
            mix_sample = osc2_sample / 2 + (0xFFFF - osc1_sample) / 2;
    }

/*
    ---------------  NOISE -------------------
    if (noise_sample > 0x7FFF && mix_sample > 0x7FFF)
        mix_sample = 0xFFFF - (((0xFFFF - noise_sample) + (0xFFFF - mix_sample)) / 2);
    else if (noise_sample <= 0x7FFF && mix_sample <= 0x7FFF)
        mix_sample = (noise_sample + mix_sample) / 2;
    else if (noise_sample <= 0x7FFF)
    {
        if (noise_sample < 0xFFFF - mix_sample)
            mix_sample = 0xFFFF - ((0xFFFF - mix_sample) / 2 + noise_sample / 2);
        else
            mix_sample = noise_sample / 2 + (0xFFFF - mix_sample) / 2;
    }
    else
    {
        if (mix_sample < 0xFFFF - noise_sample)
            mix_sample = 0xFFFF - ((0xFFFF - noise_sample) / 2 + mix_sample / 2);
        else
            mix_sample = mix_sample / 2 + (0xFFFF - noise_sample) / 2;
    }
*/

    mix_sample = (mix_sample / presetGlide) * 16;
    
    return (mix_sample);
}

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) sampleClock(void)
{
    processMIDIBuffer();
    if (OSC1.Env.cur_env || OSC2.Env.cur_env)
        DAC_value = generateAudioSample();
    else
        DAC_value = 1;
    
    IFS0bits.T2IF = FALSE;
}
