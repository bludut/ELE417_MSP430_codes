/*
 * ADC.c
 *
 *  Created on: Dec 16, 2017
 *      Author: FatihKaya
 */
#include <msp430.h>
#include "ADC.h"

void ADC_init(){
    ADC10CTL1 = INCH_7 | CONSEQ_1;            // A3/A2/A1, single sequence
    ADC10CTL0 = ADC10SHT_2 + MSC + ADC10ON + ADC10IE;
    ADC10DTC1 = 0x03;                         // 3 conversions
    ADC10AE0 |= BIT6 | BIT7;
}

void ADC_read(unsigned int *ADCdata){
   ADC10CTL0 &= ~ENC;
   while (ADC10CTL1 & ADC10BUSY);               // Wait if ADC10 core is active
   ADC10SA = ADCdata;                        // Data buffer start
   ADC10CTL0 |= ENC + ADC10SC;
}


