
#include "SynthyTwo.h"

void    create_tab_frequenz(void)
{
    s16 i;

	// 1420 * 3 = 4260

    // --------- ONDE CARRE ----------
    i = -1;
    while (i++ < 2130)
        tab_car[i] = 0x2AAA;
    i--;
    while (i++ < 4260)
        tab_car[i] = 0xD555;

    // -------- ONDE SAWTOOTH --------
    i = -1;
    while (i++ < 4259)
        tab_saw[i] = i * 15;
    tab_saw[4259] = 0xFFFF;

    // -------- ONDE TRIANGLE --------
    i = -1;
    while (i++ < 1064)
        tab_tri[i] = 0xFFFF - (i * 30);
    tab_tri[1064] = 0x8000;
	i--;
    while (i++ < 2129)
        tab_tri[i] = 0x8000 + ((i - 1064) * 30);
    tab_tri[2129] = 0xFFFF;
	i--;
    while (i++ < 3194)
        tab_tri[i] = (i - 2129) * 30;
    tab_tri[3194] = 0x7FFF;
	i--;
    while (i++ < 4259)
        tab_tri[i] = 0x7FFF - ((i - 3194) * 30);
    tab_tri[4259] = 0x0000;
   
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
}
