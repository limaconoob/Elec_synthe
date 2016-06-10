/*
 * File:   Oscillator.c
 * Author: Aydm
 *
 * Created on June 9, 2016, 5:08 AM
 */

#include "SynthyTwo.h"

void         init_oscil(void)
{
    IEC0bits.T2IE = TRUE;
    IFS0bits.T2IF = FALSE;
    IPC2bits.T2IP = 2;                //Priorit� basse
    IPC2bits.T2IS = 1;

    T2CON = 0;
    TMR2 = 0;
    PR2 = 767;
    T2CONbits.ON = TRUE;
}

u16     value = 1;       // VALUE EST LA TENSION (1 � FFFF) QUI VA AU DAC !
u8      onde = CARRE;    // Forme de l'onde (change � l'appui du bouton)
u16     cursor = 1000;   // Donne la cadence d'augmentation de la tension

void            onde_carre(void)
{
    static u16  pwm = 0x0000;      // Compteur basique (pour onde Carr�)
    static u8   mode = 0;          // Donne le sens d'�volution de la tension

    if (mode == MONTANT) {
        if (pwm < 0x7FFF - cursor) {    // Incr�mente un compteur
            pwm += cursor;              // jusqu'� beat
        }
        else {                          // Quand le compteur arrive � beat
            mode = DESCENDANT;          // on inverse la tension courante
            value = 0x8000;
            pwm = 0x8000;
        }
    }
    else if (mode == DESCENDANT) {
        if (pwm < 0xFFFF - cursor) {    // Incr�mente un compteur
            pwm += cursor;              // jusqu'� beat
        }
        else {                          // Quand le compteur arrive � beat
            mode = MONTANT;             // on inverse la tension courante
            value = 0x7FFF;
            pwm = 0x0000;
        }
    }
}

void         onde_triangle(void)
{
    static u8   mode = 0;
    u16         adj;    // Sert � ajuster la valeur pour garder la bonne fr�quence

    adj = cursor/2;
    if (mode == DESCENDANT)
    {
        if ((value <= 0xFFFF - (2*cursor + adj) && value > 0x7FFF) || value <= 0x7FFF - (2*cursor + adj)) {
            value += (2*cursor + adj);
        }
        else if (value >= 0xFFFF - (2*cursor + adj)) {
            value = 0x0000;
        }
        else if (value >= 0x7FFF - (2*cursor + adj)) {
            value = 0x7FFF;
            mode = MONTANT;
        }
    }
    else
    {
        if ((value >= 0x0000 + (2*cursor + adj) && value < 0x8000) || value >= 0x8000 + (2*cursor + adj)) {
            value -= (2*cursor + adj);
        }
        else if (value <= 0x0000 + (2*cursor + adj)) {
            value = 0xFFFF;
        }
        else if (value <= 0x8000 + (2*cursor + adj)) {
            value = 0x8000;
            mode = DESCENDANT;
        }
    }
}

void         onde_sawtooth(void)
{
    if ((value >= 0x0000 + cursor && value < 0x8000) || value >= 0x8000 + cursor) {
        value -= cursor;
    }
    else if (value <= 0x0000 + cursor) {
        value = 0xFFFF;
    }
    else if (value <= 0x8000 + cursor) {
        value = 0x7FFF;
    }
}

void __ISR(_TIMER_2_VECTOR, IPL2AUTO) sampleClock(void)
{
//    oscillator();
//    onde_carre();
//    onde_triangle();
    onde_sawtooth();
    processMIDI();

    IFS0bits.T2IF = FALSE;
}
