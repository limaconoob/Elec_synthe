/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Parseur.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 16:58:03 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/06 17:19:35 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "Midi.h"

// ----------->  PARSEURS  <----------------------------------------------------
// |
// '-> Retourne 1 en cas de succès, et 0 en cas d'erreur.

s8              parseur_note_on(s8 get_note, s8 cur_note)
{
    if (message_midi_2 <= NOTE_MAX && message_midi_2 >= NOTE_MIN) {
        if (!(get_note ^ ON_EVENT))
            return (1);
    }
    message_midi_2 = 0; // Si le parse de la note ON échoue on reboot la note courante
    return (0);
}

s8              parseur_note_off(s8 get_note, s8 cur_note)
{
    if (INTCONbits.INT1EP == RISING_EDGE && cur_note == message_midi_2) {
        if (!(get_note ^ OFF_EVENT))
            return (1);
    }
    return (0);
}
