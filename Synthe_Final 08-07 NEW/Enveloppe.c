
#include "SynthyTwo.h"


#define ENV_TimeScaler  20

u8      env_tabAtk[16];
u8      env_tabDec[16];
u8      env_tabRel[16];

u16	generateur_enveloppe(u16 value, t_env *Env)
{
    if (Env->compteur == ENV_TimeScaler)
    {
        Env->compteur = 0;
        if (Env->cur_env == ATK)
        {
            if (Env->pourcentage < ENV_Coeff)
                Env->pourcentage += env_tabAtk[Env->Atk];
            else
            {
                Env->pourcentage = ENV_Coeff;
                Env->cur_env = DEC;
            }
        }
        else if (Env->cur_env == DEC)
        {
            if (Env->pourcentage >= Env->sus_pourcentage)
                Env->pourcentage -= env_tabDec[Env->Dec];
            else
            {
                Env->cur_env = SUS;
                Env->pourcentage = Env->sus_pourcentage;
            }
        }
        else if (Env->cur_env == REL)
        {
            if (Env->pourcentage > 2 * env_tabRel[Env->Rel])
                Env->pourcentage -= env_tabRel[Env->Rel];
            else
                Env->cur_env = 0;
        }
    }

    return (multiplySample(value, Env->pourcentage, ENV_Coeff));
}

void    create_tab_env(void)
{
    env_tabAtk[0] = ENV_Coeff;
    env_tabAtk[1] = 30;
    env_tabAtk[2] = 20;
    env_tabAtk[3] = 15;
    env_tabAtk[4] = 12;
    env_tabAtk[5] = 11;
    env_tabAtk[6] = 10;
    env_tabAtk[7] = 9;
    env_tabAtk[8] = 8;
    env_tabAtk[9] = 7;
    env_tabAtk[10] = 6;
    env_tabAtk[11] = 5;
    env_tabAtk[12] = 4;
    env_tabAtk[13] = 3;
    env_tabAtk[14] = 2;
    env_tabAtk[15] = 1;

    env_tabDec[0] = 100;
    env_tabDec[1] = 50;
    env_tabDec[2] = 30;
    env_tabDec[3] = 25;
    env_tabDec[4] = 20;
    env_tabDec[5] = 17;
    env_tabDec[6] = 15;
    env_tabDec[7] = 12;
    env_tabDec[8] = 10;
    env_tabDec[9] = 9;
    env_tabDec[10] = 8;
    env_tabDec[11] = 7;
    env_tabDec[12] = 5;
    env_tabDec[13] = 3;
    env_tabDec[14] = 2;
    env_tabDec[15] = 1;

    env_tabRel[0] = ENV_Coeff;
    env_tabRel[1] = 15;
    env_tabRel[2] = 14;
    env_tabRel[3] = 13;
    env_tabRel[4] = 12;
    env_tabRel[5] = 11;
    env_tabRel[6] = 10;
    env_tabRel[7] = 9;
    env_tabRel[8] = 8;
    env_tabRel[9] = 7;
    env_tabRel[10] = 6;
    env_tabRel[11] = 5;
    env_tabRel[12] = 4;
    env_tabRel[13] = 3;
    env_tabRel[14] = 2;
    env_tabRel[15] = 1;
}