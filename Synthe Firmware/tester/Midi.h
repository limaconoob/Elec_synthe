/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Midi.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:03:53 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/05 21:12:17 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MIDI_H
# define MIDI_H

# define PROCESS 42
# define TRUE 1
# define FALSE 0
# define INPUT 1
# define OUTPUT 0
# define VCC 1
# define GND 0
# define RISING_EDGE 1
# define FALLING_EDGE 0


//-----> TYPES <---------------------------------------------------------------

typedef unsigned    char u8;
typedef unsigned    short u16;
typedef unsigned    long u32;
typedef signed      char s8;
typedef signed      short s16;
typedef signed      long s32;


//-----> NOTE MODE <-----------------------------------------------------------

# define ATTACK  1
# define DECAY   2
# define SUSTAIN 3
# define RELEASE 4


//-----> BIT MASKS <-----------------------------------------------------------

//--  OCTET 1 (ETAT) --
// Remplacer ,note_on' et ,note_off' par le message midi re�u
# define NOTE_ON note_on >> 20      // Bit [23-20]
# define NOTE_OFF note_off >> 20    // Bit [23-20]
# define ON_EVENT 0b1000            // Bit [23-20]
# define OFF_EVENT 0b1001           // Bit [23-20]

//--  OCTET 2 (NOTE) --
// Dans CURRENT_NOTE il faut remplacer ,note_on' par le message midi re�u
# define CURRENT_NOTE ((note_on >> 8) & 0xFF00) - 0xFF00  // Bit [15-8]
# define NOTE_MAX 0b01101100
# define NOTE_MIN 0b00010101

//- OCTET 3 (VELOCITE)-
// ON S'EN TAPE. MERCI AU REVOIR! :)



//-----> VARIABLES GLOBALES <--------------------------------------------------
/*
//Simulation du message MIDI :: LA 440 ON
u8             note_on = 0b10000000;
u8			   note_la = 0b01000101;
u8			   note_veloc = 0b00000000;

//Simulation du message MIDI :: LA 440 OFF
s32             note_off = 0b100100000100010100000000;

//Gestion du parsing de la note (Bonne note? Bon message?)
s8              get_note = 0;   // PARSEUR DE NOTE
s8              new_note = 0;   // CONSERVE LA NOTE COURANTE

//Gestion du mode courant => attack | decay | sustain | release
s8              note_mode;        // Indique le mode en cours
u8              mod_value;        // Valeur du preset (ATK,DEC,REL sec; SUS int)
u32             tab_period[88];   // Tableau de p�riodes
s8              key_hold = FALSE; // Indique si la note est toujours enfonc�e
*/

//-----> PROTOTYPES DES FONCTIONS <--------------------------------------------

// INIT
void                init_bits(void);
void                init_flags(void);
void                init_state(void);
void				tab_create(u32 *tab_period);

// PARSEUR
s8              parseur_note_on(s8 get_note, s8 cur_note);
s8              parseur_note_off(s8 get_note, s8 cur_note);

// OSCILLATEUR
u16                 genererateur_enveloppe(u8 note_mode);
u32                 get_periode(s8 message_midi);
u16                 oscillateur(void);

// DEBUG
# define	BUFF_SIZE 1024
void				print_period(u32 period, char *onde);
int					tab_size(char **tab);
char				**ft_splitspaces(char *str);
int					get_next_line(int fd, char **line);
char				*ft_concat(char *s1, char *s2, int pot);
void                regprocess(u32 *tab_period, char **presets);

#endif	// endif MIDI_H
