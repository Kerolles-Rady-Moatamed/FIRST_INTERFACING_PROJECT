/* 
 * File:   ecu_relay.h
 * Author: DELL
 *
 * Created on December 18, 2023, 5:58 PM
 */

#include "ecu_relay.h"

/**
 * @brief initialize the assigned pin to be  OUTPUT and turn the led or off
 * @param relay pointer to the relay module configuration
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType relay_intialize(const relay_t *relay){
    std_ReturnType ret = E_NOT_OK;
   
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(relay);
    }
    
    return ret;
}

/**
 * @brief turn the relay on
 * @param relay pointer to the relay module configuration
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType relay_turn_on(const relay_t *relay){
    std_ReturnType ret = E_NOT_OK;
   
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(relay, GPIO_HIGH);
        ret = E_OK;
    }
    
    return ret;
}

/**
 * @brief turn the relay off
 * @param relay pointer to the relay module configuration
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType relay_turn_off(const relay_t *relay){
    std_ReturnType ret = E_NOT_OK;
   
    if(NULL == relay)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(relay, GPIO_LOW);
        ret = E_OK;
    }
    
    return ret;
}

