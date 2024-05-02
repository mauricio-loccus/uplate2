//#include "MainTask.h"
#include "MainTask.h"

/*************************************************************************************
1.文件功能描述
   本程序实现的串口收发,端口：2
2.具体函数
  2.1私有函数
	unsigned short SearchRevCmdDataSum(unsigned short cmd);   //根据命令字查找ARM发过来的有效数据个数
	unsigned short SearchSendCmdDataSum(unsigned short cmd);  //根据命令字查找要发送的有效数据个数
	void UartCmdInit(unsigned short cmd);				      //对接收到的数据进行分配
	unsigned char UART2_GetChar (void) ;                      //接收1个字节的数据

  2.2公有函数
    uint32_t UARTInit( uint32_t PortNum, uint32_t baudrate )；//串口初使化
	void UART2_SendByte( unsigned char c );                       //发送1个字节的数据
	void UartSendActionData(INT16U cmd);                      //串口发送光栅扫描数据-光强检测数据
	void UartFeedBackCmd(unsigned short cmd);	               //收到命令后回复命令,通知对方命令已收到
    void Com_Process(void);                                   //串口收到命令后，进行相应的动作
	void FrameReceived(unsigned char c);                      //中断后接收数据
	void UART2_IRQHandler (void) ;	                           //串口中断处理函数
3.IO说明
  1)P0.10: U2_TXD
  2)P0.11: U2_RXD
4. 创建日期:
   2017/01/23
*************************************************************************************/


//全局变量定义
unsigned char UartRevData[UART_REV_DATA_LEN];    //串口接收数据Buf
unsigned char UartSendData[UART_SEND_DATA_LEN];	 //串口发送数据Buf
//unsigned char UartSendPra[UART_SEND_PRA_LEN];	 //串口发送数据Buf
UART_INFO UartInfo;	                             //串口数据结构体


void UartInit(void)
{
    unsigned short i,k;
    unsigned char start_num;
    unsigned long val;
    UartInfo.RevData=UartRevData;
    UartInfo.SendData= UartSendData;


    for(i=0; i<UART_REV_DATA_LEN; i++)
    {
        UartInfo.RevData[i]=0;
    }


    start_num=4;
    k=4;
    for(i=0+4; i<9*12+4; i++) //96
    {
        val=i*100;
        UartInfo.RevData[k]=(val>>16)&0xff;
        UartInfo.RevData[k+1]=(val>>8)&0xff;
        UartInfo.RevData[k+2]=(val)&0xff;

        UartInfo.RevData[378+k]=(val>>16)&0xff;
        UartInfo.RevData[378+k+1]=(val>>8)&0xff;
        UartInfo.RevData[378+k+2]=(val)&0xff;
        k=k+3;
    }
    for(i=9*12+4; i<9*13+4; i++) //输入
    {
        val=10000;
        UartInfo.RevData[k]=(val>>16)&0xff;
        UartInfo.RevData[k+1]=(val>>8)&0xff;
        UartInfo.RevData[k+2]=(val)&0xff;

        UartInfo.RevData[378+k]=(val>>16)&0xff;
        UartInfo.RevData[378+k+1]=(val>>8)&0xff;
        UartInfo.RevData[378+k+2]=(val)&0xff;
        k=k+3;
    }
    for(i=9*13+4; i<9*14+4; i++) //本底
    {
        val=100;
        UartInfo.RevData[k]=(val>>16)&0xff;
        UartInfo.RevData[k+1]=(val>>8)&0xff;
        UartInfo.RevData[k+2]=(val)&0xff;

        UartInfo.RevData[378+k]=(val>>16)&0xff;
        UartInfo.RevData[378+k+1]=(val>>8)&0xff;
        UartInfo.RevData[378+k+2]=(val)&0xff;
        k=k+3;
    }



}