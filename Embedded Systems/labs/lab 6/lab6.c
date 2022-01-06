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

#define DEFAULT_DELAY_TIME 320000
#define START_COUNTER 0
#define END_COUNTER 99

int DELAY_TIME = DEFAULT_DELAY_TIME;
int COUNTER = START_COUNTER;
int TIMER_4_COUNTER = 0;
int TIMER_2_3_COUNTER = 0;

#define LCD_SCREEN_SIZE 16
#define LCD_FIRST_LINE 0x80
#define LCD_SECOND_LINE 0xc0

char message[LCD_SCREEN_SIZE];

void init();
void delay();
void busy();
void lcd_init(char control[], int size);
void lcd_clear();
void lcd_set_text(char first_line[], char second_line[]);
void lcd_write_line(char string[]);
void lcd_set_cursor(int line);

void timer1();
void timer2_3();
void timer4();

void __ISR(_TIMER_1_VECTOR, ipl2auto) Timer1SR(void);
void __ISR(_TIMER_3_VECTOR, ipl6auto) Timer23SR(void);
void __ISR(_TIMER_4_VECTOR, ipl7auto) Timer4SR(void);

void main() {
    init();
    timer1();
    timer2_3();
    timer4();
    INTCONbits.MVEC = 1; //vector interrupt
    IPTMR = 0; //INTERRUPT PROXIMITY TIMER REGISTER
    asm("ei"); //on interrupt
    while (1);
}

void timer1() {
    // Timer 1 configuration
    PR1 = 12500; // set period register interrupt each 10 ms
    TMR1 = 0; // initialize count to 0
    T1CONbits.TGATE = 0; // not gated input (default)
    T1CONbits.TCS = 0; // PCBLK input (default)
    T1CONbits.TCKPS0 = 1; // 1:256 prescale value
    T1CONbits.TCKPS1 = 1;
    T1CONbits.TSYNC = 1;
    T1CONbits.ON = 1; // turn on Timer1
    IPC1bits.T1IP = 2; // interrupt vector priority
    IPC1bits.T1IS = 2; // interrupt vector sub priority
    IEC0bits.T1IE = 1;
    IFS0bits.T1IF = 0;
}

void timer2_3() {
    // Timer 2-3 configuration
    PR2 = 0xffff; // PR2x interrupt each 2 seconds
    PR3 = 0x3; // PR2y
    TMR2 = 0; // TMRx
    TMR3 = 0; // TMRy
    T2CONbits.TGATE = 0; // not gated input (default)
    T2CONbits.TCS = 0; // PCBLK input (default)
    T2CONbits.TCKPS0 = 1; // 1:256 prescale value
    T2CONbits.TCKPS1 = 1;
    T2CONbits.TCKPS2 = 1;
    T2CONbits.T32 = 1; // mode 32 bit
    T2CONbits.ON = 1; // turn on Timer 2-3
    T3CONbits.ON = 0; // turn on Timer 2-3
    //    IPC2bits.T2IP = 2; // interrupt vector priority
    //    IPC2bits.T2IS = 1; // interrupt vector sub priority
    IPC3bits.T3IP = 6; // interrupt vector priority
    IPC3bits.T3IS = 0; // interrupt vector sub priority
    //    IEC0bits.T2IE = 1;
    IEC0bits.T3IE = 1;
    IFS0bits.T3IF = 0; // clear interrupt flag
}

void timer4() {
    // Timer 4 configuration
    PR4 = 0xffff; // set period register interrupt each 1s
    TMR4 = 0; // initialize count to 0
    T4CONbits.TGATE = 0; // not gated input (default)
    T4CONbits.TCS = 0; // PCBLK input (default)
    T4CONbits.TCKPS0 = 1; // 1: 256 prescale value
    T4CONbits.TCKPS1 = 1;
    T4CONbits.TCKPS2 = 1;
    T4CONbits.ON = 1; // turn on Timer 4
    IPC4bits.T4IP = 7; // interrupt vector priority
    IPC4bits.T4IS = 3; // interrupt vector sub priority
    IFS0bits.T4IF = 0; // clear interrupt flag
    IEC0bits.T4IE = 1;
}

void __ISR(_TIMER_1_VECTOR, ipl2) Timer1SR(void) {
    PORTDbits.RD12 = 0; // turn RGB to GREEN
    PORTDbits.RD2 ^= 1; // turn RGB to RED
    IFS0bits.T1IF = 0; // clean interrupt flag
}

void __ISR(_TIMER_3_VECTOR, ipl6) Timer23SR(void) {
    TIMER_2_3_COUNTER++;
    if (TIMER_2_3_COUNTER == 3) {
        PORTDbits.RD2 = 0; // turn RGB to RED

        PORTDbits.RD12 ^= 1; // turn RGB to GREEN
        TIMER_2_3_COUNTER = 0;
    }
    IFS0bits.T3IF = 0; // clean interrupt flag
}

void __ISR(_TIMER_4_VECTOR, ipl7) Timer4SR(void) {
    TIMER_4_COUNTER++;
    if (TIMER_4_COUNTER == 6) {
        COUNTER = (COUNTER + 1) % 100;
        sprintf(message, "              %02d", COUNTER);
        lcd_set_text("", message);
        TIMER_4_COUNTER = 0;
    }
    IFS0bits.T4IF = 0; // clean interrupt flag
}

void init() {
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
    // RGB configurations
    TRISDbits.TRISD2 = 0; // R LED8_R AN25/RPD2/RD2 output RED
    TRISDbits.TRISD12 = 0; // G LED8_G RPD12/PMD12/RD12 output GREEN
    TRISDbits.TRISD3 = 0; // B LED8_B AN26/RPD3/RD3 output BLUE

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

void delay() {
    for (int j = 0; j < DELAY_TIME; j++);
}