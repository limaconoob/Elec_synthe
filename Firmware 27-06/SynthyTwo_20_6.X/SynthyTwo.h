/* 
 * File:   SynthyTwo.h
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:02 AM
 */

#ifndef SYNTHYTWO_H
#define	SYNTHYTWO_H

#include <stdio.h>
#include <stdlib.h>
#include <p32xxxx.h>
#include <sys/attribs.h>

#include "Types.h"

# define TRUE 1
# define FALSE 0
# define INPUT 1
# define OUTPUT 0
# define VCC 1
# define GND 0

# define MONTANT    0
# define DESCENDANT 1

# define ATK        0
# define DEC        1
# define SUS        2
# define REL        3

# define SQU        0
# define TRI        1
# define SAW        2
# define SIN        3

#define MIDI_CHANNEL 1

typedef     struct  s_env
{
    u8          Atk;
    u8          Dec;
    u8          Sus;
    u8          Rel;

    u16         compteur;
    u8          cur_env;
    u16         cur_amplitude;
    u16         amplitude_max;
    u16         seuil_max;
    u16         seuil_min;
    u16         env_reste;
}                   t_env;

typedef     struct  s_osc
{
    u16         jumper;
    u8          jump_adjust;
    u16         pos;

    u16         pitch;
    u8          pitch_adjust;

    u16         phi;
    u16         phi_adjust;

    u16         cursor;
    u8          phase;
    u8          reste;

    t_env       Env;
    u8          presetOnde;

}                   t_osc;

extern u16         tab_car[1420];
extern u16         tab_saw[1420];
extern u16         tab_tri[1420];
extern u16         tab_sin[1420];

extern u8          notesON;
extern u8          midi_note;
extern u16         DAC_value;

extern t_osc       OSC1;
extern t_osc       OSC2;

//------------------  Encodeurs  ----------------------
extern u8          prev_status;
extern u8          status;
# define _RD4      PORTDbits.RD4       // PIN A
# define _RD5      PORTDbits.RD5       // PIN B


extern u8          prev_status2;
extern u8          status2;
extern u8          boutons;
# define SW1       0x02
# define SW2       0x04
# define SW3       0x08
# define SW4       0x10
# define SW5       0x20
//------------------  Encodeurs  ----------------------


//------------------------- AudioBuffer.c -----------------------
//||                                                           ||
extern u8      onde;    // Forme de l'onde (change à l'appui du bouton)
extern u16     cursor;   // Donne la cadence d'augmentation de la tension
extern u16     pitch;
extern u8      pitch_adjust;
extern u8      phase;
extern u16     phi;
extern u8      reste;

u16     generateAudioSample(void);
//void __ISR(_TIMER_2_VECTOR, IPL1AUTO) sampleClock(void);
//||                                                           ||
//---------------------------------------------------------------



//---------------------------- DAC.c ----------------------------
//||                                                           ||
extern u16     DAC_value;       // VALUE EST LA TENSION (1 à FFFF) QUI VA AU DAC !

void         init_dac(void);
//void __ISR(_SPI_2_VECTOR, IPL3AUTO) sendSampleToDAC(void);
//||                                                           ||
//---------------------------------------------------------------



//-------------------------- Display.c --------------------------
//||                                                           ||
void      init_lcd(void);
void      waitXticks(u32 x);
void      lcd_pulse(void);
void      write4bits(u8 value);
void      lcd_command(u8 value, u8 rs);
void      lcd_printnbr(u16 value);
void      lcd_print(char *str);
void      lcd_goto(u8 col, u8 line);
//||                                                           ||
//---------------------------------------------------------------



//-------------------------- Enveloppe.c --------------------------
//||                                                           ||
extern u8      cur_env;
extern u16     compteur;
extern u16     cur_amplitude;

void            generateur_enveloppe(t_env *Env);
//||                                                           ||
//---------------------------------------------------------------



//--------------------------- MIDI.c ----------------------------
//||                                                           ||
extern u8      notesON;                  // nombre de notes enfoncees
extern u8      midi_note;                // note a jouer

void      init_MIDI(void);
void      processMIDIBuffer(void);
//void __ISR(_UART_1_VECTOR, IPL7SOFT) recieveMIDIbyte(void);
//||                                                           ||
//---------------------------------------------------------------



//------------------------ Oscillator.c -------------------------
//||                                                           ||
//static void         onde_carre(void);
//static void         onde_triangle(void);
//static void         onde_sawtooth(void);
//||                                                           ||
//---------------------------------------------------------------

//-------------------------- Preset.c ---------------------------
//||                                                           ||
void    init_preset(void);
//||                                                           ||
//---------------------------------------------------------------


//------------------------ TabCreate.c -------------------------
//||                                                           ||
extern u32      tab_period[88];

void    create_tab_period(void);
//||                                                           ||
//---------------------------------------------------------------



//--------------------------- Main.c ----------------------------
//||                                                           ||
extern u32     tab_period[88];         // Tableau contenant toutes les périodes
//void    tab_create(u32 *tab_period);
//void  main();
//||                                                           ||
//---------------------------------------------------------------



#endif	/* SYNTHYTWO_H */

