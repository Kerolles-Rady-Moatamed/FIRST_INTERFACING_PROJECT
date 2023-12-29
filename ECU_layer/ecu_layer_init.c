/* 
 * File:   ecu_layer_init.c
 * Author: DELL
 *
 * Created on December 22, 2023, 1:15 AM
 */

#include "ecu_layer_init.h"

chr_lcd_4bit_t lcd1 = {
    .lcd_rs.port = PORTC_INDEX,
    .lcd_rs.pin = GPIO_PIN0,
    .lcd_rs.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_rs.logic = GPIO_LOW,
    .lcd_en.port = PORTC_INDEX,
    .lcd_en.pin = GPIO_PIN1,
    .lcd_en.direction = GPIO_DIRECTION_OUTPUT,
    .lcd_en.logic = GPIO_LOW,
    .lcd_data[0].port = PORTC_INDEX,
    .lcd_data[0].pin = GPIO_PIN2,
    .lcd_data[0].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[0].logic = GPIO_LOW,
    .lcd_data[1].port = PORTC_INDEX,
    .lcd_data[1].pin = GPIO_PIN3,
    .lcd_data[1].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[1].logic = GPIO_LOW,
    .lcd_data[2].port = PORTC_INDEX,
    .lcd_data[2].pin = GPIO_PIN4,
    .lcd_data[2].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[2].logic = GPIO_LOW,
    .lcd_data[3].port = PORTC_INDEX,
    .lcd_data[3].pin = GPIO_PIN5,
    .lcd_data[3].direction = GPIO_DIRECTION_OUTPUT,
    .lcd_data[3].logic = GPIO_LOW,
};

keypad_t keypad1 = {
    .keypad_rows_pins[0].port = PORTD_INDEX,
    .keypad_rows_pins[0].pin = GPIO_PIN0,
    .keypad_rows_pins[0].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[0].logic = GPIO_LOW,
    .keypad_rows_pins[1].port = PORTD_INDEX,
    .keypad_rows_pins[1].pin = GPIO_PIN1,
    .keypad_rows_pins[1].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[1].logic = GPIO_LOW,
    .keypad_rows_pins[2].port = PORTD_INDEX,
    .keypad_rows_pins[2].pin = GPIO_PIN2,
    .keypad_rows_pins[2].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[2].logic = GPIO_LOW,
    .keypad_rows_pins[3].port = PORTD_INDEX,
    .keypad_rows_pins[3].pin = GPIO_PIN3,
    .keypad_rows_pins[3].direction = GPIO_DIRECTION_OUTPUT,
    .keypad_rows_pins[3].logic = GPIO_LOW,
    
    .keypad_columns_pins[0].port = PORTD_INDEX,
    .keypad_columns_pins[0].pin = GPIO_PIN4,
    .keypad_columns_pins[0].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[0].logic = GPIO_LOW,
    .keypad_columns_pins[1].port = PORTD_INDEX,
    .keypad_columns_pins[1].pin = GPIO_PIN5,
    .keypad_columns_pins[1].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[1].logic = GPIO_LOW,
    .keypad_columns_pins[2].port = PORTD_INDEX,
    .keypad_columns_pins[2].pin = GPIO_PIN6,
    .keypad_columns_pins[2].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[2].logic = GPIO_LOW,
    .keypad_columns_pins[3].port = PORTD_INDEX,
    .keypad_columns_pins[3].pin = GPIO_PIN7,
    .keypad_columns_pins[3].direction = GPIO_DIRECTION_INPUT,
    .keypad_columns_pins[3].logic = GPIO_LOW,
};


dc_motor_t motor1 = {
    .dc_motor[0].port = PORTA_INDEX,
    .dc_motor[0].pin = GPIO_PIN0,
    .dc_motor[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[1].port = PORTA_INDEX,
    .dc_motor[1].pin = GPIO_PIN1,
    .dc_motor[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT,
};

dc_motor_t motor2 = {
    .dc_motor[0].port = PORTA_INDEX,
    .dc_motor[0].pin = GPIO_PIN2,
    .dc_motor[0].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[0].direction = GPIO_DIRECTION_OUTPUT,
    .dc_motor[1].port = PORTA_INDEX,
    .dc_motor[1].pin = GPIO_PIN3,
    .dc_motor[1].logic = DC_MOTOR_OFF_STATUS,
    .dc_motor[1].direction = GPIO_DIRECTION_OUTPUT,
};


pin_config_t bazzer = {
    .port = PORTC_INDEX,
    .pin = GPIO_PIN7,
    .direction = GPIO_DIRECTION_OUTPUT,
    .logic = GPIO_LOW
};

/*
led_t led1 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN0,
    .led_status = GPIO_LOW
};

led_t led2 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN1,
    .led_status = GPIO_LOW
};

led_t led3 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN2,
    .led_status = GPIO_LOW
};

led_t led4 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN3,
    .led_status = GPIO_LOW
};

led_t led5 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN4,
    .led_status = GPIO_LOW
};

led_t led6 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN5,
    .led_status = GPIO_LOW
};
*/
led_t led7 = {
    .port_name = PORTC_INDEX,
    .pin = GPIO_PIN7,
    .led_status = GPIO_LOW
};


void ecu_layer_initialize(void)
{
    std_ReturnType ret = E_NOT_OK;
    ret = lcd_4bit_intialize(&lcd1);
    ret = keypad_intialize(&keypad1);
    ret = dc_motor_intialize(&motor1);
    ret = dc_motor_intialize(&motor2);
    
    ret = gpio_pin_intialize(&bazzer);
    
    //ret = led_initialize(&led1);
    //ret = led_initialize(&led2);
    //ret = led_initialize(&led3);
    //ret = led_initialize(&led4);
    //ret = led_initialize(&led5);
    //ret = led_initialize(&led6);
    ret = led_initialize(&led7);
    
    
    //ret = lcd_8bit_intialize(&lcd2);
}
