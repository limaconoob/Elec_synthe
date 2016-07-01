/* 
 * File:   Main.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:16 AM
 */

#include "SynthyTwo.h"

/*    <-- *
  Le 17-06
------- Oscillator.c : ---------------------
¤ Toutes les algos font une seule ligne \o/
  (je t''ai meme fait une sawtooth_reverse :3 )

¤ Toutes les algos ne dépendent que d'' un seul paramètre : "cur_amplitude"

-------- Enveloppe.c : ---------------------
¤ La hauteur max des oscillations dépendent de seuil_max/min

¤ Le seuil de Sustain est un pourcentage entre 0 et seuil_min
  Donc: presetSus <= seuil_min

¤ La durée dépendant, par corollaire, de presetSus, seuil_min
                                      ainsi que de cur_amplitude

-------  AudioBuffer.c : -------------------
¤ Les doubles oscillos et la gestion des enveloppes est indépendante.

¤ Si on veut modifier la longueur d''onde indépendament,
  il faut transformer  pitch && pitch_adjust && reste  en
                >> pitch1/2 && pitch_adjust1/2 && reste1/2

¤ Pour masquer une des deux notes, il faut silence la variable "osc"
  (ou mettre en commentaire l''autre partie)

¤ Pas besoin de gérer le mixeur. Ca se fait automatiquement.

---------  Main.c : -----------------------
¤ Il FAUT faire toutes les déclarations des variables globales dans le main
  pour éviter que le programme plante (=quand on utilise une variable dans
  une interruption et qu''elle est pas encore initialisée)


--------  Encodeur.c : --------------------
¤ J''ai commencé à implémenter un truc mais c''est pas fini :/

¤ Il faut encore adapter les menus et la réception des switchs


DéSOLé POUR LE PAVé :D
*/


t_osc       OSC1;

u16     DAC_value = 1;

t_osc       OSC2;


//----------------  ENCODEURS  -------------------
    u8          status = 0;
    u8          prev_status = 0;
//------------------------------------------------

//-----------------  BOUTONS  --------------------
    u8          status2 = 0;
    u8          prev_status2 = 0;
    u8          boutons = 0;
//------------------------------------------------


u16             tab_car[1420];
u16             tab_saw[1420];
u16             tab_tri[1420];
u16             tab_sin[1420];
void    create_tab_frequenz(void)
{
    s16 i;

    // --------- ONDE CARRE ----------
    i = -1;
    while (i++ < 710)
        tab_car[i] = 0x7FFF;
    i--;
    while (i++ < 1420)
        tab_car[i] = 0x8000;

    // -------- ONDE SAWTOOTH --------
    i = -1;
    while (i++ < 1419)
        tab_saw[i] = i * 46;
    tab_saw[1419] = 0xFFFF;

    // -------- ONDE TRIANGLE --------
    i = -1;
    while (i++ < 354)
        tab_tri[i] = (353 + i) * 92;
    i--;
    while (i++ < 710)
        tab_tri[i] = (i - 353) * 92;
    i = 1420;
    while (i-- > 1064)
        tab_tri[i] = (1063 - i) * 92;
    i++;
    while (i-- > 710)
        tab_tri[i] = (353 - i) * 92;
    tab_tri[0] = 0x8000;
    tab_tri[1] = 0x8000;
    tab_tri[2] = 0x8000;
    tab_tri[3] = 0x8000;
    tab_tri[4] = 0x8000;
    tab_tri[5] = 0x8000;
    tab_tri[6] = 0x8000;

/*  350 - 360 coté bas (~0xFFFF) Note de Jpepz
    tab_tri[351] = 0;
    tab_tri[352] = 0;
    tab_tri[353] = 0;
    tab_tri[354] = 0;
    tab_tri[355] = 0;
    tab_tri[356] = 0;
    tab_tri[357] = 0;
    tab_tri[358] = 0;
    tab_tri[359] = 0;
 */
    tab_tri[701] = 0x7FFF;
    tab_tri[702] = 0x7FFF;
    tab_tri[703] = 0x7FFF;
    tab_tri[704] = 0x7FFF;
    tab_tri[705] = 0x7FFF;
    tab_tri[706] = 0x7FFF;
    tab_tri[707] = 0x7FFF;
    tab_tri[708] = 0x7FFF;
    tab_tri[709] = 0x7FFF;
    tab_tri[710] = 0x7FFF;
    tab_tri[711] = 0x7FFF;
    tab_tri[712] = 0x7FFF;
    tab_tri[713] = 0x7FFF;
    tab_tri[714] = 0x7FFF;
    tab_tri[715] = 0x7FFF;
    tab_tri[716] = 0x7FFF;
    tab_tri[717] = 0x7FFF;
    tab_tri[718] = 0x7FFF;
    tab_tri[719] = 0x7FFF;

/*  1060 - 1070 coté haut (~0x0000) Note de Jpepz
    tab_tri[1061] = 0;
    tab_tri[1062] = 0;
    tab_tri[1063] = 0;
    tab_tri[1064] = 0;
    tab_tri[1065] = 0;
    tab_tri[1066] = 0;
    tab_tri[1067] = 0;
    tab_tri[1068] = 0;
    tab_tri[1069] = 0;
*/
    tab_tri[1414] = 0x8000;
    tab_tri[1415] = 0x8000;
    tab_tri[1416] = 0x8000;
    tab_tri[1417] = 0x8000;
    tab_tri[1418] = 0x8000;
    tab_tri[1419] = 0x8000;

/*
    --------- Pour Aydm :) --------
    i = -1;
    while (i++ < 709)
        tab_tri[i] = (1420 - i) * 92;
    tab_tri[709] = 0x0000;
    i = 1420;
    while (i-- > 710)
        tab_tri[i] = i * 92;
    tab_tri[710] = 0xFFFF;
    -------------------------------
*/

    // ----- ONDE SINUSOIDALE -----

    tab_sinus();
/*    i = -1;
    while (i++ < 354)
        tab_sin[i] = (353 + i) * 92;
    i--;
    while (i++ < 710)
        tab_sin[i] = (i - 353) * 92;
    i = 1420;
    while (i-- > 1064)
        tab_sin[i] = (1063 - i) * 92;
    i++;
    while (i-- > 710)
        tab_sin[i] = (353 - i) * 92;
    tab_sin[0] = 0x8000;
    tab_sin[1] = 0x8000;
    tab_sin[2] = 0x8000;
    tab_sin[3] = 0x8000;
    tab_sin[4] = 0x8000;
    tab_sin[5] = 0x8000;
    tab_sin[6] = 0x8000;

//  350 - 360 coté bas (~0xFFFF) Note de Jpepz
    tab_tri[351] = 0;
    tab_tri[352] = 0;
    tab_tri[353] = 0;
    tab_tri[354] = 0;
    tab_tri[355] = 0;
    tab_tri[356] = 0;
    tab_tri[357] = 0;
    tab_tri[358] = 0;
    tab_tri[359] = 0;
 //
    tab_sin[701] = 0x7FFF;
    tab_sin[702] = 0x7FFF;
    tab_sin[703] = 0x7FFF;
    tab_sin[704] = 0x7FFF;
    tab_sin[705] = 0x7FFF;
    tab_sin[706] = 0x7FFF;
    tab_sin[707] = 0x7FFF;
    tab_sin[708] = 0x7FFF;
    tab_sin[709] = 0x7FFF;
    tab_sin[710] = 0x7FFF;
    tab_sin[711] = 0x7FFF;
    tab_sin[712] = 0x7FFF;
    tab_sin[713] = 0x7FFF;
    tab_sin[714] = 0x7FFF;
    tab_sin[715] = 0x7FFF;
    tab_sin[716] = 0x7FFF;
    tab_sin[717] = 0x7FFF;
    tab_sin[718] = 0x7FFF;
    tab_sin[719] = 0x7FFF;

//  1060 - 1070 coté haut (~0x0000) Note de Jpepz
    tab_tri[1061] = 0;
    tab_tri[1062] = 0;
    tab_tri[1063] = 0;
    tab_tri[1064] = 0;
    tab_tri[1065] = 0;
    tab_tri[1066] = 0;
    tab_tri[1067] = 0;
    tab_tri[1068] = 0;
    tab_tri[1069] = 0;
//
    tab_sin[1414] = 0x8000;
    tab_sin[1415] = 0x8000;
    tab_sin[1416] = 0x8000;
    tab_sin[1417] = 0x8000;
    tab_sin[1418] = 0x8000;
    tab_sin[1419] = 0x8000;*/
}

void    init(void)
{
    INTCONbits.MVEC = TRUE;           //Multi-vector interrupt mode
    asm volatile("ei");               //Autorise les macro-ASM (interruptions)

    create_tab_frequenz();
    create_tab_period();                        // Remplit le tableau avec les périodes
    init_lcd();
    init_MIDI();
    init_dac();
    init_preset();
}

int     main(int argc, char** argv)
{
    init();

    lcd_print("Synthy two V0.1");

    while(1)
    {
        processMIDIBuffer();
//      scan_boutons();
//      scan_encodeurs();
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
}

