



//硬件相关宏定义

#define UART_REV_DATA_LEN  1000
#define UART_SEND_DATA_LEN  100
#define UART_SEND_PRA_LEN  100

#ifndef __UART_H
#define __UART_H

//串口收发数据Buf
extern unsigned char UartRevData[];	    //unsigned char  uartRxBuff_Temp[RX_BUFFER_MAX];
extern unsigned char UartSendData[];

extern unsigned char UartSendPra[];

//串口数据结构体
typedef struct
{
    unsigned short Cmd;         //命令
    unsigned short TempCmd;     //命令暂存
    //INT32U Len;	     //长度
    unsigned short Sum;		  //有效数据个数
    unsigned short SrcSum;	  //发过来的数据长度
    unsigned char Full;

    unsigned short TempLen;	  //接收数据计数器（NC)
    unsigned char* RevData;	  //接收数据指针，指向UartRevData[]
    unsigned char* SendData;    //发送数据指针，指向UartSendData[]
    unsigned short Ecc;		  //校验和
    unsigned short Src_Ecc;	  //ARM发过来的校验和

    //unsigned char test_en;

// unsigned short sc; ///

    unsigned char Sec;
    unsigned char Start;
} UART_INFO;
extern UART_INFO UartInfo;





void UartInit(void);

//uint32_t UARTInit( uint32_t PortNum, uint32_t baudrate );   //串口初使化
//void UART2_SendByte( unsigned char c );                       //发送1个字节的数据
//void UartSendActionData(INT16U cmd);                     //串口发送光栅扫描数据-光强检测数据
//void UartFeedBackCmd(unsigned short cmd);	               //收到命令后回复命令,通知对方命令已收到
//void UartSendKeyCode(unsigned char keycode);
//void Com_Process(void);                                   //串口收到命令后，进行相应的动作
//void FrameReceived(unsigned char c);                      //中断后接收数据
//void UART2_IRQHandler (void) ;	                           //串口中断处理函数
//void UART1_IRQHandler (void) ;	                           //串口中断处理函数


#endif

