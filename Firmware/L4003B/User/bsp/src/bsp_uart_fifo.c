/*************************************************************************************
1.文件功能描述
   本程序实现的串口收发,端口：UART1(引脚：PA9 PA10)
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
	 
	 注：printf关联函数int fputc(int ch, FILE *f)
*************************************************************************************/

#include "bsp.h"

#include "SystemPrameter.h"
#include "ReportCalc.h"
#include "CommUsart_PC.h"
#include "CommProcess_PC.h"

//*****************************
#define USE_UART6//使用串口6和下位机通讯，否则串口7
void UART6_Send(u16 cmd,u8 *pra_buf);
//******************************
//char Str_Version103[20];

/* 串口1的GPIO --- RS323 */
#define UART1_TX_PORT      GPIOA
#define UART1_TX_PIN       GPIO_Pin_9
#define UART1_TX_CLK       RCC_AHB1Periph_GPIOA
#define UART1_TX_SOURCE    GPIO_PinSource9

#define UART1_RX_PORT      GPIOA
#define UART1_RX_PIN       GPIO_Pin_10
#define UART1_RX_CLK       RCC_AHB1Periph_GPIOA
#define UART1_RX_SOURCE    GPIO_PinSource10

/* 串口2的GPIO  --- 只用了RX， 没用TX，硬件没有接（可用0欧姆接上） */
#define UART2_TX_PORT      GPIOA
#define UART2_TX_PIN       GPIO_Pin_2
#define UART2_TX_CLK       RCC_AHB1Periph_GPIOA
#define UART2_TX_SOURCE    GPIO_PinSource2

#define UART2_RX_PORT      GPIOA
#define UART2_RX_PIN       GPIO_Pin_3
#define UART2_RX_CLK       RCC_AHB1Periph_GPIOA
#define UART2_RX_SOURCE    GPIO_PinSource3

/* 串口3的GPIO - RS485 */
#define UART3_TX_PORT      GPIOB
#define UART3_TX_PIN       GPIO_Pin_10
#define UART3_TX_CLK       RCC_AHB1Periph_GPIOB
#define UART3_TX_SOURCE    GPIO_PinSource10

#define UART3_RX_PORT      GPIOCB
#define UART3_RX_PIN       GPIO_Pin_11
#define UART3_RX_CLK       RCC_AHB1Periph_GPIOB
#define UART3_RX_SOURCE    GPIO_PinSource11

/* 串口4的GPIO - 在SDIO接口 */
/*
#define UART4_TX_PORT      GPIOC//GPIOA   //GPIOC
#define UART4_TX_PIN       GPIO_Pin_10//GPIO_Pin_0 //GPIO_Pin_10
#define UART4_TX_CLK       RCC_AHB1Periph_GPIOC//RCC_AHB1Periph_GPIOA
#define UART4_TX_SOURCE    GPIO_PinSource10//GPIO_PinSource0

#define UART4_RX_PORT      GPIOC //GPIOA //GPIOC
#define UART4_RX_PIN       GPIO_Pin_11 //GPIO_Pin_1 //GPIO_Pin_11
#define UART4_RX_CLK       RCC_AHB1Periph_GPIOC//RCC_AHB1Periph_GPIOA
#define UART4_RX_SOURCE    GPIO_PinSource11//GPIO_PinSource1
*/

#define UART4_TX_PORT      GPIOA   //GPIOC
#define UART4_TX_PIN       GPIO_Pin_0 //GPIO_Pin_10
#define UART4_TX_CLK       RCC_AHB1Periph_GPIOA
#define UART4_TX_SOURCE    GPIO_PinSource0

#define UART4_RX_PORT      GPIOA //GPIOC
#define UART4_RX_PIN       GPIO_Pin_1 //GPIO_Pin_11
#define UART4_RX_CLK       RCC_AHB1Periph_GPIOA
#define UART4_RX_SOURCE    GPIO_PinSource1

/* 串口5的GPIO - 在SDIO接口 */
#define UART5_TX_PORT      GPIOC
#define UART5_TX_PIN       GPIO_Pin_12
#define UART5_TX_CLK       RCC_AHB1Periph_GPIOC
#define UART5_TX_SOURCE    GPIO_PinSource12

#define UART5_RX_PORT      GPIOD
#define UART5_RX_PIN       GPIO_Pin_2
#define UART5_RX_CLK       RCC_AHB1Periph_GPIOD
#define UART5_RX_SOURCE    GPIO_PinSource2

/* 串口6的GPIO -- GPRS,WIFI */
#define UART6_TX_PORT       GPIOC
#define UART6_TX_PIN       GPIO_Pin_6
#define UART6_TX_CLK       RCC_AHB1Periph_GPIOC
#define UART6_TX_SOURCE    GPIO_PinSource6

#define UART6_RX_PORT      GPIOC
#define UART6_RX_PIN       GPIO_Pin_7
#define UART6_RX_CLK       RCC_AHB1Periph_GPIOC
#define UART6_RX_SOURCE    GPIO_PinSource7

/* 串口7的GPIO -- GPRS,WIFI */
#define UART7_TX_PORT      GPIOF
#define UART7_TX_PIN       GPIO_Pin_7
#define UART7_TX_CLK       RCC_AHB1Periph_GPIOF
#define UART7_TX_SOURCE    GPIO_PinSource7

#define UART7_RX_PORT      GPIOF
#define UART7_RX_PIN       GPIO_Pin_6
#define UART7_RX_CLK       RCC_AHB1Periph_GPIOF
#define UART7_RX_SOURCE    GPIO_PinSource6

/* 定义每个串口结构体变量 */
#if UART1_FIFO_EN == 1
	//static UART_T g_tUart1;
	//static uint8_t g_TxBuf1[UART1_TX_BUF_SIZE];		/* 发送缓冲区 */
//	static uint8_t g_RxBuf1[UART1_RX_BUF_SIZE];		/* 接收缓冲区 */
#endif

#if UART2_FIFO_EN == 1

#endif

#if UART3_FIFO_EN == 1

#endif

#if UART4_FIFO_EN == 1

#endif

#if UART5_FIFO_EN == 1

#endif

#if UART6_FIFO_EN == 1

#endif
#if UART7_FIFO_EN == 1

#endif


//全局变量定义
unsigned char UartRevData[UART_REV_DATA_LEN];    //串口接收数据Buf
unsigned char UartSendData[UART_SEND_DATA_LEN];	 //串口发送数据Buf
UART_INFO UartInfo;	                             //串口数据结构体

//ARM下发的
unsigned short userCMD[SUM_CMD_MAX][3]=
{	
	/*序号 SUM  CMD*/
	//{0x01,0x01,0x01},  //无此功能
	//{0x02,0x02,0x02},  //无此功能
	{0x03,378,0x03},  //无此功能
	{0x04,756,0x04}, //无此功能
	{0x05,0x00,0x05}, 
	{0x06,0x03,0x06},
	{0x07,0x04,0x07},
	{0x0a,0x00,0x0a},
};

//根据命令字查找ARM发过来的有效数据个数
unsigned short SearchRevCmdDataSum(unsigned char cmd)
{
	unsigned char i;
	for (i=0;i<SUM_CMD_MAX;i++)
		if (cmd==userCMD[i][2])
			return (userCMD[i][1]);
	return (0xFFFF);		
}
//根据命令字查找单片机要发给ARM的有效数据个数
/*
unsigned char SearchSendCmdDataSum(unsigned char cmd)
{
	unsigned char i;
	for (i=0;i<SUM_CMD_SEND_MAX;i++)
		if (cmd==userCMD_send[i][2])
			return (userCMD_send[i][1]);
	return (0xFF);		
}*/












//********************************
/*
*********************************************************************************************************
*	函 数 名: bsp_InitUart
*	功能说明: 初始化串口硬件，并对全局变量赋初值.
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
void bsp_InitUart(void)
{
	UartVarInit();		/* 必须先初始化全局变量,再配置硬件 */

	InitHardUart();		/* 配置串口的硬件参数(波特率等) */

	//RS485_InitTXE();	/* 配置RS485芯片的发送使能硬件，配置为推挽输出 */

	ConfigUartNVIC();	/* 配置串口中断 */
}

/*
*********************************************************************************************************
*	函 数 名: USART_SetBaudRate
*	功能说明: 修改波特率寄存器，不更改其他设置。如果使用 USART_Init函数, 则会修改硬件流控参数和RX,TX配置
*			  根据固件库中 USART_Init函数，将其中配置波特率的部分单独提出来封装为一个函数
*	形    参: USARTx : USART1, USART2, USART3, UART4, UART5
*			  BaudRate : 波特率，取值 0 - 4500000
*	返 回 值: 无
*********************************************************************************************************
*/
void USART_SetBaudRate(USART_TypeDef* USARTx, uint32_t BaudRate)
{
	uint32_t tmpreg = 0x00, apbclock = 0x00;
	uint32_t integerdivider = 0x00;
	uint32_t fractionaldivider = 0x00;
	RCC_ClocksTypeDef RCC_ClocksStatus;

	/* Check the parameters */
	assert_param(IS_USART_ALL_PERIPH(USARTx));
	assert_param(IS_USART_BAUDRATE(BaudRate));  

	/*---------------------------- USART BRR Configuration -----------------------*/
	/* Configure the USART Baud Rate */
	RCC_GetClocksFreq(&RCC_ClocksStatus);

	if ((USARTx == USART1) || (USARTx == USART6))
	{
		apbclock = RCC_ClocksStatus.PCLK2_Frequency;
	}
	else
	{
		apbclock = RCC_ClocksStatus.PCLK1_Frequency;
	}

	/* Determine the integer part */
	if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
	{
		/* Integer part computing in case Oversampling mode is 8 Samples */
		integerdivider = ((25 * apbclock) / (2 * (BaudRate)));    
	}
	else /* if ((USARTx->CR1 & USART_CR1_OVER8) == 0) */
	{
		/* Integer part computing in case Oversampling mode is 16 Samples */
		integerdivider = ((25 * apbclock) / (4 * (BaudRate)));    
	}
	tmpreg = (integerdivider / 100) << 4;

	/* Determine the fractional part */
	fractionaldivider = integerdivider - (100 * (tmpreg >> 4));

	/* Implement the fractional part in the register */
	if ((USARTx->CR1 & USART_CR1_OVER8) != 0)
	{
		tmpreg |= ((((fractionaldivider * 8) + 50) / 100)) & ((uint8_t)0x07);
	}
	else /* if ((USARTx->CR1 & USART_CR1_OVER8) == 0) */
	{
		tmpreg |= ((((fractionaldivider * 16) + 50) / 100)) & ((uint8_t)0x0F);
	}

	/* Write to USART BRR register */
	USARTx->BRR = (uint16_t)tmpreg;
}

/*
*********************************************************************************************************
*	函 数 名: UartVarInit
*	功能说明: 初始化串口相关的变量
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void UartVarInit(void)
{
#if UART1_FIFO_EN == 1
	
#endif

#if UART2_FIFO_EN == 1
	
#endif

#if UART3_FIFO_EN == 1
	
#endif

#if UART4_FIFO_EN == 1
	
	
#endif

#if UART5_FIFO_EN == 1
	
#endif


#if UART6_FIFO_EN == 1
	
#endif

#if UART7_FIFO_EN == 1
	
#endif
}

/*
*********************************************************************************************************
*	函 数 名: InitHardUart
*	功能说明: 配置串口的硬件参数（波特率，数据位，停止位，起始位，校验位，中断使能）适合于STM32-F4开发板
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
static void InitHardUart(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure;

#if UART1_FIFO_EN == 1		/* 串口1 TX = PA9   RX = PA10 或 TX = PB6   RX = PB7*/

	/* 第1步： 配置GPIO */
	#if 1	/* TX = PA9   RX = PA10 */
		/* 打开 GPIO 时钟 */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);

		/* 打开 UART 时钟 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

		/* 将 PA9 映射为 USART1_TX */
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_USART1);

		/* 将 PA10 映射为 USART1_RX */
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_USART1);

		/* 配置 USART Tx 为复用功能 */
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		/* 配置 USART Rx 为复用功能 */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	#else	/* TX = PB6   RX = PB7  */
		/* 打开 GPIO 时钟 */
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

		/* 打开 UART 时钟 */
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

		/* 将 PB6 映射为 USART1_TX */
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);

		/* 将 PB7 映射为 USART1_RX */
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);

		/* 配置 USART Tx 为复用功能 */
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		/* 配置 USART Rx 为复用功能 */
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	#endif

	/* 第2步： 配置串口硬件参数 */
	USART_InitStructure.USART_BaudRate = UART1_BAUD;	/* 波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART1, &USART_InitStructure);

	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);	/* 使能接收中断 */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		注意: 不要在此处打开发送中断
		发送中断使能在SendUart()函数打开
	*/
	USART_Cmd(USART1, ENABLE);		/* 使能串口 */

	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(USART1, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
#endif
/*
#if UART2_FIFO_EN == 1		// 串口2 TX = PD5   RX = PD6 或  TX = PA2， RX = PA3 
	
	#if 0	
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	
		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);


		GPIO_PinAFConfig(GPIOD, GPIO_PinSource5, GPIO_AF_USART2);


		GPIO_PinAFConfig(GPIOD, GPIO_PinSource6, GPIO_AF_USART2);


		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOD, &GPIO_InitStructure);


		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
		GPIO_Init(GPIOD, &GPIO_InitStructure);

	#else	
	
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);


		RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);

		// 将 PA2 映射为 USART2_TX. 在STM32-V5板中，PA2 管脚用于以太网 
		//GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);

		// 将 PA3 映射为 USART2_RX 
		GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);

		// 配置 USART Tx 为复用功能 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	

		//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
		//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		//GPIO_Init(GPIOA, &GPIO_InitStructure);

		// 配置 USART Rx 为复用功能 
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
		GPIO_Init(GPIOA, &GPIO_InitStructure);
	#endif
	

	// 第2步： 配置串口硬件参数 
	USART_InitStructure.USART_BaudRate = UART2_BAUD;	
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx;		//仅选择接收模式
	USART_Init(USART2, &USART_InitStructure);

	USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);	

		//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		//注意: 不要在此处打开发送中断
		//发送中断使能在SendUart()函数打开
	
	USART_Cmd(USART2, ENABLE);		// 使能串口

	/// CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		//如下语句解决第1个字节无法正确发送出去的问题 
	//USART_ClearFlag(USART2, USART_FLAG_TC);     // 清发送完成标志，Transmission Complete flag 
#endif
*/
/*
#if UART3_FIFO_EN == 1			// 串口3 TX = PB10   RX = PB11 

	// 配置 PB2为推挽输出，用于切换 RS485芯片的收发状态 
	{
		RCC_AHB1PeriphClockCmd(RCC_RS485_TXEN, ENABLE);

		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		// 设为输出口 
		GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		// 设为推挽模式 
		GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	// 上下拉电阻不使能 
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;	// IO口最大速度 

		GPIO_InitStructure.GPIO_Pin = PIN_RS485_TXEN;
		GPIO_Init(PORT_RS485_TXEN, &GPIO_InitStructure);
	}

	// 打开 GPIO 时钟 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);

	// 打开 UART 时钟 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);

	// 将 PB10 映射为 USART3_TX 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_USART3);

	// 将 PB11 映射为 USART3_RX 
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_USART3);

	// 配置 USART Tx 为复用功能 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	// 输出类型为推挽 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	// 内部上拉电阻使能 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	// 复用模式 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// 配置 USART Rx 为复用功能 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	// 第2步： 配置串口硬件参数 
	USART_InitStructure.USART_BaudRate = UART3_BAUD;	// 波特率 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART3, &USART_InitStructure);

	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// 使能接收中断 

	//	USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		//注意: 不要在此处打开发送中断
		//发送中断使能在SendUart()函数打开

	USART_Cmd(USART3, ENABLE);		// 使能串口 

	// CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
	//	如下语句解决第1个字节无法正确发送出去的问题 
	USART_ClearFlag(USART3, USART_FLAG_TC);     //清发送完成标志，Transmission Complete flag 
#endif
*/
#if UART4_FIFO_EN == 1			/* 串口4 TX = PC10   RX = PC11 */
	// 第1步： 配置GPIO 

	//打开 GPIO 时钟 
	RCC_AHB1PeriphClockCmd(UART4_TX_CLK, ENABLE);

	// 打开 UART 时钟 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART4, ENABLE);

	// 将 PC10 映射为 UART4_TX 
	GPIO_PinAFConfig(UART4_TX_PORT, UART4_TX_SOURCE, GPIO_AF_UART4);

	// 将 PC11 映射为 UART4_RX 
	GPIO_PinAFConfig(UART4_RX_PORT, UART4_RX_SOURCE, GPIO_AF_UART4);

	// 配置 USART Tx 为复用功能 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;// 输出类型为推挽 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	// 内部上拉电阻使能 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	// 复用模式 

	GPIO_InitStructure.GPIO_Pin = UART4_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(UART4_TX_PORT, &GPIO_InitStructure);

	// 配置 USART Rx 为复用功能 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = UART4_RX_PIN;
	GPIO_Init(UART4_RX_PORT, &GPIO_InitStructure);

	// 第2步： 配置串口硬件参数 
	USART_InitStructure.USART_BaudRate = UART4_BAUD;	// 波特率 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART4, &USART_InitStructure);

	USART_ITConfig(UART4, USART_IT_RXNE, ENABLE);	/* 使能接收中断 */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		注意: 不要在此处打开发送中断
		发送中断使能在SendUart()函数打开
	*/
	USART_Cmd(UART4, ENABLE);		/* 使能串口 */

	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(UART4, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
#endif
/*
#if UART5_FIFO_EN == 1			// 串口5 TX = PC12   RX = PD2 
	// 第1步： 配置GPIO 

	// 打开 GPIO 时钟 
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC |RCC_AHB1Periph_GPIOD, ENABLE);

	// 打开 UART 时钟 
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART5, ENABLE);

	// 将 PC12 映射为 UART5_TX 
	GPIO_PinAFConfig(GPIOC, GPIO_PinSource12, GPIO_AF_UART5);

	// 将 PD2 映射为 UART5_RX 
	GPIO_PinAFConfig(GPIOD, GPIO_PinSource2, GPIO_AF_UART5);

	// 配置 UART Tx 为复用功能 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP; // 输出类型为推挽 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 // 内部上拉电阻使能 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	 // 复用模式 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// 配置 UART Rx 为复用功能 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOD, &GPIO_InitStructure);

	// 第2步： 配置串口硬件参数 
	USART_InitStructure.USART_BaudRate = UART5_BAUD;	// 波特率 
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART5, &USART_InitStructure);

	USART_ITConfig(UART5, USART_IT_RXNE, ENABLE);	// 使能接收中断 

		//USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		//注意: 不要在此处打开发送中断
		//发送中断使能在SendUart()函数打开
	
	USART_Cmd(UART5, ENABLE);		// 使能串口 

	// CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		//如下语句解决第1个字节无法正确发送出去的问题 
	USART_ClearFlag(UART5, USART_FLAG_TC);     // 清发送完成标志，Transmission Complete flag 
#endif
*/
#if UART6_FIFO_EN == 1			/* PG14/USART6_TX , PC7/USART6_RX,PG8/USART6_RTS, PG15/USART6_CTS */
	/* 第1步： 配置GPIO */

	/* 打开 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(UART4_TX_CLK, ENABLE);

	/* 打开 UART 时钟 */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART6, ENABLE);

	/* 将 PG14 映射为 USART6_TX */
	//GPIO_PinAFConfig(GPIOG, GPIO_PinSource14, GPIO_AF_USART6);
  GPIO_PinAFConfig(GPIOC, UART6_TX_SOURCE, GPIO_AF_USART6);
	/* 将 PC7 映射为 USART6_RX */
	GPIO_PinAFConfig(GPIOC, UART6_RX_SOURCE, GPIO_AF_USART6);

	/* 将 PG8 映射为 USART6_RTS */
	//GPIO_PinAFConfig(GPIOG, UART6_TX_SOURCE, GPIO_AF_USART6);

	/* 将 PG15 映射为 USART6_CTS */
	//GPIO_PinAFConfig(GPIOG, UART6_RX_SOURCE, GPIO_AF_USART6);

	/* 配置 PG14/USART6_TX 为复用功能 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;// 输出类型为推挽 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	// 内部上拉电阻使能 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	// 复用模式 

	GPIO_InitStructure.GPIO_Pin = UART6_TX_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	// 配置 PC7/USART6_RX 为复用功能 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = UART6_RX_PIN;
	GPIO_Init(GPIOC, &GPIO_InitStructure);

	/* 配置 PG8/USART6_RTS 为复用功能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* 配置 PG15/USART6_CTS 为复用功能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* 第2步： 配置串口硬件参数 */
	USART_InitStructure.USART_BaudRate = UART6_BAUD;	/* 波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	//USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	/* 选择硬件流控 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	/* 不要硬件流控 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART6, &USART_InitStructure);

	USART_ITConfig(USART6, USART_IT_RXNE, ENABLE);	/* 使能接收中断 */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		注意: 不要在此处打开发送中断
		发送中断使能在SendUart()函数打开
	*/
	USART_Cmd(USART6, ENABLE);		/* 使能串口 */

	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(USART6, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */
#endif

#if UART7_FIFO_EN == 1			/* PG14/USART6_TX , PC7/USART6_RX,PG8/USART6_RTS, PG15/USART6_CTS */
	/* 第1步： 配置GPIO */

	/* 打开 GPIO 时钟 */
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOF |RCC_AHB1Periph_GPIOF, ENABLE);

	/* 打开 UART 时钟 */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_UART7, ENABLE);//FMC

	/* 将 PG14 映射为 USART6_TX */
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource7, GPIO_AF_UART7);

	/* 将 PC7 映射为 USART6_RX */
	GPIO_PinAFConfig(GPIOF, GPIO_PinSource6,GPIO_AF_UART7);

	/* 将 PG8 映射为 USART6_RTS */
	//GPIO_PinAFConfig(GPIOG, GPIO_PinSource8, GPIO_AF_USART6);

	/* 将 PG15 映射为 USART6_CTS */
	//GPIO_PinAFConfig(GPIOG, GPIO_PinSource15, GPIO_AF_USART6);

	/* 配置 PG14/USART6_TX 为复用功能 */
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;	/* 输出类型为推挽 */
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	/* 内部上拉电阻使能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;	/* 复用模式 */

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;     //tx  f7   rx f6
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	/* 配置 PC7/USART6_RX 为复用功能 */
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOF, &GPIO_InitStructure);

	/* 配置 PG8/USART6_RTS 为复用功能 */
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
	//GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* 配置 PG15/USART6_CTS 为复用功能 */
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
	//GPIO_Init(GPIOG, &GPIO_InitStructure);

	/* 第2步： 配置串口硬件参数 */
	USART_InitStructure.USART_BaudRate = UART7_BAUD;	/* 波特率 */
	USART_InitStructure.USART_WordLength = USART_WordLength_8b;
	USART_InitStructure.USART_StopBits = USART_StopBits_1;
	USART_InitStructure.USART_Parity = USART_Parity_No ;
	//USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_RTS_CTS;	/* 选择硬件流控 */
	USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;	/* 不要硬件流控 */
	USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(UART7, &USART_InitStructure);

	USART_ITConfig(UART7, USART_IT_RXNE, ENABLE);	/* 使能接收中断 */
	/*
		USART_ITConfig(USART1, USART_IT_TXE, ENABLE);
		注意: 不要在此处打开发送中断
		发送中断使能在SendUart()函数打开
	*/
	USART_Cmd(UART7, ENABLE);		/* 使能串口 */

	/* CPU的小缺陷：串口配置好，如果直接Send，则第1个字节发送不出去
		如下语句解决第1个字节无法正确发送出去的问题 */
	USART_ClearFlag(UART7, USART_FLAG_TC);     /* 清发送完成标志，Transmission Complete flag */

//  comSendBuf(COM7, "123456789",9);
#endif
}

/*
*********************************************************************************************************
*	函 数 名: ConfigUartNVIC
*	功能说明: 配置串口硬件中断.
*	形    参:  无
*	返 回 值: 无
*********************************************************************************************************
*/
static void ConfigUartNVIC(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* Configure the NVIC Preemption Priority Bits */
	/*	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0);  --- 在 bsp.c 中 bsp_Init() 中配置中断优先级组 */

#if UART1_FIFO_EN == 1
	/* 使能串口1中断 */
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART2_FIFO_EN == 1
	/* 使能串口2中断 */
	NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART3_FIFO_EN == 1
	/* 使能串口3中断t */
	NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART4_FIFO_EN == 1
	/* 使能串口4中断t */
	NVIC_InitStructure.NVIC_IRQChannel = UART4_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART5_FIFO_EN == 1
	/* 使能串口5中断t */
	NVIC_InitStructure.NVIC_IRQChannel = UART5_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 4;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART6_FIFO_EN == 1
	/* 使能串口6中断t */
	NVIC_InitStructure.NVIC_IRQChannel = USART6_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 5;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif

#if UART7_FIFO_EN == 1
	/* 使能串口7中断t */
	NVIC_InitStructure.NVIC_IRQChannel = UART7_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 6;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
#endif
}

//-----------------------------------------------------------------//
//	功    能：串口收到命令后进行初使化
//	入口参数: cmd命令字
//	出口参数: 
//  备    注：
//-----------------------------------------------------------------//

void UartCmdInit(unsigned char cmd)
{
	switch(cmd)
	{
	    case CPU_RESPONSE_COMMAND:
		  {
			    run_status.nRunMode = RUN_MODE_IDLE;
			    break;
			}
			case CPU_RESPONSE_TEMP://上发孵育温度02
		  {
			    run_status.nRunMode = RUN_MODE_IDLE;
			    break;
			}
			case CPU_RESPONSE_STOP_END:
		  {
				  run_status.task_busy=0;
			    run_status.nRunMode = RUN_MODE_IDLE;
			    break;
			}
			case CPU_RESPONSE_END: //本次检测或振动结束05
		  {
				  if( (run_status.nRunMode != RUN_MODE_SHAKE)&&(run_status.nRunMode != RUN_MODE_SELFTEST) )
					{
						 run_status.task_busy=0;
			       run_status.nRunMode = RUN_MODE_IDLE;
					}
					else
					{
						 UartInfo.Full=1;
					}
			    break;
			}
			case CPU_RESPONSE_ORIGIN://发送原点数据06
			{
				run_status.nRunMode = RUN_MODE_IDLE;
			//	SystemPrameter.nOrigin=(unsigned int)UartSendData[0] * 65536+(unsigned int)UartSendData[1] * 256+(unsigned int)UartSendData[2];
				//bOriginCompleted = true; //2015-2-13
				//sys_para.nOrigin = (unsigned int)uartRxBuff_Temp[2] * 65536 + (unsigned int)uartRxBuff_Temp[3] * 256 + (unsigned int)uartRxBuff_Temp[4];
				break;
			}
			case CPU_RESPONSE_ERROR_CODE://发送错误代码07
			{
				run_status.task_busy=0;
				//bSerialError = true; //2015-2-13
				//run_status.nRunMode = RUN_MODE_IDLE;
				gSystem.SystemErrCode = (unsigned int)UartRevData[0] * 256 + (unsigned int)UartRevData[1];
				gSystem.nChannel= (((unsigned short)UartRevData[2])<<8)+(unsigned short)UartRevData[3];
				//UartInfo.Full=1;//add 20180201
				
				
			
				
				break;
			}
			case CPU_RESPONSE_INTENSITY_ONE://上发一次检测数据03
			{
				//SetTimer(3,1,NULL);
				if(BoardInf.KineticPara .Enable )
	      {
			     GetResultABS(1, BoardInf.KineticPara.kinetic_readings_practical);// - 1);
        }
	      else
	      {
			     BoardInf.KineticPara.kinetic_readings_practical = 1;//0;//1;
			     GetResultABS(1, 0);
	      }
				
				if(BoardInf.KineticPara.Enable)
				//if(board_inf.curentKinetic[0] == _T('O'))
				{
					 BoardInf.KineticPara.kinetic_reading_current++;
				//	BoardInf.KineticPara.kinetic_reading_current++;
					BoardInf.KineticPara.kinetic_readings_practical++;
				//	BoardInf.KineticPara.kinetic_readings_practical++;
					run_status.bHasData=1;
					//BoardInf.KineticPara.bHasData = true;
					if(BoardInf.KineticPara.kinetic_readings_practical <BoardInf.KineticPara.Readings)
					{
						if(RemoteInfo_PC.RemoteFlag)
						{
						      RemoteInfo_PC.SendFlag=1;  //modify lugj181018 做动力学连接PC
						}
						break;
					}
				}
				
				//完成检测
				run_status.task_busy=0;
				run_status.nRunMode = RUN_MODE_IDLE;
				UartInfo.Full=1;	///
			//	board_inf.wcCycles = BoardInf.KineticPara.kinetic_readings_practical;
				//if(m_bMessageBox)
			//	{
				//	m_bMessageBox = false;
			//	}
				break;
			}
			case CPU_RESPONSE_INTENSITY_TWO://上发两次检测数据04
			{
				if(BoardInf.KineticPara .Enable )
	      {
			     GetResultABS(2, BoardInf.KineticPara.kinetic_readings_practical);// - 1);
        }
	      else
	      {
			     BoardInf.KineticPara.kinetic_readings_practical = 1;//1;
			     GetResultABS(2, 0);
	      }
				
				//SetTimer(5,1,NULL);
				if(BoardInf.KineticPara.Enable)
				//if(board_inf.curentKinetic[0] == _T('O'))
				{
					 BoardInf.KineticPara.kinetic_reading_current++;
				//	BoardInf.KineticPara.kinetic_reading_current++;
					BoardInf.KineticPara.kinetic_readings_practical++;
				//	BoardInf.KineticPara.kinetic_readings_practical++;
					run_status.bHasData=1;
					//BoardInf.KineticPara.bHasData = true;
					if(BoardInf.KineticPara.kinetic_readings_practical <BoardInf.KineticPara.Readings)
					{
								if(RemoteInfo_PC.RemoteFlag)
								{
											RemoteInfo_PC.SendFlag=1;  //modify lugj181018 做动力学连接PC
								}
						    break;
					}
				}
				//检测完成
				run_status.task_busy=0;
				run_status.nRunMode = RUN_MODE_IDLE;

				UartInfo.Full=1;	///
				
			//	board_inf.wcCycles = BoardInf.KineticPara.kinetic_readings_practical;
			//	if(m_bMessageBox)
			//	{
			//		m_bMessageBox = false;
			//	}
				break;
			}
			case CPU_RESPONSE_INTENSITY_DATA://09
			{
			//	if(!bRealTimeIntensity)
			//	{
				//	SetTimer(6,1000,NULL);
			//	}
			//	else
				//{
				//	SetTimer(10,1,NULL);
			//	}
				  run_status.nRunMode = RUN_MODE_IDLE;
				  break;
			}
			default:
			{
				  break;
			}
		}
}


//UartInfo.Ecc从命令字到有效数据的所有数据之和
//UartInfo.Src_Ecc 接收到有校验和--2个字节
//UartInfo.pdata接收有效数据指针
//UartInfo.TempCmd接收命令暂存
//UartInfo.Cmd接收命令
//UartInfo.Sum从有效数据到校验和的字节数

//----------------------------------------------------------------//
// 函数功能：串口接收数据
// 入口参数：c收到的数据
// 出口参数：无
// 备注：
//----------------------------------------------------------------//
void FrameReceived(unsigned char c)
{
   // unsigned char len=0;

	UartInfo.Start=1;
	UartInfo.Sec=0;

  if(UartInfo.TempLen==0)
	{
	  if(c==UART_REV_SLA)	  //0x55										// 是否收到起始字符 
  	{												    				// 收到起始字符
		  UartInfo.TempLen++;
		  UartInfo.Ecc=c;
	   }
	   else
	   {
	      UartInfo.TempLen=0;
		    UartInfo.Ecc=0;
	   }
  }
	else if(UartInfo.TempLen==1)
	{
	   UartInfo.Ecc+=c;
		 UartInfo.TempCmd=c;
		 UartInfo.Sum=	SearchRevCmdDataSum(UartInfo.TempCmd);
		
		 if(UartInfo.Sum>UART_REV_DATA_LEN)UartInfo.TempLen=0;
		 else UartInfo.TempLen++;
	}
	
	else if(UartInfo.TempLen>=2)
	{
  	   if(UartInfo.TempLen<UartInfo.Sum+3)	                         
   	   {																
    	      *((UartInfo.RevData)+UartInfo.TempLen-2)=c;
			      if (UartInfo.TempLen<UartInfo.Sum+2)   //从命令字到有效数据的全有数据之和
			      {		               
				 	    UartInfo.Ecc+= c;	                 				//自动计算出有效数据的校验和
							UartInfo.TempLen++;
						}
						else 
						{		               
							UartInfo.SrcEcc= c;	                 				//自动计算出有效数据的校验和
							UartInfo.TempLen++;
						//}
						if (UartInfo.Ecc==UartInfo.SrcEcc)
						{
								UartInfo.TempLen=0;
								if(UartInfo.Full==1)//run_status.busy
								{
									if(UartInfo.TempCmd==CMD_STOP)
									{
										  //if(run_status.nRunMode != RUN_MODE_SELFTEST)
											//{
											   UartInfo.Cmd=UartInfo.TempCmd;
											   UartCmdInit(UartInfo.Cmd);
											//}
			               //有接收到命令
									}
							  }
								else
								{
								//	if(run_status.nRunMode != RUN_MODE_SELFTEST)
								//	{
										 UartInfo.Cmd=UartInfo.TempCmd;
				             UartCmdInit(UartInfo.Cmd);
									//}
									//	UartInfo.Full=1;			              
								}
						}//if (UartInfo.Ecc==UartInfo.Src_Ecc)
						else//校验和不正确
						{
								UartInfo.TempLen=0;
								UartInfo.Full=0;		  
						}	  //else //if (len==uart_info.sum-1)
					}
			}//if(UartInfo.TempLen<UartInfo.Sum+3)	  
		  else   
		  {
		     UartInfo.TempLen=0;
		  }
	}	 //else if(UartInfo.TempLen>=2)
}




//----------------------------------------------------------------//
//	函 数 名: USART1_IRQHandler  USART2_IRQHandler USART3_IRQHandler UART4_IRQHandler UART5_IRQHandler
//	功能说明: USART中断服务程序
//	形    参: 无
//	返 回 值: 无
//----------------------------------------------------------------//

//与单片机通讯串口
#if UART1_FIFO_EN == 1
void USART1_IRQHandler(void)
{
	#if uCOS_EN == 1
		CPU_SR_ALLOC();

	    CPU_CRITICAL_ENTER();
        OSIntEnter();                         
		CPU_CRITICAL_EXIT();
	#endif
	
	
	
	
	 if(USART_GetFlagStatus(USART1, USART_FLAG_ORE) != RESET)
   {
      	USART_ReceiveData(USART1);
		    USART_ClearFlag(USART1, USART_FLAG_ORE);
	 }
	 if(USART_GetITStatus(USART1,USART_IT_RXNE) == SET) 
	 {  
		    FrameReceived((unsigned char)USART_ReceiveData(USART1));
	      USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	 }
	 
	 
	
	
	
	
	#if uCOS_EN == 1
		OSIntExit();                           
	#endif	
}
#endif





#if UART2_FIFO_EN == 1
void USART2_IRQHandler(void)
{
	#if uCOS_EN == 1
		CPU_SR_ALLOC();

	    CPU_CRITICAL_ENTER();
        OSIntEnter();                         
		CPU_CRITICAL_EXIT();
	#endif
	
	//UartIRQ(&g_tUart2);

	#if uCOS_EN == 1
		OSIntExit();                           
	#endif
}
#endif

#if UART3_FIFO_EN == 1
void USART3_IRQHandler(void)
{
	#if uCOS_EN == 1
		CPU_SR_ALLOC();

	    CPU_CRITICAL_ENTER();
        OSIntEnter();                         
		CPU_CRITICAL_EXIT();
	#endif
	
	//UartIRQ(&g_tUart3);

	#if uCOS_EN == 1
		OSIntExit();                           
	#endif
}
#endif

//与单片机通讯串口
#if UART4_FIFO_EN == 1
void UART4_IRQHandler(void)
{

	#if uCOS_EN == 1
		CPU_SR_ALLOC();

	    CPU_CRITICAL_ENTER();
        OSIntEnter();                         
		CPU_CRITICAL_EXIT();
	#endif
	
	

	
	 if(USART_GetFlagStatus(UART4, USART_FLAG_ORE) != RESET)
   {
      	USART_ReceiveData(UART4);
		    USART_ClearFlag(UART4, USART_FLAG_ORE);
	 }
	 if(USART_GetITStatus(UART4,USART_IT_RXNE) == SET) 
	 {  
		    FrameReceived_PC((unsigned char)USART_ReceiveData(UART4));
	      USART_ClearITPendingBit(UART4, USART_IT_RXNE);
	 }
	 
	#if uCOS_EN == 1
		OSIntExit();                           
	#endif	
	
}
#endif


#if UART5_FIFO_EN == 1
void UART5_IRQHandler(void)
{
	#if uCOS_EN == 1
		CPU_SR_ALLOC();

	    CPU_CRITICAL_ENTER();
        OSIntEnter();                         
		CPU_CRITICAL_EXIT();
	#endif
	
	//UartIRQ(&g_tUart5);
	
	#if uCOS_EN == 1
		OSIntExit();                           
	#endif
}
#endif


//与单片机通讯串口
#if UART6_FIFO_EN == 1
void USART6_IRQHandler(void)
{
	#if uCOS_EN == 1
		CPU_SR_ALLOC();

	    CPU_CRITICAL_ENTER();
        OSIntEnter();                         
		CPU_CRITICAL_EXIT();
	#endif
	
	
	
	
	 if(USART_GetFlagStatus(USART6, USART_FLAG_ORE) != RESET)
   {
      	USART_ReceiveData(USART6);
		    USART_ClearFlag(USART6, USART_FLAG_ORE);
	 }
	 if(USART_GetITStatus(USART6,USART_IT_RXNE) == SET) 
	 {  
		   // FrameReceived((unsigned char)USART_ReceiveData(USART6));
	      USART_ClearITPendingBit(USART6, USART_IT_RXNE);
	 }
	 
	 
	
	
	
	
	#if uCOS_EN == 1
		OSIntExit();                           
	#endif	
}
#endif



#if UART7_FIFO_EN == 1
void UART7_IRQHandler(void)
{
	#if uCOS_EN == 1
		CPU_SR_ALLOC();

	    CPU_CRITICAL_ENTER();
        OSIntEnter();                         
		CPU_CRITICAL_EXIT();
	#endif
	
	//UartIRQ(&g_tUart7);
	#if uCOS_EN == 1
		OSIntExit();                           
	#endif
}
#endif
/*
*********************************************************************************************************
*	函 数 名: fputc
*	功能说明: 重定义putc函数，这样可以使用printf函数从串口1打印输出
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
int fputc(int ch, FILE *f)
{//int i;
#if 1	/* 将需要printf的字符通过串口中断FIFO发送出去，printf函数会立即返回 */
//	comSendChar(COM7, ch);

	return ch;
#else	/* 采用阻塞方式发送每个字符,等待数据发送完毕 */
	/* 写一个字节到USART1 */
	USART_SendData(UART7, (uint8_t) ch);

	/* 等待发送结束 */
	while (USART_GetFlagStatus(UART7, USART_FLAG_TC) == RESET)
	{}
	//for(i=0;i<50000;i++);	

	return ch;
#endif
}

/*
*********************************************************************************************************
*	函 数 名: fgetc
*	功能说明: 重定义getc函数，这样可以使用getchar函数从串口1输入数据
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
int fgetc(FILE *f)
{

#if 1	/* 从串口接收FIFO中取1个数据, 只有取到数据才返回 */
	uint8_t ucData;

	//while(comGetChar(COM1, &ucData) == 0);

	return ucData;
#else
	/* 等待串口1输入数据 */
	while (USART_GetFlagStatus(USART1, USART_FLAG_RXNE) == RESET);

	return (int)USART_ReceiveData(USART1);
#endif
}



void UART6_Send(u16 cmd,u8 *pra_buf)
{
    // for(i=0;i<len;i++)
	 {
		 #if defined  USE_UART6
		//  USART_SendData(USART6, (uint8_t) UART_Send_Buf[i]);
	    while (USART_GetFlagStatus(USART6, USART_FLAG_TC) == RESET);/* 等待发送结束 */
		 #else
		 // USART_SendData(UART7, (uint8_t) UART_Send_Buf[i]);
	    while (USART_GetFlagStatus(UART7, USART_FLAG_TC) == RESET);/* 等待发送结束 */
     #endif
   }
}
	




//发送数据给ARM
/*
void SendDataToWince(INT8U cmd)
{
   INT8U sum,crc;
   INT16U i;
   crc=0;
   uart_info.cmd=0;
   uart_info.full=0;

   DelayMs(200);
   if (cmd==RETURN_SUNCESS_CMD_SEND)     //下位机串口事件处理完成
   {
	  UartData_Send[0]=0x01;             //上发D0=0x01
   }
   else if (cmd==RETURN_SUNCESS_STOP_CMD_SEND)     //下位机STOP串口事件处理完成
   {
	  UartData_Send[0]=0x01;             //上发D0=0x01
   }
   else if (cmd==RETURN_ERRCODE_SEND)   //上发目前的孵育温度
   {
   	  UartData_Send[0]=(SystemErrCode>>8);			 //孵育温度用两个字节
	  UartData_Send[1]=(SystemErrCode&0x00ff);
	  UartData_Send[2]=(SystemErrChannel&0x00ff);
   }  
   else if(cmd==RETURN_START_STEP_SEND)  
   {
      UartData_Send[0]=detect_inf.StartStepTemp/65536;			 //孵育温度用两个字节
	  UartData_Send[1]=detect_inf.StartStepTemp%65536/256;
	  UartData_Send[2]=detect_inf.StartStepTemp%256;
   }
   sum=SearchSendCmdDataSum(cmd);
   UART1_SendByte(0xbb);			//bb
   UART1_SendByte(cmd);			    //0x01
   if(sum>0)
   {
     for(i=0;i<sum;i++)
     {
   	    crc+=*(uart_info.pdata_send+i);
	    UART1_SendByte(*(uart_info.pdata_send+i));
     }
   }
   crc=crc+0xbb+cmd;
   UART1_SendByte(crc);	
			  //2016-02-15
   // if(detect_inf.stop_state!=STOP_READY) 
   //{
     uart_info.cmd=0;
     uart_info.full=0;
  // }
    DelayMs(200);
}
*/


//串口命令初使化	
void UartInit(void)
{	
	
	unsigned int i,k;
	   //unsigned char start_num;
	   unsigned long val;
		UartInfo.RevData=UartRevData;
	  UartInfo.SendData= UartSendData;


	  for(i=0;i<UART_REV_DATA_LEN;i++)
    {
           UartInfo.RevData[i]=0;
    }

    k=0;
  //  for(i=0;i<9*14;i++)
		//{
			
		for(i=0;i<9*12;i++)    //96
		{
			val=(unsigned long)i*10000+1000;
			 UartInfo.RevData[k]=(val>>16)&0xff;
		   UartInfo.RevData[k+1]=(val>>8)&0xff;
		   UartInfo.RevData[k+2]=(val)&0xff;
           
		   UartInfo.RevData[378+k]=(val>>16)&0xff;
		   UartInfo.RevData[378+k+1]=(val>>8)&0xff;
		   UartInfo.RevData[378+k+2]=(val)&0xff;
		   k=k+3;
		}
		for(i=9*12;i<9*13;i++)    //空白
		{
			 val=2000000;
			 UartInfo.RevData[k]=(val>>16)&0xff;
		   UartInfo.RevData[k+1]=(val>>8)&0xff;
		   UartInfo.RevData[k+2]=(val)&0xff;
           
		   UartInfo.RevData[378+k]=(val>>16)&0xff;
		   UartInfo.RevData[378+k+1]=(val>>8)&0xff;
		   UartInfo.RevData[378+k+2]=(val)&0xff;
		   k=k+3;
		}
		for(i=9*13;i<9*14;i++)    //背景
		{
			val=1000;
			 UartInfo.RevData[k]=(val>>16)&0xff;
		   UartInfo.RevData[k+1]=(val>>8)&0xff;
		   UartInfo.RevData[k+2]=(val)&0xff;
           
		   UartInfo.RevData[378+k]=(val>>16)&0xff;
		   UartInfo.RevData[378+k+1]=(val>>8)&0xff;
		   UartInfo.RevData[378+k+2]=(val)&0xff;
		   k=k+3;
		}
		
 	  //for(i=0+4;i<9*12+4;i++) //96
    //{
		  // val=i*100;
      
 //   }


}
void ClearUart(unsigned char i)
{
}




