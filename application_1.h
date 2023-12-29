/* 
 * File:   application_1.h
 * Author: DELL
 *
 * Created on December 9, 2023, 4:52 AM
 */

#ifndef APPLICATION_1_H
#define	APPLICATION_1_H

/*Section : Includes*/
#include "ECU_layer/ecu_layer_init.h"
#include "MCAL_layer/interrupt/mcal_external_interrupt.h"
#include "MCAL_layer/EEPROM/hal_eeprom.h"


/*Section : Macro Declarations*/

/*Section : Macro Functions Declarations*/

/*Section : Data Type Declarations*/

//extern keypad_t keypad1;

extern chr_lcd_4bit_t lcd1;
extern keypad_t keypad1;
extern dc_motor_t motor1;
extern dc_motor_t motor2;
extern pin_config_t bazzer;

/*
extern led_t led1;
extern led_t led2;
extern led_t led3;
extern led_t led4;
extern led_t led5;
extern led_t led6;
*/ 
extern led_t led7;



/*Section : Functions Declarations*/
void application_initialize(void);
void Int0_APP_ISR(void);
void Int1_APP_ISR(void);
void Int2_APP_ISR(void);
//===============================
void RB4_Int_APP_ISR_HIGH(void);
void RB4_Int_APP_ISR_LOW(void);

void RB5_Int_APP_ISR_HIGH(void);
void RB5_Int_APP_ISR_LOW(void);

void RB6_Int_APP_ISR_HIGH(void);
void RB6_Int_APP_ISR_LOW(void);

void RB7_Int_APP_ISR_HIGH(void);
void RB7_Int_APP_ISR_LOW(void);
//===============================
void fan(void);


#endif	/* APPLICATION_1_H */

