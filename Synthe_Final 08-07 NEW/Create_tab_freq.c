
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
    while (i++ < 2130)
        tab_saw[i] = i * 7;
    i--;
    while (i++ < 4259)
        tab_saw[i] = 0xD555 + (i * 7);
    tab_saw[0] = 0;
    tab_saw[1] = 0;
    tab_saw[2] = 0;
    tab_saw[3] = 0;
    tab_saw[4] = 0;
    tab_saw[5] = 0;
    tab_saw[6] = 0;
    tab_saw[7] = 0;
    tab_saw[8] = 0;
    tab_saw[9] = 0;
    tab_saw[10] = 0;
    tab_saw[11] = 0;
    tab_saw[12] = 0;
    tab_saw[13] = 0;
    tab_saw[4240] = 0xFFFF;
    tab_saw[4241] = 0xFFFF;
    tab_saw[4242] = 0xFFFF;
    tab_saw[4243] = 0xFFFF;
    tab_saw[4244] = 0xFFFF;
    tab_saw[4245] = 0xFFFF;
    tab_saw[4246] = 0xFFFF;
    tab_saw[4247] = 0xFFFF;
    tab_saw[4248] = 0xFFFF;
    tab_saw[4249] = 0xFFFF;
    tab_saw[4250] = 0xFFFF;
    tab_saw[4251] = 0xFFFF;
    tab_saw[4252] = 0xFFFF;
    tab_saw[4253] = 0xFFFF;
    tab_saw[4254] = 0xFFFF;
    tab_saw[4255] = 0xFFFF;
    tab_saw[4256] = 0xFFFF;
    tab_saw[4257] = 0xFFFF;
    tab_saw[4258] = 0xFFFF;
    tab_saw[4259] = 0xFFFF;

    // -------- ONDE TRIANGLE --------
    i = -1;
    while (i++ < 1064)
        tab_tri[i] = 0xFFFF - (i * 15);
    tab_tri[1064] = 0xD555;
	i--;
    while (i++ < 2129)
        tab_tri[i] = 0xD555 + ((i - 1064) * 15);
    tab_tri[2129] = 0xFFFF;
	i--;
    while (i++ < 3194)
        tab_tri[i] = (i - 2129) * 15;
    tab_tri[3194] = 0x2AAA;
	i--;
    while (i++ < 4259)
        tab_tri[i] = 0x2AAA - ((i - 3194) * 15);
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
