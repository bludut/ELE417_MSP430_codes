#include <msp430.h> 
#define DELAY 50000
#define SHORT 2
#define LONG 8

volatile unsigned int count = 0;
void main(void)
{
    WDTCTL = WDTPW + WDTHOLD; // Stop WDT
    // configure the clock to 1MHz
    DCOCTL=CALDCO_1MHZ;
    BCSCTL1=CALBC1_1MHZ;

    P1DIR |= BIT0; // configure P1.0 as output. LED connection
    P1OUT &= ~BIT0; // turn the LED off
    TACCTL0 = CCIE; // enable the interrupt
    TACCR0 = DELAY; // set the timer a load value
    // the source of the timer is SMCLK, mode of the timer is up count
    // timer interrupt is enabled, SMCLK is divided by 1
    TACTL = TASSEL_2 | MC_1 | TAIE | TACLR | ID_1;

    _BIS_SR(GIE); // global interrupt enable
    while(1){

    }
}
// Timer Interrupt Vector handler
#pragma vector=TIMER0_A0_VECTOR
__interrupt void Timer_A(void)
{
    // turn on LED and short delay
    if(count == 0 ){
        P1OUT ^= BIT0;
    }
    // turn of LED and short delay
    if(count == SHORT){
        P1OUT ^= BIT0;
    }
    // turn on LED and long delay
    if(count == 2*SHORT){
        P1OUT ^= BIT0;
    }
    // turn off LED and long delay
    if(count == 2*SHORT+LONG){
        P1OUT ^= BIT0;
    }
    count++;
    if(count == 2*(SHORT+LONG)){
        count = 0;
    }
    // clear the interrupt flag
    TACTL &= ~TAIFG;
}
