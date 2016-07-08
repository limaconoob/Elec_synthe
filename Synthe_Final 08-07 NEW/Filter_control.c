
#include "SynthyTwo.h"


void            init_pwm()
{
    OC1CON = 0;
    OC1CONbits.OCM = 0b101;             //OC3 sur front descendant
    OC1CONbits.OCTSEL = 0;              //Tmr2
    OC1R = 1;
    OC1RS = 2;
    OC1CONbits.ON = 1;

    OC2CON = 0;
    OC2CONbits.OCM = 0b101;             //OC3 sur front descendant
    OC2CONbits.OCTSEL = 0;              //Tmr2
    OC2R = 1;
    OC2RS = 1024;
    OC2CONbits.ON = 1;

    OC3CON = 0;
    OC3CONbits.OCM = 0b101;             //OC3 sur front descendant
    OC3CONbits.OCTSEL = 0;              //Tmr2
    OC3R = 1;
    OC3RS = (2047 * 2) / 100;
    OC3CONbits.ON = 1;
}
