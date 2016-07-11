
#include "SynthyTwo.h"

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
    
    // NOISE
    tab_noise();
}

