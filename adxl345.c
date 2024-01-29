


#include "adxl345.h"


#define ADXL345_ADDRESS 0x53 //7bit type!


//Register enums
enum{
    REG_THRESH_ACT = 0x24,
    REG_THRESH_INACT = 0x25,
    REG_TIME_INACT = 0x26,
    REG_ACT_INACT_CTRL = 0x27,
    REG_BW_RATE = 0x2C,
    REG_POWER_CTRL = 0x2D,
    REG_INT_ENABLE = 0x2E,
    REG_INT_MAP = 0x2F,
    REG_INT_SOURCE = 0x30,
    
    REG_DATA_X0 = 0x32,
    REG_DATA_X1 = 0x33,
    
    REG_DATA_Y0 = 0x34,
    REG_DATA_Y1 = 0x35,
    
    REG_DATA_Z0 = 0x36,
    REG_DATA_Z1 = 0x37
    
    
    
};

void ADXL_mode_measure(){
    I2C_startbit();
    I2C_write(ADXL345_ADDRESS << 1);
    
    I2C_write(REG_POWER_CTRL);
    I2C_write(0b1000);//Measure mode bit set
    I2C_stopbit();
}

void ADXL_mode_detection(uint8_t threshold, uint8_t time_sec){
    
    I2C_startbit();
    I2C_write(ADXL345_ADDRESS << 1);
    
    I2C_write(REG_THRESH_ACT);
    
    I2C_write(threshold); //0x24
    I2C_write(threshold); //0x25
    I2C_write(time_sec);
    I2C_write(0xFF); //AC mode, all axis enabled for inact and act detection
    
    I2C_restartbit();
    
    I2C_write(ADXL345_ADDRESS << 1);
    I2C_write(REG_POWER_CTRL);
    
    I2C_write(0b111000); //0x2D Link, autosleep and measure bit set.
    I2C_write(0b11000); //0x2E Inact and act functions enable.
    I2C_write(0b11100111);//0x2F Send inact and act INTs to pin 1.
    I2C_stopbit();
}

uint8_t ADXL_read_int(){
    
    I2C_startbit();
    I2C_write(ADXL345_ADDRESS << 1);
    I2C_write(REG_INT_SOURCE);
    
    I2C_restartbit();
    I2C_write(ADXL345_ADDRESS << 1 | 0x01);
    
    uint8_t status_byte = I2C_read(1);
    I2C_stopbit();
    
    return status_byte;
}

void ADXL_read(Acc_data* data_frame){
    
    I2C_startbit();
    I2C_write(ADXL345_ADDRESS << 1);
    I2C_write(REG_DATA_X0);
    
    I2C_restartbit();
    
    I2C_write(ADXL345_ADDRESS << 1 | 0x01);
  
    
    data_frame->acc_x = I2C_read(0);
    data_frame->acc_x |= (I2C_read(0) << 8);
    
    data_frame->acc_y = I2C_read(0);
    data_frame->acc_y |= (I2C_read(0) << 8);
    
    data_frame->acc_z = I2C_read(0);
    data_frame->acc_z |= (I2C_read(1) << 8);
    I2C_stopbit();
}