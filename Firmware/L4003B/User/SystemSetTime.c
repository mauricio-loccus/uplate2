#include "MainTask.h"


// CDopenLanguage dialog
const int DATETIME_YEAR_START[LANGUAGE_TYPES] =  {194,126};//126,184
const int DATETIME_MONTH_START[LANGUAGE_TYPES] = {126,179}; //174,126
const int DATETIME_DAY_START[LANGUAGE_TYPES] =   {158,216}; //213,156

const char STR_DATETIME_TITLE[LANGUAGE_TYPES][ABSDLG_TITLE_CHAR_MAX] = {"Set date and time", "Ajuste de Data e Hora"};
const char STR_DATETIME_DATE[LANGUAGE_TYPES][10] = {"Date", "Data"};
const char STR_DATETIME_TIME[LANGUAGE_TYPES][10] = {"Time", "Hora"};

const int MONTH_DAY_MAX[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30,31};


/*
typedef struct {
	int          xPos;
	int          yPos;
	int          xSize;
	int          ySize;
	const char * acLabelEn;									 //按钮对应的键码
	const char * acLabelCh;
} BUTTON_DATA;*/
const BUTTON_DATA _aButtonDateTime[] =
{
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(3), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Ok", "Ok" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(4), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Back", "Voltar" },
};


//ExpEnable的值定义
enum
{
    EXP_DATE_YEAR=1,
    EXP_DATE_MONTH,
    EXP_DATE_DAY,
    EXP_TIME_HOUR,
    EXP_TIME_MIN,
    EXP_TIME_SEC,
};
static unsigned char ExpEnable;

static SYSTEM_TIME  SystemTimePraBack;


WM_HWIN SystemDateTimeWin = NULL;


void CopySystemTime(SYSTEM_TIME *destP, SYSTEM_TIME *sourceP)
{
//	unsigned char i;
    //备份系统时间
    destP->Year = sourceP->Year;

    destP->Month = sourceP->Month;
    destP->Day = sourceP->Day;
    destP->Hour = sourceP->Hour;
    destP->Min = sourceP->Min;
    destP->Sec = sourceP->Sec;
}


void SystemTimeEnter(void)
{

    CopySystemTime(&SystemTimePra, &SystemTimePraBack);


    RtcDateTime.RTC_Date.RTC_Year=SystemTimePra.Year%100;
    RtcDateTime.RTC_Date.RTC_Month=SystemTimePra.Month;
    RtcDateTime.RTC_Date.RTC_Date= SystemTimePra.Day;
    RtcDateTime.RTC_Time.RTC_Hours=SystemTimePra.Hour;
    RtcDateTime.RTC_Time.RTC_Minutes=SystemTimePra.Min;
    RtcDateTime.RTC_Time.RTC_Seconds=SystemTimePra.Sec;

    RTC_SetDate(RTC_Format_BIN, &RtcDateTime.RTC_Date);
    RTC_SetTime(RTC_Format_BIN, &RtcDateTime.RTC_Time);

    //WM_DeleteWindow(SystemTimeWin);
//	DlgSetTimeUseFlag = DLG_SETTIME_FREE;
    //gSystem.SysSec =0;
//	gSystem.MinFlag =0;
    //gSystem.SecFlag =0;
}
void SystemTimeCancel(void)
{
    WM_DeleteWindow(SystemDateTimeWin);
//	DlgSetTimeUseFlag = DLG_SETTIME_FREE;
}



void _cbDateTime(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
//	WM_HWIN hWinFocus;
    BUTTON_Handle hbutton;
    unsigned char i;
    short xSize;
    short ySize;
    short NCode, Id;
    GUI_RECT rect;

//	hWinFocus = WM_GetFocussedWindow();

    switch (pMsg->MsgId)
    {
    case WM_CREATE:
    {
        for (i = 0; i < GUI_COUNTOF(_aButtonDateTime); i++)
        {
            hbutton = BUTTON_CreateEx(_aButtonDateTime[i].xPos, _aButtonDateTime[i].yPos, _aButtonDateTime[i].xSize, _aButtonDateTime[i].ySize,
                                      hWin, WM_CF_SHOW, 0, ID_DATETIME_BUTTON + i);
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG);
                BUTTON_SetText(hbutton, _aButtonDateTime[i].acLabelEn);
            }
            else
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG_CH);
                BUTTON_SetText(hbutton, _aButtonDateTime[i].acLabelCh);
            }
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
        //	GUI_DrawBitmap(&bmMenuLeft_101_46, MODE_START_X, MODE_START_Y - TITLESBAR_HEIGHT);

        //GUI_DrawBitmap(&bmMenuRight_120_46, FILTER_1_R_START_X, FILTER_1_R_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(FILTER_1_R_START_X, FILTER_1_R_START_Y- TITLESBAR_HEIGHT,FILTER_1_R_START_X+125, FILTER_1_R_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, FILTER_1_R_START_X+125, FILTER_1_R_START_Y- TITLESBAR_HEIGHT);
        //	GUI_DrawBitmap(&bmMenuRight_120_46, FILTER_2_R_START_X, FILTER_2_R_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(FILTER_2_R_START_X, FILTER_2_R_START_Y- TITLESBAR_HEIGHT,FILTER_2_R_START_X+115, FILTER_2_R_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, FILTER_2_R_START_X+115, FILTER_2_R_START_Y- TITLESBAR_HEIGHT);
        //GUI_DrawBitmap(&bmMenuRight_90_46, MODE_R_START_X, MODE_START_Y - TITLESBAR_HEIGHT);


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
        GUI_DispStringAt(STR_DATETIME_TITLE[SystemPrameter.SystemLanguage], CONTENTBAR_CAPTION_POSX, CONTENTBAR_CAPTION_POSY);//"Measurement parameters"


        rect.x0 = FILTER_1_START_X+20;
        rect.y0 = FILTER_1_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = DATE_SET_R_START_X;
        rect.y1 = DATE_SET_R_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(STR_DATETIME_DATE[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Filter 1"


        rect.x0 = FILTER_2_START_X+20;
        rect.y0 = TIME_SET_R_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = TIME_SET_R_END_X;
        rect.y1 = TIME_SET_R_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(STR_DATETIME_TIME[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Filter 1"



        //年月日的本底选框色
        if(ExpEnable)
        {
           GUI_SetColor(COLOR_SHAKE_TIME_BK);
            if( (ExpEnable==EXP_TIME_HOUR)||(ExpEnable==EXP_TIME_MIN)||(ExpEnable==EXP_TIME_SEC) )
            {
                rect.y0=TIME_SET_R_START_Y- TITLESBAR_HEIGHT+3;
                rect.y1=TIME_SET_R_END_Y- TITLESBAR_HEIGHT-3;
                if(ExpEnable==EXP_TIME_HOUR)
                {
                    rect.x0=DATETIME_HOUR_START;
                    rect.x1=DATETIME_HOUR_START + DATETIME_TIME_WIDTH + 5;
                }
                else if(ExpEnable==EXP_TIME_MIN)
                {
                    rect.x0=DATETIME_MINUTE_START+5;
                    rect.x1=DATETIME_MINUTE_START + DATETIME_TIME_WIDTH + 10;
                }
                else if(ExpEnable==EXP_TIME_SEC)
                {
                    rect.x0=DATETIME_SECOND_START+13;
                    rect.x1=DATETIME_SECOND_START + DATETIME_TIME_WIDTH + 20;
                }
                GUI_FillRect(rect.x0, rect.y0, rect.x1, rect.y1);
            }
            else if( (ExpEnable==EXP_DATE_YEAR)||(ExpEnable==EXP_DATE_MONTH)||(ExpEnable==EXP_DATE_DAY) )
            {
                rect.y0=DATE_SET_R_START_Y- TITLESBAR_HEIGHT+3;
                rect.y1=DATE_SET_R_END_Y- TITLESBAR_HEIGHT-3;
                if(ExpEnable==EXP_DATE_YEAR)
                {
                    rect.x0=DATETIME_YEAR_START[SystemPrameter.SystemLanguage]+4;
                    rect.x1=DATETIME_YEAR_START[SystemPrameter.SystemLanguage] + DATETIME_YEAR_WIDTH+11;
                    if(SystemPrameter.SystemLanguage==LANGUAGE_CH)
                    {
                        rect.x0=rect.x0+70;
                        rect.x1=rect.x1+70;
                    }
                    else
                    {
                        rect.x0=rect.x0+2;
                    }
                }
                else if(ExpEnable==EXP_DATE_MONTH)
                {
                    rect.x0=DATETIME_MONTH_START[SystemPrameter.SystemLanguage]+4; //6
                    rect.x1=DATETIME_MONTH_START[SystemPrameter.SystemLanguage] + DATETIME_TIME_WIDTH + 5;	//8
                    if(SystemPrameter.SystemLanguage==LANGUAGE_CH)
                    {
                       rect.x0=161;
												rect.x1=190;
                    }
                    else
                    {
                        rect.x0=rect.x0-2;
                    }
                }
                else if(ExpEnable==EXP_DATE_DAY)
                {
									rect.x0=DATETIME_DAY_START[SystemPrameter.SystemLanguage]+4;
                    rect.x1=DATETIME_DAY_START[SystemPrameter.SystemLanguage] + DATETIME_TIME_WIDTH + 9;
									if(SystemPrameter.SystemLanguage==LANGUAGE_CH)
                    {
                        rect.x0=125;
												rect.x1=155;
                    }
                    else
                    {
                        rect.x1=rect.x1+2;
                    }
                }
                GUI_FillRect(rect.x0, rect.y0, rect.x1, rect.y1);
            }
            GUI_SetColor(GUI_WHITE);
        }



        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            sprintf(ConvertStr,"%02d - %02d - %04d",SystemTimePraBack.Month,SystemTimePraBack.Day,SystemTimePraBack.Year);
        }
        else
        {
            sprintf(ConvertStr,"%02d - %02d - %04d",SystemTimePraBack.Day,SystemTimePraBack.Month,SystemTimePraBack.Year);
        }
        rect.x0 = FILTER_1_R_START_X + 10;
        rect.y0 = FILTER_1_R_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = DATE_SET_R_END_X;
        rect.y1 = DATE_SET_R_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date




        sprintf(ConvertStr,"%02d : %02d : %02d",SystemTimePraBack.Hour,SystemTimePraBack.Min,SystemTimePraBack.Sec);
        rect.x0 = FILTER_2_R_START_X + 10;
        rect.y0 = FILTER_2_R_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = TIME_SET_R_END_X;
        rect.y1 = FILTER_2_R_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date

        break;

    case WM_NOTIFY_PARENT:
    {
        Id = WM_GetId(pMsg->hWinSrc);    // Id of widget
        NCode = pMsg->Data.v;               // Notification code
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
        if (NCode == WM_NOTIFICATION_RELEASED)
        {
            if (Id == ID_DATETIME_BUTTON)   //工具栏第4个按钮  Enter
            {
                //    SystemPrameter.SystemLanguage =LanguageBack;

                SystemTimeEnter();
                WM_DeleteWindow(SystemDateTimeWin);
                WM_ShowWindow(SettingWin);

                gSystem.MenuRefreshFlag = 1;
                gSystem.SystemInterface = MI_SET;
                TouchKey.KeyStatus=1;
                gSystem.TitleButtonEnable = 1;
            }
            else if (Id == ID_DATETIME_BUTTON+1)   //工具栏第5个按钮  Cancel
            {
                WM_DeleteWindow(SystemDateTimeWin);
                WM_ShowWindow(SettingWin);

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





void SystemSetTime_Interface(void)
{

    ExpEnable = 0;
    CopySystemTime(&SystemTimePraBack, &SystemTimePra);

    SystemDateTimeWin = WM_CreateWindowAsChild(CONTENTBAR_POSX, CONTENTBAR_POSY, CONTENTBAR_WIDTH, CONTENTBAR_HEIGHT, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbDateTime, 0);
    WM_BringToTop(SystemDateTimeWin);
}


void SystemSetTime_Scan(void)
{
    if (TouchKey.KeyStatus==0)
    {

        GUI_PID_STATE TouchState;

        GUI_PID_GetState(&TouchState);
        if (TouchState.Pressed)
        {
            if (ExpEnable==0)  //初使状态，没有弹出扩展项
            {
							if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
							{
                if ((TouchState.x >= DATE_SET_R_START_X) && (TouchState.x <= DATE_SET_R_END_X) &&
                        (TouchState.y >= DATE_SET_R_START_Y) && (TouchState.y <= DATE_SET_R_END_Y))
                {
                    if ((TouchState.x >DATETIME_YEAR_START[SystemPrameter.SystemLanguage])&&(TouchState.x <DATETIME_YEAR_START[SystemPrameter.SystemLanguage] + DATETIME_YEAR_WIDTH+10))// + 20) )
                    {
                        ExpEnable = EXP_DATE_YEAR;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                    else   if ((TouchState.x >DATETIME_MONTH_START[SystemPrameter.SystemLanguage])&&(TouchState.x <DATETIME_MONTH_START[SystemPrameter.SystemLanguage] + DATETIME_TIME_WIDTH + 10) )
                    {
                        ExpEnable = EXP_DATE_MONTH;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                    else   if ((TouchState.x >DATETIME_DAY_START[SystemPrameter.SystemLanguage])&&(TouchState.x <DATETIME_DAY_START[SystemPrameter.SystemLanguage] + DATETIME_TIME_WIDTH + 10) )
                    {
                        ExpEnable = EXP_DATE_DAY;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                }
                if ((TouchState.x >= TIME_SET_R_START_X) && (TouchState.x <= TIME_SET_R_END_X) &&
                        (TouchState.y >= TIME_SET_R_START_Y) && (TouchState.y <= TIME_SET_R_END_Y))
                {
                    if ((TouchState.x >DATETIME_HOUR_START)&&(TouchState.x <DATETIME_HOUR_START + DATETIME_TIME_WIDTH + 10) )
                    {
                        ExpEnable = EXP_TIME_HOUR;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                    else if ((TouchState.x >DATETIME_MINUTE_START)&&(TouchState.x <DATETIME_MINUTE_START + DATETIME_TIME_WIDTH + 10) )
                    {
                        ExpEnable = EXP_TIME_MIN;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                    else if ((TouchState.x >DATETIME_SECOND_START)&&(TouchState.x <DATETIME_SECOND_START + DATETIME_TIME_WIDTH + 20) )
                    {
                        ExpEnable = EXP_TIME_SEC;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                }
            }
					else
					{
					 if ((TouchState.x >= DATE_SET_R_START_X) && (TouchState.x <= DATE_SET_R_END_X) &&
                        (TouchState.y >= DATE_SET_R_START_Y) && (TouchState.y <= DATE_SET_R_END_Y))
                {
                    if ((TouchState.x >200)&&(TouchState.x <240))// + 20) )
                    {
                        ExpEnable = EXP_DATE_YEAR;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                    else   if ((TouchState.x >160)&&(TouchState.x <190) )
                    {
                        ExpEnable = EXP_DATE_MONTH;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                    else   if ((TouchState.x >125)&&(TouchState.x <155) )
                    {
                        ExpEnable = EXP_DATE_DAY;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                }
                if ((TouchState.x >= TIME_SET_R_START_X) && (TouchState.x <= TIME_SET_R_END_X) &&
                        (TouchState.y >= TIME_SET_R_START_Y) && (TouchState.y <= TIME_SET_R_END_Y))
                {
                    if ((TouchState.x >DATETIME_HOUR_START)&&(TouchState.x <DATETIME_HOUR_START + DATETIME_TIME_WIDTH + 10) )
                    {
                        ExpEnable = EXP_TIME_HOUR;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                    else if ((TouchState.x >DATETIME_MINUTE_START)&&(TouchState.x <DATETIME_MINUTE_START + DATETIME_TIME_WIDTH + 10) )
                    {
                        ExpEnable = EXP_TIME_MIN;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                    else if ((TouchState.x >DATETIME_SECOND_START)&&(TouchState.x <DATETIME_SECOND_START + DATETIME_TIME_WIDTH + 20) )
                    {
                        ExpEnable = EXP_TIME_SEC;
                        TouchKey.KeyStatus = 1;
                        WM_Invalidate(SystemDateTimeWin);
                    }
                }
            }
					}	
				}						
        }//if (ExpEnable==0)  //初使状态，没有弹出扩展项
    }//if (TouchKey.KeyStatus==0)





void SystemSetTime_Go(void)
{
    if (TouchKey.KeyStatus)
    {
        GUI_PID_STATE TouchState;
        unsigned short time_val;
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


        if (ExpEnable == EXP_DATE_YEAR)
        {
            sprintf(KeyPadNum.InputValueStr,"%04d",SystemTimePraBack.Year);
        }
        else  if (ExpEnable == EXP_DATE_MONTH)
        {
            sprintf(KeyPadNum.InputValueStr,"%02d",SystemTimePraBack.Month);
        }
        else   if (ExpEnable == EXP_DATE_DAY)
        {
            sprintf(KeyPadNum.InputValueStr,"%02d",SystemTimePraBack.Day);
        }
        else if (ExpEnable == EXP_TIME_HOUR)
        {
            sprintf(KeyPadNum.InputValueStr,"%02d",SystemTimePraBack.Hour);
        }
        else   if (ExpEnable == EXP_TIME_MIN )
        {
            sprintf(KeyPadNum.InputValueStr,"%02d",SystemTimePraBack.Min);
        }
        else   if (ExpEnable == EXP_TIME_SEC)
        {
            sprintf(KeyPadNum.InputValueStr,"%02d",SystemTimePraBack.Sec);
        }

        if(ExpEnable)
        {
            if(ExpEnable==EXP_DATE_YEAR)
            {
                KeyPadNum_Interface(NUM_MENUFLAG_4NUM);//KeyPadNum.InputValueStr
            }
            else
            {
                KeyPadNum_Interface(NUM_MENUFLAG_2NUM);
            }
            if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
            {
                time_val= atoi(KeyPadNum.InputValueStr);
                if(ExpEnable==EXP_DATE_YEAR)
                {
                    if(time_val > DATETIME_YEAR_MAX)
                    {
                        time_val = DATETIME_YEAR_MAX;
                    }
                    if(time_val < DATETIME_YEAR_MIN)
                    {
                        time_val = DATETIME_YEAR_MIN;
                    }
                    SystemTimePraBack.Year=time_val;
                }
                else if(ExpEnable==EXP_DATE_MONTH)
                {
                    if(time_val > DATETIME_MONTH_MAX)
                    {
                        time_val = DATETIME_MONTH_MAX;
                    }
                    if(time_val < DATETIME_MONTH_MIN)
                    {
                        time_val = DATETIME_MONTH_MIN;
                    }
                    SystemTimePraBack.Month=time_val;
                }
                else if(ExpEnable==EXP_DATE_DAY)
                {
                    if(time_val > DATETIME_DAY_MAX)
                    {
                        time_val = DATETIME_DAY_MAX;
                    }
                    if(time_val < DATETIME_DAY_MIN)
                    {
                        time_val = DATETIME_DAY_MIN;
                    }
                    SystemTimePraBack.Day=time_val;
                }
                else if(ExpEnable==EXP_TIME_HOUR)
                {
                    if(time_val > DATETIME_HOUR_MAX)
                    {
                        time_val = DATETIME_HOUR_MAX;
                    }
                    else if(time_val < DATETIME_HOUR_MIN)
                    {
                        time_val = DATETIME_HOUR_MIN;
                    }
                    SystemTimePraBack.Hour=time_val;
                }
                else if(ExpEnable==EXP_TIME_MIN)
                {
                    if(time_val > DATETIME_MINUTE_MAX)
                    {
                        time_val = DATETIME_MINUTE_MAX;
                    }
                    else if(time_val < DATETIME_MINUTE_MIN)
                    {
                        time_val = DATETIME_MINUTE_MIN;
                    }
                    SystemTimePraBack.Min=time_val;
                }
                else if(ExpEnable==EXP_TIME_SEC)
                {
                    if(time_val > DATETIME_SECOND_MAX)
                    {
                        time_val = DATETIME_SECOND_MAX;
                    }
                    else if(time_val < DATETIME_SECOND_MIN)
                    {
                        time_val = DATETIME_SECOND_MIN;
                    }
                    SystemTimePraBack.Sec=time_val;
                }
                //润年2月只有29天
                if((SystemTimePraBack.Year%4 ==0 && SystemTimePraBack.Year%100 !=0) || (SystemTimePraBack.Year%400 ==0))
                {
                    if(  (SystemTimePraBack.Month==2) &&(  SystemTimePraBack.Day>29)  )
                    {
                        SystemTimePraBack.Day=29;
                    }
                }
                //其它的2月有28天
                else if(SystemTimePraBack.Day > MONTH_DAY_MAX[SystemTimePraBack.Month - 1])
                {
                    SystemTimePraBack.Day = MONTH_DAY_MAX[SystemTimePraBack.Month - 1];
                }
            }
            ExpEnable=0;
            TouchKey.KeyStatus = 1;
            WM_Invalidate(SystemDateTimeWin);
        }//if(ExpEnable)
    }//if (TouchState.Pressed == 0)
}


