#include <msp430.h>				

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= BIT0;					// configure P1.0 as output
	P1DIR &= (~BIT3);                // configure P1.3 as input
	P1REN |= BIT3;                   // enable the pull up for P1.3

	volatile unsigned int ButtonState;
    volatile unsigned int i;    // for delay
	while(1)
	{

	    ButtonState = P1IN & BIT3;// assign the state of button

	    for(i = 1000; i>0;i--); // short delay to get rid of debounce

	    if((ButtonState & BIT3) == 0){
	        // If button is pressed
	        P1OUT |= BIT0;
	    }else{
	        P1OUT &= (~BIT0);
	    }


	}
}
