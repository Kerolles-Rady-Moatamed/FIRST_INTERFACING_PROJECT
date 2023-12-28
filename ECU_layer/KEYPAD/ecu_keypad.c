/* 
 * File:   ecu_keypad.c
 * Author: DELL
 *
 * Created on December 22, 2023, 12:37 AM
 */

#include "ecu_keypad.h"

/*
static const uint8 btn_values[KEYPAD_ROWS][KEYPAD_COLUMNS] = {
                                                                {'7', '8', '9', '/'},
                                                                {'4', '5', '6', '*'},
                                                                {'0', '2', '3', '-'},
                                                                {'#', '0', '=', '+'},
};
*/

#define KEYPAD_ROWS_pro 4
#define KEYPAD_COLUMNS_pro 3

static const uint8 btn_values[KEYPAD_ROWS_pro][KEYPAD_COLUMNS_pro] = {
                                                                {'1', '2', '3'},
                                                                {'4', '5', '6'},
                                                                {'7', '8', '9'},
                                                                {'*', '0', '#'},
};

std_ReturnType keypad_intialize(const keypad_t *keypad){
    std_ReturnType ret = E_NOT_OK;
    
    uint8 rows_counter = ZERO_INIT;
    uint8 columns_counter = ZERO_INIT;
    
    if(NULL == keypad)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(rows_counter = ZERO_INIT; rows_counter < KEYPAD_ROWS; rows_counter++){
            ret = gpio_pin_intialize(&(keypad->keypad_rows_pins[rows_counter]));
        }
        for(columns_counter = ZERO_INIT; columns_counter < KEYPAD_COLUMNS; columns_counter++){
            ret = gpio_pin_direction_intialize(&(keypad->keypad_columns_pins[columns_counter]));
        }
    }
    
    return ret;
}

std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value){
    std_ReturnType ret = E_NOT_OK;
    
    uint8 rows_counter = ZERO_INIT;
    uint8 columns_counter = ZERO_INIT;
    uint8 counter = ZERO_INIT;
    logic_t column_logic = ZERO_INIT;
   
    if(NULL == keypad || NULL == value)
    {
        ret = E_NOT_OK;
    }
    else
    {
        for(rows_counter = ZERO_INIT; rows_counter < KEYPAD_ROWS; rows_counter++){
            for(counter = ZERO_INIT; counter < KEYPAD_ROWS; counter++){
                ret = gpio_pin_write_logic(&(keypad->keypad_rows_pins[counter]), GPIO_LOW);
            }
            ret = gpio_pin_write_logic(&(keypad->keypad_rows_pins[rows_counter]), GPIO_HIGH);
            for(columns_counter = ZERO_INIT; columns_counter < KEYPAD_COLUMNS; columns_counter++){
                ret = gpio_pin_read_logic(&(keypad->keypad_columns_pins[columns_counter]), &column_logic);
                if(GPIO_HIGH == column_logic){
                    *value = btn_values[rows_counter][columns_counter];
                }
            }
        }
    }
    
    return ret;
}

