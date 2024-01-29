
#include "mcp23008.h"
#include "I2C.h"
#define MCP23008_ADDRESS 0x20

typedef enum{
    MCP8_IODIR,
    MCP8_IPOL,
    MCP8_GPINTEN,
    MCP8_DEFVAL,
    MCP8_INTCON,
    MCP8_IOCON,
    MCP8_GPPU,
    MCP8_INTF,
    MCP8_INTCAP,
    MCP8_GPIO,
    MCP8_OLAT
}REG_MCP8;

void MCP23008_ini(uint8_t dir_byte){
    
    I2C_startbit();
    I2C_write(MCP23008_ADDRESS << 1);
    
    I2C_write(MCP8_IODIR);
    I2C_write(dir_byte);        //Set data dir
    I2C_stopbit();
    
    //Address pins enable, int, etc could go here. Now all set to disable.
    
    MCP23008_gpio_write(0x00);
}

void MCP23008_gpio_write(uint8_t pin_byte){
    
    I2C_startbit();
    I2C_write(MCP23008_ADDRESS << 1);
    I2C_write(MCP8_GPIO);
    I2C_write(pin_byte);
    I2C_stopbit();
}

uint8_t MCP23008_gpio_read(){
    I2C_startbit();
    I2C_write(MCP23008_ADDRESS << 1);
    I2C_write(MCP8_GPIO);
    
    I2C_restartbit();
    
    uint8_t gpio_byte = I2C_read(1);
    I2C_stopbit();
    
    return gpio_byte;
}