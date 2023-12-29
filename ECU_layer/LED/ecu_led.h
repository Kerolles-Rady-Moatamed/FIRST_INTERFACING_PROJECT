/* 
 * File:   ecu_led.h
 * Author: KEROLLES RADY
 *
 * Created on December 9, 2023, 4:46 AM
 */

#ifndef ECU_LED_H
#define	ECU_LED_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/Hal_gpio.h"
#include "ecu_led_cfg.h"

/*Section : Macro Declarations*/

/*Section : Macro Functions Declarations*/

/*Section : Data Type Declarations*/
typedef enum{
    LED_OFF,
    LED_ON
}led_status_t;

typedef struct{
    uint8 port_name : 4;       /* @ref port_index_t */
    uint8 pin : 3;             /* @ref pin_index_t */
    uint8 led_status : 1;      /* @ref led_status_t */
}led_t;

/*Section : Functions Declarations*/
std_ReturnType led_initialize(const led_t *led);
std_ReturnType led_turn_on(const led_t *led);
std_ReturnType led_turn_off(const led_t *led);
std_ReturnType led_turn_toggle(const led_t *led);

#endif	/* ECU_LED_H */

