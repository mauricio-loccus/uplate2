#include "StrConvert.h"
#include "bsp.h"
#include  "includes.h"
#include  "MainTask.h"
//#include "bsp_fmc_sdram.h"


#define STR_LENGTH  1000
char StrTemp[STR_LENGTH] __attribute__((at(SDRAM_TEMP_STR_BUF)));
char ConvertStr[STR_LENGTH] __attribute__((at(SDRAM_CONVERT_STR_BUF)));
char CsvConvertStr[250000]  __attribute__((at(SDRAM_EXPORT_BUF)));
char PrintConvertStr[4096]  __attribute__((at(SDRAM_SPI2_PAGE_BUF)));

char *ConvertDateTime(char *val,short year,unsigned char mon,unsigned char day,unsigned char hour,unsigned char min,unsigned char str_format)
{
    char *p;
    p=val;
if(SystemPrameter.SystemLanguage == LANGUAGE_CH)
{
if(str_format==CH_TIME_24HOUR)  //????
    {		
        *val++=day/10+'0';
        *val++=day%10+'0';
			  *val++='-';
				*val++=mon/10+'0';
        *val++=mon%10+'0';
        *val++='-';
        *val++='2';
        *val++='0';
        *val++=year%100/10+'0';
        *val++=year%10+'0';

    }
    else
    {
        *val++=day/10+'0';
        *val++=day%10+'0';
			  *val++='-';
				*val++=mon/10+'0';
        *val++=mon%10+'0';
        *val++='-';
        *val++='2';
        *val++='0';
        *val++=year%100/10+'0';
        *val++=year%10+'0';
    }



}
else
{
    if(str_format==CH_TIME_24HOUR)  //????
    {		
        *val++='2';
        *val++='0';
        *val++=year%100/10+'0';
        *val++=year%10+'0';
        *val++='-';
        *val++=mon/10+'0';
        *val++=mon%10+'0';
        *val++='-';
        *val++=day/10+'0';
        *val++=day%10+'0';

    }
    else
    {

        *val++=mon/10+'0';
        *val++=mon%10+'0';
        *val++='-';
        *val++=day/10+'0';
        *val++=day%10+'0';
        *val++='-';
        *val++='2';
        *val++='0';
        *val++=year%100/10+'0';
        *val++=year%10+'0';
    }
	}
    *val++=' ';

    *val++=hour/10+'0';
    *val++=hour%10+'0';
    *val++=':';
    *val++=min/10+'0';
    *val++=min%10+'0';


    *val++=0;
    return p;
}




//char *ConvertUVLightTime(char *val,unsigned long time)
char *ShakeTimeConvertStr(char *val, unsigned long time)
{
    char *p;
    unsigned char h,m,s;
    p=val;

    h=time/3600;
    m=time%3600/60;
    s=time%60;


    *val++=h/10+'0';
    *val++=h%10+'0';
    *val++=0x20;
    *val++=':';
    *val++=0x20;
    *val++=m/10+'0';
    *val++=m%10+'0';
    *val++=0x20;
    *val++=':';
    *val++=0x20;
    *val++=s/10+'0';
    *val++=s%10+'0';

    *val++=0;
    return p;
}


char *WellNumConvertStr(char *val, unsigned char t)
{
    char *p;

    p = val;


    *val++ = 'A' + t / 12;
    t=t%12+1;
    if(t>=10)
    {
        *val++ = t / 10 + '0';
    }
    *val++=t%10 +'0';

    *val++ = 0;
    return p;
}




char *ConvertZeroAdjust(char *val,unsigned int temp)
{
    char *p;
    unsigned short h;
    unsigned char l;
    p=val;

    h=temp/100;
    l=temp%100;

    if(h>=100)
    {
        *val++=h/100+'0';
    }
    if(h>=10)
    {
        *val++=h%100/10+'0';
    }
    *val++=h%10+'0';
    *val++='.';
    *val++=l/10+'0';
    *val++=l%10+'0';

    *val++=0;
    return p;
}


char *ConvertRemainRunTime(char *val,unsigned long time)
{
    char *p;
    unsigned char h,m,s;
    p=val;
    if(time>REMAIN_RUNTIME_MAX)
    {
        time=REMAIN_RUNTIME_MAX;
    }
    h=time/3600;
    m=time%3600/60;
    s=time%60;


    *val++=h/10+'0';
    *val++=h%10+'0';
    *val++=':';
    *val++=m/10+'0';
    *val++=m%10+'0';
    *val++=':';
    *val++=s/10+'0';
    *val++=s%10+'0';

    *val++=0;
    return p;
}

char *OneByteConvertStr(char *val,unsigned char t)
{
    char *p;
    p=val;

    if(t>=100)*val++=t/100+'0';
    if(t>=10)*val++=t%100/10+'0';
    *val++=t%10+'0';


    *val++=0;
    return p;
}

//鍑芥暟鍚峜har *SetTempConvertStr(char *val,unsigned short t,unsigned char unit_flag)
//鍔熻兘璁剧疆娓╁害杞寲涓哄瓧绗︿覆(娓╁害鑼冨洿:0-120)
//杈撳叆鍊? 1)t:娓╁害鍊?  unit_flag:1琛ㄧず鏄剧ず娓╁害绗﹀彿,0琛ㄧず涓嶆樉绀烘俯搴︾鍙?
//杩斿洖鍊?瀛楃涓叉寚閽? char *val涓鸿繑鍥炵殑瀛楃涓叉寚閽?
char *SetTempConvertStr(char *val,unsigned char t,unsigned char unit_flag)
{
    char *p;
    p=val;

    if(t>=100)*val++=t/100+'0';
    if(t>=10)*val++=t%100/10+'0';
    *val++=t%10+'0';
    if(unit_flag)
    {
        //	 *val++='掳';
        *val++='C';
    }


    *val++=0;
    return p;
}
//鍑芥暟鍚峜har *PraTempConvertStr(char *val,unsigned short t,unsigned char unit_flag)
//鍔熻兘瀹為檯娓╁害杞寲涓哄瓧绗︿覆(娓╁害鑼冨洿:0-150.0)
//杈撳叆鍊? 1)t:娓╁害鍊?  unit_flag:1琛ㄧず鏄剧ず娓╁害绗﹀彿,0琛ㄧず涓嶆樉绀烘俯搴︾鍙?
//杩斿洖鍊?瀛楃涓叉寚閽? char *val涓鸿繑鍥炵殑瀛楃涓叉寚閽?
char *PraTempConvertStr(char *val,unsigned short t,unsigned char unit_flag)
{
    char *p;
    p=val;

    if(t>=1000)*val++=t/1000+'0';
    if(t>=100)*val++=t%1000/100+'0';
    *val++=t%100/10+'0';
    *val++='.';
    *val++=t%10+'0';
    if(unit_flag)
    {
        // *val++='掳';
        *val++='C';
    }

    *val++=0;
    return p;
}
//鐢垫満闆剁偣鍋忕Щ杞寲涓哄瓧绗︿覆
char *ZeroOffsetConvertStr(char *val,unsigned short t)
{
    char *p;
    p=val;

    if(t>=1000)*val++=t/1000+'0';
    if(t>=100)*val++=t%1000/100+'0';
    *val++='.';
    *val++=t%100/10+'0';
    *val++=t%10+'0';


    *val++=0;
    return p;
}

//鐢垫満闆剁偣鍋忕Щ杞寲涓哄瓧绗︿覆
char *ZeroAdjustConvertStr(char *val,unsigned char t)
{
    char *p;
    p=val;


    *val++=t/100+'0';
    *val++='.';
    *val++=t%100/10+'0';
    *val++=t%10+'0';


    *val++=0;
    return p;
}
//鍑芥暟鍚?char *PraDisConvertStr(char *val,unsigned short t)
//鍔熻兘:瀹為檯琛岀▼杞寲涓哄瓧绗︿覆
//杈撳叆鍊? 1)t:瀹為檯琛岀▼鍊?
//杩斿洖鍊?瀛楃涓叉寚閽? char *val涓鸿繑鍥炵殑瀛楃涓叉寚閽?
char *PraDisConvertStr(char *val,unsigned short t)
{
    char *p;
    unsigned char h,l;
    p=val;

    h=t/100;
    l=t%100;



    if(h>=100)*val++=h/100+'0';
    if(h>=10)*val++=h%100/10+'0';
    *val++=h%10+'0';
    *val++='.';
    *val++=l/10+'0';
    *val++=l%10+'0';


    *val++=0;
    return p;
}

char *AdvanceMixConvertStr(char *val,unsigned short t)
{
    char *p;
    unsigned char h,l;
    p=val;

    h=t/100;
    l=t%100;


    if(h>=10)*val++=h/10+'0';
    *val++=h%10+'0';
    /* *val++='.';
       *val++=l/10+'0';
    *val++=l%10+'0';*/ //fmc170220 涓嶈灏忔暟鐐?


    *val++=0;
    return p;
}
char *MotionConvertStr(char *val,unsigned char t)
{
    char *p;

    p=val;


    if(t>=100)*val++=t/100+'0';
    if(t>=10)*val++=t%100/10+'0';
    *val++=t%10+'0';


    *val++=0;
    return p;
}

char *OneNumConvertStr(char *val, unsigned char t)
{
    char *p;

    p = val;

    if (t >9)t = 9;

    *val++ = t % 10 + '0';

    *val++ = 0;
    return p;
}
char *TwoNumConvertStr(char *val, unsigned char t)
{
    char *p;

    p = val;

    if (t >99)t = 99;

    if (t >= 10)*val++ = t / 10 + '0';
    *val++ = t % 10 + '0';

    *val++ = 0;
    return p;
}
char *TwoNum2ConvertStr(char *val, unsigned char t)
{
    char *p;

    p = val;

    if (t >99)t = 99;

    *val++ = t / 10 + '0';
    *val++ = t % 10 + '0';

    *val++ = 0;
    return p;
}


char *FilterConvertStr(char *val, unsigned short t)
{
    char *p;

    p = val;

    if (t > 999)t = 999;

    if (t >= 100)*val++ = t / 100 + '0';
    if (t >= 10)*val++ = t % 100 / 10 + '0';
    *val++ = t % 10 + '0';

    *val++ = 0;
    return p;
}
/*
char *DoubleConvertE(char *str, float t)
{
	char *p;
   char str2[10];
	unsigned char n;
	p = str;

//	if (t > 999)t = 999;
  		 sprintf(str,"%d",t);
	     n=sizeof(str);
	     t=t/pow(10,n-2);
	     sprintf(str,"%.2f",t);
	     sprintf(str2,"%02d",n-2);
	     strcat(str,"e+");
	     strcat(str,str2);

	return p;
}*/




//char *ConvertUVLightTime(char *val,unsigned long time)
/*
char *EConvert2(char *val,unsigned char count)
{
   char *p;

	 p=val;

	 val[count-3]=val[count-2];
	 val[count-2]=val[count-1];
     val[count-1]=0;
     return p;
}*/


unsigned char cstrlen(char *str)
{
    unsigned char i;
    for(i=0; str[i]!='\0'; i++)  ;
    return i;
}


char *EConvert(char *val)
{
    char *p;
    unsigned char count;

    p=val;
    count =cstrlen(p) ;

    val[count-2]=val[count-1];
    val[count-1]=0;
    // val[count-1]=0;
    return p;
}
/*
char *EConvertSign(char *val)
{
   char *p;
   unsigned char count;

	 p=val;
	 count =cstrlen(p) ;

	 val[count-2]=val[count-1];
   val[count-1]=0;
     return p;
}
*/
/*
void FloatConvertChar(float a,unsigned char *px)
{
   unsigned char i;
	 void *pf;

	 pf=&a;
	 for(i=0;i<4;i++)
	 {
     *(px+i)=*((unsigned char *)pf+i);
	 }
}

//px指针指向数组[4]
void CharConvertFloat(unsigned char *px,float a)
{
	  unsigned char i;
    void *pf;
    pf=&a;
    for(i=0;i<4;i++)
    {
      *((unsigned char *)pf+i)=*(px+i);
    }
}*/



