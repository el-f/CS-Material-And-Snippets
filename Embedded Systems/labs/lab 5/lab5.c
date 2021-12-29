#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include <sys/attribs.h>
#include <string.h>
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
	Author: Denis Karabitski https://github.com/denisaka1
 */

#define NONE 0xff
#define DEFAULT_DELAY_TIME 320000
#define AUDIO_DELAY_TIME 400
#define KEYBOARD_LENGTH 16

char keyboard_values[KEYBOARD_LENGTH * 2] = {
    0x44, '1',
    0x34, '2',
    0x24, '3',
    0x43, '4',
    0x33, '5',
    0x23, '6',
    0x42, '7',
    0x32, '8',
    0x22, '9',
    0x41, '0',
    0x14, 'A',
    0x13, 'B',
    0x12, 'C',
    0x11, 'D',
    0x21, 'E',
    0x31, 'F'
};

int DELAY_TIME = DEFAULT_DELAY_TIME;

#define LCD_SCREEN_SIZE 16
#define LCD_FIRST_LINE 0x80
#define LCD_SECOND_LINE 0xc0

void init();
void beep();
int check_keyboard();
char code_to_ascii(int key_code);
void delay();
void busy();
void lcd_init(char control[], int size);
void lcd_clear();
void lcd_set_text(char first_line[], char second_line[]);
void lcd_write_line(char string[]);
void lcd_set_cursor(int line);
void toggleKeyboardRows(int toggle);
void toggleKeyboardRow(int toggle);
int in_y(int a);
unsigned int ADC_AnalogRead(unsigned char analogPIN);

void main() {
    char key_ascii; // current asccii value for pressed key
    int prev_key = NONE, key_code = NONE;
    double voltage_div_value = 1023 / 3.3;
    int voltage = 0;
    char message[LCD_SCREEN_SIZE];
    init();

    while (1) {
        key_code = check_keyboard();
        if (key_code == prev_key) continue;

        key_ascii = code_to_ascii(key_code);
        switch (key_ascii) {
            case '1':
                beep();
                voltage = ADC_AnalogRead(2); // IN analog RB2
                sprintf(message, "Analog 1 - %.2fV", voltage / voltage_div_value);
                lcd_set_text("Lab6:", message);
                break;
            case '2':
                beep();
                voltage = ADC_AnalogRead(4); // IN analog RB4
                sprintf(message, "Analog 2 - %.2fV", voltage / voltage_div_value);
                lcd_set_text("Lab6:", message);
                break;
        }
        PORTA = voltage/4;
        delay();
    }
}

unsigned int ADC_AnalogRead(unsigned char analogPIN) {
    int adc_val = 0;

    IEC0bits.T2IE = 0;
    AD1CHS = analogPIN << 16; // AD1CHS<16:19> controls which analog pin goes to the ADC

    AD1CON1bits.SAMP = 1; // Begin sampling
    while (AD1CON1bits.SAMP); // wait until acquisition is done
    while (!AD1CON1bits.DONE); // wait until conversion is done

    adc_val = ADC1BUF0;
    IEC0bits.T2IE = 1;
    return adc_val;
}

void init() {
    // ADC configuration
    AD1CON1 = 0;
    AD1CON1bits.SSRC = 7; // Internal counter ends sampling and starts conversion (auto convert)
    AD1CON1bits.FORM = 0; // Integer 16-bit
    // Setup for manual sampling
    AD1CSSL = 0;
    AD1CON3 = 0x0002; // ADC Conversion Clock Select bits: TAD = 6 TPB
    AD1CON2 = 0;
    AD1CON2bits.VCFG = 0; // Voltage Reference Configuration bits: VREFH = AVDD and VREFL = AVSS
    // Turn on ADC
    AD1CON1bits.ON = 1;

    // potentiometer configurations
    TRISBbits.TRISB2 = 1;
    ANSELBbits.ANSB2 = 1;

    // microphone configurations
    TRISBbits.TRISB4 = 1;
    ANSELBbits.ANSB4 = 1;

    // audio configurations
    TRISBbits.TRISB14 = 0;
    ANSELBbits.ANSB14 = 0;

    // keyboard configurations
    TRISCbits.TRISC2 = 0; //RC2
    TRISCbits.TRISC1 = 0; //RC1
    TRISCbits.TRISC4 = 0; //RC4            
    TRISGbits.TRISG6 = 0; //RG6
    ANSELGbits.ANSG6 = 0; // Disable digital
    TRISCbits.TRISC3 = 1; //RC3
    CNPUCbits.CNPUC3; // Resistor RC3
    TRISGbits.TRISG7 = 1; //RG7
    ANSELGbits.ANSG7 = 0; // Disable digital
    CNPUGbits.CNPUG7; // Resistor RG7
    TRISGbits.TRISG8 = 1; //RG8
    ANSELGbits.ANSG8 = 0; // Disable digital
    CNPUGbits.CNPUG8; // Resistor RG8
    TRISGbits.TRISG9 = 1; //RG9
    ANSELGbits.ANSG9 = 0; // Disable digital
    CNPUGbits.CNPUG9; // Resistor RG9

    // LCD configuration
    TRISBbits.TRISB15 = 0; // RB15 (DISP_RS) set as an output
    ANSELBbits.ANSB15 = 0; // disable analog functionality on RB15 (DISP_RS)
    TRISDbits.TRISD5 = 0; // RD5 (DISP_RW) set as an output
    TRISDbits.TRISD4 = 0; // RD4 (DISP_EN) set as an output
    ANSELEbits.ANSE2 = 0;
    ANSELEbits.ANSE4 = 0;
    ANSELEbits.ANSE5 = 0;
    ANSELEbits.ANSE6 = 0;
    ANSELEbits.ANSE7 = 0;
    PORTBbits.RB15 = 0; //rs=0
    PORTDbits.RD5 = 0; //w=0
    TRISE &= 0xff00;
    char control[] = {0x38, 0x38, 0x38, 0xe, 0x6, 0x1, 0x80};
    for (int i = 0; i < 7; i++) {
        PORTE = control[i];
        PORTDbits.RD4 = 1;
        PORTDbits.RD4 = 0;
        busy();
    }
    lcd_clear();
}

void lcd_init(char control[], int size) {
    for (int i = 0; i < size; i++) {
        PORTE = control[i];
        PORTDbits.RD4 = 1;
        PORTDbits.RD4 = 0;
        busy();
    }
    lcd_clear();
}

void lcd_clear() {
    PORTBbits.RB15 = 0; //rs=0
    PORTDbits.RD5 = 0; // w = 0
    PORTE = 0x1;
    PORTDbits.RD4 = 1;
    PORTDbits.RD4 = 0;
    busy();
    //    PORTBbits.RB15 = 1; //rs=1
}

void lcd_set_text(char firstLine[], char secondLine[]) {
    busy();
    lcd_clear();
    lcd_set_cursor(LCD_FIRST_LINE);
    lcd_write_line(firstLine);
    lcd_set_cursor(LCD_SECOND_LINE);
    lcd_write_line(secondLine);
}

void lcd_write_line(char string[]) {
    int length = strlen(string);
    PORTBbits.RB15 = 1; //rs=0
    PORTDbits.RD5 = 0; // w = 0
    for (int i = 0; i < length; i++) {
        PORTE = string[i];
        PORTDbits.RD4 = 1;
        PORTDbits.RD4 = 0;
        busy();
    }
}

void lcd_set_cursor(int line) {
    PORTBbits.RB15 = 0; //rs=0
    PORTDbits.RD5 = 0; // w = 0
    PORTE = line;
    PORTDbits.RD4 = 1;
    PORTDbits.RD4 = 0;
    PORTBbits.RB15 = 1; //rs=1
    busy();
}

void busy() {
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

void beep() {
    int tempDelayTime = DELAY_TIME;
    for (int i = 0; i < AUDIO_DELAY_TIME; i++) {
        PORTBbits.RB14 ^= 1;
        DELAY_TIME = AUDIO_DELAY_TIME + 150;
        delay();
    }
    DELAY_TIME = tempDelayTime;
}

void delay() {
    for (int j = 0; j < DELAY_TIME; j++);
}

int check_keyboard() {
    int coordinates;
    toggleKeyboardRows(1);
    for (int i = 1; i <= 4; i++) {
        toggleKeyboardRow(i);
        coordinates = in_y(i);
        if (coordinates != NONE) return coordinates;
        toggleKeyboardRow(i);
    }
}

void toggleKeyboardRows(int toggle) {
    PORTCbits.RC2 = toggle;
    PORTCbits.RC1 = toggle;
    PORTCbits.RC4 = toggle;
    PORTGbits.RG6 = toggle;
}

void toggleKeyboardRow(int toggle) {
    switch (toggle) {
        case 1:
            PORTCbits.RC2 ^= 1;
            break;
        case 2:
            PORTCbits.RC1 ^= 1;
            break;
        case 3:
            PORTCbits.RC4 ^= 1;
            break;
        case 4:
            PORTGbits.RG6 ^= 1;
            break;
    }
}

int in_y(int a) {
    int j = 0;
    char flag = 0;
    if (!PORTCbits.RC3) { // column 1
        flag = 1;
        j = 1;
    } else if (!PORTGbits.RG7) { // column 2
        flag = 1;
        j = 2;
    } else if (!PORTGbits.RG8) { // column 3
        flag = 1;
        j = 3;
    } else if (!PORTGbits.RG9) { // column 4
        flag = 1;
        j = 4;
    }

    return flag == 0 ? NONE : (j | (a << 4));
}

char code_to_ascii(int key_code) {
    int i;
    for (i = 0; i < KEYBOARD_LENGTH * 2; i += 2) {
        if (keyboard_values[i] == key_code)
            return keyboard_values[i + 1];
    }
}
