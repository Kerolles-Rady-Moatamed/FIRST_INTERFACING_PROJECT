/* 
 * File:   ecu_chr_lcd.c
 * Author: DELL
 *
 * Created on December 23, 2023, 2:11 AM
 */

#include "ecu_chr_lcd.h"

static std_ReturnType lcd_send_4bits(const chr_lcd_8bit_t *lcd, uint8 data_command);
static std_ReturnType lcd_4bits_send_enable_signal(const chr_lcd_4bit_t *lcd);
static std_ReturnType lcd_8bits_send_enable_signal(const chr_lcd_8bit_t *lcd);
static std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column);
static std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column);

std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd){
    std_ReturnType ret = E_NOT_OK;
    uint8 l_data_pins_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(l_data_pins_counter = ZERO_INIT; l_data_pins_counter < 4; l_data_pins_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_4bit_send_comand(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_4bit_send_comand(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_4bit_send_comand(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_4bit_send_comand(lcd, _LCD_CLEAR);
        ret = lcd_4bit_send_comand(lcd, _LCD_RETURN_HOME);
        ret = lcd_4bit_send_comand(lcd, _LCD_ENTRY_MODE);
        ret = lcd_4bit_send_comand(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_4bit_send_comand(lcd, _LCD_4BIT_MODE_2_LINE);
        ret = lcd_4bit_send_comand(lcd, 0x80);
        
    }
    
    return ret;
}

std_ReturnType lcd_4bit_send_comand(const chr_lcd_4bit_t *lcd, uint8 command){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        ret = lcd_send_4bits(lcd, command >> 4);
        ret = lcd_4bits_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, command);
        ret = lcd_4bits_send_enable_signal(lcd);
        
    }
    
    return ret;
}

std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        ret = lcd_send_4bits(lcd, data >> 4);
        ret = lcd_4bits_send_enable_signal(lcd);
        ret = lcd_send_4bits(lcd, data);
        ret = lcd_4bits_send_enable_signal(lcd);
    }
    
    return ret;
}

std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd, row, column);
        ret = lcd_4bit_send_char_data(lcd, data);
    }
    
    return ret;
}

std_ReturnType lcd_4bit_send_str_data(const chr_lcd_4bit_t *lcd, uint8 *str){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    
    return ret;
}

std_ReturnType lcd_4bit_send_str_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_set_cursor(lcd, row, column);
        while(*str)
        {
            ret = lcd_4bit_send_char_data(lcd, *str++);
        }
    }
    
    return ret;
}

std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos){
    std_ReturnType ret = E_NOT_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_4bit_send_comand(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter = ZERO_INIT; lcd_counter < 8; lcd_counter++){
            ret = lcd_4bit_send_char_data(lcd, chr[lcd_counter]);
        }
        ret = lcd_4bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    
    return ret;
}






std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd){
    std_ReturnType ret = E_NOT_OK;
    uint8 l_data_pins_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_intialize(&(lcd->lcd_rs));
        ret = gpio_pin_intialize(&(lcd->lcd_en));
        for(l_data_pins_counter = ZERO_INIT; l_data_pins_counter < 8; l_data_pins_counter++)
        {
            ret = gpio_pin_intialize(&(lcd->lcd_data[l_data_pins_counter]));
        }
        __delay_ms(20);
        ret = lcd_8bit_send_comand(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_ms(5);
        ret = lcd_8bit_send_comand(lcd, _LCD_8BIT_MODE_2_LINE);
        __delay_us(150);
        ret = lcd_8bit_send_comand(lcd, _LCD_8BIT_MODE_2_LINE);
        
        ret = lcd_8bit_send_comand(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_comand(lcd, _LCD_CLEAR);
        ret = lcd_8bit_send_comand(lcd, _LCD_RETURN_HOME);
        ret = lcd_8bit_send_comand(lcd, _LCD_ENTRY_MODE);
        ret = lcd_8bit_send_comand(lcd, _LCD_CURSOR_OFF_DISPLAY_ON);
        ret = lcd_8bit_send_comand(lcd, _LCD_8BIT_MODE_2_LINE);
        ret = lcd_8bit_send_comand(lcd, 0x80);
    }
    
    return ret;
}

std_ReturnType lcd_8bit_send_comand(const chr_lcd_8bit_t *lcd, uint8 command){
    std_ReturnType ret = E_NOT_OK;
    uint8 pins_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_LOW);
        
        for(pins_counter = ZERO_INIT; pins_counter < 8; pins_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[pins_counter]), (command >> pins_counter) & (uint8)0x01);
        }
        
        ret = lcd_8bits_send_enable_signal(lcd);
    }
    
    return ret;
}

std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data){
    std_ReturnType ret = E_NOT_OK;
    uint8 pins_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = gpio_pin_write_logic(&(lcd->lcd_rs), GPIO_HIGH);
        
        for(pins_counter = ZERO_INIT; pins_counter < 8; pins_counter++){
            ret = gpio_pin_write_logic(&(lcd->lcd_data[pins_counter]), (data >> pins_counter) & (uint8)0x01);
        }
        
        ret = lcd_8bits_send_enable_signal(lcd);
    }
    
    return ret;
}

std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor(lcd, row, column);
        ret = lcd_8bit_send_char_data(lcd, data);
    }
    
    return ret;
}

std_ReturnType lcd_8bit_send_str_data(const chr_lcd_8bit_t *lcd, uint8 *str){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    
    return ret;
}

std_ReturnType lcd_8bit_send_str_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_set_cursor(lcd, row, column);
        while(*str)
        {
            ret = lcd_8bit_send_char_data(lcd, *str++);
        }
    }
    
    return ret;
}

std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, 
                                         uint8 column, const uint8 chr[], uint8 mem_pos){
    std_ReturnType ret = E_NOT_OK;
    uint8 lcd_counter = ZERO_INIT;
    if(NULL == lcd)
    {
        ret = E_NOT_OK;
    }
    else
    {
        ret = lcd_8bit_send_comand(lcd, (_LCD_CGRAM_START+(mem_pos*8)));
        for(lcd_counter = ZERO_INIT; lcd_counter < 8; lcd_counter++){
            ret = lcd_8bit_send_char_data(lcd, chr[lcd_counter]);
        }
        ret = lcd_8bit_send_char_data_pos(lcd, row, column, mem_pos);
    }
    
    return ret;
}




std_ReturnType convert_byte_to_string(uint8 value, uint8 *str){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, "\0", 4);
        sprintf(str, "%i", value);
    }
    
    return ret;
}

std_ReturnType convert_short_to_string(uint16 value, uint8 *str){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, "\0", 6);
        sprintf(str, "%i", value);
    }
    
    return ret;
}

std_ReturnType convert_int_to_string(uint32 value, uint8 *str){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == str)
    {
        ret = E_NOT_OK;
    }
    else
    {
        memset(str, "\0", 11);
        sprintf(str, "%i", value);
    }
    
    return ret;
}


static std_ReturnType lcd_send_4bits(const chr_lcd_8bit_t *lcd, uint8 data_command){
    std_ReturnType ret = E_NOT_OK;
    
    ret = gpio_pin_write_logic(&(lcd->lcd_data[0]), (data_command >> 0) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[1]), (data_command >> 1) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[2]), (data_command >> 2) & (uint8)0x01);
    ret = gpio_pin_write_logic(&(lcd->lcd_data[3]), (data_command >> 3) & (uint8)0x01);
    
    return ret;
}

static std_ReturnType lcd_4bits_send_enable_signal(const chr_lcd_4bit_t *lcd){
    std_ReturnType ret = E_NOT_OK;
    
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    
    return ret;
}

static std_ReturnType lcd_8bits_send_enable_signal(const chr_lcd_8bit_t *lcd){
    std_ReturnType ret = E_NOT_OK;
    
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_HIGH);
    __delay_us(5);
    ret = gpio_pin_write_logic(&(lcd->lcd_en), GPIO_LOW);
    
    return ret;
}

static std_ReturnType lcd_8bit_set_cursor(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column){
    std_ReturnType ret = E_NOT_OK;
    column--;
    switch(row)
    {
        case ROW1: ret = lcd_8bit_send_comand(lcd, (0x80 + column)); break;
        case ROW2: ret = lcd_8bit_send_comand(lcd, (0xc0 + column)); break;
        case ROW3: ret = lcd_8bit_send_comand(lcd, (0x94 + column)); break;
        case ROW4: ret = lcd_8bit_send_comand(lcd, (0xd4 + column)); break;
        default : ;
    }
    
    return ret;
}

static std_ReturnType lcd_4bit_set_cursor(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column){
    std_ReturnType ret = E_NOT_OK;
    column--;
    switch(row)
    {
        case ROW1: ret = lcd_4bit_send_comand(lcd, (0x80 + column)); break;
        case ROW2: ret = lcd_4bit_send_comand(lcd, (0xc0 + column)); break;
        case ROW3: ret = lcd_4bit_send_comand(lcd, (0x94 + column)); break;
        case ROW4: ret = lcd_4bit_send_comand(lcd, (0xd4 + column)); break;
        default : ;
    }
    
    return ret;
}
