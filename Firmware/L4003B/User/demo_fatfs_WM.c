/*
*********************************************************************************************************
*
*	Ä£¿éÃû³Æ : SD¿¨FatÎÄ¼şÏµÍ³ÑİÊ¾Ä£¿é¡£
*	ÎÄ¼şÃû³Æ : demo_sdio_fatfs.c
*	°æ    ±¾ : V1.0
*	Ëµ    Ã÷ : ¸ÃÀı³ÌÒÆÖ²FatFSÎÄ¼şÏµÍ³£¨°æ±¾ R0.09b£©£¬ÑİÊ¾ÈçºÎ´´½¨ÎÄ¼ş¡¢¶ÁÈ¡ÎÄ¼ş¡¢´´½¨Ä¿Â¼ºÍÉ¾³ıÎÄ¼ş
*			²¢²âÊÔÁËÎÄ¼ş¶ÁĞ´ËÙ¶È¡£
*
*	ĞŞ¸Ä¼ÇÂ¼ :
*		°æ±¾ºÅ  ÈÕÆÚ        ×÷Õß     ËµÃ÷
*		V1.0    2013-02-01 armfly  ÕıÊ½·¢²¼
*
*	Copyright (C), 2013-2014, °²¸»À³µç×Ó www.armfly.com
*
*********************************************************************************************************
*/
/*
unsigned char read_all_program_head(void)
char input_one_program(char cent)
char output_one_program(char cent)
u8  creat_spi_program_table(char *buf)
u8  creat_usb_program_table(char *buf,int len,char number)
char read_all_usb_file(void)
u8 read_one_ProgramStep(char *name)//promp
void get_data(int nb,int cent)
u8 delete_one_file(void)
u8 Save_Program(void)
u8 Program_SaveAs(void);//fmc160831
int generate_new_file(void)
u8  creat_program_table(char *buf,int len)
u8 Read_Spi_File(void)
u8 read_and_check_ProgramStep(int flag)
*/
//demo_fatfs.h
#include "bsp.h"
#include "ff.h"			/* FatFSÎÄ¼şÏµÍ³Ä£¿é*/
#include "demo_fatfs.h"
#include "usbh_bsp_msc.h"
#include "GUI.h"
#include "SystemPrameter.h"
#include  "ManageStep.h"
#include  "ManageStepOption.h"
#include "prompt.h"

#include "usbh_hid_core.h"
#define FILE_HEAD_LENCH 100
#include "SystemInOut.h"  //fmc161013
#define FS_VOLUME_USB1		"2:/"
#define FS_VOLUME_SPI1		"3:/"

// #include "MainTask.h"
unsigned char read_all_program_head(void);//
extern  uint8_t sf_WriteBuffer(uint8_t* _pBuf, uint32_t _uiWriteAddr, uint16_t _usWriteSize);
extern int Step_nb;  //³ÌĞò²½ÖèÊı
extern int flag_update_busy;
unsigned char Save_flag(void);
extern  unsigned char ProgramMax;
extern uint8_t s_spiBuf[6*1024];//fmc161008
extern char *SIF_Font19_address;
extern char *SIF_Font24_address;
extern u8 UART_Send_Buf[600];//FMC160923
int CharToIntTime(int nb);
//#include "MainTask.h"
//#include "usb_bsp_msc.h"		/* usbµ×²ãÇı¶¯ */
/* ÓÃÓÚ²âÊÔ¶ÁĞ´ËÙ¶È */
#define TEST_FILE_LEN			(2*1024*1024)	/* ÓÃÓÚ²âÊÔµÄÎÄ¼ş³¤¶È */
#define BUF_SIZE				(4*1024)		/* Ã¿´Î¶ÁĞ´SD¿¨µÄ×î´óÊı¾İ³¤¶È */
uint8_t g_TestBuf[BUF_SIZE];
char *update103_buf;
//PROGRAMSTEP UsbProgramStep[STEPNODE_MAX];
PROGRAMNAME UsbProgramName[PROGRAM_MAX];
//int Step_nb=0;//³ÌĞòÎÄ¼şÀïSTEPÊı
int usb_program_number,spi_program_number;//UÅÌÓĞĞ§ÎÄ¼şÊı
FIL file;
FATFS fs;  //fmc
FATFS fs_usb,fs_spi;
FIL file_spi,file_usb;
int update_data_nember;
char update_file_name[20];
unsigned char ReadFile_font(int nb);
GUI_HMEM hMem1,hMem2,hMem3;
//extern unsigned char ProgramMax;
#define program_buf_len 1024*4//FMC160921
char program_buf[program_buf_len];//³ÌĞòÎÄ¼ş»º´æ
extern unsigned char flag_start_update,flag_update_one_ok;
u8 read_one_ProgramStep(char *name);
/* ½öÔÊĞí±¾ÎÄ¼şÄÚµ÷ÓÃµÄº¯ÊıÉùÃ÷ */
static void DispMenu(void);
//static void ViewRootDir(char *_ucVolume);
static void CreateNewFile(char *_ucVolume);
static void ReadFileData(char *_ucVolume);
static void CreateDir(char *_ucVolume);
static void DeleteDirFile(char *_ucVolume);
static void WriteFileTest(void);
static void CreateNewFile_1k(char *_ucVolume);
extern void Refresh_Pragram_Row( void);
u8  creat_usb_program_table(char *buf,int len,char number);
void ReadFile_background(char *ad);
u8 delete_one_file(void);
extern u8 read_eep_progrm(void);
extern u8 Write_eep_progrm(void);
extern u8 del_eep_progrm(void);
extern void refresh_PROGBAR(int cent);
extern void beep(void );
u8 Usb_Copy1(void);
// void ReadFile_ziti(char *ad);
void clear_program_name(void);
void DemoFatFS(void);
u8 Save_Program(void);
int program_int_buf[20];
static void FileFormat_spi(void);
//extern void USB_POWER_GPIO_Config ( void );//Êä³ö¿ÚÅäÖÃ
FRESULT f_mkfs (const TCHAR* path, BYTE sfd, UINT au);
/* FatFs APIµÄ·µ»ØÖµSPI  */
static const char * FR_Table[]=
{
    "FR_OK£º³É¹¦",				                             /* (0) Succeeded */
    "FR_DISK_ERR£ºµ×²ãÓ²¼ş´íÎó",			                 /* (1) A hard error occurred in the low level disk I/O layer */
    "FR_INT_ERR£º¶ÏÑÔÊ§°Ü",				                     /* (2) Assertion failed */
    "FR_NOT_READY£ºÎïÀíÇı¶¯Ã»ÓĞ¹¤×÷",			             /* (3) The physical drive cannot work */
    "FR_NO_FILE£ºÎÄ¼ş²»´æÔÚ",				                 /* (4) Could not find the file */
    "FR_NO_PATH£ºÂ·¾¶²»´æÔÚ",				                 /* (5) Could not find the path */
    "FR_INVALID_NAME£ºÎŞĞ§ÎÄ¼şÃû",		                     /* (6) The path name format is invalid */
    "FR_DENIED£ºÓÉÓÚ½ûÖ¹·ÃÎÊ»òÕßÄ¿Â¼ÒÑÂú·ÃÎÊ±»¾Ü¾ø",         /* (7) Access denied due to prohibited access or directory full */
    "FR_EXIST£ºÎÄ¼şÒÑ¾­´æÔÚ",			                     /* (8) Access denied due to prohibited access */
    "FR_INVALID_OBJECT£ºÎÄ¼ş»òÕßÄ¿Â¼¶ÔÏóÎŞĞ§",		         /* (9) The file/directory object is invalid */
    "FR_WRITE_PROTECTED£ºÎïÀíÇı¶¯±»Ğ´±£»¤",		             /* (10) The physical drive is write protected */
    "FR_INVALID_DRIVE£ºÂß¼­Çı¶¯ºÅÎŞĞ§",		                 /* (11) The logical drive number is invalid */
    "FR_NOT_ENABLED£º¾íÖĞÎŞ¹¤×÷Çø",			                 /* (12) The volume has no work area */
    "FR_NO_FILESYSTEM£ºÃ»ÓĞÓĞĞ§µÄFAT¾í",		             /* (13) There is no valid FAT volume */
    "FR_MKFS_ABORTED£ºÓÉÓÚ²ÎÊı´íÎóf_mkfs()±»ÖÕÖ¹",	         /* (14) The f_mkfs() aborted due to any parameter error */
    "FR_TIMEOUT£ºÔÚ¹æ¶¨µÄÊ±¼äÄÚÎŞ·¨»ñµÃ·ÃÎÊ¾íµÄĞí¿É",		 /* (15) Could not get a grant to access the volume within defined period */
    "FR_LOCKED£ºÓÉÓÚÎÄ¼ş¹²Ïí²ßÂÔ²Ù×÷±»¾Ü¾ø",				 /* (16) The operation is rejected according to the file sharing policy */
    "FR_NOT_ENOUGH_CORE£ºÎŞ·¨·ÖÅä³¤ÎÄ¼şÃû¹¤×÷Çø",		     /* (17) LFN working buffer could not be allocated */
    "FR_TOO_MANY_OPEN_FILES£ºµ±Ç°´ò¿ªµÄÎÄ¼şÊı´óÓÚ_FS_SHARE", /* (18) Number of open files > _FS_SHARE */
    "FR_INVALID_PARAMETER£º²ÎÊıÎŞĞ§"	                     /* (19) Given parameter is invalid */
};
//******************************************

void bsp_InitKey1(void)  //ÊäÈë¿Ú ÅäÖÃ
{
    GPIO_InitTypeDef GPIO_InitStructure;

    // µÚ1²½£º´ò¿ªGPIOÊ±ÖÓ */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC | RCC_AHB1Periph_GPIOG, ENABLE);

    // µÚ2²½£ºÅäÖÃËùÓĞµÄ°´¼üGPIOÎª¸¡¶¯ÊäÈëÄ£Ê½(Êµ¼ÊÉÏCPU¸´Î»ºó¾ÍÊÇÊäÈë×´Ì¬)
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;		// ÉèÎªÊäÈë¿Ú
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		//ÉèÎªÍÆÍìÄ£Ê½
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;	//ÎŞĞè¡¢ÉÏ¡¢ÏÂÀ­µç×è
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;	//IO¿Ú×î´óËÙ¶È

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_Init(GPIOG, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;// PG6\PG9Îª¼üÅÌÊäÈë
    GPIO_Init(GPIOG, &GPIO_InitStructure);
    if ((GPIOG->IDR & GPIO_Pin_6) == 0)
        return;
    if ((GPIOG->IDR & GPIO_Pin_9) == 0)
        return;
}
//****************************************
void USB_POWER_GPIO_Config ( void )//Êä³ö¿ÚÅäÖÃ
{
    /*¶¨ÒåÒ»¸öGPIO_InitTypeDefÀàĞÍµÄ½á¹¹Ìå*/
    GPIO_InitTypeDef GPIO_InitStructure;


    // ÅäÖÃ LED1 Òı½Å
    RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOH, ENABLE );

    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init (GPIOA, & GPIO_InitStructure );	//*/

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init (GPIOA, & GPIO_InitStructure );	//*/
    //GPIO_ResetBits ( GPIOA, GPIO_Pin_0 );  =0
    GPIO_SetBits   ( GPIOA, GPIO_Pin_0 );  //=1
    GPIO_SetBits   ( GPIOA, GPIO_Pin_9 );
    /* ÅäÖÃ LED2 Òı½Å */
    /*RCC_AHB1PeriphClockCmd( RCC_AHB1Periph_GPIOH, ENABLE );
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11;
    GPIO_Init ( macLED2_GPIO_PORT, & GPIO_InitStructure );	*/
}
//***************************************************

/*
*********************************************************************************************************
*	º¯ Êı Ãû: DemoFatFS
*	¹¦ÄÜËµÃ÷: FatFSÎÄ¼şÏµÍ³ÑİÊ¾Ö÷³ÌĞò
*	ĞÎ    ²Î£ºÎŞ
*	·µ »Ø Öµ: ÎŞ
*********************************************************************************************************
*/

//***********
void DemoFatFS(void)
{
    uint8_t cmd;
    uint8_t ucVolume = 0;

    /* Init Host Library */
#ifdef USE_USB_OTG_FS
    USBH_Init(&USB_OTG_Core,
              USB_OTG_FS_CORE_ID,
              &USB_Host,
              &USBH_MSC_cb,
              &USRH_cb);
#else
    USBH_Init(&USB_OTG_Core,
              USB_OTG_HS_CORE_ID,
              &USB_Host,
              &USBH_MSC_cb,
              &USRH_cb);
#endif
    USB_POWER_GPIO_Config();
    /* ´òÓ¡ÃüÁîÁĞ±í£¬ÓÃ»§¿ÉÒÔÍ¨¹ı´®¿Ú²Ù×÷Ö¸Áî */
    DispMenu();
    while (1)
    {
        //bsp_Idle();		/* Õâ¸öº¯ÊıÔÚbsp.cÎÄ¼ş¡£ÓÃ»§¿ÉÒÔĞŞ¸ÄÕâ¸öº¯ÊıÊµÏÖCPUĞİÃßºÍÎ¹¹· */

        USBH_Process(&USB_OTG_Core, &USB_Host);

        if (comGetChar(COM7, &cmd))	/* ´Ó´®¿Ú¶ÁÈëÒ»¸ö×Ö·û(·Ç×èÈû·½Ê½) */
        {
            printf("\r\n");
            switch (cmd)
            {
            case '0':
                return;
            case '1':
                printf("¡¾1 - ÏÔÊ¾SD¿¨¸ùÄ¿Â¼ÎÄ¼ş¡¿\r\n");
                //ViewRootDir(FS_VOLUME_SD);			/* ÏÔÊ¾SD¿¨¸ùÄ¿Â¼ÏÂµÄÎÄ¼şÃû */
                //printf("¡¾1 - ÏÔÊ¾NAND Flash¸ùÄ¿Â¼ÎÄ¼ş¡¿\r\n");
                //ViewRootDir(FS_VOLUME_NAND);		/* ÏÔÊ¾UÅÌ¸ùÄ¿Â¼ÏÂµÄÎÄ¼şÃû */
                printf("¡¾1 - ÏÔÊ¾UÅÌ¸ùÄ¿Â¼ÎÄ¼ş¡¿\r\n");
                //ViewRootDir(FS_VOLUME_USB);		/* ÏÔÊ¾UÅÌ¸ùÄ¿Â¼ÏÂµÄÎÄ¼şÃû */
                //		printf("¡¾1 - ÏÔÊ¾SPI¸ùÄ¿Â¼ÎÄ¼ş¡¿\r\n");
                //		ViewRootDir(FS_VOLUME_SPI	);		/* ÏÔÊ¾UÅÌ¸ùÄ¿Â¼ÏÂµÄÎÄ¼şÃû */
                break;

            case '2':
                printf("¡¾2 - CreateNewFile¡¿SD¿¨\r\n");
                CreateNewFile(FS_VOLUME_SD);	/* ´´½¨Ò»¸öĞÂÎÄ¼ş,Ğ´ÈëÒ»¸ö×Ö·û´® */
                //	printf("¡¾2 - CreateNewFile¡¿NAND\r\n");
                //		CreateNewFile(FS_VOLUME_NAND);	/* ´´½¨Ò»¸öĞÂÎÄ¼ş,Ğ´ÈëÒ»¸ö×Ö·û´® */
                printf("¡¾2 - CreateNewFile¡¿UÅÌĞ´1K×Ö½Ú\r\n");
                CreateNewFile_1k(FS_VOLUME_USB);//Ğ´1K×Ö½Úµ½UÅÌ
                //	printf("¡¾2 - CreateNewFile¡¿SPI\r\n");
                //	  CreateNewFile(FS_VOLUME_SPI);//
                break;

            case '3':
                printf("¡¾3 - ReadFileData¡¿\r\n");
                ReadFileData(FS_VOLUME_SD);		/* ¶ÁÈ¡¸ùÄ¿Â¼ÏÂarmfly.txtµÄÄÚÈİ */
                //	ReadFileData(FS_VOLUME_NAND);		/* ¶ÁÈ¡¸ùÄ¿Â¼ÏÂarmfly.txtµÄÄÚÈİ */
                ReadFileData(FS_VOLUME_USB);		/* ¶ÁÈ¡¸ùÄ¿Â¼ÏÂarmfly.txtµÄÄÚÈİ */
                ReadFileData(FS_VOLUME_SPI);
                break;

            case '4':
                printf("¡¾4 - CreateDir¡¿\r\n");
                CreateDir(FS_VOLUME_SD);		/* ´´½¨Ä¿Â¼ */
                //CreateDir(FS_VOLUME_NAND);		/* ´´½¨Ä¿Â¼ */
                CreateDir(FS_VOLUME_USB);		/* ´´½¨Ä¿Â¼ */
                break;

            case '5':
                printf("¡¾5 - DeleteDirFile¡¿\r\n");
                DeleteDirFile(FS_VOLUME_SD);	/* É¾³ıÄ¿Â¼ºÍÎÄ¼ş */
                //DeleteDirFile(FS_VOLUME_NAND);	/* É¾³ıÄ¿Â¼ºÍÎÄ¼ş */
                DeleteDirFile(FS_VOLUME_USB);	/* É¾³ıÄ¿Â¼ºÍÎÄ¼ş */
                break;

            case '6':
                printf("¡¾6 - TestSpeed¡¿\r\n");
                WriteFileTest();	/* ËÙ¶È²âÊÔ */
                break;

            case '7':
                printf("¡¾1 - SPI¸ñÊ½»¯¡¿\r\n");
                //  FileFormat_spi();//fmc

                //	printf("Start Format(Low Level) NAND Flash......\r\n");
                //	NAND_Format();
                //	printf("NAND Flash Format Ok\r\n");
                break;

            case 'V':		/* ÇĞ»»µ±Ç°ÅÌ·û */
            case 'v':
                if (ucVolume == FS_SD)
                {
                    ucVolume = FS_NAND;
                }
                else if (ucVolume == FS_NAND)
                {
                    ucVolume = FS_USB;
                }
                else
                {
                    ucVolume = FS_SD;
                }
                break;

            default:
                DispMenu();
                break;
            }
        }	/* comGetChar(COM1, &cmd) */
    }
}

/*
*********************************************************************************************************
*	º¯ Êı Ãû: DispMenu
*	¹¦ÄÜËµÃ÷: ÏÔÊ¾²Ù×÷ÌáÊ¾²Ëµ¥
*	ĞÎ    ²Î£ºÎŞ
*	·µ »Ø Öµ: ÎŞ
*********************************************************************************************************
*/
static void DispMenu(void)
{
    printf("\r\n------------------------------------------------\r\n");
    printf("ÇëÑ¡Ôñ²Ù×÷ÃüÁî:\r\n");
    printf("0 - ·µ»ØÉÏÒ»¼¶\r\n");
    printf("1 - ÏÔÊ¾¸ùÄ¿Â¼ÏÂµÄÎÄ¼şÁĞ±í\r\n");
    printf("2 - ´´½¨Ò»¸öĞÂÎÄ¼şarmfly.txt\r\n");
    printf("3 - ¶Áarmfly.txtÎÄ¼şµÄÄÚÈİ\r\n");
    printf("4 - ´´½¨Ä¿Â¼\r\n");
    printf("5 - É¾³ıÎÄ¼şºÍÄ¿Â¼\r\n");
    printf("6 - ¶ÁĞ´ÎÄ¼şËÙ¶È²âÊÔ\r\n");
    printf("7 - NAND Flash µÍ¼¶¸ñÊ½»¯\r\n");
}

/*
*********************************************************************************************************
*	º¯ Êı Ãû: ViewRootDir
*	¹¦ÄÜËµÃ÷: ÏÔÊ¾SD¿¨¸ùÄ¿Â¼ÏÂµÄÎÄ¼şÃû
*	ĞÎ    ²Î: _ucVolume : ´ÅÅÌ¾í±ê 0 - 2
*	·µ »Ø Öµ: ÎŞ
*********************************************************************************************************
*/


//**************************
/* static void ViewRootDir(char *_ucVolume)
{
	// ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ
	FRESULT result;
	//FATFS fs;
	DIR DirInf;
	FILINFO FileInf;
	uint32_t cnt = 0;
	char lfname[256];
	char path[32];


	result = f_mount(&fs, _ucVolume, 0);
	if (result != FR_OK)
	{
		printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü (%d)\r\n", result);
	}


	sprintf(path, "%s/", _ucVolume);
	result = f_opendir(&DirInf, path);
	if (result != FR_OK)
	{
		printf("´ò¿ª¸ùÄ¿Â¼Ê§°Ü (%d)\r\n", result);
		return;
	}


	FileInf.lfname = lfname;
	FileInf.lfsize = 256;

	printf("ÊôĞÔ        |  ÎÄ¼ş´óĞ¡ | ¶ÌÎÄ¼şÃû | ³¤ÎÄ¼şÃû\r\n");
	for (cnt = 0; ;cnt++)
	{
		result = f_readdir(&DirInf,&FileInf);
		if (result != FR_OK || FileInf.fname[0] == 0)
		{
			break;
		}

		if (FileInf.fname[0] == '.')
		{
			continue;
		}

		// ÅĞ¶ÏÊÇÎÄ¼ş»¹ÊÇ×ÓÄ¿Â¼
		if (FileInf.fattrib & AM_DIR)
		{
			printf("(0x%02d)Ä¿Â¼  ", FileInf.fattrib);
		}
		else
		{
			printf("(0x%02d)ÎÄ¼ş  ", FileInf.fattrib);
		}

		// ´òÓ¡ÎÄ¼ş´óĞ¡, ×î´ó4G
		printf(" %10d", FileInf.fsize);

		printf("  %s |", FileInf.fname);	// ¶ÌÎÄ¼şÃû

		printf("  %s\r\n", (char *)FileInf.lfname);	// ³¤ÎÄ¼şÃû
	}

	// Ğ¶ÔØÎÄ¼şÏµÍ³
	f_mount(NULL,_ucVolume, 0);
}*/

/*
*********************************************************************************************************
*	º¯ Êı Ãû: CreateNewFile
*	¹¦ÄÜËµÃ÷: ÔÚSD¿¨´´½¨Ò»¸öĞÂÎÄ¼ş£¬ÎÄ¼şÄÚÈİÌîĞ´¡°www.armfly.com¡±
*	ĞÎ    ²Î£ºÎŞ
*	·µ »Ø Öµ: ÎŞ
*********************************************************************************************************
*/

//***************************
static void CreateNewFile(char *_ucVolume)
{
    /* ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ */
    FRESULT result;
//	FATFS fs;
//	FIL file;
    DIR DirInf;
    uint32_t bw;
    char path[32];

    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, _ucVolume, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü (%d)\r\n", result);
    }

    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    sprintf(path, "%s/", _ucVolume);
    result = f_opendir(&DirInf, path);
    if (result != FR_OK)
    {
        printf("´ò¿ª¸ùÄ¿Â¼Ê§°Ü (%d)\r\n", result);
        return;
    }

    /* ´ò¿ªÎÄ¼ş */
    sprintf(path, "%s/armfly.txt", _ucVolume);
    result = f_open(&file, path, FA_CREATE_ALWAYS | FA_WRITE);

    /* Ğ´Ò»´®Êı¾İ */
    result = f_write(&file, "FatFS Write Demo   www.armfly.com \r\n", 34, &bw);
    if (result == FR_OK)
    {
        printf("%s ÎÄ¼şĞ´Èë³É¹¦\r\n", path);
    }
    else
    {
        printf("%s ÎÄ¼şĞ´ÈëÊ§°Ü\r\n", path);
    }

    /* ¹Ø±ÕÎÄ¼ş*/
    f_close(&file);

    /* Ğ¶ÔØÎÄ¼şÏµÍ³ */
    f_mount(NULL,_ucVolume, 0);
}
static void CreateNewFile_1k(char *_ucVolume)
{
    /* ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ */
    FRESULT result;
//	FATFS fs;
//	FIL file;
    DIR DirInf;
    uint32_t bw;
    char path[32];
    char tt[1024];
    uint32_t i;
    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, _ucVolume, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü (%d)\r\n", result);
    }

    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    sprintf(path, "%s/", _ucVolume);
    result = f_opendir(&DirInf, path);
    if (result != FR_OK)
    {
        printf("´ò¿ª¸ùÄ¿Â¼Ê§°Ü (%d)\r\n", result);
        return;
    }

    /* ´ò¿ªÎÄ¼ş */
    sprintf(path, "%s/armfly.txt", _ucVolume);
    result = f_open(&file, path, FA_CREATE_ALWAYS | FA_WRITE);
// result =f_open(&file, path, FA_WRITE);
    /* Ğ´Ò»´®Êı¾İ */
    for(i=0; i<1024; i++)
        tt[i]=0x30;
    result = f_write(&file, tt, 1024, &bw);
    //f_lseek(&file,5);
//	f_close(&file);
//	sprintf(path, "%s/", _ucVolume);
//	result = f_opendir(&DirInf, path);
    //sprintf(path, "%s/armfly.txt", _ucVolume);
    //result = f_open(&file, path, FA_CREATE_ALWAYS | FA_WRITE);

    /*for(i=0;i<1024;i++)
        tt[i]=0x33;
    f_lseek(&file,4);
    result = f_write(&file, tt, 10, &bw);*/
    if (result == FR_OK)
    {
        printf("%s ÎÄ¼şĞ´Èë³É¹¦\r\n", path);
    }
    else
    {
        printf("%s ÎÄ¼şĞ´ÈëÊ§°Ü\r\n", path);
    }

    /* ¹Ø±ÕÎÄ¼ş*/
    f_close(&file);

    /* Ğ¶ÔØÎÄ¼şÏµÍ³ */
    f_mount(NULL,_ucVolume, 0);
}

/*
*********************************************************************************************************
*	º¯ Êı Ãû: ReadFileData
*	¹¦ÄÜËµÃ÷: ¶ÁÈ¡ÎÄ¼şarmfly.txtÇ°128¸ö×Ö·û£¬²¢´òÓ¡µ½´®¿Ú
*	ĞÎ    ²Î£ºÎŞ
*	·µ »Ø Öµ: ÎŞ
*********************************************************************************************************
*/
static void ReadFileData(char *_ucVolume)
{
    /* ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ */
    FRESULT result;
//	FATFS fs;
//	FIL file;
    DIR DirInf;
    uint32_t bw;
    char buf[128];
    char path[32];

    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, _ucVolume, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü(%d)\r\n", result);
    }

    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    sprintf(path, "%s/", _ucVolume);
    result = f_opendir(&DirInf, path); 	/* 1: ±íÊ¾ÅÌ·û */
    if (result != FR_OK)
    {
        printf("´ò¿ª¸ùÄ¿Â¼Ê§°Ü(%d)\r\n", result);
        return;
    }

    /* ´ò¿ªÎÄ¼ş */
    sprintf(path, "%s/armfly.txt", _ucVolume);
    result = f_open(&file, path, FA_OPEN_EXISTING | FA_READ);
    if (result !=  FR_OK)
    {
        printf("Don't Find File : %s\r\n", path);
        return;
    }

    /* ¶ÁÈ¡ÎÄ¼ş */
    result = f_read(&file, &buf, sizeof(buf) - 1, &bw);
    if (bw > 0)
    {
        buf[bw] = 0;
        printf("\r\n%s ÎÄ¼şÄÚÈİ : \r\n%s\r\n", path,buf);
    }
    else
    {
        printf("\r\n %sÎÄ¼şÄÚÈİ : \r\n", path);
    }

    /* ¹Ø±ÕÎÄ¼ş*/
    f_close(&file);

    /* Ğ¶ÔØÎÄ¼şÏµÍ³ */
    f_mount(NULL,_ucVolume, 0);
}


//*************************************
void ReadFile_background(char *ad)
{
    /* ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ */
    FRESULT result;
//	FATFS fs;
//	FIL file;
    DIR DirInf;
    uint32_t bw;
    //char buf[128];
    char path[32];
    char tt[2]= {"3:"};
    char *_ucVolume;
    _ucVolume=tt;
    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, _ucVolume, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü(%d)\r\n", result);
    }

    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    sprintf(path, "%s/", _ucVolume);
    result = f_opendir(&DirInf, path); 	/* 1: ±íÊ¾ÅÌ·û */
    if (result != FR_OK)
    {
        printf("´ò¿ª¸ùÄ¿Â¼Ê§°Ü(%d)\r\n", result);
        return;
    }

    /* ´ò¿ªÎÄ¼ş */
    if(AdvancePra.OemFlag==OEM_AOSHENG)
        sprintf(path, "%s/Loading.jpg", _ucVolume);//ÎÄ¼şÃû´ÓÕâÀï¸´ÖÆµ½path  FMC
    else if(AdvancePra.OemFlag==OEM_OTHER)
        sprintf(path, "%s/loading_other.jpg", _ucVolume);//ÎÄ¼şÃû´ÓÕâÀï¸´ÖÆµ½path  FMC
    else// if(AdvancePra.OemFlag==OEM_NEUTRAL)
        sprintf(path, "%s/loading_neutral.jpg", _ucVolume);//ÎÄ¼şÃû´ÓÕâÀï¸´ÖÆµ½path  FMC
    result = f_open(&file, path, FA_OPEN_EXISTING | FA_READ);
    if (result !=  FR_OK)
    {
        printf("Don't Find File : %s\r\n", path);
        return;
    }

    /* ¶ÁÈ¡ÎÄ¼ş */
    result = f_read(&file,ad, file.fsize, &bw);
    if (bw > 0)
    {
        //buf[bw] = 0;
        //printf("\r\n%s ÎÄ¼şÄÚÈİ : \r\n%s\r\n", path,buf);
    }
    else
    {
        printf("\r\n %sÎÄ¼şÄÚÈİ : \r\n", path);
    }

    /* ¹Ø±ÕÎÄ¼ş*/
    f_close(&file);

    /* Ğ¶ÔØÎÄ¼şÏµÍ³ */
    f_mount(NULL,_ucVolume, 0);
}
/*void ReadFile_ziti(char *ad)
{
	// ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ
	FRESULT result;
//	FATFS fs;
//	FIL file;
	DIR DirInf;
	uint32_t bw;
	//char buf[128];
	char path[32];
	char tt[2]={"3:"};
	char *_ucVolume;
   _ucVolume=tt;
 	// ¹ÒÔØÎÄ¼şÏµÍ³
	result = f_mount(&fs, _ucVolume, 0);
	if (result != FR_OK)
	{
		printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü(%d)\r\n", result);
	}


	sprintf(path, "%s/", _ucVolume);
	result = f_opendir(&DirInf, path);
	if (result != FR_OK)
	{
		printf("´ò¿ª¸ùÄ¿Â¼Ê§°Ü(%d)\r\n", result);
		return;
	}


	sprintf(path, "%s/yahe19.sif", _ucVolume);//ÎÄ¼şÃû´ÓÕâÀï¸´ÖÆµ½path  FMC
	result = f_open(&file, path, FA_OPEN_EXISTING | FA_READ);
	if (result !=  FR_OK)
	{
		printf("Don't Find File : %s\r\n", path);
		return;
	}


	result = f_read(&file,ad, file.fsize, &bw);
	if (bw > 0)
	{
		//buf[bw] = 0;
		//printf("\r\n%s ÎÄ¼şÄÚÈİ : \r\n%s\r\n", path,buf);
	}
	else
	{
		printf("\r\n %sÎÄ¼şÄÚÈİ : \r\n", path);
	}


	f_close(&file);

	f_mount(NULL,_ucVolume, 0);
}*/
//***************************
unsigned char ReadFile_font(int nb)
{
    /* ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ */
    FRESULT result;
//	FATFS fs;
//	FIL file;

    DIR DirInf;
    uint32_t bw;
    //char buf[128];
    char path[32];
    char tt[2]= {"3:"};

    char *_ucVolume,*_acBuffer1;
    _ucVolume=tt;
    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, _ucVolume, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {   return 1;
        //printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü(%d)\r\n", result);
    }

    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    sprintf(path, "%s/", _ucVolume);
    result = f_opendir(&DirInf, path); 	/* 1: ±íÊ¾ÅÌ·û */
    if (result != FR_OK)
    {
        //printf("´ò¿ª¸ùÄ¿Â¼Ê§°Ü(%d)\r\n", result);
        return 1;
    }

    /* ´ò¿ªÎÄ¼ş */
    if(nb==1)
        sprintf(path, "%s/yahe19.sif", _ucVolume);
    else
        sprintf(path, "%s/yahe24.sif", _ucVolume);
    result = f_open(&file,path, FA_OPEN_EXISTING | FA_READ);
    if (result !=  FR_OK)
    {
        //printf("Don't Find File : %s\r\n", path);
        return 1;
    }
//	*err=1;
    if(nb==1)
    {
        hMem1=GUI_ALLOC_AllocZero(file.fsize);//????????,?????? FMC
        SIF_Font19_address=GUI_ALLOC_h2p(hMem1);
        result = f_read(&file,SIF_Font19_address, file.fsize, &bw);
        if (result !=  FR_OK)
            return 1;

    }
    else
    {
        hMem2=GUI_ALLOC_AllocZero(file.fsize);//????????,?????? FMC
        SIF_Font24_address=GUI_ALLOC_h2p(hMem2);
        result = f_read(&file,SIF_Font24_address, file.fsize, &bw);
        if (result !=  FR_OK)
            return 1;
    }
    /* ¶ÁÈ¡ÎÄ¼ş */
    //result = f_read(&file,_acBuffer1, file.fsize, &bw);
    if (bw > 0)
    {
        //buf[bw] = 0;
        //printf("\r\n%s ÎÄ¼şÄÚÈİ : \r\n%s\r\n", path,buf);
    }
    else
    {
        printf("\r\n %sÎÄ¼şÄÚÈİ : \r\n", path);
    }

    /* ¹Ø±ÕÎÄ¼ş*/
    f_close(&file);

    /* Ğ¶ÔØÎÄ¼şÏµÍ³ */
    f_mount(NULL,_ucVolume, 0);

    return 0;
}
/*
*********************************************************************************************************
*	º¯ Êı Ãû: CreateDir
*	¹¦ÄÜËµÃ÷: ÔÚSD¿¨¸ùÄ¿Â¼´´½¨Dir1ºÍDir2Ä¿Â¼£¬ÔÚDir1Ä¿Â¼ÏÂ´´½¨×ÓÄ¿Â¼Dir1_1
*	ĞÎ    ²Î£ºÎŞ
*	·µ »Ø Öµ: ÎŞ
*********************************************************************************************************
*/
static void CreateDir(char *_ucVolume)
{
    /* ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ */
    FRESULT result;
//	FATFS fs;
    char path[32];

    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, _ucVolume, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü (%d)\r\n", result);
    }

    /* ´´½¨Ä¿Â¼/Dir1 */
    sprintf(path, "%s/Dir1", _ucVolume);
    result = f_mkdir(path);
    if (result == FR_OK)
    {
        printf("f_mkdir %s Ok\r\n", path);
    }
    else if (result == FR_EXIST)
    {
        printf("%s Ä¿Â¼ÒÑ¾­´æÔÚ(%d)\r\n",path, result);
    }
    else
    {
        printf("f_mkdir %s Ê§°Ü (%d)\r\n",path, result);
        return;
    }

    /* ´´½¨Ä¿Â¼/Dir2 */
    sprintf(path, "%s/Dir2", _ucVolume);
    result = f_mkdir(path);
    if (result == FR_OK)
    {
        printf("f_mkdir %s Ok\r\n", path);
    }
    else if (result == FR_EXIST)
    {
        printf("%s Ä¿Â¼ÒÑ¾­´æÔÚ(%d)\r\n", path, result);
    }
    else
    {
        printf("f_mkdir %s Ê§°Ü (%d)\r\n", path, result);
        return;
    }

    /* ´´½¨×ÓÄ¿Â¼ /Dir1/Dir1_1	   ×¢Òâ£º´´½¨×ÓÄ¿Â¼Dir1_1Ê±£¬±ØĞëÏÈ´´½¨ºÃDir1 */
    sprintf(path, "%s//Dir1/Dir1_1", _ucVolume);
    result = f_mkdir(path);
    if (result == FR_OK)
    {
        printf("f_mkdir %s ³É¹¦\r\n", path);
    }
    else if (result == FR_EXIST)
    {
        printf("%s Ä¿Â¼ÒÑ¾­´æÔÚ (%d)\r\n",path, result);
    }
    else
    {
        printf("f_mkdir %s Ê§°Ü (%d)\r\n",path, result);
        return;
    }

    /* Ğ¶ÔØÎÄ¼şÏµÍ³ */
    f_mount(NULL,_ucVolume, 0);
}

/*
*********************************************************************************************************
*	º¯ Êı Ãû: DeleteDirFile
*	¹¦ÄÜËµÃ÷: É¾³ıSD¿¨¸ùÄ¿Â¼ÏÂµÄ armfly.txt ÎÄ¼şºÍ Dir1£¬Dir2 Ä¿Â¼
*	ĞÎ    ²Î£ºÎŞ
*	·µ »Ø Öµ: ÎŞ
*********************************************************************************************************
*/
static void DeleteDirFile(char *_ucVolume)
{
    /* ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ */
    FRESULT result;
//	FATFS fs;
    char FileName[13];
    uint8_t i;
    char path[32];

    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, _ucVolume, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü (%d)\r\n", result);
    }


    /* É¾³ıÄ¿Â¼/Dir1 ¡¾ÒòÎª»¹´æÔÚÄ¿Â¼·Ç¿Õ£¨´æÔÚ×ÓÄ¿Â¼)£¬ËùÒÔÕâ´ÎÉ¾³ı»áÊ§°Ü¡¿*/
    sprintf(path, "%s/Dir1", _ucVolume);
    result = f_unlink(path);
    if (result == FR_OK)
    {
        printf("É¾³ıÄ¿Â¼%s³É¹¦\r\n", path);
    }
    else if (result == FR_NO_FILE)
    {
        printf("Ã»ÓĞ·¢ÏÖÎÄ¼ş»òÄ¿Â¼ :%s\r\n", path);
    }
    else
    {
        printf("É¾³ı%sÊ§°Ü(´íÎó´úÂë = %d) ÎÄ¼şÖ»¶Á»òÄ¿Â¼·Ç¿Õ\r\n",path, result);
    }

    /* ÏÈÉ¾³ıÄ¿Â¼/Dir1/Dir1_1 */
    sprintf(path, "%s/Dir1/Dir1_1", _ucVolume);
    result = f_unlink(path);
    if (result == FR_OK)
    {
        printf("É¾³ı×ÓÄ¿Â¼%s³É¹¦\r\n", path);
    }
    else if ((result == FR_NO_FILE) || (result == FR_NO_PATH))
    {
        printf("Ã»ÓĞ·¢ÏÖÎÄ¼ş»òÄ¿Â¼ :%s\r\n", path);
    }
    else
    {
        printf("É¾³ı×ÓÄ¿Â¼%sÊ§°Ü(´íÎó´úÂë = %d) ÎÄ¼şÖ»¶Á»òÄ¿Â¼·Ç¿Õ\r\n", path, result);
    }

    /* ÏÈÉ¾³ıÄ¿Â¼/Dir1 */
    sprintf(path, "%s/Dir1", _ucVolume);
    result = f_unlink(path);
    if (result == FR_OK)
    {
        printf("É¾³ıÄ¿Â¼%s³É¹¦\r\n", path);
    }
    else if (result == FR_NO_FILE)
    {
        printf("Ã»ÓĞ·¢ÏÖÎÄ¼ş»òÄ¿Â¼ :%s\r\n", path);
    }
    else
    {
        printf("É¾³ı%sÊ§°Ü(´íÎó´úÂë = %d) ÎÄ¼şÖ»¶Á»òÄ¿Â¼·Ç¿Õ\r\n",path, result);
    }

    /* É¾³ıÄ¿Â¼/Dir2 */
    sprintf(path, "%s/Dir2", _ucVolume);
    result = f_unlink(path);
    if (result == FR_OK)
    {
        printf("É¾³ıÄ¿Â¼ %s ³É¹¦\r\n", path);
    }
    else if (result == FR_NO_FILE)
    {
        printf("Ã»ÓĞ·¢ÏÖÎÄ¼ş»òÄ¿Â¼ :%s\r\n", path);
    }
    else
    {
        printf("É¾³ı%sÊ§°Ü(´íÎó´úÂë = %d) ÎÄ¼şÖ»¶Á»òÄ¿Â¼·Ç¿Õ\r\n", path, result);
    }

    /* É¾³ıÎÄ¼ş armfly.txt */
    sprintf(path, "%s/armfly.txt", _ucVolume);
    result = f_unlink(path);
    if (result == FR_OK)
    {
        printf("É¾³ıÎÄ¼ş armfly.txt ³É¹¦\r\n");
    }
    else if (result == FR_NO_FILE)
    {
        printf("Ã»ÓĞ·¢ÏÖÎÄ¼ş»òÄ¿Â¼ :%s\r\n", "armfly.txt");
    }
    else
    {
        printf("É¾³ıarmfly.txtÊ§°Ü(´íÎó´úÂë = %d) ÎÄ¼şÖ»¶Á»òÄ¿Â¼·Ç¿Õ\r\n", result);
    }

    /* É¾³ıÎÄ¼ş speed1.txt */
    for (i = 0; i < 20; i++)
    {
        sprintf(FileName, "%s/Speed%02d.txt", _ucVolume, i);	/* Ã¿Ğ´1´Î£¬ĞòºÅµİÔö */
        result = f_unlink(FileName);
        if (result == FR_OK)
        {
            printf("É¾³ıÎÄ¼ş%s³É¹¦\r\n", FileName);
        }
        else if (result == FR_NO_FILE)
        {
            printf("Ã»ÓĞ·¢ÏÖÎÄ¼ş:%s\r\n", FileName);
        }
        else
        {
            printf("É¾³ı%sÎÄ¼şÊ§°Ü(´íÎó´úÂë = %d) ÎÄ¼şÖ»¶Á»òÄ¿Â¼·Ç¿Õ\r\n", FileName, result);
        }
    }

    /* Ğ¶ÔØÎÄ¼şÏµÍ³ */
    f_mount(NULL,_ucVolume, 0);
}

/*
*********************************************************************************************************
*	º¯ Êı Ãû: WriteFileTest
*	¹¦ÄÜËµÃ÷: ²âÊÔÎÄ¼ş¶ÁĞ´ËÙ¶È
*	ĞÎ    ²Î£ºÎŞ
*	·µ »Ø Öµ: ÎŞ
*********************************************************************************************************
*/
static void WriteFileTest(void)
{
    /* ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ */
    FRESULT result;
//	FATFS fs;
    //FIL file;
    DIR DirInf;
    uint32_t bw;
    uint32_t i,k;
    uint32_t runtime1,runtime2,timelen;
    uint8_t err = 0;
    char TestFileName[13];
    static uint8_t s_ucTestSn = 0;

    for (i = 0; i < sizeof(g_TestBuf); i++)
    {
        g_TestBuf[i] = (i / 512) + '0';
    }

    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, FS_VOLUME_NAND, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü (%d)\r\n", result);
    }

    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    result = f_opendir(&DirInf, "1:/"); /* Èç¹û²»´ø²ÎÊı£¬Ôò´Óµ±Ç°Ä¿Â¼¿ªÊ¼ */
    if (result != FR_OK)
    {
        printf("´ò¿ª¸ùÄ¿Â¼Ê§°Ü (%d)\r\n", result);
        return;
    }

    /* ´ò¿ªÎÄ¼ş */
    sprintf(TestFileName, "1:/Speed%02d.txt", s_ucTestSn++);		/* Ã¿Ğ´1´Î£¬ĞòºÅµİÔö */
    result = f_open(&file, TestFileName, FA_CREATE_ALWAYS | FA_WRITE);

    /* Ğ´Ò»´®Êı¾İ */
    printf("¿ªÊ¼Ğ´ÎÄ¼ş%s %dKB ...\r\n", TestFileName, TEST_FILE_LEN / 1024);
//	runtime1 = bsp_GetRunTime();	/* ¶ÁÈ¡ÏµÍ³ÔËĞĞÊ±¼ä */
    for (i = 0; i < TEST_FILE_LEN / BUF_SIZE; i++)
    {
        result = f_write(&file, g_TestBuf, sizeof(g_TestBuf), &bw);
        if (result == FR_OK)
        {
            if (((i + 1) % 8) == 0)
            {
                printf(".");
            }
        }
        else
        {
            err = 1;
            printf("%sÎÄ¼şĞ´Ê§°Ü\r\n", TestFileName);
            break;
        }
    }
//	runtime2 = bsp_GetRunTime();	/* ¶ÁÈ¡ÏµÍ³ÔËĞĞÊ±¼ä */

    if (err == 0)
    {
        timelen = (runtime2 - runtime1);
        printf("\r\n  Ğ´ºÄÊ± : %dms   Æ½¾ùĞ´ËÙ¶È : %dB/S (%dKB/S)\r\n",
               timelen,
               (TEST_FILE_LEN * 1000) / timelen,
               ((TEST_FILE_LEN / 1024) * 1000) / timelen);
    }

    f_close(&file);		/* ¹Ø±ÕÎÄ¼ş*/


    /* ¿ªÊ¼¶ÁÎÄ¼ş²âÊÔ */
    result = f_open(&file, TestFileName, FA_OPEN_EXISTING | FA_READ);
    if (result !=  FR_OK)
    {
        printf("Ã»ÓĞÕÒµ½ÎÄ¼ş: %s\r\n", TestFileName);
        return;
    }

    printf("¿ªÊ¼¶ÁÎÄ¼ş %dKB ...\r\n", TEST_FILE_LEN / 1024);
//	runtime1 = bsp_GetRunTime();	/* ¶ÁÈ¡ÏµÍ³ÔËĞĞÊ±¼ä */
    for (i = 0; i < TEST_FILE_LEN / BUF_SIZE; i++)
    {
        result = f_read(&file, g_TestBuf, sizeof(g_TestBuf), &bw);
        if (result == FR_OK)
        {
            if (((i + 1) % 8) == 0)
            {
                printf(".");
            }

            /* ±È½ÏĞ´ÈëµÄÊı¾İÊÇ·ñÕıÈ·£¬´ËÓï¾ä»áµ¼ÖÂ¶Á¿¨ËÙ¶È½á¹û½µµÍµ½ 3.5MBytes/S */
            for (k = 0; k < sizeof(g_TestBuf); k++)
            {
                if (g_TestBuf[k] != (k / 512) + '0')
                {
                    err = 1;
                    printf("Speed1.txt ÎÄ¼ş¶Á³É¹¦£¬µ«ÊÇÊı¾İ³ö´í\r\n");
                    break;
                }
            }
            if (err == 1)
            {
                break;
            }
        }
        else
        {
            err = 1;
            printf("Speed1.txt ÎÄ¼ş¶ÁÊ§°Ü\r\n");
            break;
        }
    }
//	runtime2 = bsp_GetRunTime();	/* ¶ÁÈ¡ÏµÍ³ÔËĞĞÊ±¼ä */

    if (err == 0)
    {
        timelen = (runtime2 - runtime1);
        printf("\r\n  ¶ÁºÄÊ± : %dms   Æ½¾ù¶ÁËÙ¶È : %dB/S (%dKB/S)\r\n", timelen,
               (TEST_FILE_LEN * 1000) / timelen, ((TEST_FILE_LEN / 1024) * 1000) / timelen);
    }

    /* ¹Ø±ÕÎÄ¼ş*/
    f_close(&file);

    /* Ğ¶ÔØÎÄ¼şÏµÍ³ */
    f_mount(NULL,FS_VOLUME_NAND, 0);
}

/***************************** °²¸»À³µç×Ó www.armfly.com (END OF FILE) *********************************/
/*
*********************************************************************************************************
*	º¯ Êı Ãû: FileFormat
*	¹¦ÄÜËµÃ÷: ÎÄ¼şÏµÍ³¸ñÊ½»¯
*	ĞÎ    ²Î£ºÎŞ
*	·µ »Ø Öµ: ÎŞ
*********************************************************************************************************
*/
/*static void FileFormat_spi(void)
{
	// ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ
	FRESULT result;
//	FATFS fs;

	printf("¿ªÊ¼½øĞĞµÍ¼¶¸ñÊ½»¯£¬Ê±¼ä´óÔ¼1·ÖÖÓ£¬ÄÍĞÄµÈ´ı\r\n");
	sf_EraseChip();
	printf("µÍ¼¶¸ñÊ½»¯Íê³É\r\n");
	// ¹ÒÔØÎÄ¼şÏµÍ³
	result = f_mount(&fs, FS_VOLUME_SPI, 0);
	if (result != FR_OK)
	{
		printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü (%s)\r\n", FR_Table[result]);
	}
	else
	{
		printf("¹ÒÔØÎÄ¼şÏµÍ³³É¹¦ (%s)\r\n", FR_Table[result]);
	}

	// µÚÒ»´ÎÊ¹ÓÃ±ØĞë½øĞĞ¸ñÊ½»¯ //
	result = f_mkfs(FS_VOLUME_SPI,0,0);
	if (result != FR_OK)
	{
		printf("¸ñÊ½»¯Ê§°Ü (%s)\r\n", FR_Table[result]);
	}
	else
	{
		printf("¸ñÊ½»¯³É¹¦ (%s)\r\n", FR_Table[result]);
	}

	//Ğ¶ÔØÎÄ¼şÏµÍ³ //
	result  = f_mount(NULL, FS_VOLUME_SPI, 0);
	if (result != FR_OK)
	{
		printf("Ğ¶ÔØÎÄ¼şÏµÍ³Ê§°Ü (%s)\r\n", FR_Table[result]);
	}
	else
	{
		printf("Ğ¶ÔØÎÄ¼şÏµÍ³³É¹¦ (%s)\r\n", FR_Table[result]);
	}
}*/
//************************************************************************************
//¶ÁÈ¡SPIÎÄ¼ş
u8 Read_Spi_File(void)
{
//char buf[128];
    FRESULT result;
    DIR DirInf;
    uint32_t bw,i;
//	char buf[128];
    char path[32];

    for(i=0; i<program_buf_len; i++) //³õÊ¼»¯
        program_buf[i]=0;
    for(i=0; i<32; i++)
        path[i]=0;
    clear_program_name();//fmc160914
    /*for(i=0;i<PROGRAM_NAME_LENGTH;i++)//fmc160914s
    {
    	if(CurrProgramName.Name[i]=='.')
    		break;
    }
    if(i==PROGRAM_NAME_LENGTH)
    {
    	sprintf(CurrProgramName.Name, "%s.txt", CurrProgramName.Name);
    }//fmc160914s
    //******************

    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, FS_VOLUME_SPI, 0);			/* Mount a logical drive */
    if (result != FR_OK)
        return 1;

    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    sprintf(path, "%s/", FS_VOLUME_SPI);
    result = f_opendir(&DirInf, path); 	/* 1: ±íÊ¾ÅÌ·û */
    if (result != FR_OK)
        return 2;
    //sprintf(path, "%s/", FS_VOLUME_SPI,name);
    //sprintf(path, "%s/%s.txt ", FS_VOLUME_SPI,name);
    sprintf(path, "%s%s%s ", FS_VOLUME_SPI,CurrProgramName.Name,".txt");
    result = f_open(&file, path, FA_OPEN_EXISTING | FA_READ);
    if (result !=  FR_OK)
        return 3;

    /* ¶ÁÈ¡ÎÄ¼ş */
    result = f_read(&file, &program_buf, file.fsize, &bw);
    if (bw > 0)
    {
        program_buf[bw] = 0;
    }// ÎÄ¼ş½áÎ²
    //****************
    f_close(&file);
    f_mount(NULL,FS_VOLUME_SPI, 0);
    if(InstrumentType==TYPE_AS154)
    {
        if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='4')
            return 6;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
    }
    else 	if(InstrumentType==TYPE_AS153)
    {
        if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='3')
            return 6;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
    }
    else
    {
        if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='5')
            return 6;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
    }
    return 0;

}






//UÅÌ³õÊ¼»¯
void Usb_Init(void)
{
    //USBH_Init(&USB_OTG_Core,USB_OTG_HS_CORE_ID,&USB_Host,&USBH_MSC_cb,&USRH_cb);

    USBH_Init(&USB_OTG_Core  ,USB_OTG_HS_CORE_ID,&USB_Host  ,&USBH_MSC_cb,&USRH_cb);
    USBH_Init(&USB_OTG_CoreWM,USB_OTG_FS_CORE_ID,&USB_HostWM,&HID_cb     ,&USRH_cbWM);

}
//****************************
void Usb_check(void)
{
    //USBH_Process(&USB_OTG_Core, &USB_Host);//

    USBH_Process(&USB_OTG_Core, &USB_Host);//WM HOST ÉÏUSB¿Ú
    USBH_ProcessWM(&USB_OTG_CoreWM, &USB_HostWM);// WM FS ÏÂUSB¿Ú

}
void check_usb_connect(void)//fmc161012
{
    if (HCD_IsDeviceConnected(&USB_OTG_Core)==0)
        flag_usb_disk_connect=0;
}
/*{#define FS_VOLUME_SD		"0:"
#define FS_VOLUME_NAND		"1:"
#define FS_VOLUME_USB		"2:"
#define FS_VOLUME_SPI		"3:"*/
//***************************
//²âÊÔÓÃ
void Usb_Copy(void)
{   uint8_t cmd;
    USBH_Process(&USB_OTG_Core, &USB_Host);

    if (comGetChar(COM7, &cmd))	/* ´Ó´®¿Ú¶ÁÈëÒ»¸ö×Ö·û(·Ç×èÈû·½Ê½) */
    {
        printf("\r\n");
        switch (cmd)
        {
        case '1':
//          Usb_Copy1();
            //printf("¡¾1 -TT ÏÔÊ¾UÅÌ¸ùÄ¿Â¼ÎÄ¼Ì¡¿\r\n");
            //ViewRootDir(FS_VOLUME_USB);		/* ÏÔÊ¾UÅÌ¸ùÄ¿Â¼ÏÂµÄÎÄ¼şÃû */
            //		printf("¡¾1 - ÏÔÊ¾SPI¸ùÄ¿Â¼ÎÄ¼ş¡¿\r\n");
            //		ViewRootDir(FS_VOLUME_SPI	);		/* ÏÔÊ¾UÅÌ¸ùÄ¿Â¼ÏÂµÄÎÄ¼şÃû */
            break;

        case '2':

            printf("¡¾2 - CreateNewFile¡¿UÅÌĞ´1K×Ö½Ú\r\n");
            CreateNewFile_1k(FS_VOLUME_USB);//Ğ´1K×Ö½Úµ½UÅÌ
            //	printf("¡¾2 - CreateNewFile¡¿SPI\r\n");
            //	  CreateNewFile(FS_VOLUME_SPI);//
            break;

        case '3':
            //printf("¡¾3 - ReadFileData¡¿\r\n");
            //ReadFileData(FS_VOLUME_SD);		/* ¶ÁÈ¡¸ùÄ¿Â¼ÏÂarmfly.txtµÄÄÚÈİ */
            //	ReadFileData(FS_VOLUME_NAND);		/* ¶ÁÈ¡¸ùÄ¿Â¼ÏÂarmfly.txtµÄÄÚÈİ */
            ReadFileData(FS_VOLUME_USB);		/* ¶ÁÈ¡¸ùÄ¿Â¼ÏÂarmfly.txtµÄÄÚÈİ */
            ReadFileData(FS_VOLUME_SPI);
            break;
        }

    }
}
//*************************
//È¡³öÒ»¸ö³ÌĞòÎÄ¼şÖĞÃû×Ö£¬²½ÖèÊı£¬ĞŞ¸ÄÊ±¼ä±£´æµ½EEP±í¸øLISTVIEWÓÃ
u8  creat_program_table(char *buf,int len)
{
    int i,nb,k;
//	     u8 tt[4];
    char a;
    //u8 tt[300];
    //	for(i=0;i<len;i++)
    //			    tt[i]=*(buf+i);
    nb=0;
    for(k=0; k<file_usb.fsize; k++)
    {
        if(*(buf++)!=0x0a)  //»»ĞĞ ÏÂÒ»×Ö½Ú¾ÍÊÇĞÂĞĞµÚÒ»×Ö½Ú
            continue;

        nb++;

        if(nb==1)//name
        {
            for(i=0; i<PROGRAM_NAME_LENGTH; i++)
            {
                a=*(buf+5+i);
                if(a==0x20||a==0x0D)
                    break;
                CurrProgramName.Name[i]=a;

            }
        }
        else if(nb==2)//²½ÖèÊı
        {

        }
        else if(nb==3)//¿ì½İºÍËø
        {
            CurrProgramName.ShortCutFlag=*(buf+7)-0x30;
            CurrProgramName.LockFlag=*(buf+8)-0x30;
        }
        else if(nb==4)//ĞŞ¸ÄÊ±¼ä
        {   CharToIntTime(6+k);

            ProgramName[ProgramMax].DateTime.Year=program_int_buf[0];
            ProgramName[ProgramMax].DateTime.Month=program_int_buf[1];
            ProgramName[ProgramMax].DateTime.Day=program_int_buf[2];
            ProgramName[ProgramMax].DateTime.Hour=program_int_buf[3];
            ProgramName[ProgramMax].DateTime.Min=program_int_buf[4];
            ProgramName[ProgramMax].DateTime.Sec=program_int_buf[5];
        }
        /*	 else if(nb==5)//¸ß¼¶²ÎÊı
        	 {
        		 	 for(i=0;i<10;i++)
        			    CurrProgramName.Name[i]=*(buf+i+7);
        	 } */
        //if(*data=='N'&&*(data+1)=='A'&&*(data+2)=='M'&&*(data+3)=='E')

    }
    //if(Write_eep_progrm())
    //	   return 1;
    return 0;

}
//*****************************************

//´ÓUÅÌÀï°Ñ³ÌĞòÎÄ¼ş¿½±´µ½SPI FLASH,²¢ÇÒ´æÎÄ¼ş±íµ½EEP
/*u8 Usb_Copy1(void)
{

    FRESULT fr;
    UINT br, bw;
	u8 falg_err;
	FRESULT result;
	//FATFS fs;
	DIR DirInf[2];
	FILINFO FileInf_Usb,FileInf_Spi;
	uint32_t cnt = 0;
	char lfname[256];
	char path_spi[32],path_usb[32];

	//char str1[]="%s/",str2[]="%s/",name[50];

	  falg_err=0;
    // **************************¹ÒÔØÎÄ¼ş
    if(f_mount(&fs_usb, FS_VOLUME_USB1, 0)!= FR_OK)
			 return 1;  //Ê§°Ü
    if(f_mount(&fs_spi, FS_VOLUME_SPI1, 0)!= FR_OK)
        return 1;  //Ê§°Ü

		// *************************´ò¿ªspi¸ùÎÄ¼ş¼Ğ
	  //sprintf(path_spi, "%s/",FS_VOLUME_SPI);
		strcpy(path_spi, FS_VOLUME_SPI1);
	  result = f_opendir(&DirInf[1], path_spi);
	  if (result != FR_OK)
		  return 2; //´ò¿ª¸ùÄ¿Â¼Ê§°Ü
	  // ´ò¿ªUSB¸ùÎÄ¼ş¼Ğ
	  //sprintf(path_usb, "%s/", FS_VOLUME_USB);
		strcpy(path_usb, FS_VOLUME_USB1);
	  if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
		   return  2;
    // ***********************¶ÁÈ¡µ±Ç°ÎÄ¼ş¼ĞÏÂµÄÎÄ¼şºÍÄ¿Â¼
	  FileInf_Usb.lfname = lfname;
	  FileInf_Usb.lfsize = 256;

	  for (cnt = 0; ;cnt++)
	  {
	  	result = f_readdir(&DirInf[0],&FileInf_Usb);
		  if (result != FR_OK || FileInf_Usb.fname[0] == 0)
		  {
				falg_err=3;
				break;//Ã»ÓĞÎÄ¼ş
			}
		  if (FileInf_Usb.fname[0] == '.')
			    continue;

		   //ÅĞ¶ÏÊÇÎÄ¼ş»¹ÊÇ×ÓÄ¿Â¼
		  if (FileInf_Usb.fattrib & AM_DIR)
		      continue;  //Ä¿Â¼

     //´ò¿ªÎÄ¼ş
			strcpy(path_usb, FS_VOLUME_USB1);
	    strcat(path_usb,FileInf_Usb.fname);

	    //sprintf(path_usb,FileInf_Usb.fname,FS_VOLUME_USB);//"%s/armfly.txt"
	    result = f_open(&file_usb,path_usb, FA_OPEN_EXISTING | FA_READ);
	    if (result !=  FR_OK)
		  {
				falg_err=4;
				break;       //Ã»ÓĞÎÄ¼ş
			}	   //ÕÒ²»µ½ÎÄ¼ş


	    result = f_read(&file_usb, &program_buf, file_usb.fsize, &bw);
	    if (bw > 0)
	    {
	    	program_buf[bw] = 0;
		  //  printf("\r\n%s ÎÄ¼şÄÚÈİ : \r\n%s\r\n", path,buf);
	    }
			f_close(&file_usb);
			//if(program_buf[0]=='A'&&program_buf[0]=='S'&&program_buf[0]=='1'&&program_buf[0]=='5'&&program_buf[0]=='4')
           continue;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
	    //sprintf(path_spi,FileInf_Usb.fname, FS_VOLUME_SPI);//"%s/aa.txt"
			strcpy(path_spi, FS_VOLUME_SPI1);
	    strcat(path_spi,FileInf_Usb.fname);
	    result = f_open(&file_spi, path_spi, FA_CREATE_ALWAYS | FA_WRITE);

	    //Ğ´USBÎÄ¼şµ½SPI
	    result = f_write(&file_spi, &program_buf, file_usb.fsize, &bw);
	    if (result != FR_OK)
		 {
				falg_err=4;
				break;//Ã»ÓĞÎÄ¼ş
			}	   //ÎÄ¼şĞ´ÈëÊ§°Ü
			f_close(&file_spi);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
			// *********************
//			creat_program_table(program_buf,file_usb.fsize); //È¡³öÒ»¸ö³ÌĞòÎÄ¼şÖĞÃû×Ö£¬²½ÖèÊı£¬ĞŞ¸ÄÊ±¼ä±£´æµ½EEP±í¸øLISTVIEWÓÃ
		}
		//read_eep_progrm();

		// ************************
      // ¹Ø±ÕÎÄ¼şÏµÍ³ FIL file_spi,file_usb;
      f_close(&file_spi);
      f_close(&file_usb);
			f_mount(NULL,FS_VOLUME_USB, 0);
      f_mount(NULL,FS_VOLUME_SPI, 0);
		  read_eep_progrm();
		  Refresh_Pragram_Row(); //Ë¢ĞÂ
      return falg_err;
}*/
//************************
//¸¡µã×ª×Ö·û
int floattochar(int j,float data,int addnull)
{   char str5[10];
    int i;
    for(i=0; i<10; i++)
        str5[i]=0;
    sprintf(str5,"%.1f",data);//Ğ¡ÊıÈ¡1Î»

    for(i=0; i<strlen(str5); i++)
        program_buf[j++]=str5[i];
    if(addnull)
        program_buf[j++]=0x20;
    // program_buf[j++]=0x20;
    return j;
}
//****************************
//INT×ª×Ö·û
int inttochar(int j,int data,int addnull)
{   char str[5];
    int i;
    for(i=0; i<5; i++)
        str[i]=0;
    sprintf(str,"%d",data);

    for(i=0; i<strlen(str); i++)
        program_buf[j++]=str[i];
    if(addnull)
        program_buf[j++]=0x20;
    return j;
}
int timetochar(int j,int data)
{   char str[5];
    int i;
    for(i=0; i<5; i++)
        str[i]=0;
    sprintf(str,"%d",data);

    for(i=0; i<strlen(str); i++)
        program_buf[j++]=str[i];

    return j;
}
//**************************
//3¸ö½á¹¹Ìå£º ÎÄ¼ş¡¢²½Öè¡¢Ñ¡ÏîÉú³ÉĞÂÎÄ¼ş
int generate_new_file(void)
{
    int i,j=0,len,back[6],k;
    int back_f[6];
    //float back_f[6];
    const char name1[]="bb.txt",start[]="AS154_S",name[]="NAME:",step[]="STEP:",time[]="TIME:",status[]="STATUS:",option[]="OPTION:",end[]="AS154_E";
//	char str[20];
    //char str1[20][2];
//	u8 *tt;
    /*for(i=0;i<6;i++)
    CurrProgramName.Name[i]=name1[i];
    //for(i=0;i<7;i++)
    //  status[i]=1;
    step_nb=10;SHORTCUT_CLOSE
    */
    //CurrProgramName.LockFlag=1;
    //CurrProgramName. ShortCutFlag=1;
//********************Í·ĞĞ
    for(i=0; i<7; i++)
        program_buf[j++]=start[i];
    if(InstrumentType==TYPE_AS154)//fmc161025"AS1253"
        program_buf[4]='4';
    else if(InstrumentType==TYPE_AS153)
        program_buf[4]='3';
    else
        program_buf[4]='5';

    program_buf[j++]=0x0d;
    program_buf[j++]=0x0a;
    //********************NAMEĞĞ
    for(i=0; i<5; i++)
        program_buf[j++]=name[i];
    //*****************
    for(i=0; i<PROGRAM_NAME_LENGTH; i++)
    {
        if(CurrProgramName.Name[i]=='.')
        {
            for(k=i; k<PROGRAM_NAME_LENGTH; k++)
                CurrProgramName.Name[k]=0;
            break; //fmc160913 Ğ´ÎÄ¼şÈ¥µô.txt
        }
    }
    //*********************
    len=strlen(CurrProgramName.Name);
    for(i=0; i<len; i++)
        program_buf[j++]=CurrProgramName.Name[i];
    program_buf[j++]=0x0d;
    program_buf[j++]=0x0a;
    //*********************STEPĞĞ
    for(i=0; i<5; i++)
        program_buf[j++]=step[i];
    //step_nb=12;
    j=inttochar(j,Step_nb,0);
    program_buf[j++]=0x0d;
    program_buf[j++]=0x0a;
    //********************STATUS:
    for(i=0; i<7; i++)
        program_buf[j++]=status[i];

    program_buf[j++]= CurrProgramName. ShortCutFlag+0x30;//SHORTCUT_OPEN+0x30;  //   0x30;//RUN_TABLE+0x30//FMC160827
    program_buf[j++]=LOCK_OPEN+0x30;//0x31;//LOCK+0x30 //FMC160827

    program_buf[j++]=0x0d;
    program_buf[j++]=0x0a;
    //********************TIME:
    for(i=0; i<5; i++)
        program_buf[j++]=time[i];

    j=timetochar(j,SystemTimePra.Year);
    program_buf[j++]='-';
    j=timetochar(j,SystemTimePra.Month);
    program_buf[j++]='-';
    j=timetochar(j,SystemTimePra.Day);
    program_buf[j++]=0x20;
    j=timetochar(j,SystemTimePra.Hour);
    program_buf[j++]=':';
    j=timetochar(j,SystemTimePra.Min);
    program_buf[j++]=':';
    j=timetochar(j,SystemTimePra.Sec);

    program_buf[j++]=0x0d;
    program_buf[j++]=0x0a;
//********************OPTION:
    for(i=0; i<7; i++)
        program_buf[j++]=option[i];
    for(i=0; i<TEMP_CHANNEL_NUM ; i++) //FMC160826
    {
        j=inttochar(j,ProgramOption.HeatEnable[i],1);
        //sprintf(str,"%02d",ProgramOption.HeatEnable[i]);

    }
    j=inttochar(j,ProgramOption.HeatPra.Type,1);
//	sprintf(str,"%02d",ProgramOption.HeatPra.Type);
//	program_buf[j++]=str[0];
//	program_buf[j++]=str[1];
    //j=inttochar(j,ProgramOption.HeatPra.DestnationTemper,1);
    //sprintf(str,"%04d",ProgramOption.HeatPra.DestnationTemper);
    //program_buf[j++]=str[0];
    //program_buf[j++]=str[1];
//	program_buf[j++]=str[2];
//	program_buf[j++]=str[3];

    j=inttochar(j,ProgramOption.HeatPra.LowerTemper,1);
//		sprintf(str,"%04d",ProgramOption.HeatPra.LowerTemper);
//	program_buf[j++]=str[0];
//	program_buf[j++]=str[1];
//	program_buf[j++]=str[2];
//	program_buf[j++]=str[3];
    j=inttochar(j,ProgramOption.HeatPra.HeatingPreviousStepEn,1);//fmc161027

    j=inttochar(j,ProgramOption.HeatPra.HeatingPreviousStep,1);
//	sprintf(str,"%02d",ProgramOption.HeatPra.HeatingPreviousStep);
//	program_buf[j++]=str[0];
//	program_buf[j++]=str[1];
    j=inttochar(j,ProgramOption.CoolingPra.FanEnable,1);
    //sprintf(str,"%02d",ProgramOption.CoolingPra.FanEnable);
//	program_buf[j++]=str[0];
    //program_buf[j++]=str[1];
    j=inttochar(j,ProgramOption.CoolingPra.Type,1);

    j=inttochar(j,ProgramOption.CoolingPra.DestnationTemper,1);
    //	sprintf(str,"%02d",ProgramOption.CoolingPra.Type);
    //program_buf[j++]=str[0];
    //program_buf[j++]=str[1];
    j=inttochar(j,ProgramOption.CoolingPra.HighTemper,1);//fmc161008

    j=inttochar(j,ProgramOption.MagnaticPra.Type,1);
    //program_buf[j++]=str[0];
    //program_buf[j++]=str[1];
    j=inttochar(j,ProgramOption.MagnaticPra.SegNum,0);
    //program_buf[j++]=str[0];
    //program_buf[j++]=str[1];

    program_buf[j++]=0x0d;
    program_buf[j++]=0x0a;
    //***************************stepÃ÷Ï¸ĞĞ
    for(k=0; k<Step_nb; k++)
    {
        for(i=0; i<STEP_NAME_LENGTH; i++ )
        {
            if(ProgramStep[k].Name[i]==' ')
                ProgramStep[k].Name[i]=0;//fmc160909 È¥µô¿Õ¸ñ
        }
        len=strlen(ProgramStep[k].Name);
        for(i=0; i<len; i++)
            program_buf[j++]=ProgramStep[k].Name[i];
        program_buf[j++]=0x20;
        j=inttochar(j,ProgramStep[k].Holes,1);
        //program_buf[j++]=str[0];
        //program_buf[j++]=0x20;


        back[0]=ProgramStep[k].MixingTime;
        back[1]=ProgramStep[k].MagneticTime;
        back[2]=ProgramStep[k].WaitTime;
        back[3]=ProgramStep[k].Volume;
        back[4]=ProgramStep[k].MixingSpeed;
        back[5]=ProgramStep[k].Temperature;
        for(i=0; i<6; i++)
        {
            j=inttochar(j,back[i],1);
        }


        back_f[0]=ProgramStep[k].MixingPosition;//fmc160907s
        back_f[1]=ProgramStep[k].MixingAmplitude;
        back_f[2]=ProgramStep[k].MagneticPosition;
        back_f[3]=ProgramStep[k].MagneticSpeedUpDown;

        back_f[4]=ProgramStep[k].MagneticFludeTime;//fmc160907e
        // back_f[2]=0;
        for(i=0; i<5; i++)
        {
            if(i!=4)
                // j=floattochar(j,back_f[i],1);
                j=inttochar(j,back_f[i],1);
            else
                //j=floattochar(j,back_f[i],0);
                j=inttochar(j,back_f[i],0);

        }
        program_buf[j++]=0x0d;
        program_buf[j++]=0x0a;
    }
    //********************Î²ĞĞ
    for(i=0; i<7; i++)
    {
        if(i==4)
        {
            if(InstrumentType==TYPE_AS154)//fmc161025"AS1253"
                program_buf[j++]='4';
            else if(InstrumentType==TYPE_AS153)
                program_buf[j++]='3';
            else
                program_buf[j++]='5';
            continue;
        }
        program_buf[j++]=end[i];
    }



    program_buf[j++]=0x0d;
    program_buf[j++]=0x0a;

    return j;

}
//***********************
//È¥µôÃû×ÖÀï¿Õ¸ñºÍµã£¬·ÀÖ¹³ö´í  fmc160914s
void clear_program_name(void)
{   u8 k,i;
    for(i=0; i<PROGRAM_NAME_LENGTH; i++)
    {
        if(CurrProgramName.Name[i]==' '||CurrProgramName.Name[i]=='.')
        {
            for(k=i; k<PROGRAM_NAME_LENGTH; k++)
                CurrProgramName.Name[k]=0;
            break; //fmc160913 Ğ´ÎÄ¼şÈ¥µô.txt
        }
    }
}
//*******************************fmc160914e
//Áí´æ
u8 Program_SaveAs(void) //fmc160831
{

//    FRESULT fr;          /* FatFs function common result code */
    UINT  bw;         /* File read/write count */
    u8 falg_err,i;
    FRESULT result;
    int fsize;
    //FATFS fs;
    DIR DirInf[2];
//	FILINFO FileInf_Usb,FileInf_Spi;
//	uint32_t cnt = 0;
//	char lfname[256];
    char path_spi[32];//¢,path_usb[32];

    clear_program_name();//fmc160914s
    /*for(i=0;i<PROGRAM_NAME_LENGTH;i++)
    {
    	if(CurrProgramName.Name[i]==' ')
    		CurrProgramName.Name[i]=0;
    }
    /*if(i==PROGRAM_NAME_LENGTH)
    {
    	sprintf(CurrProgramName.Name, "%s.txt", CurrProgramName.Name);
    }//fmc160914s*/

    CurrProgramName.DateTime.Year= SystemTimePra.Year;
    CurrProgramName.DateTime.Month= SystemTimePra.Month;
    CurrProgramName.DateTime.Day= SystemTimePra.Day;
    CurrProgramName.DateTime.Hour= SystemTimePra.Hour;
    CurrProgramName.DateTime.Min= SystemTimePra.Min;
    CurrProgramName.DateTime.Sec= SystemTimePra.Sec;
//	CurrProgramName.LockFlag=LOCK_DISABLE;;
//	CurrProgramName. ShortCutFlag=RUN_TABLE;
    CurrProgramName.ShortCutFlag= SHORTCUT_OPEN;  //FMC160827
    CurrProgramName.LockFlag= LOCK_OPEN;//FMC160827


    read_one_ProgramStep(CurrProgramName.Name);//¶Á³öÎÄ¼şÄÚÈİ·Åµ½3¸ö½á¹¹Ìå£º ÎÄ¼ş¡¢²½Öè¡¢Ñ¡Ïî

    //sprintf(New_File_Name, "%s.txt", New_File_Name);
    strcpy(CurrProgramName.Name,New_File_Name);//fmc160914
    strcpy(ProgramName[ProgramMax].Name,New_File_Name);
    /*	for(i=0;i<PROGRAM_NAME_LENGTH ;i++)
    	{
    		CurrProgramName.Name[i]= New_File_Name[i];
    		ProgramName[ProgramMax].Name[i]=CurrProgramName.Name[i];
    	}	*/

    ProgramName[ProgramMax].DateTime.Year=CurrProgramName.DateTime.Year;
    ProgramName[ProgramMax].DateTime.Month=CurrProgramName.DateTime.Month;
    ProgramName[ProgramMax].DateTime.Day=CurrProgramName.DateTime.Day;
    ProgramName[ProgramMax].DateTime.Hour=CurrProgramName.DateTime.Hour;
    ProgramName[ProgramMax].DateTime.Min=CurrProgramName.DateTime.Min;
    ProgramName[ProgramMax].DateTime.Sec=CurrProgramName.DateTime.Sec;
    ProgramName[ProgramMax].LockFlag=CurrProgramName.LockFlag;
    ProgramName[ProgramMax].ShortCutFlag=CurrProgramName. ShortCutFlag;


    //************************************½«3¸ö½á¹¹ÌåÉú³ÉĞÂÎÄ¼ş CurrProgramName.Name
    //sprintf(New_File_Name, "%s/%s.txt ", New_File_Name,name);
    //sprintf(New_File_Name, "%s.txt ", New_File_Name);
    strcpy(CurrProgramName.Name,New_File_Name);
    fsize=generate_new_file();
    falg_err=0;
    //************************************
    if(f_mount(&fs_spi, FS_VOLUME_SPI1, 0)!= FR_OK)
    {
        falg_err=4;
        goto err;
    }

    //*************************´ò¿ªspi¸ùÎÄ¼ş¼Ğ
    //sprintf(path_spi, "%s/",FS_VOLUME_SPI);
    strcpy(path_spi, FS_VOLUME_SPI1);
    result = f_opendir(&DirInf[1], path_spi);
    if (result != FR_OK)
    {
        falg_err=4;
        goto err;
    }
    strcpy(path_spi, FS_VOLUME_SPI1);
    strcat(path_spi,CurrProgramName.Name);
    strcat(path_spi,".txt");
    result = f_open(&file_spi, path_spi, FA_CREATE_ALWAYS | FA_WRITE);
    if (result != FR_OK)
    {
        falg_err=4;
        goto err;
    }
    //Ğ´USBÎÄ¼şµ½SPI
    result = f_write(&file_spi, &program_buf, fsize, &bw);
    if (result != FR_OK)
    {
        falg_err=4;
        goto err;
    }	   //ÎÄ¼şĞ´ÈëÊ§°Ü
    f_close(&file_spi);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
    f_mount(NULL,FS_VOLUME_SPI, 0);
    return 0;
    //	if(Write_eep_progrm())
    //		   return 1;
err:
    f_close(&file_spi);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
    f_mount(NULL,FS_VOLUME_SPI, 0);
    return falg_err;
}
//¢******************************
//±£´æ³ÌĞòÎÄ¼ş Ğ´3¸ö½á¹¹Ìå±í£¬²¢ÇÒ¸üĞÂEEP ³ÌĞòÎÄ¼ş±í
u8 Save_Program(void)
{

//    FRESULT fr;          /* FatFs function common result code */
    UINT bw;         /* File read/write count */
    u8 falg_err,i;
    FRESULT result;
    int fsize;
    //FATFS fs;
    DIR DirInf[2];
//	FILINFO FileInf_Usb,FileInf_Spi;
//	uint32_t cnt = 0;
//	char lfname[256];
    char path_spi[32];//¢,path_usb[32];

    clear_program_name();//fmc160914s
    /*	for(i=0;i<PROGRAM_NAME_LENGTH;i++)
    	{
    		if(CurrProgramName.Name[i]=='.')
    			break;
    	}
    	if(i==PROGRAM_NAME_LENGTH)
    	{
    		sprintf(CurrProgramName.Name, "%s.txt", CurrProgramName.Name);
    	}//fmc160914e*/
    CurrProgramName.DateTime.Year= SystemTimePra.Year;
    CurrProgramName.DateTime.Month= SystemTimePra.Month;
    CurrProgramName.DateTime.Day= SystemTimePra.Day;
    CurrProgramName.DateTime.Hour= SystemTimePra.Hour;
    CurrProgramName.DateTime.Min= SystemTimePra.Min;
    CurrProgramName.DateTime.Sec= SystemTimePra.Sec;
    if(flag_new_file)                                   //FMC160922 ÀÏÎÄ¼ş²»¸Ä
        CurrProgramName.ShortCutFlag= SHORTCUT_OPEN;  //FMC160922
    CurrProgramName.LockFlag= LOCK_OPEN;//FMC160827
    //************************************½«3¸ö½á¹¹ÌåÉú³ÉĞÂÎÄ¼ş CurrProgramName.Name
    fsize=generate_new_file();

    //************************************
    if(f_mount(&fs_spi, FS_VOLUME_SPI1, 0)!= FR_OK)
    {
        falg_err=4;
        goto err;
    }
    //*************************´ò¿ªspi¸ùÎÄ¼ş¼Ğ
    strcpy(path_spi, FS_VOLUME_SPI1);
    result = f_opendir(&DirInf[1], path_spi);
    if (result != FR_OK)
    {
        falg_err=4;
        goto err;
    }
    strcpy(path_spi, FS_VOLUME_SPI1);
    strcat(path_spi,CurrProgramName.Name);
    strcat(path_spi,".txt");//fmc160914
    result = f_open(&file_spi, path_spi, FA_CREATE_ALWAYS | FA_WRITE);
    if (result != FR_OK)
    {
        falg_err=4;
        goto err;
    }
    //ÎÄ¼şµ½SPI
    result = f_write(&file_spi, &program_buf, fsize, &bw);
    if (result != FR_OK)
    {
        falg_err=4;
        goto err;
    }	   //ÎÄ¼şĞ´ÈëÊ§°Ü
    f_close(&file_spi);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
    f_mount(NULL,FS_VOLUME_SPI, 0);

    //if(Write_eep_progrm())
    //	   return 1;
    return 0;
err:
    f_close(&file_spi);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
    f_mount(NULL,FS_VOLUME_SPI, 0);
    return falg_err;
}
//****************************
//É¾³ı,CurrProgramName.NameÎÄ¼ş  Êä³ö0³É¹¦
u8 delete_one_file(void)
{
    /* ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ */
    FRESULT result;
//	FATFS fs;
//	char FileName[13];
//	uint8_t i;
    char path[32];

    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, FS_VOLUME_SPI, 0);			/* Mount a logical drive */
    if (result != FR_OK)
        return 1;

    //É¾³ıÎÄ¼ş

    //sprintf(path, "%s/%s ", FS_VOLUME_SPI1,name);
    sprintf(path, "%s/%s%s ", FS_VOLUME_SPI,CurrProgramName.Name,".txt");
    result = f_unlink(path);
    f_mount(NULL,FS_VOLUME_SPI, 0);	/* Ğ¶ÔØÎÄ¼şÏµÍ³ */
    if (result != FR_OK&&result != FR_NO_FILE)
        return 5;
//	if(del_eep_progrm())//É¾³ıEEP±í
//	   return 6;
    return 0;
}

//*****************************

//*************************************************************
//È¡Ò»ĞĞ²½ÖèÊı¾İ
void get_data(int nb,int cent)
{
    int i,k;
    char str[16][12];
    char a;
    //data=&program_buf[cent];

    for(k=0; k<15; k++) //15¸öÊı¾İ
    {
        for(i=0; i<10; i++)
            str[k][i]=0;
    }
    //************
    cent++;
    for(i=0; i<STEP_NAME_LENGTH; i++)
    {   //cent++;
        //a=*(data++);
        if(program_buf[cent]==0x20)
            break;
        ProgramStep[nb].Name[i]=program_buf[ cent];
        cent++;
    }
    if(program_buf[cent]==0x20)
        cent++;
    for(k=0; k<12; k++) //12¸öÊı¾İ
    {
        for(i=0; i<10; i++)
        {
            // a=*(data++);
            a=program_buf[ cent++];
            if(a==0x20||a==0x0d)
                break;
            str[k][i]=a;
        }
        str[k][i]=0;
        //data++;
    }
    for(i=0; i<11; i++) ////fmc160907s
    {
        sscanf(str[i], "%d", &program_int_buf[i]);
    }
    ProgramStep[nb].Holes=program_int_buf[0];
    ProgramStep[nb].MixingTime=program_int_buf[1];
    ProgramStep[nb].MagneticTime=program_int_buf[2];
    ProgramStep[nb].WaitTime=program_int_buf[3];
    ProgramStep[nb].Volume=program_int_buf[4];
    ProgramStep[nb].MixingSpeed=program_int_buf[5];
    ProgramStep[nb].Temperature=program_int_buf[6];

    ProgramStep[nb].MixingPosition=program_int_buf[7];
    ProgramStep[nb].MixingAmplitude=program_int_buf[8];
    ProgramStep[nb].MagneticPosition=program_int_buf[9];
    ProgramStep[nb].MagneticSpeedUpDown=program_int_buf[10];
    /*ProgramStep[nb].MixingPosition=atof(str[7]);
    ProgramStep[nb].MixingAmplitude=atof(str[8]);
    ProgramStep[nb].MagneticPosition=atof(str[9]);
    ProgramStep[nb].MagneticSpeedUpDown=atof(str[10]);
    ProgramStep[nb].MagneticFludeTime=atof(str[11]);*/ // fmc160907e


}
//*******************************
//½«³ÌĞòÎÄ¼şĞ¡ÓÚÒ»ĞĞÊı¾İ×ª»»ÎªcentINT´æµ½program_int_buf
//ÊäÈë³ÌĞòÎÄ¼şµÚ¼¸¸öÊı¾İÎ»ÖÃnb¿ªÊ¼×ª£¬ĞèÒª×ªcent¸öINTÊı¾İ
//·µ»Ø 0£¬Ê§°Ü£¬ÆäËû±íÊ¾×ª»»ÍêºóÊı¾İÎ»ÖÃ

int CharToInt(int nb,int cent)
{

    char str4[10],a;
    int i,k,n;

    for(k=0; k<cent; k++)
    {
        for(n=0; n<10; n++)
            str4[n]=0x35;
        for(i=0; i<10; i++)
        {
            a=program_buf[nb++];
            if(a==0x20)
                break;

            if(a==0x0d)
            {   nb++;
                break;
            }
            str4[i]=a;
        }
        str4[i]='\0';
        //program_int_buf[k]=atoi(str4);        //==>0XF
        sscanf(str4, "%d", &program_int_buf[k]);//==>0X15
        if(a==0x0d)
            break;
    }
    return nb;
}
//**********************
//¶ÁÈ¡Ñ¡¶¨³ÌĞòÎÄ¼şµÄ²½Öè²ÎÊı
u8 read_one_ProgramStep(char *name)
{
    u16 i,j,k,nb;
    unsigned char *addr;
//	char str[10],str1[4];
    u16 cent=0,tt[4];//,back;
    //int tt[20];
    for(i=0; i<STEPNODE_MAX; i++) //³õÊ¼»¯
    {
        addr=(unsigned char *)&ProgramStep[i];
        for(k=0; k<sizeof(PROGRAMSTEP); k++)
            *(addr++)=0;
    }
    if(Read_Spi_File())
    {   beep();
        return 1;//program_buf
    }
    nb=0;
    for(k=0; k<file.fsize; k++)
    {
        if(program_buf[k]!=0x0a)  //»»ĞĞ ÏÂÒ»×Ö½Ú¾ÍÊÇĞÂĞĞµÚÒ»×Ö½Ú
            continue;
        nb++;
        if(nb==2)//²½ÖèÊı
        {
            tt[0]=program_buf[k+6];
            tt[1]= program_buf[k+7];
            tt[2]= program_buf[k+8];
            tt[3]= program_buf[k+9];

            if(tt[1]==0x0d)
                Step_nb=tt[0]-0x30;
            else if(tt[2]==0x0d)
            {   tt[0]=tt[0]-0x30;
                tt[1]=tt[1]-0x30;
                Step_nb=(tt[0])*10+tt[1];
            }
            else if(tt[3]==0x0d)
            {
                tt[0]=tt[0]-0x30;
                tt[1]=tt[1]-0x30;
                tt[2]=tt[2]-0x30;
                Step_nb=tt[0]*100+tt[1]*10+tt[2];

            }

        }
        else if(nb>=6&&nb<(Step_nb+6))//È¡²½ÖèÊı¾İ
        {
            get_data(cent,k);
            cent++;

        }
        else if(nb==5)//¸ß¼¶²ÎÊı	 20×Ö½Ú   //fmc161008s
        {   j=k+8;
            CharToInt(j,18);

            for(i=0; i<TEMP_CHANNEL_NUM; i++)
            {
                ProgramOption.HeatEnable[i]=program_int_buf[i];  //8
            }
            ProgramOption.HeatPra.Type=program_int_buf[8];//fmc161027s
            //ProgramOption.HeatPra.DestnationTemper=program_int_buf[9];
            ProgramOption.HeatPra.LowerTemper=program_int_buf[9];
            ProgramOption.HeatPra.HeatingPreviousStepEn=program_int_buf[10];
            ProgramOption.HeatPra.HeatingPreviousStep=program_int_buf[11];

            ProgramOption.CoolingPra.FanEnable=program_int_buf[12];        //1
            ProgramOption.CoolingPra.Type  =program_int_buf[13];               //1
            ProgramOption.CoolingPra.DestnationTemper  =program_int_buf[14];

            ProgramOption.CoolingPra.HighTemper  =program_int_buf[15]; 	//

            ProgramOption.MagnaticPra.Type =program_int_buf[16];           //  1
            ProgramOption.MagnaticPra.SegNum=program_int_buf[17];         //fmc161008e

            //**************fmc161013s
            /*if(ProgramOption.HeatPra.DestnationTemper>HEATPRA_DEST_TEMPER_MAX)
             ProgramOption.HeatPra.DestnationTemper=HEATPRA_DEST_TEMPER_MAX;
            if(ProgramOption.HeatPra.DestnationTemper<HEATPRA_DEST_TEMPER_MIN)
             ProgramOption.HeatPra.DestnationTemper=HEATPRA_DEST_TEMPER_MIN;

            if(ProgramOption.CoolingPra.DestnationTemper>COOLINGTPRA_DEST_TEMPER_MAX)
             ProgramOption.CoolingPra.DestnationTemper=COOLINGTPRA_DEST_TEMPER_MAX;
            if(ProgramOption.CoolingPra.DestnationTemper<COOLINGTPRA_DEST_TEMPER_MIN)
             ProgramOption.CoolingPra.DestnationTemper=COOLINGTPRA_DEST_TEMPER_MIN;	*/
            if(ProgramOption.HeatPra.LowerTemper>50)
                ProgramOption.HeatPra.LowerTemper=50;
            if(ProgramOption.HeatPra.LowerTemper<1)
                ProgramOption.HeatPra.LowerTemper=1;
            if(ProgramOption.CoolingPra.HighTemper>50)
                ProgramOption.CoolingPra.HighTemper=50;
            if(ProgramOption.CoolingPra.HighTemper<1)
                ProgramOption.CoolingPra.HighTemper=1;
            if(ProgramOption.HeatPra.HeatingPreviousStepEn!=0&&ProgramOption.HeatPra.HeatingPreviousStepEn!=1)
                ProgramOption.HeatPra.HeatingPreviousStepEn=0;
            if(ProgramOption.HeatPra.HeatingPreviousStep>3)
                ProgramOption.HeatPra.HeatingPreviousStep=3;
            if(ProgramOption.HeatPra.HeatingPreviousStep<1)
                ProgramOption.HeatPra.HeatingPreviousStep=1;

            if(ProgramOption.MagnaticPra.SegNum>MAGNATIONPRA_SENNUM_MAX)
                ProgramOption.MagnaticPra.SegNum=MAGNATIONPRA_SENNUM_MAX;
            if(ProgramOption.MagnaticPra.SegNum<MAGNATIONPRA_SENNUM_MIN)
                ProgramOption.MagnaticPra.SegNum=MAGNATIONPRA_SENNUM_MIN;

            //**************fmc161013e
        }

    }
    return 0;
}
//*********************
u8 check_Program_step(void)
{   int i,k,nb;
    for(nb=0; nb<Step_nb; nb++)
    {
        if( ProgramStep[nb].Name[0]==0||ProgramStep[nb].Name[0]==' ')
            return 1;
        for(i=0; i< PROGRAM_NAME_LENGTH; i++)
        {
            if( ProgramStep[nb].Name[i]==' ')
                ProgramStep[nb].Name[i]=0;
        }
        //*************
        if( ProgramStep[nb].Holes>HOLES_MAX||ProgramStep[nb].Holes<HOLES_MIN)
            return 1;
        if( ProgramStep[nb].MixingTime>MIXING_TIME_MAX||ProgramStep[nb].MixingTime<MIXING_TIME_MIN)
            return 1;
        if( ProgramStep[nb].MagneticTime>MAGNETICTIME_MAX||ProgramStep[nb].MagneticTime<MAGNETICTIME_MIN)
            return 1;
        if( ProgramStep[nb].WaitTime>WAITTIME_MAX||ProgramStep[nb].WaitTime<WAITTIME_MIN)
            return 1;
        if(ProgramStep[nb].Holes==1)
        {
            if(InstrumentType==TYPE_AS154)//fmc161025"AS1253"
            {
                if( ProgramStep[nb].Volume>VOLUME_MAX||ProgramStep[nb].Volume<VOLUME_MIN)
                    return 1;
            }
            else if(InstrumentType==TYPE_AS153)//fmc161025"AS1253"
            {
                if( ProgramStep[nb].Volume>VOLUME_MAX_153||ProgramStep[nb].Volume<VOLUME_MIN)
                    return 1;
            }
            else
            {
                if( ProgramStep[nb].Volume>VOLUME_MAX_155||ProgramStep[nb].Volume<VOLUME_MIN)
                    return 1;
            }

        }
        else
        {
            if( ProgramStep[nb].Volume>VOLUME_MAX||ProgramStep[nb].Volume<VOLUME_MIN)
                return 1;
        }

        if( ProgramStep[nb].MixingSpeed>MIXINGSPEED_MAX||ProgramStep[nb].MixingSpeed<MIXINGSPEED_MIN)
            return 1;
        if( ProgramStep[nb].Temperature>TEMPERATURE_MAX||ProgramStep[nb].Temperature<TEMPERATURE_MIN)
            return 1;

        if( ProgramStep[nb].MixingPosition>MIXINGPOSITION_MAX||ProgramStep[nb].MixingPosition<MIXINGPOSITION_MIN)
            return 1;
        if( ProgramStep[nb].MixingAmplitude>MIXINGAMPLITUDE_MAX||ProgramStep[nb].MixingAmplitude<MIXINGAMPLITUDE_MIN)
            return 1;
        if( ProgramStep[nb].MagneticPosition>MagneticPosition_MAX||ProgramStep[nb].MagneticPosition<MagneticPosition_MIN)
            return 1;
        if( ProgramStep[nb].MagneticSpeedUpDown>MAGNETICSPEEDUPDOWN_MAX||ProgramStep[nb].MagneticSpeedUpDown<MAGNETICSPEEDUPDOWN_MIN)
            return 1;
    }
    return 0;
}
//*********************
//u8 read_one_ProgramStep1(int flag)
u8 read_and_check_ProgramStep(int flag)
{
    u16 i,j,k,nb;
    unsigned char *addr;
    //char str[10],str1[4];
    u16 cent=0,tt[4];
    //int tt[20];
    for(i=0; i<STEPNODE_MAX; i++) //³õÊ¼»¯
    {
        addr=(unsigned char *)&ProgramStep[i];
        for(k=0; k<sizeof(PROGRAMSTEP); k++)
            *(addr++)=0;
    }
    if(flag==READ_FILE)
    {
        if(Read_Spi_File())
        {
            beep();
            return 1;//program_buf
        }
    }
    nb=0;
    for(k=0; k<file.fsize; k++)
    {
        if(program_buf[k]!=0x0a)  //»»ĞĞ ÏÂÒ»×Ö½Ú¾ÍÊÇĞÂĞĞµÚÒ»×Ö½Ú
            continue;
        nb++;
        if(nb==2)//²½ÖèÊı
        {
            tt[0]=program_buf[k+6];
            tt[1]= program_buf[k+7];
            tt[2]= program_buf[k+8];
            tt[3]= program_buf[k+9];

            if(tt[1]==0x0d)
                Step_nb=tt[0]-0x30;
            else if(tt[2]==0x0d)
            {   tt[0]=tt[0]-0x30;
                tt[1]=tt[1]-0x30;
                Step_nb=(tt[0])*10+tt[1];
            }
            else if(tt[3]==0x0d)
            {
                tt[0]=tt[0]-0x30;
                tt[1]=tt[1]-0x30;
                tt[2]=tt[2]-0x30;
                Step_nb=tt[0]*100+tt[1]*10+tt[2];

            }

        }
        else if(nb>=6&&nb<(Step_nb+6))//È¡²½ÖèÊı¾İ
        {
            get_data(cent,k);
            cent++;

        }
        else if(nb==5)//¸ß¼¶²ÎÊı	 20×Ö½Ú
        {   j=k+8;
            CharToInt(j,18);

            for(i=0; i<TEMP_CHANNEL_NUM; i++)
            {
                ProgramOption.HeatEnable[i]=program_int_buf[i];  //8
            }
            ProgramOption.HeatPra.Type=program_int_buf[8];
            //ProgramOption.HeatPra.DestnationTemper=program_int_buf[9];
            ProgramOption.HeatPra.LowerTemper=program_int_buf[9];
            ProgramOption.HeatPra.HeatingPreviousStepEn=program_int_buf[10];
            ProgramOption.HeatPra.HeatingPreviousStep=program_int_buf[11];
            ProgramOption.CoolingPra.FanEnable=program_int_buf[12];        //1
            ProgramOption.CoolingPra.Type  =program_int_buf[13];               //1
            ProgramOption.CoolingPra.DestnationTemper  =program_int_buf[14];

            ProgramOption.CoolingPra.HighTemper  =program_int_buf[15]; 	//

            ProgramOption.MagnaticPra.Type =program_int_buf[16];           //  1
            ProgramOption.MagnaticPra.SegNum=program_int_buf[17];         //fmc161008e
            //**************fmc161013s

            if(ProgramOption.HeatPra.LowerTemper>50)
                ProgramOption.HeatPra.LowerTemper=50;
            if(ProgramOption.HeatPra.LowerTemper<1)
                ProgramOption.HeatPra.LowerTemper=1;
            if(ProgramOption.CoolingPra.HighTemper>50)
                ProgramOption.CoolingPra.HighTemper=50;
            if(ProgramOption.CoolingPra.HighTemper<1)
                ProgramOption.CoolingPra.HighTemper=1;
            if(ProgramOption.HeatPra.HeatingPreviousStepEn!=0&&ProgramOption.HeatPra.HeatingPreviousStepEn!=1)
                ProgramOption.HeatPra.HeatingPreviousStepEn=0;
            if(ProgramOption.HeatPra.HeatingPreviousStep>3)
                ProgramOption.HeatPra.HeatingPreviousStep=3;
            if(ProgramOption.HeatPra.HeatingPreviousStep<1)
                ProgramOption.HeatPra.HeatingPreviousStep=1;
            /* if(ProgramOption.HeatPra.DestnationTemper>HEATPRA_DEST_TEMPER_MAX)
            	 ProgramOption.HeatPra.DestnationTemper=HEATPRA_DEST_TEMPER_MAX;
             if(ProgramOption.HeatPra.DestnationTemper<HEATPRA_DEST_TEMPER_MIN)
            	 ProgramOption.HeatPra.DestnationTemper=HEATPRA_DEST_TEMPER_MIN;

             if(ProgramOption.CoolingPra.DestnationTemper>COOLINGTPRA_DEST_TEMPER_MAX)
            	 ProgramOption.CoolingPra.DestnationTemper=COOLINGTPRA_DEST_TEMPER_MAX;
             if(ProgramOption.CoolingPra.DestnationTemper<COOLINGTPRA_DEST_TEMPER_MIN)
            	 ProgramOption.CoolingPra.DestnationTemper=COOLINGTPRA_DEST_TEMPER_MIN;	*/

            if(ProgramOption.MagnaticPra.SegNum>MAGNATIONPRA_SENNUM_MAX)
                ProgramOption.MagnaticPra.SegNum=MAGNATIONPRA_SENNUM_MAX;
            if(ProgramOption.MagnaticPra.SegNum<MAGNATIONPRA_SENNUM_MIN)
                ProgramOption.MagnaticPra.SegNum=MAGNATIONPRA_SENNUM_MIN;

            //**************fmc161013e
        }

    }
    if(check_Program_step())//¼ì²éÊı¾İºÏ·¨
        return 1;
    return 0;
}
//*********************************************************
//**********************************************************
char read_all_usb_file(void)
{

//    FRESULT fr;          /* FatFs function common result code */
    UINT bw;         /* File read/write count */
    u8 falg_err,nb;
    FRESULT result;
    //FATFS fs;
    DIR DirInf[2];
    FILINFO FileInf_Usb;
    uint32_t cnt = 0;
    char lfname[256];
    char path_usb[32];



    falg_err=0;
    //**************************¹ÒÔØÎÄ¼ş
    if(f_mount(&fs_usb, FS_VOLUME_USB, 0)!= FR_OK)
        return 1;  //Ê§°Ü

    //*************************´ò¿ªÖ÷Ä¿Â¼
    sprintf(path_usb, "%s/", FS_VOLUME_USB);
    //strcpy(path_usb, FS_VOLUME_USB1);
    if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
        return  2;
    //*************************´ò¿ª×ÓÄ¿Â¼
    strcat(path_usb,DIR_USB_PROGRAM_INPUT);

    if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
        return  2;
    //***********************¶ÁÈ¡µ±Ç°ÎÄ¼ş¼ĞÏÂµÄÎÄ¼şºÍÄ¿Â¼
    FileInf_Usb.lfname = lfname;
    FileInf_Usb.lfsize = 256;
    nb=0;
    for (cnt = 0; ; cnt++)
    {
        result = f_readdir(&DirInf[0],&FileInf_Usb); 		/* ¶ÁÈ¡Ä¿Â¼Ïî£¬Ë÷Òı»á×Ô¶¯ÏÂÒÆ */
        if (result != FR_OK || FileInf_Usb.fname[0] == 0)
        {
            falg_err=0;
            break;//Ã»ÓĞÎÄ¼ş ¶ÁÍê
        }
        if (FileInf_Usb.fname[0] == '.')
            continue;

        //ÅĞ¶ÏÊÇÎÄ¼ş»¹ÊÇ×ÓÄ¿Â¼
        if (FileInf_Usb.fattrib & AM_DIR)
            continue;  //Ä¿Â¼

        //´ò¿ªÎÄ¼ş
        strcpy(path_usb, FS_VOLUME_USB);
        //sprintf(path_usb, "%s/", DIR_USB_PROGRAM_INPUT);
        strcat(path_usb,DIR_USB_PROGRAM_INPUT);
        strcat(path_usb,"/");
        strcat(path_usb,FileInf_Usb.fname);//*/
        result = f_open(&file_usb,path_usb, FA_OPEN_EXISTING | FA_READ);
        if (result !=  FR_OK)
        {
            falg_err=4;
            break;       //Ã»ÓĞÎÄ¼ş
        }

        //¶ÁÈ¡UÅÌÎÄ¼ş */
        result = f_read(&file_usb, &program_buf, file_usb.fsize, &bw);
        if (bw > 0)
        {
            program_buf[bw] = 0;
            //  printf("\r\n%s ÎÄ¼şÄÚÈİ : \r\n%s\r\n", path,buf);
        }
        f_close(&file_usb);
        if(InstrumentType==TYPE_AS154)//fmc161025
        {
            if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='4')
                continue;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
        }
        else if(InstrumentType==TYPE_AS153)//fmc161025
        {
            if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='3')
                continue;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
        }
        else//155
        {
            if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='5')
                continue;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
        }
        f_close(&file_usb);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
        //*********************
        creat_usb_program_table(program_buf,file_usb.fsize,nb++);
        //creat_program_table(program_buf,file_usb.fsize); //È¡³öÒ»¸ö³ÌĞòÎÄ¼şÖĞÃû×Ö£¬²½ÖèÊı£¬ĞŞ¸ÄÊ±¼ä±£´æµ½EEP±í¸øLISTVIEWÓÃ
    }
    //read_eep_progrm();

    //************************
    usb_program_number=nb;
    f_close(&file_usb);
    f_mount(NULL,FS_VOLUME_USB, 0);
    //read_eep_progrm();
    //Refresh_Pragram_Row(); //Ë¢ĞÂ
    return falg_err;
}
//**************************************
//½«³ÌĞòÎÄ¼şĞ¡ÓÚÒ»ĞĞÊ±¼äÊı¾İ×ª»»ÎªcentINT´æµ½program_int_buf
//ÊäÈë³ÌĞòÎÄ¼şµÚ¼¸¸öÊı¾İÎ»ÖÃnb¿ªÊ¼×ª£¬ĞèÒª×ªcent¸öINTÊı¾İ
//·µ»Ø 0£¬Ê§°Ü£¬ÆäËû±íÊ¾×ª»»ÍêºóÊı¾İÎ»ÖÃ

int CharToIntTime(int nb)
{

    char str4[10],a;
    int i,k,n;

    for(k=0; k<6; k++) //ÄêÔÂÈÕÊ±·ÖÃë 6¸ö
    {
        for(n=0; n<10; n++)
            str4[n]=0x35;
        for(i=0; i<10; i++)
        {
            a=program_buf[nb++];
            if(a>0x39||a<0x30)
                break;

            if(a==0x0d)
            {   nb++;
                break;
            }
            str4[i]=a;
        }
        str4[i]='\0';
        //program_int_buf[k]=atoi(str4);        //==>0XF
        sscanf(str4, "%d", &program_int_buf[k]);//==>0X15
        if(a==0x0d)
            break;
    }
    return nb;
}
//È¡³öÒ»¸ö³ÌĞòÎÄ¼şÖĞÃû×Ö£¬²½ÖèÊı£¬ĞŞ¸ÄÊ±¼ä±£´æµ½ UsbProgramName
u8  creat_usb_program_table(char *buf,int len,char number)
{
    int i,nb,k;
//	     u8 time[22],tt[4];
    char a;//,str[14][5];

    for(i=0; i<PROGRAM_NAME_LENGTH; i++)
        UsbProgramName[number].Name[i]=0;//cshh
    //************
    nb=0;
    for(k=0; k<file_usb.fsize; k++)
    {
        if(*(buf++)!=0x0a)  //»»ĞĞ ÏÂÒ»×Ö½Ú¾ÍÊÇĞÂĞĞµÚÒ»×Ö½Ú
            continue;

        nb++;

        if(nb==1)//name
        {
            for(i=0; i<PROGRAM_NAME_LENGTH; i++)
            {
                a=*(buf+5+i);
                if(a==0x20||a==0x0D)
                    break;
                UsbProgramName[number].Name[i]=a;

            }
        }
        else if(nb==2)//²½ÖèÊı
        {

        }
        else if(nb==3)//¿ì½İºÍËø
        {
            UsbProgramName[number].ShortCutFlag=0;//*(buf+7)-0x30;
            // UsbProgramName.LockFlag=*(buf+8)-0x30;
        }
        else if(nb==4)//ĞŞ¸ÄÊ±¼ä
        {
            CharToIntTime(6+k);

            UsbProgramName[number].DateTime.Year=program_int_buf[0];
            UsbProgramName[number].DateTime.Month=program_int_buf[1];
            UsbProgramName[number].DateTime.Day=program_int_buf[2];
            UsbProgramName[number].DateTime.Hour=program_int_buf[3];
            UsbProgramName[number].DateTime.Min=program_int_buf[4];
            UsbProgramName[number].DateTime.Sec=program_int_buf[5];
        }

    }
    // if(Write_eep_progrm())
    //	   return 1;
    return 0;

}
//¢*************************************
//È¡³öÒ»¸ö³ÌĞòÎÄ¼şÖĞÃû×Ö£¬²½ÖèÊı£¬ĞŞ¸ÄÊ±¼ä±£´æµ½ ProgramName
u8  creat_spi_program_table(char *buf)
{
    int i,nb,k;
    // u8 time[22],tt[4];
    char a;

    nb=0;
    for(k=0; k<FILE_HEAD_LENCH; k++)
    {
        if(*(buf++)!=0x0a)  //»»ĞĞ ÏÂÒ»×Ö½Ú¾ÍÊÇĞÂĞĞµÚÒ»×Ö½Ú
            continue;

        nb++;

        if(nb==1)//name
        {
            for(i=0; i<PROGRAM_NAME_LENGTH; i++)
            {
                a=*(buf+5+i);
                if(a==0x20||a==0x0D)
                    break;
                ProgramName[ProgramMax].Name[i]=a;

            }
        }
        else if(nb==2)//²½ÖèÊı
        {

        }
        else if(nb==3)//¿ì½İºÍËø
        {   //a=*(buf+7);
            //a=*(buf+8);
            ProgramName[ProgramMax].ShortCutFlag=*(buf+7)-0x30;
            ProgramName[ProgramMax].LockFlag=*(buf+8)-0x30;
        }
        else if(nb==4)//ĞŞ¸ÄÊ±¼ä
        {
            CharToIntTime(6+k);

            ProgramName[ProgramMax].DateTime.Year=program_int_buf[0];
            ProgramName[ProgramMax].DateTime.Month=program_int_buf[1];
            ProgramName[ProgramMax].DateTime.Day=program_int_buf[2];
            ProgramName[ProgramMax].DateTime.Hour=program_int_buf[3];
            ProgramName[ProgramMax].DateTime.Min=program_int_buf[4];
            ProgramName[ProgramMax].DateTime.Sec=program_int_buf[5];

            ProgramMax++;
            return 0;
        }

    }
    // if(Write_eep_progrm())
    //	   return 1;
    return 1;

}
//*********************************//**********************fmc161013s
//µ¼³öµÚCENT¸öÎÄ¼ş
char output_one_program(char cent)
{

//   FRESULT fr;          /* FatFs function common result code */
    UINT  bw;         /* File read/write count */
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

    strcpy(CurrProgramName.Name, ProgramName[cent].Name);
    if( Read_Spi_File())
        return 1;  //¶ÁSPIÎÄ¼şÊ§°Ü
    falg_err=0;
    //**************************¹ÒÔØÎÄ¼ş
    if(f_mount(&fs_usb, FS_VOLUME_USB1, 0)!= FR_OK)
        return 1;  //Ê§°Ü
    //*************************´ò¿ªÖ÷Ä¿Â¼
    sprintf(path_usb, "%s/", FS_VOLUME_USB);

    if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
        return  2;
    //*************************´ò¿ªUÅÌ×ÓÄ¿Â¼
    strcat(path_usb,DIR_USB_PROGRAM_OUTPUT);

    if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
        return  2;

    //*********************fmc161013ÖØÃûÌáÊ¾
    strcat(path_usb,"/");
    strcat(path_usb,ProgramName[cent].Name);////fmc160914
    strcat(path_usb,".txt");//fmc160914
    result = f_open(&file_usb, path_usb, FA_OPEN_EXISTING | FA_READ);
    if (result == FR_OK)
    {
        f_close(&file_usb);
        if(Prompt_select_two(PROMPT_INPUT_PROGRAM_NAME_SAME)==0)
        {

            return 0;
        }
    }
    program_cent++;//fmc161013
    //***********************¶ÁÈ¡µ±Ç°ÎÄ¼ş¼ĞÏÂµÄÎÄ¼şºÍÄ¿Â¼//

    result = f_open(&file_usb, path_usb, FA_CREATE_ALWAYS | FA_WRITE);
    if (result != FR_OK)
        return 7; //ÎÄ¼şĞ´ÈëÊ§°Ü

    result = f_write(&file_usb, &program_buf, file.fsize, &bw);//file.fsize  spiÎÄ¼ş
    if (result != FR_OK)
        return 7; //ÎÄ¼şĞ´ÈëÊ§°Ü
    //f_close(&file_spi);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
    // ¹Ø±ÕÎÄ¼şÏµÍ³ FIL file_spi,file_usb;
    f_close(&file_usb);
    f_mount(NULL,FS_VOLUME_USB, 0);

    return 0;
}
//¢*********************
//µ¼ÈëµÚCENT¸öÎÄ¼ş
char input_one_program(char cent)
{

//    FRESULT fr;          /* FatFs function common result code */
    UINT  bw;         /* File read/write count */
//	u8 falg_err;
    FRESULT result;
    //FATFS fs;
    DIR DirInf[2];
    FILINFO FileInf_Usb;//,FileInf_Spi;
//	uint32_t cnt = 0;
    char lfname[256];
    char path_spi[32],path_usb[32];
    u8 i;

    for(i=0; i<32; i++)
    {
        path_spi[i]=0;
        path_usb[i]=0;
    }
//	  falg_err=0;
    //**************************¹ÒÔØÎÄ¼ş
    if(f_mount(&fs_usb, FS_VOLUME_USB1, 0)!= FR_OK)
        return 1;  //Ê§°Ü
    if(f_mount(&fs_spi, FS_VOLUME_SPI1, 0)!= FR_OK)
        return 1;  //Ê§°Ü

    //*************************´ò¿ªspi¸ùÎÄ¼ş¼Ğ
    strcpy(path_spi, FS_VOLUME_SPI1);
    result = f_opendir(&DirInf[1], path_spi);
    if (result != FR_OK)
        return 2; //´ò¿ª¸ùÄ¿Â¼Ê§°Ü

    //*************************´ò¿ªÖ÷Ä¿Â¼
    sprintf(path_usb, "%s/", FS_VOLUME_USB);
    //strcpy(path_usb, FS_VOLUME_USB1);
    if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
        return  2;
    //*************************´ò¿ª×ÓÄ¿Â¼
    strcat(path_usb,DIR_USB_PROGRAM_INPUT);

    if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
        return  2;
    //***********************¶ÁÈ¡µ±Ç°ÎÄ¼ş¼ĞÏÂµÄÎÄ¼şºÍÄ¿Â¼
    FileInf_Usb.lfname = lfname;
    FileInf_Usb.lfsize = 256;

    //´ò¿ªÎÄ¼ş
    strcpy(FileInf_Usb.fname, UsbProgramName[cent].Name);

    strcpy(path_usb, FS_VOLUME_USB);
    //sprintf(path_usb, "%s/", DIR_USB_PROGRAM_INPUT);
    strcat(path_usb,DIR_USB_PROGRAM_INPUT);
    strcat(path_usb,"/");
    strcat(path_usb,FileInf_Usb.fname);//
    strcat(path_usb,".txt");//fmc160914
    result = f_open(&file_usb,path_usb, FA_OPEN_EXISTING | FA_READ);
    if (result !=  FR_OK)
    {
        return 4;    //Ã»ÓĞÎÄ¼ş
    }

    //¶ÁÈ¡UÅÌÎÄ¼ş */
    result = f_read(&file_usb, &program_buf, file_usb.fsize, &bw);
    if (bw > 0)
    {
        program_buf[bw] = 0;
        //  printf("\r\n%s ÎÄ¼şÄÚÈİ : \r\n%s\r\n", path,buf);
    }
    f_close(&file_usb);
    if(InstrumentType==TYPE_AS154)
    {
        if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='4')
            return 6;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
    }
    else 	if(InstrumentType==TYPE_AS153)
    {
        if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='3')
            return 6;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
    }
    else
    {
        if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='5')
            return 6;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
    }
    //**********************
    file.fsize=file_usb.fsize;//ÎÄ¼ş³¤¶È
    if(read_and_check_ProgramStep(NOT_READ_FILE))
        return 9;               //ÅĞ¶ÏÎÄ¼şÊı¾İºÏ·¨
    //**********************
    strcpy(path_spi, FS_VOLUME_SPI1);
    strcat(path_spi,FileInf_Usb.fname);
    strcat(path_spi,".txt");//fmc160914
    //*********************ÖØÃûÌáÊ¾
    result = f_open(&file_spi, path_spi, FA_OPEN_EXISTING | FA_READ);
    if (result == FR_OK)
    {   f_close(&file_spi);
        if(Prompt_select_two(PROMPT_INPUT_PROGRAM_NAME_SAME)==0)
        {
            //f_close(&file_spi);
            return 0;
        }
    }
    program_cent++;//fmc161013
    //**********************
    result = f_open(&file_spi, path_spi, FA_CREATE_ALWAYS | FA_WRITE);
    if (result != FR_OK)
        return 7;
    //Ğ´USBÎÄ¼şµ½SPI
    result = f_write(&file_spi, &program_buf, file_usb.fsize, &bw);
    if (result != FR_OK)
        return 7; //ÎÄ¼şĞ´ÈëÊ§°Ü

    f_close(&file_spi);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
    //*********************
    creat_program_table(program_buf,file_usb.fsize); //È¡³öÒ»¸ö³ÌĞòÎÄ¼şÖĞÃû×Ö£¬²½ÖèÊı£¬ĞŞ¸ÄÊ±¼ä±£´æµ½EEP±í¸øLISTVIEWÓÃ

    //************************
    // ¹Ø±ÕÎÄ¼şÏµÍ³ FIL file_spi,file_usb;
    f_close(&file_spi);
    f_close(&file_usb);
    f_mount(NULL,FS_VOLUME_USB, 0);
    f_mount(NULL,FS_VOLUME_SPI, 0);
    //read_eep_progrm();
    Refresh_Pragram_Row(); //Ë¢ĞÂ
    return 0;
}//**********************fmc161013e
//****************************
//¶Á³öSPI³ÌĞòÎÄ¼şÉú³É±í
unsigned char read_all_program_head(void)
{
//   FRESULT fr;          /* FatFs function common result code */
    UINT  bw;         /* File read/write count */
    u8 falg_err;
    FRESULT result;
    int i,k;

    DIR DirInf;
    FILINFO FileInf;
    uint32_t cnt = 0;
    char lfname[256];
    char path[32];

    for(k=0; k<PROGRAM_MAX; k++) //³õÊ¼»¯Ãû×Ö fmc160907
    {
        for(i=0; i<PROGRAM_NAME_LENGTH; i++)
            ProgramName[k].Name[i]=0;
    }

    ProgramMax=0;
    //for(i=0;i<)
    falg_err=0;
    result = f_mount(&fs, FS_VOLUME_SPI, 0);			/* Mount a logical drive */
    if (result != FR_OK)
        return 1;
    sprintf(path, "%s/", FS_VOLUME_SPI);
    result = f_opendir(&DirInf, path); 	/* 1: ±íÊ¾ÅÌ·û */
    if (result != FR_OK)
        return 2;
    //***********************¶ÁÈ¡µ±Ç°ÎÄ¼ş¼ĞÏÂµÄÎÄ¼şºÍÄ¿Â¼
    FileInf.lfname = lfname;
    FileInf.lfsize = 256;
//    nb=0;

    for (cnt = 0; ; cnt++)
    {
        for(i=0; i<PROGRAM_NAME_LENGTH; i++)
            FileInf.fname[i]=0;//³õÊ¼»¯

        if(ProgramMax>=PROGRAM_MAX)
            return 0;
        result = f_readdir(&DirInf,&FileInf); 		/* ¶ÁÈ¡Ä¿Â¼Ïî£¬Ë÷Òı»á×Ô¶¯ÏÂÒÆ */
        if (result != FR_OK || FileInf.fname[0] == 0)
        {
            falg_err=3;
            break;//Ã»ÓĞÎÄ¼ş
        }
        if (FileInf.fname[0] == '.')
            continue;

        //ÅĞ¶ÏÊÇÎÄ¼ş»¹ÊÇ×ÓÄ¿Â¼
        if (FileInf.fattrib & AM_DIR)
            continue;  //Ä¿Â¼

        for(i=0; i<PROGRAM_NAME_LENGTH; i++)
        {
            if(FileInf.fname[i]=='.')
                break;
        }
        if(FileInf.fname[i+1]!='t'||FileInf.fname[i+2]!='x'||FileInf.fname[i+3]!='t')
        {
            if(FileInf.fname[i+1]!='T'||FileInf.fname[i+2]!='X'||FileInf.fname[i+3]!='T')
                continue;  //²»ÊÇ³ÌĞòÎÄ¼ş
        }
//*******************
        //´ò¿ªÎÄ¼ş
        strcpy(path, FS_VOLUME_SPI);
        strcat(path,FileInf.fname);//*/
        result = f_open(&file,path, FA_OPEN_EXISTING | FA_READ);
        if (result !=  FR_OK)
        {
            falg_err=4;
            goto err;
        }

        //¶ÁÎÄ¼ş
        result = f_read(&file, &program_buf,file.fsize , &bw);//file.fsize FILE_HEAD_LENCH
        if (bw > 0)
        {
            program_buf[bw] = 0;
        }

        f_close(&file);
        if(InstrumentType==TYPE_AS154)//fmc161025
        {
            if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='4')
                continue;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
        }
        else if(InstrumentType==TYPE_AS153)//fmc161025
        {
            if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='3')
                continue;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
        }
        else//155
        {
            if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='5')
                continue;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş
        }
        program_buf[0]=0;
        f_close(&file);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
        //*********************

        ProgramName[ProgramMax].CreatTime=FileInf.fdate;	//FMC161107
        ProgramName[ProgramMax].CreatTime=ProgramName[ProgramMax].CreatTime<<16;//FMC161022
        ProgramName[ProgramMax].CreatTime=ProgramName[ProgramMax].CreatTime+FileInf.ftime;//FMC161022

        creat_spi_program_table(program_buf);
        //creat_program_table(program_buf,file_usb.fsize); //È¡³öÒ»¸ö³ÌĞòÎÄ¼şÖĞÃû×Ö£¬²½ÖèÊı£¬ĞŞ¸ÄÊ±¼ä±£´æµ½EEP±í¸øLISTVIEWÓÃ
    }
    return 0;
    //************************
err:
    f_close(&file);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
    f_mount(NULL,FS_VOLUME_SPI, 0);
    return falg_err;

}
//*****************************************
int  get_status_address(char *buf)
{
    int nb,k;
//	     u8 time[22],tt[4];
//	     char a;

    nb=0;
    for(k=0; k<FILE_HEAD_LENCH; k++)
    {
        if(*(buf++)!=0x0a)  //»»ĞĞ ÏÂÒ»×Ö½Ú¾ÍÊÇĞÂĞĞµÚÒ»×Ö½Ú
            continue;

        nb++;

        if(nb==1)//name
        {

        }
        else if(nb==2)//²½ÖèÊı
        {

        }
        else if(nb==3)//¿ì½İºÍËø
        {   //a=*(buf+7);
            //a=*(buf+8);
            return k+8;
            //ProgramName[ProgramMax].ShortCutFlag=*(buf+7)-0x30;
            //ProgramName[ProgramMax].LockFlag=*(buf+8)-0x30;
        }

    }
    return 0;
}
//¢******************************
//ĞŞ¸Ä³ÌĞòÎÄ¼ş STASUT±êÖ¾
u8 Save_flag(void)
{
//return 0;
//    FRESULT fr;
    UINT  bw;
    u8 falg_err,i;
    FRESULT result;
//	int fsize;
    //FATFS fs;
    DIR DirInf;
//	FILINFO FileInf_Usb,FileInf_Spi;
    uint32_t address;
//	char lfname[256];
    char path[32];//¢,path_usb[32];
//	char buf[128];
    /*	for(i=0;i<PROGRAM_NAME_LENGTH;i++)//fmc160914s
    	{
    		if(CurrProgramName.Name[i]=='.')
    			break;
    	}
    	if(i==PROGRAM_NAME_LENGTH)
    	{*///fmc160914e
    //	sprintf(CurrProgramName.Name, "%s.txt", CurrProgramName.Name);//
    //}//fmc160829s

    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, FS_VOLUME_SPI, 0);			/* Mount a logical drive */
    if (result != FR_OK)
        return 1;

    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    sprintf(path, "%s/", FS_VOLUME_SPI);
    result = f_opendir(&DirInf, path); 	/* 1: ±íÊ¾ÅÌ·û */
    if (result != FR_OK)
        return 2;

    sprintf(path, "%s%s%s ", FS_VOLUME_SPI,CurrProgramName.Name,".txt");//fmc160914
    result = f_open(&file, path, FA_OPEN_EXISTING | FA_READ);

    if (result !=  FR_OK)
    {
        falg_err=4;
        goto err;
    }
    result = f_read(&file, &program_buf, FILE_HEAD_LENCH, &bw);//file.fsize
    if (result !=  FR_OK)
    {
        falg_err=4;
        goto err;
    }
    if (bw > 0)
    {
        program_buf[bw] = 0;
    }
    //***********
    address=get_status_address(program_buf);
    f_close(&file);
    result = f_open(&file, path,  FA_OPEN_EXISTING | FA_WRITE);//ÒÔĞ´·½Ê½´ò¿ªÎÄ¼ş
    if (result != FR_OK)
    {
        falg_err=4;
        goto err;
    }
    //***********
    if(address==0||address>100)
        return 5;
    program_buf[0]=ProgramName[Curr_program_Row].ShortCutFlag+0x30;//0x35;
    program_buf[1]=ProgramName[Curr_program_Row].LockFlag+0x30;//0x35;
    if(program_buf[0]!=0x30)
        program_buf[0]=0x31;
    if(program_buf[1]!=0x30)
        program_buf[1]=0x31;
    //  result = f_open(&file_spi, path, FA_CREATE_ALWAYS | FA_WRITE);//ÒÔĞ´·½Ê½´ò¿ªÎÄ¼
    f_lseek(&file,address);
    //****************************
    //ÎÄ¼şµ½SPI
    result = f_write(&file, &program_buf, 2, &bw);
    if (result != FR_OK)
    {
        falg_err=4;
        goto err;
    }	   //ÎÄ¼şĞ´ÈëÊ§°Ü
    f_close(&file);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
    f_mount(NULL,FS_VOLUME_SPI, 0);

    //if(Write_eep_progrm())
    //	   return 1;
    return 0;
err:
    f_close(&file);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
    f_mount(NULL,FS_VOLUME_SPI, 0);
    return falg_err;
}
//*/
//******************************************

//********************************************
//»ñµÃÉı¼¶³ÌĞòÎÄ¼şÃû 0ÉÏÎ»»ú1ÏÂÎ»»ú
char find_update_file_name(unsigned char cent)
{
    char *name1="AS154H",*name2="AS154L";
//    FRESULT fr;          /* FatFs function common result code */
    UINT bw;         /* File read/write count */
    u8 falg_err,nb,i;
    FRESULT result;
    //FATFS fs;
    DIR DirInf[2];
    FILINFO FileInf_Usb;
    uint32_t cnt = 0;
    char lfname[256];
    char path_usb[32];



    falg_err=0;
    //**************************¹ÒÔØÎÄ¼ş
    if(f_mount(&fs_usb, FS_VOLUME_USB, 0)!= FR_OK)
    {
        falg_err=1;  //Ê§°Ü
        goto err;
    }
    //*************************´ò¿ªÖ÷Ä¿Â¼
    sprintf(path_usb, "%s/", FS_VOLUME_USB);
    //strcpy(path_usb, FS_VOLUME_USB1);
    if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
    {
        falg_err=1;  //Ê§°Ü
        goto err;
    }
    //*************************´ò¿ª×ÓÄ¿Â¼
    strcat(path_usb,DIR_USB_PROGRAM_UPDATE);

    if ( f_opendir(&DirInf[0], path_usb)!= FR_OK)
    {
        falg_err=1;  //Ê§°Ü
        goto err;
    }
    //***********************¶ÁÈ¡µ±Ç°ÎÄ¼ş¼ĞÏÂµÄÎÄ¼şºÍÄ¿Â¼
    FileInf_Usb.lfname = lfname;
    FileInf_Usb.lfsize = 256;
    nb=0;
    for (cnt = 0; ; cnt++)
    {
        result = f_readdir(&DirInf[0],&FileInf_Usb); 		/* ¶ÁÈ¡Ä¿Â¼Ïî£¬Ë÷Òı»á×Ô¶¯ÏÂÒÆ */
        if (result != FR_OK || FileInf_Usb.fname[0] == 0)
        {
            falg_err=0;
            break;//Ã»ÓĞÎÄ¼ş ¶ÁÍê
        }
        if (FileInf_Usb.fname[0] == '.')
            continue;

        //ÅĞ¶ÏÊÇÎÄ¼ş»¹ÊÇ×ÓÄ¿Â¼
        if (FileInf_Usb.fattrib & AM_DIR)
            continue;  //Ä¿Â¼
        nb=0;
        if( strncmp(FileInf_Usb.fname,name1,6)==0&&cent==0)
        {
            for(i=0; i<20; i++)
            {
                update_file_name[i]=FileInf_Usb.fname[i];
                if(update_file_name[i]=='.')
                    nb=i;
            }
            if(update_file_name[nb+1]=='b'||update_file_name[nb+1]=='B')
                return 0;
        }
        if( strncmp(FileInf_Usb.fname,name2,6)==0&&cent==1)
        {
            for(i=0; i<20; i++)
            {
                update_file_name[i]=FileInf_Usb.fname[i];
                if(update_file_name[i]=='.')
                    nb=i;
            }
            if(update_file_name[nb+1]=='b'||update_file_name[nb+1]=='B')
                return 0;
        }

        //´ò¿ªÎÄ¼ş
        /*	strcpy(path_usb, FS_VOLUME_USB);
        	//sprintf(path_usb, "%s/", DIR_USB_PROGRAM_INPUT);
          strcat(path_usb,DIR_USB_PROGRAM_INPUT);
        	strcat(path_usb,"/");
        strcat(path_usb,FileInf_Usb.fname);//
        result = f_open(&file_usb,path_usb, FA_OPEN_EXISTING | FA_READ);
        if (result !=  FR_OK)
          {
        		falg_err=4;
        		break;       //Ã»ÓĞÎÄ¼ş
        	}

        //¶ÁÈ¡UÅÌÎÄ¼ş
        result = f_read(&file_usb, &program_buf, file_usb.fsize, &bw);
        if (bw > 0)
        {
        	program_buf[bw] = 0;
          //  printf("\r\n%s ÎÄ¼şÄÚÈİ : \r\n%s\r\n", path,buf);
        }
        	f_close(&file_usb);
        		if(program_buf[0]!='A'||program_buf[1]!='S'||program_buf[2]!='1'||program_buf[3]!='5'||program_buf[4]!='4')
        			continue;//²»ÊÇ³ÌĞòÎÄ¼ş£¬¼ÌĞø¶ÁÏÂÒ»¸öÎÄ¼ş as154ÎÄ¼ş

        	f_close(&file_usb);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
        	//*********************
        	creat_usb_program_table(program_buf,file_usb.fsize,nb++);
        	//creat_program_table(program_buf,file_usb.fsize); //È¡³öÒ»¸ö³ÌĞòÎÄ¼şÖĞÃû×Ö£¬²½ÖèÊı£¬ĞŞ¸ÄÊ±¼ä±£´æµ½EEP±í¸øLISTVIEWÓÃ
        */
    }
    falg_err=5;
    //read_eep_progrm();
err:
    //************************

    f_close(&file_usb);
    f_mount(NULL,FS_VOLUME_USB, 0);
    //read_eep_progrm();
    //Refresh_Pragram_Row(); //Ë¢ĞÂ
    return falg_err;
}

//******************************************

u8 Read_send_bin_File(void)
{
    //#define  SPI_PROGRAM_ADDRESS        13*1024*1024//14 15M´æ³ÌĞò
    //#define  PROGRAM_PARAMETES_ADDRESS  15*1024*1024//×îºó16M´æÊı¾İ
#define  SEND_PAGE  1024

    uint8_t  data_buf[SEND_PAGE];
    FRESULT result;
    DIR DirInf;
    uint32_t bw,i,page,excess,address;
    char falg_err;
    char path[32],err=0;
    union data {
        uint8_t size_char[4];
        uint32_t size_long;
    };
    union data program_size;
    uint32_t nb,cent,send_len;

    if(find_update_file_name(1))
    {
        falg_err=1;
        goto err;
    }

    for(i=0; i<32; i++)
        path[i]=0;

    falg_err=0;
    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, FS_VOLUME_USB, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        falg_err=1;
        goto err;
    }
    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    sprintf(path, "%s/", FS_VOLUME_USB);
    result = f_opendir(&DirInf, path); 	/* 1: ±íÊ¾ÅÌ·û */
    if (result != FR_OK)
    {
        falg_err=1;
        goto err;
    }
    //*************************´ò¿ª×ÓÄ¿Â¼
    strcat(path,DIR_USB_PROGRAM_UPDATE);
    if ( f_opendir(&DirInf, path)!= FR_OK)
    {
        falg_err=2;
        goto err;
    }

    strcpy(path, FS_VOLUME_USB);
    //sprintf(path_usb, "%s/", DIR_USB_PROGRAM_INPUT);
    strcat(path,DIR_USB_PROGRAM_UPDATE);
    strcat(path,"/");
    //strcat(path,UPDATE_PROGRAM_NAME);//*/
    strcat(path,update_file_name);
//	sprintf(path, "%s/%s ", FS_VOLUME_USB,UPDATE_PROGRAM_NAME);
    result = f_open(&file, path, FA_OPEN_EXISTING | FA_READ);
    if (result !=  FR_OK)
    {
        falg_err=3;
        goto err;
    }
    cent=0;
    //****************************************
    hMem3=GUI_ALLOC_AllocZero(512*1024);//????????,?????? FMC
    update103_buf=GUI_ALLOC_h2p(hMem3);
    if(file.fsize>512*1024)
        file.fsize=512*1024;
    result = f_read(&file, &update103_buf,file.fsize , &bw);
    if (result !=  FR_OK)
    {
        falg_err=3;
        goto err;
    }
    //******************************
err:
    //****************
    f_close(&file);
    f_mount(NULL,FS_VOLUME_USB, 0);
    return falg_err;
}
//**************************
//¶ÁÈ¡Éı¼¶³ÌĞò·¢¸øÏÂÎ»»ú¼ş
u8 Read_send_bin_File1(void)
{
    //#define  SPI_PROGRAM_ADDRESS        13*1024*1024//14 15M´æ³ÌĞò
    //#define  PROGRAM_PARAMETES_ADDRESS  15*1024*1024//×îºó16M´æÊı¾İ
#define  SEND_PAGE  512

    uint8_t  data_buf[SEND_PAGE];
    FRESULT result;
    DIR DirInf;
    uint32_t bw,i,page,address;
    char falg_err;
    char path[32],err=0;
    union data {
        uint8_t size_char[4];
        uint32_t size_long;
    };
    union data program_size;
    uint32_t nb,cent,send_len;
    int page_max,excess, page_cent,k,m;

    if(find_update_file_name(1))
    {
        falg_err=1;
        goto err;
    }

    for(i=0; i<32; i++)
        path[i]=0;

    falg_err=0;
    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, FS_VOLUME_USB, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        falg_err=1;
        goto err;
    }
    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    sprintf(path, "%s/", FS_VOLUME_USB);
    result = f_opendir(&DirInf, path); 	/* 1: ±íÊ¾ÅÌ·û */
    if (result != FR_OK)
    {
        falg_err=1;
        goto err;
    }
    //*************************´ò¿ª×ÓÄ¿Â¼
    strcat(path,DIR_USB_PROGRAM_UPDATE);
    if ( f_opendir(&DirInf, path)!= FR_OK)
    {
        falg_err=2;
        goto err;
    }

    strcpy(path, FS_VOLUME_USB);
    //sprintf(path_usb, "%s/", DIR_USB_PROGRAM_INPUT);
    strcat(path,DIR_USB_PROGRAM_UPDATE);
    strcat(path,"/");
    //strcat(path,UPDATE_PROGRAM_NAME);//*/
    strcat(path,update_file_name);
//	sprintf(path, "%s/%s ", FS_VOLUME_USB,UPDATE_PROGRAM_NAME);
    result = f_open(&file, path, FA_OPEN_EXISTING | FA_READ);
    if (result !=  FR_OK)
    {
        falg_err=3;
        goto err;
    }
    cent=0;
    if(file.fsize>100*1024)
        file.fsize=100*1024;
    //****************************************
    /* ¶ÁÈ¡ÎÄ¼ş */    //
    page=file.fsize/SEND_PAGE;
    excess=file.fsize%SEND_PAGE;
    nb=page;
//***************************
    flag_start_update=0;
    for(i=0; i<3; i++)
    {
        UART6_Send(CMD_UPDATE,0);
        for(m=0; m<10; m++)
        {
            GUI_Delay(100);
            if(flag_start_update==1)
                break;
        }
        if(m<10)
            break;
    }
    if(i>=3)
    {
        Prompt_select(PROMPT_UPDATA_DISCONNECT);
        falg_err=11;
        goto err;
    }
    refresh_PROGBAR(1);
    GUI_Delay(10);
    for(i=0; i<3; i++)
    {
        UART6_Send(CMD_UPDATE_START ,0);
        for(m=0; m<20; m++)
        {
            GUI_Delay(100);
            if(flag_start_update==2)
                break;
        }
        if(m<20)
            break;
    }
    if(i>=3)
    {
        Prompt_select(PROMPT_UPDATA_DISCONNECT);
        falg_err=11;
        goto err;
    }
    GUI_Delay(10);
//*****************************
    //page_cent=0;
    for(i=0; i<page+1; i++)
    {   update_data_nember=i;
        result = f_read(&file, &data_buf,SEND_PAGE , &bw);
        if (result != FR_OK)
        {
            falg_err=4;
            goto err;
        }
        if(i==page)
        {
            for(k=excess; k<512; k++)
                data_buf[k]=0xff;
        }
        //	Usb_check();
        if(flag_usb_disk_connect==0)//fmc160928
        {
            falg_err=4;
            goto err;
        }
        //********************·¢ËÍºÍ½ÓÊÕ SEND_PAGE
        UART_Send_Buf[5]=i>>8;
        UART_Send_Buf[6]=i;
        //address=page_cent*512;
        for(m=0; m<512; m++)
            UART_Send_Buf[7+m]=data_buf[m];
        for(k=0; k<3; k++) //·¢Èı´Î
        {
            flag_update_one_ok=0;
            UART6_Send(CMD_UPDATE_SEND,0);
            for(m=0; m<200; m++)
            {
                GUI_Delay(10);
                if(flag_update_one_ok)
                    break;
            }
            if(flag_update_one_ok)
                break;
        }
        if(flag_update_one_ok==0)
        {
            Prompt_select(PROMPT_UPDATA_DISCONNECT);
            {
                falg_err=11;
                goto err;
            }
        }
        //************************
        cent=i*100/page;
        if(cent!=0&&cent!=100)
            refresh_PROGBAR(cent);
        GUI_Delay(10);

    }
    for(k=0; k<2; k++) //·¢Èı´Î
    {
        flag_update_one_ok=0;
        UART6_Send(CMD_UPDATE_END,0);
        for(m=0; m<200; m++)
        {
            GUI_Delay(100);
            if(flag_update_one_ok)
                break;
        }
        if(flag_update_one_ok)
            break;
    }
    if(flag_update_one_ok==0)
    {
        Prompt_select(PROMPT_UPDATA_DISCONNECT);
        {
            falg_err=11;
            goto err;
        }
    }
    GUI_Delay(100);
    if(flag_usb_disk_connect==0)//fmc160928
    {
        falg_err=4;
        goto err;
    }
    refresh_PROGBAR(100);
    GUI_Delay(10);
    Prompt_select(PROMPT_UPDATA_OK);
    //lgj161013 start
    GUI_Delay(100);
    UART6_Send(CMD_CHECK,UartActiveData);
    GUI_Delay(10);
    //lgj161013 end
    //*****************************

    //*****************************
    //****************
err:
    Prompt_select(PROMPT_UPDATA_DISCONNECT);//PROMPT_NO_U_DISK);
    flag_update_busy=0;
    f_close(&file);
    f_mount(NULL,FS_VOLUME_USB, 0);
    return 0;

}

//********************************************
//½«USBÖĞÉÏÎ»»úÉı¼¶³ÌĞò×ª´æµ½SPIÖĞ
u8 Read_write_bin_File(void)
{
#define  SPI_PROGRAM_ADDRESS        13*1024*1024//14 15M´æ³ÌĞò
#define  PROGRAM_PARAMETES_ADDRESS  15*1024*1024//×îºó16M´æÊı¾İ
#define  SPI_PAGE  4096

    uint8_t  data_buf[SPI_PAGE];
    FRESULT result;
    DIR DirInf;
    uint32_t bw,i,page,excess,address;
    char falg_err;
    char path[32],err=0;
    union data {
        uint8_t size_char[4];
        uint32_t size_long;
    };
    union data program_size;
    uint32_t nb,cent;
    // for(i=0;i<program_buf_len;i++)//³õÊ¼»¯
    //    program_buf[i]=0;

    if(find_update_file_name(0))
    {
        falg_err=1;
        goto err;
    }
    for(i=0; i<32; i++)
        path[i]=0;

    falg_err=0;
    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, FS_VOLUME_USB, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        falg_err=1;
        goto err;
    }
    /* ´ò¿ª¸ùÎÄ¼ş¼Ğ */
    sprintf(path, "%s/", FS_VOLUME_USB);
    result = f_opendir(&DirInf, path); 	/* 1: ±íÊ¾ÅÌ·û */
    if (result != FR_OK)
    {
        falg_err=1;
        goto err;
    }
    //*************************´ò¿ª×ÓÄ¿Â¼
    strcat(path,DIR_USB_PROGRAM_UPDATE);
    if ( f_opendir(&DirInf, path)!= FR_OK)
    {
        falg_err=2;
        goto err;
    }

    strcpy(path, FS_VOLUME_USB);
    //sprintf(path_usb, "%s/", DIR_USB_PROGRAM_INPUT);
    strcat(path,DIR_USB_PROGRAM_UPDATE);
    strcat(path,"/");
//	strcat(path,UPDATE_PROGRAM_NAME);//*/
    strcat(path,update_file_name);
//	sprintf(path, "%s/%s ", FS_VOLUME_USB,UPDATE_PROGRAM_NAME);
    result = f_open(&file, path, FA_OPEN_EXISTING | FA_READ);
    if (result !=  FR_OK)
    {
        falg_err=3;
        goto err;
    }
    cent=0;
    //****************************************
    /* ¶ÁÈ¡ÎÄ¼ş */    //
    page=file.fsize/SPI_PAGE;
    excess=file.fsize%SPI_PAGE;
    //page=page;
    nb=page;
    address=SPI_PROGRAM_ADDRESS;
    for(i=0; i<page; i++)
    {
        result = f_read(&file, &data_buf,SPI_PAGE , &bw);
        if (result != FR_OK)
        {
            falg_err=4;
            goto err;
        }
        if(flag_usb_disk_connect==0)//fmc160928
        {
            falg_err=4;
            goto err;
        }
        if(sf_WriteBuffer( data_buf,address, SPI_PAGE)==0)
        {
            falg_err=11;
            goto err;
        }
        address=address+SPI_PAGE;

        cent=i*100/page;
        refresh_PROGBAR(cent);

    }
    result = f_read(&file, &data_buf,excess, &bw);//Ê£ÓàĞ¡ÓÚ4KÊı¾İ
    if (result != FR_OK)
    {
        falg_err=4;
        goto err;
    }


    data_buf[excess]=0xff;//×îºóÒ»×Ö½ÚÇå0xFF
    //Usb_check();
    GUI_Delay(100);
    if(flag_usb_disk_connect==0)//fmc160928
    {
        falg_err=4;
        goto err;
    }
    if(sf_WriteBuffer( data_buf,address, excess)==0)
    {
        falg_err=11;
        goto err;
    }
    //refresh_PROGBAR(100);
    //********************²âÊÔ
    /*for(i=2048;i<4096;i++)
     data_buf[i-2048]=data_buf[i];
    for(i=0;i<4096;i++)
     data_buf[i]=0;
    sf_ReadBuffer( data_buf,address+2048, 4096);*/
    //******************Ğ´6×Ö½Ú²ÎÊı
    program_size.size_long=file.fsize;
    data_buf[0]=0XAA;
    for(i=0; i<4; i++)
        data_buf[i+1]=program_size.size_char[i];
    data_buf[5]=0XAA;

    address=PROGRAM_PARAMETES_ADDRESS;
    if(sf_WriteBuffer( data_buf,address, 16)==0)
    {
        falg_err=11;
        goto err;
    }
    refresh_PROGBAR(100);
    //***********************
    /* for(i=2048;i<4096;i++)
     data_buf[i-2048]=data_buf[i];
    for(i=0;i<4096;i++)
     data_buf[i]=0;
    address=SPI_PROGRAM_ADDRESS;
    sf_ReadBuffer( data_buf,address, 4096);*/
    //******************************
    //****************
    flag_update_busy=0;
    f_close(&file);
    f_mount(NULL,FS_VOLUME_USB, 0);
    return 0;

err:
    flag_update_busy=0;
    f_close(&file);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
    f_mount(NULL,FS_VOLUME_SPI, 0);
//	beep();
    return falg_err;
}
//*******************Create_USB_Dir(FS_VOLUME_USB);
void Create_USB_Dir(char *_ucVolume)//fmc161013s
{
    /* ±¾º¯ÊıÊ¹ÓÃµÄ¾Ö²¿±äÁ¿Õ¼ÓÃ½Ï¶à£¬ÇëĞŞ¸ÄÆô¶¯ÎÄ¼ş£¬±£Ö¤¶ÑÕ»¿Õ¼ä¹»ÓÃ */
    FRESULT result;
//	FATFS fs;
    char path[32];

    /* ¹ÒÔØÎÄ¼şÏµÍ³ */
    result = f_mount(&fs, _ucVolume, 0);			/* Mount a logical drive */
    if (result != FR_OK)
    {
        printf("¹ÒÔØÎÄ¼şÏµÍ³Ê§°Ü (%d)\r\n", result);
    }

    /* ´´½¨Ä¿Â¼/Dir1 */
    sprintf(path, "%s/", _ucVolume);
    strcat(path,DIR_USB_PROGRAM_INPUT);
    result = f_mkdir(path);
    if (result == FR_OK)
    {
        printf("f_mkdir %s Ok\r\n", path);
    }
    else if (result == FR_EXIST)
    {
        printf("%s Ä¿Â¼ÒÑ¾­´æÔÚ(%d)\r\n",path, result);
    }
    else
    {
        printf("f_mkdir %s Ê§°Ü (%d)\r\n",path, result);
        //return;
    }
    /*
    	// ´´½¨Ä¿Â¼/Dir2
    	sprintf(path, "%s/input", _ucVolume);
    	result = f_mkdir(path);
    	if (result == FR_OK)
    	{
    		printf("f_mkdir %s Ok\r\n", path);
    	}
    	else if (result == FR_EXIST)
    	{
    		printf("%s Ä¿Â¼ÒÑ¾­´æÔÚ(%d)\r\n", path, result);
    	}
    	else
    	{
    		printf("f_mkdir %s Ê§°Ü (%d)\r\n", path, result);
    		//return;
    	}
    */
    /* ´´½¨×ÓÄ¿Â¼ /Dir1/Dir1_1	   ×¢Òâ£º´´½¨×ÓÄ¿Â¼Dir1_1Ê±£¬±ØĞëÏÈ´´½¨ºÃDir1 */
    /*sprintf(path, "%s//Dir1/Dir1_1", _ucVolume);
    result = f_mkdir(path);
    if (result == FR_OK)
    {
    	printf("f_mkdir %s ³É¹¦\r\n", path);
    }
    else if (result == FR_EXIST)
    {
    	printf("%s Ä¿Â¼ÒÑ¾­´æÔÚ (%d)\r\n",path, result);
    }
    else
    {
    	printf("f_mkdir %s Ê§°Ü (%d)\r\n",path, result);
    	return;
    }*/

    /* Ğ¶ÔØÎÄ¼şÏµÍ³ */
    f_mount(NULL,_ucVolume, 0);
}//fmc161013e


//****************************************************
//**********************ÒÔÏÂ½ØÆÁ**************************
/*extern FRESULT result;
extern FIL file;
extern FIL FileSave;   //×¨ÃÅÓÃÓÚÍ¼Æ¬µÄ±£´æ
extern DIR DirInf;
extern UINT bw;
extern FATFS fs;
extern FATFS fs_nand;

unsigned char Pic_Name=1;
extern UINT bw;
char *_screen_buf;
extern uint8_t Pic_Name;
void _WriteByte2File1(U8 Data, void * p)
{//FRESULT result;
	//result = f_write (p, &Data, 1, &bw);
	_screen_buf[file.fsize]=Data;
	file.fsize++;
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

   for(i=0;i<32;i++)
	 {
		// path_spi[i]=0;
	   path_usb[i]=0;
	 }
	 	hMem=GUI_ALLOC_AllocZero(800*480*3+100);//??????????????????????????????????FMC
    _screen_buf=GUI_ALLOC_h2p(hMem);

    //**************************¹ÒÔØÎÄ¼ş
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
    //***********************¶ÁÈ¡µ±Ç°ÎÄ¼ş¼ĞÏÂµÄÎÄ¼şºÍÄ¿Â¼//
      sprintf(path_usb,"2:/PicSave/%d.bmp",Pic_Name);//USB
	    result = f_open(&file, path_usb, FA_CREATE_ALWAYS | FA_WRITE);
	    if (result != FR_OK)
				return 7; //ÎÄ¼şĞ´ÈëÊ§°Ü

      GUI_BMP_Serialize(_WriteByte2File1, &file);

	    result = f_write(&file, _screen_buf, file.fsize, &bw);//file.fsize  spiÎÄ¼ş
	    if (result != FR_OK)
				return 7; //ÎÄ¼şĞ´ÈëÊ§°Ü
			//f_close(&file_spi);//FS_LOCK ÄÜ¹»¿ØÖÆÍ¬Ê±´ò¿ªÎÄ¼şµÄ¸öÊı 3
      // ¹Ø±ÕÎÄ¼şÏµÍ³ FIL file_spi,file_usb;
      f_close(&file);
			f_mount(NULL,FS_VOLUME_USB, 0);
GUI_ALLOC_Free(hMem);//
      return 0;
}
// ***********************************************
// ¢***********½ØÆÁµ÷ÓÃÒÔÏÂº¯Êı********************
void Print_Screen(void)
{	uint8_t buf[50];
//	uint8_t Pic_Name=0;


	if ((GPIOB->IDR & GPIO_Pin_1) != 0) //K1
		return;
	beep();
	while(1)
  {
		if ((GPIOB->IDR & GPIO_Pin_1) != 0) //K1
		   break;
  }
	if(output_screen())
	{
		beep();beep();
	}
	beep();
	Pic_Name++;


}*/