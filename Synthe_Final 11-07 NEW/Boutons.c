
#include "SynthyTwo.h"

u8  curBank = 0;
u8  curPreset = 1;

u8  presets[1][100][30];

void        printPresetMenu(void)
{
    lcd_goto(1, 2);
    lcd_print("Bank Num    ");
    lcd_print(saveLoad ? "Save" : "Load");
    lcd_goto(1, 1);
    lcd_command(curBank + 'A', 1);
    if (curPreset < 10)
        lcd_print(" ");
    lcd_printnbr(curPreset);
    lcd_print("-");
    lcd_print("            ");
    lcd_goto(5, 1);
    printName(&presets[curBank][curPreset][14]);
}

void            validPresetMenu(void)
{
    lcd_goto(4, 2);
    lcd_print(" ^ ");
    lcd_goto(1, 1);
    lcd_command(curBank + 'A', 1);
    if (curPreset < 10)
        lcd_print(" ");
    lcd_printnbr(curPreset);
    lcd_print("-");
}

void            validSavePreset(void)
{
    cur_menu = 8;
    cursor_pos = 0;
    preset_save(name_buf, curBank, curPreset);
    u8 i;
    i = 0;
    while (i < 12)
        name_buf[i++] = 0;
    printPresetMenu();
}

void         update_menu(void)
{
    lcd_goto(1, 1);
    lcd_print("                ");
    lcd_goto(1, 2);
    lcd_print("                ");
    lcd_goto(1, 1);
    if (cur_menu == 8)
        printPresetMenu();
    else if (cur_menu == 9)
        validPresetMenu();
    else if (cur_menu == 10)
        validSavePreset();
    else
    {
        lcd_print(print_menu[cur_menu]);
        lcd_goto(1, 2);
        printmenu_tab[cur_menu][0](params_tab[cur_menu][0]);
        lcd_goto(5, 2);
        printmenu_tab[cur_menu][1](params_tab[cur_menu][1]);
        lcd_goto(9, 2);
        printmenu_tab[cur_menu][2](params_tab[cur_menu][2]);
        lcd_goto(13, 2);
        printmenu_tab[cur_menu][3](params_tab[cur_menu][3]);
    }
}

void            light_led(void)
{
    clear_leds();
    if (cur_menu == 0)
        _LED0 = VCC;
    else if (cur_menu == 1)
        _LED1 = VCC;
    else if (cur_menu == 2)
        _LED2 = VCC;
    else if (cur_menu == 3)
        _LED3 = VCC;
    else if (cur_menu == 4)
        _LED4 = VCC;
    else if (cur_menu == 5)
        _LED5 = VCC;
    else if (cur_menu == 6)
        _LED6 = VCC;
    else if (cur_menu == 7)
        _LED7 = VCC;
    else if (cur_menu == 8)
        _LED8 = VCC;
    else if (cur_menu == 9)
        _LED8 = VCC;
}

void            boutons(void)
{
    u8 k;

    status_bt = (_SW5) + (_SW4 << 1) + (_SW3 << 2) + (_SW2 << 3) + (_SW1 << 4);

    k = ((prev_status_bt ^ status_bt) ^ 0);
    if (prev_status_bt != status_bt && (k & status_bt))
    {
        if (k == 0x01)
            cur_menu = (cur_menu == 0 ? 1 : 0);
        else if (k == 0x02)
            cur_menu = (cur_menu == 2 ? 3 : 2);
        else if (k == 0x04)
            cur_menu = (cur_menu == 4 ? 5 : 4);
        else if (k == 0x08)
        {
            cur_menu = (cur_menu == 6 ? 7 : 6);
        }
        else if (k == 0x10 && cur_menu < 8)
            cur_menu = 8;
        else if (k == 0x10 && saveLoad && cur_menu != 9)
            cur_menu = 9;
        else if (k == 0x10 && saveLoad)
            validSavePreset();
        else if (k == 0x10 && !saveLoad)
            preset_load(curBank, curPreset);

        light_led();
        update_menu();
    }
    prev_status_bt = status_bt;

}
