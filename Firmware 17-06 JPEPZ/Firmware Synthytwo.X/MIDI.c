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
    u32 x = 128;

    pitch = tab_period[midi_note] / x;
    pitch_adjust = ((tab_period[midi_note] % x) * 100) / x;
    phi1 = pitch - 1;
    phi2 = pitch - 1;
}

void        processMIDINoteON(void)
{
    midi_notesON[midi_data1] = midi_data2;
    notesON++;
    if (midi_data1 >= midi_note) {        //La note la plus aigue est jouee

            cur_env1 = ATK;
            cur_amplitude1 = seuil_min1;
            cur_env2 = ATK;
            cur_amplitude2 = seuil_min2;

        midi_note = midi_data1;
    }
    calculatePitch();

    resetMIDIMessage();
}

void        processMIDINoteOFF(void)
{
    midi_notesON[midi_data1] = 0;
    if (notesON)
    {
        notesON--;
        if (midi_data1 == midi_note)    //Si on relache la note la plus aigue
        {
            u8 x = midi_data1;
            while (midi_notesON[midi_data1] == 0 && midi_data1)
                midi_data1--;
            midi_note = midi_data1;   // on jouera la note enfoncee en dessous
        }
    }
    u8 x;
    if (!notesON)
    {
           cur_env1 = REL;
           cur_env2 = REL;

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

void __ISR(_UART_1_VECTOR, IPL5SOFT) recieveMIDIbyte(void)
{
    while (U1STAbits.URXDA)
    {
        midi_buffer[midi_buffer_wr++] = U1RXREG;  // U1RXREG est le buffer de réception UART
        if (midi_buffer_wr >= 199)
            midi_buffer_wr = 0;
        U1RXREG = 0;
    }
    IFS0bits.U1RXIF = FALSE;
}

void         init_MIDI(void)
{
    // UART pour la réception MIDI IN et envoi de MIDI THRU
    // BaudRate MIDI = 31250;

    IFS0bits.U1RXIF = FALSE;
    IPC6bits.U1IP = 5;                //Priorité maximale
    IPC6bits.U1IS = 1;
    IEC0bits.U1RXIE = TRUE;           //Enable UART1 Reception interrupt

    U1STA = 0;
    U1MODE = 0;
    U1RXREG = 0;
    U1BRG = 159;                         // Set Baud rate
    U1STAbits.URXISEL = 0b10;
    U1STAbits.URXEN = 1;
    U1MODEbits.ON = TRUE;               // Enable UART for 8-bit data

    u8 x;
    for (x = 0; x < 88; x++)
        midi_notesON[x] = 0;
}
