#include <p32xxxx.h>
#include <sys/attribs.h>

# define PROCESS 42
# define TRUE 1
# define FALSE 0
# define INPUT 1
# define OUTPUT 0
# define VCC 1
# define GND 0

# define MONTANT    0
# define DESCENDANT 1

# define CARRE      1
# define TRIANGLE   2
# define SAWTOOTH   3
# define SINUSOID   4

typedef unsigned    char u8;
typedef unsigned    short u16;
typedef unsigned    long u32;
typedef signed      char s8;
typedef signed      short s16;
typedef signed      long s32;

# define TRIS_RS TRISBbits.TRISB10
# define TRIS_E TRISBbits.TRISB11
# define TRIS_DB4 TRISBbits.TRISB12
# define TRIS_DB5 TRISBbits.TRISB13
# define TRIS_DB6 TRISBbits.TRISB14
# define TRIS_DB7 TRISBbits.TRISB15
# define _RS LATBbits.LATB10
# define _E LATBbits.LATB11
# define _DB4 LATBbits.LATB12
# define _DB5 LATBbits.LATB13
# define _DB6 LATBbits.LATB14
# define _DB7 LATBbits.LATB15


# define TRIS_A0 TRISDbits.TRISD0
# define TRIS_A1 TRISDbits.TRISD1
# define _A0 LATDbits.LATD0
# define _A1 LATDbits.LATD1


static void      waitXticks(u32 x)
{
    u32 i = 0;
    while (i < x)
        i++;
    return;
}

static void      lcd_pulse(void)
{
    _E = 0;
    waitXticks(1);
    _E = 1;
    waitXticks(100);        //enable pulse lasts 100us
    _E = 0;
    waitXticks(10);        //wait 20us for enable to settle down
    return;
}

static void      write4bits(u8 value)
{
    _DB4 = (value & 0x01);
    _DB5 = ((value >> 1) & 0x01);
    _DB6 = ((value >> 2) & 0x01);
    _DB7 = ((value >> 3) & 0x01);
    lcd_pulse();
    return;
}


static void      lcd_command(u8 value, u8 rs)
{
    if (rs)                  //set RS to write or read
        _RS = 1;
    else
        _RS = 0;

    write4bits(value >> 4);
    write4bits(value);

    return;
}


static void      lcd_printnbr(u16 value)
{
    if (value >= 10)
        lcd_printnbr(value / 10);
    lcd_command((value % 10) + '0', 1);
    return;
}


static void      lcd_print(char *str)
{
    int x = 0;

    while (str[x])
    {
        lcd_command(str[x], 1);
        x++;
    }
    return;
}


static void      lcd_goto(u8 col, u8 line)
{
    u8 x;
    if (line == 1)
        x = 0b10000000;
    else if (line == 2)
        x = 0b11000000;
    else
        return;
    if (col >= 1 && col <= 16)
    {
        x |= col - 1;
        lcd_command(x, 0);
    }
}

static void      init_interrupt(void)
{
    //----- INTERRUPT -----
    INTCONbits.MVEC = TRUE;           //Multi-vector mode

    //-----   FLAG   -----
    IFS0bits.U1RXIF = FALSE;
    IPC6bits.U1IP = 7;                //Priorité maximale
    IPC6bits.U1IS = 1;
    IEC0bits.U1RXIE = TRUE;           //Enable UART1 Reception interrupt

    IEC0bits.T2IE = TRUE;
    IFS0bits.T2IF = FALSE;
    IPC2bits.T2IP = 1;                //Priorité basse
    IPC2bits.T2IS = 1;

    asm volatile("ei");               //Autorise les macro-ASM (interruptions)
}

static void         init_uart(void)
{
    //------  UART  -------
    // UART pour la réception MIDI IN et envoi de MIDI THRU
    // BaudRate MIDI = 31250;
    U1STA = 0;
    U1MODE = 0;
    U1RXREG = 0;
    U1BRG = 159;                         // Set Baud rate
    U1STAbits.URXISEL = 0b10;
    U1STAbits.URXEN = 1;
    U1MODEbits.ON = TRUE;               // Enable UART for 8-bit data
}

static void         init_oscil(void)
{
    T2CON = 0;
    TMR2 = 0;
    PR2 = 767;
//    PR2 = 48;
    T2CONbits.ON = TRUE;
}

static void         init_dac()
{
    OC5CON = 0;
    OC5CONbits.OCM = 0b011;             //OC3 sur front descendant
    OC5CONbits.OCTSEL = 0;              //Tmr2
    OC5R = 420;
    OC5CONbits.ON = 1;
    //SysClock generator - 80Mhz / 6
/*    IEC0bits.T3IE = TRUE;
    IFS0bits.T3IF = FALSE;
    IPC3bits.T3IP = 1;                //Priorité basse
    IPC3bits.T3IS = 1;
*/    T3CON = 0;
    TMR3 = 0;
    PR3 = 5;
    OC4CON = 0;
    OC4CONbits.OCM = 0b011;             //OC3 sur front descendant
    OC4CONbits.OCTSEL = 1;              //Tmr3
    OC4R = 5;
    OC4CONbits.ON = 1;
    T3CONbits.ON = 1;

    IFS1bits.SPI2TXIF = FALSE;
    IPC7bits.SPI2IP =  3;
    IPC7bits.SPI2IS =  1;
    IEC1bits.SPI2TXIE = TRUE;

    SPI2CON = 0;
    SPI2BUF = 0;
    SPI2BRG = 23;
    SPI2CONbits.FRMEN = 0;              //NON Framed mode (generation de clock ininterompue)
    SPI2CONbits.FRMSYNC = 0;            //Frame master
   // = 1;              //NON Framed mode (generation de clock ininterompue)

    SPI2STATbits.SPIROV = 0;
//    SPI2CONbits = ;
    SPI2CONbits.MSTEN = 1;              //Set SPI2 as Master
    SPI2CONbits.MODE16 = 1;             //16bit messages to transmit
    SPI2CONbits.MODE32 = 0;
    SPI2CONbits.CKE = 0;
    SPI2CONbits.ON = 1;
}

static void      init_lcd(void)
{
    //-----  PAD IO  ----
    TRIS_RS = OUTPUT;          //RS is output
    TRIS_E = OUTPUT;           //E is output
    TRIS_DB4 = OUTPUT;         //DB4 is output
    TRIS_DB5 = OUTPUT;         //DB5 is output
    TRIS_DB6 = OUTPUT;         //DB6 is output
    TRIS_DB7 = OUTPUT;         //DB7 is output

    _RS = 0;
    _E = 0;
    _DB4 = 0;
    _DB5 = 0;
    _DB6 = 0;
    _DB7 = 0;

    waitXticks(3000);         //Wait 3s for LCD to power up to 5V
    write4bits(0b0010);          //Set 4 bit mode
    waitXticks(1000);
    lcd_command(0b00101000, 0);  //Set 4bit mode, 2line display, 5*8 char
    waitXticks(1000);
    lcd_command(0b00000110, 0);  //Set DDRam incrementation, Display Shift OFF
    waitXticks(1000);
    lcd_command(0b00000001, 0);  //Clear display
    waitXticks(5000);
    lcd_command(0b00001100, 0);  //Set Diplay ON, Cursor OFF, Blinking OFF
    waitXticks(1000);

    return;
}

// ---------------------------------V  CECI EST IMPORTANT  V-------------------
u16         value = 1;       // VALUE EST LA TENSION (0 à FFFF) QUI VA AU DAC !
u8          onde = CARRE;    // Forme de l'onde (change à l'appui du bouton)
u32         tab[88];         // Tableau contenant toutes les périodes
u16         cursor = 1000;   // Donne la cadence d'augmentation de la tension

static void            onde_carre(void)
{
    static u16  pwm = 0x0000;      // Compteur basique (pour onde Carré)
    static u8   mode = 0;          // Donne le sens d'évolution de la tension

    if (mode == MONTANT) {
        if (pwm < 0x7FFF - cursor) {    // Incrémente un compteur
            pwm += cursor;              // jusqu'à beat
        }
        else {                          // Quand le compteur arrive à beat
            mode = DESCENDANT;          // on inverse la tension courante
            value = 0x8000;
            pwm = 0x8000;
        }
    }
    else if (mode == DESCENDANT) {
        if (pwm < 0xFFFF - cursor) {    // Incrémente un compteur
            pwm += cursor;              // jusqu'à beat
        }
        else {                          // Quand le compteur arrive à beat
            mode = MONTANT;             // on inverse la tension courante
            value = 0x7FFF;
            pwm = 0x0000;
        }
    }
}

static void         onde_triangle(void)
{
    static u8   mode = 0;
    u16         adj;    // Sert à ajuster la valeur pour garder la bonne fréquence

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

static void         onde_sawtooth(void)
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

/*
void __ISR(_TIMER_3_VECTOR, IPL1AUTO) dac_sysclk(void)
{
    LATDbits.LATD3 = 1;
    IFS0bits.T3IF = FALSE;
}
*/

void __ISR(_TIMER_2_VECTOR, IPL1AUTO) Freq(void)
{
//    oscillator();
//    onde_carre();
//    onde_triangle();
    onde_sawtooth();

    IFS0bits.T2IF = FALSE;
}

//-------------V  SPI  V-------------------------------------------------------
void __ISR(_SPI_2_VECTOR, IPL3AUTO) Go_spi(void)
{
 //   if (!PORTDbits.RD4)
        SPI2BUF = value;
 //  else
 //       SPI2BUF = 0x89;
    IFS1bits.SPI2TXIF = FALSE;
    //IFS1bits.SPI2RXIF = FALSE;
}

u8  midi_buffer[200];
u8  midi_byte_wr = 0;
u8  midi_byte_rd = 0;

void __ISR(_UART_1_VECTOR, IPL7SOFT) ft_uart(void)
{
    while (U1STAbits.URXDA)
    {
        midi_buffer[midi_byte_wr++] = U1RXREG;  // U1RXREG est le buffer de réception UART
        if (midi_byte_wr >= 200)
            midi_byte_wr = 0;
    }

    IFS0bits.U1RXIF = FALSE;
}

static void         parseur_on_off(u8 message_midi)
{
    lcd_goto(6, 2);
    if ((message_midi >> 4) ^ 0b1000 == 0xFFFF)
        lcd_print("ON  ");
    else if ((message_midi >> 4) ^ 0b1001 == 0xFFFF)
        lcd_print("OFF ");
    else
        lcd_print("    ");
}

static void         print_onde(void)
{
    lcd_goto(7, 1);
    value = 0;
    if (onde == CARRE)
        lcd_print("CARRE   ");
    else if (onde == SAWTOOTH)
        lcd_print("SAWTOOTH");
    else if (onde == TRIANGLE)
        lcd_print("TRIANGLE");
}

void				tab_create(u32 *tab_period)
{
	tab_period[87] = 1194;
	tab_period[86] = 1265;
	tab_period[85] = 1341;
	tab_period[84] = 1420;
	tab_period[83] = 1505;
	tab_period[82] = 1594;
	tab_period[81] = 1689;
	tab_period[80] = 1790;
	tab_period[79] = 1896;
	tab_period[78] = 2009;
	tab_period[77] = 2128;
	tab_period[76] = 2255;
	tab_period[75] = 2389;
	tab_period[74] = 2531;
	tab_period[73] = 2681;
	tab_period[72] = 2841;
	tab_period[71] = 3010;
	tab_period[70] = 3189;
	tab_period[69] = 3379;
	tab_period[68] = 3579;
	tab_period[67] = 3792;
	tab_period[66] = 4018;
	tab_period[65] = 4257;
	tab_period[64] = 4510;
	tab_period[63] = 4778;
	tab_period[62] = 5062;
	tab_period[61] = 5363;
	tab_period[60] = 5682;
	tab_period[59] = 6020;
	tab_period[58] = 6378;
	tab_period[57] = 6757;
	tab_period[56] = 7159;
	tab_period[55] = 7584;
	tab_period[54] = 8035;
	tab_period[53] = 8513;
	tab_period[52] = 9019;
	tab_period[51] = 9556;
	tab_period[50] = 10124;
	tab_period[49] = 10726;
	tab_period[48] = 11364;
	tab_period[47] = 12039;
	tab_period[46] = 12755;
	tab_period[45] = 13514;
	tab_period[44] = 14317;
	tab_period[43] = 15167;
	tab_period[42] = 16071;
	tab_period[41] = 17026;
	tab_period[40] = 18039;
	tab_period[39] = 19111;
	tab_period[38] = 20248;
	tab_period[37] = 21452;
	tab_period[36] = 22727;
	tab_period[35] = 24079;
	tab_period[34] = 25510;
	tab_period[33] = 27027;
	tab_period[32] = 28635;
	tab_period[31] = 30337;
	tab_period[30] = 32141;
	tab_period[29] = 34053;
	tab_period[28] = 36077;
	tab_period[27] = 38223;
	tab_period[26] = 40495;
	tab_period[25] = 42903;
	tab_period[24] = 45455;
	tab_period[23] = 48157;
	tab_period[22] = 51021;
	tab_period[21] = 54055;
	tab_period[20] = 57269;
	tab_period[19] = 60675;
	tab_period[18] = 64282;
	tab_period[17] = 68105;
	tab_period[16] = 72155;
	tab_period[15] = 76445;
	tab_period[14] = 80991;
	tab_period[13] = 85807;
	tab_period[12] = 90909;
	tab_period[11] = 96315;
	tab_period[10] = 102042;
	tab_period[9] = 108110;
	tab_period[8] = 114538;
	tab_period[7] = 121349;
	tab_period[6] = 128565;
	tab_period[5] = 136210;
	tab_period[4] = 144309;
	tab_period[3] = 152890;
	tab_period[2] = 161982;
	tab_period[1] = 171613;
	tab_period[0] = 181818;
}


int             main(void) {
    u8          status;
    u8          prev_status;

    TRISFbits.TRISF1 = OUTPUT;              //RF1 = Led verte
    LATFbits.LATF1 = GND;                   //Etat initial = éteint
    TRISDbits.TRISD8 = INPUT;               //Bouton pour changer de fréquence

    init_lcd();
    lcd_goto(1, 1);
    lcd_print("SPI: ");
    lcd_goto(1, 2);
    lcd_print("OSC: ");
    init_dac();
    init_interrupt();
    init_oscil();
    init_uart();

    SPI2BUF = 0xFFFF;                         //Start SPI2

    tab_create(tab);                        // Remplit le tableau avec les périodes
    cursor = 1000;                          // Détermine la période
   // cursor = 0;


    while(PROCESS)
    {
        status = PORTDbits.RD8;
        if (!status && prev_status)
        {                                   // Appuyer sur le bouton change la fréquence
            if (cursor == 100)
                cursor = 10000;
            else
                cursor /= 10;
            print_onde();
        }
        prev_status = status;

        while (midi_byte_rd < midi_byte_wr)
        {
            lcd_printnbr(midi_buffer[midi_byte_rd]);
            if (midi_byte_rd >= 200)
                midi_byte_rd = 0;
//            if (midi_byte_rd == 0 || (midi_byte_rd > 2 && midi_byte_rd % 3 == 0))
//                parseur_on_off(midi_buffer[midi_byte_rd]);
//            else if (midi_byte_rd == 1 || midi_byte_rd % 3 == 1)
//                cursor = 0xFFFF / (tab[midi_buffer[midi_byte_rd]] / 208);
            lcd_print(" ");
            midi_byte_rd++;
        }
        waitXticks(3000);
        lcd_goto(7, 1);
        lcd_print("                ");
        lcd_goto(7, 1);

        WDTCONbits.WDTCLR = TRUE;       //Clear Watchdog
    }
}

                // -----V  CECI EST IMPORTANT  V-------------------------------
                // Si le message lu est la note :
                // cursor déterminera la vitesse à laquelle la tension va
                // augmenter de 0x0 à 0xFFFF et vicevs (c'est à dire la période)
                // Soit : 48kHz (imposé) => 1 sample toutes les 20,8 µs
                // Donc : 1 demi-période = tab[note](µs/20) / 208
                // '-> D'où, comme on varie de 0x0 à 0xFFFF :
                // On divise 0xFFFF par le temps d'une demi-période.

// Rendu théorique :
// ,-------------------,
// | Midi: 145 48 125  |   => (Infos provenant du Midi)
// | Tension: 15000    |   => (Info à envoyer au DAC (entre 0 et 65535))
// '-------------------'
