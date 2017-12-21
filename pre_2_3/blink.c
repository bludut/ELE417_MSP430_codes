#include <msp430.h>				


/**
 * blink.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= 0xff;					// configure P1 port as output
	P1OUT = 0x00;   // all LEDs are off

	P2DIR &= ~BIT7; // configure p2.7 as input

    volatile unsigned int ButtonState; // holds the state of the button
    volatile unsigned int i;    // for delay
    volatile unsigned int count=0; // counter variable

	while(1)
	{
	    ButtonState = P2IN & BIT7; // read the button state

	    if(ButtonState == 0){
	    while (ButtonState == 0){
	               count++;
	               _delay_cycles(1000000); // wait one second
	         }
	    P1OUT = count; // show the time on LEDs in second
	    count = 0;
	    }
	}
}
