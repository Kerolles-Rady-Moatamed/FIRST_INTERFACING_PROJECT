/* 
 * File:   ecu_dc_motor.c
 * Author: DELL
 *
 * Created on December 19, 2023, 9:43 PM
 */


#include "ecu_dc_motor.h"

static pin_config_t motor_pin1;
static pin_config_t motor_pin2;



std_ReturnType dc_motor_intialize(const dc_motor_t *dc_motor){
    std_ReturnType ret = E_NOT_OK;
   
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(dc_motor->dc_motor[0]));
        ret = gpio_pin_intialize(&(dc_motor->dc_motor[1]));
    }
    
    return ret;
}

std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor){
    std_ReturnType ret = E_NOT_OK;
   
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        
        gpio_pin_write_logic(&(dc_motor->dc_motor[0]), GPIO_HIGH);
        gpio_pin_write_logic(&(dc_motor->dc_motor[1]), GPIO_LOW);
    }
    
    return ret;
}

std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor){
    std_ReturnType ret = E_NOT_OK;
   
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(dc_motor->dc_motor[0]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor[1]), GPIO_HIGH);
    }
    
    return ret;
}

std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor){
    std_ReturnType ret = E_NOT_OK;
   
    if(NULL == dc_motor)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_write_logic(&(dc_motor->dc_motor[0]), GPIO_LOW);
        gpio_pin_write_logic(&(dc_motor->dc_motor[1]), GPIO_LOW);
    }
    
    return ret;
}

