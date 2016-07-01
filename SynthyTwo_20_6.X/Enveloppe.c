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

#define ENV_TimeScaler  5000

void            generateur_enveloppe(t_env *Env)
{
    (*Env).compteur++;
    if ((*Env).cur_env == ATK)
    {
        if ((*Env).compteur / ENV_TimeScaler < ((*Env).Atk + 1))
        {
            (*Env).cur_amplitude += ((*Env).amplitude_max / (ENV_TimeScaler * ((*Env).Atk + 1)));
            (*Env).env_reste += (((*Env).amplitude_max % (ENV_TimeScaler * ((*Env).Atk + 1))) * 1000) / (ENV_TimeScaler * ((*Env).Atk + 1));
            if ((*Env).env_reste >= 1000)
            {
                (*Env).cur_amplitude++;
                (*Env).env_reste -= 1000;
            }
        }
        else
        {
            (*Env).cur_env = DEC;
            (*Env).compteur = 0;
        }
    }

    else if ((*Env).cur_env == DEC)
    {
        if ((*Env).compteur / ENV_TimeScaler < ((*Env).Dec + 1))
        {
            (*Env).cur_amplitude -= ((((*Env).amplitude_max / 16) * ((*Env).Sus + 1)) / (ENV_TimeScaler * ((*Env).Dec + 1)));
            (*Env).env_reste += (((((*Env).amplitude_max / 16) * ((*Env).Sus + 1)) % (ENV_TimeScaler * ((*Env).Dec + 1))) * 1000) / (ENV_TimeScaler * ((*Env).Dec + 1));
            if ((*Env).env_reste >= 1000)
            {
                (*Env).cur_amplitude--;
                (*Env).env_reste -= 1000;
            }
        }
        else
        {
            (*Env).cur_env = SUS;
            (*Env).compteur = 0;
        }
    }
    else if ((*Env).cur_env == REL)
    {
        if ((*Env).compteur / ENV_TimeScaler < (*Env).Rel)
        {
            (*Env).env_reste += ((2 * (*Env).cur_amplitude % (ENV_TimeScaler * (*Env).Rel)) * 1000) / (ENV_TimeScaler * (*Env).Rel);
            if ((*Env).env_reste >= 1000)
            {
                (*Env).cur_amplitude -= 2;
                (*Env).env_reste -= 1000;
            }
            (*Env).cur_amplitude -= (2 * (*Env).cur_amplitude / (ENV_TimeScaler * (*Env).Rel));
        }
        else
        {
            (*Env).cur_env = 0;
            (*Env).compteur = 0;
        }
    }
}

/*
void            generateur_enveloppe(void)
{
    static u8   x = 0;
    static u16  sus = 0;

    // 52150 = 0.5 sec en théorie

    if (cur_env == ATK)
    {
        if (x < 1 && compteur / ENV_TimeScaler < presetAtk) {
            x++;
            compteur++;
        }
        else if (cur_seuil < seuil_max && compteur / ENV_TimeScaler < presetAtk) {
            x = 0;
            compteur++;
            cur_seuil++;
        }
        else {
            x = 0;
            compteur = 0;
            cur_seuil = seuil_max;
            sus = ENV_TimeScaler / presetSus;       //sus == seuil_max . presetSus
            cur_env = DEC;
        }
    }

    else if (cur_env == DEC)
    {
        if (x < sus && compteur / ENV_TimeScaler < presetDec) {
            x++;
            compteur++;
        }
        else if (compteur / ENV_TimeScaler < presetDec && cur_seuil) {
            x = 0;
            compteur++;
            cur_seuil--;
        }
        else {
            x = 0;
            compteur = 0;
            cur_seuil = presetSus;
            sus = ENV_TimeScaler / (seuil_max - presetSus);  //sus == presetSus . 0
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
        if (x < sus && compteur / ENV_TimeScaler < presetRel) {
            x++;
            compteur++;
        }
        else if (compteur / ENV_TimeScaler < presetRel && cur_seuil) {
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
*/


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
 * */