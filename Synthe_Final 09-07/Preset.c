/*
 * File:   Preset.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

void   init_preset2(void)
{
  cur_preset.FILT_Type = 0;
  cur_preset.FILT_Freq = 0;
  cur_preset.FILT_Reso = 0;
  cur_preset.FILT_EnvMod = 0;
  cur_preset.FILT_Atk = 0;
  cur_preset.FILT_Dec = 0;
  cur_preset.FILT_Sus = 0;
  cur_preset.FILT_Rel = 0;

  cur_preset.MIX_VCO1 = 99;
  cur_preset.MIX_VCO2 = 99;
  cur_preset.MIX_NOIS = 0;
  cur_preset.MIX_Glide = 0;
  cur_preset.NOIS_Atk = 0;
  cur_preset.NOIS_Dec = 0;
  cur_preset.NOIS_Sus = 0;
  cur_preset.NOIS_Rel = 0;
}

void    init_preset(void)
{
    OSC1.pitch = 0;
    OSC1.pitch_adjust = 0;
    OSC1.cursor = 0;
    OSC1.phase = 1;
    OSC1.phi = 0;
    OSC1.reste = 0;

    OSC1.presetOnde = SQU;
    OSC1.presetOct = 3;
    OSC1.presetPitch = 5;
    OSC1.presetFine = 50;
    OSC1.Env.Atk = 0;
    OSC1.Env.Dec = 0;
    OSC1.Env.Sus = 15;
    OSC1.Env.Rel = 0;

    OSC1.pos = 0;
    OSC1.jumper = 0;
    OSC1.jump_adjust = 0;
    OSC1.reste = 0;


    OSC2.pitch = 0;
    OSC2.pitch_adjust = 0;
    OSC2.cursor = 0;
    OSC2.phase = 1;
    OSC2.phi = 0;
    OSC2.reste = 0;

    OSC2.presetOnde = SQU;
    OSC2.presetOct = 3;
    OSC2.presetPitch = 5;
    OSC2.presetFine = 50;
    OSC2.Env.Atk = 0;
    OSC2.Env.Dec = 0;
    OSC2.Env.Sus = 15;
    OSC2.Env.Rel = 0;
    init_preset2();
}
