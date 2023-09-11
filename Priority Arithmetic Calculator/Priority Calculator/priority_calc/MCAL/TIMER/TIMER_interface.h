#ifndef TIMER_INTERFACE_H
#define TIMER_INTERFACE_H

#define RISING_EDGE   0
#define FALLING_EDGE  1
#define ENABLE        0
#define DISABLE       1

void TIMER_voidTimer0OVFInit(void); //for normal mode
void TIMER_voidTimer0SetCompareMatchValue(u8 Copy_u8CompareMatchValue); //el value ely lama bywsalo yb2a eltimer by3ml interrupt
void TIMER_voidTimer0CTCInit(void); //for CTC mode
void TIMER_voidSetBusyWaitTimer0_ms(u32 Copy_u32Time_ms); //for CTC mode



void TIMER_voidTimer2FastPWM(void);
void TIMER_voidTimer2SetCompareMatchValue(u8 Copy_u8CompareMatchValue);
void TIMER_voidSetBusyWaitTimer2_ms(u32 Copy_u32Time_ms);

void TIMER_voidTimer1Init(void);
void TIMER_voidTimer1SetOverFlowValue(u16 Copy_u16OverFlowValue);
void TIMER_voidTimer1ChannelASetCompareMatchValue(u16 Copy_u16CompareMatchValue);
void TIMERS_voidTimer1SetPreloadValue(u16 Copy_u16Value);
u16  TIMERS_voidGetTimer1Value(void);


void ICU_voidInit(void);
void ICU_voidSetSenseControl(u8 Copy_u8SenseControl);
void ICU_voidSetCallBackFunction(void (*Copy_pvNotificationFunction)(void));
u16 ICU_u16ReadInputCapture(void);
void ICU_voidInterruptControl(u8 Copy_u8InterruptState);
#endif /* TIMER_INTERFACE_H */