
#include "PID.h"

static float kp, ki, kd;

static int16_t last_pid = 0;

static uint8_t has_looped;
static double i;

void PID_ini(float new_kp, float new_ki, float new_kd){
    kp = new_kp;
    ki = new_ki;
    kd = new_kd;
}

void PID_reset(){
    has_looped = 0;
    last_pid = 0;
}

int16_t PID_calculate(int16_t target_value, int16_t current_value, uint32_t time_ms){
    
    static uint32_t last_time_ms;
    static int16_t last_error;
    
    //Only allow positive delta
    if(time_ms < last_time_ms){
        last_time_ms = time_ms;
        return last_pid;
    }
    else if(time_ms == last_time_ms){
        return last_pid; 
    }
            
    int16_t error = target_value - current_value;
    
    int16_t p = error * kp;
    
    int16_t d;
    uint16_t time_delta;
    if(has_looped){ 
        time_delta = time_ms - last_time_ms;
        d = ((error - last_error) / time_delta) * kd;
        i += error * time_delta * ki;
    }
    else{   //Handle first loop
        d = 0;
        i = 0;
        has_looped = 1;
    }
    
    
    
    int16_t pid = p + i + d;
    
    last_pid = pid;
    last_time_ms = time_ms;
    last_error = error;
    
    
    return pid;
}

int16_t PID_debug(int16_t target_value, int16_t current_value, uint32_t time_ms, int16_t components[]){
    
    static uint32_t last_time_ms;
    static int16_t last_error;
    
    //Only allow positive delta
    if(time_ms < last_time_ms){
        last_time_ms = time_ms;
        return last_pid;
    }
    else if(time_ms == last_time_ms){
        return last_pid; 
    }
            
    int16_t error = target_value - current_value;
    
    int16_t p = error * kp;
    
    int16_t d;
    uint16_t time_delta;
    if(has_looped){ //Handle first loop
        time_delta = time_ms - last_time_ms;
        d = ((error - last_error) / time_delta) * kd;
        i += error * time_delta * ki;
    }
    else{
        d = 0;
        i = 0;
        has_looped = 1;
    }
    
    
    
    int16_t pid = p + i + d;
    
    last_pid = pid;
    last_time_ms = time_ms;
    last_error = error;
    
    components[0] = p;
    components[1] = i;
    components[2] = d;
    
    return pid;
}