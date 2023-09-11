#include <avr/io.h>
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "GIE_interface.h"


void GIE_voidEnableGlobalInterrupt(void)
{
    SET_BIT(SREG,7);
}

void GIE_voidDisableGlobalInterrupt(void)
{
    CLR_BIT(SREG,7);
}



