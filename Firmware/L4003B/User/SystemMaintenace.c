//程序已自检-导入，更新，校准，复位未检,数据存贮未做,gSystem.PasswordOpenFlag=0;取消
#include "MainTask.h"
#include  "includes.h"
#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>



const char STR_MAINTENANCE_TITLE[LANGUAGE_TYPES][15] = {"Maintenance", "Ferramentas"};
const char STR_MAINTENANCE_PLATE[LANGUAGE_TYPES][10] = {"Eject", "Ejetar"};
const char STR_MAINTENANCE_INTENSITY_RAW[LANGUAGE_TYPES][10] = {"Raw", "Raw"};
const char STR_MAINTENANCE_INTENSITY_INTENSITY[LANGUAGE_TYPES][15] = {"Intensity", "Intens."};
const char STR_MAINTENANCE_ORIGIN[LANGUAGE_TYPES][10] = {"Origin", "Origem"};
const char STR_PASSWORD[LANGUAGE_TYPES][15] = {"Password", "Password"};
const char STR_LOCK[LANGUAGE_TYPES][15] = {"Lock", "Bloquear"};
const char STR_LOCK_STATUS[LANGUAGE_TYPES][DOOR_STATUS_MAX][15] =
{   {"Enable", "Disable"},
    {"Habilitar", "Desabilit."}
};


const char DOOR_STATUS[LANGUAGE_TYPES][DOOR_STATUS_MAX][10] =
{   {"Off", "On"},
    {"Off", "On"}
};


const char RAW_INTENSITY_STATUS[LANGUAGE_TYPES][RAW_INTENSITY_STATUS_MAX][10] =
{   {"Off", "On"},
    {"Off", "On"}
};


const char STR_MODE_2[LANGUAGE_TYPES][10] = {"Mode", "Modo"};

//modify start lugj 180910
const char CALI_MODE[LANGUAGE_TYPES][2][10] =
{   {"Factory", "Customer"},
    {"Fábrica", "Cliente"}
};
//modify end lugj 180910


const BUTTON_DATA _aButtonMaintenace[] =
{
    //导入图片
    { TOOLS0_BUTTON_POSX(4), TOOLS0_BUTTON_POSY, TOOLS0_BUTTON_WIDTH, TOOLS0_BUTTON_HEIGHT, "Import", "Importar" },

    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(0), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Reset", "Reset" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(1), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Upgrade", "Upgrade" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(2), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Calibration", "Calibração" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(3), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Ok", "Ok" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(4), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Back", "Voltar" },
};

//ExpEnable的值定义
enum
{
    EXP_DOOR=1,
    EXP_RAW_INTENSITY,
    EXP_ORGIN,
    EXP_PASSWORD,  //密码
	  EXP_CALI_MODE, //校准模式
	  EXP_LOCK,
};
static unsigned char ExpEnable;



unsigned short m_Zero;
unsigned char m_bRawIntensity;
unsigned char m_bDoorOpen;

static unsigned char m_CaliMode;  //modify lugj 20180910
static unsigned char m_LockStatus;//锁状态 0=enable 1=disable
//SYSTEM_TIME  SystemTimePraBack;

WM_HWIN SystemMaintenaceWin = NULL;


//Modify start lugj 20180910 校准模式扩展项
void DisplayCaliModeExpand(void)
{
    unsigned char i;
    short start_x, start_y, wide, high;
    GUI_RECT rect;

    start_x = CALI_MODE_R_START_X ;
    start_y = CALI_MODE_R_START_Y - TITLESBAR_HEIGHT;
    wide = CALI_MODE_SEL_WIDTH1;
    high = 40;
    //GUI_DrawBitmap(&bmExpMenuRight_180_46, FILTER_1_R_START_X, FILTER_1_R_START_Y - TITLESBAR_HEIGHT);//bmExpMenuRight_180_46

    GUI_SetColor(COLOR_EXP_PICTURE_FRAME);
    GUI_DrawLine(start_x, start_y,start_x+160,start_y);
    GUI_DrawLine(start_x, start_y+45,start_x+160,start_y+45);
    GUI_SetColor(COLOR_EXP_PICTURE);
    GUI_FillRect(start_x, start_y,start_x+160,start_y+45);
    GUI_DrawBitmap(&bmExpMenuRight_20_46, start_x+160, start_y);

    start_x +=3;
    start_y += 3;
    for (i = 0; i<2; i++)
    {

        //填充选中的底色
        GUI_SetColor(COLOR_SHAKE_BK);
        strcpy(ConvertStr,CALI_MODE[SystemPrameter.SystemLanguage][i] );//

        //填充选中的文字-白色
        if(m_CaliMode==i)
            //	if (((SystemPrameterBack.PrintHeaderEnable == 0) && (i == 0)) || ((SystemPrameterBack.PrintHeaderEnable) && (i == 1)))
        {
            GUI_FillRect(start_x, start_y, start_x + wide, start_y + high);
            GUI_SetColor(COLOR_SHAKE_TXT);
        }

        rect.x0 = start_x;
        rect.y0 = start_y - 1;
        rect.x1 = start_x + wide;
        rect.y1 = start_y + high;

        start_x += wide;
        wide =CALI_MODE_SEL_WIDTH2;

        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    }
}
//Modify end lugj 20180910



//Modify start lugj 20180910 校准模式扩展项
void DisplayLockExpand(void)
{
    unsigned char i;
    short start_x, start_y, wide, high;
    GUI_RECT rect;

    start_x = LOCK_R_START_X ;
    start_y = LOCK_R_START_Y - TITLESBAR_HEIGHT;
    wide = CALI_MODE_SEL_WIDTH1;
    high = 40;
    //GUI_DrawBitmap(&bmExpMenuRight_180_46, FILTER_1_R_START_X, FILTER_1_R_START_Y - TITLESBAR_HEIGHT);//bmExpMenuRight_180_46

    GUI_SetColor(COLOR_EXP_PICTURE_FRAME);
    GUI_DrawLine(start_x, start_y,start_x+160,start_y);
    GUI_DrawLine(start_x, start_y+45,start_x+160,start_y+45);
    GUI_SetColor(COLOR_EXP_PICTURE);
    GUI_FillRect(start_x, start_y,start_x+160,start_y+45);
    GUI_DrawBitmap(&bmExpMenuRight_20_46, start_x+160, start_y);

    start_x +=3;
    start_y += 3;
    for (i = 0; i<2; i++)
    {

        //填充选中的底色
        GUI_SetColor(COLOR_SHAKE_BK);
        strcpy(ConvertStr,STR_LOCK_STATUS[SystemPrameter.SystemLanguage][i] );//

        //填充选中的文字-白色
        if(m_LockStatus==i)
            //	if (((SystemPrameterBack.PrintHeaderEnable == 0) && (i == 0)) || ((SystemPrameterBack.PrintHeaderEnable) && (i == 1)))
        {
            GUI_FillRect(start_x, start_y, start_x + wide, start_y + high);
            GUI_SetColor(COLOR_SHAKE_TXT);
        }

        rect.x0 = start_x;
        rect.y0 = start_y - 1;
        rect.x1 = start_x + wide;
        rect.y1 = start_y + high;

        start_x += wide;
        wide =CALI_MODE_SEL_WIDTH2;

        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    }
}
//Modify end lugj 20180910



void DisplayDoorExpand(void)
{
    unsigned char i;
    short start_x, start_y, wide, high;
    GUI_RECT rect;

    start_x = FILTER_1_R_START_X ;
    start_y = FILTER_1_R_START_Y - TITLESBAR_HEIGHT;
    wide = PLATE_SEL_WIDTH;
    high = 40;
    //GUI_DrawBitmap(&bmExpMenuRight_180_46, FILTER_1_R_START_X, FILTER_1_R_START_Y - TITLESBAR_HEIGHT);//bmExpMenuRight_180_46

    GUI_SetColor(COLOR_EXP_PICTURE_FRAME);
    GUI_DrawLine(start_x, start_y,start_x+160,start_y);
    GUI_DrawLine(start_x, start_y+45,start_x+160,start_y+45);
    GUI_SetColor(COLOR_EXP_PICTURE);
    GUI_FillRect(start_x, start_y,start_x+160,start_y+45);
    GUI_DrawBitmap(&bmExpMenuRight_20_46, start_x+160, start_y);

    start_x +=3;
    start_y += 3;
    for (i = 0; i<2; i++)
    {

        //填充选中的底色
        GUI_SetColor(COLOR_SHAKE_BK);
        strcpy(ConvertStr,DOOR_STATUS[SystemPrameter.SystemLanguage][i] );//

        //填充选中的文字-白色
        if(m_bDoorOpen==i)
            //	if (((SystemPrameterBack.PrintHeaderEnable == 0) && (i == 0)) || ((SystemPrameterBack.PrintHeaderEnable) && (i == 1)))
        {
            GUI_FillRect(start_x, start_y, start_x + wide, start_y + high);
            GUI_SetColor(COLOR_SHAKE_TXT);
        }

        rect.x0 = start_x;
        rect.y0 = start_y - 1;
        rect.x1 = start_x + wide;
        rect.y1 = start_y + high;

        start_x += wide;
        wide =PLATE_SEL_WIDTH;

        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    }
}




void DisplayRawIntensityExpand(void)
{
    unsigned char i;
    //char str[10];
    GUI_RECT rect;

    int start_x, start_y, wide, high;

    start_x = FILTER_2_R_START_X ;
    start_y = FILTER_2_R_START_Y - TITLESBAR_HEIGHT;
    wide = DOOR_SEL_WIDTH;//INTER_SEL_WIDTH;
    high = 40;
//	GUI_DrawBitmap(&bmExpMenuRight_180_46, FILTER_2_R_START_X, FILTER_2_R_START_Y - TITLESBAR_HEIGHT);
    GUI_SetColor(COLOR_EXP_PICTURE_FRAME);
    GUI_DrawLine(start_x, start_y,start_x+160,start_y);
    GUI_DrawLine(start_x, start_y+45,start_x+160,start_y+45);
    GUI_SetColor(COLOR_EXP_PICTURE);
    GUI_FillRect(start_x, start_y,start_x+160,start_y+45);
    GUI_DrawBitmap(&bmExpMenuRight_20_46, start_x+160, start_y);

    start_x +=3;
    start_y += 3;

    for (i = 0; i<2; i++)
    {
        //填充选中的底色
        GUI_SetColor(COLOR_SHAKE_BK);
        strcpy(ConvertStr,RAW_INTENSITY_STATUS[SystemPrameter.SystemLanguage][i] );//

        //填充选中的文字-白色
        if(m_bRawIntensity==i)
        {
            GUI_FillRect(start_x, start_y, start_x + wide, start_y + high);
            GUI_SetColor(COLOR_SHAKE_TXT);
        }

        rect.x0 = start_x;
        rect.y0 = start_y - 1;
        rect.x1 = start_x + wide;
        rect.y1 = start_y + high;

        start_x += wide;
        wide =DOOR_SEL_WIDTH;// INTER_SEL_WIDTH;

        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    }
}



void _cbMaintenace(WM_MESSAGE * pMsg)
{
    //char str[10];
    WM_HWIN hWin = pMsg->hWin;
//	WM_HWIN hWinFocus;
    BUTTON_Handle hbutton;
    unsigned char i;
    int        xSize;
    int        ySize;
    short NCode, Id;
    GUI_RECT rect;
    //	int  day_max;
    //hWinFocus = WM_GetFocussedWindow();
    //IdWinFocus = WM_GetId(hWinFocus);

    switch (pMsg->MsgId)
    {
    case WM_CREATE:
    {
        for (i = 0; i < GUI_COUNTOF(_aButtonMaintenace); i++)
        {
            hbutton = BUTTON_CreateEx(_aButtonMaintenace[i].xPos, _aButtonMaintenace[i].yPos, _aButtonMaintenace[i].xSize, _aButtonMaintenace[i].ySize,
                                      hWin, WM_CF_SHOW, 0, ID_MAINTENACE_BUTTON + i);
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG);
                BUTTON_SetText(hbutton, _aButtonMaintenace[i].acLabelEn);
            }
            else
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG_CH);
                BUTTON_SetText(hbutton, _aButtonMaintenace[i].acLabelCh);
            }
            //if(i==1) //隐藏Reset键
            // {
            //  WM_HideWindow(hbutton);
            // }
            if( (gSystem.PasswordOpenFlag==0)&&(i<=3) )
            {
                //BUTTON_SetState(hbutton,BUTTON_CI_DISABLED);
                WM_DisableWindow(hbutton);
            }
            else
            {
                WM_EnableWindow(hbutton);
                //BUTTON_SetState(hbutton,BUTTON_CI_UNPRESSED);
            }
            BUTTON_SetTextColor(hbutton, BUTTON_CI_DISABLED, GUI_GRAY);
            //	WM_DisableWindow(KeyButton[30]);
            // WM_DisableWindow(KeyButton[32]);
            BUTTON_SetTextAlign(hbutton, GUI_TA_HCENTER | GUI_TA_VCENTER);
            BUTTON_SetFocussable(hbutton, 0);
        }
        break;
    }
    //删除按钮
    case WM_DELETE:

        //WM_ShowWindow(ButtonZero[i]);
        break;
        //绘制背景
    case WM_PAINT:
        xSize = WM_GetWindowSizeX(hWin);
        ySize = WM_GetWindowSizeY(hWin);
        //上方第一行
        GUI_SetColor(COLOR_TITLEBAR);
        GUI_FillRect(0, 0, xSize - 1, CONTENTBAR_TITLE_HEIGHT - 1);
        //左方内容栏
        GUI_SetColor(COLOR_CONTENTBAR);
        GUI_FillRect(0, CONTENTBAR_CONTENT_POSY, CONTENTBAR_CONTENT_WIDTH - 1, ySize - 1);
        //右侧工具栏
        GUI_SetColor(COLOR_TOOLSBAR);
        GUI_FillRect(CONTENTBAR_CONTENT_WIDTH, CONTENTBAR_CONTENT_POSY, xSize - 1, ySize - 1);
				GUI_SetColor(GUI_GRAY);
				GUI_DrawLine(0,0, xSize - 1,0);
				GUI_DrawLine(0,CONTENTBAR_TITLE_HEIGHT - 1, xSize - 1,CONTENTBAR_TITLE_HEIGHT - 1);

        GUI_DrawBitmap(&bmMenuLeft_101_46, FILTER_1_START_X, FILTER_1_START_Y - TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmMenuLeft_101_46, FILTER_2_START_X, FILTER_2_START_Y - TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmMenuLeft_101_46, MODE_START_X, MODE_START_Y - TITLESBAR_HEIGHT);

        GUI_DrawBitmap(&bmMenuLeft_101_46, PASSWORD_START_X, PASSWORD_START_Y - TITLESBAR_HEIGHT);//////////CALCULATION_PARA_START_X
        GUI_DrawBitmap(&bmMenuLeft_101_46, CALI_MODE_START_X, CALI_MODE_START_Y - TITLESBAR_HEIGHT); 
        
#ifndef SOFTWARE_DN

        GUI_DrawBitmap(&bmMenuLeft_101_46, LOCK_START_X, LOCK_START_Y - TITLESBAR_HEIGHT); //Modify lugj 20180910
        
#endif				
				
        //GUI_DrawBitmap(&bmMenuRight_120_46, FILTER_1_R_START_X, FILTER_1_R_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(FILTER_1_R_START_X, FILTER_1_R_START_Y- TITLESBAR_HEIGHT,FILTER_1_R_START_X+100, FILTER_1_R_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, FILTER_1_R_START_X+100, FILTER_1_R_START_Y- TITLESBAR_HEIGHT);

        //GUI_DrawBitmap(&bmMenuRight_120_46, FILTER_2_R_START_X, FILTER_2_R_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(FILTER_2_R_START_X, FILTER_2_R_START_Y- TITLESBAR_HEIGHT,FILTER_2_R_START_X+100, FILTER_2_R_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, FILTER_2_R_START_X+100, FILTER_2_R_START_Y- TITLESBAR_HEIGHT);

        //GUI_DrawBitmap(&bmMenuRight_120_46, MODE_R_START_X, MODE_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(MODE_R_START_X, MODE_START_Y- TITLESBAR_HEIGHT,MODE_R_START_X+100, MODE_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, MODE_R_START_X+100, MODE_START_Y- TITLESBAR_HEIGHT);

        //GUI_DrawBitmap(&bmMenuRight_120_46, PASSWORD_R_START_X, PASSWORD_R_START_Y - TITLESBAR_HEIGHT);/////////////
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(PASSWORD_R_START_X, PASSWORD_R_START_Y- TITLESBAR_HEIGHT,PASSWORD_R_START_X+100, PASSWORD_R_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, PASSWORD_R_START_X+100, PASSWORD_R_START_Y- TITLESBAR_HEIGHT);

        //Modify start lugj 20180910  模式右侧项
         //GUI_DrawBitmap(&bmMenuRight_120_46, PASSWORD_R_START_X, PASSWORD_R_START_Y - TITLESBAR_HEIGHT);/////////////
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(CALI_MODE_R_START_X, CALI_MODE_R_START_Y- TITLESBAR_HEIGHT,CALI_MODE_R_END_X-20, CALI_MODE_R_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, CALI_MODE_R_END_X-20, CALI_MODE_R_START_Y- TITLESBAR_HEIGHT);
				//Modify end lugj 20180910
				
				
#ifndef SOFTWARE_DN
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(LOCK_R_START_X, LOCK_R_START_Y- TITLESBAR_HEIGHT,LOCK_R_END_X-20, LOCK_R_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, LOCK_R_END_X-20, LOCK_R_START_Y- TITLESBAR_HEIGHT);
#endif

        GUI_SetTextMode(GUI_TM_TRANS);

        GUI_SetColor(COLOR_PAINT_TXT);

        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            GUI_SetFont(GUI_FONT_BIG);
        }
        else
        {
            GUI_SetFont(GUI_FONT_BIG_CH);
        }

        GUI_DispStringAt(STR_MAINTENANCE_TITLE[SystemPrameter.SystemLanguage], CONTENTBAR_CAPTION_POSX, CONTENTBAR_CAPTION_POSY);//"Measurement parameters"

        rect.x0 = FILTER_1_START_X+20;
        rect.y0 = FILTER_1_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = DATE_SET_R_START_X;
        rect.y1 = DATE_SET_R_END_Y - TITLESBAR_HEIGHT;
        //strcpy(ConvertStr, "Filter 1");
        GUI_DispStringInRect(STR_MAINTENANCE_PLATE[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Filter 1"


        rect.x0 = FILTER_1_R_START_X + 10;
        rect.y0 = FILTER_1_R_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = DATE_SET_R_END_X;
        rect.y1 = DATE_SET_R_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(DOOR_STATUS[SystemPrameter.SystemLanguage][m_bDoorOpen], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date


        if(gSystem.PasswordOpenFlag==0)
        {
            GUI_SetColor(COLOR_PAINT_TXT_DIS);
        }
        else
        {
            GUI_SetColor(COLOR_PAINT_TXT);
        }
        rect.x0 = FILTER_2_START_X+20;
        rect.y0 = FILTER_2_START_Y - TITLESBAR_HEIGHT+5;
        rect.x1 = FILTER_2_END_X;
        rect.y1= rect.y0 +15;
        GUI_DispStringInRect(STR_MAINTENANCE_INTENSITY_RAW[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"原始

        rect.y0=rect.y1;
        rect.y1 = FILTER_2_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(STR_MAINTENANCE_INTENSITY_INTENSITY[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//光强

        rect.x0 = MODE_START_X+20;
        rect.y0 = MODE_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = MODE_END_X;
        rect.y1=  MODE_END_Y- TITLESBAR_HEIGHT;
        GUI_DispStringInRect(STR_MAINTENANCE_ORIGIN[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//零点

        rect.x0 = FILTER_2_R_START_X + 10;
        rect.y0 = FILTER_2_R_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = TIME_SET_R_END_X;
        rect.y1 = FILTER_2_R_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(RAW_INTENSITY_STATUS[SystemPrameter.SystemLanguage][m_bRawIntensity], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date

//Lock
#ifndef SOFTWARE_DN

        rect.x0 = LOCK_START_X+20;
        rect.y0 = LOCK_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = LOCK_END_X;
        rect.y1=  LOCK_END_Y- TITLESBAR_HEIGHT;
        GUI_DispStringInRect(STR_LOCK[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Lock

        rect.x0 = LOCK_R_START_X + 10;
        rect.y0 = LOCK_R_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = LOCK_R_END_X;
        rect.y1 = LOCK_R_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(STR_LOCK_STATUS[SystemPrameter.SystemLanguage][m_LockStatus], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date
#endif


        rect.x0 = MODE_R_START_X + 10;
        rect.y0 = MODE_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = TIME_SET_R_END_X;
        rect.y1 = MODE_R_END_Y - TITLESBAR_HEIGHT;
        if (ExpEnable==EXP_ORGIN)
        {
            GUI_SetColor(0x0);
            GUI_FillRect(rect.x0-5,rect.y0+10,rect.x1-40,rect.y1-10);
            GUI_SetColor(COLOR_PAINT_TXT);
        }

			
        if(gSystem.PasswordOpenFlag)
        {
            sprintf(ConvertStr,"%d",m_Zero);
        }
        else
        {
            sprintf(ConvertStr,"%d",0);
        }
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date

        //密码项
        if(gSystem.PasswordOpenFlag)
        {
            GUI_SetColor(COLOR_PAINT_TXT_DIS);
        }
        else
        {
            GUI_SetColor(COLOR_PAINT_TXT);
        }
        rect.x0 = PASSWORD_START_X+20;
        rect.y0 = PASSWORD_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = PASSWORD_END_X;
        rect.y1=  PASSWORD_END_Y- TITLESBAR_HEIGHT;
        GUI_DispStringInRect(STR_PASSWORD[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//零点


        rect.x0 = PASSWORD_R_START_X + 10;
        rect.y0 = PASSWORD_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = PASSWORD_R_END_X;
        rect.y1 = PASSWORD_END_Y - TITLESBAR_HEIGHT;
        if (ExpEnable==EXP_PASSWORD)
        {
            GUI_SetColor(0x0);
            GUI_FillRect(rect.x0-5,rect.y0+10,rect.x1-20,rect.y1-10);
            GUI_SetColor(COLOR_PAINT_TXT);
        }
        GUI_DispStringInRect("********", &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date

				
				
				
				
				
				//校准模式
        if(gSystem.PasswordOpenFlag==0)
        {
            GUI_SetColor(COLOR_PAINT_TXT_DIS);
        }
        else
        {
            GUI_SetColor(COLOR_PAINT_TXT);
        }
        rect.x0 = CALI_MODE_START_X+20;
        rect.y0 = CALI_MODE_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = CALI_MODE_END_X;
        rect.y1=  CALI_MODE_END_Y- TITLESBAR_HEIGHT;
        GUI_DispStringInRect(STR_MODE_2[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//零点


        rect.x0 = CALI_MODE_R_START_X + 10;
        rect.y0 = CALI_MODE_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = CALI_MODE_R_END_X;
        rect.y1 = CALI_MODE_END_Y - TITLESBAR_HEIGHT;
        if (ExpEnable==EXP_CALI_MODE)
        {
            GUI_SetColor(0x0);
            GUI_FillRect(rect.x0-5,rect.y0+10,rect.x1-20,rect.y1-10);
            GUI_SetColor(COLOR_PAINT_TXT);
        }
        GUI_DispStringInRect(CALI_MODE[SystemPrameter.SystemLanguage][m_CaliMode], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date

				
				
				#ifdef SOFTWARE_DN
        ;
        #else
				 rect.x0 = LOCK_R_START_X + 10;
        rect.y0 = LOCK_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = LOCK_R_END_X;
        rect.y1 = LOCK_END_Y - TITLESBAR_HEIGHT;
        if (ExpEnable==EXP_LOCK)
        {
            GUI_SetColor(0x0);
            GUI_FillRect(rect.x0-5,rect.y0+10,rect.x1-20,rect.y1-10);
            GUI_SetColor(COLOR_PAINT_TXT);
        }
        GUI_DispStringInRect(STR_LOCK_STATUS[SystemPrameter.SystemLanguage][m_LockStatus], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date
				#endif
				
				
				
				
				
        //扩展项
        GUI_SetColor(COLOR_PAINT_TXT);
        //	GUI_SetFont(GUI_FONT_MED);
        if (ExpEnable==EXP_DOOR)
        {
            DisplayDoorExpand();
        }
        else if(ExpEnable==EXP_RAW_INTENSITY)
        {
            DisplayRawIntensityExpand();
        }
				else if(ExpEnable==EXP_CALI_MODE)
        {
            DisplayCaliModeExpand();
        }
				#ifndef SOFTWARE_DN
				else if(ExpEnable==EXP_LOCK)
        {
            DisplayLockExpand();
        }
				#endif
        break;

    case WM_NOTIFY_PARENT:
    {
        if(RemoteInfo_PC.RemoteFlag)
        {
            break;
        }
        if( (KeyPadAsc.UseFlag == KEYPAD_BUSY)||(KeyPadNum.UseFlag == KEYPAD_BUSY)||(PromptMenu.InterfaceStatus==PROMPT_MENU_BUSY) )
        {
            break;
        }
        if(TouchKey.KeyStatus)
        {
            break;
        }
        Id = WM_GetId(pMsg->hWinSrc);       // Id of widget
        NCode = pMsg->Data.v;               // Notification code
         if (NCode == WM_NOTIFICATION_RELEASED)
        {
            if ( (Id == ID_MAINTENACE_BUTTON) &&(gSystem.PasswordOpenFlag) )  //工具栏第1个按钮  开机图片更新
            {
                if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                {
                    strcpy(PromptMenu.InputStr,"Update picture?");
                }
                else
                {
                    strcpy(PromptMenu.InputStr,"Atualizar Imagens?");
                }
                Prompt_Interface(PROMPT_YES_NO);
                if(PromptMenu.KeyReturnValue==PROMPT_MENU_RETURN_ENTER)
                {
                    StartUpPra.EnableUsbCheck=0;
                    if(CopyStartupPicture())
                    {
                        //ERROR
                        Usb_Init();
                        StartUpPra.EnableUsbCheck=1;
                        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                        {
                            strcpy(PromptMenu.InputStr,"Error");
                        }
                        else
                        {
                            strcpy(PromptMenu.InputStr,"Erro");
                        }
                        Prompt_Interface(PROMPT_ERROR);

												
                    }
                    else
                    {
                        StartUpPra.EnableUsbCheck=1;
                        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                        {
                            strcpy(PromptMenu.InputStr,"Ok");
                        }
                        else
                        {
                            strcpy(PromptMenu.InputStr,"Ok");
                        }
                        Prompt_Interface(PROMPT_OK);
                    }
                }
            }
            else if( (Id == ID_MAINTENACE_BUTTON+1)&&(gSystem.PasswordOpenFlag) )    //工具栏第1个按钮  Reset
            {
                if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                {
                    strcpy(PromptMenu.InputStr, "Restore the Factory Settings?");
                }
                else
                {
                    strcpy(PromptMenu.InputStr, "Restaurar as configurações de fábrica？");
                }
                Prompt_Interface(PROMPT_YES_NO);
                if(PromptMenu.KeyReturnValue==PROMPT_MENU_RETURN_ENTER)
                {
                    if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                    {
                        strcpy(PromptMenu.InputStr, "Please waiting...");
                    }
                    else
                    {
                        strcpy(PromptMenu.InputStr, "Aguarde...");
                    }
                    Prompt_Interface(PROMPT_RUN);
                    NAND_Format();
                    RestoreFactory();
                    NandReadAllHead();

                    m_bDoorOpen=0;
                    SystemPrameter.DoorOpen=0;//恢复出厂设置
										//SystemPrameter.LockStatus=LOCK_DISABLE; //出厂后禁用密码 lugj 20190614
                    SpiSaveSystemPra();


                    DeletePromptMenu(0);
                    WM_InvalidateWindow(SystemMaintenaceWin);
                    GUI_Delay(20);
                    //WM_Window(SystemMaintenaceWin);

                    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                    {
                        strcpy(PromptMenu.InputStr,"Ok");
                    }
                    else
                    {
                        strcpy(PromptMenu.InputStr,"Ok");
                    }
                    Prompt_Interface(PROMPT_OK);
                    WM_InvalidateWindow(hWin);
                }
            }
            else if ((Id == ID_MAINTENACE_BUTTON+2)&&(gSystem.PasswordOpenFlag) )    //工具栏2个按钮  Update
            {
                gSystem.SystemInterface = MI_INSTRUMENT_UPDATE;
                SystemUpdate_Interface();
            }
            else   if( (Id == ID_MAINTENACE_BUTTON+3)&&(gSystem.PasswordOpenFlag) )    //工具栏第3个按钮  Calibration
            {
							  run_status.bHasDataBack=run_status.bHasData;//lugj20180913
		            memcpy(&BoardInfBack,&BoardInf,sizeof(BOARD_INF)); 
							
                gSystem.SystemInterface=MI_ABS_CALIBRATION;
							  
							  SystemPrameter.CaliMode=m_CaliMode;
                AbsCalibration_Interface();
							  SystemPrameter.CaliMode=m_CaliMode;//lugj 181023
            }

            else if (Id == ID_MAINTENACE_BUTTON+4)   //工具栏第4个按钮  Ok
            {
							  gSystem.PasswordOpenFlag=0;
							  SystemPrameter.CaliMode=m_CaliMode; //lugj 181023
							
                if(m_bDoorOpen!=SystemPrameter.DoorOpen)
                {
                    SystemPrameter.DoorOpen=m_bDoorOpen;
                    SpiSaveSystemPra();
                }

                if((m_bRawIntensity!=SystemPrameter.RawIntensity)||(m_Zero!=SystemPrameter.nOrigin)||(m_LockStatus!=SystemPrameter.LockStatus))
                {
									  if(SpiReadAbs()!=SPI_OK)
										{
											 SpiReadAbs();
										}
                    SystemPrameter.RawIntensity=m_bRawIntensity;
                    SystemPrameter.nOrigin=m_Zero;
										
										SystemPrameter.LockStatus=m_LockStatus;
									  //SystemPrameter.CaliMode=m_CaliMode;
                    //E2pSaveAdvancePra();
                    SpiSaveAbs();
                }
                
								if(m_CaliMode!=SystemPrameter.CaliModeBack) 
							  {
									 if(SpiReadAbs2()!=SPI_OK)
									 {
											 SpiReadAbs2();
									 }
									 
								//	 SystemPrameter.LockStatus=m_LockStatus;
									 
									 SystemPrameter.CaliMode=m_CaliMode;
									 SystemPrameter.CaliModeBack=m_CaliMode;
									 SpiSaveAbs2(); //用户模式，工厂/用户模式一起写入,为了软件向下兼容,工厂/用户模式没有放到SpiSaveAbs();
							  }
							
								
								
								if(m_CaliMode!=CALI_MODE_FACTORY) //lugj 20181023
								{
									  if(SpiReadAbs2()!=SPI_OK)
									  {
											 SpiReadAbs2();
									  }
										SystemPrameter.CaliMode=m_CaliMode;
	                  if(SpiReadAbs()!=SPI_OK)
										{
											 SpiReadAbs();
										}
									  if(FindUserData())
									  {
									     GenerateCaliData();
									  }
								}
								else
								{
									  SystemPrameter.CaliMode=m_CaliMode;
									  if(SpiReadAbs()!=SPI_OK)
										{
											 SpiReadAbs();
										}
								}
								
								
		            memcpy(&BoardInf, &BoardInfBack, sizeof(BOARD_INF)); //lugj20180913
								
                WM_DeleteWindow(SystemMaintenaceWin);
                WM_ShowWindow(SettingWin);
								

                gSystem.MenuRefreshFlag = 1;
                gSystem.SystemInterface = MI_SET;
                gSystem.TitleButtonEnable = 1;
                TouchKey.KeyStatus=1;
            }
            else if (Id == ID_MAINTENACE_BUTTON+5)   //工具栏第5个按钮  Back
            {
							  gSystem.PasswordOpenFlag=0;
							  SystemPrameter.CaliMode= SystemPrameter.CaliModeBack;
								if(SystemPrameter.CaliMode!=CALI_MODE_FACTORY)
								{
									  SpiReadAbs2();
									  SystemPrameter.CaliMode= SystemPrameter.CaliModeBack;
	                  SpiReadAbs();
									  if(FindUserData())
									  {
									     GenerateCaliData();
									  }
								}
								else
								{
									  if(SpiReadAbs()!=SPI_OK)
										{
											 SpiReadAbs();
										}
								}
								

								
		            memcpy(&BoardInf, &BoardInfBack, sizeof(BOARD_INF)); //lugj20180913
							
                WM_DeleteWindow(SystemMaintenaceWin);
                //WM_ShowWindow(SettingWin);

                gSystem.MenuRefreshFlag = 1;
                gSystem.SystemInterface = MI_SET;
                gSystem.TitleButtonEnable = 1;
                TouchKey.KeyStatus=1;
            }
        }
        break;
    }

    default:
        //		WM_DefaultProc(pMsg);
        break;
    }
}

void SystemMaintenace_Interface(void)
{
    //SystemPrameter.nOrigin=100;///////////
    
    ExpEnable = 0;
    m_Zero=SystemPrameter.nOrigin;
    m_bRawIntensity=SystemPrameter.RawIntensity;
    m_bDoorOpen=SystemPrameter.DoorOpen;
	
    SystemPrameter.CaliModeBack=SystemPrameter.CaliMode;//
	  m_CaliMode=SystemPrameter.CaliMode;
	  m_LockStatus=SystemPrameter.LockStatus;
    //lgj171123 debug start 测试用
    //gSystem.PasswordOpenFlag=0;//开机后密码要重新输入


    //CopySystemTime(&SystemTimePraBack, &SystemTimePra);
    //SystemPrameterBack.PrintHeaderEnable=SystemPrameter.PrintHeaderEnable;
    //strcpy(SystemPrameterBack.StrPrintHeader,SystemPrameter.StrPrintHeader);

    SystemMaintenaceWin = WM_CreateWindowAsChild(CONTENTBAR_POSX, CONTENTBAR_POSY, CONTENTBAR_WIDTH, CONTENTBAR_HEIGHT, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbMaintenace, 0);
    WM_BringToTop(SystemMaintenaceWin);
}

void SystemMaintenace_Scan(void)
{
    if (TouchKey.KeyStatus==0)
    {
        GUI_PID_STATE TouchState;

        GUI_PID_GetState(&TouchState);
        if (TouchState.Pressed)
        {
            if (ExpEnable==0)  //初使状态，没有弹出扩展项
            {
                if ((TouchState.x >= FILTER_1_R_START_X) && (TouchState.x <=  FILTER_1_R_END_X) &&
                        (TouchState.y >= FILTER_1_START_Y) && (TouchState.y <= FILTER_1_END_Y))
                {
                    ExpEnable = EXP_DOOR;
                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemMaintenaceWin);
                }
                else if ((TouchState.x >= FILTER_2_R_START_X) && (TouchState.x <=  FILTER_2_R_END_X) &&
                         (TouchState.y >= FILTER_2_START_Y) && (TouchState.y <= FILTER_2_END_Y)&&(gSystem.PasswordOpenFlag))
                {
                    ExpEnable = EXP_RAW_INTENSITY;
                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemMaintenaceWin);
                    //键盘输入
                }
                else if ((TouchState.x >= MODE_R_START_X) && (TouchState.x <=  MODE_R_END_X) &&
                         (TouchState.y >= MODE_START_Y) && (TouchState.y <= MODE_END_Y)&&(gSystem.PasswordOpenFlag))
                {
                    ExpEnable = EXP_ORGIN;
                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemMaintenaceWin);
                }
                else if ((TouchState.x >= PASSWORD_R_START_X) && (TouchState.x <= PASSWORD_R_END_X) &&
                         (TouchState.y >= PASSWORD_START_Y) && (TouchState.y <= PASSWORD_END_Y)&&(gSystem.PasswordOpenFlag==0))
                {
                    ExpEnable = EXP_PASSWORD;

                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemMaintenaceWin);
                }
								//校准模式
								 else if ((TouchState.x >= CALI_MODE_R_START_X) && (TouchState.x <= CALI_MODE_R_END_X) &&
                         (TouchState.y >= CALI_MODE_START_Y) && (TouchState.y <= CALI_MODE_END_Y)&&(gSystem.PasswordOpenFlag))
                {
                    ExpEnable = EXP_CALI_MODE;

                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemMaintenaceWin);
                }
								#ifndef SOFTWARE_DN
								else if ((TouchState.x >= LOCK_R_START_X) && (TouchState.x <= LOCK_R_END_X) &&
                         (TouchState.y >= LOCK_START_Y) && (TouchState.y <= LOCK_END_Y)&&(gSystem.PasswordOpenFlag))
                {
                    ExpEnable = EXP_LOCK;

                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemMaintenaceWin);
                }
								#endif
            }
            else// if (ExpEnable ) //模式扩展
            {
                if (ExpEnable==EXP_DOOR )
                {
                    if ((TouchState.x >= FILTER_1_R_START_X) && (TouchState.x <=  FILTER_1_R_START_X+PLATE_SEL_WIDTH) &&
                            (TouchState.y >= FILTER_1_START_Y) && (TouchState.y <= FILTER_1_END_Y))
                    {
                        m_bDoorOpen=0;
                    }
                    else  if ((TouchState.x >= FILTER_1_R_START_X+PLATE_SEL_WIDTH) && (TouchState.x <=  FILTER_1_R_START_X+2*PLATE_SEL_WIDTH+10) &&
                              (TouchState.y >= FILTER_1_START_Y) && (TouchState.y <= FILTER_1_END_Y))
                    {
                        m_bDoorOpen=1;
                    }
                    ExpEnable = 0;
                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemMaintenaceWin);
                }
                if(ExpEnable==EXP_RAW_INTENSITY)
                {
                    if ((TouchState.x >= FILTER_2_R_START_X) && (TouchState.x <=  FILTER_2_R_START_X+DOOR_SEL_WIDTH) &&
                            (TouchState.y >= FILTER_2_START_Y) && (TouchState.y <= FILTER_2_END_Y))
                    {
                        m_bRawIntensity=0;
                    }
                    else  if ((TouchState.x >= FILTER_2_R_START_X+DOOR_SEL_WIDTH) && (TouchState.x <=  FILTER_2_R_START_X+2*DOOR_SEL_WIDTH+10) &&
                              (TouchState.y >= FILTER_2_START_Y) && (TouchState.y <= FILTER_2_END_Y))
                    {
                        m_bRawIntensity=1;
                    }
                    ExpEnable = 0;
                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemMaintenaceWin);
                }
								 if(ExpEnable==EXP_CALI_MODE)  //校准模式
                 {
                    if ((TouchState.x >= CALI_MODE_R_START_X) && (TouchState.x <=  CALI_MODE_R_START_X+CALI_MODE_SEL_WIDTH1+5) &&
                            (TouchState.y >= CALI_MODE_START_Y) && (TouchState.y <= CALI_MODE_END_Y))
                    {
                        m_CaliMode=0;  //工厂 
                    }
                    else  if ((TouchState.x >= CALI_MODE_R_START_X+CALI_MODE_SEL_WIDTH1) && (TouchState.x <=  CALI_MODE_R_START_X+2*CALI_MODE_SEL_WIDTH2+10) &&
                              (TouchState.y >= CALI_MODE_START_Y) && (TouchState.y <= CALI_MODE_END_Y))
                    {
                        m_CaliMode=1;
                    }
                    ExpEnable = 0;
                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemMaintenaceWin);
                }
								 #ifndef SOFTWARE_DN
								 if(ExpEnable==EXP_LOCK)  //Lock模式
                 {
                    if ((TouchState.x >= LOCK_R_START_X) && (TouchState.x <=  LOCK_R_START_X+CALI_MODE_SEL_WIDTH1+5) &&
                            (TouchState.y >= LOCK_START_Y) && (TouchState.y <= LOCK_END_Y))
                    {
                        m_LockStatus=0;  //enable 
                    }
                    else  if ((TouchState.x >= LOCK_R_START_X+CALI_MODE_SEL_WIDTH1) && (TouchState.x <=  LOCK_R_START_X+2*CALI_MODE_SEL_WIDTH2+10) &&
                              (TouchState.y >= LOCK_START_Y) && (TouchState.y <= LOCK_END_Y))
                    {
                        m_LockStatus=1;//disable
                    }
                    ExpEnable = 0;
                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemMaintenaceWin);
                }
								 #endif
            }
        }//if (TouchState.Pressed)
    }

}


void SystemMaintenace_Go(void)
{
    if (TouchKey.KeyStatus)
    {
        GUI_PID_STATE TouchState;

        GUI_PID_GetState(&TouchState);
        if (TouchState.Pressed == 0)
        {
            TouchKey.KeyPressDelay++;
            if (TouchKey.KeyPressDelay > TOUCH_RELEASE_DELAY)
            {
                TouchKey.KeyPressDelay = 0;
                TouchKey.KeyStatus = 0;
            }
        }
    }


    if (ExpEnable == EXP_ORGIN)
    {
        strcpy(KeyPadNum.InputValueStr,"");

        sprintf(KeyPadNum.InputValueStr ,"%d",m_Zero);
        KeyPadNum_Interface(NUM_MENUFLAG_4NUM);//KeyPadNum.InputValueStr
        if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
        {
            m_Zero= atoi(KeyPadNum.InputValueStr);
            if(m_Zero>ZERO_MAX)m_Zero=ZERO_MAX;
            else if(m_Zero<ZERO_MIN)m_Zero=ZERO_MIN;
            MCU_SendSaveOrigin(m_Zero);
        }
        ExpEnable=0;
        TouchKey.KeyStatus = 1;
        WM_Invalidate(SystemMaintenaceWin);
    }
    else if (ExpEnable == EXP_PASSWORD)
    {
        ExpEnable =0;
        strcpy(KeyPadNum.InputValueStr,"");
        KeyPadNum_Interface(NUM_MENUFLAG_PASSWORD);//KeyPadNum.InputValueStr

        if ( strcmp(KeyPadNum.InputValueStr, UPDATA_PASSWORD)==0)
        {
            gSystem.PasswordOpenFlag=1;
            WM_EnableWindow(WM_GetDialogItem(SystemMaintenaceWin,ID_MAINTENACE_BUTTON));
            WM_EnableWindow(WM_GetDialogItem(SystemMaintenaceWin,ID_MAINTENACE_BUTTON+1));
            WM_EnableWindow(WM_GetDialogItem(SystemMaintenaceWin,ID_MAINTENACE_BUTTON+2));
            WM_EnableWindow(WM_GetDialogItem(SystemMaintenaceWin,ID_MAINTENACE_BUTTON+3));
            //BUTTON_SetState(WM_GetDialogItem(SystemMaintenaceWin,ID_MAINTENACE_BUTTON),BUTTON_CI_UNPRESSED);
            // BUTTON_SetState(WM_GetDialogItem(SystemMaintenaceWin,ID_MAINTENACE_BUTTON+1),BUTTON_CI_UNPRESSED);
            //BUTTON_SetState(WM_GetDialogItem(SystemMaintenaceWin,ID_MAINTENACE_BUTTON+2),BUTTON_CI_UNPRESSED);
        }
        else if ( strcmp(KeyPadNum.InputValueStr, FORMAT_PASSWORD)==0)
        {
            GUI_Delay(50);
            //strcpy(PromptMenu.InputStr,STR_FORMAT_MEMORY[SystemPrameter.SystemLanguage]);
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                strcpy(PromptMenu.InputStr,"Format?");
            }
            else
            {
                strcpy(PromptMenu.InputStr,"Formatar?");
            }
            Prompt_Interface(PROMPT_YES_NO);
            if(PromptMenu.KeyReturnValue==PROMPT_MENU_RETURN_ENTER)
            {
                if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                {
                    strcpy(PromptMenu.InputStr, "Please waiting...");
                }
                else
                {
                    strcpy(PromptMenu.InputStr, "Aguarde...");
                }
                Prompt_Interface(PROMPT_RUN);
                FileFormat_spi();
                // NandSaveFile(0);
                //NAND_Format();
                //sf_EraseChip();
                DeletePromptMenu(0);
                if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                {
                    strcpy(PromptMenu.InputStr,"Finish");
                }
                else
                {
                    strcpy(PromptMenu.InputStr,"Finalizado");
                }
                Prompt_Interface(PROMPT_WARMING);
								ExpEnable=0;
        TouchKey.KeyStatus = 1;
        WM_Invalidate(SystemMaintenaceWin);
            }
        }
        else
        {
           // gSystem.PasswordOpenFlag=0;
						        ExpEnable=0;
        TouchKey.KeyStatus = 1;
        WM_Invalidate(SystemMaintenaceWin);
            //Prompt_Interface(PROMPT_PASSWORD_ERR);
        }

        ExpEnable=0;
        TouchKey.KeyStatus = 1;
        WM_Invalidate(SystemMaintenaceWin);

    }
}




