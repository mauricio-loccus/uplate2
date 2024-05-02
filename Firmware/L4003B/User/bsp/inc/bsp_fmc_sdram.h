/*
*********************************************************************************************************
*
*	模块名称 : 外部SDRAM驱动模块
*	文件名称 : bsp_fmc_sdram.h
*	版    本 : V1.0
*	说    明 : 头文件
*
*	修改记录 :
*		版本号  日期       作者    说明
*		v1.0    2014-05-04 armfly  ST固件库版本 V1.3.0
*
*	Copyright (C), 2014-2015, 安富莱电子 www.armfly.com
*
*********************************************************************************************************
*/

#ifndef _BSP_FMC_SDRAM_H
#define _BSP_FMC_SDRAM_H

#define EXT_SDRAM_ADDR  	((uint32_t)0xC0000000)
#define EXT_SDRAM_SIZE		(16 * 1024 * 1024)

/* LCD显存,第1页, 分配2M字节 */
#define SDRAM_LCD_BUF1 		EXT_SDRAM_ADDR

/* LCD显存,第2页, 分配2M字节 */
#define SDRAM_LCD_BUF2		(EXT_SDRAM_ADDR + 2 * 1024 * 1024)//(EXT_SDRAM_ADDR + 4 * 1024 * 1024)

/* 剩下的8M字节，提供给应用程序使用 */
#define SDRAM_APP_BUF		(EXT_SDRAM_ADDR + 4 * 1024 * 1024)//8 改为4


#define SDRAM_APP_SIZE		(12 * 1024 * 1024)


#define SDRAM_INTENSITY_BUF		       (EXT_SDRAM_ADDR + 12 * 1024 * 1024)               //20k*4=80k
#define SDRAM_ABS_BUF		             (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128 * 1024)   //20k*4=80k
#define SDRAM_ABS_INIT_BUF		       (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*2 * 1024) //20k*4=80k
#define SDRAM_ABS_BACK_BUF		       (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*3 * 1024) //20k*4=80k
//#define SDRAM_ABS_INIT_BACK_BUF		   (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*14 * 1024)  //modify 20180424


#define SDRAM_EXPORT_BUF             (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*4 * 1024)  //250k
#define SDRAM_PGORAMENAME_BUF        (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 64*12 * 1024)  //26k
#define SDRAM_USBPGORAMENAME_BUF     (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 64*13 * 1024)  //26k

#define SDRAM_BOARD_INF_BUF          (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*7 * 1024)
#define SDRAM_BOARD_BACK_BUF         (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*8 * 1024)
#define SDRAM_BOARD_TEMP_BUF         (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*9 * 1024)
#define SDRAM_NORMAL_ANALYSIS_BUF    (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*10 * 1024)
#define SDRAM_CALCU_BUF              (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*11 * 1024)


#define SDRAM_INPUT_INTENSITY_BUF		 (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024)                //1k
#define SDRAM_BK_INTENSITY_BUF		   (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024+ 32* 1 * 1024)  //1k
#define SDRAM_FLASH_PAGE_BUF         (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024+ 32* 2 * 1024)
#define SDRAM_SPI_PAGE_BUF           (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024+ 32* 3 * 1024)
#define SDRAM_SPI1_PAGE_BUF          (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024+ 4* 32 * 1024)
#define SDRAM_SPI2_PAGE_BUF          (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024+ 4* 34 * 1024)

#define SDRAM_SEL_FLAG_BUF           (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024+ 4* 36 * 1024)  //1K
#define SDRAM_CONVERT_STR_BUF        (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024+ 4* 37 * 1024)  //1K
#define SDRAM_TEMP_STR_BUF           (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024+ 4* 38 * 1024)  //1K
#define SDRAM_PC_COMM_BUF            (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024+ 4* 39 * 1024)  //PC閫氳
#define SDRAM_PC_FIFO_BUF            (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*12 * 1024+ 4* 40 * 1024)  //PC閫氳FIFO
//#define SDRAM_CURR_PGORAMENAME_BUF   (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 256*6 * 1024 + 32* 5 * 1024)


#define SDRAM_NAND1_BUF              (EXT_SDRAM_ADDR + 12 * 1024 * 1024+  128*12 * 1024+ 32* 6 * 1024)
#define SDRAM_NAND2_BUF              (EXT_SDRAM_ADDR + 12 * 1024 * 1024+  128*12 * 1024+ 32* 7 * 1024)
//#define SDRAM_ABS_BACK_BUF		   (EXT_SDRAM_ADDR + 12 * 1024 * 1024+ 128*14 * 1024)  //modify 20180424



void bsp_InitExtSDRAM(void);
uint32_t bsp_TestExtSDRAM1(void);
uint32_t bsp_TestExtSDRAM2(void);

#endif

/***************************** 安富莱电子 www.armfly.com (END OF FILE) *********************************/
