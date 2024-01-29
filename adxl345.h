
/* 
 *  Library for the ADXL345 acceleration IC by Tom Stenvall
 * 
 * 
 */


#ifndef ADXL345_H
#define	ADXL345_H

#include "I2C.h"

//Struct for accelerations x,y,z
typedef struct{
    int acc_x;
    int acc_y;
    int acc_z;
}Acc_data;

//Masks for checking interrupt source
typedef enum{
    ADXL_INACTIVITY = 0b1000,
    ADXL_ACTIVITY = 0b10000
}ADXL_STATUS_MASK;

//Sets the ADXL345 to measuring mode
void ADXL_mode_measure();

//Sets the mode to detect activity and inactivity that lasts (time_sec)
void ADXL_mode_detection(uint8_t threshold, uint8_t time_sec);

//Reads and parses acceleration data to a Acc_data struct
void ADXL_read(Acc_data* data_frame);

//Returns interrupt source byte (use the masks to check a interrupt state)
uint8_t ADXL_read_int();

#endif

