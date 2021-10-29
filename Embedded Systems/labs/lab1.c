#include <xc.h>
#include <stdbool.h>

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

typedef uint32_t DELAY;
DELAY SHORT_DELAY = 64000, LONG_DELAY = 64000 * 8,
        SND_SHORT_DELAY = 256, SND_LONG_DELAY = 512;

void $wait(DELAY delay) {
    uint32_t j;
    for (j = 0; j < delay; j++);
}

void main() {
    TRISA &= 0xff00;        // SET lower bits (LEDs) as output (0)
    PORTA = 0;              // turn off LEDs

    /* CONFIGURE SWITCHES TO ACCEPT INPUT*/
    TRISFbits.TRISF3 = 1;   // RF3  (SW0) configured as input
    TRISFbits.TRISF3 = 1;   // RF3  (SW0) configured as input
    TRISFbits.TRISF5 = 1;   // RF5  (SW1) configured as input
    TRISFbits.TRISF4 = 1;   // RF4  (SW2) configured as input
    TRISDbits.TRISD15 = 1;  // RD15 (SW3) configured as input
    TRISDbits.TRISD14 = 1;  // RD14 (SW4) configured as input
    TRISBbits.TRISB11 = 1;  // RB11 (SW5) configured as input
    ANSELBbits.ANSB11 = 0;  // RB11 (SW5) disabled analog
    TRISBbits.TRISB10 = 1;  // RB10 (SW6) configured as input
    ANSELBbits.ANSB10 = 0;  // RB10 (SW6) disabled analog
    TRISBbits.TRISB9 = 1;   // RB9  (SW7) configured as input
    ANSELBbits.ANSB9 = 0;   // RB9  (SW7) disabled analog

    TRISBbits.TRISB14 = 0;  // set speaker as output
    ANSELBbits.ANSB14 = 0;  // speaker - disabled analog

    uint8_t x = 1;
    DELAY cycle_delay = LONG_DELAY, sound_delay = SND_LONG_DELAY;
    bool run = true, reverse = false;
    uint32_t snd_duration = 400, snd_interval = 50;
    uint8_t menifa_nums[] = {0x18, 0x24, 0x42, 0x81}, m_idx = 0;
    uint8_t shift_nums[] = {1, 2, 4, 8, 0x10, 0x20, 0x40, 0x80}, s_idx = 0;

    while (1) {
        /* SW7 - EXIT PROGRAM */
        if (PORTBbits.RB9) {
            PORTA = 0;
            return;
        }

        /* SW6 - MAKE BEEP SOUND */
        if (PORTBbits.RB10) {
            uint16_t s;
            for (s = 0; s < snd_duration; s++) {
                PORTBbits.RB14 ^= 1;
                $wait(sound_delay);
            }
            if (snd_duration >= 400 || snd_duration <= 100) snd_interval *= -1;
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
            if (PORTFbits.RF4) {        // SW2 - `MENIFA`
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
