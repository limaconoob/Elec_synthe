/*
 * File:   Preset.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

void    init_preset(void)
{
    OSC1.pitch = 0;
    OSC1.pitch_adjust = 0;
    OSC1.cursor = 0;
    OSC1.phase = 1;
    OSC1.phi = 0;
    OSC1.reste = 0;
    OSC1.presetOnde = SQU;

    OSC1.Env.Atk = 0b0000;
    OSC1.Env.Dec = 0b0000;
    OSC1.Env.Sus = 0b0000;
    OSC1.Env.Rel = 0b0000;
    OSC1.Env.amplitude_max = 0x3FFF;


    OSC2.pitch = 0;
    OSC2.pitch_adjust = 0;
    OSC2.cursor = 0;
    OSC2.phase = 1;
    OSC2.phi = 0;
    OSC2.reste = 0;
    OSC2.presetOnde = SQU;

    OSC2.Env.Atk = 0b1111;
    OSC2.Env.Dec = 0b0010;
    OSC2.Env.Sus = 0b0010;
    OSC2.Env.Rel = 0b0000;
    OSC2.Env.amplitude_max = 0x3FFF;
}
