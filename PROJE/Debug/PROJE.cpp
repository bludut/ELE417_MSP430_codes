#include "Energia.h"

#line 1 "C:/Users/FatihKaya/Documents/CCS_MSP430_WS/PROJE/PROJE.ino"






#include <Wire.h>          

#define MPU_ADD 0x68
#define MPU6050_RA_WHO_AM_I 0x75
int8_t I2C_readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data);
int8_t I2C_readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data);
int8_t I2C_readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data);
bool I2C_writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* data);
bool I2C_writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data);
bool I2C_writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data);
void setup();
void MPUInit();
void loop();

#line 11
uint8_t data[1];


int8_t I2C_readBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t *data){
    int8_t count = 0;
    for (uint8_t k = 0; k < length; k += min(length, BUFFER_LENGTH)) {
        Wire.beginTransmission(devAddr);
        Wire.write(regAddr);
        Wire.endTransmission();
        Wire.beginTransmission(devAddr);
        Wire.requestFrom(devAddr, (uint8_t)min(length - k, BUFFER_LENGTH));

        for (; Wire.available(); count++) {
            data[count] = Wire.read();
            #ifdef I2CDEV_SERIAL_DEBUG
                Serial.print(data[count], HEX);
                if (count + 1 < length) Serial.print(" ");
            #endif
        }
        Wire.endTransmission();
    }

    return count;
}

int8_t I2C_readByte(uint8_t devAddr, uint8_t regAddr, uint8_t *data) {
    return I2C_readBytes(devAddr, regAddr, 1, data);
}

int8_t I2C_readBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint16_t *data) {
    
    
    
    
    
    uint8_t count, b;
    if ((count = I2C_readByte(devAddr, regAddr, &b)) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        b &= mask;
        b >>= (bitStart - length + 1);
        *data = b;
    }
    return count;
}


bool I2C_writeBytes(uint8_t devAddr, uint8_t regAddr, uint8_t length, uint8_t* data) {
  uint8_t status = 0;
  Wire.beginTransmission(devAddr);
  Wire.write((uint8_t) regAddr); 
  for (uint8_t i = 0; i < length; i++) {
          Wire.write((uint8_t) data[i]);
   }
  Wire.endTransmission();

  return status == 0;
}

bool I2C_writeByte(uint8_t devAddr, uint8_t regAddr, uint8_t data) {
    return I2C_writeBytes(devAddr, regAddr, 1, &data);

}

bool I2C_writeBits(uint8_t devAddr, uint8_t regAddr, uint8_t bitStart, uint8_t length, uint8_t data) {
    
    
    
    
    
    
    
    uint8_t b;
    if (I2C_readByte(devAddr, regAddr, &b) != 0) {
        uint8_t mask = ((1 << length) - 1) << (bitStart - length + 1);
        data <<= (bitStart - length + 1); 
        data &= mask; 
        b &= ~(mask); 
        b |= data; 
        return I2C_writeByte(devAddr, regAddr, b);
    } else {
        return false;
    }
}


void setup()
{
  Serial.begin(9600);      
  Wire.begin();            
}

#define MPU6050_RA_PWR_MGMT_1 0x6B
#define MPU6050_PWR1_CLKSEL_BIT 2
#define MPU6050_PWR1_CLKSEL_LENGTH 3
#define MPU6050_CLOCK_PLL_XGYRO 0x01
#define MPU6050_PWR1_SLEEP_BIT 6

void MPUInit(){
I2C_writeBits(MPU_ADD, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_CLKSEL_BIT, MPU6050_PWR1_CLKSEL_LENGTH, MPU6050_CLOCK_PLL_XGYRO);
I2C_writeBits(MPU_ADD, MPU6050_RA_PWR_MGMT_1, MPU6050_PWR1_SLEEP_BIT,1, 0);
}


void loop()
{

I2C_readByte(MPU_ADD, MPU6050_RA_WHO_AM_I, data);
 Serial.println(data[1]);
 delay(50);

 I2C_readByte(MPU_ADD+1, MPU6050_RA_WHO_AM_I, data);
 Serial.println(data[1]);
 delay(50);
 
}




