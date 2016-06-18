/*
 * File:   Enveloppe.c
 * Author: Jpepz
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

/*    <-- *
  LE 15-06
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
    static u16  seuil_temps = 0; //varie de 0 à 0x7FFF
    static u16  tempo = 0;

    if (cur_env1 == ATK)
    {
        if (cur_amplitude1 > 0)
            cur_amplitude1--;
        else
        {
            seuil_temps = seuil_min1 / (presetSus1 + 1);
            tempo = 0;
            cur_env1 = DEC;
        }
    }
    else if (cur_env1 == DEC)
    {
        if (tempo < seuil_temps)
            tempo++;
        else if (tempo == seuil_temps && cur_amplitude1 < presetSus1)
        {
            tempo = 0;
            cur_amplitude1++;
        }
        else
        {
            seuil_temps = seuil_min1 / (seuil_min1 - presetSus1 + 1);
            tempo = 0;
            cur_env1 = SUS;
        }
    }
    else if (cur_env1 == REL)
    {
        if (tempo < seuil_temps)
            tempo++;
        else if (tempo == seuil_temps && cur_amplitude1 < seuil_min1)
        {
            tempo = 0;
            cur_amplitude1++;
        }
        else
        {
            tempo = 0;
            seuil_temps = 0;
            cur_env1 = ATK;
        }
    }
}

void            generateur_enveloppe2(void)
{
    static u16  seuil_temps2 = 0; //varie de 0 à 0x7FFF
    static u16  tempo2 = 0;

    if (cur_env2 == ATK)
    {
        if (cur_amplitude2 > 0)
            cur_amplitude2--;
        else
        {
            seuil_temps2 = seuil_min2 / (presetSus2 + 1);
            tempo2 = 0;
            cur_env2 = DEC;
        }
    }
    else if (cur_env2 == DEC)
    {
        if (tempo2 < seuil_temps2)
            tempo2++;
        else if (tempo2 == seuil_temps2 && cur_amplitude2 < presetSus2)
        {
            tempo2 = 0;
            cur_amplitude2++;
        }
        else
        {
            seuil_temps2 = seuil_min2 / (seuil_min2 - presetSus2 + 1);
            tempo2 = 0;
            cur_env2 = SUS;
        }
    }
    else if (cur_env2 == REL)
    {
        if (tempo2 < seuil_temps2)
            tempo2++;
        else if (tempo2 == seuil_temps2 && cur_amplitude2 < seuil_min2)
        {
            tempo2 = 0;
            cur_amplitude2++;
        }
        else
        {
            tempo2 = 0;
            seuil_temps2 = 0;
            cur_env2 = ATK;
        }
    }
}
