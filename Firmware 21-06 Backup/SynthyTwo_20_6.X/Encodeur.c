
#include "SynthyTwo.h"

    /*
        DANS LE MAIN ::
        u8 k;

        status = (EA)(_RD4 ^ _RD5) + (EB)(_RD4 ^ _RD5) << 1 +
                        (EC)(_RD4 ^ _RD5) << 2 + (ED)(_RD4 ^ _RD5) << 3

        if (prev_status != status)
        {
            k = !(prev_status ^ status);
            if (k == 0x01)
                encodeurA(boutons);
            else if (k == 0x02)
                encodeurB(boutons);
            else if (k == 0x04)
                encodeurC(boutons);
            else if (k == 0x08)
                encodeurD(boutons);
        }

        PENSER A CHANGER LES PINS D''ENTREE DES ENCORDEURS!!
     */

void            print_value(s8 i)
{
    static u16  valeur = 0;

    valeur += i;
    if (valeur & 0x8000) {
        lcd_print("-");
        lcd_printnbr((valeur ^ 0xFFFF) + 1);
    }
    else
        lcd_printnbr(valeur);
    lcd_print("       ");
}

void            encodeurA(u8 boutons)
{
    static u8   stock_EA = 0;// = _RD4;

        if (stock_EA ^ _RD5) {
            // if (boutons & 0x01)
            // else if (boutons & 0x02)
            // else if (boutons & 0x04)
            // else if (boutons & 0x08)
            // else if (boutons & 0x10)
            lcd_goto(1, 2);
            lcd_print("Droite : ");
            print_value(1);
        }
         else {
            lcd_goto(1, 2);
            lcd_print("Gauche : ");
            print_value(-1);
        }
         stock_EA = _RD4;
         prev_status |= (status & 0x01);
}

void            encodeurB(u8 boutons)
{
    static u8   stock_EB = 0;// = _RD4;

        if (stock_EB ^ _RD5) {
            lcd_goto(1, 2);
            lcd_print("Droite : ");
            print_value(1);
        }
         else {
            lcd_goto(1, 2);
            lcd_print("Gauche : ");
            print_value(-1);
        }
         stock_EB = _RD4;
         prev_status |= (status & 0x02);
}

void            encodeurC(u8 boutons)
{
    static u8   stock_EC = 0;// = _RD4;

        if (stock_EC ^ _RD5) {
            lcd_goto(1, 2);
            lcd_print("Droite : ");
            print_value(1);
        }
         else {
            lcd_goto(1, 2);
            lcd_print("Gauche : ");
            print_value(-1);
        }
         stock_EC = _RD4;
         prev_status |= (status & 0x04);
}

void            encodeurD(u8 boutons)
{
    static u8   stock_ED = 0;// = _RD4;

        if (stock_ED ^ _RD5) {
            lcd_goto(1, 2);
            lcd_print("Droite : ");
            print_value(1);
        }
         else {
            lcd_goto(1, 2);
            lcd_print("Gauche : ");
            print_value(-1);
        }
         stock_ED = _RD4;
         prev_status |= (status & 0x08);
}
