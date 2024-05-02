

#ifndef _STR_CONVERT_H
#define _STR_CONVERT_H

#define REMAIN_RUNTIME_MAX   (3600*100-1)

enum { TEMP_HIDE_UNIT = 0, TEMP_SHOW_UNIT };
extern char StrTemp[];
extern char ConvertStr[];
extern char CsvConvertStr[];
extern char PrintConvertStr[];

//char *ConvertDateTime(char *val,short year,unsigned char mon,unsigned char day,unsigned char hour,unsigned char min,unsigned char str_format);
enum { CH_TIME_24HOUR=0,EN_TIME_24HOUR};

char *SetTempConvertStr(char *val,unsigned char t,unsigned char unit_flag);
char *PraTempConvertStr(char *val,unsigned short t,unsigned char unit_flag);
char *ConvertDateTime(char *val,short year,unsigned char mon,unsigned char day,unsigned char hour,unsigned char min,unsigned char str_format);


char *ConvertZeroAdjust(char *val,unsigned int temp);
char *ConvertRemainRunTime(char *val,unsigned long time);
char *OneByteConvertStr(char *val,unsigned char t);
char *SetTempConvertStr(char *val,unsigned char t,unsigned char unit_flag);
char *PraTempConvertStr(char *val,unsigned short t,unsigned char unit_flag);
char *MotionConvertStr(char *val,unsigned char t);
char *AdvanceMixConvertStr(char *val,unsigned short t);
char *ZeroOffsetConvertStr(char *val,unsigned short t);
char *ZeroAdjustConvertStr(char *val,unsigned char t);  //0.00~0.99
char *PraDisConvertStr(char *val,unsigned short t);
char *AdvanceHoleSitConvertStr(char *val,unsigned short t);

char *OneNumConvertStr(char *val, unsigned char t);
char *TwoNumConvertStr(char *val, unsigned char t);
char *TwoNum2ConvertStr(char *val, unsigned char t);
char *FilterConvertStr(char *val, unsigned short t);
char *ShakeTimeConvertStr(char *val, unsigned long time);

char *WellNumConvertStr(char *val, unsigned char t);
char *floatConvertE(char *str, float t);
char *EConvert(char *val);
//void FloatConvertChar(float a,unsigned char *px);
//void CharConvertFloat(unsigned char *px,float a);
//char *EConvert1(char *val,unsigned char count);
//char *EConvert2(char *val,unsigned char count);
#endif
