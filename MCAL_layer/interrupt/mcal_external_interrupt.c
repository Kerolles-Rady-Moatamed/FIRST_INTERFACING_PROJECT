/* 
 * File:   mcal_external_interrupt.c
 * Author: DELL
 *
 * Created on December 25, 2023, 7:15 PM
 */

#include "mcal_external_interrupt.h"

/* Pointer to function to to hold the callback for INTx */
static InterruptHandler INT0_InterruptHandler = NULL;
static InterruptHandler INT1_InterruptHandler = NULL;
static InterruptHandler INT2_InterruptHandler = NULL;

/* Pointer to function to to hold the callback for RBx */
static InterruptHandler RB4_InterruptHandler_HIGH = NULL;
static InterruptHandler RB4_InterruptHandler_LOW = NULL;
static InterruptHandler RB5_InterruptHandler_HIGH = NULL;
static InterruptHandler RB5_InterruptHandler_LOW = NULL;
static InterruptHandler RB6_InterruptHandler_HIGH = NULL;
static InterruptHandler RB6_InterruptHandler_LOW = NULL;
static InterruptHandler RB7_InterruptHandler_HIGH = NULL;
static InterruptHandler RB7_InterruptHandler_LOW = NULL;

static std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj);
static std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj);

static std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void));
static std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void));
static std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void));
static std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj);

static std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_Clear_Flag(const interrupt_RBx_t *int_obj);
static std_ReturnType Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj);


/**
 * 
 * @param int_obj
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType Interrupt_INTx_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the external interrupt */
        ret = Interrupt_INTx_Disable(int_obj);
        
        /* Clear interrupt flag : external interrupt did not occur */
        ret |= Interrupt_INTx_Clear_Flag(int_obj);
        
        /* Configure external interrupt edge*/
        ret |= Interrupt_INTx_Edge_Init(int_obj);
        
        /* Configure external interrupt priority*/
        ret |= Interrupt_INTx_Priority_Init(int_obj);
        
        /* Configure external interrupt I/O pin*/
        ret |= Interrupt_INTx_Pin_Init(int_obj);
        
        /* Configure Default interrupt callback*/
        ret |= Interrupt_INTx_SetInterruptHandler(int_obj);
        
        /* Enable the external interrupt */
        ret |= Interrupt_INTx_Enable(int_obj);
        
        
    }
    
    return ret;
}





void INT0_ISR(void){
    /* the INT0 external interrupt occurred (must be cleared in software) */
    EXT_INT0_InterruptFlagClear();
    
    /* code */
    
    /* callback function gets called every time this ISR executes */
    if(INT0_InterruptHandler){
        INT0_InterruptHandler();
    }
}

void INT1_ISR(void){
    /* the INT1 external interrupt occurred (must be cleared in software) */
    EXT_INT1_InterruptFlagClear();
    
    /* code */
    
    /* callback function gets called every time this ISR executes */
    if(INT1_InterruptHandler){
        INT1_InterruptHandler();
    }
}

void INT2_ISR(void){
    /* the INT2 external interrupt occurred (must be cleared in software) */
    EXT_INT2_InterruptFlagClear();
    
    /* code */
    
    /* callback function gets called every time this ISR executes */
    if(INT2_InterruptHandler){
        INT2_InterruptHandler();
    }
}
//=====================================================================================================
void RB4_ISR(uint8 RB4_source){
    /* the RB4 external interrupt occurred (must be cleared in software) */
    EXT_RTx_InterruptFlagClear();
    
    /* code */
    
    /* callback function gets called every time this ISR executes */
    if(0 == RB4_source){
        if(RB4_InterruptHandler_HIGH){
            RB4_InterruptHandler_HIGH();
        }
        else{/*no thing*/}
    }
    else if(1 == RB4_source){
        if(RB4_InterruptHandler_LOW){
            RB4_InterruptHandler_LOW();
        }
        else{/*no thing*/}
    }
    else{/*no thing*/}
}

void RB5_ISR(uint8 RB5_source){
    /* the RB5 external interrupt occurred (must be cleared in software) */
    EXT_RTx_InterruptFlagClear();
    
    /* code */
    
    /* callback function gets called every time this ISR executes */
    if(0 == RB5_source){
        if(RB5_InterruptHandler_HIGH){
            RB5_InterruptHandler_HIGH();
        }
        else{/*no thing*/}
    }
    else if(1 == RB5_source){
        if(RB5_InterruptHandler_LOW){
            RB5_InterruptHandler_LOW();
        }
        else{/*no thing*/}
    }
    else{/*no thing*/}
}

void RB6_ISR(uint8 RB6_source){
    /* the RB6 external interrupt occurred (must be cleared in software) */
    EXT_RTx_InterruptFlagClear();
    
    /* code */
    
    /* callback function gets called every time this ISR executes */
    if(0 == RB6_source){
        if(RB6_InterruptHandler_HIGH){
            RB6_InterruptHandler_HIGH();
        }
        else{/*no thing*/}
    }
    else if(1 == RB6_source){
        if(RB6_InterruptHandler_LOW){
            RB6_InterruptHandler_LOW();
        }
        else{/*no thing*/}
    }
    else{/*no thing*/}
}

void RB7_ISR(uint8 RB7_source){
    /* the RB7 external interrupt occurred (must be cleared in software) */
    EXT_RTx_InterruptFlagClear();
    
    /* code */
    
    /* callback function gets called every time this ISR executes */
    if(0 == RB7_source){
        if(RB7_InterruptHandler_HIGH){
            RB7_InterruptHandler_HIGH();
        }
        else{/*no thing*/}
    }
    else if(1 == RB7_source){
        if(RB7_InterruptHandler_LOW){
            RB7_InterruptHandler_LOW();
        }
        else{/*no thing*/}
    }
    else{/*no thing*/}
}



/**
 * 
 * @param int_obj
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType Interrupt_INTx_DeInit(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = Interrupt_INTx_Disable(int_obj);
    }
    
    return ret;
}


/**
 * 
 * @param int_obj
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType Interrupt_RBx_Init(const interrupt_RBx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the external interrupt */
        ret = Interrupt_RBx_Disable(int_obj);
        
        /* Clear interrupt flag : external interrupt did not occur */
        ret |= Interrupt_RBx_Clear_Flag(int_obj);
        
        /* Configure external interrupt priority*/
        ret |= Interrupt_RBx_Priority_Init(int_obj);
        
        /* Configure external interrupt I/O pin*/
        ret |= Interrupt_RBx_Pin_Init(int_obj);
        
        /* Configure Default interrupt callback*/
        ret |= Interrupt_RBx_SetInterruptHandler(int_obj);
        
        /* Enable the external interrupt */
        ret |= Interrupt_RBx_Enable(int_obj);
    }
    
    return ret;
}

/**
 * 
 * @param int_obj 
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
std_ReturnType Interrupt_RBx_DeInit(const interrupt_RBx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the external interrupt */
        ret = Interrupt_RBx_Disable(int_obj);
    }
    
    return ret;
}



/**
 * 
 * @param int_obj 
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
static std_ReturnType Interrupt_INTx_Enable(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 :
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                     INTERRUPT_GlobalInterruptHighEnable();
                #else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT0_InterruptEnable(); 
                ret = E_OK; 
                break;
            
            case INTERRUPT_EXTERNAL_INT1 : 
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                    if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                        INTERRUPT_GlobalInterruptLowEnable();
                        ret = E_OK;
                    }
                    else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                        INTERRUPT_GlobalInterruptHighEnable();
                        ret = E_OK;
                    }
                    else{
                        ret = E_NOT_OK;
                    } 
                #else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT1_InterruptEnable(); 
                ret = E_OK; 
                break;
            
            case INTERRUPT_EXTERNAL_INT2 :
                #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
                    INTERRUPT_PriorityLevelsEnable();
                    if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                        INTERRUPT_GlobalInterruptLowEnable();
                        ret = E_OK;
                    }
                    else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                        INTERRUPT_GlobalInterruptHighEnable();
                        ret = E_OK;
                    }
                    else{
                        ret = E_NOT_OK;
                    } 
                #else
                    INTERRUPT_GlobalInterruptEnable();
                    INTERRUPT_PeripheralInterruptEnable();
                #endif
                EXT_INT2_InterruptEnable(); 
                ret = E_OK; 
                break;
            
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param int_obj 
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
static std_ReturnType Interrupt_INTx_Disable(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptDisable(); 
                ret = E_OK; 
                break;
            
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_InterruptDisable(); 
                ret = E_OK; 
                break;
            
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptDisable(); 
                ret = E_OK; 
                break;
            
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param int_obj 
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
static std_ReturnType Interrupt_INTx_Priority_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE == INTERRUPT_FEATURE_ENABLE
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    EXT_INT1_LowPrioritySet();
                    ret = E_OK;
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    EXT_INT1_HighPrioritySet();
                    ret = E_OK;
                }
                else{
                    ret = E_NOT_OK;
                }  
                break;            
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                    EXT_INT2_LowPrioritySet();
                    ret = E_OK;
                }
                else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                    EXT_INT2_HighPrioritySet();
                    ret = E_OK;
                }
                else{
                    ret = E_NOT_OK;
                } 
                break;
            
            default : ret = E_NOT_OK;
        }
        #endif
    }
    
    return ret;
}

/**
 * 
 * @param int_obj 
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
static std_ReturnType Interrupt_INTx_Edge_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){
                    EXT_INT0_FallingEdgeSet();
                    ret = E_OK;
                }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){
                    EXT_INT1_RisingEdgeSet();
                    ret = E_OK;
                }
                else{
                    ret = E_NOT_OK;
                }  
                break;
            case INTERRUPT_EXTERNAL_INT1 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){
                    EXT_INT1_FallingEdgeSet();
                    ret = E_OK;
                }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){
                    EXT_INT1_RisingEdgeSet();
                    ret = E_OK;
                }
                else{
                    ret = E_NOT_OK;
                }  
                break;            
            case INTERRUPT_EXTERNAL_INT2 : 
                if(INTERRUPT_FALLING_EDGE == int_obj->edge){
                    EXT_INT2_FallingEdgeSet();
                    ret = E_OK;
                }
                else if(INTERRUPT_RISING_EDGE == int_obj->edge){
                    EXT_INT2_RisingEdgeSet();
                    ret = E_OK;
                }
                else{
                    ret = E_NOT_OK;
                } 
                break;
            
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}

/**
 * 
 * @param int_obj 
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
static std_ReturnType Interrupt_INTx_Pin_Init(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    return ret;
}

/**
 * 
 * @param int_obj 
 * @return status of the function
 *         (E_OK) : the function done successfully
 *         (E_NOT_OK) : the function has issue to perform this action
 */
static std_ReturnType Interrupt_INTx_Clear_Flag(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                EXT_INT0_InterruptFlagClear(); 
                ret = E_OK; 
                break;
            
            case INTERRUPT_EXTERNAL_INT1 : 
                EXT_INT1_InterruptFlagClear(); 
                ret = E_OK; 
                break;
            
            case INTERRUPT_EXTERNAL_INT2 : 
                EXT_INT2_InterruptFlagClear(); 
                ret = E_OK; 
                break;
            
            default : ret = E_NOT_OK;
        }
    }
    return ret;
}








static std_ReturnType Interrupt_RBx_Enable(const interrupt_RBx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Enable the external interrupt */
        EXT_RBx_InterruptEnable();
    }
    
    return ret;
}

static std_ReturnType Interrupt_RBx_Disable(const interrupt_RBx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Disable the external interrupt */
        EXT_RBx_InterruptDisable();
    }
    
    return ret;
}

static std_ReturnType Interrupt_RBx_Priority_Init(const interrupt_RBx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Configure external interrupt priority*/
        #if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE
            INTERRUPT_PriorityLevelsEnable();
            if(INTERRUPT_LOW_PRIORITY == int_obj->priority){
                INTERRUPT_GlobalInterruptLowEnable();
                /* this routine sets the RBx External Interrupt Priority to be low priority */
                EXT_RBx_Priority_Low();
                ret = E_OK;
            }
            else if(INTERRUPT_HIGH_PRIORITY == int_obj->priority){
                INTERRUPT_GlobalInterruptHighEnable();
                /* this routine sets the RBx External Interrupt Priority to be high priority */
                EXT_RBx_Priority_High();
                ret = E_OK;
            }
            else{
                ret = E_NOT_OK;
            } 
        #else
            INTERRUPT_GlobalInterruptEnable();
            INTERRUPT_PeripheralInterruptEnable();
        #endif
    }
    
    return ret;
}

static std_ReturnType Interrupt_RBx_Pin_Init(const interrupt_RBx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Configure external interrupt I/O pin*/
        ret = gpio_pin_direction_intialize(&(int_obj->mcu_pin));
    }
    
    return ret;
}

static std_ReturnType Interrupt_RBx_Clear_Flag(const interrupt_RBx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Clear interrupt flag : external interrupt did not occur */
        EXT_RTx_InterruptFlagClear();
    }
    
    return ret;
}

static std_ReturnType Interrupt_RBx_SetInterruptHandler(const interrupt_RBx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        /* Configure Default interrupt callback*/
        switch(int_obj->mcu_pin.pin){
            case GPIO_PIN4 : 
                RB4_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB4_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
                
            case GPIO_PIN5 :
                RB5_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB5_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
                
            case GPIO_PIN6 :
                RB6_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB6_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
                
            case GPIO_PIN7 :
                RB7_InterruptHandler_HIGH = int_obj->EXT_InterruptHandler_HIGH;
                RB7_InterruptHandler_LOW = int_obj->EXT_InterruptHandler_LOW;
                break;
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}










static std_ReturnType INT0_SetInterruptHandler(void(*InterruptHandler)(void)){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        INT0_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    
    return ret;
}

static std_ReturnType INT1_SetInterruptHandler(void(*InterruptHandler)(void)){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        INT1_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    
    return ret;
}

static std_ReturnType INT2_SetInterruptHandler(void(*InterruptHandler)(void)){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == InterruptHandler){
        ret = E_NOT_OK;
    }
    else{
        INT2_InterruptHandler = InterruptHandler;
        ret = E_OK;
    }
    
    return ret;
}

static std_ReturnType Interrupt_INTx_SetInterruptHandler(const interrupt_INTx_t *int_obj){
    std_ReturnType ret = E_NOT_OK;
    
    if(NULL == int_obj){
        ret = E_NOT_OK;
    }
    else{
        switch(int_obj->source){
            case INTERRUPT_EXTERNAL_INT0 : 
                ret = INT0_SetInterruptHandler(int_obj->EXT_InterruptHandler); 
                ret = E_OK; 
                break;
            
            case INTERRUPT_EXTERNAL_INT1 : 
                ret = INT1_SetInterruptHandler(int_obj->EXT_InterruptHandler); 
                ret = E_OK; 
                break;
            
            case INTERRUPT_EXTERNAL_INT2 : 
                ret = INT2_SetInterruptHandler(int_obj->EXT_InterruptHandler); 
                ret = E_OK; 
                break;
            
            default : ret = E_NOT_OK;
        }
    }
    
    return ret;
}

