
/* 
 * File:   
 * Author: Tom Stenvall
 * Comments:
 * Revision history: 
 */

#ifndef MCP23008_H
#define	MCP23008_H
#include <xc.h>


//Sets gpio pins data direction, 1:input, 0:output
void MCP23008_ini(uint8_t dir_byte);

//Write to the gpio register
void MCP23008_gpio_write(uint8_t pin_byte);

//Returns gpio register byte
uint8_t MCP23008_gpio_read();


#endif

