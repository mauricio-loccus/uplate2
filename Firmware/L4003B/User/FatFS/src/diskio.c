/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for FatFs     (C)ChaN, 2014        */
/*-----------------------------------------------------------------------*/
/* If a working storage control module is available, it should be        */
/* attached to the FatFs via a glue function rather than modifying it.   */
/* This is an example of glue functions to attach various exsisting      */
/* storage control modules to the FatFs module with a defined API.       */
/*-----------------------------------------------------------------------*/

#include "diskio.h"			/* FatFs lower layer API */
#include "bsp.h"			/* 底层驱动， 提供SD, USB, NAND 驱动 */
#include "usbh_bsp_msc.h"	/* 提供U盘的读写函数 */
#include "SystemPrameter.h"//fmc161010
//#define ff_printf	printf
#define ff_printf(...)

#define SECTOR_SIZE		512	/* SD卡扇区大小必须为512 */
extern  unsigned char flag_new_file,flag_saveasnew_file;//fmc160920s
//extern  unsigned char flag_usb_hs;//0 ?? 1U? 2?? 3??? 4??
//extern  unsigned char flag_usb_fs;//0 ?? 1U? 2?? 3??? 4PC??
/*-----------------------------------------------------------------------*/
/* Get Drive Status                                                      */
/*-----------------------------------------------------------------------*/

DSTATUS disk_status (
	BYTE pdrv		/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;

	switch (pdrv)
	{
		case FS_SD :
			stat = 0;
			break;

		case FS_NAND :
			stat = 0;
			break;
		
		case FS_USB :
			stat = 0;
			break;
		case FS_SPI_FLASH :
			stat = 0;
			break;
		default:
			break;
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Inidialize a Drive                                                    */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (
	BYTE pdrv				/* Physical drive nmuber to identify the drive */
)
{
	DSTATUS stat = STA_NOINIT;

	switch (pdrv)
	{
		case FS_SD :		/* SD卡 */
			if (SD_Init() == SD_OK)
			{
				stat = RES_OK;
			}
			else
			{
				stat = STA_NODISK;
			}
			break;

		case FS_NAND :		/* NAND Flash */
			if (NAND_Init() == NAND_OK)
			{
				stat = RES_OK;
			}
			else
			{
				/* 如果初始化失败，请执行低级格式化 */
				printf("NAND_Init() Error!  \r\n");
				stat = RES_ERROR;
			}
			break;
		
		case FS_USB :		/* STM32 USB Host 口外接U盘 */
			if(HCD_IsDeviceConnected(&USB_OTG_Core))
			{
				stat &= ~STA_NOINIT;
			}
			break;
			
		case FS_SPI_FLASH :
			bsp_InitSFlash();
			stat =  RES_OK;
			break;
		
		default:
			break;
	}
	return stat;
}



/*-----------------------------------------------------------------------*/
/* Read Sector(s)                                                        */
/*-----------------------------------------------------------------------*/

DRESULT disk_read (
	BYTE pdrv,		/* Physical drive nmuber to identify the drive */
	BYTE *buff,		/* Data buffer to store read data */
	DWORD sector,	/* Sector address in LBA */
	UINT count		/* Number of sectors to read */
)
{ unsigned int m,i;
	DRESULT res;

	switch (pdrv)
	{
		case FS_SD :
		{
			SD_Error Status = SD_OK;

			if (count == 1)
			{
				Status = SD_ReadBlock(buff, sector << 9 , SECTOR_SIZE);
			}
			else
			{
				Status = SD_ReadMultiBlocks(buff, sector << 9 , SECTOR_SIZE, count);
			}
			if (Status != SD_OK)
			{
				res = RES_ERROR;
				break;
			}

		#ifdef SD_DMA_MODE
			/* SDIO工作在DMA模式，需要检查操作DMA传输是否完成 */
			Status = SD_WaitReadOperation();
			if (Status != SD_OK)
			{
				res = RES_ERROR;
				break;
			}

			while(SD_GetStatus() != SD_TRANSFER_OK);
		#endif

			res = RES_OK;
			break;
		}

		case FS_NAND :
			if (NAND_OK == NAND_ReadMultiSectors(buff, sector, 512, count))
			{
				res = RES_OK;
			}
			else
			{
				printf("NAND_ReadMultiSectors() Error! sector = %d, count = %d \r\n", sector, count);
				res = RES_ERROR;
			}
			break;
			
		case FS_USB :
			//res = USB_disk_read(buff, sector, count);
			{
				BYTE status = USBH_MSC_OK;

				//if (Stat & STA_NOINIT) 	return RES_NOTRDY;

				if (HCD_IsDeviceConnected(&USB_OTG_Core))
				{
					m=0;//fmc
					do
					{
						status = USBH_MSC_Read10(&USB_OTG_Core, buff,sector,512 * count);
						USBH_MSC_HandleBOTXfer(&USB_OTG_Core ,&USB_Host);
						
						if(status != USBH_MSC_OK)//fmcusb防止死机
						{
							m++;
							if(m>62000)
							{ 
								i++;
								break;
							}
						}
						
						/*Usb_check();
            if(flag_usb_hs==0)
								break;//fmcusb*/
						
						if (!HCD_IsDeviceConnected(&USB_OTG_Core))
						{
							break;
						}
					}
					while (status == USBH_MSC_BUSY );
				}
				else if (HCD_IsDeviceConnected(&USB_OTG_CoreWM))//modify 20180210 two usb
				{
					m=0;//fmc
					do
					{
						status = USBH_MSC_Read10(&USB_OTG_CoreWM, buff,sector,512 * count);
						USBH_MSC_HandleBOTXfer(&USB_OTG_CoreWM ,&USB_Host);
						
						if(status != USBH_MSC_OK)//fmcusb防止死机
						{
							m++;
							if(m>62000)
							{ 
								i++;
								break;
							}
						}
						if (!HCD_IsDeviceConnected(&USB_OTG_CoreWM))
						{
							break;
						}
					}
					while (status == USBH_MSC_BUSY );
				}


				if (status == USBH_MSC_OK)
				{
					res = RES_OK;
				}
				else
				{
					res = RES_ERROR;
				}
			}
			break;
			
		case FS_SPI_FLASH :
			sf_ReadBuffer(buff, sector << 12, count<<12);
			res =  RES_OK;
			break;
		
		default:
			res = RES_PARERR;
			break;
	}
	return res;
}



/*-----------------------------------------------------------------------*/
/* Write Sector(s)                                                       */
/*-----------------------------------------------------------------------*/

#if _USE_WRITE
DRESULT disk_write (
	BYTE pdrv,			/* Physical drive nmuber to identify the drive */
	const BYTE *buff,	/* Data to be written */
	DWORD sector,		/* Sector address in LBA */
	UINT count			/* Number of sectors to write */
)
{
	DRESULT res;

	switch (pdrv)
	{
		case FS_SD :
		{
			SD_Error Status = SD_OK;

			if (count == 1)
			{
				Status = SD_WriteBlock((uint8_t *)buff, sector << 9 ,SECTOR_SIZE);

				if (Status != SD_OK)
				{
					res = RES_ERROR;
					break;
				}

			#ifdef SD_DMA_MODE
				/* SDIO工作在DMA模式，需要检查操作DMA传输是否完成 */
				Status = SD_WaitReadOperation();
				if (Status != SD_OK)
				{
					res = RES_ERROR;
					break;
				}
				while(SD_GetStatus() != SD_TRANSFER_OK);
			#endif
				res = RES_OK;
			}
			else
			{
				/* 此处存在疑问： 扇区个数如果写 count ，将导致最后1个block无法写入 */
				//Status = SD_WriteMultiBlocks((uint8_t *)buff, sector << 9 ,SECTOR_SIZE, count);
				Status = SD_WriteMultiBlocks((uint8_t *)buff, sector << 9 ,SECTOR_SIZE, count + 1);

				if (Status != SD_OK)
				{
					res = RES_ERROR;
					break;
				}

			#ifdef SD_DMA_MODE
				/* SDIO工作在DMA模式，需要检查操作DMA传输是否完成 */
				Status = SD_WaitReadOperation();
				if (Status != SD_OK)
				{
					res = RES_ERROR;
					break;
				}
				while(SD_GetStatus() != SD_TRANSFER_OK);
			#endif
				res = RES_OK;
			}
			break;
		}

		case FS_NAND :
			if (NAND_OK == NAND_WriteMultiSectors((uint8_t *)buff, sector, 512, count))
			{
				res = RES_OK;
			}
			else
			{
				printf("NAND_WriteMultiSectors() Error! sector = %d, count = %d \r\n", sector, count);
				res = RES_ERROR;
			}
			break;
			
		case FS_USB :
			//res = USB_disk_write(buff, sector, count);
			{
				BYTE status = USBH_MSC_OK;

				//if (drv || !count) return RES_PARERR;

				//if (Stat & STA_NOINIT) return RES_NOTRDY;
				//if (Stat & STA_PROTECT) return RES_WRPRT;

				if (HCD_IsDeviceConnected(&USB_OTG_Core))
				{
					do
					{
						status = USBH_MSC_Write10(&USB_OTG_Core,(BYTE*)buff,sector, 512 * count);
						USBH_MSC_HandleBOTXfer(&USB_OTG_Core, &USB_Host);

						if(!HCD_IsDeviceConnected(&USB_OTG_Core))
						{
							break;
						}
					}
					while(status == USBH_MSC_BUSY );

				}
	
        else if (HCD_IsDeviceConnected(&USB_OTG_CoreWM)) //modify 20180210 two usb
				{
					do
					{
						status = USBH_MSC_Write10(&USB_OTG_CoreWM,(BYTE*)buff,sector, 512 * count);
						USBH_MSC_HandleBOTXfer(&USB_OTG_CoreWM, &USB_Host);

						if(!HCD_IsDeviceConnected(&USB_OTG_CoreWM))
						{
							break;
						}
					}
					while(status == USBH_MSC_BUSY );

				}
				if (status == USBH_MSC_OK)
				{
					res = RES_OK;
				}
				else
				{
					res = RES_ERROR;
				}
			}
			break;
			
	case FS_SPI_FLASH :
		{
			#if 0
				uint8_t i;
				BYTE *p;
				
				p = (BYTE *)buff;
				for(i = 0; i < count; i++)
				{
					sf_WriteBuffer((uint8_t *)p, (sector+i) << 12, 4096);
					p += 4096;					
				}
			#else
				sf_WriteBuffer((uint8_t *)buff, sector << 12, count<<12);
			#endif
			res =  RES_OK;
			break;
		}
		default:
			res = RES_PARERR;
			break;
	}
	return res;
}
#endif


/*-----------------------------------------------------------------------*/
/* Miscellaneous Functions                                               */
/*-----------------------------------------------------------------------*/

#if _USE_IOCTL
DRESULT disk_ioctl (
	BYTE pdrv,		/* Physical drive nmuber (0..) */
	BYTE cmd,		/* Control code */
	void *buff		/* Buffer to send/receive control data */
)
{
	DRESULT res;

	switch (pdrv) 
	{
	/*case FS_SD :
		// SD卡磁盘容量： SDCardInfo.CardCapacity 
		res = RES_OK;
		return res;*/
  case FS_SD :
		switch (cmd)   //FMC 改了也不好  #define	_MAX_SS		4096   改SPIFLASH要4096 SD 512
		{
			/* SD卡磁盘容量： SDCardInfo.CardCapacity */
			case CTRL_SYNC :		/* Wait for end of internal write process of the drive */
				res = RES_OK;
				break;

			case GET_SECTOR_COUNT :	/* Get drive capacity in unit of sector (DWORD) */
				*(DWORD*)buff = SDCardInfo.CardCapacity / 512;
				res = RES_OK;
				break;
      case  GET_SECTOR_SIZE:
			  *(WORD*)buff = 512;
			  res = RES_OK;
				break;
			case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */
				*(WORD*)buff = 512;
				res = RES_OK;
				break;

			case CTRL_ERASE_SECTOR: /* Erase a block of sectors (used when _USE_ERASE == 1) */
				res = RES_OK;
				break;
			
			default:
				res = RES_PARERR;
				break;
		}
		break;
	case FS_NAND :
		{
			DRESULT res = RES_OK;

			res = RES_ERROR;
			switch (cmd)
			{
				case CTRL_SYNC :		/* Make sure that no pending write process */
					res = RES_OK;
					break;

				case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
					*(DWORD*)buff = 262144;
					res = RES_OK;
					break;

				case GET_SECTOR_SIZE :	/* Get R/W sector size (WORD) */
					*(WORD*)buff = 512;
					res = RES_OK;
					break;

				case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */\
					*(DWORD*)buff = 512;
					res = RES_OK;
					break;

				default:
					res = RES_PARERR;
					break;
			}
			return res;			
		}	
		
	case FS_USB :
		{
			//if (drv) return RES_PARERR;
			res = RES_ERROR;

			//if (Stat & STA_NOINIT) return RES_NOTRDY;
			switch (cmd)
			{
				case CTRL_SYNC :		/* Make sure that no pending write process */
					res = RES_OK;
					break;

				case GET_SECTOR_COUNT :	/* Get number of sectors on the disk (DWORD) */
					*(DWORD*)buff = (DWORD) USBH_MSC_Param.MSCapacity;
					res = RES_OK;
					break;

				case GET_SECTOR_SIZE :	/* Get R/W sector size (WORD) */
					*(WORD*)buff = 512;
					res = RES_OK;
					break;

				case GET_BLOCK_SIZE :	/* Get erase block size in unit of sector (DWORD) */\
					*(DWORD*)buff = 512;
					res = RES_OK;
					break;

				default:
					res = RES_PARERR;
					break;
			}
			return res;
		}
	case FS_SPI_FLASH :
		res = RES_ERROR;
		switch(cmd)
		{
			/* SPI Flash不需要同步 */
			case CTRL_SYNC :  
				res =  RES_OK;
				break;
			
			/* 返回SPI Flash扇区大小 */
			case GET_SECTOR_SIZE:
				*((WORD *)buff) = 4096;  
				res =  RES_OK;
				break;
			
			/* 返回SPI Flash扇区数 */
			case GET_SECTOR_COUNT:
				*((DWORD *)buff) = 2048;    
				res =  RES_OK;
				break;
			
			/* 下面这两项暂时未用 */
			case GET_BLOCK_SIZE:   
				res =  RES_OK;
				break;
			
			case CTRL_ERASE_SECTOR:
				res =  RES_OK;  
				break;
			
			default:
				res = RES_PARERR;
				break;			
		}
	   break;

	default:
		res = RES_PARERR;
		break;
  }
	return res;
	//return RES_PARERR;
}
#endif

/*
*********************************************************************************************************
*	函 数 名: get_fattime
*	功能说明: 获得系统时间，用于改写文件的创建和修改时间。客户可以自行移植和系统的RTC关联起来
*	形    参: 无
*	返 回 值: 无
*********************************************************************************************************
*/

DWORD get_fattime (void)//modify lugj 20180817 鏃犳璇彞鍒欏湪瀵煎嚭鏂囦欢鏃舵棤鏃堕棿
{
	return	  ((DWORD)(SystemTimePra.Year- 1980) << 25)	/* Year = 2013 */
			| ((DWORD)SystemTimePra.Month << 21)				/* Month = 1 */
			| ((DWORD)SystemTimePra.Day << 16)				/* Day_m = 1*/
			| ((DWORD)SystemTimePra.Hour << 11)				/* Hour = 0 */
			| ((DWORD)SystemTimePra.Min << 5)				/* Min = 0 */
			| ((DWORD)SystemTimePra.Sec >> 1);				/* Sec = 0 */
}



