#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include <string.h>
#include <stdbool.h>

#pragma config JTAGEN = OFF     
#pragma config FWDTEN = OFF
#pragma config FNOSC =	FRCPLL
#pragma config FSOSCEN =	OFF
#pragma config POSCMOD =	EC
#pragma config OSCIOFNC =	ON
#pragma config FPBDIV =     DIV_1
#pragma config FPLLIDIV =	DIV_2
#pragma config FPLLMUL =	MUL_20
#pragma config FPLLODIV =	DIV_1

/*
    Authors: Elazar Fine & Michael Sieradzki
 */

/*
    LCD VARS:
        DISP_RS 	AN15/RPB15/OCFB/CTED6/PMA0/RB15 	Register Select: High for Data Transfer, Low for Instruction Transfer.
        DISP_RW 	RPD5/PMRD/RD5 	Read/Write signal: High for Read mode, Low for Write mode.
        DISP_EN 	RPD4/PMWR/RD4 	Read/Write Enable: High for Read, falling edge writes data
 */

typedef uint32_t DELAY;
uint8_t get_pressed();
void lab2_main(
        DELAY* cycle_delay,
        DELAY* sound_delay,
        uint16_t* snd_duration,
        uint16_t* snd_interval,
        uint8_t* m_idx,
        uint8_t* s_idx,
        uint8_t* x,
        bool* reverse
        );
void busy(void);
void init_lcd();
void print_to_lcd(const bool, const char *);
void move_cursor_to_pos(uint32_t);
char *get_first_line_by_switch(); // get text for first line
char *get_second_line_by_switches(); // get text for second line
void update_switches_by_keyboard(uint8_t xy);

// cycle delay constants
DELAY SHORT_DELAY = 64000 * 3, LONG_DELAY = 64000 * 8,
        SND_SHORT_DELAY = 256, SND_LONG_DELAY = 512;

// beep duration constants
uint16_t SND_DUR_CEIL = 400, SND_DUR_FLOOR = 100, SND_DUR_JUMP = 50;

void $wait(DELAY delay) {
    uint32_t j;
    for (j = 0; j < delay; j++);
}

bool switches[] = {false, false, false, false, false, false, false, false};

// instructions for the LCD controller
char _control[] = {0x38, 0x38, 0x38, 0xe, 0x6, 0x1, 0x1};

// used for moving second line left and right by adding spaces before
uint8_t spaces_amount = 0, spaces_add = 1;
uint8_t menifa_nums[] = {0x18, 0x24, 0x42, 0x81};
uint8_t shift_nums[] = {1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80};

void main(void) {
    TRISA &= 0xff00; // SET lower bits (LEDs) as output (0)
    PORTA = 0; // turn off LEDs

    TRISBbits.TRISB15 = 0; // RB15 (DISP_RS) set as an output
    ANSELBbits.ANSB15 = 0; // disable analog functionality on RB15 (DISP_RS)
    TRISDbits.TRISD5 = 0; // RD5 (DISP_RW) set as an output
    TRISDbits.TRISD4 = 0; // RD4 (DISP_EN) set as an output
    TRISE &= 0xff00;
    ANSELEbits.ANSE2 = 0;
    ANSELEbits.ANSE4 = 0;
    ANSELEbits.ANSE5 = 0;
    ANSELEbits.ANSE6 = 0;
    ANSELEbits.ANSE7 = 0;

    TRISCbits.TRISC2 = 0; //RC2
    TRISCbits.TRISC1 = 0; //RC1
    TRISCbits.TRISC4 = 0; //RC4            
    TRISGbits.TRISG6 = 0; //RG6
    ANSELGbits.ANSG6 = 0; //??
    TRISCbits.TRISC3 = 1; //RC3
    CNPUCbits.CNPUC3; //???????              
    TRISGbits.TRISG7 = 1; //RG7
    ANSELGbits.ANSG7 = 0;
    CNPUGbits.CNPUG7;
    TRISGbits.TRISG8 = 1; //RG8
    ANSELGbits.ANSG8 = 0; //???????
    CNPUGbits.CNPUG8; //?????
    TRISGbits.TRISG9 = 1; //RG9
    ANSELGbits.ANSG9 = 0; //???????
    CNPUGbits.CNPUG9; //????? 

    TRISBbits.TRISB14 = 0; // configured as output 
    ANSELBbits.ANSB14 = 0; // disabled analog

    uint8_t xy;
    DELAY cycle_delay = LONG_DELAY, sound_delay = SND_LONG_DELAY;
    uint16_t snd_duration = SND_DUR_CEIL, snd_interval = SND_DUR_JUMP;
    uint8_t m_idx = 0, s_idx = 0, x = 1;
    bool reverse = false;

    //    execution();

    while (1) {
        uint32_t get_input_counter = 0;
        for (get_input_counter = 0; get_input_counter < 2500; get_input_counter++) {
            PORTCbits.RC2 = 1; // x1
            PORTCbits.RC1 = 1; // x2
            PORTCbits.RC4 = 1; // x3
            PORTGbits.RG6 = 1; // x4

            // check first row (x1) - turn off row and check all columns
            PORTCbits.RC2 = 0;
            xy = get_pressed();
            if (xy != 0xff)
                break;
            PORTCbits.RC2 = 1;

            // check second row (x2) - turn off row and check all columns
            PORTCbits.RC1 = 0;
            xy = get_pressed();
            if (xy != 0xff)
                break;
            PORTCbits.RC1 = 1;

            // check third row (x3) - turn off row and check all columns
            PORTCbits.RC4 = 0;
            xy = get_pressed();
            if (xy != 0xff)
                break;
            PORTCbits.RC4 = 1;

            // check fourth row (x4) - turn off row and check all columns
            PORTGbits.RG6 = 0;
            xy = get_pressed();
            if (xy != 0xff)
                break;
            PORTGbits.RG6 = 1;

        }

        update_switches_by_keyboard(xy);
        lab2_main(
                &cycle_delay,
                &sound_delay,
                &snd_duration,
                &snd_interval,
                &m_idx,
                &s_idx,
                &x,
                &reverse
                );
        busy();
    }
}

void update_switches_by_keyboard(uint8_t xy) {
    switch (xy) {
        case 0:
            switches[0] = true;
            switches[1] = false;
            switches[2] = false;
            break;
        case 1:
            switches[0] = false;
            switches[1] = true;
            switches[2] = false;
            break;
        case 2:
            switches[0] = false;
            switches[1] = false;
            switches[2] = true;
            break;
        case 3:
            switches[xy] ^= true;
            break;
        case 4:
            switches[xy] ^= true;
            break;
        case 5:
            switches[xy] ^= true;
            break;
        case 6:
            switches[xy] ^= true;
            break;
        case 7:
            switches[xy] = true;
            break;
        default:
            break;
    }
}

uint8_t get_pressed() {
    uint8_t pressed = 0xff;
    if      (!PORTCbits.RC3 && !PORTGbits.RG6) pressed = 0; //0
    else if (!PORTGbits.RG9 && !PORTGbits.RG6) pressed = 1; //1 
    else if (!PORTGbits.RG9 && !PORTCbits.RC4) pressed = 2; //2 
    else if (!PORTGbits.RG9 && !PORTCbits.RC1) pressed = 3; //3 
    else if (!PORTGbits.RG8 && !PORTGbits.RG6) pressed = 4; //4
    else if (!PORTGbits.RG8 && !PORTCbits.RC4) pressed = 5; //5
    else if (!PORTGbits.RG8 && !PORTCbits.RC1) pressed = 6; //6
    else if (!PORTGbits.RG7 && !PORTGbits.RG6) pressed = 7; //7
    //    else if (!PORTGbits.RG7 && !PORTCbits.RC1) pressed = 8; //8 
    //    else if (!PORTGbits.RG7 && !PORTCbits.RC4) pressed = 9; //9 
    //    else if (!PORTCbits.RC2 && !PORTGbits.RG9) pressed = 10; //a 
    //    else if (!PORTCbits.RC2 && !PORTGbits.RG8) pressed = 11; //b 
    //    else if (!PORTGbits.RG7 && !PORTCbits.RC2) pressed = 12; //c 
    //    else if (!PORTCbits.RC2 && !PORTCbits.RC3) pressed = 13; //d 
    //    else if (!PORTCbits.RC3 && !PORTCbits.RC4) pressed = 14; //e     
    //    else if (!PORTCbits.RC3 && !PORTCbits.RC1) pressed = 15; //f

    return pressed;
}

void print_to_lcd(const bool second_line, const char *str) {
    PORTBbits.RB15 = 1; // rs: Register Select: 1: Data, 0: Instructions.
    PORTDbits.RD5 = 0; // RW: write = 0, read = 1

    busy(); // delay

    uint8_t str_len = strlen(str), i;

    // move second line left and right by adding spaces before the string
    if (second_line && str_len > 0) {
        for (i = 0; i < spaces_amount; i++) {
            PORTE = ' ';
            PORTDbits.RD4 = 1; // give pulse to apply PORTE change (enable)
            PORTDbits.RD4 = 0; // give pulse to apply PORTE change (enable)
            busy();
        }
        if (spaces_amount >= 16 - str_len) { // text reached right end of line
            spaces_add = -1;
        } else if (spaces_amount <= 0) { // text reached left end of line
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

void lab2_main(
        DELAY* cycle_delay,
        DELAY* sound_delay,
        uint16_t* snd_duration,
        uint16_t* snd_interval,
        uint8_t* m_idx,
        uint8_t* s_idx,
        uint8_t* x,
        bool* reverse
        ) {
    init_lcd(); // reset LCD
    print_to_lcd(false, get_first_line_by_switch()); // print to first line
    move_cursor_to_pos(0xc0); // move cursor to second line
    print_to_lcd(true, get_second_line_by_switches()); // print to second line

    /* SW7 - EXIT PROGRAM */
    if (switches[7]) {
        PORTA = 0;
        exit(0);
    }

    /* SW6 - MAKE BEEP SOUND */
    if (switches[6]) {
        uint16_t s;
        for (s = 0; s < *snd_duration; s++) {
            PORTBbits.RB14 ^= 1; // bit flip
            $wait(*sound_delay);
        }
        if (*snd_duration >= SND_DUR_CEIL) *snd_interval = -SND_DUR_JUMP;
        else if (*snd_duration <= SND_DUR_FLOOR) *snd_interval = SND_DUR_JUMP;
        *snd_duration += *snd_interval;
    }

    /* SW4 - CHANGE SPEED */
    *cycle_delay = switches[4] ? SHORT_DELAY : LONG_DELAY;
    *sound_delay = switches[4] ? SND_SHORT_DELAY : SND_LONG_DELAY;

    /* SW3 - CHANGE DIRECTION */
    *reverse = switches[3];

    if (!switches[5]) { /* SW5 - STOP LED MOVEMENT */
        /* CHOOSE AND DO CHOSEN OPERATION */
        if (switches[2]) { // SW2 - `MENIFA`
            PORTA = menifa_nums[*m_idx % 4];
            if (*reverse) *m_idx -= 1;
            else *m_idx += 1;
        } else if (switches[1]) { // SW1 - SHIFT
            PORTA = shift_nums[*s_idx % 8];
            if (*reverse) *s_idx -= 1;
            else *s_idx += 1;
        } else if (switches[0]) { // SW0 - BINARY COUNTER
            PORTA = *x;
            if (*reverse) *x -= 1;
            else *x += 1;
        }
    }

    $wait(*cycle_delay);
}

char *get_first_line_by_switch() {
    if (switches[7]) return "Mode 7:";
    if (switches[6]) return "Mode 6:";
    if (switches[5]) return "Mode 5:";
    if (switches[2]) return "Mode 2:";
    if (switches[1]) return "Mode 1:";
    if (switches[0]) return "Mode 0:";
    return "No Mode Selected";
}

char *get_second_line_by_switches() {
    if (switches[7]) return "Exit";
    if (switches[6]) return "Beep Mode";
    if (switches[5]) return "Halt";

    bool fast = switches[4];
    bool reversed = switches[3];

    if (switches[2]) { // menifa
        if (!fast && !reversed) return "SwingUpSlow";
        if (!fast && reversed)  return "SwingDownSlow";
        if (fast && !reversed)  return "SwingUpFast";
        return "SwingDownFast";
    }
    if (switches[1]) { // shift
        if (!fast && !reversed) return "ShiftLeftSlow";
        if (!fast && reversed)  return "ShiftRightSlow";
        if (fast && !reversed)  return "ShiftLeftFast";
        return "ShiftRightFast";
    }
    if (switches[0]) { // counter
        if (!fast && !reversed) return "CounterUpSlow";
        if (!fast && reversed)  return "CounterDownSlow";
        if (fast && !reversed)  return "CounterUpFast";
        return "CounterDownFast";
    }
    return "";
}

void init_lcd() {
    PORTBbits.RB15 = 0; //rs=0
    PORTDbits.RD5 = 0; //write=0
    char control[] = {0x38, 0x38, 0x38, 0xe, 0x6, 0x1, 0x01};
    for (int i = 0; i < sizeof (control) / sizeof (control[0]); i++) {
        PORTE = control[i];
        PORTDbits.RD4 = 1; // pulse to apply cmd
        PORTDbits.RD4 = 0;
        busy();
    }
    PORTBbits.RB15 = 1; //rs=1 to read or to write
    PORTDbits.RD5 = 0; //w=0       
}

void move_cursor_to_pos(uint32_t pos) {
    PORTBbits.RB15 = 0; // rs: Register Select: 1: Data, 0: Instructions.
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
