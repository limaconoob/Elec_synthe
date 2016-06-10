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

# define PROCESS 42
# define TRUE 1
# define FALSE 0
# define INPUT 1
# define OUTPUT 0
# define VCC 1
# define GND 0

# define MONTANT    0
# define DESCENDANT 1

# define CARRE      1
# define TRIANGLE   2
# define SAWTOOTH   3
# define SINUSOID   4


//------- DAC.c -------
void         init_dac(void);
//void __ISR(_SPI_2_VECTOR, IPL3AUTO) sendSampleToDAC(void);

//----- Display.c -----
//void      init_lcd(void);
void      waitXticks(u32 x);
void      lcd_pulse(void);
void      write4bits(u8 value);
void      lcd_command(u8 value, u8 rs);
void      lcd_printnbr(u16 value);
void      lcd_print(char *str);
void      lcd_goto(u8 col, u8 line);

//------ MIDI.c -------
extern u8      midi_buffer[200];
extern u8      midi_byte_wr;
extern u8      midi_byte_rd;
extern u8      noteON;

void      init_MIDI(void);
void      processMIDI(void);
//void __ISR(_UART_1_VECTOR, IPL7SOFT) recieveMIDIbyte(void);

//--- Oscillator.c ----
extern u16     value;       // VALUE EST LA TENSION (1 � FFFF) QUI VA AU DAC !
extern u8      onde;    // Forme de l'onde (change � l'appui du bouton)
extern u16     cursor;   // Donne la cadence d'augmentation de la tension
void         init_oscil(void);
//static void         onde_carre(void);
//static void         onde_triangle(void);
//static void         onde_sawtooth(void);
//void __ISR(_TIMER_2_VECTOR, IPL1AUTO) sampleClock(void);

//------ Main.c -------
static u32     tab[88];         // Tableau contenant toutes les p�riodes
//void    tab_create(u32 *tab_period);
//void  main();

#endif	/* SYNTHYTWO_H */

