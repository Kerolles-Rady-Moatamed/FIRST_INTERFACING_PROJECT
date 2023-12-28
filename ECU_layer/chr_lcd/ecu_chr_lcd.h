/* 
 * File:   ecu_chr_lcd.h
 * Author: DELL
 *
 * Created on December 23, 2023, 2:10 AM
 */

#ifndef ECU_CHR_LCD_H
#define	ECU_CHR_LCD_H

/*Section : Includes*/
#include "../../MCAL_layer/GPIO/Hal_gpio.h"
#include "ecu_chr_lcd_cfg.h"

/*Section : Macro Declarations*/
#define _LCD_CLEAR                    0x01
#define _LCD_RETURN_HOME              0x02
#define _LCD_ENTRY_MODE               0x06
#define _LCD_CURSOR_OFF_DISPLAY_ON    0x0C
#define _LCD_CURSOR_OFF_DISPLAY_OFF   0x08
#define _LCD_CURSOR_ON_BLINK_ON       0x0F
#define _LCD_CURSOR_ON_BLINK_OFF      0x0E
#define _LCD_DISPLAY_SHIFT_RIGHT      0x1C
#define _LCD_DISPLAY_SHIFT_LEFT       0x18
#define _LCD_8BIT_MODE_2_LINE         0x38
#define _LCD_4BIT_MODE_2_LINE         0x28
#define _LCD_CGRAM_START              0x40
#define _LCD_DDRAM_START              0x80

#define ROW1 1
#define ROW2 2
#define ROW3 3
#define ROW4 4


/*Section : Macro Functions Declarations*/

/*Section : Data Type Declarations*/
typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[4];
}chr_lcd_4bit_t;

typedef struct {
    pin_config_t lcd_rs;
    pin_config_t lcd_en;
    pin_config_t lcd_data[8];
}chr_lcd_8bit_t;

/*Section : Functions Declarations*/
std_ReturnType lcd_4bit_intialize(const chr_lcd_4bit_t *lcd);
std_ReturnType lcd_4bit_send_comand(const chr_lcd_4bit_t *lcd, uint8 command);
std_ReturnType lcd_4bit_send_char_data(const chr_lcd_4bit_t *lcd, uint8 data);
std_ReturnType lcd_4bit_send_char_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 data);
std_ReturnType lcd_4bit_send_str_data(const chr_lcd_4bit_t *lcd, uint8 *str);
std_ReturnType lcd_4bit_send_str_data_pos(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, uint8 *str);
std_ReturnType lcd_4bit_send_custom_char(const chr_lcd_4bit_t *lcd, uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos);

std_ReturnType lcd_8bit_intialize(const chr_lcd_8bit_t *lcd);
std_ReturnType lcd_8bit_send_comand(const chr_lcd_8bit_t *lcd, uint8 command);
std_ReturnType lcd_8bit_send_char_data(const chr_lcd_8bit_t *lcd, uint8 data);
std_ReturnType lcd_8bit_send_char_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 data);
std_ReturnType lcd_8bit_send_str_data(const chr_lcd_8bit_t *lcd, uint8 *str);
std_ReturnType lcd_8bit_send_str_data_pos(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, uint8 *str);
std_ReturnType lcd_8bit_send_custom_char(const chr_lcd_8bit_t *lcd, uint8 row, uint8 column, const uint8 chr[], uint8 mem_pos);

std_ReturnType convert_byte_to_string(uint8 value, uint8 *str);
std_ReturnType convert_short_to_string(uint16 value, uint8 *str);
std_ReturnType convert_int_to_string(uint32 value, uint8 *str);


#endif	/* ECU_CHR_LCD_H */

