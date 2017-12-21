#include <msp430.h>				

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= BIT0;					// configure P1.0 as output

    P1DIR &= (~BIT3); // set the pin of the button as input
    P1REN |= BIT3;  // enable the pull up resistor

    volatile unsigned int ButtonState; // holds the state of the button
    volatile unsigned int i;    // for delay
	P1OUT &= (~BIT0);
	while(1)
	{
	    ButtonState = P1IN & BIT3;
	    for(i= 1000; i>0; i--); // debounce delay
	    if (ButtonState == 0){
            P1OUT ^= BIT0; // toggle the led
            while(ButtonState == 0){ // wait until the button is released
                ButtonState = P1IN & BIT3;
                for(i= 100; i>0; i--); // debounce delay
            }
	    }

	}
}
