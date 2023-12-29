/* 
 * File:   hal_eeprom.c
 * Author: DELL
 *
 * Created on December 27, 2023, 5:06 AM
 */

#include "hal_eeprom.h"

/**
 * 
 * @param bAdd
 * @param bData
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType Data_EEPROM_WriteByte(uint16 bAdd, uint8 bData){
    std_ReturnType ret = E_OK;
    
    /* Read The Interrupt Status "Enabled or Disabled" */
    uint8 Global_Interrupt_Status = INTCONbits.GIE;
    
    /* Update the address register */
    EEADRH = (uint8)((bAdd >> 8) & 0x03);
    EEADR = (uint8)(bAdd & 0xFF);
    
    /* Update the data register */
    EEDATA = bData;
    
    /* Select Access data EEPROM memory */
    EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
    EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
    
    /* Allows write cycles to flash program/data EEPROM */
    EECON1bits.WREN = ALLOW_WRITE_CYCLES_FLASH_EEPROM;
    
    /* Disabled all interrupts "General Interrupts" */
    INTERRUPT_GlobalInterruptDisable();
    
    /* Write the required sequence "0x55 -> 0xAA" */
    EECON2 = 0x55;
    EECON2 = 0xAA;
    
    /* Initiates a data EEPROM erase/write cycle */
    EECON1bits.WR = INITIATE_DATA_EEPROM_WRITE_ERASE;
    
    /* wait for write complete */
    while(EECON1bits.WR);
    
    /* Inhibits write cycles to flash program/data EEPROM */
    EECON1bits.WREN = INHITBTS_WRITE_CYCLES_FLASH_EEPROM;
    
    /* Restore the interrupt status "Enabled or Disabled" */
    INTCONbits.GIE = Global_Interrupt_Status;
    
    return ret;
}

/**
 * 
 * @param bAdd
 * @param bData
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType Data_EEPROM_ReadByte(uint16 bAdd, uint8 *bData){
    std_ReturnType ret = E_NOT_OK;
   
    if(NULL == bData)
    {
        ret = E_NOT_OK;
    }
    else
    {
        /* Update the address register */
        EEADRH = (uint8)((bAdd >> 8) & 0x03);
        EEADR = (uint8)(bAdd & 0xFF);
        
        /* Select Access data EEPROM memory */
        EECON1bits.EEPGD = ACCESS_EEPROM_PROGRAM_MEMORY;
        EECON1bits.CFGS = ACCESS_FLASH_EEPROM_MEMORY;
        
        /* Initiates a data EEPROM Read cycle */
        EECON1bits.RD = INITIATE_DATA_EEPROM_READ;
        NOP();
        NOP();
        
        /* Return Data */
        *bData = EEDATA;
    }
    
    return ret;
}
