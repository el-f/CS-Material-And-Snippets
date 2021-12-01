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

void busy(void);
void init_lcd();
void print_to_lcd(const bool, const char *);
void move_cursor_to_pos(uint32_t);
char *get_first_line_by_switch(); // get text for first line
char *get_second_line_by_switches(); // get text for second line

typedef uint32_t DELAY;

// cycle delay constants
DELAY SHORT_DELAY = 64000 * 3, LONG_DELAY = 64000 * 8,
        SND_SHORT_DELAY = 256, SND_LONG_DELAY = 512;

void $wait(DELAY delay) {
    uint32_t j;
    for (j = 0; j < delay; j++);
}

// beep duration constants
uint16_t SND_DUR_CEIL = 400, SND_DUR_FLOOR = 100, SND_DUR_JUMP = 50;

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
    uint8_t menifa_nums[] = {0x18, 0x24, 0x42, 0x81}, m_idx = 0;
    uint8_t shift_nums[] = {1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80}, s_idx = 0;
    uint8_t x = 1;

    while (1) {
        init_lcd(); // reset LCD
        print_to_lcd(false, get_first_line_by_switch()); // print to first line
        move_cursor_to_pos(0xc0); // move cursor to second line
        print_to_lcd(true, get_second_line_by_switches()); // print to second line

        /* SW7 - EXIT PROGRAM */
        if (PORTBbits.RB9) {
            PORTA = 0;
            return;
        }

        /* SW6 - MAKE BEEP SOUND */
        if (PORTBbits.RB10) {
            uint16_t s;
            for (s = 0; s < snd_duration; s++) {
                PORTBbits.RB14 ^= 1; // bit flip
                $wait(sound_delay);
            }
            if (snd_duration >= SND_DUR_CEIL) snd_interval = -SND_DUR_JUMP;
            else if (snd_duration <= SND_DUR_FLOOR) snd_interval = SND_DUR_JUMP;
            snd_duration += snd_interval;
        }

        /* SW5 - STOP LED MOVEMENT */
        run = !PORTBbits.RB11;

        /* SW4 - CHANGE SPEED */
        cycle_delay = PORTDbits.RD14 ? SHORT_DELAY : LONG_DELAY;
        sound_delay = PORTDbits.RD14 ? SND_SHORT_DELAY : SND_LONG_DELAY;

        /* SW3 - CHANGE DIRECTION */
        reverse = PORTDbits.RD15;

        if (run) {
            /* CHOOSE AND DO CHOSEN OPERATION */
            if (PORTFbits.RF4) { // SW2 - `MENIFA`
                PORTA = menifa_nums[m_idx % 4];
                reverse ? m_idx-- : m_idx++;
            } else if (PORTFbits.RF5) { // SW1 - SHIFT
                PORTA = shift_nums[s_idx % 8];
                reverse ? s_idx-- : s_idx++;
            } else if (PORTFbits.RF3) { // SW0 - BINARY COUNTER
                PORTA = reverse ? x-- : x++;
            }
        }

        $wait(cycle_delay);
    }
}

char *get_first_line_by_switch() {
    if (PORTBbits.RB9)  return "Mode 7:";
    if (PORTBbits.RB10) return "Mode 6:";
    if (PORTBbits.RB11) return "Mode 5:";
    if (PORTFbits.RF4)  return "Mode 2:";
    if (PORTFbits.RF5)  return "Mode 1:";
    if (PORTFbits.RF3)  return "Mode 0:";
    return "No Mode Selected";
}

char *get_second_line_by_switches() {
    if (PORTBbits.RB9)  return "Exit";
    if (PORTBbits.RB10) return "Beep Mode";
    if (PORTBbits.RB11) return "Halt";

    bool fast = PORTDbits.RD14;
    bool reversed = PORTDbits.RD15;

    if (PORTFbits.RF4) { // menifa
        if (!fast && !reversed) return "SwingUpSlow";
        if (!fast && reversed)  return "SwingDownSlow";
        if (fast && !reversed)  return "SwingUpFast";
        return "SwingDownFast";
    }
    if (PORTFbits.RF5) { // shift
        if (!fast && !reversed) return "ShiftLeftSlow";
        if (!fast && reversed)  return "ShiftRightSlow";
        if (fast && !reversed)  return "ShiftLeftFast";
        return "ShiftRightFast";
    }
    if (PORTFbits.RF3) { // counter
        if (!fast && !reversed) return "CounterUpSlow";
        if (!fast && reversed)  return "CounterDownSlow";
        if (fast && !reversed)  return "CounterUpFast";
        return "CounterDownFast";
    }
    return "";
}

void print_to_lcd(const bool move_str, const char *str) {
    PORTBbits.RB15 = 1; // rs -> 1
    PORTDbits.RD5 = 0; // write = 0, read = 1

    busy(); // delay lcd

    uint8_t str_len = strlen(str), i;
    
    // move second line left and right by adding spaces before the string
    if (move_str && str_len > 0) { 
        for (i = 0; i < spaces_amount; i++) {
            PORTE = ' ';
            PORTDbits.RD4 = 1; // give pulse to apply PORTE change (enable)
            PORTDbits.RD4 = 0; // give pulse to apply PORTE change (enable)
            busy();
        }
        if (spaces_amount >= 16 - str_len) {    // text reached right end of line
            spaces_add = -1;
        } else if (spaces_amount <= 0) {        // text reached left end of line
            spaces_add = 1;
        }
        spaces_amount += spaces_add;
    }
    
    // print the string
    for (i = 0; i < str_len; i++) {
        PORTE = str[i];
        PORTDbits.RD4 = 1; // give pulse to apply PORTE change (enable)
        PORTDbits.RD4 = 0; // give pulse to apply PORTE change (enable)
        busy();
    }
}

void init_lcd() {
    PORTBbits.RB15 = 0; // rs -> 0
    PORTDbits.RD5 = 0; //w=0
    
    // instructions for the LCD controller
    char control[] = {0x38, 0x38, 0x38, 0xe, 0x6, 0x1, 0x01};
    uint8_t i;
    for (i = 0; i < (sizeof (control) / sizeof (control[0])); i++) {
        PORTE = control[i];
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

// the smart way to delay on lcd
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
