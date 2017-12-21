#include <msp430.h>				


/**
 * blink.c
 */
void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	P1DIR |= 0x01;					// configure P1.0 as output

	P1DIR &= ~BIT2;
	P1IE |= BIT2;
	P1IES |= BIT2;
	P1IFG &= ~BIT2;



	_bis_SR_register(GIE);

	while(1){

	}
}

#pragma vector=PORT1_VECTOR
__interrupt void port1handler(){

    P1IFG &= ~BIT2;
}

#pragma vector = TIMER0_A0_VECTOR
__interrupt void timerinthandler(){

}
