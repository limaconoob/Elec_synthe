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


u16     DAC_value = 1;

//---------------  OSCILLATEUR 1  ----------------
u8          phase1 = 1;
u16         cursor1 = 1;   // Donne la cadence d'augmentation de la tension
u8          presetAtk1 = 0b0001;        // en secondes
u8          presetDec1 = 0b0001;        // en secondes
u8          presetRel1 = 0b0001;        // en secondes
u16         presetSus1 = 0x3000;        // presetSus < seuil_min
u8          presetOnde1 = CARRE;        // forme de l'onde
u8          cur_env1 = 0;               // mode courant (ATK, DEC, SUS, REL)
u16         cur_amplitude1 = 0;         // seuil_bas = cur_seuil ; seuil_haut = 0xFFFF - cur_seuil
u16         seuil_max1 = 0xA000;        // seuil_max >= 0x8000
u16         seuil_min1 = 0x5FFF;        // seuil_min <= 0x7FFF
u16         phi1 = 0;
u16         pitch1 = 1;
u8          pitch_adjust1 = 1;
u8          reste1 = 1;

//------------------------------------------------

//---------------  OSCILLATEUR 2  ----------------
u8          phase2 = 1;
u16         cursor2 = 1;   // Donne la cadence d'augmentation de la tension
u8          presetAtk2 = 0b0001;        // en secondes
u8          presetDec2 = 0b0001;        // en secondes
u8          presetRel2 = 0b0001;        // en secondes
u16         presetSus2 = 0x1000;        // presetSus < seuil_min
u8          presetOnde2 = TRIANGLE;     // forme de l'onde
u8          cur_env2 = 0;               // mode courant (ATK, DEC, SUS, REL)
u16         cur_amplitude2 = 0;         // seuil_bas = cur_seuil ; seuil_haut = 0xFFFF - cur_seuil
u16         seuil_max2 = 0xCFFF;        // seuil_max >= 0x8000
u16         seuil_min2 = 0x3000;        // seuil_min <= 0x7FFF
u16         phi2 = 0;
u16         pitch2 = 1;
u8          pitch_adjust2 = 1;
u8          reste2 = 1;
//------------------------------------------------

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
    init_oscil();
    init_MIDI();
    init_dac();
}

int     main(int argc, char** argv)
{
    init();

    lcd_print("Synthy two V0.1");

    while(PROCESS)
    {
        processMIDIBuffer();
//        fillAudioBuffer();
//        fillAudioBuffer();
//        fillAudioBuffer();
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }


}

