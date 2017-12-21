#include <msp430.h>				


/**
 * blink.c
 */
void main(void)
{
    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    P1DIR |= BIT0;                  // configure P1.0 as output

    P1DIR &= (~BIT3); // set the pin of the button as input
    P1REN |= BIT3;  // enable the pull up resistor

    P2DIR = 0xff;   // set the P2 as output

    volatile unsigned int ButtonState; // holds the state of the button
    volatile unsigned int i;    // for delay
    volatile unsigned int count=0; // counter variable

    while(1)
    {
        ButtonState = P1IN & BIT3; // read the button state
        for(i= 1000; i>0; i--);
        if (ButtonState == 0){
            count++;
            while(ButtonState == 0){
                ButtonState = P1IN & BIT3;
                for(i= 100; i>0; i--);
            }

            P2OUT = count; // show the results on the leds connected to P2

        }

    }
}
