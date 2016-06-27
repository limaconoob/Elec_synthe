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


void    init(void)
{
    INTCONbits.MVEC = TRUE;           //Multi-vector interrupt mode
    asm volatile("ei");               //Autorise les macro-ASM (interruptions)

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

