/*
 * myUart.c
 *
 *  Created on: Dec 17, 2017
 *      Author: FatihKaya
 */
#include <msp430.h>
#include "myUart.h"


void Uart_send(unsigned char data){
    // uart byte send
    while (!(IFG2&UCA0TXIFG));                // USCI_A0 TX buffer ready?
    UCA0TXBUF = data;
}

void Uart_init(){
    /*
     * Uart init
     */
    P1SEL = BIT1 + BIT2 ;                     // P1.1 = RXD, P1.2=TXD
    P1SEL2 = BIT1 + BIT2 ;                    // P1.1 = RXD, P1.2=TXD
    UCA0CTL1 |= UCSSEL_2;                     // SMCLK
    UCA0BR0 = 104;                            // 1MHz 9600
    UCA0BR1 = 0;                              // 1MHz 9600
    UCA0MCTL = UCBRS0;                        // Modulation UCBRSx = 1
    UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
    IE2 |= UCA0RXIE;                          // Enable USCI_A0 RX interrupt
    __bis_SR_register( GIE);       // Enter LPM0, interrupts enabled

}
