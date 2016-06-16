/*
 * File:   Enveloppe.c
 * Author: Jpepz
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

/*    <-- *
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

/*#define ENV_TimeScaler  50000

void            generateur_enveloppe(void)
{
        compteur++;
    if (cur_env == ATK)
    {
        if (compteur / ENV_TimeScaler < presetAtk)
        {
            if (env_reste >= 100)
            {
                cur_amplitude++;
                env_reste -= 100;
            }
        }
        else
        {
            cur_env = DEC;
            compteur = 0;
        }
    }

    else if (cur_env == DEC)
    {
        if (compteur / ENV_TimeScaler < presetDec)
        {
            if (env_reste >= 1000)
            {
                cur_amplitude--;
                env_reste -= 1000;
            }
        }
        else
        {
            cur_env = SUS;
            compteur = 0;
         }
    }
    else if (cur_env == REL)
    {
        if (compteur / ENV_TimeScaler >= presetRel)
        {
            if (env_reste >= 100)
            {
                cur_amplitude--;
                env_reste -= 100;
            }

        }
        else
        {
            phi = 0;
            cur_env = 0;
            compteur = 0;
        }
    }
}
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
            cur_amplitude -= 2;
        }
        else if (cur_seuil < seuil_max && compteur / 52150 < presetAtk) {
            x = 0;
            compteur++;
            cur_seuil++;
        }
        else {
            x = 0;
            compteur = 0;
            cur_amplitude = seuil_max;
            cur_seuil = seuil_max;
            sus = 52150 / presetSus;       //sus == seuil_max -> presetSus
            cur_env = DEC;
        }
    }

    else if (cur_env == DEC)
    {
        if (x < 2 && compteur / 52150 < presetDec) {
            x++;
            compteur++;
            cur_amplitude += 4;
        }
        else if (compteur / 52150 < presetDec && cur_seuil > presetSus) {
            x = 0;
            compteur++;
            cur_seuil--;
        }
        else {
            x = 0;
            compteur = 0;
            cur_amplitude = presetSus;
            cur_seuil = presetSus;
            sus = 52150 / (seuil_max - presetSus);  //sus == presetSus -> 0
            cur_env = SUS;
        }
    }

    else if (cur_env == REL)
    {
        if (x < 3 && compteur / 52150 < presetRel) {
            x++;
            compteur++;
            cur_amplitude += 2;
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
            cur_amplitude = 0;
            sus = 0;
            cur_env = ATK;
        }
    }
    if (presetOnde == CARRE)
        cur_amplitude = cur_seuil;
}
