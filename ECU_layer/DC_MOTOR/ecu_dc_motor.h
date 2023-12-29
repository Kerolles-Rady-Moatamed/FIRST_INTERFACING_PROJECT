/* 
 * File:   ecu_dc_motor.h
 * Author: DELL
 *
 * Created on December 19, 2023, 9:42 PM
 */

#ifndef ECU_DC_MOTOR_H
#define	ECU_DC_MOTOR_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/Hal_gpio.h"
#include "ecu_dc_motor_cfg.h"

/*Section : Macro Declarations*/
#define DC_MOTOR_ON_STATUS 0x01U
#define DC_MOTOR_OFF_STATUS 0x00U

#define DC_MOTOR_PIN1 0x00U
#define DC_MOTOR_PIN2 0x01U

/*Section : Macro Functions Declarations*/

/*Section : Data Type Declarations*/
typedef struct {
    pin_config_t dc_motor[2];
}dc_motor_t;

/*Section : Functions Declarations*/
std_ReturnType dc_motor_intialize(const dc_motor_t *dc_motor);
std_ReturnType dc_motor_move_right(const dc_motor_t *dc_motor);
std_ReturnType dc_motor_move_left(const dc_motor_t *dc_motor);
std_ReturnType dc_motor_stop(const dc_motor_t *dc_motor);



#endif	/* ECU_DC_MOTOR_H */

