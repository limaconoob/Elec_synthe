/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Oscillateur.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:10:34 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/06 17:19:20 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "Midi.h"

// Ici, oscil est la valeur (de 0x0000 à 0xFFFF) de tension envoyée au DAC

u16             oscillateur(void)
{
    u16         oscil;

    if (onde == TRIANGLE) {
        if (mode == 0) {
            if (pwm < beat) {
                pwm++;
                oscil = pwm;
            }
            else if (pwm == beat) {
                mode = 1;
                beat = !(beat & 0xFFFF);
            }
        }
        else {
            if (pwm > beat) {
                pwm--;
                oscil = pwm;
            }
            else if (pwm == beat) {
                mode = 0;
                beat = !(beat & 0xFFFF);
            }
        }
    }

    else if (onde == CARRE) {
        if (mode == 0) {
            if (pwm < beat) {
                pwm++;
            }
            else if (pwm == beat) {
                mode = 1;
                oscil = pwm;
            }
        }
        else {
            if (pwm > beat) {
                pwm--;
            }
            else if (pwm == beat) {
                mode = 0;
                oscil = pwm;
            }
        }
    }

    else if (onde == SAWTOOTH) {
        if (mode == 0) {
            if (pwm < beat) {
                pwm++;
            }
            else if (pwm == beat) {
                pwm = !(pwm & 0xFFFF);
            }
        }
        else {
            if (pwm > beat) {
                pwm--;
            }
            else if (pwm == beat) {
                pwm = !(pwm & 0xFFFF);
            }
        }
        oscil = pwm;
    }

    return (oscil);
}
