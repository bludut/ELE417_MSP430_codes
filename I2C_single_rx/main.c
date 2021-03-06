#include <msp430.h>
#include "typedef.h"

#define MPU_ADD 0x68
#define WHOAMI 0x75

enum I2C_ERROR {I2C_NO_ERROR, I2C_ERROR_STOP_CONDITION, I2C_ERROR_START_CONDITION};
#define I2C_TIMEOUT 0xFF

void I2C_Init(uint8_t slaveAddr);
uint8_t I2C_Read(uint8_t registerAddr);
uint8_t I2C_GenerateStart();
uint8_t I2C_GenerateStop();

volatile unsigned int data=0;
int main(void)
{
    WDTCTL = WDTPW | WDTHOLD;   // stop watchdog timer
    P1DIR = BIT0;
    P1OUT &= ~BIT0;

    while(1){
        I2C_Init(MPU_ADD);
        data = I2C_Read(WHOAMI);

        if(data == MPU_ADD){
            P1OUT ^= BIT0;
        }
        _delay_cycles(10000);

    }


    return 0;
}

void I2C_Init(uint8_t slaveAddr)
{
    //P1.7 -> SDA
    //P1.6 -> SCL
    P1SEL  |= (BIT6 | BIT7);
    P1SEL2 |= (BIT6 | BIT7);
    //Reset to USCI module
    //-- USCI Module Set as I2C
    //-- Single Master
    //-- 7Bit Slave Address
    //-- Master Mode
    //-- Sycnhrous Mode
    //-- SMCLCK
    UCB0CTL0 = (UCMST | UCSYNC | UCMODE_3);
    UCB0CTL1 = UCSSEL_2 + UCSWRST;
    UCB0BR0 = 12;                           //Baudrate
    UCB0BR1 = 0;
    UCB0I2CSA = slaveAddr;
    UCB0CTL1 &= ~UCSWRST;
}


uint8_t I2C_Read(uint8_t registerAddr,uint8_t slaveAddr)
{
    UCB0I2CSA = slaveAddr;

    // i2c transmit
    UCB0CTL1 |= (UCTR);
    IFG2 &= ~UCB0TXIFG;

    UCB0CTL1 |= UCTXSTT; // Send Start and slave address
    while (( UCB0CTL1 & UCTXSTT) != 0) {
    }

    UCB0TXBUF = registerAddr;
    while(!(IFG2 & UCB0TXIFG));     //Wait for TXIFG == 1
    IFG2 &= ~(UCB0TXIFG);           //then clear TXIFG

    UCB0CTL1 &= ~(UCTR);
    if(I2C_GenerateStart() != I2C_NO_ERROR) return 2;   // send start
    if(I2C_GenerateStop()  != I2C_NO_ERROR) return 3;   // send stop

    while(!(IFG2 & UCB0RXIFG));
    IFG2 &= ~(UCB0RXIFG);
    return UCB0RXBUF;
}

uint8_t I2C_GenerateStart()
{
    uint8_t timeout = I2C_TIMEOUT;

    UCB0CTL1 |= (UCTXSTT);
    while(UCB0CTL1 & UCTXSTT)
    {
      //  if(timeout == 0) return I2C_ERROR_START_CONDITION;
        timeout--;
    }
    return I2C_NO_ERROR;
}

uint8_t I2C_GenerateStop()
{
    uint8_t timeout = I2C_TIMEOUT;
    UCB0CTL1 |= (UCTXSTP);
    while(UCB0CTL1 & UCTXSTP)
    {
        if(timeout == 0) return I2C_ERROR_STOP_CONDITION;
        timeout--;
    }
    return I2C_NO_ERROR;
}
