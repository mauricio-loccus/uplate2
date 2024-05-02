
#ifndef __UART_PROCESS_H
#define __UART_PROCESS_H


void MCU_SendRun(void);
void SendShakeProtocol(void);
void MCU_StartStop(unsigned char state);
void openClosedoor(unsigned char state);
void MCU_RepeatSend(void);
void  MCU_SendSaveOrigin(unsigned int nOrigin);
void MCU_SendSelftest(void);
void UartExceedCheck(void);
void RefreshPauseTime(void);
#endif
