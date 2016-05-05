/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oscillateur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:10:34 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/05 17:10:48 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "Midi.h"

//-----------------------------------------------------------------------------

//  On récupère la bonne valeur en fonction de l'octet central MIDI
u32            get_periode(s8 message_midi)
{
    message_midi -= 21;
    return (tab_period[message_midi]);
}

//-----------------------------------------------------------------------------
//
u16             oscillateur(s8 message_midi)
{
    u32 cur_periode;

    cur_periode = read_period_preset(message_midi);

}
