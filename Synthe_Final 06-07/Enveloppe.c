
#include "SynthyTwo.h"


#define ENV_TimeScaler  5000

u16	generateur_enveloppe(u16 value, t_env *Env)
{
    u32 new_val;
    if ((*Env).cur_env == ATK)
    {
        if ((*Env).compteur / ENV_TimeScaler < ((*Env).Atk + 1))
            (*Env).pourcentage = ((*Env).compteur * 100) / (ENV_TimeScaler * ((*Env).Atk + 1));
        else
        {
            (*Env).cur_env = DEC;
            (*Env).compteur = 0;
        }
    }
    else if ((*Env).cur_env == DEC)
    {
        if ((*Env).compteur / ENV_TimeScaler < ((*Env).Dec + 1))
            (*Env).pourcentage = 100 - (((*Env).compteur * (*Env).sus_pourcentage) / (ENV_TimeScaler * ((*Env).Dec + 1)));
        else
        {
            (*Env).cur_env = SUS;
            (*Env).pourcentage = (*Env).sus_pourcentage;
            (*Env).compteur = 0;
        }
    }
    else if ((*Env).cur_env == REL)
    {
        if ((*Env).compteur / ENV_TimeScaler < ((*Env).Rel / 2) + 3)
            (*Env).pourcentage = (100 - (*Env).sus_pourcentage) - (((*Env).compteur * (*Env).sus_pourcentage) / (ENV_TimeScaler * ((*Env).Rel + 1)));
        else 
        {
            (*Env).cur_env = 0;
            (*Env).compteur = 0;
        }
    }
    new_val = (value * (*Env).pourcentage) / 100;
    return (new_val);
}
