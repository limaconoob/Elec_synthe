/* 
 * File:   MainSWAG.c
 * Author: jpepin
 *
 * Created on March 22, 2016, 5:54 PM
 */
#include <P32XXXX.h>
#include "TypesSWAG.h"
/*
 * 
 */

static void    init_bits(void)
{
    TRISFbits.TRISF1 = OUTPUT; /* RF1 = Led verte */
    LATFbits.LATF1 = GND; /* Etat initial = éteint */
    TRISDbits.TRISD8 = INPUT; /* RD8 = Bouton poussoir */

    TRISCbits.TRISC12 = INPUT;

    T2CON = 0b1000000000111000;
    PR2 = 0b0000011111010000;
    TMR2 = 0;
}

int             main(void)
{
    // INIT
    // Initialisation des bits
    init_bits();

    // Initialisation des variables
    // s8 led_status = TRUE;
    s8 status;
    s8 prev_status = FALSE;

    // PROCESS
    while (PROCESS) {
        status = PORTDbits.RD8;

        // La led clignote 1.On.sec && 1.Off.sec (=> 0.5Hz)
        // Si on appuie sur le bouton, la fréquence change (=> Freq*2)
        if (status == FALSE && prev_status == TRUE) {
            // La fréquence est multipliée par 2 à chaque appui.
            // (=> Le temps max PR2 de la clock est réduit)
            if (PR2 > 0b0000000001111101)
                PR2 = PR2 >> 1;
            // Si la fréquence atteint 8Hz, elle est réinit à 0.5Hz
            else
                PR2 = PR2 << 4;
            // Le Timer est réinit car s'il est supérieur à
            // PR2, le Timer est perdu dans le Nether
            TMR2 = 0;
        }
        prev_status = status;

        // PR2 = Temps total (=> PR2/2 = Moitié du temps (Clignotement))
        if (TMR2 < PR2 / 2)
            LATFbits.LATF1 = TRUE;
        else
            LATFbits.LATF1 = FALSE;

        // Si on appuie sur le bouton, la led change de status
        // jusqu'au prochain appui.
 /*       if (status == FALSE && prev_status == TRUE) {
            led_status = !led_status;
        }
        prev_status = status;

        LATFbits.LATF1 = led_status;*/
    }
    return (0);
}
