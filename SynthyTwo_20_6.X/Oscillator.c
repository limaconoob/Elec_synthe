/*
 * File:   Oscillator.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

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

/*    <-- *
  LE 16-06
PROBLEME :
L.enveloppe fait encore nimp...
MAIS
Les alggos d''ondes tiennent tous dans une seule ligne.
Elles dépendent toutes de "cur_amplitude". J''ai d''ailleur essayé de taper
dedans pour faire des tests dqns le generateur d''enveloppe (et au pasage 
j''ai repris mon alggo d''enveloppe, parce que j''arrivais mieux à le lire).
*/

/*    <-- *
  LE 17-06
OK ENVELOPPE, OK ONDES. NEED DOUBLE OSCILLO!
*/



u16            onde_carre(u8 phase, u16 cur_amplitude)
{
    return (!phase ? cur_amplitude : (0xFFFF - cur_amplitude));
}
/*
u16            onde_triangle(void)
{
    return (phase1 ? seuil_min1 - cur_amplitude1 - (2 * (phi1 * cursor1)) : seuil_max1 + cur_amplitude1 + (2 * (phi1 * cursor1)));
}

u16            onde_sawtooth(void)
{
    return (phase1 ? seuil_min1 - cur_amplitude1 - (phi1 * cursor1) : 0xFFFF - (phi1 * cursor1));
}

u16            onde_sawtooth_reverse(void)
{
    return (phase1 ? phi1 * cursor1 : seuil_max1 + cur_amplitude1 + (phi1 * cursor1));
}
*/

/*
u16            onde_triangle2(void)
{
    return (phase2 ? seuil_min2 - cur_amplitude2 - (2 * (phi2 * cursor2)) : seuil_max2 + cur_amplitude2 + (2 * (phi2 * cursor1)));
}

u16            onde_sawtooth2(void)
{
    return (phase2 ? seuil_min2 - cur_amplitude2 - (phi2 * cursor2) : 0xFFFF - (phi2 * cursor2));
}

u16            onde_sawtooth_reverse2(void)
{
    return (phase2 ? phi2 * cursor2 : seuil_max2 + cur_amplitude2 + (phi2 * cursor2));
}

u16            onde_carre2()
{
    return (phase2 ? seuil_min2 - cur_amplitude2 : seuil_max2 + cur_amplitude2);
}
 * */