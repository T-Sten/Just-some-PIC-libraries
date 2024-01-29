

#include "i2c.h"

#include <xc.h>


void I2C_ini(uint8_t sspaddreg_value){
    //SCL, SDA pins to inputs. MSSP takes control of these pins in master mode
    TRISC3 = 1;
    TRISC4 = 1;
    SSPCON  = 0x28;   //I2C Master mode, SSP enable -> SDA and SCL is used for I2C

    SSPCONbits.SSPEN = 1; //Enable MSSP, takes control of SDI, SDO, SS and SCK pins
    SSPCONbits.SSPM = 0x08; //Master mode, clock = FOSC/(4 * (SSPADD + 1))

    SSPCON2 = 0b00000000;   //TOIMINNOT

    SSPADD = sspaddreg_value; //Set baudrate prescaler for desired baudrate
    SSPSTAT = 0x00;
}

static void I2C_wait(){
    while((SSPCON2 & 0b00011111) | SSPSTATbits.R_W); //These are bits that indicate I2C is busy
}


void I2C_startbit(){
    I2C_wait();
    SSPCON2bits.SEN = 1;
}

void I2C_stopbit(){
    I2C_wait();
    SSPCON2bits.PEN = 1;
}

void I2C_restart(){
    I2C_wait();
    SSPCON2bits.RSEN = 1;
}

void I2C_write(uint8_t data){
  I2C_wait();
  SSPBUF = data;
}

unsigned short I2C_read(uint8_t ack){

  //Wait for I2C module to become idle, else RCEN bit may not be set
  I2C_wait();
  SSPCON2bits.RCEN = 1; //Enable I2C receive mode
  
  //Wait for receive to complete before reading
  I2C_wait();
  uint8_t data = SSPBUF;
  
  SSPCON2bits.ACKDT = ack; //If this is the last byte to receive, set NACK bit
  ACKEN = 1; //Send ACK or NACK bit
  
  return data;
}


#endif
