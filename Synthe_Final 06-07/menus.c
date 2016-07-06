
#include "SynthyTwo.h"

print printmenu_tab[8][4];
menus menu_tab[8][4];
u8*   params_tab[8][4];
char *print_menu[9];
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

  if (Wave == &cur_preset.VCO1_Wave)
      OSC1.presetOnde = *Wave;
  else if (Wave == &cur_preset.VCO2_Wave)
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

        calculatePitch(read_period_preset());
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
      if (pitch == &cur_preset.VCO1_Pitch && cur_preset.VCO1_Oct)
	{
	  updateVCO_Oct(0, &cur_preset.VCO1_Oct);
	  *pitch = 11;
	}
      else if (pitch == &cur_preset.VCO2_Pitch && cur_preset.VCO2_Oct)
	{
	  updateVCO_Oct(0, &cur_preset.VCO2_Oct);
	  *pitch = 11;
	}
    }
  else if (!sens && *pitch)
    *pitch -= 1;
  else if (sens && *pitch < 11)
    *pitch += 1;
  else if (sens && *pitch == 11)
    {
      if (pitch == &cur_preset.VCO1_Pitch && cur_preset.VCO1_Oct < 7)
	{
	  updateVCO_Oct(1, &cur_preset.VCO1_Oct);
	  *pitch = 0;
	}
      else if (pitch == &cur_preset.VCO2_Pitch && cur_preset.VCO2_Oct < 7)
	{
	  updateVCO_Oct(1, &cur_preset.VCO2_Oct);
	  *pitch = 0;
	}
    }

        calculatePitch(read_period_preset());
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
      if (!cur_preset.VCO1_Oct && !cur_preset.VCO1_Pitch)
          return ;
      if (fine == &cur_preset.VCO1_Fine)
	{
	  updateVCO_Pitch(0, &cur_preset.VCO1_Pitch);
	  *fine = 99;
	}
      else if (fine == &cur_preset.VCO2_Fine)
	{
	  updateVCO_Pitch(0, &cur_preset.VCO2_Pitch);
	  *fine = 99;
	}
    }
  else if (!sens && *fine)
    *fine -= 1;
  else if (sens && *fine < 99)
    *fine += 1;
  else if (sens && *fine == 99)
    {
      if (cur_preset.VCO1_Oct == 7 && cur_preset.VCO1_Pitch == 11)
          return ;
      if (fine == &cur_preset.VCO1_Fine)
	{
	  updateVCO_Pitch(1, &cur_preset.VCO1_Pitch);
	  *fine = 0;
	}
      else if (fine == &cur_preset.VCO2_Fine)
	{
	  updateVCO_Pitch(1, &cur_preset.VCO2_Pitch);
	  *fine = 0;
	}
    }

        calculatePitch(read_period_preset());
  printVCO_Fine(fine);
}

void  printFILT_Type(u8 *type)
{
  if (*type == 0)
    lcd_print("OFF");
  else if (*type == 1)
    lcd_print("HiP");
  else if (*type == 2)
    lcd_print("BdP");
  else if (*type == 3)
    lcd_print("LoP");
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

void  updateFILT_Type(u8 sens, u8 *type)
{
  if (!sens && *type)
    *type -= 1;
  else if (sens && *type < 3)
    *type += 1;
  updateMultiPlex(*type);

  printFILT_Type(type);
}

void  printVal(u8 *val)
{
  lcd_print("   ");
  lcd_moveleft();
  lcd_moveleft();
  lcd_moveleft();
  lcd_printnbr(*val + 1);
}

void            updateFreq(u8 val)
 {
      OC1CONbits.ON = 0;
      OC1RS = (2047 * (val + 1)) / 100;
      OC1CONbits.ON = 1;
  }

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

  if (val == &cur_preset.FILT_Freq)
      updateFreq(*val);

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

void   init_Menus(void)
{

    print_menu[0] = "Wav Oct Pit Fin";
    print_menu[1] = "Atk Dec Sus Rel";
    print_menu[2] = "Wav Oct Pit Fin";
    print_menu[3] = "Atk Dec Sus Rel";
    print_menu[4] = "Typ Frq Res Mod";
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
  menu_tab[4][0] = updateFILT_Type;
  menu_tab[4][1] = update7bitVal;
  menu_tab[4][2] = update4bitVal;
  menu_tab[4][3] = update4bitVal;
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
  printmenu_tab[4][0] = printFILT_Type;
  printmenu_tab[4][1] = printVal;
  printmenu_tab[4][2] = printVal;
  printmenu_tab[4][3] = printVal;
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

  params_tab[0][0] = &cur_preset.VCO1_Wave;
  params_tab[0][1] = &cur_preset.VCO1_Oct;
  params_tab[0][2] = &cur_preset.VCO1_Pitch;
  params_tab[0][3] = &cur_preset.VCO1_Fine;
  params_tab[1][0] = &cur_preset.VCO1_Atk;
  params_tab[1][1] = &cur_preset.VCO1_Dec;
  params_tab[1][2] = &cur_preset.VCO1_Sus;
  params_tab[1][3] = &cur_preset.VCO1_Rel;
  params_tab[2][0] = &cur_preset.VCO2_Wave;
  params_tab[2][1] = &cur_preset.VCO2_Oct;
  params_tab[2][2] = &cur_preset.VCO2_Pitch;
  params_tab[2][3] = &cur_preset.VCO2_Fine;
  params_tab[3][0] = &cur_preset.VCO2_Atk;
  params_tab[3][1] = &cur_preset.VCO2_Dec;
  params_tab[3][2] = &cur_preset.VCO2_Sus;
  params_tab[3][3] = &cur_preset.VCO2_Rel;
  params_tab[4][0] = &cur_preset.FILT_Type;
  params_tab[4][1] = &cur_preset.FILT_Freq;
  params_tab[4][2] = &cur_preset.FILT_Reso;
  params_tab[4][3] = &cur_preset.FILT_EnvMod;
  params_tab[5][0] = &cur_preset.FILT_Atk;
  params_tab[5][1] = &cur_preset.FILT_Dec;
  params_tab[5][2] = &cur_preset.FILT_Sus;
  params_tab[5][3] = &cur_preset.FILT_Rel;
  params_tab[6][0] = &cur_preset.MIX_VCO1;
  params_tab[6][1] = &cur_preset.MIX_VCO2;
  params_tab[6][2] = &cur_preset.MIX_NOIS;
  params_tab[6][3] = &cur_preset.MIX_Glide;
  params_tab[7][0] = &cur_preset.NOIS_Atk;
  params_tab[7][1] = &cur_preset.NOIS_Dec;
  params_tab[7][2] = &cur_preset.NOIS_Sus;
  params_tab[7][3] = &cur_preset.NOIS_Rel;
}
