#include <msp430.h> 

void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop watchdog timer
    P1DIR |= BIT6; // configure P1.6 as output LED connection
    P1OUT &= ~BIT6; // turn off the LED
    P1REN |= BIT3;  // configure P1.3 as input Switch connection
    P1IE |= BIT3; //   enable P1.3 interrupt
    P1IES |= BIT3; // configure the edge of the interrupt
    P1IFG &= ~BIT3; // clear the interrupt flag
    _BIS_SR(GIE); // Enter LPM4 w/interrupt

    while(1){

    }
}

// Port 1 interrupt service routine
#pragma vector=PORT1_VECTOR
__interrupt void Port_1(void)
{
    _delay_cycles(10000);
    P1OUT ^= BIT6; // toggle LED
    P1IES ^= BIT3;  // toggle the edge of the interrupt
    P1IFG &= ~BIT3; // clear interrupt flag
}
