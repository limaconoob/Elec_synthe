/*
 * File:   Preset.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

void   init_preset2(void)
{
  cur_preset.ARPG_Type = 0;
  cur_preset.ARPG_Speed = 1;
  cur_preset.FILT_Atk = 0;
  cur_preset.FILT_Dec = 0;
  cur_preset.FILT_Sus = 0;
  cur_preset.FILT_Rel = 0;

  cur_preset.MIX_VCO1 = 99;
  cur_preset.MIX_VCO2 = 99;
  cur_preset.MIX_NOIS = 0;
  cur_preset.MIX_Glide = 0;
  cur_preset.Env.Atk = 0;
  cur_preset.Env.Dec = 0;
  cur_preset.Env.Sus = 0;
  cur_preset.Env.Rel = 0;
}

void    init_preset(void)
{
    OSC1.pitch = 0;
    OSC1.pitch_adjust = 0;
    OSC1.cursor = 0;
    OSC1.phase = 1;
    OSC1.phi = 0;
    OSC1.reste = 0;

    OSC1.presetOnde = SIN;
    OSC1.presetOct = 2;
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

    OSC2.presetOnde = SIN;
    OSC2.presetOct = 2;
    OSC2.presetPitch = 5;
    OSC2.presetFine = 70;
    OSC2.Env.Atk = 0;
    OSC2.Env.Dec = 0;
    OSC2.Env.Sus = 15;
    OSC2.Env.Rel = 0;
    init_preset2();
}
