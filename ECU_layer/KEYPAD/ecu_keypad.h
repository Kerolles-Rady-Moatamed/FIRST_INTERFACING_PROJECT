/* 
 * File:   ecu_keypad.h
 * Author: DELL
 *
 * Created on December 22, 2023, 12:37 AM
 */

#ifndef ECU_KEYPAD_H
#define	ECU_KEYPAD_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/Hal_gpio.h"
#include "ecu_keypad_cfg.h"

/*Section : Macro Declarations*/
#define KEYPAD_ROWS 4
#define KEYPAD_COLUMNS 4

/*Section : Macro Functions Declarations*/

/*Section : Data Type Declarations*/
typedef struct{
    pin_config_t keypad_rows_pins[KEYPAD_ROWS];
    pin_config_t keypad_columns_pins[KEYPAD_ROWS];
}keypad_t;

/*Section : Functions Declarations*/
std_ReturnType keypad_intialize(const keypad_t *keypad);
std_ReturnType keypad_get_value(const keypad_t *keypad, uint8 *value);

#endif	/* ECU_KEYPAD_H */

