/* 
 * File:   ecu_button.h
 * Author: DELL
 *
 * Created on December 15, 2023, 9:02 PM
 */

#ifndef ECU_BUTTON_H
#define	ECU_BUTTON_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/Hal_gpio.h"
#include "ecu_button_cfg.h"

/*Section : Macro Declarations*/

/*Section : Macro Functions Declarations*/

/*Section : Data Type Declarations*/
typedef enum{
    BUTTON_PRESSED,
    BUTTON_RELEASED
}button_state_t;

typedef enum{
    BUTTON_ACTIVE_HIGH,
    BUTTON_ACTIVE_LOW
}button_active_t;

typedef struct{
    pin_config_t button_pin;
    button_state_t button_state;
    button_active_t button_connection;
}button_t;

/*Section : Functions Declarations*/
std_ReturnType button_initialize(const button_t *btn);
std_ReturnType button_read_state(const button_t *btn, button_state_t *btn_state);

#endif	/* ECU_BUTTON_H */

