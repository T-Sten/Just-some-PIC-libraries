
#include "crowtail_lcd.h"

#ifndef _XTAL_FREQ
    #error Please create a config.h file with _XTAL_FREQ defined or define it in the cowtail_lcd.h file
#endif

//MCP23008 to LCD pins
enum{
    
    RW = 0b10,
    RS = 0b10,   
    EN = 0b100,
    BL = 0b10000000
            
};

void lcd_start(){
    MCP23008_ini(0x00); //Set gpio pins all to output
    
    MCP23008_gpio_write(0b11000| BL | EN );
    MCP23008_gpio_write(0x00 | BL);
    
    __delay_ms(10);
    
    //Set 4-bit mode
    MCP23008_gpio_write(0b10000| BL | EN );
    MCP23008_gpio_write(0x00 | BL);
    
    __delay_ms(10);
    
    lcd_ins(0b101000); //Set line count to 2, font
    
    __delay_ms(10);
    
    lcd_ins(0b1100); //Set display state, cursor state, cursor blinking state
    
    __delay_ms(10);
    
    lcd_ins(CLEAR);
    
    __delay_ms(10);
}

void lcd_write(uint8_t c){
    
    //D4-D7 pins are gpio 3-6, make msb and lsb from parameter byte
    char c_msb = (c & 0b11110000) >> 1;
    char c_lsb = (c & 0b1111) << 3;
    
    MCP23008_gpio_write(c_msb | BL | EN | RS);
    MCP23008_gpio_write(0x00 | BL);//Clear
    
    MCP23008_gpio_write(c_lsb | BL | EN | RS);
    MCP23008_gpio_write(0x00 | BL);//Clear
    
    
}

void lcd_print(uint8_t s[]){
    uint8_t len = strlen(s);
    for(int i=0; i < len; i++){
        lcd_write(s[i]);
    }
}

void lcd_ins(uint8_t ins_byte){

    //D4-D7 pins are gpio 3-7, make msb and lsb from instruction byte
    uint8_t ins_msb = (ins_byte & 0b11110000) >> 1;
    uint8_t ins_lsb = (ins_byte & 0b1111) << 3;

    MCP23008_gpio_write(ins_msb | BL | EN);
    MCP23008_gpio_write(0x00 | BL);//Clear
    
    MCP23008_gpio_write(ins_lsb | BL | EN);
    MCP23008_gpio_write(0x00 | BL);//Clear
}


void lcd_setcursor(uint8_t col, uint8_t row){
    lcd_ins(SET_DDRAM_ADDRESS | col | (0x80 >> row));
}

void lcd_createchar(char* custom_char, uint8_t slot){
  uint8_t address = 0x40 + 8 * slot;
  lcd_ins(address);
    
  for(int i = 0; i < 8; i++){
    lcd_write(custom_char[i]);
  }
}
