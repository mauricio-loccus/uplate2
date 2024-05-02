//程序已自检-打印内容未显示
#include "MainTask.h"


const char  STR_PRINTER_TITLE[LANGUAGE_TYPES][30] = {"Set report title" , "Título do Relatório"};
const char  STR_PRINTER_TITLE_ENABLE[LANGUAGE_TYPES][20] = {"Title", "Habilitar"};
const char  STR_PRINTER_TITLE_CONTENT[LANGUAGE_TYPES][15] = {"Content", "Título"};



const BUTTON_DATA _aButtonPrinter[] =
{
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(3), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Ok", "Ok" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(4), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Back", "Voltar" },
};


//ExpEnable的值定义
enum
{
    EXP_ENABLE=1,
    EXP_TITLE,
};
static unsigned char ExpEnable;


WM_HWIN SystemPrinterWin = NULL;




void DisplayEnableExpand(void)
{
    unsigned char i;
    GUI_RECT rect;

    int start_x, start_y, wide, high;

    start_x = FILTER_1_R_START_X ;
    start_y = FILTER_1_R_START_Y  - TITLESBAR_HEIGHT;
    //GUI_DrawBitmap(&bmExpMenuRight_135_46, FILTER_1_R_START_X, FILTER_1_R_START_Y - TITLESBAR_HEIGHT);
    GUI_SetColor(COLOR_EXP_PICTURE_FRAME);
    GUI_DrawLine(start_x, start_y,start_x+160,start_y);
    GUI_DrawLine(start_x, start_y+45,start_x+160,start_y+45);
    GUI_SetColor(COLOR_EXP_PICTURE);
    GUI_FillRect(start_x, start_y,start_x+160,start_y+45);
    GUI_DrawBitmap(&bmExpMenuRight_20_46, start_x+160, start_y);

    start_x += 3;
    start_y += 3;
    wide = 66;//INTER_SEL_WIDTH;
    high = 40;
    for (i = 0; i<2; i++)
    {

        //填充选中的底色
        GUI_SetColor(COLOR_SHAKE_BK);
        if (i == 0)
        {
            strcpy(ConvertStr,STR_CLOSE[SystemPrameter.SystemLanguage] );//"Off"
        }
        else
        {
            strcpy(ConvertStr, STR_OPEN[SystemPrameter.SystemLanguage] );//"On"
        }

        //填充选中的文字-白色
        if (((SystemPrameterBack.PrintHeaderEnable == 0) && (i == 0)) || ((SystemPrameterBack.PrintHeaderEnable) && (i == 1)))
        {
            GUI_FillRect(start_x, start_y, start_x + wide, start_y + high);
            GUI_SetColor(COLOR_SHAKE_TXT);
            //GUI_DrawCircle(RUNMENU_CIRCLE_POSX(i), RUNMENU_CIRCLE_POSY, RUNMENU_CIRCLE_RADIUS);
        }

        rect.x0 = start_x;
        rect.y0 = start_y - 1;
        rect.x1 = start_x + wide;
        rect.y1 = start_y + high;

        start_x += wide;
        wide =66;// INTER_SEL_WIDTH;

        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    }

}




void _cbPrinter(WM_MESSAGE * pMsg)
{

    //char str[10];
    WM_HWIN hWin = pMsg->hWin;
    WM_HWIN hWinFocus;
    BUTTON_Handle hbutton;
    unsigned char i;
    short        xSize;
    short        ySize;
    short NCode, Id;
    GUI_RECT rect;
    //	int  day_max;
    hWinFocus = WM_GetFocussedWindow();
//	IdWinFocus = WM_GetId(hWinFocus);

    switch (pMsg->MsgId)
    {
    case WM_CREATE:
    {
        for (i = 0; i < GUI_COUNTOF(_aButtonPrinter); i++)
        {
            hbutton = BUTTON_CreateEx(_aButtonPrinter[i].xPos, _aButtonPrinter[i].yPos, _aButtonPrinter[i].xSize, _aButtonPrinter[i].ySize,
                                      hWin, WM_CF_SHOW, 0, ID_DATETIME_BUTTON + i);
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG);
                BUTTON_SetText(hbutton, _aButtonPrinter[i].acLabelEn);
            }
            else
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG_CH);
                BUTTON_SetText(hbutton, _aButtonPrinter[i].acLabelCh);
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

        //	GUI_DrawBitmap(&bmMenuRight_120_46, FILTER_1_R_START_X, FILTER_1_R_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(FILTER_1_R_START_X, FILTER_1_R_START_Y- TITLESBAR_HEIGHT,FILTER_1_R_START_X+100, FILTER_1_R_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, FILTER_1_R_START_X+100, FILTER_1_R_START_Y- TITLESBAR_HEIGHT);
//		GUI_DrawBitmap(&bmMenuRight_320_46, FILTER_2_R_START_X, FILTER_2_R_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(FILTER_2_R_START_X, FILTER_2_R_START_Y- TITLESBAR_HEIGHT,FILTER_2_R_START_X+300, FILTER_2_R_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, FILTER_2_R_START_X+300, FILTER_2_R_START_Y- TITLESBAR_HEIGHT);


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

        GUI_DispStringAt(STR_PRINTER_TITLE[SystemPrameter.SystemLanguage], CONTENTBAR_CAPTION_POSX, CONTENTBAR_CAPTION_POSY);//"Measurement parameters"


        //GUI_SetFont(GUI_FONT_SMALL);

        rect.x0 = FILTER_1_START_X+20;
        rect.y0 = FILTER_1_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = DATE_SET_R_START_X;
        rect.y1 = DATE_SET_R_END_Y - TITLESBAR_HEIGHT;
        //strcpy(ConvertStr, "Filter 1");
        GUI_DispStringInRect(STR_PRINTER_TITLE_ENABLE[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Filter 1"





        if (SystemPrameterBack.PrintHeaderEnable)
        {
            strcpy(ConvertStr,STR_OPEN[SystemPrameter.SystemLanguage]);// "On");
        }
        else
        {
            strcpy(ConvertStr, STR_CLOSE[SystemPrameter.SystemLanguage]);//"Off");
        }
        rect.x0 = FILTER_1_R_START_X + 10;
        rect.y0 = FILTER_1_R_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = DATE_SET_R_END_X;
        rect.y1 = DATE_SET_R_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date



        if(SystemPrameterBack.PrintHeaderEnable)
        {
            GUI_SetColor(COLOR_PAINT_TXT);
        }
        else
        {
            GUI_SetColor(COLOR_PAINT_TXT_DIS);
        }

        rect.x0 = FILTER_2_START_X+20;
        rect.y0 = TIME_SET_R_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = TIME_SET_R_END_X;
        rect.y1 = TIME_SET_R_END_Y - TITLESBAR_HEIGHT;
        //strcpy(ConvertStr, "Filter 1");
        GUI_DispStringInRect(STR_PRINTER_TITLE_CONTENT[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Filter 1"


        //sprintf(ConvertStr,"%02d : %02d : %02d",SystemTimePraBack.Hour,SystemTimePraBack.Min,SystemTimePraBack.Sec);
        rect.x0 = FILTER_2_R_START_X + 10;
        rect.y0 = FILTER_2_R_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = FILTER_2_R_START_X+320;
        rect.y1 = FILTER_2_R_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(SystemPrameterBack.StrPrintHeader, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//Date




        GUI_SetColor(COLOR_PAINT_TXT);
        //GUI_SetFont(GUI_FONT_MED);
        if (ExpEnable==EXP_ENABLE)
        {
            DisplayEnableExpand();
        }

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
            if (Id == ID_PRINTER_BUTTON)   //工具栏第4个按钮  Enter
            {
                SystemPrameter.PrintHeaderEnable=SystemPrameterBack.PrintHeaderEnable;
							#ifdef DEBUG_AS112
							strcpy(SystemPrameterBack.StrPrintHeader,"");//
							#endif
                strcpy(SystemPrameter.StrPrintHeader,SystemPrameterBack.StrPrintHeader);
                SpiSaveSystemPra();//lgj171116  故障报警

                WM_DeleteWindow(SystemPrinterWin);
                WM_ShowWindow(SettingWin);

                gSystem.SystemInterface = MI_SET;
                gSystem.TitleButtonEnable = 1;
                TouchKey.KeyStatus=1;
                gSystem.MenuRefreshFlag = 1;
            }
            else if (Id == ID_PRINTER_BUTTON+1)   //工具栏第5个按钮  Cancel
            {
                WM_DeleteWindow(SystemPrinterWin);
                WM_ShowWindow(SettingWin);

                gSystem.SystemInterface = MI_SET;
                gSystem.TitleButtonEnable = 1;
                TouchKey.KeyStatus=1;
                gSystem.MenuRefreshFlag = 1;
            }
        }
        break;
    }

    default:
        //		WM_DefaultProc(pMsg);
        break;
    }
}


void SystemPrinter_Interface(void)
{

    ExpEnable = 0;
    //CopySystemTime(&SystemTimePraBack, &SystemTimePra);
    SystemPrameterBack.PrintHeaderEnable=SystemPrameter.PrintHeaderEnable;
    strcpy(SystemPrameterBack.StrPrintHeader,SystemPrameter.StrPrintHeader);

    SystemPrinterWin = WM_CreateWindowAsChild(CONTENTBAR_POSX, CONTENTBAR_POSY, CONTENTBAR_WIDTH, CONTENTBAR_HEIGHT, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbPrinter, 0);
    WM_BringToTop(SystemPrinterWin);
}


void SystemPrinter_Scan(void)
{

    if (TouchKey.KeyStatus==0)
    {
        GUI_PID_STATE TouchState;

        GUI_PID_GetState(&TouchState);
        if (TouchState.Pressed)
        {
            if (ExpEnable==0)  //初使状态，没有弹出扩展项
            {
                if ((TouchState.x >= FILTER_1_R_START_X) && (TouchState.x <=  FILTER_1_R_START_X+105) &&
                        (TouchState.y >= FILTER_1_START_Y) && (TouchState.y <= FILTER_1_END_Y))
                {
                    ExpEnable = EXP_ENABLE;
                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemPrinterWin);
                }
                else if ((TouchState.x >= FILTER_2_R_START_X) && (TouchState.x <=  FILTER_2_R_START_X+320) &&
                         (TouchState.y >= FILTER_2_START_Y) && (TouchState.y <= FILTER_2_END_Y)&&(SystemPrameterBack.PrintHeaderEnable))
                {

                    ExpEnable = EXP_TITLE;


                    TouchKey.KeyStatus = 1;
                    WM_Invalidate(SystemPrinterWin);

                    //键盘输入
                    //KeyPadAscii_Interface(0);

                }

            }

            else if (ExpEnable ) //模式扩展
            {
                if (ExpEnable==EXP_ENABLE )
                {
                    if ((TouchState.x >= FILTER_1_R_START_X) && (TouchState.x <=  FILTER_1_R_START_X+65) &&
                            (TouchState.y >= FILTER_1_START_Y) && (TouchState.y <= FILTER_1_END_Y))
                    {
                        SystemPrameterBack.PrintHeaderEnable=0;
                    }
                    else  if ((TouchState.x >= FILTER_1_R_START_X+66) && (TouchState.x <=  FILTER_1_R_START_X+135) &&
                              (TouchState.y >= FILTER_1_START_Y) && (TouchState.y <= FILTER_1_END_Y))
                    {
                        SystemPrameterBack.PrintHeaderEnable=1;
                    }
                }
                ExpEnable = 0;
                WM_Invalidate(SystemPrinterWin);
                TouchKey.KeyStatus = 1;
            }
        }
    }

}



void SystemPrinter_Go(void)
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

    if (ExpEnable == EXP_TITLE)
    {
        //键盘输入
        strcpy(KeyPadAsc.InputValueStr,SystemPrameterBack.StrPrintHeader);
        TouchKey.KeyStatus = 1;
        KeyPadAscii_Interface(0,PROMPT_TITLE);
        if ( (KeyPadAsc.ReturnKey == KEYPAD_RETURN_ENTER)&&(KeyPadAsc.InputValueStr[0]!=0) )
        {
            strcpy(SystemPrameterBack.StrPrintHeader,KeyPadAsc.InputValueStr);
        }
        ExpEnable =0;
        TouchKey.KeyStatus=1;
        WM_Invalidate(SystemPrinterWin);
    }

}




