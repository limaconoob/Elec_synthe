
#include "SynthyTwo.h"

void            encodeurA(void)//(u8 boutons)
{
    static u8   stock_EA = 0;
    static u8   value = 0;

    if (stock_EA ^ _EAB) {
        lcd_goto(13, 2);
        lcd_print("   ");
        lcd_goto(13, 2);
        value++;
    }
    else {
        lcd_goto(13, 2);
        lcd_print("   ");
        lcd_goto(13, 2);
        value--;
    }
    lcd_printnbr(value);
    stock_EA = _EAA;
}

void            encodeurB(void)//(u8 boutons)
{
    static u8   stock_EB = 0;
    static u8   value = 0;

    if (stock_EB ^ _EBB) {
        lcd_goto(9, 2);
        lcd_print("   ");
        lcd_goto(9, 2);
        value++;
    }
    else {
        lcd_goto(9, 2);
        lcd_print("   ");
        lcd_goto(9, 2);
        value--;
    }
    lcd_printnbr(value);
    stock_EB = _EBA;
}

void            encodeurC(void)//(u8 boutons)
{
    static u8   stock_EC = 0;
    static u8   value = 0;

    if (stock_EC ^ _ECB) {
        lcd_goto(5, 2);
        lcd_print("   ");
        lcd_goto(5, 2);
        value++;
    }
    else {
        lcd_goto(5, 2);
        lcd_print("   ");
        lcd_goto(5, 2);
        value--;
    }
    lcd_printnbr(value);
    stock_EC = _ECA;
}

void            encodeurD(void)//(u8 boutons)
{
    static u8   stock_ED = 0;
    static u8   value = 0;

    if (stock_ED ^ _EDB) {
        lcd_goto(1, 2);
        lcd_print("   ");
        lcd_goto(1, 2);
        value++;
    }
    else {
        lcd_goto(1, 2);
        lcd_print("   ");
        lcd_goto(1, 2);
        value--;
    }
    lcd_printnbr(value);
    stock_ED = _EDA;
}

void            processEncodeur(void)//(u8 boutons)
{
    u8 k;

    status = (_EAA ^ _EAB) + ((_EBA ^ _EBB) << 1) + ((_ECA ^ _ECB) << 2) + ((_EDA ^ _EDB) << 3);

    if (prev_status != status)
    {
       // tab[!(prev_status ^ status)]; Tableau de fonctions?
       // encodeur(!(prev_status ^ status));//, boutons); Fonction générale?
        k = ((prev_status ^ status) ^ 0);
        if (k == 0x01)
            encodeurA();
        else if (k == 0x02)
            encodeurB();
        else if (k == 0x04)
            encodeurC();
        else if (k == 0x08)
            encodeurD();
    }
    prev_status = status;
}


/*
u32             read_period_preset(void)
{
    u32         cur_periode;
    s8          cur_message;
    u32         centieme;

    cur_message = midi_note;
    cur_message += 1 * 12 * 12; //Preset octave    // Une octave de plus
    cur_message -= 3;        // Preset_demi_ton    // Trois demi-tons de moins
    if (cur_message - 21 > 0) {
        cur_message -= 21;
        cur_periode = tab_period[cur_message];
        centieme = tab_period[cur_message - 1] - tab_period[cur_message];
        centieme /= 100;
        if (!centieme)
            centieme = 1;
        cur_periode += 10 * centieme; // preset_centieme * centieme
        return (cur_periode);
    }
    else if (cur_message - 21 == 0) {
        cur_message -= 21;
        cur_periode = tab_period[cur_message];
        centieme = tab_period[cur_message] - tab_period[cur_message + 1];
        centieme /= 100;
        if (!centieme)
            centieme = 1;
        cur_periode += 10 * centieme // preset_centieme * centieme
        return (cur_periode);
    }
    return (tab_period[midi_note] - 21]);
}
*/
