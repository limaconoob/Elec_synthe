/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jpepin <jpepin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/05/05 17:08:13 by jpepin            #+#    #+#             */
/*   Updated: 2016/05/06 17:17:07 by jpepin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "Midi.h"

// ---------->  INITIALISATION  <----------------------------------------------

void            init_bits(void)
{
    //-----  PAD IO  -----
    TRISFbits.TRISF1 = OUTPUT;          //RF1 = Led verte
    LATFbits.LATF1 = GND;               //Etat initial = éteint
    TRISDbits.TRISD8 = INPUT;           //RD8 = Bouton

    //-----  TIMER2  -----
    T2CON = 0;                          //Clear le timer2
    T2CONbits.ON = FALSE;               //Attend la pression du bouton
    TMR2 = 0;
    PR2 = 633;

    OC1CON = 0;
    OC1R = PR2;
    OC1RS = PR2;
    OC1CONbits.OCM = 0b010;
    OC1CONbits.OCFLT = TRUE;
    OC1CONbits.OCTSEL = FALSE;

    //------  UART  -------
    // UART pour la réception MIDI IN et envoi de MIDI THRU
    // BaudRate MIDI = 31250;
    U1BRG = 19;                         // Set Baud rate
    U1STA = 0;
    U1MODE = 0;
    U1STAbits.URXEN = TRUE;
    U1STAbits.UTXEN = TRUE;
    U1MODEbits.ON = TRUE;               // Enable UART for 8-bit data
}

void            init_flag(void)
{
    //----- INTERRUPT -----
    INTCONbits.MVEC = TRUE;             //Multi-vector mode
    INTCONbits.INT1EP = FALLING_EDGE;   //Prend INT1 au front descendant

    //-----   FLAG   -----
    IEC0bits.T2IE = TRUE;               //Autorise interruption timer2
    IFS0bits.T2IF = FALSE;              //Flag à NO (Attend signal pour blink)
    IPC2bits.T2IP = 1;                  //Passe en priorité basse
    IPC2bits.T2IS = 1;                  //Sous-priorité osef'

    IEC0bits.U1RXIE = TRUE;             //Autorise interruption timer2
    IFS0bits.U1RXIF = FALSE;            //Flag à NO (Attend signal pour blink)
    IPC6bits.U1IP = 7;                  //Passe en priorité basse
    IPC6bits.U1IS = 1;                  //Sous-priorité osef'

    IEC0bits.INT1IE = TRUE;             //Autorise interruption bouton
    IFS0bits.INT1IF = FALSE;            //Met le Flag à NO (attend bouton)
    IPC1bits.INT1IP = 2;                //Passe en priorité haute
    IPC1bits.INT1IS = 1;                //Sous-priorité osef'

    asm volatile("ei");                 //Autorise les macro-ASM (interruptions)
}

void            init_state(void)
{
    mode = 0;
    pwm = 0;
    beat = 0xFFFF;
    onde = read_onde_preset();
    cur_period = read_period_preset();
    get_period = (cur_period * 100) / 158;
    get_period = get_period - ((get_period / 100) * 100); // = 55
    magic_period = cur_period / 158;                      // = 7
}

//  On crée un tableau dans lequel on range toutes les périodes
//  correspondantes aux numéros des notes
u32             *tab_create(void)
{
//  script:: tab_period[key_number] = Temps(µs/20);
}
