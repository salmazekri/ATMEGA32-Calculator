#ifndef _TWI_INTERFACE_H
#define _TWI_INTERFACE_H

#define START_ACK 0x08
#define REP_START_ACK 0x10  //repeated start
#define SLAVE_ADD_AND_WR_ACK 0x18  //slave address and write
#define MSTR_WR_BYTE_ACK 0x28  //master write byte
#define MSTR_RD_BYTE_WITH_NACK 0x58  //master read byte with nack
#define MSTR_RD_BYTE_WITH_ACK 0x50  //master read byte with ack
#define SLAVE_ADD_AND_RD_ACK 0x40  //slave address and read

typedef enum{
    NoError,
    StartConditionErr,
    RepeatedStartErr,
    SlaveAddressWithWriteErr,
    SlaveAddressWithReadErr,
    MasterWriteDataByteErr,
    MasterReadDataByteErr
}TWI_ErrStatus;

//master
void TWI_voidMasterInit(u8 Copy_u8MasterAddress);
void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_SendStartCondition(void);
TWI_ErrStatus TWI_SendRepeatedStart(void);
TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);
TWI_ErrStatus TWI_MasterWriteDataByte(u8 Copy_u8DataByte);
TWI_ErrStatus TWI_MasterReadDataByte(u8 *Copy_pu8DataByte);
void TWI_SendStopCondition(void);

//void TWI_voidSendStopCondition(void);

//slave
// void TWI_voidSlaveInit(u8 Copy_u8SlaveAddress);
// TWI_ErrStatus TWI_SendSlaveAddressWithRead(u8 Copy_u8SlaveAddress);
// TWI_ErrStatus TWI_SendSlaveAddressWithWrite(u8 Copy_u8SlaveAddress);
// TWI_ErrStatus TWI_SlaveWriteDataByte(u8 Copy_u8Data);
// TWI_ErrStatus TWI_SlaveReadDataByte(u8 *Copy_pu8Data);




#endif // _TWI_INTERFACE_H
