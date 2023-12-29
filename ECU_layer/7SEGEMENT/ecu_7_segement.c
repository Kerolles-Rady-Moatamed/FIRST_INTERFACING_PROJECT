/* 
 * File:   ecu_7_segement.c
 * Author: DELL
 *
 * Created on December 21, 2023, 3:58 AM
 */

#include "ecu_7_segement.h"

std_ReturnType seven_segment_intialize(const segment_t *segment){
    std_ReturnType ret = E_NOT_OK;
   
    if(NULL == segment)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(segment->segment_pins[SEGMENT_PIN0]));
        ret = gpio_pin_intialize(&(segment->segment_pins[SEGMENT_PIN1]));
        ret = gpio_pin_intialize(&(segment->segment_pins[SEGMENT_PIN2]));
        ret = gpio_pin_intialize(&(segment->segment_pins[SEGMENT_PIN3]));
    }
    
    return ret;
}

std_ReturnType seven_segment_write_number(const segment_t *segment, uint8 number){
    std_ReturnType ret = E_NOT_OK;
   
    if(NULL == segment && number < 10)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN0]), number & 0x01);
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN1]), (number>>1) & 0x01);
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN2]), (number>>2) & 0x01);
        ret = gpio_pin_write_logic(&(segment->segment_pins[SEGMENT_PIN3]), (number>>3) & 0x01);
    }
    
    return ret;
}
