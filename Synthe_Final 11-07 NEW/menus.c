
#include "SynthyTwo.h"

print printmenu_tab[8][4];
menus menu_tab[10][4];
u8*   params_tab[10][4];
char *print_menu[9];
char    name_buf[13];
// VCO1 - VCO = 0;
//      - Env = 1;
// VCO2 - VCO = 2;
//      - Env = 3;
// FILT - FIL = 4;
//      - Env = 5;
// MIX  - Mix = 6;
//      - Env = 7;
//static    u8     cur_menu = 6;

void  printVCO_Wave(u8 *Wave)
{
 if (*Wave == SQU)
    lcd_print("SQU");
  else if (*Wave == TRI)
    lcd_print("TRI");
  else if (*Wave == SAW)
    lcd_print("SAW");
  else
    lcd_print("SIN");
}

void  updateVCO_Wave(u8 sens, u8 *Wave)
{
  if (!sens && *Wave)
    *Wave -= 1;
  else if (sens && *Wave < 3)
    *Wave += 1;

  if (Wave == &OSC1.presetOnde)
      OSC1.presetOnde = *Wave;
  else
      OSC2.presetOnde = *Wave;

  printVCO_Wave(Wave);
 }

void  printVCO_Oct(u8 *Oct)
{
  lcd_goto(5, 2);

  if (*Oct == 0)
    lcd_print("-3");
  else if (*Oct == 1)
    lcd_print("-2");
  else if (*Oct == 2)
    lcd_print("-1");
  else if (*Oct == 3)
    lcd_print(" 0");
  else if (*Oct == 4)
    lcd_print("+1");
  else if (*Oct == 5)
    lcd_print("+2");
  else if (*Oct == 6)
    lcd_print("+3");
  else if (*Oct == 7)
    lcd_print("+4");
}

void  updateVCO_Oct(u8 sens, u8 *Oct)
{
  if (!sens && *Oct)
    *Oct -= 1;
  else if (sens && *Oct < 7)
    *Oct += 1;

  if (Oct == &OSC1.presetOct)
      calculatePitch(read_period_preset(&OSC1), &OSC1);
  else
      calculatePitch(read_period_preset(&OSC2), &OSC2);
  printVCO_Oct(Oct);
}

void  printVCO_Pitch(u8 *pitch)
{
  lcd_goto(9, 2);
  if (*pitch == 0)
    lcd_print("-5");
  else if (*pitch == 1)
    lcd_print("-4");
  else if (*pitch == 2)
    lcd_print("-3");
  else if (*pitch == 3)
    lcd_print("-2");
  else if (*pitch == 4)
    lcd_print("-1");
  else if (*pitch == 5)
    lcd_print(" 0");
  else if (*pitch == 6)
    lcd_print("+1");
  else if (*pitch == 7)
    lcd_print("+2");
  else if (*pitch == 8)
    lcd_print("+3");
  else if (*pitch == 9)
    lcd_print("+4");
  else if (*pitch == 10)
    lcd_print("+5");
  else if (*pitch == 11)
    lcd_print("+6");
}

void  updateVCO_Pitch(u8 sens, u8 *pitch)
{
  if (!sens && *pitch == 0)
    {
      if (pitch == &OSC1.presetPitch && OSC1.presetOct)
	{
	  updateVCO_Oct(0, &OSC1.presetOct);
	  *pitch = 11;
	}
      else if (pitch == &OSC2.presetPitch && OSC2.presetOct)
	{
	  updateVCO_Oct(0, &OSC2.presetOct);
	  *pitch = 11;
	}
    }
  else if (!sens && *pitch)
    *pitch -= 1;
  else if (sens && *pitch < 11)
    *pitch += 1;
  else if (sens && *pitch == 11)
    {
      if (pitch == &OSC1.presetPitch && OSC1.presetOct < 7)
	{
	  updateVCO_Oct(1, &OSC1.presetOct);
	  *pitch = 0;
	}
      else if (pitch == &OSC2.presetPitch && OSC2.presetOct < 7)
	{
	  updateVCO_Oct(1, &OSC2.presetOct);
	  *pitch = 0;
	}
    }

  if (pitch == &OSC1.presetPitch)
      calculatePitch(read_period_preset(&OSC1), &OSC1);
  else
      calculatePitch(read_period_preset(&OSC2), &OSC2);
  printVCO_Pitch(pitch);
}

void  printVCO_Fine(u8 *fine)
{
  lcd_goto(13, 2);
  lcd_print("   ");
  lcd_goto(13, 2);
  if (*fine < 50)
    {
      lcd_print("-");
      lcd_printnbr(50 - *fine);
    }
  else if (*fine == 50)
    lcd_print(" 0");
  else if (*fine > 50)
    {
      lcd_print("+");
      lcd_printnbr(*fine - 50);
    }
}

void  updateVCO_Fine(u8 sens, u8 *fine)
{
  if (!sens && *fine == 0)
    {
      if (fine == &OSC1.presetFine)
        {
          if (!OSC1.presetOct && !OSC1.presetPitch)
              return ;
          updateVCO_Pitch(0, &OSC1.presetPitch);
	  *fine = 99;
	}
      else
	{
          if (!OSC2.presetOct && !OSC2.presetPitch)
              return ;
          updateVCO_Pitch(0, &OSC2.presetPitch);
	  *fine = 99;
	}
    }
  else if (!sens && *fine)
    *fine -= 1;
  else if (sens && *fine < 99)
    *fine += 1;
  else if (sens && *fine == 99)
    {
      if (fine == &OSC1.presetFine)
	{
          if (OSC1.presetOct == 7 && OSC1.presetPitch == 11)
              return ;
          updateVCO_Pitch(1, &OSC1.presetPitch);
	  *fine = 0;
	}
      else
	{
          if (OSC2.presetOct == 7 && OSC2.presetPitch == 11)
              return ;
	  updateVCO_Pitch(1, &OSC2.presetPitch);
	  *fine = 0;
	}
    }
  
  if (fine == &OSC1.presetFine)
      calculatePitch(read_period_preset(&OSC1), &OSC1);
  else
      calculatePitch(read_period_preset(&OSC2), &OSC2);
  printVCO_Fine(fine);
}

void  printARPG_Type(u8 *type)
{
  if (*type == 0)
    lcd_print("OFF");
  else if (*type == 1)
    lcd_print("Asc");
  else if (*type == 2)
    lcd_print("Des");
  else if (*type == 3)
    lcd_print("Bth");
}

void    updateMultiPlex(u8 type)
{
  if (type == 0)
  {
      _MULT0 = 0;
      _MULT1 = 0;
  }
  else if (type == 1)
  {
      _MULT0 = 1;
      _MULT1 = 0;
  }
  else if (type == 2)
  {
      _MULT0 = 0;
      _MULT1 = 1;
  }
  else if (type == 3)
  {
      _MULT0 = 1;
      _MULT1 = 1;
  }
}

void  updateARPG_Type(u8 sens, u8 *type)
{
  if (!sens && *type)
    *type -= 1;
  else if (sens && *type < 3)
    *type += 1;

  printARPG_Type(type);
}

void  printVal(u8 *val)
{
  lcd_print("   ");
  lcd_moveleft();
  lcd_moveleft();
  lcd_moveleft();
  lcd_printnbr(*val + 1);
}
/*
void            updateFreq(u8 val)
 {
      OC1CONbits.ON = 0;
      OC1RS = (2047 * (val + 1)) / 100;
      OC1CONbits.ON = 1;
  }
*/
void            updateFmod(u8 val)
 {
      OC3CONbits.ON = 0;
      OC3RS = (2047 * (val + 1)) / 100;
      OC3CONbits.ON = 1;
  }

void  update7bitVal(u8 sens, u8 *val)
{
  if (!sens && *val)
    *val -= 1;
  else if (sens && *val < 99)
    *val += 1;

  printVal(val);
}

void  update4bitVal(u8 sens, u8 *val)
{
  if (!sens && *val)
    *val -= 1;
  else if (sens && *val < 15)
    *val += 1;

  printVal(val);
}

void  printName(char *str)
{
    u8 i;

    i = 0;
    while (i < 12)
    {
        if (!str[i])
            lcd_moveright();
        else
            lcd_command(str[i], 1);
        i++;
    }
}

void  updatePresetBank(u8 sens, u8 *bank)
{
  if (!sens && curBank + 'A' > 'A')
    curBank -= 1;
  else if (sens && curBank + 'A' < 'F')
    curBank += 1;

  lcd_goto(1, 1);
  lcd_command(curBank + 'A', 1);
  if (curPreset < 10)
    lcd_print(" ");
  lcd_printnbr(curPreset);
  lcd_print("-");
  lcd_goto(5, 1);
  lcd_print("             ");
  lcd_goto(5, 1);
  printName(&presets[curBank][curPreset][14]);

}

void  updatePresetNum(u8 sens, u8 *num)
{
  if (!sens && curPreset > 1)
    curPreset -= 1;
  else if (sens && curPreset < 99)
    curPreset += 1;

  lcd_goto(2, 1);
  if (curPreset < 10)
    lcd_print(" ");
  lcd_printnbr(curPreset);
  lcd_print("-");
  lcd_goto(5, 1);
  lcd_print("             ");
  lcd_goto(5, 1);
  printName(&presets[curBank][curPreset][14]);

}

void  do_nothing(u8 sens, u8 *bank)
{
}

void  updateSaveLoad(u8 sens, u8 *num)
{
    saveLoad = (sens ^ saveLoad ? saveLoad : !saveLoad);
    lcd_goto(13, 2);
    lcd_print(saveLoad ? "Save" : "Load");
}

void  updatePos(u8 sens, u8 *num)
{
    if (!sens && cursor_pos)
        cursor_pos--;
    else if (sens && cursor_pos < 11)
        cursor_pos++;

    lcd_goto(cursor_pos + 4, 2);
    lcd_print(" ^ ");
}

void  updateChar(u8 sens, u8 *num)
{
    if (!name_buf[cursor_pos])
        name_buf[cursor_pos] = '9';

    if (!sens && ((name_buf[cursor_pos] > '0' && name_buf[cursor_pos] <= '9') || name_buf[cursor_pos] > 'A'))
         name_buf[cursor_pos]--;
    else if (!sens && name_buf[cursor_pos] == 'A')
        name_buf[cursor_pos] = '9';
    else if (sens && (name_buf[cursor_pos] < '9' || (name_buf[cursor_pos] >= 'A' && name_buf[cursor_pos] < 'Z')))
         name_buf[cursor_pos]++;
    else if (sens && name_buf[cursor_pos] == '9')
        name_buf[cursor_pos] = 'A';

    lcd_goto(cursor_pos + 5, 1);
    lcd_command(name_buf[cursor_pos], 1);
}

void   init_Menus(void)
{

    print_menu[1] = "                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              ";
    flash_adress = 0x9D009980;
    print_menu[0] = "Wav Oct Pit Fin";
    print_menu[1] = "Atk Dec Sus Rel";
    print_menu[2] = "Wav Oct Pit Fin";
    print_menu[3] = "Atk Dec Sus Rel";
    print_menu[4] = "Arp Spd        ";
    print_menu[5] = "Atk Dec Sus Rel";
    print_menu[6] = "OS1 OS2 Noi Gli";
    print_menu[7] = "Atk Dec Sus Rel";


  menu_tab[0][0] = updateVCO_Wave;
  menu_tab[0][1] = updateVCO_Oct;
  menu_tab[0][2] = updateVCO_Pitch;
  menu_tab[0][3] = updateVCO_Fine;
  menu_tab[1][0] = update4bitVal;
  menu_tab[1][1] = update4bitVal;
  menu_tab[1][2] = update4bitVal;
  menu_tab[1][3] = update4bitVal;
  menu_tab[2][0] = updateVCO_Wave;
  menu_tab[2][1] = updateVCO_Oct;
  menu_tab[2][2] = updateVCO_Pitch;
  menu_tab[2][3] = updateVCO_Fine;
  menu_tab[3][0] = update4bitVal;
  menu_tab[3][1] = update4bitVal;
  menu_tab[3][2] = update4bitVal;
  menu_tab[3][3] = update4bitVal;
  menu_tab[4][0] = updateARPG_Type;
  menu_tab[4][1] = update7bitVal;
  menu_tab[4][2] = do_nothing;
  menu_tab[4][3] = do_nothing;
  menu_tab[5][0] = update4bitVal;
  menu_tab[5][1] = update4bitVal;
  menu_tab[5][2] = update4bitVal;
  menu_tab[5][3] = update4bitVal;
  menu_tab[6][0] = update7bitVal;
  menu_tab[6][1] = update7bitVal;
  menu_tab[6][2] = update7bitVal;
  menu_tab[6][3] = update4bitVal;
  menu_tab[7][0] = update4bitVal;
  menu_tab[7][1] = update4bitVal;
  menu_tab[7][2] = update4bitVal;
  menu_tab[7][3] = update4bitVal;
  menu_tab[8][0] = updatePresetBank;
  menu_tab[8][1] = updatePresetNum;
  menu_tab[8][2] = do_nothing;
  menu_tab[8][3] = updateSaveLoad;
  menu_tab[9][0] = updateChar;
  menu_tab[9][1] = updatePos;
  menu_tab[9][2] = do_nothing;
  menu_tab[9][3] = do_nothing;

  printmenu_tab[0][0] = printVCO_Wave;
  printmenu_tab[0][1] = printVCO_Oct;
  printmenu_tab[0][2] = printVCO_Pitch;
  printmenu_tab[0][3] = printVCO_Fine;
  printmenu_tab[1][0] = printVal;
  printmenu_tab[1][1] = printVal;
  printmenu_tab[1][2] = printVal;
  printmenu_tab[1][3] = printVal;
  printmenu_tab[2][0] = printVCO_Wave;
  printmenu_tab[2][1] = printVCO_Oct;
  printmenu_tab[2][2] = printVCO_Pitch;
  printmenu_tab[2][3] = printVCO_Fine;
  printmenu_tab[3][0] = printVal;
  printmenu_tab[3][1] = printVal;
  printmenu_tab[3][2] = printVal;
  printmenu_tab[3][3] = printVal;
  printmenu_tab[4][0] = printARPG_Type;
  printmenu_tab[4][1] = printVal;
  printmenu_tab[4][2] = do_nothing;
  printmenu_tab[4][3] = do_nothing;
  printmenu_tab[5][0] = printVal;
  printmenu_tab[5][1] = printVal;
  printmenu_tab[5][2] = printVal;
  printmenu_tab[5][3] = printVal;
  printmenu_tab[6][0] = printVal;
  printmenu_tab[6][1] = printVal;
  printmenu_tab[6][2] = printVal;
  printmenu_tab[6][3] = printVal;
  printmenu_tab[7][0] = printVal;
  printmenu_tab[7][1] = printVal;
  printmenu_tab[7][2] = printVal;
  printmenu_tab[7][3] = printVal;

  params_tab[0][0] = &OSC1.presetOnde;
  params_tab[0][1] = &OSC1.presetOct;
  params_tab[0][2] = &OSC1.presetPitch;
  params_tab[0][3] = &OSC1.presetFine;
  params_tab[1][0] = &OSC1.Env.Atk;
  params_tab[1][1] = &OSC1.Env.Dec;
  params_tab[1][2] = &OSC1.Env.Sus;
  params_tab[1][3] = &OSC1.Env.Rel;
  params_tab[2][0] = &OSC2.presetOnde;
  params_tab[2][1] = &OSC2.presetOct;
  params_tab[2][2] = &OSC2.presetPitch;
  params_tab[2][3] = &OSC2.presetFine;
  params_tab[3][0] = &OSC2.Env.Atk;
  params_tab[3][1] = &OSC2.Env.Dec;
  params_tab[3][2] = &OSC2.Env.Sus;
  params_tab[3][3] = &OSC2.Env.Rel;
  params_tab[4][0] = &cur_preset.ARPG_Type;
  params_tab[4][1] = &cur_preset.ARPG_Speed;
  params_tab[4][2] = 0;
  params_tab[4][3] = 0;
  params_tab[5][0] = &cur_preset.FILT_Atk;
  params_tab[5][1] = &cur_preset.FILT_Dec;
  params_tab[5][2] = &cur_preset.FILT_Sus;
  params_tab[5][3] = &cur_preset.FILT_Rel;
  params_tab[6][0] = &cur_preset.MIX_VCO1;
  params_tab[6][1] = &cur_preset.MIX_VCO2;
  params_tab[6][2] = &cur_preset.MIX_NOIS;
  params_tab[6][3] = &cur_preset.MIX_Glide;
  params_tab[7][0] = &cur_preset.Env.Atk;
  params_tab[7][1] = &cur_preset.Env.Dec;
  params_tab[7][2] = &cur_preset.Env.Sus;
  params_tab[7][3] = &cur_preset.Env.Rel;
  params_tab[8][0] = &curBank;
  params_tab[8][1] = &curPreset;
  params_tab[8][2] = 0;
  params_tab[8][3] = &saveLoad;
  params_tab[9][0] = 0;
  params_tab[9][1] = &cursor_pos;
  params_tab[9][2] = 0;
  params_tab[9][3] = 0;

  init_factoryPreset();

}
