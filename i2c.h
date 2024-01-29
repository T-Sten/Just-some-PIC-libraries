

#ifndef I2C_H
#define I2C_H

#include <xc.h>

/* I2C_ini initialises SSP module for I2C and sets the baudrate
 * 
 * FORMULA FOR SSPADD REGISTER VALUE:
 * sspaddreg_value = (Fosc/4) * baudRate) - 1;
 */
void I2C_ini(uint8_t sspaddreg_value);


void I2C_startbit(void);    //Sends startbit
void I2C_stopbit(void);     //Sends stopbit
void I2C_restartbit(void);  //sends repeated start bit

void I2C_write(uint8_t data);       //Writes one byte
uint8_t I2C_read(uint8_t ack);      //Returns recieved byte, send ack for slave to stop reading after this call

#endif