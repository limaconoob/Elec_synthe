/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Read_Preset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:09:52 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/06 17:20:37 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "Midi.h"


u16             read_env_preset(s8 mode)
{
    u16         value;

    value = 0;
    if (mode == ATTACK) {
        value = 2;                  // En secondes
    }
    else if (mode == DECAY) {
        value = 2;                  // En secondes
    }
    else if (mode == SUSTAIN) {
        value = 0b0111111111111111; // En intensité du son
        return (value);             // (de 0 à 0b1111111111111111)
    }                               // (0b0xx... = négatif, 0b1xx... = positif)
    else if (mode == RELEASE) {
        value = 2;                  // En secondes
    }
    return (value);
}


u32             read_period_preset(void)
{
    u32         cur_periode;
    s8          cur_message;
    u32         centieme;

    cur_message = message_midi_2;
    cur_message += 1 * 12 /* preset_octave * 12 */; // Une octave de plus
    cur_message -= 3  /* preset_demi_ton */;        // Trois demi-tons de moins
    if (cur_message - 21 > 0) {
        cur_message -= 21;
        cur_periode = tab_period[cur_message];
        centieme = tab_period[cur_message - 1] - tab_period[cur_message];
        centieme /= 100;
        if (!centieme)
            centieme = 1;
        cur_periode += 10 * centieme /* preset_centieme * centieme */;
        return (cur_periode);
    }
    else if (cur_message - 21 == 0) {
        cur_message -= 21;
        cur_periode = tab_period[cur_message];
        centieme = tab_period[cur_message] - tab_period[cur_message + 1];
        centieme /= 100;
        if (!centieme)
            centieme = 1;
        cur_periode += 10 * centieme /* preset_centieme * centieme */;
        return (cur_periode);
    }
    return (tab_period[message_midi_2 - 21]);
}


s8              read_onde_preset(void)
{
    s8          onde_forme;
    
    onde_forme = CARRE;
    return (onde_forme);
}
