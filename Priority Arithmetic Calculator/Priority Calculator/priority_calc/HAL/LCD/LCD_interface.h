#ifndef LCD_INTERFACE_H_  
#define LCD_INTERFACE_H_
/*
RS 0->data 1->command
RW 0->write 1->read
EN 1->enable
*/
#define LCD_RS_PORT DIO_PORTB
#define LCD_RS_PIN DIO_PIN0

#define LCD_RW_PORT DIO_PORTB
#define LCD_RW_PIN DIO_PIN1

#define LCD_EN_PORT DIO_PORTB
#define LCD_EN_PIN DIO_PIN2

#define LCD_DATA_PORT DIO_PORTA


void  LCD_voidPrintSpecialChar(void);

void LCD_voidSendData(u8 Copy_u8Data);
void LCD_voidSendCommand(u8 Copy_u8Command);
void LCD_voidInit(void);
void LCD_voidSendString(u8 *Copy_u8String);
void LCD_voidSendNumber(int Copy_u32Number);
void LCD_voidGoToXY(u8 Copy_u8XPos,u8 Copy_u8YPos);
void LCD_voidClearDisplay(void);
void LCD_voidSendSpecialChar(unsigned char loc, unsigned char *msg);
//display float numbers
void LCD_voidSendDecimalNumber(u32 Copy_u32Number);
//void LCD_CreateCustomChar(uint8_t code, const uint8_t* pattern) ;
#endif /* LCD_INTERFACE_H_ */












