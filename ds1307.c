

#include "ds1307.h"



void DS1307_sqw_enable(DS1307_SQWFREQ freq_setting){
    
    I2C_startbit();
    I2C_write(DS1307_ADDRESS << 1);
    I2C_write(REG_CONTROL);
    I2C_write(freq_setting | 0b10000); //Set SQW freq and set SQW enable bit
    I2C_stopbit();
}

void DS1307_start(){
    
    //Sets all timekeeping registers to 0
    
    I2C_startbit();
    I2C_write(DS1307_ADDRESS << 1);
    I2C_write(REG_SECONDS);
    I2C_write(0x00);
    I2C_write(0x00);
    I2C_write(0x00);
    I2C_write(0x00);
    I2C_write(0x00);
    I2C_write(0x00);
    I2C_write(0x00);
    I2C_stopbit();
}

void DS1307_time_read(Ds1307_time* time_struct){
    
    
    I2C_startbit();
    I2C_write(DS1307_ADDRESS << 1);
    I2C_write(REG_SECONDS); //Set register address pointer
    
    I2C_restartbit();
    
    I2C_write(DS1307_ADDRESS << 1 | 0x01); //Write read request
    
    uint8_t sec_reg = I2C_read(0);
    uint8_t min_reg = I2C_read(0);
    uint8_t hour_reg = I2C_read(1);
    I2C_stopbit();
    
    time_struct->time[5] = sec_reg & 0b1111;    
    time_struct->time[4] = (sec_reg >> 4) & 0b111;    

    time_struct->time[3] = min_reg & 0b1111;
    time_struct->time[2] = (min_reg >> 4);

    time_struct->time[1] = hour_reg & 0b1111;            
    time_struct->time[0] = (hour_reg >> 4) & 0b11;    

    
    time_struct->total_time_min = (time_struct->time[0]*600) + (time_struct->time[1]*60) + (time_struct->time[2]*10) + (time_struct->time[3]);
}

void DS1307_set_time(Ds1307_time *time_struct){
    
    I2C_startbit();
    I2C_write(DS1307_ADDRESS << 1);
    
    I2C_write(REG_SECONDS);
    
    //Set time, seconds to 0
    I2C_write(0x00); //THIS WILL ALSO START THE OSCILLATOR AND TIMEKEEPING IF HALTED!! Set bit 7 (CH) for halting
    I2C_write(time_struct->time[2] << 4 | time_struct->time[3]);
    I2C_write(time_struct->time[0] << 4 | time_struct->time[1]);
    
    I2C_stopbit();
    
            
    
}
