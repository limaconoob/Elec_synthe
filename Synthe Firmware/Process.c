/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:11:36 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/05 17:11:52 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "Midi.h"

/*
**  _,-'�'-,_,-'�'-- Initialisation du MIDI --'�'-,_,-'�'-,_
**
**
**      ETAT      |        NOTE         |       VELOCITE
** 1000.... = ON  | 00000000 = C (= MIN)| ????????????????
** 1001.... = OFF | 01000101 = LA (440) | |
**                | 01111111 = G (= MAX)| '-> 00000000 (0 par d�faut)
**
**    MESSAGE_MIDI = 0b1000xxxx 0xxxxxxx 00000000
**                          |       |
**          Pas important <-'       '-> Num�ro de la note
**
**
**      o*o*o*o*o*o REFERENCES o*o*o*o*o*o
**  www.midi.org/images/downloads/midituning.pdf
**    www.pianoweb.fr/outils-messagesmidi.php
** www.microchip.com/wwwproducts/en/PIC32MX340F512H
** WIKIPEDIA: ,piano key frequencies' (= Valeur des fr�quences des notes)
**            ,Fourier Transform' (= Filtres)
**
**
**
*/


// ------------>  BOUTON  <----------------------------------------------------

void __ISR(_EXTERNAL_1_VECTOR, IPL2AUTO) note_pressed(void)
{
    /*get_note = NOTE_OFF;
    if (INTCONbits.INT1EP == FALLING_EDGE && !new_note)
    {
        get_note = NOTE_ON;             // Stock du message pour le parseur
        new_note = CURRENT_NOTE;        // Conservation de la note courante
        TMR2 = 0;
        if (parseur_note_on(get_note, new_note)) {
            init_state();
            note_mode = ATTACK;         // ATTACK_EVENT � l'initialisation
            INTCONbits.INT1EP = RISING_EDGE; // attend le rel�chement du bouton
            T2CONbits.ON = TRUE;        // D�marre le timer2 pour le compute
        }
    }

    // L'id�e c'est qu'il faut rel�cher la seule note jou�e (touches multiples)
    else if (parseur_note_off(get_note, CURRENT_NOTE)) {
        note_mode = RELEASE;        // Passage en mode release (END_EVENT)
        INTCONbits.INT1EP = FALLING_EDGE; // attend le prochain appui
    }*/

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

u16             generateur_enveloppe(u16 cur_intensite)
{
    u16         sustain;

    //-- GESTION DES MODES & COMPUTE --
    // La fonction read_env_preset va lire le preset pour l'enveloppe demand�
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
        // Ceci est dans le rel�chement du bouton : note_mode = RELEASE;
    }

    else if (note_mode == RELEASE) {
        note_mode = 0;
        init_state();
        TMR2 = 0;
        T2CONbits.ON = FALSE;
    }
}*/

void __ISR(_TIMER_2_VECTOR, IPL1AUTO) led_blink(void)
{

 //   generateur_enveloppe();
    //--- REINIT DU FLAG ---
    IFS0bits.T2IF = FALSE;
}


// ------------>  MAIN  <------------------------------------------------------

int             main(void) {

    init_bits();
    init_flag();
    init_state();
    tab_create();

    while(PROCESS) {
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
}
