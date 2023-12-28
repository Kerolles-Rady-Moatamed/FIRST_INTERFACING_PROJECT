/* 
 * File:   application_1.c
 * Author: KEROLLES RADY
 *
 * Created on December 9, 2023, 4:15 AM
 */

#include "application_1.h" 



interrupt_INTx_t int0_obj = {
    .EXT_InterruptHandler = Int0_APP_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT0,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN0,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_INTx_t int1_obj = {
    .EXT_InterruptHandler = Int1_APP_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_LOW_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT1,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN1,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_INTx_t int2_obj = {
    .EXT_InterruptHandler = Int2_APP_ISR,
    .edge = INTERRUPT_RISING_EDGE,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .source = INTERRUPT_EXTERNAL_INT2,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN2,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

//====================================================================

interrupt_RBx_t RB4_int_obj = {
    .EXT_InterruptHandler_HIGH = RB4_Int_APP_ISR_HIGH,
    .EXT_InterruptHandler_LOW = RB4_Int_APP_ISR_LOW,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN4,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t RB5_int_obj = {
    .EXT_InterruptHandler_HIGH = RB5_Int_APP_ISR_HIGH,
    .EXT_InterruptHandler_LOW = RB5_Int_APP_ISR_LOW,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN5,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t RB6_int_obj = {
    .EXT_InterruptHandler_HIGH = RB6_Int_APP_ISR_HIGH,
    .EXT_InterruptHandler_LOW = RB6_Int_APP_ISR_LOW,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN6,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};

interrupt_RBx_t RB7_int_obj = {
    .EXT_InterruptHandler_HIGH = RB7_Int_APP_ISR_HIGH,
    .EXT_InterruptHandler_LOW = RB7_Int_APP_ISR_LOW,
    .priority = INTERRUPT_HIGH_PRIORITY,
    .mcu_pin.port = PORTB_INDEX,
    .mcu_pin.pin = GPIO_PIN7,
    .mcu_pin.direction = GPIO_DIRECTION_INPUT
};



uint8 Heart[] = {
  0x00,
  0x0A,
  0x15,
  0x11,
  0x0A,
  0x04,
  0x00,
  0x00
};

uint8 face[] = {
  0x00,
  0x00,
  0x0A,
  0x00,
  0x11,
  0x0E,
  0x00,
  0x00
};

std_ReturnType ret = E_NOT_OK;

volatile uint8 keypad_value = ZERO_INIT;
volatile uint8 password_keypad[6] = {' ', ' ', ' ', ' ', ' ', ' '};
volatile uint8 limit_switch = ZERO_INIT;
volatile uint8 key = 0;
const uint8 password[6] = {'6', '5', '4', '3', '2', '1'};
volatile uint8 flag = 0;
volatile uint8 kero = ' ';
int i = 6;
uint8 swap;
uint8 fan_val;

int main() {
    std_ReturnType ret = E_NOT_OK;
    
    application_initialize();
    
    fan();
    lcd_4bit_send_str_data_pos(&lcd1, 2, 6, "WELLCOME");
    lcd_4bit_send_str_data_pos(&lcd1, 3, 6, "GOOD DAY");
    lcd_4bit_send_custom_char(&lcd1, 2, 16, face, 0);
    lcd_4bit_send_custom_char(&lcd1, 2, 17, face, 0);
    lcd_4bit_send_custom_char(&lcd1, 2, 18, face, 0);
    lcd_4bit_send_custom_char(&lcd1, 2, 19, face, 0);
    
    lcd_4bit_send_custom_char(&lcd1, 3, 16, Heart, 1);
    lcd_4bit_send_custom_char(&lcd1, 3, 17, Heart, 1);
    lcd_4bit_send_custom_char(&lcd1, 3, 18, Heart, 1);
    lcd_4bit_send_custom_char(&lcd1, 3, 19, Heart, 1);

    while(1)
    {  
        ret = keypad_get_value(&keypad1, &keypad_value);
        if(keypad_value == '*' || keypad_value == '#'){
            fan_val = keypad_value;
            keypad_value = swap;
        }
        else{
            swap = keypad_value;
        }

        if('7' == keypad_value)
        {
            lcd_4bit_send_comand(&lcd1, _LCD_CLEAR);
            //fan();
            lcd_4bit_send_str_data_pos(&lcd1, 1, 2, "It is privet floor");
            lcd_4bit_send_str_data_pos(&lcd1, 2, 2, "Inter the password");
            lcd_4bit_send_str_data_pos(&lcd1, 3, 1, "                     ");
            while(i > 0){
                while(password_keypad[i-1] == ' '){
                    kero = ' ';
                    for(int k = 0; k < 350; k++){
                        ret = keypad_get_value(&keypad1, &kero);
                        lcd_4bit_send_str_data_pos(&lcd1, 3, 13-i, &kero);
                    }                   
                    password_keypad[i-1] = kero;
                }

                if(password_keypad[i-1] != ' ')
                {
                    i--;
                }
            }

            for(int j = 0; j < 6; j++){
               
                if(password_keypad[j] == password[j]){
                    key++;
                }
            }
            
            
            for(int y = 0; y < 6; y++){
                password_keypad[y] = ' ';
            }
            
            if(6 == key){
                lcd_4bit_send_str_data_pos(&lcd1, 4, 2, "correct password");
                __delay_ms(1000);
            }
            
            if(6 == key && limit_switch < '7'){               
                lcd_4bit_send_comand(&lcd1, _LCD_CLEAR);
                fan();
                lcd_4bit_send_str_data_pos(&lcd1, 1, 9, "Up");
                lcd_4bit_send_str_data_pos(&lcd1, 2, 9, "To");
                lcd_4bit_send_str_data_pos(&lcd1, 3, 3, "the Floor No: 7");
                lcd_4bit_send_str_data_pos(&lcd1, 4, 9, "Up");
                __delay_ms(1000);
                ret = dc_motor_move_right(&motor1);
            }

            else if(key != 6 && limit_switch != '7'){
                key = 0;
                i = 6;
                lcd_4bit_send_comand(&lcd1, _LCD_CLEAR);
                fan();
                lcd_4bit_send_str_data_pos(&lcd1, 2, 3, "Wrong password");
                lcd_4bit_send_str_data_pos(&lcd1, 3, 6, "try again");
                __delay_ms(1000);
            }
            else{}
        }
        else if(keypad_value > '0' && keypad_value < '7'){
            if(keypad_value > limit_switch){
                lcd_4bit_send_comand(&lcd1, _LCD_CLEAR);
                fan();
                lcd_4bit_send_str_data_pos(&lcd1, 1, 9, "Up");
                lcd_4bit_send_str_data_pos(&lcd1, 2, 9, "To");
                lcd_4bit_send_str_data_pos(&lcd1, 3, 3, "the Floor No:");
                lcd_4bit_send_str_data_pos(&lcd1, 4, 9, "Up");
                lcd_4bit_send_str_data_pos(&lcd1, 3, 17, &keypad_value);
                __delay_ms(1000);
                ret = dc_motor_move_right(&motor1);
            }
            else if(keypad_value < limit_switch){
                lcd_4bit_send_comand(&lcd1, _LCD_CLEAR);
                fan();
                lcd_4bit_send_str_data_pos(&lcd1, 1, 8, "Down");
                lcd_4bit_send_str_data_pos(&lcd1, 2, 9, "To");
                lcd_4bit_send_str_data_pos(&lcd1, 3, 3, "the Floor No:");
                lcd_4bit_send_str_data_pos(&lcd1, 4, 8, "Down");
                lcd_4bit_send_str_data_pos(&lcd1, 3, 17, &keypad_value);
                __delay_ms(1000);
                ret = dc_motor_move_left(&motor1);
            }
            else{
                lcd_4bit_send_comand(&lcd1, _LCD_CLEAR);
                fan();
                lcd_4bit_send_str_data_pos(&lcd1, 2, 5, "You Are On");
                lcd_4bit_send_str_data_pos(&lcd1, 3, 3, "the Floor No:");
                lcd_4bit_send_str_data_pos(&lcd1, 3, 17, &keypad_value);
                __delay_ms(1000);
                ret = dc_motor_stop(&motor1);
            }
        }
        else{
            ret = led_turn_toggle(&led7);
            __delay_ms(250);
        }
        if(fan_val == '*'){
            ret = dc_motor_move_right(&motor2);
            flag = 1;
        }
        else if(fan_val == '#'){
            ret = dc_motor_stop(&motor2);
            flag = 0;
        }
        else{
            /* no thing */
        }
        
  
    }  
    return (EXIT_SUCCESS);
}


void application_initialize(void)
{
    std_ReturnType ret = E_NOT_OK;
    ecu_layer_initialize();
    ret = Interrupt_INTx_Init(&int0_obj);
    ret = Interrupt_INTx_Init(&int1_obj);
    ret = Interrupt_INTx_Init(&int2_obj);
    //=========================================
    ret = Interrupt_RBx_Init(&RB4_int_obj);
    ret = Interrupt_RBx_Init(&RB5_int_obj);
    ret = Interrupt_RBx_Init(&RB6_int_obj);
    ret = Interrupt_RBx_Init(&RB7_int_obj);
}

void Int0_APP_ISR(void){
    limit_switch = '7';
    keypad_value = '0';
    i = 6;
    key = 0;
    ret = dc_motor_stop(&motor1);
    lcd_4bit_send_comand(&lcd1, _LCD_CLEAR);
    fan();
    lcd_4bit_send_str_data_pos(&lcd1, 2, 5, "You Are On");
    lcd_4bit_send_str_data_pos(&lcd1, 3, 3, "the Floor No: 7");
    __delay_ms(1000);
}
void Int1_APP_ISR(void){
    limit_switch = '6';
}
void Int2_APP_ISR(void){
    limit_switch = '5';
}

//===================================================

void RB4_Int_APP_ISR_HIGH(void){
    limit_switch = '4';
}
void RB4_Int_APP_ISR_LOW(void){
    
}


void RB5_Int_APP_ISR_HIGH(void){
    limit_switch = '3';
}
void RB5_Int_APP_ISR_LOW(void){
    
}

void RB6_Int_APP_ISR_HIGH(void){
    limit_switch = '2';
}
void RB6_Int_APP_ISR_LOW(void){
   
}

void RB7_Int_APP_ISR_HIGH(void){
    limit_switch = '1';
}
void RB7_Int_APP_ISR_LOW(void){
    
}

void fan(void){
    if(flag == 1){
        lcd_4bit_send_str_data_pos(&lcd1, 1, 1, " * On");
    }
    else if (flag == 0){
        lcd_4bit_send_str_data_pos(&lcd1, 1, 1, " * Off");
    }
    else{
        /* no thing */
    }
}
