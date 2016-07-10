
#include "SynthyTwo.h"

void            encodeurA(void)//(u8 boutons)
{
    static u8   stock_EA = 0;

    lcd_goto(13, 2);
    if (stock_EA ^ _EAB)
        menu_tab[cur_menu][3](0, params_tab[cur_menu][3]);
    else
        menu_tab[cur_menu][3](1, params_tab[cur_menu][3]);
    stock_EA = _EAA;
}

void            encodeurB(void)//(u8 boutons)
{
    static u8   stock_EB = 0;

    lcd_goto(9, 2);
    if (stock_EB ^ _EBB)
        menu_tab[cur_menu][2](0, params_tab[cur_menu][2]);
    else
        menu_tab[cur_menu][2](1, params_tab[cur_menu][2]);
    stock_EB = _EBA;
}

void            encodeurC(void)//(u8 boutons)
{
    static u8   stock_EC = 0;

    lcd_goto(5, 2);
    if (stock_EC ^ _ECB)
        menu_tab[cur_menu][1](0, params_tab[cur_menu][1]);
    else
        menu_tab[cur_menu][1](1, params_tab[cur_menu][1]);
    stock_EC = _ECA;
}

void            encodeurD(void)//(u8 boutons)
{
    static u8   stock_ED = 0;

    lcd_goto(1, 2);
    if (stock_ED ^ _EDB)
        menu_tab[cur_menu][0](0, params_tab[cur_menu][0]);
    else
        menu_tab[cur_menu][0](1, params_tab[cur_menu][0]);
    stock_ED = _EDA;
}

void            processEncodeur(void)//(u8 boutons)
{
    u8 k;

    status_ec = (_EAA ^ _EAB) + ((_EBA ^ _EBB) << 1) + ((_ECA ^ _ECB) << 2) + ((_EDA ^ _EDB) << 3);

    if (prev_status_ec != status_ec)
    {
       // tab[!(prev_status ^ status)]; Tableau de fonctions?
       // encodeur(!(prev_status ^ status));//, boutons); Fonction g�n�rale?
        k = ((prev_status_ec ^ status_ec) ^ 0);
	k /= 2;
	k = (k == 4 ? 3 : k);
        if (k == 0x00)
            encodeurA();
        else if (k == 0x01)
            encodeurB();
        else if (k == 0x02)
            encodeurC();
        else if (k == 0x03)
            encodeurD();
    }
    prev_status_ec = status_ec;
}
