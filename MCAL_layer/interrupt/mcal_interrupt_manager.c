/* 
 * File:   mcal_interrupt_manager.c
 * Author: DELL
 *
 * Created on December 25, 2023, 7:16 PM
 */

#include "mcal_interrupt_manager.h"

static volatile uint8 RB4_flag = 1;
static volatile uint8 RB5_flag = 1;
static volatile uint8 RB6_flag = 1;
static volatile uint8 RB7_flag = 1;

#if INTERRUPT_PRIORITY_LEVELS_ENABLE==INTERRUPT_FEATURE_ENABLE

void __interrupt() InterruptManagerHigh(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }else{/* no thing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }else{/* no thing */}
}

void __interrupt(low_priority) InterruptManagerLow(void){
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }else{/* no thing */}
}

#else

void __interrupt() InterruptManager(void){
    if((INTERRUPT_ENABLE == INTCONbits.INT0IE) && (INTERRUPT_OCCUR == INTCONbits.INT0IF)){
        INT0_ISR();
    }else{/* no thing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT1IE) && (INTERRUPT_OCCUR == INTCON3bits.INT1IF)){
        INT1_ISR();
    }else{/* no thing */}
    if((INTERRUPT_ENABLE == INTCON3bits.INT2IE) && (INTERRUPT_OCCUR == INTCON3bits.INT2IF)){
        INT2_ISR();
    }else{/* no thing */}
    /*=============================== START : PortB external on change interrupt start ===============================*/
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_HIGH) && (1 == RB4_flag)){
        RB4_flag = 0;
        RB4_ISR(0);
    }else{/* no thing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB4 == GPIO_LOW) && (0 == RB4_flag)){
        RB4_flag = 1;
        RB4_ISR(1);
    }else{/* no thing */}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_HIGH) && (1 == RB5_flag)){
        RB5_flag = 0;
        RB5_ISR(0);
    }else{/* no thing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB5 == GPIO_LOW) && (0 == RB5_flag)){
        RB5_flag = 1;
        RB5_ISR(1);
    }else{/* no thing */}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_HIGH) && (1 == RB6_flag)){
        RB6_flag = 0;
        RB6_ISR(0);
    }else{/* no thing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB6 == GPIO_LOW) && (0 == RB6_flag)){
        RB6_flag = 1;
        RB6_ISR(1);
    }else{/* no thing */}
    
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_HIGH) && (1 == RB7_flag)){
        RB7_flag = 0;
        RB7_ISR(0);
    }else{/* no thing */}
    if((INTERRUPT_ENABLE == INTCONbits.RBIE) && (INTERRUPT_OCCUR == INTCONbits.RBIF) && (PORTBbits.RB7 == GPIO_LOW) && (0 == RB7_flag)){
        RB7_flag = 1;
        RB7_ISR(1);
    }else{/* no thing */}
    /*=============================== END : PortB external on change interrupt start ===============================*/
}

#endif
