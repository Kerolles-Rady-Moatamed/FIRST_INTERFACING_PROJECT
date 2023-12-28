/* 
 * File:   mcal_interrupt_config.h
 * Author: DELL
 *
 * Created on December 25, 2023, 7:16 PM
 */

#ifndef MCAL_INTERRUPT_CONFIG_H
#define	MCAL_INTERRUPT_CONFIG_H

/*Section : Includes*/
#include "../proc/pic18f4620.h"
#include "../mcal_std_types.h"
#include "../GPIO/Hal_gpio.h"
#include "mcal_interrupt_gen_cfg.h"

/*Section : Macro Declarations*/
#define INTERRUPT_ENABLE             1
#define INTERRUPT_DISABLE            0
#define INTERRUPT_OCCUR              1
#define INTERRUPT_NOT_OCCUR          0
#define INTERRUPT_PRIORITY_ENABLE    1
#define INTERRUPT_PRIORITY_DISABLE   0

/*Section : Macro Functions Declarations*/

#if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE

/* this macro will enable Priority levels on interrupts */
#define INTERRUPT_PriorityLevelsEnable()  (RCONbits.IPEN = 1)
/* this macro will disable Priority levels on interrupts */
#define INTERRUPT_PriorityLevelsDisable()  (RCONbits.IPEN  = 0)

/* this macro will enable high priority global interrupts */
#define INTERRUPT_GlobalInterruptHighEnable()  (INTCONbits.GIEH = 1)
/* this macro will disable high priority global interrupts */
#define INTERRUPT_GlobalInterruptHighDisable()  (INTCONbits.GIEH = 0)

/* this macro will enable low priority global interrupts */
#define INTERRUPT_GlobalInterruptLowEnable()  (INTCONbits.GIEL = 1)
/* this macro will disable low priority global interrupts */
#define INTERRUPT_GlobalInterruptLowDisable()  (INTCONbits.GIEL = 0)

#else

/* this macro will enable global interrupts */
#define INTERRUPT_GlobalInterruptEnable()  (INTCONbits.GIE = 1)
/* this macro will disable global interrupts */
#define INTERRUPT_GlobalInterruptDisable()  (INTCONbits.GIE = 0)

/* this macro will enable Peripheral interrupts */
#define INTERRUPT_PeripheralInterruptEnable()  (INTCONbits.PEIE = 1)
/* this macro will disable Peripheral interrupts */
#define INTERRUPT_PeripheralInterruptDisable()  (INTCONbits.PEIE = 0)

#endif

/*Section : Data Type Declarations*/

typedef enum{
    INTERRUPT_LOW_PRIORITY = 0,
    INTERRUPT_HIGH_PRIORITY
}interrupt_priority_cfg;

/*Section : Functions Declarations*/

#endif	/* MCAL_INTERRUPT_CONFIG_H */

