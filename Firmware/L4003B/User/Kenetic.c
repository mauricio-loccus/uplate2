//程序已自检(中文未测)
#include "MainTask.h"
/*
 //Para.
	BoardInfTemp.KineticPara.kinetic_analysis_mode=BoardInf.KineticPara.kinetic_analysis_mode;
	BoardInfTemp.KineticPara.BaseLinePoint=BoardInf.KineticPara.BaseLinePoint;
	BoardInfTemp.KineticPara.BaseLineSel=BoardInf.KineticPara.BaseLineSel;
	BoardInfTemp.KineticPara.EndReadings=BoardInf.KineticPara.EndReadings;
	BoardInfTemp.KineticPara.FirstReadings=BoardInf.KineticPara.FirstReadings;
	BoardInfTemp.KineticPara.Change=BoardInf.KineticPara.Change;
*/

 const char KINETIC_MAIN_TITLE[LANGUAGE_TYPES][30] = {"Kinetic parameters", "Parâmetros da Cinética"};
const char KINETIC_READINGS[LANGUAGE_TYPES][10] = {"Readings", "Leituras"};
const char KINETIC_TYPE[LANGUAGE_TYPES][15] = {"Type", "Tipo"};
const char KINETIC_FIRST_READING[LANGUAGE_TYPES][20] = {"First", "Primeira \nLeitura"};
const char KINETIC_LAST_READING[LANGUAGE_TYPES][20] = {"Last", "Última \nLeitura"};
const char KINETIC_BASELINE[LANGUAGE_TYPES][14] = {"Baseline", "Baseline"};
const char KINETIC_SELECT[LANGUAGE_TYPES][10] = {"select", "(Ref.)"};
const char KINETIC_POINTS[LANGUAGE_TYPES][10] = {"points", "(Pontos)"};
const char KINETIC_CHANGE[LANGUAGE_TYPES][10] = {"Change", "Gradiente"};






const char KINETIC_ANALYSIS_SELECTION[2][LANGUAGE_TYPES][KINETIC_ANALYSIS_MAX][20]
= {{{"Average", "Max.", "Time to", "Time to", "Max.", "Time to"}
        ,{"Taxa", "Taxa", "Tempo de", "Tempo de", "Conc. Máx.", "Tempo de"} 
    }
    , {{"rate", "rate", "max. rate", "change", "of well", "max."}
        , {"Média", "Máx.", "Taxa Máx.", "mudança", "de Poço", "Conc. Máx."}
    }
};

const char KINETIC_ANALYSIS_BASELINE[LANGUAGE_TYPES][2][15]
= {{"End", "Begin"}, {"Fim", "Início"}}; //"Beginning"


//BUTTON_Handle ProtocolMeasureButton[2];




const BUTTON_DATA _aButtonProtocolKinetic[] =
{
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(3), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Ok", "Ok" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(4), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Back", "Voltar" },

};


//const int KINETIC_TYPE_SEL_WIDTH[6]={70, 45, 75, 65, 60, 64};
const int KINETIC_TYPE_SEL_WIDTH[LANGUAGE_TYPES][KINETIC_ANALYSIS_MAX] = {{70, 45, 75, 65, 60, 64}
    ,{55, 50, 100, 100, 100, 110}
};




//ExpEnable的值定义
enum
{
    EXP_TYPE=1,
    EXP_START_READINGS,
    EXP_END_READINGS,
    EXP_BASE_LINE_SEL,
    EXP_BASE_LINE_POINT,
    EXP_CHANGE,
};
static unsigned char ExpEnable;


//signed char Filter1Locate;               //第1个滤光片
//signed char Filter2Locate;               //辐滤光片
//unsigned char DetectMode;                //检测模式

WM_HWIN ProtocolKineticWin = NULL;       //检测窗体




void DisplayTypeExpand(void)
{
    GUI_RECT rect;

    unsigned char i;
    short start_x, start_y, wide;
    start_x = FILTER_1_EXPAND_START_X;
    start_y = FILTER_1_EXPAND_START_Y - TITLESBAR_HEIGHT;
    //wide = KINETIC_TYPE_SEL_WIDTH[0]; //43  39+3=42
    //high = 11; //46
    //GUI_DrawBitmap(&bmExpMenuRight_400_46, FILTER_1_EXPAND_START_X, FILTER_1_EXPAND_START_Y - TITLESBAR_HEIGHT);
    GUI_SetColor(COLOR_EXP_PICTURE_FRAME);
    GUI_DrawLine(start_x, start_y,start_x+530,start_y);
    GUI_DrawLine(start_x, start_y+45,start_x+530,start_y+45);
    GUI_SetColor(COLOR_EXP_PICTURE);
    GUI_FillRect(start_x, start_y,start_x+530,start_y+45);
    GUI_DrawBitmap(&bmExpMenuRight_20_46, start_x+530, start_y);

    start_x += 3;


    for (i = 0; i<KINETIC_ANALYSIS_MAX; i++)
    {
        wide = KINETIC_TYPE_SEL_WIDTH[SystemPrameter.SystemLanguage][i];

        if (i == BoardInfTemp.KineticPara.kinetic_analysis_mode)  //选中的扩展项
        {
            //填充选中的底色
            GUI_SetColor(COLOR_FILTER_SEL_BK);
            GUI_FillRect(start_x, start_y + 3, start_x + wide, start_y + 43);


            //填充选中的文字-白色
            GUI_SetColor(COLOR_FILTER_SEL_TXT);

        }//if (i == BoardInf.Filter1Locate && FilterLun.Filter[i]!=0)  //选中的扩展项
        else
        {
            //填充选中文字的底色
            GUI_SetColor(COLOR_FILTER_NUM_BK);
        }

        rect.x0 = start_x;
        rect.x1 = start_x + wide;
        rect.y0 = start_y+2;
        rect.y1 = start_y + 19;
        GUI_DispStringInRect(KINETIC_ANALYSIS_SELECTION[0][SystemPrameter.SystemLanguage][i], &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);//"off"



        rect.y0 = start_y + 19;
        rect.y1 = start_y + 39;
        GUI_DispStringInRect(KINETIC_ANALYSIS_SELECTION[1][SystemPrameter.SystemLanguage][i], &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);

        start_x += KINETIC_TYPE_SEL_WIDTH[SystemPrameter.SystemLanguage][i]; //43  39+3=42
    }

}

//DisplayChangeExpand(void)
void DisplayBaseLineExpand(void)
{
    GUI_RECT rect;
    short i;
    short start_x, start_y, wide, high;

    start_x=SPEED_EXPAND_START_X  +KINETIC_PARA_POS_START;
    start_y = FILTER_1_R_START_Y - TITLESBAR_HEIGHT;
    wide = MODE_EXPAND_WIDTH1;
    high = 40;
    //GUI_DrawBitmap(&bmExpMenuRight_135_46, start_x, start_y);
    GUI_SetColor(COLOR_EXP_PICTURE_FRAME);
    GUI_DrawLine(start_x, start_y,start_x+115,start_y);
    GUI_DrawLine(start_x, start_y+45,start_x+115,start_y+45);
    GUI_SetColor(COLOR_EXP_PICTURE);
    GUI_FillRect(start_x, start_y,start_x+115,start_y+45);
    GUI_DrawBitmap(&bmExpMenuRight_20_46, start_x+115, start_y);

    start_x += 3;
    start_y += 3;
    for (i = 0; i<2; i++)
    {
        //填充选中的底色
        GUI_SetColor(COLOR_MODE_SEL_BK);
        if (i == 0)
        {
            strcpy(ConvertStr, KINETIC_ANALYSIS_BASELINE[SystemPrameter.SystemLanguage][0]);//"Begin"
        }
        else
        {
            strcpy(ConvertStr,KINETIC_ANALYSIS_BASELINE[SystemPrameter.SystemLanguage][1] );//"End"
        }

        //填充选中的文字-白色

        if(BoardInfTemp.KineticPara.BaseLineSel == i)
        {
            GUI_FillRect(start_x+3, start_y+3, start_x +3+ wide, start_y-3+high);
            GUI_SetColor(COLOR_MODE_SEL_TXT);
            //GUI_DrawCircle(RUNMENU_CIRCLE_POSX(i), RUNMENU_CIRCLE_POSY, RUNMENU_CIRCLE_RADIUS);
        }

        rect.x0 = start_x;
        rect.y0 = start_y - 1;
        rect.x1 = start_x + wide;
        rect.y1 = start_y + high;

        start_x += wide;
        wide = MODE_EXPAND_WIDTH2;

        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    }


}

//修正读数
void ChangeReadingsTemp(void)
{
    if(BoardInfTemp.KineticPara.FirstReadings>=BoardInfTemp.KineticPara.Readings)//if(kinetic_para.kinetic_first_readings >= kinetic_para.kinetic_readings)
    {
        if(BoardInfTemp.KineticPara.Readings==0)
        {
            BoardInfTemp.KineticPara.FirstReadings=BoardInfTemp.KineticPara.Readings;
        }
        else
        {
            BoardInfTemp.KineticPara.FirstReadings = BoardInfTemp.KineticPara.Readings;
        }
    }
    else
    {
        if(BoardInfTemp.KineticPara.Readings==0)
        {
            BoardInfTemp.KineticPara.FirstReadings=BoardInfTemp.KineticPara.Readings;
        }
        else if(BoardInfTemp.KineticPara.FirstReadings==0)
        {
            BoardInfTemp.KineticPara.FirstReadings = 1;
        }
    }
    if(BoardInfTemp.KineticPara.EndReadings>=BoardInfTemp.KineticPara.Readings)//if(kinetic_para.kinetic_first_readings >= kinetic_para.kinetic_readings)
    {
        if(BoardInfTemp.KineticPara.Readings==0)
        {
            BoardInfTemp.KineticPara.EndReadings=BoardInfTemp.KineticPara.Readings;
        }
        else
        {
            BoardInfTemp.KineticPara.EndReadings = BoardInfTemp.KineticPara.Readings;
        }
    }
    else
    {
        if(BoardInfTemp.KineticPara.Readings==0)
        {
            BoardInfTemp.KineticPara.EndReadings=BoardInfTemp.KineticPara.Readings;
        }
        else if(BoardInfTemp.KineticPara.EndReadings==0)
        {
            BoardInfTemp.KineticPara.EndReadings = 1;
        }
    }
    if(BoardInfTemp.KineticPara.EndReadings <=BoardInfTemp.KineticPara.FirstReadings)
    {
        BoardInfTemp.KineticPara.EndReadings = BoardInfTemp.KineticPara.FirstReadings;
    }
    //基线点数
    if(BoardInfTemp.KineticPara.BaseLinePoint >BoardInfTemp.KineticPara.EndReadings-BoardInfTemp.KineticPara.FirstReadings+1)
    {
        BoardInfTemp.KineticPara.BaseLinePoint = BoardInfTemp.KineticPara.EndReadings-BoardInfTemp.KineticPara.FirstReadings+1;//BoardInf.KineticPara.nPoints
    }

    //if(BoardInf.KineticPara.EndReadings >=BoardInfTemp.KineticPara.Readings)
    //{
    //        BoardInf.KineticPara.EndReadings = BoardInfTemp.KineticPara.Readings - BoardInf.KineticPara.FirstReadings - 1;
    //}

//	BoardInf.KineticPara.FirstReadings +

    //if(BoardInf.KineticPara.BaseLinePoint >BoardInfTemp.KineticPara.Readings- BoardInf.KineticPara.FirstReadings - BoardInf.KineticPara.EndReadings)
    //{
    //      BoardInf.KineticPara.BaseLinePoint = BoardInfTemp.KineticPara.Readings- BoardInf.KineticPara.FirstReadings -BoardInf.KineticPara.EndReadings;//BoardInf.KineticPara.nPoints
//	}
}




void _cbProtocolKinetic(WM_MESSAGE * pMsg)
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
    //IdWinFocus = WM_GetId(hWinFocus);

    switch (pMsg->MsgId)
    {
    case WM_CREATE:
    {
        for (i = 0; i < GUI_COUNTOF(_aButtonProtocolKinetic); i++)
        {
            hbutton = BUTTON_CreateEx(_aButtonProtocolKinetic[i].xPos, _aButtonProtocolKinetic[i].yPos, _aButtonProtocolKinetic[i].xSize, _aButtonProtocolKinetic[i].ySize,
                                      hWin, WM_CF_SHOW, 0, ID_KINETIC_BUTTON + i);
            // BUTTON_SetText(hbutton, _aButtonProtocolKinetic[i].acLabelEn);
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG);
                BUTTON_SetText(hbutton, _aButtonProtocolKinetic[i].acLabelEn);
            }
            else
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG_CH);
                BUTTON_SetText(hbutton, _aButtonProtocolKinetic[i].acLabelCh);
            }
            if( (BoardInfTemp.KineticPara.Enable==0)&&(i==0) )
            {
                //BUTTON_SetState(hbutton,BUTTON_CI_DISABLED);
                WM_DisableWindow(hbutton);
            }
            BUTTON_SetTextAlign(hbutton, GUI_TA_HCENTER | GUI_TA_VCENTER);
            BUTTON_SetFocussable(hbutton, 0);

            //else
            //{
            //BUTTON_SetState(hbutton,BUTTON_CI_UNPRESSED);
            //}
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
        GUI_DrawBitmap(&bmMenuLeft_101_46, MODE_START_X,     MODE_START_Y - TITLESBAR_HEIGHT);

        //GUI_DrawBitmap(&bmMenuRight_90_46, FILTER_1_R_START_X, FILTER_1_R_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(FILTER_1_R_START_X, FILTER_1_R_START_Y- TITLESBAR_HEIGHT,FILTER_1_R_START_X+100, FILTER_1_R_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, FILTER_1_R_START_X+100, FILTER_1_R_START_Y- TITLESBAR_HEIGHT);


        GUI_DrawBitmap(&bmMenuRight_90_46, FILTER_2_R_START_X, FILTER_2_R_START_Y - TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmMenuRight_90_46, MODE_R_START_X, MODE_START_Y - TITLESBAR_HEIGHT);



        GUI_DrawBitmap(&bmMenuLeft_101_46, FILTER_1_START_X+KINETIC_PARA_POS_START, FILTER_1_START_Y - TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmMenuLeft_101_46, FILTER_2_START_X+KINETIC_PARA_POS_START, FILTER_2_START_Y - TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmMenuLeft_101_46, MODE_START_X+KINETIC_PARA_POS_START,     MODE_START_Y - TITLESBAR_HEIGHT);




        GUI_DrawBitmap(&bmMenuRight_90_46, FILTER_1_R_START_X+KINETIC_PARA_POS_START, FILTER_1_R_START_Y - TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmMenuRight_90_46, FILTER_2_R_START_X+KINETIC_PARA_POS_START, FILTER_2_R_START_Y - TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmMenuRight_90_46, MODE_R_START_X+KINETIC_PARA_POS_START, MODE_START_Y - TITLESBAR_HEIGHT);


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

        GUI_DispStringAt(KINETIC_MAIN_TITLE[SystemPrameter.SystemLanguage], CONTENTBAR_CAPTION_POSX, CONTENTBAR_CAPTION_POSY);




        rect.x0 = FILTER_1_START_X+20;
        rect.y0 = FILTER_1_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = FILTER_1_END_X;
        rect.y1 = FILTER_1_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(KINETIC_TYPE[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Type "

        rect.y0 = FILTER_2_START_Y - TITLESBAR_HEIGHT;
        rect.y1 = FILTER_2_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(KINETIC_FIRST_READING[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"First"

        //else if ((TouchState.x >= KINETIC_READINGS_START + KINETIC_PARA_POS_START) && (TouchState.x <= KINETIC_READINGS_START + KINETIC_READINGS_WIDTH + KINETIC_PARA_POS_START) &&
        //(TouchState.y >= FILTER_2_START_Y) && (TouchState.y <= FILTER_2_R_END_Y)&&(BoardInfTemp.KineticPara.kinetic_analysis_mode==KINETIC_ANALYSIS_TIME_CHANGE) )
        //{



        rect.y0 = MODE_START_Y - TITLESBAR_HEIGHT;
        rect.y1 = MODE_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(KINETIC_LAST_READING[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Last"


        rect.x0 = FILTER_1_R_START_X + 10;
        rect.y0 = FILTER_1_R_START_Y - TITLESBAR_HEIGHT-2;
        rect.x1 = FILTER_1_R_END_X+40;
        rect.y1 = FILTER_1_R_END_Y-22 - TITLESBAR_HEIGHT;
        //Type的具体参数
        GUI_DispStringInRect(KINETIC_ANALYSIS_SELECTION[0][SystemPrameter.SystemLanguage][BoardInfTemp.KineticPara.kinetic_analysis_mode], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Change Time"
        rect.y0 = rect.y1;
        rect.y1=FILTER_1_R_END_Y - TITLESBAR_HEIGHT-2;
        GUI_DispStringInRect(KINETIC_ANALYSIS_SELECTION[1][SystemPrameter.SystemLanguage][BoardInfTemp.KineticPara.kinetic_analysis_mode], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);


        ///First Readings的具体参数
        rect.y0 = FILTER_2_START_Y - TITLESBAR_HEIGHT;
        rect.y1 = FILTER_2_END_Y - TITLESBAR_HEIGHT;
        sprintf(ConvertStr,"%d",BoardInfTemp.KineticPara.FirstReadings);
        if(ExpEnable == EXP_START_READINGS)
        {
            GUI_SetColor(COLOR_SHAKE_TIME_BK);
            GUI_FillRect(rect.x0-5, rect.y0+10, rect.x0+66, rect.y1-10);
            GUI_SetColor(GUI_WHITE);
        }
        else
        {
            GUI_SetColor(COLOR_PAINT_TXT);
        }
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);


        ///Last Readings的具体参数
        rect.y0 = MODE_START_Y - TITLESBAR_HEIGHT;
        rect.y1 = MODE_END_Y - TITLESBAR_HEIGHT;
        if(ExpEnable == EXP_END_READINGS)
        {
            GUI_SetColor(COLOR_SHAKE_TIME_BK);
            GUI_FillRect(rect.x0-5, rect.y0+10, rect.x0+66, rect.y1-10);
            GUI_SetColor(GUI_WHITE);
        }
        else
        {
            GUI_SetColor(COLOR_PAINT_TXT);
        }
        sprintf(ConvertStr,"%d",BoardInfTemp.KineticPara.EndReadings);
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);



        if(BoardInfTemp.KineticPara.kinetic_analysis_mode==KINETIC_ANALYSIS_TIME_CHANGE)
        {
            GUI_SetColor(COLOR_PAINT_TXT);
        }
        else
        {
            GUI_SetColor(COLOR_TXT_DISABLE);
        }

        rect.x0 = FILTER_1_START_X+10+KINETIC_PARA_POS_START;
        rect.y0 = FILTER_1_START_Y - TITLESBAR_HEIGHT-2;
        rect.x1 = FILTER_1_END_X+KINETIC_PARA_POS_START;
        rect.y1 = FILTER_1_END_Y - TITLESBAR_HEIGHT-22;

        GUI_DispStringInRect(KINETIC_BASELINE[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Baseline "


        rect.y0=rect.y1;
        rect.y1= FILTER_1_END_Y - TITLESBAR_HEIGHT-2;
        GUI_DispStringInRect(KINETIC_SELECT[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Select "

        rect.y0 = FILTER_2_START_Y - TITLESBAR_HEIGHT-2;
        rect.y1 = FILTER_2_END_Y - TITLESBAR_HEIGHT-22;
        GUI_DispStringInRect(KINETIC_BASELINE[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Baseline "

        rect.y0=rect.y1;
        rect.y1= FILTER_2_END_Y - TITLESBAR_HEIGHT-2;
        GUI_DispStringInRect(KINETIC_POINTS[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Point"

        rect.y0 = MODE_START_Y - TITLESBAR_HEIGHT;
        rect.y1 = MODE_END_Y - TITLESBAR_HEIGHT;
        GUI_DispStringInRect(KINETIC_CHANGE[SystemPrameter.SystemLanguage], &rect, GUI_TA_LEFT | GUI_TA_VCENTER);//"Change"

        rect.x0 = FILTER_1_START_X+110+KINETIC_PARA_POS_START;
        rect.y0 = FILTER_1_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = FILTER_1_END_X+110+KINETIC_PARA_POS_START;
        rect.y1 = FILTER_1_END_Y - TITLESBAR_HEIGHT;
        strcpy(ConvertStr,KINETIC_ANALYSIS_BASELINE[SystemPrameter.SystemLanguage][BoardInfTemp.KineticPara.BaseLineSel]);
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);

        rect.y0 = FILTER_2_START_Y - TITLESBAR_HEIGHT;
        rect.y1 = FILTER_2_END_Y - TITLESBAR_HEIGHT;
        if(ExpEnable == EXP_BASE_LINE_POINT)
        {
            GUI_SetColor(COLOR_SHAKE_TIME_BK);
            GUI_FillRect(rect.x0-5, rect.y0+10, rect.x0+66, rect.y1-10);
            GUI_SetColor(GUI_WHITE);
        }
        //else
        //	{
        //GUI_SetColor(COLOR_PAINT_TXT);
        //}
        sprintf(ConvertStr,"%d",BoardInfTemp.KineticPara.BaseLinePoint);
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);

        rect.y0 = MODE_START_Y - TITLESBAR_HEIGHT;
        rect.y1 = MODE_END_Y - TITLESBAR_HEIGHT;
        //if(( (BoardInfTemp.KineticPara.Change<1000)&&(BoardInfTemp.KineticPara.Change>0.01 )   ) ||
        //	((BoardInfTemp.KineticPara.Change > -CONCENTRATION_VALUE_MIN) && (BoardInfTemp.KineticPara.Change < CONCENTRATION_VALUE_MIN)) )
        if(((BoardInfTemp.KineticPara.Change < 1000.0f && BoardInfTemp.KineticPara.Change > 0.01f) ||
                (BoardInfTemp.KineticPara.Change > -CONCENTRATION_VALUE_MIN && BoardInfTemp.KineticPara.Change < CONCENTRATION_VALUE_MIN)))
        {
            sprintf(ConvertStr,"%1.3f",BoardInfTemp.KineticPara.Change);
        }
        else
        {
            sprintf(ConvertStr,"%.3e",BoardInfTemp.KineticPara.Change);
            EConvert(ConvertStr);
        }
        if(ExpEnable == EXP_CHANGE)
        {
            GUI_SetColor(COLOR_SHAKE_TIME_BK);
            GUI_FillRect(rect.x0-5, rect.y0+10, rect.x0+66, rect.y1-10);
            GUI_SetColor(GUI_WHITE);
        }
        //else
        //{
        //GUI_SetColor(COLOR_PAINT_TXT);
        //}
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);


        if (ExpEnable==EXP_TYPE)
        {
            DisplayTypeExpand();
        }
        else if (ExpEnable == EXP_BASE_LINE_SEL)
        {
            DisplayBaseLineExpand();
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
            if (Id == ID_KINETIC_BUTTON)   //工具栏第4个按钮  Enter
            {
                //保存参数

                if(BoardInfTemp.KineticPara.FirstReadings>0)BoardInfTemp.KineticPara.FirstReadings-=1;
                if(BoardInfTemp.KineticPara.EndReadings>0)BoardInfTemp.KineticPara.EndReadings-=1;
                ChangeReadings();


                if(memcmp(&BoardInf,&BoardInfTemp, sizeof(BOARD_INF)))   //板信息已修改
                {
                    memcpy(&BoardInf, &BoardInfTemp,sizeof(BOARD_INF));  //程序拷贝
                    if(BoardInf.bHasData)
                    {
                        ReportMenu.ReportReady=1;
                        LanguageChange.Report=1;
                    }
                }
                BoardInf.KineticPara.kinetic_analysis_mode=BoardInfTemp.KineticPara.kinetic_analysis_mode;
                BoardInf.KineticPara.FirstReadings=BoardInfTemp.KineticPara.FirstReadings;
                BoardInf.KineticPara.EndReadings=BoardInfTemp.KineticPara.EndReadings;
                BoardInf.KineticPara.BaseLineSel=BoardInfTemp.KineticPara.BaseLineSel;
                BoardInf.KineticPara.BaseLinePoint=BoardInfTemp.KineticPara.BaseLinePoint;
                BoardInf.KineticPara.Change=BoardInfTemp.KineticPara.Change;

                WM_DeleteWindow(ProtocolKineticWin);
                WM_ShowWindow(ProtocolWin);
                //gSystem.MenuRefreshFlag = 1;
                gSystem.SystemInterface = MI_PROTOCOL_CALCULATE;
                TouchKey.KeyStatus=1;
                //gSystem.TitleButtonEnable = 1;
            }
            else if (Id == ID_KINETIC_BUTTON+1)                          //工具栏第5个按钮  Cancel
            {
                //还原数据
                /*
                 	BoardInfTemp.KineticPara.kinetic_analysis_mode=BoardInf.KineticPara.kinetic_analysis_mode;
                BoardInfTemp.KineticPara.BaseLinePoint=BoardInf.KineticPara.BaseLinePoint;
                BoardInfTemp.KineticPara.BaseLineSel=BoardInf.KineticPara.BaseLineSel;
                BoardInfTemp.KineticPara.EndReadings=BoardInf.KineticPara.EndReadings;
                BoardInfTemp.KineticPara.FirstReadings=BoardInf.KineticPara.FirstReadings;
                BoardInfTemp.KineticPara.Change=BoardInf.KineticPara.Change;
                */
                WM_DeleteWindow(ProtocolKineticWin);
                WM_ShowWindow(ProtocolWin);
                gSystem.SystemInterface = MI_PROTOCOL_CALCULATE;
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

void ProtocolKenetic_Interface(void)
{
    //读取参数
    gSystem.SystemInterface = MI_PROTOCOL_KINETIC;

    BoardInfTemp.KineticPara.kinetic_analysis_mode=BoardInf.KineticPara.kinetic_analysis_mode;
    BoardInfTemp.KineticPara.BaseLinePoint=BoardInf.KineticPara.BaseLinePoint;
    BoardInfTemp.KineticPara.BaseLineSel=BoardInf.KineticPara.BaseLineSel;
    BoardInfTemp.KineticPara.EndReadings=BoardInf.KineticPara.EndReadings;
    BoardInfTemp.KineticPara.FirstReadings=BoardInf.KineticPara.FirstReadings;
    BoardInfTemp.KineticPara.Change=BoardInf.KineticPara.Change;

    BoardInfTemp.KineticPara.FirstReadings+=1;
    BoardInfTemp.KineticPara.EndReadings+=1;
    ChangeReadingsTemp();

    ProtocolKineticWin = WM_CreateWindowAsChild(CONTENTBAR_POSX, CONTENTBAR_POSY, CONTENTBAR_WIDTH, CONTENTBAR_HEIGHT, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbProtocolKinetic, 0);
    WM_BringToTop(ProtocolKineticWin);
}

void ProtocolKenetic_Scan(void)
{
    if(TouchKey.KeyStatus==0)
    {
        unsigned char i;
        GUI_PID_STATE TouchState;
        int start_x,wide;

        GUI_PID_GetState(&TouchState);
        if (TouchState.Pressed)
        {
            if (ExpEnable==0)  //初使状态，没有弹出扩展项
            {
                //分析类型
                if ((TouchState.x >= FILTER_1_R_START_X) && (TouchState.x <= FILTER_1_R_END_X) &&
                        (TouchState.y >= FILTER_1_R_START_Y) && (TouchState.y <= FILTER_1_R_END_Y))
                {
                    TouchKey.KeyStatus = 1;
                    ExpEnable = EXP_TYPE;
                    WM_Invalidate(ProtocolKineticWin);
                }
                //First Readings
                else if ((TouchState.x >= KINETIC_READINGS_START) && (TouchState.x <= KINETIC_READINGS_START + KINETIC_READINGS_WIDTH) &&
                         (TouchState.y >= FILTER_2_START_Y) && (TouchState.y <= FILTER_2_END_Y))
                {
                    TouchKey.KeyStatus = 1;
                    ExpEnable = EXP_START_READINGS;
                    WM_Invalidate(ProtocolKineticWin);
                }
                //Last Readings
                else if ((TouchState.x >= KINETIC_READINGS_START) && (TouchState.x <= KINETIC_READINGS_START + KINETIC_READINGS_WIDTH) &&
                         (TouchState.y >= MODE_START_Y) && (TouchState.y <= MODE_END_Y))
                {
                    TouchKey.KeyStatus = 1;
                    ExpEnable = EXP_END_READINGS;
                    WM_Invalidate(ProtocolKineticWin);
                }
                //基线选择
                else if ((TouchState.x >= FILTER_1_R_START_X+KINETIC_PARA_POS_START) && (TouchState.x <= FILTER_1_R_END_X+KINETIC_PARA_POS_START) &&
                         (TouchState.y >= FILTER_1_R_START_Y) && (TouchState.y <= FILTER_1_R_END_Y)&&(BoardInfTemp.KineticPara.kinetic_analysis_mode==KINETIC_ANALYSIS_TIME_CHANGE))
                {
                    TouchKey.KeyStatus = 1;
                    ExpEnable = EXP_BASE_LINE_SEL;
                    WM_Invalidate(ProtocolKineticWin);
                }
                //基线点数
                else if ((TouchState.x >= KINETIC_READINGS_START + KINETIC_PARA_POS_START) && (TouchState.x <= FILTER_1_R_END_X+KINETIC_PARA_POS_START) &&
                         (TouchState.y >= FILTER_2_START_Y) && (TouchState.y <= FILTER_2_R_END_Y)&&(BoardInfTemp.KineticPara.kinetic_analysis_mode==KINETIC_ANALYSIS_TIME_CHANGE) )
                {
                    TouchKey.KeyStatus = 1;
                    ExpEnable = EXP_BASE_LINE_POINT;
                    WM_Invalidate(ProtocolKineticWin);
                }
                //Change
                else if ((TouchState.x >= KINETIC_READINGS_START + KINETIC_PARA_POS_START) && (TouchState.x <= FILTER_1_R_END_X+KINETIC_PARA_POS_START) &&
                         (TouchState.y >= MODE_START_Y) && (TouchState.y <= MODE_END_Y)&&(BoardInfTemp.KineticPara.kinetic_analysis_mode==KINETIC_ANALYSIS_TIME_CHANGE) )
                {
                    TouchKey.KeyStatus = 1;
                    ExpEnable = EXP_CHANGE;
                    WM_Invalidate(ProtocolKineticWin);
                }
            }
            else if (ExpEnable == EXP_TYPE)//分析类型
            {
                if ((TouchState.x >= KINETIC_TYPE_EXPAND_START_X) && (TouchState.x <= KINETIC_TYPE_EXPAND_END_X) &&
                        (TouchState.y >= KINETIC_TYPE_EXPAND_START_Y) && (TouchState.y <= KINETIC_TYPE_EXPAND_END_Y))
                {
                    start_x=KINETIC_TYPE_EXPAND_START_X;
									
										wide=KINETIC_TYPE_SEL_WIDTH[SystemPrameter.SystemLanguage][0];

                    for (i = 0; i<KINETIC_ANALYSIS_MAX; i++)
                    {
												wide=KINETIC_TYPE_SEL_WIDTH[SystemPrameter.SystemLanguage][i];
                        if ((TouchState.x >= start_x) && (TouchState.x < start_x+wide))
                        {
                            BoardInfTemp.KineticPara.kinetic_analysis_mode=i;
                            break;
                        }

                        start_x+=KINETIC_TYPE_SEL_WIDTH[SystemPrameter.SystemLanguage][i];
											
                    }
                }
                ExpEnable = 0;
                WM_Invalidate(ProtocolKineticWin);

                TouchKey.KeyStatus = 1;
            }//	else if (ExpEnable == EXP_TYPE)//分析类型
            else if (ExpEnable == EXP_BASE_LINE_SEL)  //基线选择扩展
            {
                if ((TouchState.x >= FILTER_1_R_START_X + KINETIC_PARA_POS_START) && (TouchState.x <= FILTER_1_R_START_X+ 45+KINETIC_PARA_POS_START) &&
                        (TouchState.y >= FILTER_1_EXPAND_START_Y) && (TouchState.y <= FILTER_1_EXPAND_END_Y))
                {
                    BoardInfTemp.KineticPara.BaseLineSel=0;//0表示起始点
                }
                else if ((TouchState.x >= FILTER_1_R_START_X + KINETIC_PARA_POS_START+45) && (TouchState.x <= FILTER_1_R_START_X+ 115+KINETIC_PARA_POS_START) &&
                         (TouchState.y >= FILTER_1_EXPAND_START_Y) && (TouchState.y <= FILTER_1_EXPAND_END_Y))
                {
                    BoardInfTemp.KineticPara.BaseLineSel=1;//1表示终止点
                }


                ExpEnable = 0;
                WM_Invalidate(ProtocolKineticWin);

                TouchKey.KeyStatus = 1;
            }//else if (ExpEnable == EXP_BASE_LINE_SEL)  //基线选择扩展
        }//if (TouchState.Pressed)
    }
}


void ProtocolKenetic_Go(void)
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
    //First Readings
    if (ExpEnable == EXP_START_READINGS)
    {
        //数字键盘
        sprintf(KeyPadNum.InputValueStr,"%d",BoardInfTemp.KineticPara.FirstReadings); //kinetic_para_back.nPoints
        KeyPadNum_Interface(NUM_MENUFLAG_2NUM);
        if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
        {
            BoardInfTemp.KineticPara.FirstReadings=atoi(KeyPadNum.InputValueStr);
            ChangeReadingsTemp();
            //if(BoardInfTemp.KineticPara.FirstReadings >= BoardInfTemp.KineticPara.Readings-  BoardInfTemp.KineticPara.EndReadings)
            //{
            //    BoardInfTemp.KineticPara.FirstReadings = BoardInfTemp.KineticPara.Readings-  BoardInfTemp.KineticPara.EndReadings-1;
            // }
            //if(BoardInfTemp.KineticPara.BaseLinePoint> BoardInfTemp.KineticPara.Readings- BoardInfTemp.KineticPara.FirstReadings- BoardInfTemp.KineticPara.EndReadings)
            //{
            //  BoardInfTemp.KineticPara.BaseLinePoint = BoardInfTemp.KineticPara.Readings- BoardInfTemp.KineticPara.FirstReadings- BoardInfTemp.KineticPara.EndReadings;
            // }
        }//if (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)

        ExpEnable = 0;
        TouchKey.KeyStatus = 1;
        WM_Invalidate(ProtocolKineticWin);
    }
    //Last Readings
    else if (ExpEnable == EXP_END_READINGS)
    {
        //数字键盘
        sprintf(KeyPadNum.InputValueStr,"%d",BoardInfTemp.KineticPara.EndReadings); //kinetic_para_back.nPoints
        KeyPadNum_Interface(NUM_MENUFLAG_2NUM);
        if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
        {
            BoardInfTemp.KineticPara.EndReadings=atoi(KeyPadNum.InputValueStr);
            ChangeReadingsTemp();
            //if(BoardInfTemp.KineticPara.EndReadings >= BoardInfTemp.KineticPara.Readings-  BoardInfTemp.KineticPara.FirstReadings)
            //{
            //  BoardInfTemp.KineticPara.EndReadings = BoardInfTemp.KineticPara.Readings-  BoardInfTemp.KineticPara.FirstReadings-1;
            //}
            //if(BoardInfTemp.KineticPara.BaseLinePoint> BoardInfTemp.KineticPara.Readings- BoardInfTemp.KineticPara.FirstReadings - BoardInfTemp.KineticPara.EndReadings)
            // {
            //BoardInfTemp.KineticPara.BaseLinePoint = BoardInfTemp.KineticPara.Readings- BoardInfTemp.KineticPara.FirstReadings - BoardInfTemp.KineticPara.EndReadings;
            // }
        }//if (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)

        ExpEnable = 0;
        TouchKey.KeyStatus = 1;
        WM_Invalidate(ProtocolKineticWin);
    }//else if (ExpEnable == EXP_END_READINGS)

    //基线点数
    else if (ExpEnable == EXP_BASE_LINE_POINT)
    {
        //数字键盘
        sprintf(KeyPadNum.InputValueStr,"%d",BoardInfTemp.KineticPara.BaseLinePoint); //kinetic_para_back.nPoints
        KeyPadNum_Interface(NUM_MENUFLAG_2NUM);
        if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
        {
            BoardInfTemp.KineticPara.BaseLinePoint=atoi(KeyPadNum.InputValueStr);
            ChangeReadingsTemp();
            ///if(BoardInfTemp.KineticPara.BaseLinePoint > BoardInf.KineticPara.Readings- BoardInfTemp.KineticPara.FirstReadings - BoardInfTemp.KineticPara.EndReadings)
            //  {
            //BoardInfTemp.KineticPara.BaseLinePoint = BoardInfTemp.KineticPara.Readings- BoardInfTemp.KineticPara.FirstReadings - BoardInfTemp.KineticPara.EndReadings;
            // }
        }
        ExpEnable = 0;
        TouchKey.KeyStatus = 1;
        WM_Invalidate(ProtocolKineticWin);
    }//else if (ExpEnable == EXP_BASE_LINE_POINT)
    //Change
    else if (ExpEnable == EXP_CHANGE)
    {
        //数字键盘
        sprintf(KeyPadNum.InputValueStr,"%.3f",BoardInfTemp.KineticPara.Change); //kinetic_para_back.dChange
        KeyPadNum_Interface(POINT_MENU_FLAG);
        if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
        {
            BoardInfTemp.KineticPara.Change=atof(KeyPadNum.InputValueStr);
            if(BoardInfTemp.KineticPara.Change>CONCENTRATION_MAX)
            {
                BoardInfTemp.KineticPara.Change=CONCENTRATION_MAX;
            }
            else if(BoardInfTemp.KineticPara.Change<0)
            {
                BoardInfTemp.KineticPara.Change=0;
            }

        }
        ExpEnable = 0;
        TouchKey.KeyStatus = 1;
        WM_Invalidate(ProtocolKineticWin);
    }//else if (ExpEnable == EXP_CHANGE)
}
