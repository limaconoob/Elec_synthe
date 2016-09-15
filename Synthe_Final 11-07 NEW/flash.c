
#include "SynthyTwo.h"

/*
    --------------------- FLASH ------------------------
    int x;

	for(x =0; x < sizeof(databuff); x++)
		databuff[x] = 'A';

//    NVMUnlock();
   NVMProgram((void *)(NVM_PROGRAM_PAGE + NVM_PAGE_SIZE), (const void *)databuff, sizeof(databuff), (void*) pagebuff);

	for(x =0; x < sizeof(databuff); x++)
		databuff[x] = 'B';
   TRISDbits.TRISD8 = 1;

    while(1)
    {
        if (PORTDbits.RD8 == 0)
           NVMProgram((void *)(NVM_PROGRAM_PAGE + NVM_PAGE_SIZE), (const void *)databuff, sizeof(databuff), (void*) pagebuff);

        lcd_print((void *)(NVM_PROGRAM_PAGE + NVM_PAGE_SIZE));
        processMIDIBuffer();
//      scan_boutons();
//      scan_encodeurs();
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
*/

unsigned int pagebuff[1024];
unsigned int databuff[128];

#define NVM_PROGRAM_PAGE 0xbd000000
#define NVM_PAGE_SIZE	4096


void  preset_save(char *name, u8 bank, u8 num)
{
    presets[bank][num][0] = 0;
    presets[bank][num][0] |= OSC1.presetOnde << 6;
    presets[bank][num][0] |= OSC2.presetOnde << 4;
    presets[bank][num][0] |= cur_preset.MIX_Glide;
    presets[bank][num][1] = 0;
    presets[bank][num][1] |= OSC1.presetPitch << 4;
    presets[bank][num][1] |= OSC2.presetPitch;
    presets[bank][num][2] = OSC1.presetFine;
    presets[bank][num][3] = OSC2.presetFine;
    presets[bank][num][4] = 0;
    presets[bank][num][4] |= OSC1.presetOct << 5;
    presets[bank][num][4] |= OSC2.presetOct << 2;
    presets[bank][num][5] = 0;
    presets[bank][num][5] |= OSC1.Env.Atk << 4;
    presets[bank][num][5] |= OSC1.Env.Dec;
    presets[bank][num][6] = 0;
    presets[bank][num][6] |= OSC1.Env.Sus << 4;
    presets[bank][num][6] |= OSC1.Env.Rel;
    presets[bank][num][7] = 0;
    presets[bank][num][7] |= OSC2.Env.Atk << 4;
    presets[bank][num][7] |= OSC2.Env.Dec;
    presets[bank][num][8] = 0;
    presets[bank][num][8] |= OSC2.Env.Sus << 4;
    presets[bank][num][8] |= OSC2.Env.Rel;
    presets[bank][num][9] = cur_preset.MIX_VCO1;
    presets[bank][num][10] = cur_preset.MIX_VCO2;
    presets[bank][num][11] = cur_preset.MIX_NOIS;
    presets[bank][num][12] = 0;
    presets[bank][num][12] |= cur_preset.Env.Atk << 4;
    presets[bank][num][12] |= cur_preset.Env.Dec;
    presets[bank][num][13] = 0;
    presets[bank][num][13] |= cur_preset.Env.Sus << 4;
    presets[bank][num][13] |= cur_preset.Env.Rel;
    u8 i;
    i = 0;
    while (i < 12)
    {
         presets[bank][num][14 + i] = name[i];
         i++;
    }

    _LED3 = 1;
    NVMProgram(flash_adress, (const void *)&presets, sizeof(presets), (void*) pagebuff);
    _LED4 = 1;
}

void  preset_load(u8 bank, u8 num)
{
    OSC1.presetOnde = (presets[bank][num][0] & 0xC0) >> 6;
    OSC2.presetOnde = (presets[bank][num][0] & 0x30)  >> 4;
    cur_preset.MIX_Glide = (presets[bank][num][0] & 0x0F);
    OSC1.presetPitch = (presets[bank][num][1] & 0xF0) >> 4;
    OSC2.presetPitch = (presets[bank][num][1] & 0x0F);
    OSC1.presetFine = (presets[bank][num][2]);
    OSC2.presetFine = (presets[bank][num][3]);
    OSC1.presetOct = (presets[bank][num][4] & 0xE0) >> 5;
    OSC2.presetOct = (presets[bank][num][4] & 0x1C) >> 2;
    OSC1.Env.Atk = (presets[bank][num][5] & 0xF0) >> 4;
    OSC1.Env.Dec = (presets[bank][num][5] & 0x0F);
    OSC1.Env.Sus = (presets[bank][num][6] & 0xF0) >> 4;
    OSC1.Env.Rel = (presets[bank][num][6] & 0x0F);
    OSC2.Env.Atk = (presets[bank][num][7] & 0xF0) >> 4;
    OSC2.Env.Dec = (presets[bank][num][7] & 0x0F);
    OSC2.Env.Sus = (presets[bank][num][8] & 0xF0) >> 4;
    OSC2.Env.Rel = (presets[bank][num][8] & 0x0F);
    cur_preset.MIX_VCO1 = (presets[bank][num][9]);
    cur_preset.MIX_VCO2 = (presets[bank][num][10]);
    cur_preset.MIX_NOIS = (presets[bank][num][11]);
    cur_preset.Env.Atk = (presets[bank][num][12] & 0xF0) >> 4;
    cur_preset.Env.Dec = (presets[bank][num][12] & 0x0F);
    cur_preset.Env.Sus = (presets[bank][num][13] & 0xF0) >> 4;
    cur_preset.Env.Rel = (presets[bank][num][13] & 0x0F);
}

void  init_factoryPreset(void)
{
  int x = 0;
  int y = 0;
  int z = 0;
  while (x < 6)
  {
      while (y < 99)
      {
          while (z < 30)
          {
              presets[x][y][z] = 0;
              z++;
          }
          z = 0;
          y++;
      }
      y = 0;
      x++;
  }

}
