/* 
 * File:   hal_eeprom.h
 * Author: DELL
 *
 * Created on December 27, 2023, 5:06 AM
 */

#ifndef HAL_EEPROM_H
#define	HAL_EEPROM_H

/*Section : Includes*/
#include "../mcal_std_types.h"
#include "../proc/pic18f4620.h"
#include "../interrupt/mcal_internal_interrupt.h"

/*Section : Macro Declarations*/

/* flash program or data EEPROM memory select */
#define ACCESS_FLASH_PROGRAM_MEMORY  1
#define ACCESS_EEPROM_PROGRAM_MEMORY 0

/* flash program/data EEPROM or configuration select */
#define ACCESS_CONFIG_REGISTERS      1
#define ACCESS_FLASH_EEPROM_MEMORY   0

/* flash program/data EEPROM write enable */
#define ALLOW_WRITE_CYCLES_FLASH_EEPROM      1
#define INHITBTS_WRITE_CYCLES_FLASH_EEPROM   0

/* write control */
#define INITIATE_DATA_EEPROM_WRITE_ERASE     1
#define DATA_EEPROM_WRITE_COMPLETED          0

/* read control */
#define INITIATE_DATA_EEPROM_READ           1

/*Section : Macro Functions Declarations*/

/*Section : Data Type Declarations*/

/*Section : Functions Declarations*/
std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData);
std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData);

#endif	/* HAL_EEPROM_H */

