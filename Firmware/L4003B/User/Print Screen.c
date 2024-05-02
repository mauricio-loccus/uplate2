#include "bsp.h"
#include "ff.h"			/* FatFSÎÄ¼þÏµÍ³Ä£¿é*/
#include "demo_fatfs.h"
#include "usbh_bsp_msc.h"
#include "GUI.h"
#include "SystemPrameter.h"

#include "Systemprompt.h"
#include "StrConvert.h"

#define FILE_HEAD_LENCH 100
#define FS_VOLUME_USB1		"2:/"
#define FS_VOLUME_SPI1		"3:/"

//**********************ÒÔÏÂ½ØÆÁ**************************
extern FATFS fs_usb,fs_spi;
extern FRESULT result;
extern FIL file;
extern FIL FileSave;   //×¨ÃÅÓÃÓÚÍ¼Æ¬µÄ±£´æ
extern DIR DirInf;
extern UINT bw;
extern FATFS fs;
extern FATFS fs_usb,fs_spi;
extern FATFS fs_nand;

unsigned char Pic_Name=1;
extern UINT bw;
char *_screen_buf;
extern uint8_t Pic_Name;
void _WriteByte2File1(U8 Data, void * p)
{   //FRESULT result;
    //result = f_write (p, &Data, 1, &bw);
    _screen_buf[file.fsize]=Data;
    file.fsize++;
}



unsigned char OutScreenXY(unsigned short x,unsigned short y,unsigned short width,unsigned short high)
{
    GUI_HMEM hMem;

    UINT  bw;
    u8 falg_err,i;
    FRESULT result;

    DIR DirInf;
   // char path_usb[32];

   // for(i=0; i<32; i++)
   // {
      //  path_usb[i]=0;
    //}
		if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        sprintf(StrTemp,"%02d%02d%04d",SystemTimePra.Month,SystemTimePra.Day,SystemTimePra.Year);
    }
    else
    {
        sprintf(StrTemp,"%04d%02d%02d",SystemTimePra.Year,SystemTimePra.Month,SystemTimePra.Day);
    }
    sprintf(ConvertStr,"%02d%02d%02d",SystemTimePra.Hour,SystemTimePra.Min,SystemTimePra.Sec);
    strcat(StrTemp,ConvertStr);
		
		
    hMem=GUI_ALLOC_AllocZero(600*320*3+100);
    _screen_buf=GUI_ALLOC_h2p(hMem);

		falg_err=0;
    if(f_mount(&fs_usb, FS_VOLUME_USB, 0)!= FR_OK)
    {
        falg_err=1;
        goto err;
    }
		
    //**************************Ú’Õ˜Ï„Ý¾
    //if(f_mount(&fs_usb, FS_VOLUME_USB1, 0)!= FR_OK)
     //   return 1;  //Ê§Ñœ
    //*************************Õ²ßª×·Ä¿Â¼
    //sprintf(path_usb, "%s/", FS_VOLUME_USB);
    sprintf(ConvertStr, "%s/", FS_VOLUME_USB);	//path_usb
		if ( f_opendir(&DirInf, ConvertStr)!= FR_OK)
    {
        falg_err=2;
        goto err;
    }
		strcat(ConvertStr,BoardInf.Name);
    strcat(ConvertStr,"_");
    strcat(ConvertStr,StrTemp);
    strcat(ConvertStr,".bmp");
    // if(f_open(&file_usb, ConvertStr, FA_OPEN_EXISTING | FA_READ)==FR_OK)//æœ‰ç›¸åŒçš„æ–‡ä»¶å
  //  {
    //    falg_err=3;
     //   goto err;
   // }


    if(f_open(&file, ConvertStr, FA_CREATE_ALWAYS | FA_WRITE)!= FR_OK)
    {
        falg_err=4;
        goto err;
    }

    GUI_BMP_SerializeEx(_WriteByte2File1,x,y,width,high,&file);

    result = f_write(&file, _screen_buf, file.fsize, &bw);//file.fsize  spiÏ„Ý¾
    if (result != FR_OK)
    {
        falg_err=5;
        goto err;
    }
		err:   
    f_close(&file);
    f_mount(NULL,FS_VOLUME_USB, 0);
    GUI_ALLOC_Free(hMem);//
    return falg_err;
}



unsigned char output_screen(void)
{
    GUI_HMEM hMem;

    UINT  bw;
    u8 falg_err,i;
    FRESULT result;
    //FATFS fs;
    DIR DirInf[2];
    //FILINFO FileInf_Usb,FileInf_Spi;
//	uint32_t cnt = 0;
//	char lfname[256];
    char path_usb[32];

    for(i=0; i<32; i++)
    {
        // path_spi[i]=0;
        path_usb[i]=0;
    }
    hMem=GUI_ALLOC_AllocZero(800*480*3+100);//??????????????????????????????????FMC
    _screen_buf=GUI_ALLOC_h2p(hMem);

    //**************************¹ÒÔØÎÄ¼þ
    if(f_mount(&fs_usb, FS_VOLUME_USB1, 0)!= FR_OK)
        return 1;  //Ê§°Ü
    //*************************´ò¿ªÖ÷Ä¿Â¼
    sprintf(path_usb, "%s/", FS_VOLUME_USB);

    if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
        return  2;
    //*************************´ò¿ªUÅÌ×ÓÄ¿Â¼
    strcat(path_usb,"PicSave");

    if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
        return  2;

    //*********************fmc161013ÖØÃûÌáÊ¾
    //strcat(path_usb,"/2");
    //strcat(path_usb,".bmp");//fmc160914
    //***********************¶ÁÈ¡µ±Ç°ÎÄ¼þ¼ÐÏÂµÄÎÄ¼þºÍÄ¿Â¼//
    sprintf(path_usb,"2:/PicSave/%d.bmp",Pic_Name);//USB
    result = f_open(&file, path_usb, FA_CREATE_ALWAYS | FA_WRITE);
    if (result != FR_OK)
        return 7; //ÎÄ¼þÐ´ÈëÊ§°Ü

    GUI_BMP_Serialize(_WriteByte2File1, &file);

    result = f_write(&file, _screen_buf, file.fsize, &bw);//file.fsize  spiÎÄ¼þ
    if (result != FR_OK)
        return 7; //ÎÄ¼þÐ´ÈëÊ§°Ü
    //f_close(&file_spi);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼þµÄ¸öÊý 3
    // ¹Ø±ÕÎÄ¼þÏµÍ³ FIL file_spi,file_usb;
    f_close(&file);
    f_mount(NULL,FS_VOLUME_USB, 0);
    GUI_ALLOC_Free(hMem);//
    return 0;
}
//***********************************************
//¢***********½ØÆÁµ÷ÓÃÒÔÏÂº¯Êý********************
void Print_Screen(void)
{   uint8_t buf[50];
//	uint8_t Pic_Name=0;


    // if ((GPIOA->IDR & GPIO_Pin_3)!= 0) // TAP
    //   return;
    //beep();
    // while(1)
    //{
    // if ((GPIOA->IDR & GPIO_Pin_3) != 0) //
    //   break;
    // }
    /*if ((GPIOB->IDR & GPIO_Pin_1) != 0) //K1
    	return;
    beep();
    while(1)
    {
    	if ((GPIOB->IDR & GPIO_Pin_1) != 0) //K1
    	   break;
    }*/
    if(output_screen())
    {
        beep();
        beep();
    }
    beep();
    Pic_Name++;


}

