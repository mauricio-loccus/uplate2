

#ifndef _FAT_H
#define _FAT_H
enum
{
    NOT_READ_FILE=0,
    READ_FILE
};
#define SPI_OK   0
#define SPI_ERR  1

#define  DIR_USB_PROGRAM_INPUT   "Protocols"  //"Items"   //"imput"//fmc161013
#define  DIR_USB_PROGRAM_OUTPUT  "Protocols"  // "Items"   //"imput"//fmc161013
#define  DIR_USB_PROGRAM_UPDATE  "update"   //"imput"
#define  DIR_USB_REPORT          "report"   //"imput"
//#define  UPDATE_PROGRAM_NAME     "output.bin"






//char output_one_program(char cent);
void check_usb_connect(void);


extern int usb_program_number,spi_program_number;


void Create_USB_Dir(char *_ucVolume);

//¿ª»ú±³¾°Í¼Æ¬
unsigned char ReadFile_background(char *ad,unsigned char picture_flag);//´ÓNand¶ÁÈ¡±³¾°Í¼Æ¬
unsigned char ReadFileFromUSB_BG(char *ad,unsigned char picture_flag); //´ÓUSB¶ÁÈ¡±³¾°Í¼Æ¬
unsigned char WriteFile_background(char *_ucVolume,unsigned long len,unsigned char picture_flag);//Ğ´±³¾°Í¼Æ¬
unsigned char CopyStartupPicture(void);     //¸´ÖÆ±³¾°Í¼Æ¬


void Usb_Init(void);   //³õÊ¹»¯USB
void Usb_check(void);  //¼ì²âUSB
void check_usb_connect(void);//¼ì²âUSBÁ¬½Ó×´Ì¬

int GenerateNewFile(void);//²úÉúĞÂÎÄ¼ş
unsigned char  SaveProgram(void);     //±£´æ³ÌĞò(²»ÓÃ)
unsigned char DeleteOneFile(char name[]);//(²»ÓÃ)

unsigned char UsbInputFileData(void);      //±»SpiInputFileDataµ÷ÓÃ
unsigned char UsbOpenOneFile(void);       //µ¼ÈëÎÄ¼ş.erf
unsigned char UsbOpenFile_read_data(void);//µ¼ÈëÒ»¸ö±ê×¼ÖµÎÄ¼ş.TXT

unsigned char UsbReadAllProgramHead(void); //´ÓUÅÌ¶ÁÈ¡ËùÓĞ³ÌĞòÍ·
unsigned char SpiGenerateBoardFile(void);  //½«±¾°åµÄĞÅÏ¢´æÈëSPIFLASH
unsigned char ExportAbsCalibrationFile(char *name_str);//µ¼³öĞ£×¼±¨¸æ
unsigned char ExportOneFile(void);         //µ¼³öerfÎÄ¼ş
unsigned char ExportOneProgram(void);      //¼ì²â±¨¸æµ¼³öµ½.csv
//unsigned char ReadAllProgramHead(void);  //¶ÁÈ¡ËùÓĞ³ÌĞòÍ·

//±£´æÏµÍ³µ÷ÖÃ²ÎÊı
unsigned char SpiSaveAbs(void);            //±£´æĞ£×¼Îü¹â¶È
unsigned char SpiReadAbs(void);
unsigned char SpiSaveAbs2(void);            //ä¿å­˜2.5mmæ¿æ ¡å‡†å‚æ•°ã€æ ¡å‡†æ¿é€‰æ‹©é¡¹
unsigned char SpiReadAbs2(void);            //è¯»å–2.5mmæ¿æ ¡å‡†å‚æ•°ã€æ ¡å‡†æ¿é€‰æ‹©é¡¹
unsigned char SpiSavePN(void);              //±£´æPNºÅ
unsigned char SpiReadPN(void);              //¶ÁÈ¡PNºÅ
void  GenerateCaliData(void);
unsigned char FindUserData(void);          //ÅÑ¶ÏÓÃ»§Êı¾İÊÇ·ñÕıÈ·
unsigned char SpiSaveSystemPra(void);      //±£´æÏµÍ³²ÎÊı
unsigned char SpiReadSystemPra(void);
void FileFormat_spi(void);
//lgj161013 start
unsigned char Read_send_bin_File(void);
unsigned char Read_write_bin_File(void);
//lgj161013 end
//static void CreateNewFile(char *_ucVolume)






void WriteFileTest(void);
extern char *update103_buf;
#endif

