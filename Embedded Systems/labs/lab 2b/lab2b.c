#include <xc.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma config JTAGEN = OFF
#pragma config FWDTEN = OFF
#pragma config FNOSC = FRCPLL
#pragma config FSOSCEN = OFF
#pragma config POSCMOD = EC
#pragma config OSCIOFNC = ON
#pragma config FPBDIV = DIV_1
#pragma config FPLLIDIV = DIV_2
#pragma config FPLLMUL = MUL_20
#pragma config FPLLODIV = DIV_1

/*
    Authors: Elazar Fine & Michael Sieradzki
 */

 /*
     LCD VARS:

         DISP_RS 	AN15/RPB15/OCFB/CTED6/PMA0/RB15 	Register Select: High for Data Transfer, Low for Instruction Transfer.
         DISP_RW 	RPD5/PMRD/RD5 	Read/Write signal: High for Read mode, Low for Write mode.
         DISP_EN 	RPD4/PMWR/RD4 	Read/Write Enable: High for Read, falling edge writes data
 */

void set_CGRAM();
void set_DDRAM(const bool);
void busy(void);
void init_lcd();
void print_cg_char_to_lcd(const char *, const bool);
void move_cursor_to_pos(uint32_t);
char *get_first_line_by_switch(); // get text for first line
char *get_second_line_by_switches(); // get text for second line

typedef uint32_t DELAY;

// cycle delay constants
DELAY SHORT_DELAY = 64000 * 2, LONG_DELAY = 64000 * 8,
        SND_SHORT_DELAY = 256, SND_LONG_DELAY = 512;

void $wait(DELAY delay) {
    uint32_t j;
    for (j = 0; j < delay; j++);
}

// beep duration constants
uint16_t SND_DUR_CEIL = 400, SND_DUR_FLOOR = 100, SND_DUR_JUMP = 50;

char CG_chars_choose[] = {0};
uint8_t CG_chars_choose_len = 1;

char CG_symbols[] = {0xA, 0xA, 0xA, 0x0, 0x11, 0x11, 0xE, 0x0};
uint8_t CG_symbols_len = 8;

// used for moving second line left and right by adding spaces before
uint8_t spaces_amount = 0, spaces_add = 1;

void main() {
    TRISA &= 0xff00; // SET lower bits (LEDs) as output (0)
    PORTA = 0; // turn off LEDs

    /**************************************/
    /* CONFIGURE SWITCHES TO ACCEPT INPUT */
    TRISFbits.TRISF3 = 1; // RF3  (SW0) configured as input
    TRISFbits.TRISF3 = 1; // RF3  (SW0) configured as input
    TRISFbits.TRISF5 = 1; // RF5  (SW1) configured as input
    TRISFbits.TRISF4 = 1; // RF4  (SW2) configured as input
    TRISDbits.TRISD15 = 1; // RD15 (SW3) configured as input
    TRISDbits.TRISD14 = 1; // RD14 (SW4) configured as input
    TRISBbits.TRISB11 = 1; // RB11 (SW5) configured as input
    ANSELBbits.ANSB11 = 0; // RB11 (SW5) disabled analog
    TRISBbits.TRISB10 = 1; // RB10 (SW6) configured as input
    ANSELBbits.ANSB10 = 0; // RB10 (SW6) disabled analog
    TRISBbits.TRISB9 = 1; // RB9  (SW7) configured as input
    ANSELBbits.ANSB9 = 0; // RB9  (SW7) disabled analog

    TRISBbits.TRISB14 = 0; // set speaker as output
    ANSELBbits.ANSB14 = 0; // speaker - disabled analog
    /**************************************/
    /********* CONFIGURE LCD TRIS *********/
    TRISBbits.TRISB15 = 0; // RB15 (DISP_RS) set as an output
    ANSELBbits.ANSB15 = 0; // disable analog functionality on RB15 (DISP_RS)
    TRISDbits.TRISD5 = 0; // RD5 (DISP_RW) set as an output
    TRISDbits.TRISD4 = 0; // RD4 (DISP_EN) set as an output
    //TRISEbits.TRISE0 = 1; // RE0 (DB0) set as input (change 1 to 0 for
    TRISE &= 0xff00;
    ANSELEbits.ANSE2 = 0;
    ANSELEbits.ANSE4 = 0;
    ANSELEbits.ANSE5 = 0;
    ANSELEbits.ANSE6 = 0;
    PORTBbits.RB15 = 0; //rs=0
    PORTDbits.RD5 = 0; //w=0
    ANSELEbits.ANSE7 = 0;
    /**************************************/

    DELAY cycle_delay = LONG_DELAY, sound_delay = SND_LONG_DELAY;
    bool run = true, reverse = false;
    uint16_t snd_duration = SND_DUR_CEIL, snd_interval = SND_DUR_JUMP;
    uint8_t x = 1;

    while (1) {
        init_lcd(); // reset LCD

        /* SW1 - CHOOSE LINE */
        print_cg_char_to_lcd(CG_symbols, !PORTFbits.RF5);

        /* SW7 - MAKE BEEP SOUND */
        if (PORTBbits.RB9) {
            uint16_t s;
            for (s = 0; s < snd_duration; s++) {
                PORTBbits.RB14 ^= 1; // bit flip
                $wait(sound_delay);
            }
            if (snd_duration >= SND_DUR_CEIL) snd_interval = -SND_DUR_JUMP;
            else if (snd_duration <= SND_DUR_FLOOR) snd_interval = SND_DUR_JUMP;
            snd_duration += snd_interval;
        }

        $wait(cycle_delay);
    }
}

void set_CGRAM() {
    PORTBbits.RB15 = 0; //rs=0
    PORTDbits.RD5 = 0; //w=0
    PORTE = 0x40;
    PORTDbits.RD4 = 1;
    PORTDbits.RD4 = 0;
    busy();
    PORTBbits.RB15 = 1; //rs
}

void set_DDRAM(const bool is_second_line) {
    PORTBbits.RB15 = 0; //rs control 
    PORTE = 0x80; //DDRAM
    if (is_second_line) move_cursor_to_pos(0xc0); // move cursor to second line
    PORTDbits.RD4 = 1; //enable=1
    PORTDbits.RD4 = 0; //enable=0
    busy();
    PORTBbits.RB15 = 1; //rs 
}

void print_cg_char_to_lcd(const char *chr, const bool is_second_line) {
    set_CGRAM(); // set to CGRAM mode to load symbols
    uint8_t i;

    // load the symbols into CGRAM
    for (i = 0; i < CG_symbols_len; i++) {
        PORTE = chr[i];
        PORTDbits.RD4 = 1; // give pulse to apply PORTE change (enable)
        PORTDbits.RD4 = 0; // give pulse to apply PORTE change (enable)
        busy();
    }

    set_DDRAM(is_second_line); // set to DDRAM mode to write to LCD

    // move line left and right by adding spaces before the string
    for (i = 0; i < spaces_amount; i++) {
        PORTE = ' ';
        PORTDbits.RD4 = 1; // give pulse to apply PORTE change (enable)
        PORTDbits.RD4 = 0; // give pulse to apply PORTE change (enable)
        busy();
    }
    if (PORTFbits.RF3) {
        if (spaces_amount >= 15) {
            spaces_add = -1;
        } else if (spaces_amount <= 0) {
            spaces_add = 1;
        }
        spaces_amount += spaces_add;
    }

    // print the symbols that are in CGRAM
    for (i = 0; i < CG_chars_choose_len; i++) {
        PORTE = CG_chars_choose[i];
        PORTDbits.RD4 = 1; //enable=1
        PORTDbits.RD4 = 0; //enable=0
        busy();
    }
}

void init_lcd() {
    PORTBbits.RB15 = 0; // rs -> 0
    PORTDbits.RD5 = 0; //w=0
    // instructions for the LCD controller
    char _control[] = {0x38, 0x38, 0x38, 0xe, 0x6, 0x1, 0x01};
    uint8_t i;
    for (i = 0; i < (sizeof (_control) / sizeof (_control[0])); i++) {
        PORTE = _control[i];
        PORTDbits.RD4 = 1; // give pulse to apply PORTE change (enable)
        PORTDbits.RD4 = 0; // give pulse to apply PORTE change (enable)
        busy();
    }
    PORTBbits.RB15 = 1; // rs -> 1
    PORTDbits.RD5 = 0; // write = 0, read = 1
}

void move_cursor_to_pos(uint32_t pos) {
    PORTBbits.RB15 = 0; //rs=1 
    PORTE = pos; //DDRAM
    PORTDbits.RD4 = 1; //enable=1
    PORTDbits.RD4 = 0; //enable=0
}

void busy(void) {
    char RD, RS;
    int STATUS_TRISE;
    int portMap;
    RD = PORTDbits.RD5;
    RS = PORTBbits.RB15;
    STATUS_TRISE = TRISE;
    PORTDbits.RD5 = 1; //w/r
    PORTBbits.RB15 = 0; //rs 
    portMap = TRISE;
    portMap |= 0x80;
    TRISE = portMap;
    do {
        PORTDbits.RD4 = 1; //enable=1
        PORTDbits.RD4 = 0; //enable=0
    } while (PORTEbits.RE7); // BF ?????
    PORTDbits.RD5 = RD;
    PORTBbits.RB15 = RS;
    TRISE = STATUS_TRISE;
}
