//程序已自检(表格不能点)
#include "MainTask.h"

/*
	1.   BoardInf.QualityResult.                      //sys_para.quality_para.
	      	unsigned char Enable; //允许定性分析
	        unsigned char AbsFlag; //采用吸光度

	       float dTarget[2][QC_MAX]; //目标值
	       float dSD[3][QC_MAX]; //3通道 标准偏差
           float dCV[3][QC_MAX]; //3通道
	        float dUpperLimit[2][QC_MAX];//上限
	        float dLowerLimit[2][QC_MAX];//下限
*/

//board_inf.quality_para.nCurrentPage = 0;当前业号(0,1)
//board_inf.quality_para.nCurrentSelectPage在本页中的选择（0-4）
//board_inf.quality_para.nCurrentSelect在所有页的选择（0-9）
//board_inf.quality_para.nCurrentSelect = board_inf.quality_para.nCurrentPage * QC_PAGE_NUMBER
//	+ board_inf.quality_para.nCurrentSelectPage;





const BUTTON_DATA _aButtonProtocolQuality[] =
{
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(3), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Ok", "OK" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(4), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Back", "Voltar" },
};






const short QUALITY_TABLE_TARGET_START_X[LANGUAGE_TYPES] = {0, -5};
const short QUALITY_TABLE_SD_START_X[LANGUAGE_TYPES] = {0, -15};
const short QUALITY_TABLE_CV_START_X[LANGUAGE_TYPES] = {0, -15};






//const char FUNCTION_STATUS[LANGUAGE_TYPES][2][10] = {{_T("Off"), _T("On")}, {_T("关闭"), _T("打开")}, {_T("Off"), _T("On")}, {_T("Off"), _T("On")}};
//const char REFERENCE_SELECT[LANGUAGE_TYPES][2][10] = {{_T("Conc."), _T("ABS")}, {_T("浓度"), _T("吸光度")}, {_T("Conc."), _T("ABS")}, {_T("Conc."), _T("ABS")}};
//const wchar_t QUALITY_RESULT[LANGUAGE_TYPES][2][10] = {{_T("Passed"), _T("Failed")}, {_T("通过"), _T("失败")}, {_T("Passed"), _T("Failed")}, {_T("Passed"), _T("Failed")}}; //2015-3-16


const char QC_SET_ERROR[LANGUAGE_TYPES][50] = {{"The same QC value is not allowed."},{"O mesmo valor de CQ não é permitido."}};

WM_HWIN ProtocolQualityWin = NULL;       //检测窗体

//ExpEnable的值定义
enum
{
    EXP_ENABLE=1,
    EXP_CONC,

    EXP_TABLE_TARGET,
    EXP_TABLE_SD,
};
static unsigned char ExpEnable;

static short nCurrentSelect;
static short nCurrentSelectPage;
static short nCurrentPage;
static short nCurrentSelectBack;


//static QUALITY_PARA BoardInfTemp.QualityPara;





void SetQCPara(void)
{
    signed char i;
    for(i = 0; i < QC_MAX; i++)
    {
        if(BoardInfTemp.QualityPara.dTarget[0][i]!=0)
        {
            BoardInfTemp.QualityPara.dCV[0][i] = BoardInfTemp.QualityPara.dSD[0][i] / BoardInfTemp.QualityPara.dTarget[0][i];
        }
        else BoardInfTemp.QualityPara.dCV[0][i] =0;

        if(BoardInfTemp.QualityPara.dTarget[1][i]!=0)
        {
            BoardInfTemp.QualityPara.dCV[1][i] = BoardInfTemp.QualityPara.dSD[1][i] / BoardInfTemp.QualityPara.dTarget[1][i];
        }
        else BoardInfTemp.QualityPara.dCV[1][i] =0;


        BoardInfTemp.QualityPara.dLowerLimit[0][i] = BoardInfTemp.QualityPara.dTarget[0][i] - BoardInfTemp.QualityPara.dSD[0][i] * QC_COEF;
        BoardInfTemp.QualityPara.dLowerLimit[1][i] = BoardInfTemp.QualityPara.dTarget[1][i] - BoardInfTemp.QualityPara.dSD[1][i] * QC_COEF;

        BoardInfTemp.QualityPara.dUpperLimit[0][i] = BoardInfTemp.QualityPara.dTarget[0][i] + BoardInfTemp.QualityPara.dSD[0][i] * QC_COEF;
        BoardInfTemp.QualityPara.dUpperLimit[1][i] = BoardInfTemp.QualityPara.dTarget[1][i] + BoardInfTemp.QualityPara.dSD[1][i] * QC_COEF;
    }
}




//2015-3-16
unsigned char GetTargetStatus(void)
{
    unsigned char i,j,k;
    for(k = 0; k < 2; k++)  //1表示浓度，0表示吸光度
    {
        for(i = 0; i < QC_MAX; i++)
        {
            if(BoardInfTemp.QualityPara.dSD[k][i] < 0.0f)   //标准偏差<0返回
            {
                break;
            }
            for(j = i + 1; j < QC_MAX; j++)
            {
                if(BoardInfTemp.QualityPara.dSD[k][j] < 0.0f)
                {
                    break;
                }
                if( (BoardInfTemp.QualityPara.dTarget[k][i] == BoardInfTemp.QualityPara.dTarget[k][j])&&(BoardInfTemp.QualityPara.dTarget[k][i] >0) )
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}



void DisplayExpandConc(void)
{
    unsigned char i;
    unsigned short start_x, start_y, wide, high;
    GUI_RECT rect;


    start_x = QUALITY_CONC_EXPAND_START_X;
    start_y = QUALITY_CONC_SELECT_START_Y - TITLESBAR_HEIGHT;
    wide = QUALITY_CONC_WIDTH;
    high = 40;
    //GUI_DrawBitmap(&bmExpMenuLeft_170_46, start_x, start_y);
    GUI_DrawBitmap(&bmExpMenuLeft_20_46, start_x, start_y);
    GUI_SetColor(COLOR_EXP_PICTURE_FRAME);
    GUI_DrawLine(start_x+20, start_y,start_x+170,start_y);
    GUI_DrawLine(start_x+20, start_y+45,start_x+170,start_y+45);
    GUI_SetColor(COLOR_EXP_PICTURE);
    GUI_FillRect(start_x+20, start_y,start_x+170,start_y+45);


    for (i = 0; i<2; i++)
    {
        //填充选中的底色
        GUI_SetColor(COLOR_SHAKE_BK);
        if (i == 0)
        {
            strcpy(ConvertStr, STR_ABS[SystemPrameter.SystemLanguage]);//"Open");
        }
        else
        {
            strcpy(ConvertStr, STR_CONC[SystemPrameter.SystemLanguage]);//CONC
        }

        //填充选中的文字-白色
        if (((BoardInfTemp.QualityPara.AbsFlag) && (i == 0)) || ((BoardInfTemp.QualityPara.AbsFlag==0) && (i == 1)))
        {
            GUI_FillRect(start_x+20, start_y+3, start_x +20+ wide, start_y +3+ high);
            GUI_SetColor(COLOR_SHAKE_TXT);
        }

        rect.x0 = start_x+20;
        rect.y0 = start_y +3;
        rect.x1 = start_x +20+ wide;
        rect.y1 = start_y + high;

        start_x += wide+10;
        wide =QUALITY_CONC_WIDTH;

        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    }


}


void DisplayExpandEnable(void)
{
    unsigned char i;
    unsigned short start_x, start_y, wide, high;
    GUI_RECT rect;


    start_x = QUALITY_OPEN_EXPAND_START_X;
    start_y = QUALITY_OPEN_SELECT_START_Y - TITLESBAR_HEIGHT;
    wide = QUALITY_CONC_WIDTH;
    high = 40;

    //GUI_DrawBitmap(&bmExpMenuLeft_170_46, start_x, start_y);
    GUI_DrawBitmap(&bmExpMenuLeft_20_46, start_x, start_y);
    GUI_SetColor(COLOR_EXP_PICTURE_FRAME);
    GUI_DrawLine(start_x+20, start_y,start_x+170,start_y);
    GUI_DrawLine(start_x+20, start_y+45,start_x+170,start_y+45);
    GUI_SetColor(COLOR_EXP_PICTURE);
    GUI_FillRect(start_x+20, start_y,start_x+170,start_y+45);
    for (i = 0; i<2; i++)
    {
        //填充选中的底色
        GUI_SetColor(COLOR_SHAKE_BK);
        if (i == 0)
        {
            strcpy(ConvertStr, STR_CLOSE[SystemPrameter.SystemLanguage]);//CLOSE
        }
        else
        {
            strcpy(ConvertStr, STR_OPEN[SystemPrameter.SystemLanguage]);//"Open");
        }

        //填充选中的文字-白色
        if (((BoardInfTemp.QualityPara.Enable == 0) && (i == 0)) || ((BoardInfTemp.QualityPara.Enable) && (i == 1)))
        {
            GUI_FillRect(start_x+20, start_y+3, start_x +20+ wide, start_y +3+ high);
            GUI_SetColor(COLOR_SHAKE_TXT);
        }

        rect.x0 = start_x+20;
        rect.y0 = start_y +3;
        rect.x1 = start_x +20 + wide;
        rect.y1 = start_y + high;

        start_x += wide+10;
        wide =QUALITY_CONC_WIDTH;// INTER_SEL_WIDTH;

        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    }


}


void _cbProtocolQuality(WM_MESSAGE * pMsg)
{

    //char str[10];
    WM_HWIN hWin = pMsg->hWin;
//	WM_HWIN hWinFocus;
    BUTTON_Handle hbutton;
    unsigned short i,j;
    short        xSize;
    short        ySize;
    short NCode, Id;
    float temp;
    GUI_RECT rect;

    //char str[10];

    //	int  day_max;
    //hWinFocus = WM_GetFocussedWindow();
//	IdWinFocus = WM_GetId(hWinFocus);

    switch (pMsg->MsgId)
    {

    case WM_CREATE:
    {

        for (i = 0; i < GUI_COUNTOF(_aButtonProtocolQuality); i++)
        {
            hbutton = BUTTON_CreateEx(_aButtonProtocolQuality[i].xPos, _aButtonProtocolQuality[i].yPos, _aButtonProtocolQuality[i].xSize, _aButtonProtocolQuality[i].ySize,
                                      hWin, WM_CF_SHOW, 0, ID_QUALITY_BUTTON + i);
            //BUTTON_SetText(hbutton, _aButtonProtocolQuality[i].acLabelEn);
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG);
                BUTTON_SetText(hbutton, _aButtonProtocolQuality[i].acLabelEn);
            }
            else
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG_CH);
                BUTTON_SetText(hbutton, _aButtonProtocolQuality[i].acLabelCh);
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
        //右侧工具栏(第1个和第2个按扭)
        //GUI_DrawBitmap(&bmMenuRight_120_46, QUALITY_CONC_SELECT_START_X, QUALITY_CONC_SELECT_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(QUALITY_CONC_SELECT_START_X, QUALITY_CONC_SELECT_START_Y- TITLESBAR_HEIGHT,QUALITY_CONC_SELECT_START_X+100, QUALITY_CONC_SELECT_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, QUALITY_CONC_SELECT_START_X+100, QUALITY_CONC_SELECT_START_Y- TITLESBAR_HEIGHT);
        //	GUI_DrawBitmap(&bmMenuRight_120_46, QUALITY_OPEN_SELECT_START_X, QUALITY_OPEN_SELECT_START_Y - TITLESBAR_HEIGHT);
        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(QUALITY_OPEN_SELECT_START_X, QUALITY_OPEN_SELECT_START_Y- TITLESBAR_HEIGHT,QUALITY_OPEN_SELECT_START_X+100, QUALITY_OPEN_SELECT_START_Y- TITLESBAR_HEIGHT+45);
        GUI_DrawBitmap(&bmMenuRight_20_46, QUALITY_OPEN_SELECT_START_X+100, QUALITY_OPEN_SELECT_START_Y- TITLESBAR_HEIGHT);


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
        GUI_DispStringAt(QUALITY_MAIN_TITLE[SystemPrameter.SystemLanguage], CONTENTBAR_CAPTION_POSX, CONTENTBAR_CAPTION_POSY);


        if(BoardInfTemp.QualityPara.Enable==0)
        {
            GUI_SetColor(COLOR_TXT_DISABLE);
        }
        //右侧第1个工具栏(浓度、吸光度)
        rect.x0=QUALITY_CONC_SELECT_START_X;
        rect.y0=QUALITY_CONC_SELECT_START_Y-TITLESBAR_HEIGHT;
        rect.x1=QUALITY_CONC_SELECT_END_X;
        rect.y1=QUALITY_CONC_SELECT_END_Y-TITLESBAR_HEIGHT;
        if(BoardInfTemp.QualityPara.AbsFlag)
        {
            strcpy(ConvertStr,STR_ABS[SystemPrameter.SystemLanguage]);
        }
        else
        {
            strcpy(ConvertStr,STR_CONC[SystemPrameter.SystemLanguage]);
        }
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);


        GUI_SetColor(COLOR_PAINT_TXT);
        //右侧第2个工具栏(On 、Off)
        rect.x0=QUALITY_OPEN_SELECT_START_X;
        rect.y0=QUALITY_OPEN_SELECT_START_Y-TITLESBAR_HEIGHT;
        rect.x1=QUALITY_OPEN_SELECT_END_X;
        rect.y1=QUALITY_OPEN_SELECT_END_Y-TITLESBAR_HEIGHT;
        if(BoardInfTemp.QualityPara.Enable)
        {
            strcpy(ConvertStr,STR_OPEN[SystemPrameter.SystemLanguage]);
        }
        else
        {
            strcpy(ConvertStr,STR_CLOSE[SystemPrameter.SystemLanguage]);
        }
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);


        //画表格的边框
				GUI_SetColor(GUI_GRAY);//GUI_SetColor(0xe1d8ca);//ok
        rect.x0 = TABLE_QUALITY_START_X;
        rect.y0 = TABLE_QUALITY_START_Y - TITLESBAR_HEIGHT;
        rect.x1 =TABLE_QUALITY_END_X;
        rect.y1=TABLE_QUALITY_END_Y - TITLESBAR_HEIGHT;
        GUI_DrawRect(rect.x0, rect.y0, rect.x1, rect.y1);
        //画表格顶行的背景色
        GUI_SetColor(COLOR_TITLEBAR);
        GUI_FillRect(rect.x0 + 2, rect.y0 + 2, rect.x1 - 2, rect.y0 + 35);    //首行
        //画表格翻页图标的背景色
        //GUI_SetColor(COLOR_TOOLSBAR);
       GUI_SetColor(0x3e302b);// GUI_SetColor(0xf4dbb2);
        GUI_FillRect(rect.x0+2, rect.y1-37, rect.x1-2 , rect.y1-2);                //尾行
        GUI_SetColor(GUI_GRAY);
				GUI_DrawLine(0,0, xSize - 1,0);
				GUI_DrawLine(0,CONTENTBAR_TITLE_HEIGHT - 1, xSize - 1,CONTENTBAR_TITLE_HEIGHT - 1);
				
				//画表格线(5条）
        for(i=rect.x0; i<rect.x1;)
        {
            for(j=0; j<5; j++)
            {
                GUI_DrawPoint(i,rect.y0+37*2+37*j);
                GUI_DrawPoint(i+1,rect.y0+37*2+37*j);
                GUI_DrawPoint(i+2,rect.y0+37*2+37*j);
            }
            i=i+5;
        }
        //画表格的翻页图标
        GUI_DrawBitmap(&bmQcTabFirst_P, TABPAGE_LEFT_START_X, TABPAGE_LEFT_START_Y- TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmQcTabPrev_P, TAB_LEFT_START_X, TAB_LEFT_START_Y - TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmQcTabNext_P, TAB_RIGHT_START_X, TAB_RIGHT_START_Y - TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmQcTabEnd_P, TABPAGE_RIGHT_START_X, TABPAGE_RIGHT_START_Y - TITLESBAR_HEIGHT);

        //画表格顶部的文字
        GUI_SetColor(GUI_WHITE);//GUI_SetColor(0xffdddd);//
        rect.x0 = QUALITY_CONTROL_COLUMN_NO ;
        rect.y0 = TABLE_QUALITY_START_Y+QUALITY_ROW_TXT_DIS_Y;
        rect.y0=rect.y0 -TITLESBAR_HEIGHT;
        GUI_DispStringAt(STR_TABLE_RECORD_NO[SystemPrameter.SystemLanguage],rect.x0,rect.y0);
        GUI_DispStringAt(QUALITY_TABLE_TARGET[SystemPrameter.SystemLanguage],
                         QUALITY_CONTROL_COLUMN_TARGET + QUALITY_TABLE_TARGET_START_X[SystemPrameter.SystemLanguage],
                         rect.y0);
        GUI_DispStringAt(QUALITY_TABLE_SD[SystemPrameter.SystemLanguage],
                         QUALITY_CONTROL_COLUMN_SD + QUALITY_TABLE_SD_START_X[SystemPrameter.SystemLanguage],
                         rect.y0);
        GUI_DispStringAt(QUALITY_TABLE_CV[SystemPrameter.SystemLanguage],
                         QUALITY_CONTROL_COLUMN_CV + QUALITY_TABLE_CV_START_X[SystemPrameter.SystemLanguage],
                         rect.y0);
        GUI_DispStringAt(QUALITY_TABLE_UPPER_LIMIT[SystemPrameter.SystemLanguage],
                         QUALITY_CONTROL_COLUMN_UPPER,
                         rect.y0);
        GUI_DispStringAt(QUALITY_TABLE_LOWER_LIMIT[SystemPrameter.SystemLanguage],
                         QUALITY_CONTROL_COLUMN_LOWER,
                         rect.y0);



        if(nCurrentSelect>= QC_MAX ||  nCurrentSelect<0) // //只有九个质控品
        {
            nCurrentSelect=0;
        }
        nCurrentPage = nCurrentSelect / QC_PAGE_NUMBER;
        nCurrentSelectPage = nCurrentSelect % QC_PAGE_NUMBER;

        //质控打开时的绘制
        if(BoardInfTemp.QualityPara.Enable)
        {
            //画当前选中的背景色
            GUI_SetColor(0x96842c);
            rect.x0=QUALITY_CONTROL_COLUMN_NO;
            rect.y0=PAGE_SELECT_START_Y+2-TITLESBAR_HEIGHT+PAGE_SELECT_DIS_Y*nCurrentSelectPage;
            rect.x1=QUALITY_CONTROL_COLUMN_NO+SELECT_LEN;
            rect.y1=rect.y0+SELECT_HIGH;
            GUI_FillRect(rect.x0, rect.y0, rect.x1 , rect.y1);

            GUI_SetColor(0xFFFFFF);
            for (i = 0; i < QC_PAGE_NUMBER; i++)
            {
                if((i + QC_PAGE_NUMBER * nCurrentPage + 1) > QC_MAX)    //只有九个质控品
                {
                    break;
                }
                //SD<0,Target<=0 return
                if( (BoardInfTemp.QualityPara.dSD[BoardInfTemp.QualityPara.AbsFlag][i + QC_PAGE_NUMBER * nCurrentPage] < 0.0f)&&(BoardInfTemp.QualityPara.dTarget [BoardInfTemp.QualityPara.AbsFlag][i + QC_PAGE_NUMBER * nCurrentPage]<= 0.0) )
                {
                    break;
                }

                //显示No
                GUI_SetColor(0xFFFFFF);
                rect.x0 = QUALITY_CONTROL_COLUMN_NO;
                rect.y0=PAGE_SELECT_START_Y+2-TITLESBAR_HEIGHT+i*PAGE_SELECT_DIS_Y;
                rect.x1 = rect.x0+55;
                rect.y1 =  rect.y0+SELECT_HIGH;
                sprintf(ConvertStr,"%d",i + QC_PAGE_NUMBER * nCurrentPage + 1);
                GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);




                //显示Target
                temp=BoardInfTemp.QualityPara.dTarget[BoardInfTemp.QualityPara.AbsFlag][i + QC_PAGE_NUMBER * nCurrentPage];
                if(temp > 1000.0f || temp < -1000.0f)
                {
                    sprintf(ConvertStr,"%.3e",temp);
                    EConvert(ConvertStr);
                }
                else
                {
                    sprintf(ConvertStr,"%1.3f",temp);
                }
                rect.x0 = QUALITY_CONTROL_COLUMN_TARGET+ QUALITY_TABLE_TARGET_START_X[SystemPrameter.SystemLanguage];
                rect.x1 = rect.x0+110;//
                if((ExpEnable==EXP_TABLE_TARGET)&&(i==nCurrentSelect) )
                {
                    GUI_SetColor(0x0);
                    //GUI_FillRect(rect.x0 + 2, rect.y0 + 2, rect.x1 - 2, rect.y0 + 35);
                    GUI_FillRect(rect.x0 -10, rect.y0 + 2, rect.x1 -20, rect.y0 + 31);
                    GUI_SetColor(0xFFFFFF);
                }
                GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);


                //显示SD
                GUI_SetColor(0xFFFFFF);
                temp=BoardInfTemp.QualityPara.dSD[BoardInfTemp.QualityPara.AbsFlag][i + QC_PAGE_NUMBER * nCurrentPage];
                if(temp > 1000.0f || temp < -1000.0f)
                {
                    sprintf(ConvertStr,"%.3e",temp);
                    EConvert(ConvertStr);
                }
                else
                {
                    sprintf(ConvertStr,"%1.3f",temp);
                }
                //rect.x0 = QUALITY_CONTROL_COLUMN_SD-10;
                rect.x0 = QUALITY_CONTROL_COLUMN_SD+ QUALITY_TABLE_SD_START_X[SystemPrameter.SystemLanguage];
                rect.x1 = rect.x0+100;

                GUI_SetColor(0xFFFFFF);
                if((ExpEnable==EXP_TABLE_SD)&&(i==nCurrentSelect) )
                {
									GUI_SetColor(0x0);
                    //GUI_FillRect(rect.x0 + 2, rect.y0 + 2, rect.x1 - 2, rect.y0 + 35);
                    GUI_FillRect(rect.x0 -10, rect.y0 + 2, rect.x1 - 10, rect.y0 + 31);
                    GUI_SetColor(0xFFFFFF);
                }
                GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);

                //CV
                GUI_SetColor(0xFFFFFF);
                temp=BoardInfTemp.QualityPara.dCV[BoardInfTemp.QualityPara.AbsFlag][i + QC_PAGE_NUMBER * nCurrentPage];
                if(temp < CONCENTRATION_VALUE_MIN && temp > -CONCENTRATION_VALUE_MIN)
                {
                    strcpy(ConvertStr,"N.A.");
                }
                else if(temp > 1000.0f || temp < -1000.0f)
                {
                    sprintf(ConvertStr,"%.3e",temp);
                    EConvert(ConvertStr);
                }
                else
                {
                    sprintf(ConvertStr,"%1.3f",temp);
                }
                rect.x0 = QUALITY_CONTROL_COLUMN_CV+ QUALITY_TABLE_CV_START_X[SystemPrameter.SystemLanguage];
                rect.x1 = rect.x0+100;//
                GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);


                //Upper limit
                temp=BoardInfTemp.QualityPara.dUpperLimit[BoardInfTemp.QualityPara.AbsFlag][i + QC_PAGE_NUMBER * nCurrentPage];
                if(temp > 1000.0f || temp < -1000.0f)
                {
                    sprintf(ConvertStr,"%.3e",temp);
                    EConvert(ConvertStr);
                }
                else
                {
                    sprintf(ConvertStr,"%1.3f",temp);
                }
                rect.x0 = QUALITY_CONTROL_COLUMN_UPPER;
                rect.x1 = rect.x0+120;
                GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);


                //Lower limit
                temp=BoardInfTemp.QualityPara.dLowerLimit[BoardInfTemp.QualityPara.AbsFlag][i + QC_PAGE_NUMBER * nCurrentPage];
                if(temp > 1000.0f || temp < -1000.0f)
                {
                    sprintf(ConvertStr,"%.3e",temp);
                    EConvert(ConvertStr);
                }
                else
                {
                    sprintf(ConvertStr,"%1.3f",temp);
                }
                rect.x0 = QUALITY_CONTROL_COLUMN_LOWER;
                rect.x1 = rect.x0+100;//
                GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);
                rect.y0 +=PAGE_SELECT_DIS_Y;
            }

        }

        //4.画页码
        GUI_SetColor(0xFFFFFF);
        rect.x0=273;
        rect.x1=353;
        rect.y0=TAB_RIGHT_START_Y-10- TITLESBAR_HEIGHT;
        rect.y1=TAB_RIGHT_END_Y+10- TITLESBAR_HEIGHT;

        if(BoardInfTemp.QualityPara.Enable)
        {
            sprintf(ConvertStr,"%d",nCurrentPage + 1);
            strcat(ConvertStr," / ");
            sprintf(StrTemp,"%d",QC_PAGES);
            strcat(ConvertStr,StrTemp);
        }
        else
        {
            strcpy(ConvertStr,"1 / 1");
        }
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);


        if(ExpEnable==EXP_ENABLE)
        {
            DisplayExpandEnable();
        }
        else if(ExpEnable==EXP_CONC)
        {
            DisplayExpandConc();
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
        if( (NCode == WM_NOTIFICATION_RELEASED)&&(TouchKey.KeyStatus==0) )
        {
            if (Id == ID_QUALITY_BUTTON)   //工具栏第4个按钮  Enter
            {
                if(GetTargetStatus())
                {
                    if(memcmp(&BoardInf.QualityPara,&BoardInfTemp.QualityPara, sizeof(QUALITY_PARA)))   //
                    {
                        memcpy(&BoardInf.QualityPara, &BoardInfTemp.QualityPara,sizeof(QUALITY_PARA));

                        if(BoardInf.bHasData)
                        {
                            ReportMenu.ReportReady=1;
                            LanguageChange.Report=1;
                        }
                    }

                    // memcpy(&BoardInf.QualityPara,&BoardInfTemp.QualityPara, sizeof(QUALITY_PARA) ); //保存质控参数
                    WM_DeleteWindow(ProtocolQualityWin);
                    WM_ShowWindow(ProtocolWin);

                    gSystem.SystemInterface = MI_PROTOCOL;
                    gSystem.TitleButtonEnable = 1;
                    TouchKey.KeyStatus=1;
                    gSystem.MenuRefreshFlag = 1;
                }
                else
                {
                    strcpy(PromptMenu.InputStr,QC_SET_ERROR[SystemPrameter.SystemLanguage]);
                    Prompt_Interface(PROMPT_ERROR);
                    //提示质控值不允许相同(至标志，在主循环中调用提示框)
                }
            }
            else if (Id == ID_QUALITY_BUTTON+1)   //工具栏第5个按钮  Cancel
            {
                //memcmp(&BoardInfTemp.QualityPara,&BoardInf.QualityPara, sizeof(QUALITY_PARA));

                WM_DeleteWindow(ProtocolQualityWin);
                WM_ShowWindow(ProtocolWin);

                gSystem.MenuRefreshFlag = 1;
                gSystem.SystemInterface = MI_PROTOCOL;
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



void ProtocolQuality_Interface(void)
{

    //备份质控参数
    //BoardInfTemp.QualityPara.Enable=BoardInf.QualityPara.Enable;     //允许定性分析
    //BoardInfTemp.QualityPara. AbsFlag=BoardInf.QualityPara.AbsFlag; //采用吸光度
    // memcpy(BoardInfTemp.QualityPara.dTarget, BoardInf.QualityPara.dTarget, sizeof(float) * QC_MAX*2);//float dTarget[2][QC_MAX]; //目标值  0表示浓度，1表示吸光度
    //memcpy(BoardInfTemp.QualityPara.dSD, BoardInf.QualityPara.dSD, sizeof(float) * QC_MAX*2);//float dSD[2][QC_MAX]; 2通道 标准偏差
    //memcpy(BoardInfTemp.QualityPara.dCV, BoardInf.QualityPara.dCV, sizeof(float) * QC_MAX*2);//float dCV[2][QC_MAX]; //2通道 变异系数
    //memcpy(BoardInfTemp.QualityPara.dUpperLimit, BoardInf.QualityPara.dUpperLimit, sizeof(float) * QC_MAX*2);// float dUpperLimit[2][QC_MAX];//上限
    //memcpy(BoardInfTemp.QualityPara.dLowerLimit, BoardInf.QualityPara.dLowerLimit, sizeof(float) * QC_MAX*2); //float dLowerLimit[2][QC_MAX];//下限

    //memcpy(&BoardInfTemp.QualityPara,&BoardInf.QualityPara, sizeof(QUALITY_PARA) ); //保存质控参数
    memcpy(&BoardInfTemp.QualityPara,&BoardInf.QualityPara, sizeof(QUALITY_PARA) ); //保存质控参数

    nCurrentSelect=0;
    nCurrentSelectBack=0;
    ExpEnable = 0;
    ProtocolQualityWin = WM_CreateWindowAsChild(CONTENTBAR_POSX, CONTENTBAR_POSY, CONTENTBAR_WIDTH, CONTENTBAR_HEIGHT, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbProtocolQuality, 0);
    WM_BringToTop(ProtocolQualityWin);
}


void ProtocolQuality_Scan(void)
{
    if(TouchKey.KeyStatus==0)
    {
        GUI_PID_STATE TouchState;
        GUI_PID_GetState(&TouchState);

        if (TouchState.Pressed)
        {
            if (ExpEnable==0)  //初使状态，没有弹出扩展项
            {
                //OPEN
                if ((TouchState.x >= QUALITY_OPEN_SELECT_START_X) && (TouchState.x <= QUALITY_OPEN_SELECT_END_X) &&
                        (TouchState.y >= QUALITY_OPEN_SELECT_START_Y) && (TouchState.y <= QUALITY_OPEN_SELECT_END_Y))
                {
                    TouchKey.KeyStatus = 1;
                    ExpEnable = EXP_ENABLE;
                    WM_Invalidate(ProtocolQualityWin);
                }
                //CONC
                else if ((TouchState.x >= QUALITY_CONC_SELECT_START_X) && (TouchState.x <= QUALITY_CONC_SELECT_END_X) &&
                         (TouchState.y >= QUALITY_CONC_SELECT_START_Y) && (TouchState.y <= QUALITY_CONC_SELECT_END_Y)&&(BoardInfTemp.QualityPara.Enable))
                {
                    TouchKey.KeyStatus = 1;
                    ExpEnable = EXP_CONC;
                    WM_Invalidate(ProtocolQualityWin);
                }
                //上1页
                else if ((TouchState.x>TABPAGE_LEFT_START_X-15)&&(TouchState.x<TABPAGE_LEFT_END_X+15)&&(TouchState.y>TABPAGE_LEFT_START_Y-15)
                         &&(TouchState.y<TABPAGE_LEFT_END_Y+15) )
                {
                    if( (BoardInfTemp.QualityPara.Enable)&&(nCurrentPage > 0) )
                    {
                        TouchKey.KeyStatus=1;
                        nCurrentPage = 0;
                        nCurrentSelect = nCurrentPage * QC_PAGE_NUMBER + nCurrentSelectPage;
                        WM_Invalidate(ProtocolQualityWin);
                    }
                }
                //下1页
                else if ((TouchState.x>TABPAGE_RIGHT_START_X-15)&&(TouchState.x<TABPAGE_RIGHT_END_X+15)&&(TouchState.y>TABPAGE_RIGHT_START_Y-15)
                         &&(TouchState.y<TABPAGE_RIGHT_END_Y+15))
                {
                    if( (BoardInfTemp.QualityPara.Enable)&&(nCurrentPage ==0) )
                    {
                        TouchKey.KeyStatus=1;
                        nCurrentPage = 1;
                        nCurrentSelect = nCurrentPage * QC_PAGE_NUMBER + nCurrentSelectPage;
                        WM_Invalidate(ProtocolQualityWin);
                    }
                }
                //上1行
                else if ((TouchState.x>TAB_LEFT_START_X-15)&&(TouchState.x<TAB_LEFT_END_X+15)&&(TouchState.y>TAB_LEFT_START_Y-15)&&(TouchState.y<TAB_LEFT_END_Y+15))
                {
                    if(BoardInfTemp.QualityPara.Enable)
                    {
                        TouchKey.KeyStatus=1;
                        nCurrentSelect--;
                        if(nCurrentSelect <= 0)
                        {
                            nCurrentSelect = 0;
                        }
                        WM_Invalidate(ProtocolQualityWin);
                    }
                }
                //下1页
                else if ((TouchState.x>TAB_RIGHT_START_X-15)&&(TouchState.x<TAB_RIGHT_END_X+15)&&(TouchState.y>TAB_RIGHT_START_Y-15)&&(TouchState.y<TAB_RIGHT_END_Y+15))
                {
                    if(BoardInfTemp.QualityPara.Enable)
                    {
                        TouchKey.KeyStatus=1;
                        nCurrentSelect++;
                        if(nCurrentSelect >= QC_MAX)
                        {
                            nCurrentSelect = QC_MAX - 1;
                        }
                        WM_Invalidate(ProtocolQualityWin);
                    }
                }
                //输入1行的信息
                else if (((TouchState.x>PAGE_SELECT_START_X)&&(TouchState.x<PAGE_SELECT_END_X)&&(TouchState.y>PAGE_SELECT_START_Y)&&(TouchState.y<PAGE_SELECT_END_Y))//page.selectLocateY[5]+SELECT_HIGH))//第一行
                         &&(BoardInfTemp.QualityPara.Enable) )
                {
                    if( ((TouchState.y - PAGE_SELECT_START_Y) / PAGE_SELECT_DIS_Y==4)&&(nCurrentPage==1) )
                    {
                        return;
                    }
                    TouchKey.KeyStatus=1;

                    nCurrentSelectPage = (TouchState.y - PAGE_SELECT_START_Y) / PAGE_SELECT_DIS_Y;
                    nCurrentSelect = nCurrentPage * QC_PAGE_NUMBER+ nCurrentSelectPage;
                    if(nCurrentSelectBack == nCurrentSelect)
                    {
                        //SD
                        if(TouchState.x < (QUALITY_CONTROL_COLUMN_SD+QUALITY_TABLE_SD_START_X[SystemPrameter.SystemLanguage])
                                && TouchState.x > (QUALITY_CONTROL_COLUMN_TARGET+QUALITY_TABLE_TARGET_START_X[SystemPrameter.SystemLanguage]))
                        {
                            ExpEnable = EXP_TABLE_TARGET;
                            //WM_Invalidate(ProtocolQualityWin);
                        }
                        //CV
                        else if(TouchState.x < (QUALITY_CONTROL_COLUMN_CV+QUALITY_TABLE_CV_START_X[SystemPrameter.SystemLanguage])
                                && TouchState.x > (QUALITY_CONTROL_COLUMN_SD+QUALITY_TABLE_SD_START_X[SystemPrameter.SystemLanguage]))
                        {
                            ExpEnable = EXP_TABLE_SD;
                            //WM_Invalidate(ProtocolQualityWin);
                        }
                    }//if(nCurrentSelectBack == nCurrentSelect)
                    nCurrentSelectBack = nCurrentSelect;
                    WM_Invalidate(ProtocolQualityWin);
                }//else if ((TouchState.x>PAGE_SELECT_START_X)&&(TouchState.x<PAGE_SELECT_END_X)&&(TouchState.y>PAGE_SELECT_START_Y)&&(TouchState.y<PAGE_SELECT_END_Y))//page.selectLocateY[5]+SELECT_HIGH))//第一行
            }//if (ExpEnable==0)  //初使状态，没有弹出扩展项
            else if (ExpEnable == EXP_ENABLE)//打开
            {
                if ((TouchState.x >= QUALITY_OPEN_SELECT_START_X-170) && (TouchState.x <= QUALITY_OPEN_SELECT_START_X) &&
                        (TouchState.y >= QUALITY_OPEN_SELECT_START_Y) && (TouchState.y <= QUALITY_OPEN_SELECT_END_Y))
                {
                    TouchKey.KeyStatus = 1;
                    if ((TouchState.x>QUALITY_OPEN_SELECT_START_X - 170)&&(TouchState.x<QUALITY_OPEN_SELECT_START_X - 80))
                    {
                        BoardInfTemp.QualityPara.Enable = 0;
                    }
                    else
                    {
                        BoardInfTemp.QualityPara.Enable = 1;
                    }
                }
                ExpEnable = 0;
                WM_Invalidate(ProtocolQualityWin);
            }//else if (ExpEnable == EXP_ENABLE)//打开
            else if (ExpEnable == EXP_CONC)//浓度扩展
            {
                if ((TouchState.x >= QUALITY_CONC_SELECT_START_X-170) && (TouchState.x <= QUALITY_CONC_SELECT_START_X) &&
                        (TouchState.y >= QUALITY_CONC_SELECT_START_Y) && (TouchState.y <= QUALITY_CONC_SELECT_END_Y))
                {
                    TouchKey.KeyStatus = 1;
                    if ((TouchState.x>QUALITY_CONC_SELECT_START_X - 170)&&(TouchState.x<QUALITY_CONC_SELECT_START_X - 90))
                    {
                        BoardInfTemp.QualityPara.AbsFlag = 1;  //吸光度
                    }
                    else
                    {
                        BoardInfTemp.QualityPara.AbsFlag = 0;
                    }
                }
                ExpEnable = 0;
                WM_Invalidate(ProtocolQualityWin);
            }//else if (ExpEnable == EXP_CONC)//浓度扩展

        }//if (TouchState.Pressed)
    }//if(TouchKey.KeyStatus==0)
}


void ProtocolQuality_Go(void)
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
        //SD
        if(ExpEnable == EXP_TABLE_TARGET)
        {
            sprintf(KeyPadNum.InputValueStr,"%.3f",BoardInfTemp.QualityPara.dTarget[BoardInfTemp.QualityPara.AbsFlag][nCurrentSelect]);
            KeyPadNum_Interface(POINT_MENU_FLAG);
            if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
            {
                BoardInfTemp.QualityPara.dTarget[BoardInfTemp.QualityPara.AbsFlag][nCurrentSelect]= atof(KeyPadNum.InputValueStr);
                SetQCPara();
            }
            ExpEnable = 0;
            TouchKey.KeyStatus = 1;
            WM_Invalidate(ProtocolQualityWin);
        }

        //CV
        else if(ExpEnable == EXP_TABLE_SD)
        {
            sprintf(KeyPadNum.InputValueStr,"%.3f",BoardInfTemp.QualityPara.dSD[BoardInfTemp.QualityPara.AbsFlag][nCurrentSelect]);
            KeyPadNum_Interface(POINT_MENU_FLAG);
            if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
            {
                BoardInfTemp.QualityPara.dSD[BoardInfTemp.QualityPara.AbsFlag][nCurrentSelect]= atof(KeyPadNum.InputValueStr);
                SetQCPara();
            }
            ExpEnable = 0;
            TouchKey.KeyStatus = 1;
            WM_Invalidate(ProtocolQualityWin);
        }

    }//if (TouchKey.KeyStatus)

}
