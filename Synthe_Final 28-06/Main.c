/* 
 * File:   Main.c
 * Author: bocal
 *
 * Created on June 28, 2016, 8:00 PM
 */

#include <stdio.h>
#include <stdlib.h>

/*
 * 
 */
int main(int argc, char** argv) {

    init_pins();
    init_lcd();
    lcd_print("SynthyTwo");
    lcd_goto(1, 2);
    lcd_print("Coming Soon...");
    while (42)
        ;
    return (EXIT_SUCCESS);
}

