/*
 * File:   MIDI.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

static u8      midi_buffer[200];
static u8      midi_buffer_wr = 0;
static u8      midi_buffer_rd = 0;

static u8      midi_status = 0;
static u8      midi_data1 = 0xFF;        // FF car 0 est une valeur utilisable
static u8      midi_data2 = 0xFF;

u8             notesON = 0;              // compteur de notes enfoncees
u8             midi_note;                // note a jouer
static u8      midi_notesON[88];

void        resetMIDIMessage(void)
{
    midi_status = 0;
    midi_data1 = 0xFF;
    midi_data2 = 0xFF;
}

void        calculatePitch(void)
{
    OSC1.jumper = 1420 / (tab_period[midi_note] / 128);
    OSC1.jump_adjust = ((1420 % (tab_period[midi_note] / 128)) * 100) / (tab_period[midi_note] / 128);
}

void        processMIDINoteON(void)
{
    if (midi_data2 && !midi_notesON[midi_data1])
    {
        midi_notesON[midi_data1] = midi_data2;
        if (!notesON)
        {
            OSC1.Env.cur_env = ATK;
            OSC1.Env.cur_amplitude = 0;
            OSC1.Env.compteur = 0;

            OSC2.Env.cur_env = ATK;
            OSC2.Env.cur_amplitude = 0;
            OSC2.Env.compteur = 0;
        }
        notesON++;
        if (midi_data1 >= midi_note)        //La note la plus aigue est jouee
            midi_note = midi_data1;

        calculatePitch();
    }
    resetMIDIMessage();
}

void        processMIDINoteOFF(void)
{
    midi_notesON[midi_data1] = 0;
    notesON--;
    if (notesON)
    {
        if (midi_data1 == midi_note)    //Si on relache la note la plus aigue
        {
            u8 x = midi_data1;
            while (midi_notesON[x] == 0 && x)
                x--;
            midi_note = x;   // on jouera la note enfoncee en dessous
            calculatePitch();
        }
    }
    else
    {
       OSC1.Env.cur_env = 0;
//       OSC1.Env.cur_env = REL;
       OSC1.Env.compteur = 0;
       OSC2.Env.cur_env = REL;
       OSC2.Env.compteur = 0;

       midi_note = 0;
       u8 x;
       for (x = 0; x < 88; x++)
           midi_notesON[x] = 0;
    }

    resetMIDIMessage();
}

void        processMIDIMessage(void)
{
    if (midi_status == 9)
        processMIDINoteON();
    else if (midi_status == 8)
        processMIDINoteOFF();
}

void        processMIDIStatusByte(u8 midiByte)
{
    //---- Status byte ----
    //   1 s s s n n n n
    //   s : message type
    //   n : midi channel

    if (((midiByte << 4) & 0b11110000) == 0)
    {
        midiByte = ((midiByte << 1) >> 5);
        midi_status = midiByte;
    }
}

void        processMIDIDataByte(u8 midiByte)
{
    //----  Data byte  ----
    //   0 x x x x x x x
    //   x : data
    if (midi_status == 8 || midi_status == 9)       //Support note ON/OFF only
    {
        if (midi_data1 == 0xFF)
            midi_data1 = midiByte;
        else
        {
            midi_data2 = midiByte;
            processMIDIMessage();
        }
    }
    else
        midi_status = 0;
}

void        processMIDIBuffer(void)
{
    u8 midiByte;

    while (midi_buffer_rd != midi_buffer_wr)
    {
        midiByte = midi_buffer[midi_buffer_rd++];
        if (midi_buffer_rd >= 199)
            midi_buffer_rd = 0;

        if ((midiByte >> 7) == 1)
            processMIDIStatusByte(midiByte);
        else
            processMIDIDataByte(midiByte);
    }
}

void __ISR(_UART_4_VECTOR, IPL5SOFT) recieveMIDIbyte(void)
{
    while (U4STAbits.URXDA)
    {
        midi_buffer[midi_buffer_wr++] = U4RXREG;  // U1RXREG est le buffer de réception UART
        if (midi_buffer_wr >= 199)
            midi_buffer_wr = 0;
        U4RXREG = 0;
    }
    IFS2bits.U4RXIF = FALSE;
}

void         init_MIDI(void)
{
    // UART pour la réception MIDI IN et envoi de MIDI THRU
    // BaudRate MIDI = 31250;

    IFS2bits.U4RXIF = FALSE;
    IPC12bits.U4IP = 5;                //Priorité maximale
    IPC12bits.U4IS = 1;
    IEC2bits.U4RXIE = TRUE;           //Enable UART1 Reception interrupt

    U4STA = 0;
    U4MODE = 0;
    U4RXREG = 0;
    U4BRG = 146;                         // Set Baud rate
    U4STAbits.URXISEL = 0b00;
    U4STAbits.URXEN = 1;
    U4MODEbits.ON = TRUE;               // Enable UART for 8-bit data

    u8 x;
    for (x = 0; x < 88; x++)
        midi_notesON[x] = 0;
}

