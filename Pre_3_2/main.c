#include <msp430.h>


/**
 * main.c
 */
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD; // stop watchdog timer
    P1DIR |= BIT6;  // P1.0 is configured as output
    P1OUT = ~BIT6; // Led on P1.1 is turned off
    TACCR0 = 32797;
    TACTL = TASSEL_1 | MC_1 | TACLR;
    while(1){
        if(TACTL&TAIFG == TAIFG){
            P1OUT ^= BIT6;
            TACTL &= ~TAIFG;
        }
    }
}
