/* 
 * File:   Hal_gpio.h
 * Author: KEROLLES RADY
 *
 * Created on December 9, 2023, 4:31 AM
 */

#ifndef HAL_GPIO_H
#define	HAL_GPIO_H

/*Section : Includes*/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../../device_config.h"
#include "Hal_gpio_config.h"

/*Section : Macro Declarations*/
#define BIT_MASK (uint8)1

#define PORT_PIN_MAX_NUMBER   8
#define PORT_MAX_NUMBER       5

#define PORTX_MASK            0xFF

/*Section : Macro Functions Declarations*/
#define HWREG8(_x)         (*((volatile uint8 *) (_x)))

#define SET_BIT(REG_ADDR, BIT_POSN)    (REG_ADDR |= (BIT_MASK << BIT_POSN))
#define CLEAR_BIT(REG_ADDR, BIT_POSN)  (REG_ADDR &= ~(BIT_MASK << BIT_POSN))
#define TOGGLE_BIT(REG_ADDR, BIT_POSN) (REG_ADDR ^= (BIT_MASK << BIT_POSN))

#define READ_BIT(REG_ADDR, BIT_POSN)        ((REG_ADDR >> BIT_POSN) & BIT_MASK)

/*Section : Data Type Declarations*/
typedef enum{
    GPIO_LOW = 0,
    GPIO_HIGH
}logic_t;

typedef enum{
    GPIO_DIRECTION_OUTPUT = 0,
    GPIO_DIRECTION_INPUT
}direction_t;

typedef enum{
    GPIO_PIN0 = 0,
    GPIO_PIN1 = 1,
    GPIO_PIN2 = 2,
    GPIO_PIN3 = 3,
    GPIO_PIN4 = 4,
    GPIO_PIN5 = 5,
    GPIO_PIN6 = 6,
    GPIO_PIN7 = 7     
}pin_index_t;

typedef enum{
    PORTA_INDEX = 0,
    PORTB_INDEX,
    PORTC_INDEX,
    PORTD_INDEX,
    PORTE_INDEX
}port_index_t;

typedef struct{
    uint8 port : 3;       /* @ref port_index_t */
    uint8 pin : 3;        /* @ref pin_index_t */
    uint8 direction : 1;  /* @ref direction_t */
    uint8 logic : 1;      /* @ref logic_t */
}pin_config_t;

/*Section : Functions Declarations*/
std_ReturnType gpio_pin_direction_intialize(const pin_config_t *_pin_config);
std_ReturnType gpio_pin_git_direction_status(const pin_config_t *_pin_config, direction_t *direction_status);
std_ReturnType gpio_pin_write_logic(const pin_config_t *_pin_config, logic_t logic);
std_ReturnType gpio_pin_read_logic(const pin_config_t *_pin_config, logic_t *logic);
std_ReturnType gpio_pin_toggle_logic(const pin_config_t *_pin_config);
std_ReturnType gpio_pin_intialize(const pin_config_t *_pin_config);

std_ReturnType gpio_port_direction_intialize(port_index_t port, uint8 direction);
std_ReturnType gpio_port_git_direction_status(port_index_t port, uint8 *direction_status);
std_ReturnType gpio_port_write_logic(port_index_t port, uint8 logic);
std_ReturnType gpio_port_read_logic(port_index_t port, uint8 *logic);
std_ReturnType gpio_port_toggle_logic(port_index_t port);

#endif	/* HAL_GPIO_H */

