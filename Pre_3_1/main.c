#include <msp430.h> 


/**
 * main.c
 */
int main(void)
{

    /*
     *  Configure P2.6 and P2.7 as clock input
     */

/*
    P2SEL |= (BIT6 | BIT7); // Set P2.6 and P2.6 SEL for XIN, XOUT
    P2SEL2 &= ~(BIT6|BIT7); // Set P2.6 and P2.7 SEL2 for XIN, XOUT

    BCSCTL1 &= (~XTS); // ACLK = LFXT1CLK
    BCSCTL3 &= ~(BIT4|BIT5); // 32768Hz crystal on LFXT1
*/
	WDTCTL = WDT_ADLY_1000;	// stop watchdog timer
	P1DIR |= BIT6;  // P1.0 is configured as output
	P1OUT = ~BIT6; // Led on P1.1 is turned off
	while(1){
	    if(IFG1&BIT0 == WDTIFG){
	        P1OUT ^= BIT6;
	        IFG1 &= ~WDTIFG;
	    }
	}
}
