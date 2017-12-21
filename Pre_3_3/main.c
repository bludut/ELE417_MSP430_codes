#include <msp430.h>

#define LONG_DELAY 32797
#define SHORT_DELAY LONG_DELAY/4

int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR |= BIT6;  // P1.0 is configured as output
    P1OUT |= BIT6; // Led on P1.1 is turned on
    TACCR0 = LONG_DELAY;
    TACTL = TASSEL_1 | MC_1 | TACLR;

    volatile unsigned int isShort = 0;
    volatile unsigned int isLong = 1;
    volatile unsigned int count = 0;
    while(1){
        // blink when interrupt flag is set
        if(TACTL&TAIFG == TAIFG){
            P1OUT ^= BIT6;
            TACTL &= ~TAIFG;
            count++;
        }
        // after one blink set the delay type
        if(count == 2){
            count=0;
            isShort ^= 1;
            isLong ^= 1;
        }
        // Due to delay type set TACCR0 register
        if(isShort == 1){
            TACCR0 = SHORT_DELAY;
        }
        else if(isLong == 1){
            TACCR0 = LONG_DELAY;
        }



    }
}
