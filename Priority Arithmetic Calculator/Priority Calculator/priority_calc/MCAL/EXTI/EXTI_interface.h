#ifndef EXTI_INTERFACE_H
#define EXTI_INTERFACE_H

void EXTI_voidInit(void);

void EXTI_voidInit0SetCallBack(void (*NotificationFunction)(void));

void EXTI_voidInit1SetCallBack(void (*NotificationFunction)(void));

#endif // !EXTI_INTERFACE_H
