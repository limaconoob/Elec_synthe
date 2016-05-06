/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:11:36 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/06 17:20:12 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "Midi.h"

/*
**  _,-'²'-,_,-'²'-- Initialisation du MIDI --'²'-,_,-'²'-,_
**
**
**      ETAT      |        NOTE         |       VELOCITE
** 1000.... = ON  | 00000000 = C (= MIN)| ????????????????
** 1001.... = OFF | 01000101 = LA (440) | |
**                | 01111111 = G (= MAX)| '-> 00000000 (0 par défaut)
**
**    MESSAGE_MIDI = 0b1000xxxx 0xxxxxxx 00000000
**                          |       |
**          Pas important <-'       '-> Numéro de la note
**
**
**      o*o*o*o*o*o REFERENCES o*o*o*o*o*o
**  www.midi.org/images/downloads/midituning.pdf
**    www.pianoweb.fr/outils-messagesmidi.php
** www.microchip.com/wwwproducts/en/PIC32MX340F512H
** WIKIPEDIA: ,piano key frequencies' (= Valeur des fréquences des notes)
**            ,Fourier Transform' (= Filtres)
**
**
**
*/


// ------------>  BOUTON  <----------------------------------------------------

void __ISR(_EXTERNAL_1_VECTOR, IPL2AUTO) note_pressed(void)
{
    message_midi_2 = 0b01000101;
    if (INTCONbits.INT1EP == FALLING_EDGE && !new_note)
    {
        get_note = NOTE_ON;             // Stock du message pour le parseur
        new_note = CURRENT_NOTE;        // Conservation de la note courante
        TMR2 = 0;
        if (parseur_note_on(get_note, new_note)) {
            init_state();
            note_mode = ATTACK;         // ATTACK_EVENT à l'initialisation
            INTCONbits.INT1EP = RISING_EDGE; // attend le relâchement du bouton
            T2CONbits.ON = TRUE;        // Démarre le timer2 pour le compute
            OC1CONbits.ON = TRUE;
        }
    }

    // L'idée c'est qu'il faut relâcher la seule note jouée (touches multiples)
    else if (parseur_note_off(NOTE_OFF, CURRENT_NOTE)) {
        note_mode = RELEASE;        // Passage en mode release (END_EVENT)
        INTCONbits.INT1EP = FALLING_EDGE; // attend le prochain appui
    }

    IFS0bits.INT1IF = FALSE;
}

void __ISR(_UART_1_VECTOR, IPL7AUTO) ft_uart(void)
{
    printf('BULL$HIT');
    IFS0bits.U1RXIF = FALSE;
}


// ------------>  COMPUTE  <---------------------------------------------------
/*
static void     get_decay(u16 cur_intensite, u16 mod_value)
{
}

static void     get_attack(u16 cur_intensite, u16 mod_value)
{
}
*/
/*u16             generateur_enveloppe(u16 cur_intensite)
{
    u16         sustain;

    //-- GESTION DES MODES & COMPUTE --
    // La fonction read_env_preset va lire le preset pour l'enveloppe demandé
    if (note_mode == ATTACK) {
        if (!cur_intensite)
            mod_value = read_env_preset(ATTACK);
        get_attack(cur_intensite, mod_value);
        if (cur_intensite == 0xFFFF)
            note_mode = DECAY;
    }

    else if (note_mode == DECAY) {
        if (cur_intensite == 0xFFFF) {
            sustain = read_env_preset(SUSTAIN);
            mod_value = read_env_preset(DECAY);
        }
        get_decay(cur_intensite, mod_value);
        if (cur_intensite == sustain)
            note_mode = SUSTAIN;
    }

    else if (note_mode == SUSTAIN) {
        // Ceci est dans le relâchement du bouton : note_mode = RELEASE;
    }

    else if (note_mode == RELEASE) {
        note_mode = 0;
        init_state();
        TMR2 = 0;
        T2CONbits.ON = FALSE;
        OC1CONbits.ON = FALSE;
    }
}*/


// PR2 = 633; 63191*PR2 = 1sec ; => Pour une période de 48kHz;
void __ISR(_TIMER_2_VECTOR, IPL1AUTO) led_blink(void)
{
    u16     cur_oscil;

    if (OC1RS != PR2) {
        OC1RS = PR2;
        magic_period = cur_period / 158;
        mode ^= 1;
    }
    cur_oscil = oscillateur(message_midi_2);

    magic_period--;
    if (magic_period == 0)
        OC1RS = (PR2 * get_period) / 100;

    // cur_oscil = generateur_enveloppe(cur_oscil);

    // dac(cur_oscil);

    //--- REINIT DU FLAG ---
    IFS0bits.T2IF = FALSE;
}


// ------------>  MAIN  <------------------------------------------------------

int             main(void) {

    init_bits();
    init_flag();
    init_state();
    tab_create(tab_period);

    while(PROCESS) {
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
}
