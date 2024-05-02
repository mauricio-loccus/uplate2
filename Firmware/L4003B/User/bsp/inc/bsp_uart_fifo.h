#define CMD_STOP  0x04







#define SUM_CMD_MAX 6
#define DETECT_ON_CMD 0x01

#define STOP_DETECT_CMD 0x04
#define DOOR_CLOSE_CMD 0x05

#define CALI_START_STEP_CMD	 0x0b
#define SAVE_START_STEP_CMD	 0x0c
#define SHAKE_CMD            0x0d
#define TESTSELF_CMD         0x0e
//#define SET_FILTER_CMD       0x0f
#define RE_SEND_CMD          0x10
#define PLATE_IN_CMD         0x11  //?????
#define PLATE_OUT_CMD        0x13  //?????
#define PLATE_SCAN_CMD       0x15
#define PLATE_READ_CMD      0x16



#define SUM_CMD_SEND_MAX 4
#define RETURN_SUNCESS_CMD_SEND 0x05	 //??????
#define RETURN_START_STEP_SEND	0x06	 //??????
#define RETURN_ERRCODE_SEND     0x07
#define RETURN_SUNCESS_STOP_CMD_SEND 0x0a	 //STOP????


#define UART_REV_SUM_LEN       0x11

#define PLATE_STATE_IN         0
#define PLATE_STATE_OUT        13



#define UART_SEND_SLA 0xaa
#define UART_REV_SLA  0xbb
////////////////////
#define UART_REV_DATA_LEN   1000
#define UART_SEND_DATA_LEN  1000



#ifndef _BSP_USART_FIFO_H_
#define _BSP_USART_FIFO_H_


//如果需要更改串口对应的管脚，请自行修改 bsp_uart_fifo.c文件中的 static void InitHardUart(void)函数


/* 定义使能的串口, 0 表示不使能（不增加代码大小）， 1表示使能 */
#ifdef STM32_X3	/* 安富莱 STM32-X4 开发板 */
	/* 安富莱STM32-X3开发板串口分配：
		PA9/USART1_TX	  --- 打印调试口
		PA10/USART1_RX
	*/
	#define	UART1_FIFO_EN	1
	#define	UART2_FIFO_EN	0
	#define	UART3_FIFO_EN	0
	#define	UART4_FIFO_EN	0
	#define	UART5_FIFO_EN	0
	#define	UART6_FIFO_EN	0
#else
	/*
		安富莱STM32-V5 串口分配：
		【串口1】 RS232 芯片第1路。
			PB6/USART1_TX	  --- 打印调试口
			PB7/USART1_RX

		【串口2】 PA2 管脚用于以太网； RX管脚用于接收GPS信号
			PA2/USART2_TX/ETH_MDIO (用于以太网，不做串口发送用)
			PA3/USART2_RX	;接GPS模块输出

		【串口3】 RS485 通信 - TTL 跳线 和 排针
			PB10/USART3_TX
			PB11/USART3_RX

		【串口4】 --- 不做串口用。
		【串口5】 --- 不做串口用。

		【串口6】--- GPRS模块 （硬件流控）
			PC6/USART6_TX
			PC7/USART6_RX
			PG8/USART6_RTS
			PG15/USART6_CTS
	*/
	#define	UART1_FIFO_EN	1
	#define	UART2_FIFO_EN	0
	#define	UART3_FIFO_EN	0
	#define	UART4_FIFO_EN	1  //PC通讯
	#define	UART5_FIFO_EN	0
	#define	UART6_FIFO_EN	1  //单片机外接打印机
  #define	UART7_FIFO_EN	0
	/* RS485芯片发送使能GPIO, PB2 */
	#define RCC_RS485_TXEN 	RCC_AHB1Periph_GPIOB
	#define PORT_RS485_TXEN  GPIOB
	#define PIN_RS485_TXEN	 GPIO_Pin_2

	#define RS485_RX_EN()	PORT_RS485_TXEN->BSRRH = PIN_RS485_TXEN
	#define RS485_TX_EN()	PORT_RS485_TXEN->BSRRL = PIN_RS485_TXEN
#endif

/* 定义端口号 */
typedef enum
{
	COM1 = 0,	/* USART1  PA9, PA10 或  PB6, PB7*/
	COM2 = 1,	/* USART2, PD5,PD6 或 PA2, PA3 */
	COM3 = 2,	/* USART3, PB10, PB11 */
	COM4 = 3,	/* UART4, PC10, PC11 */
	COM5 = 4,	/* UART5, PC12, PD2 */
	COM6 = 5,	/* USART6, PC6, PC7 */
	COM7 = 6	/* USART6, PC6, PC7 */
}COM_PORT_E;

/* 定义串口波特率和FIFO缓冲区大小，分为发送缓冲区和接收缓冲区, 支持全双工 */
#if UART1_FIFO_EN == 1
	#define UART1_BAUD			  38400      //115200
	#define UART1_TX_BUF_SIZE	1*1024
	#define UART1_RX_BUF_SIZE	1*1024
#endif

#if UART2_FIFO_EN == 1
	#define UART2_BAUD			9600
	#define UART2_TX_BUF_SIZE	1
	#define UART2_RX_BUF_SIZE	2*1024
#endif

#if UART3_FIFO_EN == 1
	#define UART3_BAUD			9600
	#define UART3_TX_BUF_SIZE	1*1024
	#define UART3_RX_BUF_SIZE	1*1024

#endif

#if UART4_FIFO_EN == 1
	#define UART4_BAUD			115200
	#define UART4_TX_BUF_SIZE	1*1024
	#define UART4_RX_BUF_SIZE	1*1024
#endif

#if UART5_FIFO_EN == 1
	#define UART5_BAUD			115200
	#define UART5_TX_BUF_SIZE	1*1024
	#define UART5_RX_BUF_SIZE	1*1024
#endif

#if UART6_FIFO_EN == 1
	#define UART6_BAUD			115200
	#define UART6_TX_BUF_SIZE	1*1024
	#define UART6_RX_BUF_SIZE	1*1024
#endif

#if UART7_FIFO_EN == 1
	#define UART7_BAUD			115200
	#define UART7_TX_BUF_SIZE	1*1024
	#define UART7_RX_BUF_SIZE	1*1024
#endif





extern unsigned char UartRevData[];	    
extern unsigned char UartSendData[];







typedef struct
{
  unsigned char Cmd;         //命令
  unsigned char TempCmd;     //命令暂存
  unsigned short Sum;		     //有效数据个数
  unsigned char Full;
	unsigned short TempLen;	   //
  unsigned char* RevData;		 //reveive 
  unsigned char* SendData;   //send
  unsigned char Ecc;		     //校验和
  unsigned char SrcEcc;	    //发送端发过来的校验和
	
  unsigned char Sec;
  unsigned char Start;
	
}UART_INFO;
extern UART_INFO UartInfo;




void bsp_InitUart(void);
//void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen);
//void comSendChar(COM_PORT_E _ucPort, uint8_t _ucByte);
//uint8_t comGetChar(COM_PORT_E _ucPort, uint8_t *_pByte);
//void comSendBuf(COM_PORT_E _ucPort, uint8_t *_ucaBuf, uint16_t _usLen);
//void comClearTxFifo(COM_PORT_E _ucPort);
//void comClearRxFifo(COM_PORT_E _ucPort);
void comSetBaud(COM_PORT_E _ucPort, uint32_t _BaudRate);

void USART_SetBaudRate(USART_TypeDef* USARTx, uint32_t BaudRate);



static void UartVarInit(void);

static void InitHardUart(void);

static void ConfigUartNVIC(void);

void RS485_InitTXE(void);
//void RS485_SendBuf(uint8_t *_ucaBuf, uint16_t _usLen);
//void RS485_SendStr(char *_pBuf);
//void RS485_SetBaud(uint32_t _baud);








unsigned char UART6_Analysis(void);
void UART6_Send(u16 cmd,u8 *pra_buf);
void UartInit(void);
void ClearUart(unsigned char i);




#endif

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
