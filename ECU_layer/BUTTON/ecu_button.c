/* 
 * File:   ecu_button.c
 * Author: KEROLLES RADY
 *
 * Created on December 9, 2023, 4:15 AM
 */

#include "ecu_button.h"

/**
 * @brief initialize the assigned pin to be input
 * @param btn pointer to the button configurations
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType button_initialize(const button_t *btn){
    std_ReturnType ret = E_OK;
    
    if(NULL == btn)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_direction_intialize(&(btn->button_pin));
    }
    
    return ret;
}

/**
 * @brief read the state of the button
 * @param btn pointer to the button configurations
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state){
    std_ReturnType ret = E_NOT_OK;
    logic_t pin_logic_status = GPIO_LOW;
    if(NULL == btn || NULL == btn_state)
    {
        ret = E_NOT_OK;
    }
    else
    {
        gpio_pin_read_logic(&(btn->button_pin), &pin_logic_status);
        if(BUTTON_ACTIVE_HIGH == btn->button_connection)
        {
            if(GPIO_HIGH == pin_logic_status)
            {
                *btn_state = BUTTON_PRESSED; 
            }
            else
            {
               *btn_state = BUTTON_RELEASED;
            }
        }
        else if(BUTTON_ACTIVE_LOW == btn->button_connection)
        {
            if(GPIO_LOW == pin_logic_status)
            {
                *btn_state = BUTTON_PRESSED; 
            }
            else
            {
                *btn_state = BUTTON_RELEASED;
            }
        }
        else
        {
            
        }
        ret = E_OK;
    }
    
    return ret;
}