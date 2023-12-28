/* 
 * File:   ecu_relay.h
 * Author: DELL
 *
 * Created on December 18, 2023, 5:58 PM
 */

#ifndef ECU_RELAY_H
#define	ECU_RELAY_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/Hal_gpio.h"
#include "ecu_relay_cfg.h"

/*Section : Macro Declarations*/
#define RELAY_ON_STATUS 0x01U
#define RELAY_OFF_STATUS 0x00U

/*Section : Macro Functions Declarations*/

/*Section : Data Type Declarations*/
typedef struct {
    pin_config_t relay_pin;
}relay_t;

/*Section : Functions Declarations*/
std_ReturnType relay_intialize(const relay_t *relay);
std_ReturnType relay_turn_on(const relay_t *relay);
std_ReturnType relay_turn_off(const relay_t *relay);

#endif	/* ECU_RELAY_H */

