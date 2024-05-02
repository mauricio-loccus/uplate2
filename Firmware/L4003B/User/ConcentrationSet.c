//程序已自检,浓度单位选项，ul不对，位置不准
#include "MainTask.h"


/*
  memcpy(BoardInfTemp.m_dConcentration, BoardInf.dConcentration, sizeof(float) * CALIBRATOR_CONCENTRATION_MAX);//备份浓度float BoardInfTemp.m_dConcentration[CALIBRATOR_CONCENTRATION_MAX];
	m_CurrentUnit=BoardInf.wcCurrentUnit;  //备份浓度单位
*/




const BUTTON_DATA _aButtonConcentrationSet[] =
{
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(3), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Ok", "Ok" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(4), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Back", "Voltar" },

};
const char STR_CONCENT_SET_ERROR[LANGUAGE_TYPES][40] = {"The same concentration is not allowed.", "A mesma concentração nao e permitida."};
const int CONCENTRATIOND_TABLE_CONCENTRATION_START_X[LANGUAGE_TYPES] = {0, 40};


const char STR_CONCENTRATION_TITLE[LANGUAGE_TYPES][32] = {"Set standard concentration", "Concentrações dos Padrões"}; //2015-3-16
const char STR_CONCENTRATION_UNIT[LANGUAGE_TYPES][10] = {"Unit: ", "Unid.："};







WM_HWIN ConcentrationSetWin = NULL;       //检测窗体

//ExpEnable的值定义
enum
{
    EXP_UNIT=1,
    EXP_CONCENTRATION,
    //EXP_CONC,
};
static unsigned char ExpEnable;



//static float m_dConcentration[CALIBRATOR_CONCENTRATION_MAX];
signed char  m_CurrentUnit;
signed char m_CurrentConcentration;


//QUALITY_PARA QualityParaBack;


//浓度有相同返回false
unsigned char GetConcentrationStatus(void)
{
    unsigned char i,j;


    for(i = 0; i < CALIBRATOR_CONCENTRATION_MAX; i++)
    {
        for(j = i + 1; j < CALIBRATOR_CONCENTRATION_MAX; j++)
        {
            if( (BoardInfTemp.dConcentration[i] == BoardInfTemp.dConcentration[j])&&(BoardInfTemp.dConcentration[i]>CONCENTRATION_VALUE_MIN))
            {
                return 0;//false;
            }
        }
    }
    return 1;//true;
}

void DisplayExpandUnit(void)
{
    unsigned char i;
    GUI_RECT rect;

    unsigned short start_x, start_y, wide, high;




    GUI_SetFont(GUI_FONT_BIG_CH);



    start_x = ANALYSIS_FILTER_SELECT_START_X - CONCENTRATION_UNIT_SEL_WIDTH; //2014-8-18项
    start_y = ANALYSIS_FILTER_SELECT_START_Y-TITLESBAR_HEIGHT;
    wide = CONCENTRATION_UNIT_SEL_UNIT_WIDTH;
    high = 46;
//	GUI_DrawBitmap(&bmExpMenuLeft_403_46, start_x, start_y);
    GUI_DrawBitmap(&bmExpMenuLeft_20_46, start_x-20, start_y);
    GUI_SetColor(COLOR_EXP_PICTURE_FRAME);
    GUI_DrawLine(start_x, start_y,start_x+403,start_y);
    GUI_DrawLine(start_x, start_y+45,start_x+403,start_y+45);
    GUI_SetColor(COLOR_EXP_PICTURE);
    GUI_FillRect(start_x, start_y,start_x+403,start_y+45);


    GUI_SetColor(0xeff0cc);
    for(i = 0; i < CALIBRATOR_CONCENTRATION_UNIT_MAX; i++)
    {
        if(STR_CONCENTRATION_SELECT_UNIT[i][0] == 0)
        {
            strcpy(ConvertStr,STR_OFF[SystemPrameter.SystemLanguage]);
        }
        else
        {
            strcpy(ConvertStr,STR_CONCENTRATION_SELECT_UNIT[i]);//lugj modify 171207
        }

        rect.x0 = start_x;
        rect.y0 = start_y - 1;
        rect.x1 = start_x + wide;
        rect.y1 = start_y + high;
        if(m_CurrentUnit == i)
        {
            GUI_SetColor(COLOR_SHAKE_TIME_BK);
            GUI_FillRect(rect.x0, rect.y0+10, rect.x1, rect.y1-10);
            GUI_SetColor(GUI_WHITE);
        }
        else
        {
            GUI_SetColor(GUI_WHITE);
        }
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
        /*  if(i<=4)
        	{
        		if(i==0)GUI_DrawLine(rect.x0+32,rect.y0+28,rect.x0+32,rect.y0+33);
        		else if(i==4)GUI_DrawLine(rect.x0+33,rect.y0+28,rect.x0+33,rect.y0+33);
        		else GUI_DrawLine(rect.x0+35,rect.y0+28,rect.x0+35,rect.y0+33); //ul下方加点 //30 15偏左上 rect.x0+35,rect.y0+30,rect.x0+35,rect.y0+35 第1个右偏2个点
        	}*/
        start_x += wide;
    }
    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        GUI_SetFont(GUI_FONT_BIG);
    }
    else
    {
        GUI_SetFont(GUI_FONT_BIG_CH);
    }

}



void _cbConcentrationSet(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
    WM_HWIN hWinFocus;
    BUTTON_Handle hbutton;
    unsigned char i;
    short        xSize;
    short        ySize;
//	short nSelectRectStartX,	nSelectRectStartY,nRowRectStartX,nRowRectStartY;
    short NCode, Id;
    GUI_RECT rect;

    hWinFocus = WM_GetFocussedWindow();
    //IdWinFocus = WM_GetId(hWinFocus);

    switch (pMsg->MsgId)
    {
    case WM_CREATE:
    {
        for (i = 0; i < GUI_COUNTOF(_aButtonConcentrationSet); i++)
        {
            hbutton = BUTTON_CreateEx(_aButtonConcentrationSet[i].xPos, _aButtonConcentrationSet[i].yPos, _aButtonConcentrationSet[i].xSize, _aButtonConcentrationSet[i].ySize,
                                      hWin, WM_CF_SHOW, 0, ID_CONCENTRATION_BUTTON + i);
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG);
                BUTTON_SetText(hbutton, _aButtonConcentrationSet[i].acLabelEn);
            }
            else
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG_CH);
                BUTTON_SetText(hbutton, _aButtonConcentrationSet[i].acLabelCh);
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
        //GUI_DrawBitmap(&bmMenuRight_120_46, ANALYSIS_FILTER_SELECT_START_X, ANALYSIS_FILTER_SELECT_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(ANALYSIS_FILTER_SELECT_START_X, ANALYSIS_FILTER_SELECT_START_Y- TITLESBAR_HEIGHT,ANALYSIS_FILTER_SELECT_START_X+100, ANALYSIS_FILTER_SELECT_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, ANALYSIS_FILTER_SELECT_START_X+100, ANALYSIS_FILTER_SELECT_START_Y- TITLESBAR_HEIGHT);


        GUI_SetTextMode(GUI_TM_TRANS);

        GUI_SetColor(GUI_WHITE);//GUI_SetColor(COLOR_PAINT_TXT);


        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            GUI_SetFont(GUI_FONT_BIG);
        }
        else
        {
            GUI_SetFont(GUI_FONT_BIG_CH);
        }

        GUI_DispStringAt(STR_CONCENTRATION_TITLE[SystemPrameter.SystemLanguage], CONTENTBAR_CAPTION_POSX, CONTENTBAR_CAPTION_POSY);
				
				
				 GUI_SetColor(GUI_WHITE);

				memset(&ConvertStr, 0, 1000*sizeof(char));
				memset(&StrTemp, 0, 1000*sizeof(char));
        //单位ng/ul
       strcpy(ConvertStr,STR_CONCENTRATION_UNIT[SystemPrameter.SystemLanguage]);
       strcpy(StrTemp,STR_CONCENTRATION_SELECT_UNIT[m_CurrentUnit]);//m_CurrentConcentration
        if(StrTemp[0]==0)
        {
            strcpy(StrTemp,STR_OFF[SystemPrameter.SystemLanguage]);
        }
        strcat(ConvertStr,StrTemp);
        rect.x0=ANALYSIS_FILTER_SELECT_START_X;
        rect.y0=ANALYSIS_FILTER_SELECT_START_Y-TITLESBAR_HEIGHT;
        rect.x1=rect.x0+120;
        rect.y1=rect.y0+46;//+TITLESBAR_HEIGHT;

        //GUI_SetFont(GUI_FONT_BIG_CH);
        
				
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            GUI_SetFont(GUI_FONT_BIG);
        }
        else
        {
            GUI_SetFont(GUI_FONT_BIG_CH);
        }
				GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
			//	GUI_DispStringAt(STR_CONCENTRATION_UNIT[SystemPrameter.SystemLanguage], ANALYSIS_FILTER_SELECT_START_X, ANALYSIS_FILTER_SELECT_START_Y-TITLESBAR_HEIGHT);
        /*
        if(m_CurrentUnit<=4)
        {
        //	if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        	{
        	   if(m_CurrentUnit==0)GUI_DrawLine(rect.x0+85,rect.y0+28,rect.x0+85,rect.y0+33); //ul下方加点
             else if(m_CurrentUnit==4)GUI_DrawLine(rect.x0+86,rect.y0+28,rect.x0+86,rect.y0+33);
             else GUI_DrawLine(rect.x0+87,rect.y0+28,rect.x0+87,rect.y0+33);
        	}
        }*/

        //左边框
        rect.x0 = TABLE_CONCENTRATION1_COLUMN_NO;
        rect.y0 = TABLE_CONCENTRATION_ROW_TITLE_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = rect.x0+278;  //294-17
        rect.y1 = rect.y0+260;
        GUI_SetColor(GUI_GRAY);//ok
        GUI_DrawRect(rect.x0-5, rect.y0-5, rect.x1+5, rect.y1+5);
        GUI_SetColor(COLOR_TITLEBAR);
        GUI_FillRect(rect.x0-2, rect.y0-2, rect.x1+2, rect.y0 + 35);
				GUI_SetColor(GUI_GRAY);
				GUI_DrawLine(0,0, xSize - 1,0);
				GUI_DrawLine(0,CONTENTBAR_TITLE_HEIGHT - 1, xSize - 1,CONTENTBAR_TITLE_HEIGHT - 1);
        //左侧框标题
        GUI_SetColor(GUI_WHITE);//
        GUI_DispStringAt(STR_TABLE_RECORD_NO[SystemPrameter.SystemLanguage],rect.x0,rect.y0+TABLE_CONCENTRATION_TXT_OFFSET_Y);
        GUI_DispStringAt(STR_LAYOUT_CONCENTRATION[SystemPrameter.SystemLanguage],
                         TABLE_CONCENTRATION1_COLUMN_CONCENTRATION + CONCENTRATIOND_TABLE_CONCENTRATION_START_X[SystemPrameter.SystemLanguage]-13,
                         rect.y0+TABLE_CONCENTRATION_TXT_OFFSET_Y);

        //右边框
        rect.x0 = TABLE_CONCENTRATION2_COLUMN_NO;
        rect.y0 = TABLE_CONCENTRATION_ROW_TITLE_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = rect.x0+278;  //294-17
        rect.y1 = rect.y0+260;
        GUI_SetColor(GUI_GRAY);//ok
        GUI_DrawRect(rect.x0-5, rect.y0-5, rect.x1+5, rect.y1+5);
        GUI_SetColor(COLOR_TITLEBAR);
        GUI_FillRect(rect.x0-2, rect.y0-2, rect.x1+2, rect.y0 + 35);
				GUI_SetColor(GUI_GRAY);
				GUI_DrawLine(0,0, xSize - 1,0);
				GUI_DrawLine(0,CONTENTBAR_TITLE_HEIGHT - 1, xSize - 1,CONTENTBAR_TITLE_HEIGHT - 1);
        //右侧框标题
        GUI_SetColor(GUI_WHITE);//
        GUI_DispStringAt(STR_TABLE_RECORD_NO[SystemPrameter.SystemLanguage],rect.x0,rect.y0+TABLE_CONCENTRATION_TXT_OFFSET_Y);
        GUI_DispStringAt(STR_LAYOUT_CONCENTRATION[SystemPrameter.SystemLanguage],
                         TABLE_CONCENTRATION2_COLUMN_CONCENTRATION + CONCENTRATIOND_TABLE_CONCENTRATION_START_X[SystemPrameter.SystemLanguage]-13,
                         rect.y0+TABLE_CONCENTRATION_TXT_OFFSET_Y);

        //3.选中项的背景色
        //3.1位置定义
        rect.x0 = TABLE_CONCENTRATION1_COLUMN_NO  + TABLE_CONCENTRATION_WIDTH * (m_CurrentConcentration/ (CALIBRATOR_CONCENTRATION_MAX / 2));
        rect.y0 = TABLE_CONCENTRATION_ROW_TITLE_START_Y + TABLE_CONCENTRATION_ROW_HEIGHT
                  + (m_CurrentConcentration	% (CALIBRATOR_CONCENTRATION_MAX / 2)) * TABLE_CONCENTRATION_ROW_HEIGHT+2- TITLESBAR_HEIGHT;
        rect.x1 = rect.x0 + TABLE_CONCENTRATION_SELECT_WIDTH;  //294-17
        rect.y1 = rect.y0 + TABLE_CONCENTRATION_SELECT_HEIGHT;

        GUI_SetColor(0x96842c);
        GUI_FillRect(rect.x0-2 , rect.y0-2 , rect.x1+2 , rect.y1+2 );



        for(i = 0; i < CALIBRATOR_CONCENTRATION_MAX; i++)
        {
            GUI_SetColor(GUI_WHITE);
            //No.
            rect.x0  = TABLE_CONCENTRATION1_COLUMN_NO + TABLE_CONCENTRATION_WIDTH * (i/ (CALIBRATOR_CONCENTRATION_MAX / 2));
            rect.y0 = TABLE_CONCENTRATION_ROW_TITLE_START_Y + TABLE_CONCENTRATION_ROW_HEIGHT
                      + (i	% (CALIBRATOR_CONCENTRATION_MAX / 2)) * TABLE_CONCENTRATION_ROW_HEIGHT+2- TITLESBAR_HEIGHT;
            rect.x1 = rect.x0+ TABLE_CONCENTRATION_SELECT_WIDTH;  //294-17
            rect.y1 = rect.y0 + TABLE_CONCENTRATION_SELECT_HEIGHT;

            sprintf(ConvertStr,"%02d",i+1);
            GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);

            if( (ExpEnable == EXP_CONCENTRATION)&&(m_CurrentConcentration==i) )
            {
                GUI_SetColor(0x96842c);
                GUI_FillRect(rect.x0+35, rect.y0 , rect.x1, rect.y1 );
                GUI_SetColor(0xC1b99B);
            }

            if(BoardInfTemp.dConcentration[i]>10000)
            {
                sprintf(ConvertStr,"%.3e",BoardInfTemp.dConcentration[i]);
            }
            else
            {
                sprintf(ConvertStr,"%1.3f",BoardInfTemp.dConcentration[i]);
            }
            //	rect.y1 =rect.y1 -5;
            rect.x0=rect.x0+2;
            rect.x1=rect.x1-2;
            GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_CENTER | GUI_TA_VCENTER);//右对齐，改为中心对齐
        }


        GUI_SetColor(GUI_WHITE);
        if(ExpEnable==EXP_UNIT)
        {
            DisplayExpandUnit();
        }


        break;

    case WM_NOTIFY_PARENT:
    {
        Id = WM_GetId(pMsg->hWinSrc);            // Id of widget
        NCode = pMsg->Data.v;
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
        }		// Notification code
        if (NCode == WM_NOTIFICATION_RELEASED)
        {
            if (Id == ID_CONCENTRATION_BUTTON)   //工具栏第4个按钮  Enter
            {
                if(GetConcentrationStatus())
                {
                    //保存参数
                    BoardInfTemp.wcCurrentUnit=m_CurrentUnit;  //备份浓度单位

                    if(memcmp(&BoardInf.dConcentration,&BoardInfTemp.dConcentration, sizeof(float) * CALIBRATOR_CONCENTRATION_MAX))   //
                    {
                        memcpy(&BoardInf.dConcentration,&BoardInfTemp.dConcentration, sizeof(float) * CALIBRATOR_CONCENTRATION_MAX);  //
                        if(BoardInf.bHasData)
                        {
                            ReportMenu.ReportReady=1;
                        }
                    }

                    //memcpy(BoardInf.dConcentration, BoardInfTemp.dConcentration, sizeof(float) * CALIBRATOR_CONCENTRATION_MAX);//备份浓度

                    WM_DeleteWindow(ConcentrationSetWin);
                    WM_ShowWindow(ProtocolWin);

                    gSystem.SystemInterface = MI_PROTOCOL_LAYOUT;
                    TouchKey.KeyStatus=1;
                    //gSystem.TitleButtonEnable = 1;
                }
                else
                {
                    strcpy(PromptMenu.InputStr,STR_CONCENT_SET_ERROR[SystemPrameter.SystemLanguage]);
                    Prompt_Interface(PROMPT_SAME_NAME);
                }
            }
            else if (Id == ID_CONCENTRATION_BUTTON+1)   //工具栏第5个按钮  Cancel
            {
                WM_DeleteWindow(ConcentrationSetWin);
                WM_ShowWindow(ProtocolWin);
                gSystem.SystemInterface = MI_PROTOCOL_LAYOUT;
                TouchKey.KeyStatus=1;
                //gSystem.TitleButtonEnable = 1;
            }
        }
        break;
    }

    default:
        //		WM_DefaultProc(pMsg);
        break;
    }
}



void ConcentrationSet_Interface(void)
{
    memcpy(BoardInfTemp.dConcentration, BoardInf.dConcentration, sizeof(float) * CALIBRATOR_CONCENTRATION_MAX);//备份浓度
    m_CurrentUnit=BoardInfTemp.wcCurrentUnit;  //备份浓度单位

    m_CurrentConcentration=0;
    ExpEnable=0;
    ConcentrationSetWin = WM_CreateWindowAsChild(CONTENTBAR_POSX, CONTENTBAR_POSY, CONTENTBAR_WIDTH, CONTENTBAR_HEIGHT, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbConcentrationSet, 0);
    WM_BringToTop(ConcentrationSetWin);
}



void ConcentrationSet_Scan(void)
{
    if(TouchKey.KeyStatus==0)
    {
        unsigned char i;

        GUI_RECT rect;
        GUI_PID_STATE TouchState;

        GUI_PID_GetState(&TouchState);
        if (TouchState.Pressed)
        {
            if (ExpEnable==0)  //初使状态，没有弹出扩展项
            {
                //修改单位
                if ((TouchState.x >= ANALYSIS_FILTER_SELECT_START_X) && (TouchState.x <= ANALYSIS_FILTER_SELECT_END_X) &&
                        (TouchState.y >= ANALYSIS_FILTER_SELECT_START_Y) && (TouchState.y <= ANALYSIS_FILTER_SELECT_END_Y))
                {
                    TouchKey.KeyStatus = 1;
                    ExpEnable = EXP_UNIT;
                    WM_Invalidate(ConcentrationSetWin);
                }
                else
                {
                    for(i = 0; i < CALIBRATOR_CONCENTRATION_MAX; i++)
                    {
                        rect.x0 = TABLE_CONCENTRATION1_COLUMN_NO + TABLE_CONCENTRATION_WIDTH * (i / (CALIBRATOR_CONCENTRATION_MAX / 2));
                        rect.y0 = TABLE_CONCENTRATION_ROW_TITLE_START_Y + TABLE_CONCENTRATION_ROW_HEIGHT + (i	% (CALIBRATOR_CONCENTRATION_MAX / 2)) * TABLE_CONCENTRATION_ROW_HEIGHT;

                        rect.x1=rect.x0 + TABLE_CONCENTRATION_SELECT_WIDTH;
                        rect.y1=rect.y0 + TABLE_CONCENTRATION_ROW_HEIGHT ;

                        if(TouchState.x > rect.x0 && TouchState.x< rect.x1 && TouchState.y < rect.y1 && TouchState.y > rect.y0)
                        {
                            TouchKey.KeyStatus=1;
                            if(i == m_CurrentConcentration)
                            {
                                ExpEnable = EXP_CONCENTRATION;
                                TouchKey.KeyStatus = 1;
                                WM_Invalidate(ConcentrationSetWin);
                            }//if(i == m_CurrentConcentration)
                            else
                            {
                                m_CurrentConcentration = i;
                                WM_Invalidate(ConcentrationSetWin);
                            }
                            break;
                        }//if(TouchState.x > rect.x0 && pt.x < TouchState.x1 && TouchState.y < rect.y1 && TouchState.y > rect.y0)
                    }//for(i = 0; i < CALIBRATOR_CONCENTRATION_MAX; i++)
                }
            }//if (ExpEnable==0)
            else if (ExpEnable == EXP_UNIT)//打开
            {
                if ((TouchState.x >= ANALYSIS_FILTER_SELECT_START_X - CONCENTRATION_UNIT_SEL_WIDTH) && (TouchState.x <= ANALYSIS_FILTER_SELECT_START_X) &&
                        (TouchState.y >= ANALYSIS_FILTER_SELECT_START_Y) && (TouchState.y <= ANALYSIS_FILTER_SELECT_END_Y))
                {

                    rect.x0 = ANALYSIS_FILTER_SELECT_START_X - CONCENTRATION_UNIT_SEL_WIDTH;
                    rect.x1=rect.x0 + CONCENTRATION_UNIT_SEL_UNIT_WIDTH;

                    for(i = 0; i < CALIBRATOR_CONCENTRATION_UNIT_MAX; i++)
                    {
                        if(TouchState.x >= rect.x0 && TouchState.x< rect.x1)
                        {
                            m_CurrentUnit = i;
                            break;
                        }
                        rect.x0 +=CONCENTRATION_UNIT_SEL_UNIT_WIDTH;
                        rect.x1 +=CONCENTRATION_UNIT_SEL_UNIT_WIDTH;
                    }
                }
                ExpEnable = 0;
                TouchKey.KeyStatus = 1;
                WM_Invalidate(ConcentrationSetWin);
            }//else if (ExpEnable == EXP_ENABLE)//打开

        }//if (TouchState.Pressed)
    }
}



void ConcentrationSet_Go(void)
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
    }//if (TouchKey.KeyStatus)
    if(ExpEnable == EXP_CONCENTRATION)
    {
        sprintf(KeyPadNum.InputValueStr,"%.3f",BoardInfTemp.dConcentration[m_CurrentConcentration]);
        KeyPadNum_Interface(POINT_MENU_FLAG);
        if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
        {
            BoardInfTemp.dConcentration[m_CurrentConcentration]= atof(KeyPadNum.InputValueStr);
            if(BoardInfTemp.dConcentration[m_CurrentConcentration]>CONCENTRATION_MAX)
            {
                BoardInfTemp.dConcentration[m_CurrentConcentration]=CONCENTRATION_MAX;
            }
            else if(BoardInfTemp.dConcentration[m_CurrentConcentration]<0)
            {
                BoardInfTemp.dConcentration[m_CurrentConcentration]=0;
            }
        }
        ExpEnable =0;
        TouchKey.KeyStatus=1;
        WM_Invalidate(ConcentrationSetWin);
    }
}


