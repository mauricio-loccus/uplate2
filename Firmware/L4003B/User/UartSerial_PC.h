#define MACHINE_BUSY 1   //仪器忙

#define CHECK_SUM_LEN  2

#define PC_COMMAND_CONNECT_LEN    (48+CHECK_SUM_LEN)//连接命令长度
#define PC_COMMAND_UNCONNECT_LEN  (CHECK_SUM_LEN)   //断开命令长度



#ifndef __UART_SERIAL_PC_H
#define __UART_SERIAL_PC_H


typedef struct
{
    unsigned char bRemote;
    unsigned char bRunning;
    unsigned char bfinished;
    unsigned char bReconnected;
    unsigned char nPlateTotal;
    unsigned char nPlateCurrent;
} REMOTE_INFO_PC;
extern REMOTE_INFO_PC RemoteInfo_PC;


void GetCheckSum_PC(unsigned char *pCommand, unsigned short ptr);
unsigned short AddCommandHead_PC(unsigned char  *pCommand, unsigned short nCommandSecond, unsigned short nLength);

#endif
