/*
*********************************************************************************************************
*
*	模块名称 : 应用程序参数模块
*	文件名称 : param.c
*	版    本 : V1.0
*	说    明 : 读取和保存应用程序的参数
*	修改记录 :
*		版本号  日期        作者     说明
*		V1.0    2013-01-01 armfly  正式发布
*
*	Copyright (C), 2012-2013, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

//#include "bsp.h"
#include "param.h"

extern PARAM_T g_tParam;

/* 将16KB 一个扇区的空间预留出来做为参数区 For MDK */
//const uint8_t para_flash_area[16*1024] __attribute__((at(ADDR_FLASH_SECTOR_3)));

/*
*********************************************************************************************************
*	函 数 名: LoadParam
*	功能说明: 从Flash读参数到g_tParam
*	形    参：无
*	返 回 值: 无
*********************************************************************************************************
*/
void LoadParam1(void)
{
/*#ifdef PARAM_SAVE_TO_FLASH
	//读取CPU Flash中的参数 /
	bsp_ReadCpuFlash(PARAM_ADDR, (uint8_t *)&g_tParam, sizeof(PARAM_T));
#endif

#ifdef PARAM_SAVE_TO_EEPROM
	//读取EEPROM中的参数 /
	ee_ReadBytes((uint8_t *)&g_tParam, PARAM_ADDR, sizeof(PARAM_T));
#endif*/

	/* 填充缺省参数 */
	//if (g_tParam.ParamVer != PARAM_VER)
	{
		g_tParam.ParamVer = PARAM_VER;

		g_tParam.ucBackLight = 200;

		/* uip  本机IP地址 */
		g_tParam.uip_ip[0] = 192;
		g_tParam.uip_ip[1] = 168;
		g_tParam.uip_ip[2] = 1;
		g_tParam.uip_ip[3] = 88;

		/* uip  子网掩码 */
		g_tParam.uip_net_mask[0] = 255;
		g_tParam.uip_net_mask[1] = 255;
		g_tParam.uip_net_mask[2] = 255;
		g_tParam.uip_net_mask[3] = 0;

		/* uip  默认网关 */
		g_tParam.uip_gateway[0] = 192;
		g_tParam.uip_gateway[1] = 168;
		g_tParam.uip_gateway[2] = 1;
		g_tParam.uip_gateway[3] = 1;

		/* lwip  本机IP地址 */
		g_tParam.lwip_ip[0] = 192;
		g_tParam.lwip_ip[1] = 168;
		g_tParam.lwip_ip[2] = 1;
		g_tParam.lwip_ip[3] = 86;

		/* lwip  子网掩码 */
		g_tParam.lwip_net_mask[0] = 255;
		g_tParam.lwip_net_mask[1] = 255;
		g_tParam.lwip_net_mask[2] = 255;
		g_tParam.lwip_net_mask[3] = 0;

		/* lwip  默认网关 */
		g_tParam.lwip_gateway[0] = 192;
		g_tParam.lwip_gateway[1] = 168;
		g_tParam.lwip_gateway[2] = 1;
		g_tParam.lwip_gateway[3] = 1;


		/* 485 通信波特率 */
		g_tParam.Baud485 = 9600;

		//SaveParam();							/* 将新参数写入Flash */
	}
}

/*
*********************************************************************************************************
*	函 数 名: SaveParam
*	功能说明: 将全局变量g_tParam 写入到CPU内部Flash
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/
void SaveParam1(void)
{
#ifdef PARAM_SAVE_TO_FLASH
	/* 将全局的参数变量保存到 CPU Flash */
	bsp_WriteCpuFlash(PARAM_ADDR, (unsigned char *)&g_tParam, sizeof(PARAM_T));
#endif

#ifdef PARAM_SAVE_TO_EEPROM
	/* 将全局的参数变量保存到EEPROM */
	//ee_WriteBytes((uint8_t *)&g_tParam, PARAM_ADDR, sizeof(PARAM_T));
#endif
}

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
