/*
 * File:   Oscillator.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

void         init_oscil(void)
{
    IEC0bits.T2IE = TRUE;
    IFS0bits.T2IF = FALSE;
    IPC2bits.T2IP = 4;                //Priorité basse
    IPC2bits.T2IS = 1;

    T2CON = 0;
    TMR2 = 0;
    PR2 = 767;
//    PR2 = 1536;
    T2CONbits.ON = TRUE;
}

u16     value = 1;       // VALUE EST LA TENSION (1 à F FFF) QUI VA AU DAC !
u16     cursor;   // Donne la cadence d'augmentation de la tension
u8      reste = 0;
u16     pitch;
u8      pitch_adjust;
u8      phase = 1;
u16     phi = 0;


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

//--------------  GENERATEUR D'ENVELOPPE -------------------------------------------------------

u8          cur_env = 0;            // mode courant (ATK, DEC, SUS, REL)
u16         compteur = 0;

u16         seuil_max = 0x3FFF;     // seuil_max coté bas => 0x7FFF / 2 = 0x3FFF
                                    // seuil_max coté haut => 0xFFFF / 2 = 0xBFFF

u16         cur_seuil = 0;          // seuil_bas = cur_seuil ; seuil_haut = 0xFFFF - cur_seuil

u8          presetAtk = 0b0001;          // en secondes
u8          presetDec = 0b0001;          // en secondes
u8          presetRel = 0b0001;          // en secondes
u16         presetSus = 0x2000;          // en seuil -> limite pour le DAC



/    <-- *
!! PROBLEME !!
LA PERIODE EST MODIFIEE ALORS QUELLE NE DEVRAIT PAS !! (#Vaudou)

Ca fait l''enveloppe comme il faut cependant.

Données:
¤ La vitesse se controle avec x et la valeur 52150 (à modifier)
  ¤ x saute x*périodes, 52150 est une période.
¤ sus est le temps qui va varier en fonction du Sustain et qui représentera
  le curseur de temps qui ira de seuil_max (0x3FFF) à seuil_sustain (Sustain "SUS"),
  puis de seuil_sustain à 0x0000 (Release "REL")

COMPILATION :: METTRE EN COMMENTAIRE CE MESSAGE !!
*/



void            generateur_enveloppe(void)
{
    static u8   x = 0;
    static u16  sus = 0;

    // 52150 = 0.5 sec en théorie

    if (cur_env == ATK)
    {
        if (x < 1 && compteur / 52150 < presetAtk) {
            x++;
            compteur++;
        }
        else if (cur_seuil < seuil_max && compteur / 52150 < presetAtk) {
            x = 0;
            compteur++;
            cur_seuil++;
        }
        else {
            x = 0;
            compteur = 0;
            cur_seuil = seuil_max;
            sus = 52150 / presetSus;       //sus == seuil_max -> presetSus
            cur_env = DEC;
        }
    }

    else if (cur_env == DEC)
    {
        if (x < sus && compteur / 52150 < presetDec) {
            x++;
            compteur++;
        }
        else if (compteur / 52150 < presetDec && cur_seuil) {
            x = 0;
            compteur++;
            cur_seuil--;
        }
        else {
            x = 0;
            compteur = 0;
            cur_seuil = presetSus;
            sus = 52150 / (seuil_max - presetSus);  //sus == presetSus -> 0
            cur_env = SUS;
        }
    }

    else if (cur_env == SUS)
    {
        if (DEC == SUS)
            x++;
        else {
            if (DEC == SUS)
                x++;
            else
                x++;
        }
    }

    else if (cur_env == REL)
    {
        if (x < sus && compteur / 52150 < presetRel) {
            x++;
            compteur++;
        }
        else if (compteur / 52150 < presetRel && cur_seuil) {
            x = 0;
            compteur++;
            cur_seuil--;
        }
        else {
            // RESET ALL
            x = 0;
            compteur = 0;
            cur_seuil = 0;
            sus = 0;
            cur_env = ATK;
        }
    }
}
//--------------  GENERATEUR D'ENVELOPPE -------------------------------------------------------


void        onde_triangle(void)
{
    static u8   mode = 0;
    u16         adj;    // Sert à ajuster la valeur pour garder la bonne fréquence

    adj = cursor/2 - 50;
    if (mode == DESCENDANT)
    {
        if ((value <= 0xFFFF - (2*cursor + adj) && value > cur_seuil) || value <= cur_seuil - (2*cursor + adj)) {
            value += (2*cursor + adj);
        }
        else if (value >= 0xFFFF - (2*cursor + adj)) {
            value = 0x0000;
        }
        else if (value >= cur_seuil - (2*cursor + adj)) {
            value = cur_seuil;
            mode = MONTANT;
        }
    }
    else
    {
        if ((value >= 0x0000 + (2*cursor + adj) && value < (0xFFFF - cur_seuil)) || value >= (0xFFFF - cur_seuil) + (2*cursor + adj)) {
            value -= (2*cursor + adj);
        }
        else if (value <= 0x0000 + (2*cursor + adj)) {
            value = 0xFFFF;
        }
        else if (value <= (0xFFFF - cur_seuil) + (2*cursor + adj)) {
            value = (0xFFFF - cur_seuil);
            mode = DESCENDANT;
        }
    }
}


void         onde_sawtooth(void)
{
    u16         adj;    // Sert à ajuster la valeur pour garder la bonne fréquence

    adj = 1;
    if ((value >= (cursor + adj) && value < (0xFFFF - cur_seuil)) || value >= (0xFFFF - cur_seuil) + (cursor + adj))
        value -= (cursor + adj);
    else if (value <= (cursor + adj))
        value = 0xFFFF;
    else if (value <= (0xFFFF - cur_seuil) + (cursor + adj))
        value = cur_seuil;
}

void            onde_carre()
{
    if (phase == 1)
        value = cur_seuil;
    else
        value = (0xFFFF - cur_seuil);
}

void __ISR(_TIMER_2_VECTOR, IPL4AUTO) sampleClock(void)
{
    static u8       boool = 1;

    if (!boool)
    {
       if (notesON || cur_env == REL)
        {
           // if (cur_env != SUS)
                generateur_enveloppe();

            if (phi)
                phi--;
            else
            {
                if (reste < 100)
                {
                    phi = pitch - 1;
                    cursor = ((0xFFFF - cur_seuil) / pitch);
                }
                else
                {
                    reste -= 100;
                    phi = pitch;
                    cursor = ((0xFFFF - cur_seuil) / (pitch + 1));
                }
                reste += pitch_adjust;
           }

           if (phi == 1)
               phase = (!phase);

//        onde_sawtooth();
        onde_carre();
//        onde_triangle();

            if (value == 0)
               value = 1;
       }
       else
       {
          phi = 0;
          value = 1;
          reste = 0;
        }
    }
    boool = !boool;
    processMIDIBuffer();
    IFS0bits.T2IF = FALSE;
}
