/*
*********************************************************************************************************
*
*	模块名称 : BSP模块(For STM32F4XX)
*	文件名称 : bsp.c
*	版    本 : V1.1
*	说    明 : 这是硬件底层驱动程序的主文件。每个c文件可以 #include "bsp.h" 来包含所有的外设驱动模块。
*			   bsp = Borad surport packet 板级支持包
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2013-03-01  armfly   正式发布
*		V1.1    2013-06-20  armfly   规范注释，添加必要说明
*
*	Copyright (C), 2013-2014, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "includes.h"
#include "MainTask.h"



//extern void bsp_InitI2C1(void);

void key_init(void)//fmc160818
{
		GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOG|RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOB|RCC_AHB1Periph_GPIOH|RCC_AHB1Periph_GPIOI, ENABLE ); 															   
	
	// 第2步：配置所有的按键GPIO为浮动输入模式(实际上CPU复位后就是输入状态) 
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		// 设为输入口 
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//设为推挽模式 
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//无需、上、下拉电阻 
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO口最大速度 

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3; //DOOR
	GPIO_Init(GPIOA, &GPIO_InitStructure);       
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;// PG6\PG9为键盘输入
	GPIO_Init(GPIOA, &GPIO_InitStructure);
		
  //GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;// PG6\PG9为键盘输入
	//GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;		// 设为输出口 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;// PG6\PG9为键盘输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;// PG6\PG9为键盘输入
	GPIO_Init(GPIOB, &GPIO_InitStructure);

}	
/*
//****************检查键盘
char check_key(void)//fmc160818
{
	if ((GPIOG->IDR & GPIO_Pin_11) == 1)//DOOR
		return 1;
	
	GPIO_SetBits   ( GPIOI, GPIO_Pin_4 );  //=1
	GPIO_ResetBits ( GPIOI, GPIO_Pin_11 );  //=0
	if ((GPIOB->IDR & GPIO_Pin_1) == 0) //K1
		return 1;
	if ((GPIOA->IDR & GPIO_Pin_3) == 0) //K2
		return 2;
	
	
	if ((GPIOH->IDR & GPIO_Pin_4) == 0) //K3
		return 4;
	if ((GPIOI->IDR & GPIO_Pin_11) == 0) //K4
		return 5;
	return 0;
}*/
	void touch_reset_pin_init(void)
	{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA, ENABLE ); 															   
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4;	
	GPIO_Init (GPIOA, & GPIO_InitStructure );	//PF10    //PA4
	GPIO_SetBits( GPIOA, GPIO_Pin_4 );  //=10
	}	
	void touch_reset_1(void)
	{
		GPIO_SetBits( GPIOA, GPIO_Pin_4 );  //=10
	}
	void touch_reset_0(void)
	{
		GPIO_ResetBits( GPIOA, GPIO_Pin_4 );  //=10
	}
	//*******************
	void wifi_reset(void)
	{
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOB, ENABLE ); 															   
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	
	GPIO_Init (GPIOB, & GPIO_InitStructure );	
	GPIO_SetBits( GPIOB, GPIO_Pin_10 );  //=10
	}		
//蜂鸣器初始化
//***************************
	void beep_init(void)
	{
		GPIO_InitTypeDef GPIO_InitStructure;
	  RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOH|RCC_AHB1Periph_GPIOC, ENABLE ); 															   
	
	  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	
	  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;	
	  GPIO_Init (GPIOC, & GPIO_InitStructure );	
	}		
	//**************************
	void drower_init(void)//抽屉到位开关//fmc170110
	{
		GPIO_InitTypeDef GPIO_InitStructure;
	RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOA, ENABLE ); 															   
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
	GPIO_Init (GPIOA, & GPIO_InitStructure );	//E3输入
		
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;   
	GPIO_InitStructure.GPIO_OType = GPIO_OType_OD;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;	
	GPIO_Init (GPIOE, & GPIO_InitStructure );	//A2  输出
		
	 
	GPIO_ResetBits( GPIOE, GPIO_Pin_3 );  //=1
	//GPIO_SetBits   ( GPIOE, GPIO_Pin_3 );  //=1
	}		
//***********************
	void check_drower(void)//fmc170110
	{
	}
//***************************
void beep(void )//
{		
	GPIO_SetBits   ( GPIOC, GPIO_Pin_0 );  //=1
  GUI_Delay(400);
  GPIO_ResetBits ( GPIOC, GPIO_Pin_0 );  //=0
	 GUI_Delay(300);
}
/*
*********************************************************************************************************
*	函 数 名: bsp_Init
*	功能说明: 初始化所有的硬件设备。该函数配置CPU寄存器和外设的寄存器并初始化一些全局变量。只需要调用一次
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/

void bsp_Init(void)
{
	/*
		由于ST固件库的启动文件已经执行了CPU系统时钟的初始化，所以不必再次重复配置系统时钟。
		启动文件配置了CPU主时钟频率、内部Flash访问速度和可选的外部SRAM FSMC初始化。

		系统时钟缺省配置为168MHz，如果需要更改，可以修改 system_stm32f4xx.c 文件
	*/
	/* 使能CRC 因为使用STemWin前必须要使能 */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_CRC, ENABLE);
	
	/* 优先级分组设置为4，可配置0-15级抢占式优先级，0级子优先级，即不存在子优先级。*/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	
	SystemCoreClockUpdate();	/* 根据PLL配置更新系统时钟频率变量 SystemCoreClock */
  bsp_InitDWT();       /* 初始DWT */
	
	bsp_InitUart(); 	/* 初始化串口 */
	bsp_InitKey();		/* 初始化按键变量（必须在 bsp_InitTimer() 之前调用） */
	
	bsp_InitExtIO();    /* FMC总线上扩展了32位输出IO, 操作LED等外设必须初始化 */
	bsp_InitLed(); 		/* 初始LED指示灯端口 */
	
	bsp_InitI2C();		/* 配置I2C总线 */
	//bsp_InitI2C1();   
	
	bsp_InitExtSDRAM();
	bsp_DetectLcdType(); /* 检测触摸板和LCD面板型号, 结果存在全局变量 g_TouchType, g_LcdType */
	//**************
	TOUCH_InitHard();	 /* 初始化配置触摸芯片 */
	LCD_ConfigLTDC();    /* 初始化配置LTDC */
	bsp_InitRTC();// FMC ADD
	bsp_InitSPIBus();
	beep_init();
	key_init();
	
	CommInit_PC();
	drower_init();
	bsp_InitSFlash();
	BeepOnCount(1);
//	bsp_InitSFlash();  FMC20160712
//*****************
//	result = f_mount(&fs, "0:/", 0); 	/* 挂载文件系统 */
}

/*
*********************************************************************************************************
*	函 数 名: BSP_Tick_Init
*	功能说明: 初始化系统滴答时钟做为uCOS-II的系统时钟节拍，1ms一次
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void BSP_Tick_Init (void)
{
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
