/* 
 * File:   Process.c
 * Author: jpepin
 *
 * Created on April 11, 2016, 10:59 PM
 */

#include <p32xxxx.h>
#include <sys/attribs.h>
#include "Midi.h"

/*
**  _,-'�'-,_,-'�'-- Initialisation du MIDI --'�'-,_,-'�'-,_
**
**
**      ETAT      |        NOTE         |       VELOCITE
** 1000.... = ON  | 00000000 = C (= MIN)| ????????????????
** 1001.... = OFF | 01000101 = LA (440) | |
**                | 01111111 = G (= MAX)| '-> 00000000 (0 par d�faut)
**
**    MESSAGE_MIDI = 0b1000xxxx 0xxxxxxx 00000000
**                          |       |
**          Pas important <-'       '-> Num�ro de la note
**
**
**      o*o*o*o*o*o REFERENCES o*o*o*o*o*o
**  www.midi.org/images/downloads/midituning.pdf
**    www.pianoweb.fr/outils-messagesmidi.php
** www.microchip.com/wwwproducts/en/PIC32MX340F512H
**
**
**
*/


//Simulation du message MIDI :: LA 440 ON
s32             note_on = 0b100000000100010100000000;

//Simulation du message MIDI :: LA 440 OFF
s32             note_off = 0b100100000100010100000000;

//Gestion du parsing de la note (Bonne note? Bon message?)
s8              get_note = 0;   // Parse la note courante
s8              cur_note = 0;   // Conserve la note courante

//Pour le blink de la led (Simulation du sch�ma d'anowak)
s8              dim;            // Pourcentage d'intensit� actuel
s8              state;          // Curseur pour le blink
s8              led_status;     // Signe de la pente, TRUE = >=0, FALSE = <0.
s8              beat;           // Intensit� max de la led
s32             cur_time;       // Monte jusqu'� want_time => r�gle le temps
s8              want_time = 33; // 33 ~= 1sec (dur�e du mode (atk, decay...))

//Gestion du mode courant => attack | decay | sustain | release
s8              note_mode;        // Indique le mode en cours
s8              key_hold = FALSE; // Indique si la note est toujours enfonc�e


static void      init_bits(void)
{
    //-----  PAD IO  -----
    TRISFbits.TRISF1 = OUTPUT;          //RF1 = Led verte
    LATFbits.LATF1 = GND;               //Etat initial = �teint
    TRISDbits.TRISD8 = INPUT;           //RD8 = Bouton

    //-----  TIMER2  -----
    T2CON = 0;                          //Clear le timer2
    T2CONbits.T32 = TRUE;               //32bits mode ON
    T2CONbits.TCKPS = 0b000;            //timer rescaler = 1;
    T2CONbits.ON = FALSE;               //Attend la pression du bouton
    TMR2 = 0;
    PR2 = 500;                          //Blink tr�s rapide (0,0005 sec)
}

static void      init_flag(void)
{
    //----- INTERRUPT -----
    INTCONbits.MVEC = TRUE;             //Multi-vector mode
    INTCONbits.INT1EP = FALLING_EDGE;   //Prend INT1 au front descendant

    //-----   FLAG   -----
    IEC0bits.T3IE = TRUE;               //Autorise interruption timer2
    IFS0bits.T3IF = FALSE;              //Flag � NO (Attend signal pour blink)
    IPC3bits.T3IP = 1;                  //Passe en priorit� basse
    IPC3bits.T3IS = 1;                  //Sous-priorit� osef'

    IEC0bits.INT1IE = TRUE;             //Autorise interruption bouton
    IFS0bits.INT1IF = FALSE;            //Met le Flag � NO (attend bouton)
    IPC1bits.INT1IP = 2;                //Passe en priorit� haute
    IPC1bits.INT1IS = 1;                //Sous-priorit� osef'

    asm volatile("ei");                 //Autorise les macro-ASM (interruptions)
}


// Initialisation des variables de r�glage
static void     init_state(void)
{
    dim = 0;
    state = 0;
    cur_time = 0;
    beat = 0;
    led_status = TRUE;
}


// R�ception de l'appui de la note
void __ISR(_EXTERNAL_1_VECTOR, IPL2AUTO) note_pressed(void)
{
    if (INTCONbits.INT1EP == FALLING_EDGE && !cur_note)
    {
        get_note = NOTE_ON;             // Stock du message pour le parseur
        cur_note = CURRENT_NOTE;        // Conservation de la note courante
        TMR2 = 0;
        if (!(get_note ^ ON_EVENT)) {   // Parseur de Message "ON"
            init_state();
            note_mode = ATTACK;         // ATTACK_EVENT � l'initialisation
            beat = 60;                  // 60 pour l'exemple
            INTCONbits.INT1EP = RISING_EDGE; // attend le rel�chement du bouton
            T2CONbits.ON = TRUE;        // D�marre le timer2 pour le compute
        }
    }

    //L'id�e c'est qu'il faut rel�cher la seule note jou�e (touches multiples)
    else if (INTCONbits.INT1EP == RISING_EDGE && cur_note == CURRENT_NOTE)
    {
        //On v�rifie si le message est bien pour mettre sur "OFF"
        //<=> On ne g�re que ce signal (et le signal "ON")
        get_note = NOTE_OFF;            // Note OFF
        if (!(get_note ^ OFF_EVENT)) {  // Parseur de Message "OFF"
            cur_note = 0;               // R�init de la note courante
            note_mode = RELEASE;        // Passage en mode release (END_EVENT)
            beat = 100;                 // 100 pour l'exemple
            want_time = 20;             // 20 pour l'exemple
            led_status = FALSE;         // led va vers le mode �teint
            INTCONbits.INT1EP = FALLING_EDGE; // attend le prochain appui
        }
    }

    //----- REINIT DU FLAG -----
    IFS0bits.INT1IF = FALSE;
}


void __ISR(_TIMER_3_VECTOR, IPL1AUTO) led_blink(void)
{
    //-----------  BLINK  ------------
    if (state < dim)
        LATFbits.LATF1 = led_status;
    else if (state < 100)
        LATFbits.LATF1 = !led_status;
    else
        state = -1;

    //-- GESTION DES MODES & COMPUTE --
    state = state + 1;
    cur_time = cur_time + 1;
    if (note_mode != SUSTAIN && cur_time >= want_time)
    {
        // Fait varier l'intensit� de la led
        if (dim < beat)
            dim = dim + 1;

        // DECAY_EVENT quand ATTACK_EVENT est finit
        else if (note_mode == ATTACK)
        {
            led_status = FALSE;
            dim = 0;
            beat = 40;
            want_time = 25;
            note_mode = DECAY;
        }

        // SUSTAIN_EVENT quand DECAY_EVENT est finit
        else if (note_mode == DECAY)
        {
            dim = beat;
            note_mode = SUSTAIN;
        }

        cur_time = 0;
    }

    // END_EVENT quand RELEASE_EVENT est finit
    if (note_mode == RELEASE && dim == beat)
    {
        init_state();
        TMR2 = 0;
        T2CONbits.ON = FALSE;
        LATFbits.LATF1 = FALSE;
    }

    //--- REINIT DU FLAG ---
    IFS0bits.T3IF = FALSE;
}


int             main(void) {

    init_bits();
    init_flag();

    while(PROCESS) {
        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
}
