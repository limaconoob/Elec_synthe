/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Read_Preset.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:09:52 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/05 17:10:11 by jpepin           ###   ########.fr       */
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

u32             read_period_preset(s8 message_midi)
{
    u32         cur_periode;

    message_midi += 12;             // Une octave de plus
    message_midi -= 3;              // Trois demi-tons de moins
    cur_periode = get_periode(message_midi);
    // cur_periode += nombre_de_centièmes;
    return (cur_periode);
}
