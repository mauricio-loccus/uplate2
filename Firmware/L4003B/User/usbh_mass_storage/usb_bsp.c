/*
*********************************************************************************************************
*
*	模块名称 : USB底层GPIO、中断配置
*	文件名称 : bsp_usb.c
*	版    本 : V1.1
*	说    明 : 提供USB底层接口. 根据 usb_bsp.c （V2.2.0， 09-November-2015）修改。
*
*	修改记录 :
*		版本号  日期         作者       说明
*		V1.0    2013-02-01  armfly     正式发布
*		V1.1    2016-02-26  Eric2013   升级2.1.0的USB库位2.2.0
*
*	Copyright (C), 2016-2020, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/
#include "bsp.h"


extern USB_OTG_CORE_HANDLE  USB_OTG_dev; /* 这两个变量在usb_usr.c文件定义 */
extern USB_OTG_CORE_HANDLE  USB_OTG_Core;
extern USB_OTG_CORE_HANDLE	USB_OTG_CoreWM;
/**
  * @brief  USB_OTG_BSP_Init
  *         Initilizes BSP configurations
  * @param  None
  * @retval None
  */
void USB_OTG_BSP_Init(USB_OTG_CORE_HANDLE *pdev)
{

	
	GPIO_InitTypeDef GPIO_InitStructure;
	
	
//	USB2_IO();
	
	/* 相关的GPIO全部切换到输入模式 */
/*	{
		RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		

		GPIO_Init(GPIOA, &GPIO_InitStructure);		

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_Init(GPIOB, &GPIO_InitStructure);
	}
*/
	/* USB Host */
	if (pdev == &USB_OTG_Core)
	{
		RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;	
		
		GPIO_Init(GPIOB, &GPIO_InitStructure);
		
		
		
		/* 安富莱STM32-V5开发板只使用2根线 PB14/OTG_HS_DM 和 PB15/OTG_HS_DP 接U盘 */
		printf("WM =================================== 使用:USB_OTG_Core \r\n");
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB , ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14 | GPIO_Pin_15;

		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOB, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOB, GPIO_PinSource14,GPIO_AF_OTG2_FS) ;
		GPIO_PinAFConfig(GPIOB, GPIO_PinSource15,GPIO_AF_OTG2_FS) ;

		RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_OTG_HS, ENABLE) ;
		
	}
	/* USB Host 2*/
	if (pdev == &USB_OTG_CoreWM)
	{
		RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		

		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		
		
		
		/* 安富莱STM32-V5开发板只使用2根线 PB14/OTG_HS_DM 和 PB15/OTG_HS_DP 接U盘 */
		printf("WM =================================== 使用:USB_OTG_CoreWM \r\n");
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;

		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_OTG1_FS) ;
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_OTG1_FS) ;

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG, ENABLE);
		RCC_AHB2PeriphClockCmd( RCC_AHB2Periph_OTG_FS, ENABLE) ;
		
		
	}

	
	/* USB Device */
	if (pdev == &USB_OTG_dev)
	{
		RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOA | RCC_AHB1Periph_GPIOB, ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;
		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		

		GPIO_Init(GPIOA, &GPIO_InitStructure);
		
		
		
		printf("WM =================================== 使用:USB_OTG_dev \r\n");
		//RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);

		//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;

		//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		//GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
		//GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
		//GPIO_Init(GPIOA, &GPIO_InitStructure);

		//GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_OTG1_FS);
		//GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_OTG1_FS);

		//RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		//RCC_AHB2PeriphClockCmd(RCC_AHB2Periph_OTG_FS, ENABLE);
		
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA , ENABLE);

		GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_12;

		GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
		GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
		GPIO_Init(GPIOA, &GPIO_InitStructure);

		GPIO_PinAFConfig(GPIOA,GPIO_PinSource11,GPIO_AF_OTG1_FS) ;
		GPIO_PinAFConfig(GPIOA,GPIO_PinSource12,GPIO_AF_OTG1_FS) ;

		RCC_APB2PeriphClockCmd( RCC_APB2Periph_SYSCFG, ENABLE);
		RCC_AHB2PeriphClockCmd( RCC_AHB2Periph_OTG_FS, ENABLE) ;
		
	}
}


/* 关闭所有和USB相关的中断  */
void USB_OTG_BSP_DisableInterrupt(USB_OTG_CORE_HANDLE *pdev)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 先关闭所有和USB相关的中断 */
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = DISABLE;

	if (pdev->cfg.coreID == USB_OTG_FS_CORE_ID)
	{
		NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
	if (pdev->cfg.coreID == USB_OTG_HS_CORE_ID)
	{
		NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	
		NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_EP1_OUT_IRQn;
		NVIC_Init(&NVIC_InitStructure);

		NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_EP1_IN_IRQn;
		NVIC_Init(&NVIC_InitStructure);
	}
}

/**
  * @brief  USB_OTG_BSP_EnableInterrupt
  *         Configures USB Global interrupt
  * @param  None
  * @retval None
  */
void USB_OTG_BSP_EnableInterrupt(USB_OTG_CORE_HANDLE *pdev)
{
	NVIC_InitTypeDef NVIC_InitStructure;

	/* 先关闭所有和USB相关的中断 */
	USB_OTG_BSP_DisableInterrupt(pdev);

	/* USB Host -HS */
	if (pdev == &USB_OTG_Core)
	{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);// 配置为 优先组别 1 组
		
		NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_IRQn;	/* USE_USB_OTG_HS */ // WM OTG_HS_IRQHandler
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 主优先占位 指定抢占式优先级别 1 , 可取 0-1  // 如果不同主,在于中断抢占,并且高中断可实现打断低中断,实现中断嵌套方法
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;        // WM 从优先级别 修正 指定优先级别 1,可取 0-7  // 如果相同主,那么不同从之间先后运行
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		/* 使能 OTG_HS_IRQn */
		NVIC_Init(&NVIC_InitStructure);
		printf("WM ------------------------------USB_OTG_Core--------------------- > OTG_HS_IRQn 中断使能 \r\n");
	}
	/* USB Host 2 -> FS */
	if (pdev == &USB_OTG_CoreWM)
	{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);// 配置为 优先组别 1 组
		
		NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_IRQn;	/* USE_USB_OTG_HS */ // WM OTG_HS_IRQHandler
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1; // 主优先占位 指定抢占式优先级别 1 , 可取 0-1  // 如果不同主,在于中断抢占,并且高中断可实现打断低中断,实现中断嵌套方法
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;        // WM 从优先级别 修正 指定优先级别 1,可取 0-7  // 如果相同主,那么不同从之间先后运行
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;		/* 使能 OTG_HS_IRQn */
		NVIC_Init(&NVIC_InitStructure);
		printf("WM ------------------------------USB_OTG_CoreWM--------------------- > OTG_FS_IRQn 中断使能 \r\n");
	}

	/* USB Device */
	if (pdev == &USB_OTG_dev)
	{
		NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
		NVIC_InitStructure.NVIC_IRQChannel = OTG_FS_IRQn;
		NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
		NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;// WM 修正
		NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
		NVIC_Init(&NVIC_InitStructure);

		#ifdef USB_OTG_HS_DEDICATED_EP1_ENABLED
			NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_EP1_OUT_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;// WM 修正
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);

			NVIC_InitStructure.NVIC_IRQChannel = OTG_HS_EP1_IN_IRQn;
			NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
			NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;// WM 修正
			NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
			NVIC_Init(&NVIC_InitStructure);
		#endif
	}
}

/**
  * @brief  BSP_Drive_VBUS
  *         Drives the Vbus signal through IO
  * @param  state : VBUS states
  * @retval None
  */

void USB_OTG_BSP_DriveVBUS(USB_OTG_CORE_HANDLE *pdev, uint8_t state)
{
	/* 安富莱STM32-V5开发板不支持对外供电的控制 */
}

/**
  * @brief  USB_OTG_BSP_ConfigVBUS
  *         Configures the IO for the Vbus and OverCurrent
  * @param  None
  * @retval None
  */

void  USB_OTG_BSP_ConfigVBUS(USB_OTG_CORE_HANDLE *pdev)
{
	/* 安富莱STM32-V5开发板不支持对外供电的控制 */
}

/**
  * @brief  USB_OTG_BSP_uDelay
  *         This function provides delay time in micro sec
  * @param  usec : Value of delay required in micro sec
  * @retval None
  */
void USB_OTG_BSP_uDelay (const uint32_t usec)
{
	bsp_DelayUS(usec);
}


/**
  * @brief  USB_OTG_BSP_mDelay
  *          This function provides delay time in milli sec
  * @param  msec : Value of delay required in milli sec
  * @retval None
  */
void USB_OTG_BSP_mDelay (const uint32_t msec)
{
	bsp_DelayMS(msec);
}


/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
