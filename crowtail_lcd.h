
/*  
 * Tom Stenvall
 * 
 * Library for the crowtail I2C LCD module done by 
 * reverse engineering the I2C module that is simply a MCP23008 IO module
 */

#ifndef CROWTAIL_LCD_H
#define	CROWTAIL_LCD_H

#include "config.h" //Needs the _XTAL_FREQ for delays
#include "mcp23008.h"
#include <string.h>
#include <xc.h>

typedef enum{
    CLEAR = 0x01,
    CURSOR_ON = 0x0E,
    CURSOR_OFF = 0x0C,
    DISPLAY_OFF = 0x08,
    DISPLAY_ON = 0x0C,
            
    
    SET_DDRAM_ADDRESS = 0x80,
    SET_CGRAM_ADDRESS = 0x40
            

}LCD_INSTRUCTIONS;

void lcd_start(void);
void lcd_stop();

void lcd_print(char* s);
void lcd_write(char c);

void lcd_ins(uint8_t ins_byte);
void lcd_createchar(char* custom_char, uint8_t slot);
void lcd_setcursor(uint8_t col, uint8_t row);

#endif

