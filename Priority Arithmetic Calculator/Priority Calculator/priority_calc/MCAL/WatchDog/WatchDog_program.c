#include <avr/io.h>
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"
#include "WatchDog_interface.h"

void WDT_voidEnable(void){
    //enable WDT
    SET_BIT(WDTCR,3);
    //set prescaler
    SET_BIT(WDTCR,0);
    CLR_BIT(WDTCR,1);
    CLR_BIT(WDTCR,2);
    CLR_BIT(WDTCR,4);
    CLR_BIT(WDTCR,5);
    //enable global interrupt
    SET_BIT(SREG,7);
}
void WDT_voidDisable(void){
    //disable WDT
    CLR_BIT(WDTCR,3);
    //set prescaler
    SET_BIT(WDTCR,0);
    SET_BIT(WDTCR,1);
    SET_BIT(WDTCR,2);
    SET_BIT(WDTCR,4);
    SET_BIT(WDTCR,5);
    //enable global interrupt
    SET_BIT(SREG,7);
}

void WDT_voidReset(void){
    //reset WDT
    SET_BIT(WDTCR,4);
    CLR_BIT(WDTCR,4);
    //enable global interrupt
    SET_BIT(SREG,7);
}