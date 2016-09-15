/*
 * File:   DAC.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"


void         init_dac(void)
{
    //LR generator - samplingFreq / 2
    IEC0bits.T2IE = TRU;
    IFS0bits.T2IF = FALS;
    IPC2bits.T2IP = 4;                //Priorité basse
    IPC2bits.T2IS = 1;

    T2CON = 0;
    TMR2 = 0;
    PR2 = 2047;

    OC5CON = 0;
    OC5CONbits.OCM = 0b101;             //OC3 sur front descendant
    OC5CONbits.OCTSEL = 0;              //Tmr2
    OC5R = 870;
    OC5RS = OC5R + 1024;
    T2CONbits.ON = TRU;
    OC5CONbits.ON = 1;

    //SysClock generator - 80Mhz / 6
    T3CON = 0;
    TMR3 = 0;
    PR3 = 7;
    OC4CON = 0;
    OC4CONbits.OCM = 0b011;             //OC3 sur front descendant
    OC4CONbits.OCTSEL = 1;              //Tmr3
    OC4R = 3;
    OC4CONbits.ON = 1;
    T3CONbits.ON = 1;

    SPI4CON = 0;
    SPI4BUF = 0;
    SPI4BRG = 31;
    SPI4STATbits.SPIROV = 0;
    SPI4CONbits.FRMEN = 0;              //NON Framed mode (generation de clock ininterompue)
    SPI4CONbits.FRMSYNC = 0;            //Frame master
    SPI4CONbits.MSTEN = 1;              //Set SPI2 as Master
    SPI4CONbits.MODE16 = 1;             //16bit messages to transmit
    SPI4CONbits.MODE32 = 0;
    SPI4CONbits.CKE = 0;
    SPI4CONbits.CKP = 1;
    SPI4CONbits.MSSEN = 0;
    SPI4CONbits.ON = 1;

    SPI4BUF = 1;                         //Start SPI2

    //SPI2 audio sample transmission
    IFS1bits.SPI4TXIF = FALS;
    IPC8bits.SPI4IP =  6;
    IPC8bits.SPI4IS =  1;
    IEC1bits.SPI4TXIE = TRU;
}

void __ISR(_SPI_4_VECTOR, IPL6AUTO) sendSampleToDAC(void)
{
    static u8              flag = 0;

    SPI4BUF = DAC_value;

    if (!flag)
    {
        if (OSC1.Env.cur_env)
        {
            OSC1.pos += OSC1.jumper;
            OSC1.reste += OSC1.jump_adjust;
            if (OSC1.reste >= 100) {
                OSC1.pos++;
                OSC1.reste -= 100;
            }
            OSC1.pos = (OSC1.pos >= 1420 ? (OSC1.pos - 1420) : OSC1.pos);
        }
        
        if (OSC2.Env.cur_env)
        {
            OSC2.pos += OSC2.jumper;
            OSC2.reste += OSC2.jump_adjust;
            if (OSC2.reste >= 100) {
                OSC2.pos++;
                OSC2.reste -= 100;
            }
            OSC2.pos = (OSC2.pos >= 1420 ? (OSC2.pos - 1420) : OSC2.pos);
        }
        flag = 1;
    }
    else
        flag = 0;

    IFS1bits.SPI4TXIF = FALS;
}

