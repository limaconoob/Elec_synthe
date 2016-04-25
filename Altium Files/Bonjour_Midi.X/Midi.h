/* 
 * File:   Midi.h
 * Author: bocal
 *
 * Created on April 11, 2016, 11:02 PM
 */

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


//-*-*- NOTE MODE -*-*-
# define ATTACK  1
# define DECAY   2
# define SUSTAIN 3
# define RELEASE 4

//-*-*- BIT MASKS -*-*-

//--  OCTET 1 (ETAT) --
# define NOTE_ON note_on >> 20      // Bit [23-20]
# define NOTE_OFF note_off >> 20    // Bit [23-20]
# define ON_EVENT 0b1000            // Bit [23-20]
# define OFF_EVENT 0b1001           // Bit [23-20]

//--  OCTET 2 (NOTE) --
# define CURRENT_NOTE ((note_on >> 8) & 0x7F) - 0x7F  // Bit [15-8]

//- OCTET 3 (VELOCITE)-

typedef unsigned    char u8;
typedef unsigned    short u16;
typedef unsigned    long u32;
typedef signed      char s8;
typedef signed      short s16;
typedef signed      long s32;

#endif	// endif MIDI_H
