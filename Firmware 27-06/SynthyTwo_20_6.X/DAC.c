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
    IEC0bits.T2IE = TRUE;
    IFS0bits.T2IF = FALSE;
    IPC2bits.T2IP = 4;                //Priorité basse
    IPC2bits.T2IS = 1;

    T2CON = 0;
    TMR2 = 0;
    PR2 = 2047;

    T2CONbits.ON = TRUE;
    OC5CON = 0;
    OC5CONbits.OCM = 0b101;             //OC3 sur front descendant
    OC5CONbits.OCTSEL = 0;              //Tmr2
    OC5R = 80;
    OC5RS = OC5R + 1024;
    OC5CONbits.ON = 1;

    //SysClock generator - 80Mhz / 6
    T3CON = 0;
    TMR3 = 0;
    PR3 = 7;
    OC4CON = 0;
    OC4CONbits.OCM = 0b011;             //OC3 sur front descendant
    OC4CONbits.OCTSEL = 1;              //Tmr3
    OC4R = 7;
    OC4CONbits.ON = 1;
    T3CONbits.ON = 1;

    //SPI2 audio sample transmission
    IFS1bits.SPI2TXIF = FALSE;
    IPC7bits.SPI2IP =  6;
    IPC7bits.SPI2IS =  1;
    IEC1bits.SPI2TXIE = TRUE;

    SPI2CON = 0;
    SPI2BUF = 0;
    SPI2BRG = 31;
    SPI2STATbits.SPIROV = 0;
    SPI2CONbits.FRMEN = 0;              //NON Framed mode (generation de clock ininterompue)
    SPI2CONbits.FRMSYNC = 0;            //Frame master
    SPI2CONbits.MSTEN = 1;              //Set SPI2 as Master
    SPI2CONbits.MODE16 = 1;             //16bit messages to transmit
    SPI2CONbits.MODE32 = 0;
    SPI2CONbits.CKE = 0;
    SPI2CONbits.ON = 1;

    SPI2BUF = 1;                         //Start SPI2

}

void __ISR(_SPI_2_VECTOR, IPL6AUTO) sendSampleToDAC(void)
{
    static u8              flag = 0;

    SPI2BUF = DAC_value;
    if (!flag) {
        OSC1.pos += OSC1.jumper;
        if (OSC1.reste >= 100) {
            OSC1.pos++;
            OSC1.reste -= 100;
        }
        OSC1.reste += OSC1.jump_adjust;
        OSC1.pos = (OSC1.pos >= 1420 ? (OSC1.pos - 1420) : OSC1.pos);
        flag = 1;
    }
    else
        flag = 0;
 //   if (OSC1.phi)
 //       OSC1.phi--;
 //   if (OSC2.phi)
 //       OSC2.phi--;
    IFS1bits.SPI2TXIF = FALSE;
}

