/*
 * File:   MIDI.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

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
}

u8      midi_buffer[200];
u8      midi_byte_wr = 0;
u8      midi_byte_rd = 0;

void __ISR(_UART_1_VECTOR, IPL5SOFT) recieveMIDIbyte(void)
{
    while (U1STAbits.URXDA)
    {
        midi_buffer[midi_byte_wr++] = U1RXREG;  // U1RXREG est le buffer de réception UART
        if (midi_byte_wr >= 199)
            midi_byte_wr = 0;
        U1RXREG = 0;
    }
    IFS0bits.U1RXIF = FALSE;
}

u8      noteON = 0;

void        processMIDI(void)
{
    static u8 midiByte = 0;

    while (midi_byte_rd != midi_byte_wr)
    {
        midiByte = midi_buffer[midi_byte_rd++];
        if (midi_byte_rd >= 199)
            midi_byte_rd = 0;

        if (midiByte == 144)
            noteON++;
        else if (midiByte == 128 && noteON)
            noteON--;


        lcd_printnbr(midiByte);

    }
}

void         parseur_on_off(u8 message_midi)
{
    lcd_goto(6, 2);
    if ((message_midi >> 4) ^ 0b1000 == 0xFFFF)
        lcd_print("ON  ");
    else if ((message_midi >> 4) ^ 0b1001 == 0xFFFF)
        lcd_print("OFF ");
    else
        lcd_print("    ");
}
