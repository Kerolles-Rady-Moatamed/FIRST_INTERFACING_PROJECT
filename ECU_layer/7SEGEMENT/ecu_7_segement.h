/* 
 * File:   ecu_7_segement.h
 * Author: DELL
 *
 * Created on December 21, 2023, 3:58 AM
 */

#ifndef ECU_7_SEGEMENT_H
#define	ECU_7_SEGEMENT_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/Hal_gpio.h"
#include "ecu_7_segement_cfg.h"

/*Section : Macro Declarations*/
#define SEGMENT_PIN0 0
#define SEGMENT_PIN1 1
#define SEGMENT_PIN2 2
#define SEGMENT_PIN3 3

/*Section : Macro Functions Declarations*/

/*Section : Data Type Declarations*/
typedef enum{
    SEGMENT_COMMON_ANODE,
    SEGMENT_COMMON_CATHODE
}segment_type_t;

typedef struct{
    pin_config_t segment_pins[4];
    segment_type_t segment_type;
}segment_t;

/*Section : Functions Declarations*/
std_ReturnType seven_segment_intialize(const segment_t *segment);
std_ReturnType seven_segment_write_number(const segment_t *segment, uint8 number);

#endif	/* ECU_7_SEGEMENT_H */

