
#include "MainTask.h"
/*
SystemPrameter.AbsCaliEnable;
SystemPrameter.AbsCali[sys_para.nChannelCurrent]        // sys_para.abs_cal[sys_para.nChannelCurrent]    abs_cal.dABS
*/
ABS_CAL AbsCali;


#define ID_ABS_BUTTON      (ID_KEY_TOOLS_BUTTON)        //保存键按下的ID






const BUTTON_DATA _aButtonAbs[] =
{
    { TOOLS0_BUTTON_POSX(3)+3, TOOLS0_BUTTON_POSY, TOOLS0_BUTTON_WIDTH, TOOLS0_BUTTON_HEIGHT, "Enable", "Habilitar" },
    { TOOLS0_BUTTON_POSX(4), TOOLS0_BUTTON_POSY, TOOLS0_BUTTON_WIDTH, TOOLS0_BUTTON_HEIGHT, "Clear all", "Limpar" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(3), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Ok", "Ok" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(4), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Back", "Voltar" },
    { 195+103*0, TOOLS0_BUTTON_POSY, TOOLS01_BUTTON_WIDTH, TOOLS0_BUTTON_HEIGHT, "ABS.input", "ABS.input" },
    { 195+103*1, TOOLS0_BUTTON_POSY, TOOLS01_BUTTON_WIDTH, TOOLS0_BUTTON_HEIGHT, "Cal.low", "Cal. Inf." },
    { 195+103*2, TOOLS0_BUTTON_POSY, TOOLS01_BUTTON_WIDTH, TOOLS0_BUTTON_HEIGHT, "Cal.high", "Cal. Sup." },
    { 195+103*3, TOOLS0_BUTTON_POSY, TOOLS01_BUTTON_WIDTH, TOOLS0_BUTTON_HEIGHT, "Export", "Exportar" },
};



WM_HWIN AbsWin = NULL;                //数字键盘




const int ABSDLG_TABLE_CAL_ABS_START_X[LANGUAGE_TYPES] = { 0, 20};
const int ABSDLG_TABLE_ABS_START_X[LANGUAGE_TYPES] = { 10, 13};
const int BUTTON_ABSDLG_OFF_START_X[LANGUAGE_TYPES] = { 26, 33};
const int BUTTON_ABSDLG_ON_START_X[LANGUAGE_TYPES] = { 28, 33};
const int BUTTON_ABSDLG_CLEAR_START_X[LANGUAGE_TYPES] = { 9, 25};

const char BUTTON_ABSDLG_OFF[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = { "Disable", "Desabilit."};
const char BUTTON_ABSDLG_ON[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = { "Enable", "Habilitado"};
const char BUTTON_ABSDLG_CLEAR[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = {"Clear all", "Limp. tudo"};
const char ABSDLG_MAIN_TITLE[LANGUAGE_TYPES][ABSDLG_TITLE_CHAR_MAX] = { "Calibrate absorbance", "Calibra Absorbância"};
const char ABSDLG_TABLE_CAL_ABS[LANGUAGE_TYPES][PLATE_IN_OUT_CHAR_MAX] = {"Standard", "Standard"};
const char ABSDLG_TABLE_ABS[LANGUAGE_TYPES][PLATE_IN_OUT_CHAR_MAX] = { "Calibrate", "Calib."};
const char ABSDLG_TABLE_ERROR[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = { "TestVal","Test.Val" };
const char ABSDLG_SELECT_CHANNEL[LANGUAGE_TYPES][PLATE_IN_OUT_CHAR_MAX] = { "Channel:  ", "Canal："};
const char ABSDLG_TABLE_NO[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = { "NO.","Nº."};
const char ABSDLG_SELECT_AUTO_ON[LANGUAGE_TYPES][ABSDLG_TITLE_CHAR_MAX] = { "Auto: On ", "Auto: On"};
const char ABSDLG_SELECT_AUTO_OFF[LANGUAGE_TYPES][ABSDLG_TITLE_CHAR_MAX] = { "Auto: Off ", "Auto: Off"};


const char BUTTON_ABSDLG_U_PAN[LANGUAGE_TYPES][PROMPT_CHAR_MAX] = { "Please insert u disk", "Insira o disco"};
const char BUTTON_ABSDLG_DATA_OUTPUT_SUCCESS[LANGUAGE_TYPES][PROMPT_CHAR_MAX] = { "Data Export Succeeded", "Exportação de dados bem-sucedida"};
const char BUTTON_ABSDLG_DATA_INPUT_SUCCESS[LANGUAGE_TYPES][PROMPT_CHAR_MAX] = { "Data Import Succeeded", "Importação de dados bem-sucedida"};
const char BUTTON_ABSDLG_OPEN_FILE_FAIL[LANGUAGE_TYPES][PROMPT_CHAR_MAX] = { "Failed to open file", "Falha ao abrir arquivo"};

unsigned char CalibrateFlag;                       //开启校准(0=关闭，1=开启)


//ExpEnable的值定义
enum
{
    EXP_PRACTICAL_ABS=1,
    EXP_ABS,
    EXP_ABS_AUTO_LOW,
    EXP_ABS_AUTO_HIGH,
    EXP_EXPORT,
};
static unsigned char ExpEnable;

signed char m_CurrentAbs;//当前吸光度编号

char channel_auto_plus_flag=0;  //通道自动累加 ，默认累加，非零不累加

//char  Usb_data_file_export_flag=0;
char AbsCalibration_auto_flag_end=0; //自动校准结束 lugj20180906
char AbsCalibration_auto_flag=0;     //自动校准=1，不保存数据，不进入Report界面lugj20180906
float Used_AbsCali[ABS_CHANNEL_MAX+1][12];  //存放（启用状态下的实测值)，8个通道，12组数据lugj20180906


static  u16 AbsCal_si=0;  //自动测量当前通道号,lugj20180906
char start_test_flag=0;   //进入检测状态=1,全部测完=0
u8  alrealay_send_move=0; //1=下发运行命令


extern GUI_PID_STATE State;

void  ClearAutoCaliFlag(void)    
{
	    AbsCalibration_auto_flag_end=0;
			AbsCalibration_auto_flag=0;  //不出报告
			AbsCal_si=0;
			start_test_flag=0;
	    alrealay_send_move=0;
      ExpEnable = 0;
     // WM_Invalidate(AbsWin);
}
					  
void _cbAbsCalibration(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;
//	WM_HWIN hWinFocus;
    BUTTON_Handle hbutton;
    unsigned int i,j;
    short nRowRectStartX,	nRowRectStartY;
    short        xSize;
    short        ySize;
    short NCode, Id;
    GUI_RECT rect;
    //hWinFocus = WM_GetFocussedWindow();
//	IdWinFocus = WM_GetId(hWinFocus);

    switch (pMsg->MsgId)
    {
        //创建所耐的按钮
    case WM_CREATE:
    {
        for (i = 0; i < GUI_COUNTOF(_aButtonAbs); i++)
        {
            hbutton = BUTTON_CreateEx(_aButtonAbs[i].xPos, _aButtonAbs[i].yPos, _aButtonAbs[i].xSize, _aButtonAbs[i].ySize,
                                      hWin, WM_CF_SHOW, 0, ID_ABS_BUTTON + i);
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG);
                BUTTON_SetText(hbutton, _aButtonAbs[i].acLabelEn);
            }
            else
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG_CH);
                BUTTON_SetText(hbutton, _aButtonAbs[i].acLabelCh);
            }
            if(i==0)
            {
                if( CalibrateFlag==0)
                {
                    BUTTON_SetText(hbutton, BUTTON_ABSDLG_OFF[SystemPrameter.SystemLanguage]);
                }
                else
                {
                    BUTTON_SetText(hbutton, BUTTON_ABSDLG_ON[SystemPrameter.SystemLanguage]);
                }
            }
            BUTTON_SetTextAlign(hbutton, GUI_TA_HCENTER | GUI_TA_VCENTER);
            BUTTON_SetFocussable(hbutton, 0);
						
					 if( SystemPrameter.CaliMode!=CALI_MODE_FACTORY ) //用户模式
				   {
						   if(i==5)
							 {
								   if(SystemPrameter.SystemLanguage==LANGUAGE_EN)BUTTON_SetText(hbutton, "Calibrate");
								   else BUTTON_SetText(hbutton, "Calibração");
						   }
						   else if(i==6) WM_HideWindow(hbutton);//隐高浓度校准项
				   }
        }
				
				
    }
    break;
    //删除按钮
    case WM_DELETE:


        break;
        //绘制背景
    case WM_PAINT:
    {
        xSize = WM_GetWindowSizeX(hWin);
        ySize = WM_GetWindowSizeY(hWin);

        GUI_SetTextMode(GUI_TM_TRANS);
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            GUI_SetFont(GUI_FONT_BIG);
        }
        else
        {
            GUI_SetFont(GUI_FONT_BIG_CH);
        }

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
        //GUI_DrawBitmap(&bmMenuRight_120_46, ANALYSIS_FILTER_SELECT_START_X, ANALYSIS_FILTER_SELECT_START_Y - TITLESBAR_HEIGHT);

        /*
        		GUI_SetColor(COLOR_PICTURE);
        	  GUI_FillRect(ANALYSIS_FILTER_SELECT_START_X, ANALYSIS_FILTER_SELECT_START_Y- TITLESBAR_HEIGHT,ANALYSIS_FILTER_SELECT_START_X+100, ANALYSIS_FILTER_SELECT_START_Y- TITLESBAR_HEIGHT+45);
        	  GUI_DrawBitmap(&bmMenuRight_20_46, ANALYSIS_FILTER_SELECT_START_X+100, ANALYSIS_FILTER_SELECT_START_Y- TITLESBAR_HEIGHT);


        		GUI_DrawBitmap(&bmMenuPlus_62_37, ABS_PLUS_BUTTON_START_X, ABS_PLUS_BUTTON_START_Y - TITLESBAR_HEIGHT);
            GUI_DrawBitmap(&bmMenuMinus_62_37, ABS_MINUS_BUTTON_START_X, ABS_MINUS_BUTTON_START_Y - TITLESBAR_HEIGHT);
        		*/

        GUI_SetColor(COLOR_PICTURE);
        GUI_FillRect(ABS_CHANNEL_BUTTON_START_X, ABS_CHANNEL_BUTTON_START_Y-TITLESBAR_HEIGHT,ABS_CHANNEL_BUTTON_END_X, ABS_CHANNEL_BUTTON_END_Y-TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmMenuRight_20_46, ABS_CHANNEL_BUTTON_END_X, ABS_CHANNEL_BUTTON_START_Y-TITLESBAR_HEIGHT);


        GUI_DrawBitmap(&bmMenuMinus_62_37, ABS_PLUS_BUTTON_START_X, ABS_PLUS_BUTTON_START_Y-TITLESBAR_HEIGHT );
        GUI_DrawBitmap(&bmMenuPlus_62_37, ABS_MINUS_BUTTON_START_X, ABS_MINUS_BUTTON_START_Y-TITLESBAR_HEIGHT);

        GUI_FillRect(ABS_AUTO_BUTTON_START_X, ABS_AUTO_BUTTON_START_Y-TITLESBAR_HEIGHT,ABS_AUTO_BUTTON_END_X, ABS_AUTO_BUTTON_END_Y-TITLESBAR_HEIGHT);
        GUI_DrawBitmap(&bmMenuRight_20_46, ABS_AUTO_BUTTON_END_X, ABS_AUTO_BUTTON_START_Y-TITLESBAR_HEIGHT);


        //标题
        GUI_SetColor(COLOR_PAINT_TXT);
        //GUI_SetFont(GUI_FONT_BIG);
        GUI_DispStringAt(ABSDLG_MAIN_TITLE[SystemPrameter.SystemLanguage], CONTENTBAR_CAPTION_POSX, CONTENTBAR_CAPTION_POSY);



        //右侧按钮通道
        rect.x0 = ABS_CHANNEL_BUTTON_START_X;
        rect.y0 = ABS_CHANNEL_BUTTON_START_Y-TITLESBAR_HEIGHT;
        rect.x1 = ABS_CHANNEL_BUTTON_END_X;
        rect.y1 = ABS_CHANNEL_BUTTON_END_Y-TITLESBAR_HEIGHT;
        strcpy(ConvertStr, ABSDLG_SELECT_CHANNEL[SystemPrameter.SystemLanguage]);
        sprintf(StrTemp, "%d",SystemPrameter.nChannelCurrent+1);//CurrChannel
        strcat(ConvertStr, StrTemp);
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);

        //右侧按钮自动
        rect.x0 = ABS_AUTO_BUTTON_START_X;
        rect.y0 = ABS_AUTO_BUTTON_START_Y-TITLESBAR_HEIGHT;
        rect.x1 = ABS_AUTO_BUTTON_END_X;
        rect.y1 = ABS_AUTO_BUTTON_END_Y-TITLESBAR_HEIGHT;
        if(channel_auto_plus_flag==0)
        {
            strcpy(ConvertStr, ABSDLG_SELECT_AUTO_ON[SystemPrameter.SystemLanguage]);
        }
        else
        {
            strcpy(ConvertStr, ABSDLG_SELECT_AUTO_OFF[SystemPrameter.SystemLanguage]);
        }
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
        //左边框
        rect.x0 = TABLE_ABS1_COLUMN_NO;
        rect.y0 = TABLE_CONCENTRATION_ROW_TITLE_START_Y - TITLESBAR_HEIGHT;
        rect.x1 = rect.x0+278;
        rect.y1 = rect.y0+260;
        GUI_SetColor(0xe1d8ca);
        GUI_DrawRect(rect.x0-5, rect.y0-5, rect.x1+5, rect.y1+5);
        GUI_SetColor(COLOR_TITLEBAR);
        GUI_FillRect(rect.x0 - 2, rect.y0 - 2, rect.x1 + 2, rect.y0 + 35);
GUI_SetColor(GUI_GRAY);
				GUI_DrawLine(0,0, xSize - 1,0);
				GUI_DrawLine(0,CONTENTBAR_TITLE_HEIGHT - 1, xSize - 1,CONTENTBAR_TITLE_HEIGHT - 1);
        //右边框
        rect.x0 = TABLE_ABS2_COLUMN_NO;
        rect.x1 = rect.x0 + 278;  //294-17
        GUI_SetColor(0xe1d8ca);//ok
        GUI_DrawRect(rect.x0-5, rect.y0-5, rect.x1+5, rect.y1+5);
        GUI_SetColor(COLOR_TITLEBAR);
        GUI_FillRect(rect.x0 - 2, rect.y0 - 2, rect.x1 + 2, rect.y0 + 35);
GUI_SetColor(GUI_GRAY);
				GUI_DrawLine(0,0, xSize - 1,0);
				GUI_DrawLine(0,CONTENTBAR_TITLE_HEIGHT - 1, xSize - 1,CONTENTBAR_TITLE_HEIGHT - 1);
        GUI_SetColor(0xffdddd);//
        rect.y0 = TABLE_CONCENTRATION_ROW_TITLE_START_Y - TITLESBAR_HEIGHT+TABLE_CONCENTRATION_TXT_OFFSET_Y;
        GUI_DispStringAt(ABSDLG_TABLE_NO[SystemPrameter.SystemLanguage], TABLE_ABS1_COLUMN_NO, rect.y0);
        GUI_DispStringAt(ABSDLG_TABLE_CAL_ABS[SystemPrameter.SystemLanguage], TABLE_ABS1_COLUMN_CAL + ABSDLG_TABLE_CAL_ABS_START_X[SystemPrameter.SystemLanguage], rect.y0);
        GUI_DispStringAt(ABSDLG_TABLE_ABS[SystemPrameter.SystemLanguage], TABLE_ABS1_COLUMN_PRACTICAL + ABSDLG_TABLE_ABS_START_X[SystemPrameter.SystemLanguage], rect.y0);
        //if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        //{
        //	GUI_DispStringAt(ABSDLG_TABLE_ERROR[SystemPrameter.SystemLanguage], TABLE_ABS1_COLUMN_ERROR-20, rect.y0);
        //}
        //else
        //{
        GUI_DispStringAt(ABSDLG_TABLE_ERROR[SystemPrameter.SystemLanguage], TABLE_ABS1_COLUMN_ERROR, rect.y0);
        //}


        GUI_DispStringAt(ABSDLG_TABLE_NO[SystemPrameter.SystemLanguage], TABLE_ABS2_COLUMN_NO, rect.y0);
        GUI_DispStringAt(ABSDLG_TABLE_CAL_ABS[SystemPrameter.SystemLanguage], TABLE_ABS2_COLUMN_CAL + ABSDLG_TABLE_CAL_ABS_START_X[SystemPrameter.SystemLanguage], rect.y0);
        GUI_DispStringAt(ABSDLG_TABLE_ABS[SystemPrameter.SystemLanguage], TABLE_ABS2_COLUMN_PRACTICAL + ABSDLG_TABLE_ABS_START_X[SystemPrameter.SystemLanguage], rect.y0);

        // if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        //{
        //GUI_DispStringAt(ABSDLG_TABLE_ERROR[SystemPrameter.SystemLanguage], TABLE_ABS2_COLUMN_ERROR-20, rect.y0);
        //}
        //else
        //{
        GUI_DispStringAt(ABSDLG_TABLE_ERROR[SystemPrameter.SystemLanguage], TABLE_ABS2_COLUMN_ERROR, rect.y0);
        //}

        //3.选中项的背景色
        //3.1位置定义
        rect.x0 = TABLE_ABS1_COLUMN_NO  + TABLE_CONCENTRATION_WIDTH * (m_CurrentAbs/ (CALIBRATOR_CONCENTRATION_MAX / 2));
        rect.y0 = TABLE_CONCENTRATION_ROW_TITLE_START_Y + TABLE_CONCENTRATION_ROW_HEIGHT
                  + (m_CurrentAbs	% (CALIBRATOR_CONCENTRATION_MAX / 2)) * TABLE_CONCENTRATION_ROW_HEIGHT+2
                  - TITLESBAR_HEIGHT;
        rect.x1 = rect.x0 + TABLE_CONCENTRATION_SELECT_WIDTH;  //294-17
        rect.y1 = rect.y0 + TABLE_CONCENTRATION_SELECT_HEIGHT;
        //GUI_SetColor(0xcad8e1);//ok//RGB(198,225,248)
        GUI_SetColor(0xf8ffc6);
        GUI_FillRect(rect.x0-2 , rect.y0-2 , rect.x1+2 , rect.y1+2 );

        for (i = 0; i < CALIBRATOR_ABS_MAX; i++)
        {
            if( CalibrateFlag==0)
            {
                GUI_SetColor(COLOR_PAINT_TXT_DIS);
            }
            else
            {
                GUI_SetColor(0x000000);   //色
            }
            if (AbsCali.dABS[i] < 0.0f)
            {
                break;
            }
            nRowRectStartX = TABLE_ABS1_COLUMN_NO + TABLE_CONCENTRATION_WIDTH * (i/ (CALIBRATOR_CONCENTRATION_MAX / 2));
            nRowRectStartY = TABLE_CONCENTRATION_ROW_TITLE_START_Y + TABLE_CONCENTRATION_ROW_HEIGHT
                             + (i % (CALIBRATOR_CONCENTRATION_MAX / 2)) * TABLE_CONCENTRATION_ROW_HEIGHT;
            rect.x0=nRowRectStartX;
            rect.y0=nRowRectStartY- TITLESBAR_HEIGHT;
            rect.x1 = rect.x0 + TABLE_ABS1_COLUMN_PRACTICAL - TABLE_ABS1_COLUMN_NO;
            rect.y1 = rect.y0 + TABLE_CONCENTRATION_SELECT_HEIGHT ;
            sprintf(ConvertStr, "%02d", i+1);
            rect.x0 += 5;
            GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);


            if( (i==5)&&( SystemPrameter.CaliMode!=CALI_MODE_FACTORY ) )
						{
              strcpy(ConvertStr, " >4.0");
            }
						else
						{
							 sprintf(ConvertStr, "%1.3f", AbsCali.dABS[i]);
						}
            if( (ExpEnable == EXP_ABS)&&(m_CurrentAbs==i) )
            {
                GUI_SetColor(0x000000);
                GUI_FillRect(rect.x0+TABLE_ABS1_COLUMN_CAL-TABLE_ABS1_COLUMN_NO, rect.y0 , rect.x1, rect.y1 );
                GUI_SetColor(0xffffff);
            }
            rect.x1 -= 25;
            GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_RIGHT | GUI_TA_VCENTER);


            rect.x1 = nRowRectStartX + TABLE_ABS1_COLUMN_ERROR - TABLE_ABS1_COLUMN_NO;
            sprintf(ConvertStr, "%1.3f", AbsCali.dABSPractical[i]);
            if( CalibrateFlag==0)
            {
                GUI_SetColor(COLOR_PAINT_TXT_DIS);
            }
            else if( (ExpEnable == EXP_PRACTICAL_ABS)&&(m_CurrentAbs==i) )
            {
                GUI_SetColor(0x000000);
                GUI_FillRect(rect.x0+TABLE_ABS1_COLUMN_PRACTICAL-TABLE_ABS1_COLUMN_NO, rect.y0 , rect.x1, rect.y1 );
                GUI_SetColor(0xffffff);
            }
            else GUI_SetColor(0x0);
            rect.x1-= 25;
            GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_RIGHT | GUI_TA_VCENTER);

            if( CalibrateFlag==0)
            {
                GUI_SetColor(COLOR_PAINT_TXT_DIS);
            }
            else GUI_SetColor(0x000000);
            //AbsCali.dABSError[i] = AbsCali.dABSPractical[i] - AbsCali.dABS[i];
            rect.x1 = nRowRectStartX + TABLE_CONCENTRATION_SELECT_WIDTH;
            rect.x1 -= 5;
            if(CalibrateFlag==0)
            {
                GUI_DispStringInRect(" ", &rect, GUI_TA_RIGHT | GUI_TA_VCENTER);
            }
            else
            {
							  if( (i==5)&&( SystemPrameter.CaliMode!=CALI_MODE_FACTORY ) )
								{
									  GUI_DispStringInRect(" ", &rect, GUI_TA_RIGHT | GUI_TA_VCENTER);
								}
								else
								{
										sprintf(ConvertStr, "%1.3f", Used_AbsCali[SystemPrameter.nChannelCurrent][i]);
										GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_RIGHT | GUI_TA_VCENTER);
								}
            }
        }
    }
    break;
    case WM_NOTIFY_PARENT:
    {
        Id = WM_GetId(pMsg->hWinSrc);       // Id of widget
        NCode = pMsg->Data.v;               // Notification code
        // switch (NCode)
        if(RemoteInfo_PC.RemoteFlag)
        {
            break;
        }
        else if( (KeyPadAsc.UseFlag == KEYPAD_BUSY)||(KeyPadNum.UseFlag == KEYPAD_BUSY)||(PromptMenu.InterfaceStatus==PROMPT_MENU_BUSY) )
        {
            break;
        }
        else if(TouchKey.KeyStatus)
        {
            break;
        }
        else if (NCode == WM_NOTIFICATION_RELEASED)
        {
            if (Id == ID_ABS_BUTTON)   //工具栏 Off
            {
                if(CalibrateFlag==0)CalibrateFlag=1;
                else CalibrateFlag=0;
                if( CalibrateFlag==0)
                {
                    BUTTON_SetText(WM_GetDialogItem(AbsWin,ID_ABS_BUTTON), BUTTON_ABSDLG_OFF[SystemPrameter.SystemLanguage]);
                }
                else
                {
                    BUTTON_SetText(WM_GetDialogItem(AbsWin,ID_ABS_BUTTON), BUTTON_ABSDLG_ON[SystemPrameter.SystemLanguage]);
                }
                TouchKey.KeyStatus=1;
                SystemPrameter.AbsCaliEnable=CalibrateFlag;
                WM_Invalidate(AbsWin);
            }
            else   if (Id == ID_ABS_BUTTON+1)   //工具栏 Clear all
            {
							  if( SystemPrameter.CaliMode==CALI_MODE_FACTORY ) //工厂模式
								{
										for(i = 0; i< CALIBRATOR_ABS_MAX; i++) //?
										{
												SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABS[i] = -1.0;
												AbsCali.dABS[i] = -1.0;
												SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABSPractical[i]=0.0;
												SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABSError[i]=0.0;
												Used_AbsCali[SystemPrameter.nChannelCurrent][i]=0.0;
										}
								}
								else// if( SystemPrameter.CaliMode==CALI_MODE_FACTORY ) //工厂模式
								{
										for(i = 0; i< CALIBRATOR_ABS_MAX; i++) //?
										{
											  SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABS[i] = -1.0;
												SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABSPractical[i]=0.0;
												SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABSError[i]=0.0;
											
											
											
												SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent].dABS[i] = -1.0;
												AbsCali.dABS[i] = -1.0;
												SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent].dABSPractical[i]=0.0;
												SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent].dABSError[i]=0.0;
												Used_AbsCali[SystemPrameter.nChannelCurrent][i]=0.0;
										}
								}
							/*	for(j=0; j<96; j++)
								{
										dABS[SystemPrameter.nChannelCurrent+1][0][j]=0.0;
										dABS[SystemPrameter.nChannelCurrent+1][1][j]=0.0;
								}*/
							  
                TouchKey.KeyStatus=1;
                m_CurrentAbs=0;
                WM_Invalidate(AbsWin);
            }
            else if (Id == ID_ABS_BUTTON+2)   //工具栏第4个按钮  Ok
            {
                /*
                for ( i = 0; i < CALIBRATOR_ABS_MAX; i++)
                {
                if (AbsCali.dABS[i] < 0.0f)
                {
                break;
                }
                AbsCali.dABSError[i] = AbsCali.dABSPractical[i] - AbsCali.dABS[i];
                }
                memcpy(&(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), &AbsCali, sizeof(ABS_CAL));
                */ // wwy
                SystemPrameter.nChannelCurrent = (SystemPrameter.nChannelCurrent + 1) % ABS_CHANNEL_MAX;			
                //E2pSaveAdvancePra();//保存高级参数
							  SystemPrameter.AbsCaliEnable=CalibrateFlag; 
							  
						 
							  
							  if( SystemPrameter.CaliMode==CALI_MODE_FACTORY ) 
							  {
                    SpiSaveAbs();        //工厂模式 
							  }
								else
								{
									if(SystemPrameter.AbsCaliEnable!=SystemPrameter.AbsCaliEnableBack)
									{
											if(SpiReadAbs()==SPI_OK)
											{										
												 SystemPrameter.AbsCaliEnable=CalibrateFlag; 
												 SpiSaveAbs();        //工厂模式 	
											}	
								  }
                  SpiSaveAbs2();          //用户模式									
								}
							
							
	 
                //lgj171116出故障则报警
                //保存到存贮器中,后面加入
                TouchKey.KeyStatus=1;
                channel_auto_plus_flag=0;
                WM_DeleteWindow(AbsWin);
                WM_ShowWindow(ProtocolWin);
                //gSystem.MenuRefreshFlag = 1;
                gSystem.SystemInterface = MI_MAITENACE;

                channel_auto_plus_flag=0;
                alrealay_send_move=0;
                AbsCalibration_auto_flag=0; //可以出报告
                AbsCalibration_auto_flag_end=0;//恢复正常
                //gSystem.TitleButtonEnable = 1;
                BoardInf.bHasData=0;//不能查看数据
            }
            else if (Id == ID_ABS_BUTTON + 3)   //工具栏第4个按钮  Cancel
            {
							 // SpiReadAbs2(); //用户模式
							  //if( SystemPrameter.CaliMode==CALI_MODE_FACTORY ) 
							  //{
                    SpiReadAbs();  //工厂模式 
							 // }
							
                WM_DeleteWindow(AbsWin);
                WM_ShowWindow(ProtocolWin);
                //gSystem.MenuRefreshFlag = 1;
                // gSystem.SystemInterface = MI_RUN;
                gSystem.SystemInterface = MI_MAITENACE;
                TouchKey.KeyStatus=1;
                channel_auto_plus_flag=0;
                alrealay_send_move=0;
                AbsCalibration_auto_flag=0; //可以出报告
                AbsCalibration_auto_flag_end=0;//恢复正常
                //gSystem.TitleButtonEnable = 1;
							  BoardInf.bHasData=0;//不能查看数据
            }
            else if (Id == ID_ABS_BUTTON + 4)   //工具栏第5个按钮  标准值导入
            {
                if(UsbOpenFile_read_data()== FR_OK)
                {
                    SystemPrameter.nChannelCurrent=0;
									  if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)
										{
                       memcpy(&AbsCali, &(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
										}
										else
										{
											 memcpy(&AbsCali, &(SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
											 for(j=0;j<ABS_CHANNEL_MAX;j++)
											 {
													 memcpy(&(SystemPrameter.AbsCali[j]), &(SystemPrameter.AbsCali2[j]), sizeof(ABS_CAL));
											 }
										}
                    TouchKey.KeyStatus=1;
                    WM_Invalidate(AbsWin);
                    strcpy(PromptMenu.InputStr,BUTTON_ABSDLG_DATA_INPUT_SUCCESS[SystemPrameter.SystemLanguage]);//数据导入成功
                    Prompt_Interface(PROMPT_WARMING);
                }
                else if(UsbOpenFile_read_data()== 4)  //打开文件失败
                {
                    strcpy(PromptMenu.InputStr,BUTTON_ABSDLG_OPEN_FILE_FAIL[SystemPrameter.SystemLanguage]);//请插入U盘
                    Prompt_Interface(PROMPT_WARMING);
                }
                else
                {
                    strcpy(PromptMenu.InputStr,BUTTON_ABSDLG_U_PAN[SystemPrameter.SystemLanguage]);//请插入U盘
                    Prompt_Interface(PROMPT_WARMING);
                }

            }
            else if (Id == ID_ABS_BUTTON + 5)   //工具栏第6个按钮   低浓度测量
            {
                BoardInf.KineticPara.Enable=0;
                BoardInf.ShakeEnable=0;
                BoardInf.Filter2Locate=-1;
                AbsCalibration_auto_flag_end=0;
                AbsCalibration_auto_flag=1;  //不出报告
                TouchKey.KeyStatus=1; 
                ExpEnable = EXP_ABS_AUTO_LOW;
                AbsCal_si=0;
                start_test_flag=0;

            }
            else if (Id == ID_ABS_BUTTON + 6)   //工具栏第6个按钮   高浓度测量
            {
                BoardInf.KineticPara.Enable=0;
                BoardInf.ShakeEnable=0;
                BoardInf.Filter2Locate=-1;
                AbsCalibration_auto_flag_end=0;
                AbsCalibration_auto_flag=1;  //不出报告
                TouchKey.KeyStatus=1;
                ExpEnable =EXP_ABS_AUTO_HIGH;
                AbsCal_si=0;
                start_test_flag=0;

            }
            else if (Id == ID_ABS_BUTTON + 7)   //工具栏第7个按钮   数据导出
            {
                //Usb_data_file_export_flag=1;
                ExpEnable =EXP_EXPORT;
                TouchKey.KeyStatus=1;
            }
            break;
        }
    }
    break;
    default:
        WM_DefaultProc(pMsg);
        break;
    }
}




void AbsCalibration_Interface(void)
{
    //备份参数
	  unsigned char i,j;
	
    SystemPrameter.nChannelCurrent=0;
    CalibrateFlag=SystemPrameter.AbsCaliEnable;
	  SystemPrameter.AbsCaliEnableBack=SystemPrameter.AbsCaliEnable;
	
	  if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)  //工厂模式
		{
			 SpiReadAbs();
			 memcpy(&AbsCali, &(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
		}
		else                                            //用户模式
		{
       memcpy(&AbsCali, &(SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
		
			    //memcpy(&(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), &(SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
			    
			 //for(i = 0; i< CALIBRATOR_ABS_MAX; i++) 
			 //{
				     for(j=0;j<ABS_CHANNEL_MAX;j++)
				     {
							   memcpy(&(SystemPrameter.AbsCali[j]), &(SystemPrameter.AbsCali2[j]), sizeof(ABS_CAL));
								 SystemPrameter.AbsCali[j].dABS[5] = -1.0;
						 }
				
    }
	
 
		
    ExpEnable = 0;
    m_CurrentAbs=0;

    AbsWin = WM_CreateWindowAsChild(CONTENTBAR_POSX, CONTENTBAR_POSY, CONTENTBAR_WIDTH, CONTENTBAR_HEIGHT, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbAbsCalibration, 0);
    WM_BringToTop(AbsWin);
}


void AbsCalibration_Scan(void)
{
    if (TouchKey.KeyStatus==0)
    {
        unsigned char i;

        int nRowRectStartX,nRowRectStartY,nABSStartX,nABSEndX;

        GUI_RECT rect;
        GUI_PID_STATE TouchState;

        GUI_PID_GetState(&TouchState);
        if (TouchState.Pressed)
        {
            if ((TouchState.x >= ABS_PLUS_BUTTON_START_X) && (TouchState.x <= ABS_PLUS_BUTTON_END_X) &&
                    (TouchState.y >= ABS_PLUS_BUTTON_START_Y) && (TouchState.y <= ABS_PLUS_BUTTON_END_Y))
				 {
                //memcpy(&(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), &AbsCali, sizeof(ABS_CAL));
                if (SystemPrameter.nChannelCurrent>0)
                    SystemPrameter.nChannelCurrent = (SystemPrameter.nChannelCurrent - 1) % ABS_CHANNEL_MAX;
                else
                {
                    SystemPrameter.nChannelCurrent = (SystemPrameter.nChannelCurrent + ABS_CHANNEL_MAX - 1) % ABS_CHANNEL_MAX;
                }
								if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)  //工厂模式
								{
                    memcpy(&AbsCali, &(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
								}
								else
								{
									 memcpy(&AbsCali, &(SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
								}
                TouchKey.KeyStatus=1;
                WM_Invalidate(AbsWin);
            }
						
            
            else if 		((TouchState.x >= ABS_MINUS_BUTTON_START_X) && (TouchState.x <= ABS_MINUS_BUTTON_END_X) &&
                     (TouchState.y >= ABS_MINUS_BUTTON_START_Y) && (TouchState.y <= ABS_MINUS_BUTTON_END_Y))
						{
                // memcpy(&(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), &AbsCali, sizeof(ABS_CAL));//wwy
                SystemPrameter.nChannelCurrent = (SystemPrameter.nChannelCurrent + 1) % ABS_CHANNEL_MAX;
							  if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)  //工厂模式
								{
                    memcpy(&AbsCali, &(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
								}
								else
								{
									  memcpy(&AbsCali, &(SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
								}
                TouchKey.KeyStatus=1;
                WM_Invalidate(AbsWin);
            }
           
            else if ((TouchState.x >= ABS_AUTO_BUTTON_START_X) && (TouchState.x <= ABS_AUTO_BUTTON_END_X) &&
                     (TouchState.y >= ABS_AUTO_BUTTON_START_Y) && (TouchState.y <= ABS_AUTO_BUTTON_END_Y))      //自动：开关
            {
                channel_auto_plus_flag=~channel_auto_plus_flag;
                TouchKey.KeyStatus=1;
                WM_Invalidate(AbsWin);
            }
            else
            {
                for (i = 0; i < CALIBRATOR_ABS_MAX; i++)
                {
                    nRowRectStartX = TABLE_ABS1_COLUMN_NO + TABLE_CONCENTRATION_WIDTH * (i
                                     / (CALIBRATOR_CONCENTRATION_MAX / 2));
                    nRowRectStartY = TABLE_CONCENTRATION_ROW_TITLE_START_Y + TABLE_CONCENTRATION_ROW_HEIGHT
                                     + (i % (CALIBRATOR_CONCENTRATION_MAX / 2)) * TABLE_CONCENTRATION_ROW_HEIGHT;
                    rect.x0 = nRowRectStartX;
                    rect.x1 = nRowRectStartX + TABLE_CONCENTRATION_SELECT_WIDTH;
                    rect.y0 = nRowRectStartY;
                    rect.y1 = nRowRectStartY + TABLE_CONCENTRATION_SELECT_HEIGHT;
                    if (TouchState.x > rect.x0 && TouchState.x < rect.x1  && TouchState.y > rect.y0 && TouchState.y < rect.y1)
                    {
                        if(i == m_CurrentAbs)  //保证从第1行开始，中间不丢行
                        {
                            nABSStartX = TABLE_ABS1_COLUMN_CAL + TABLE_CONCENTRATION_WIDTH * (i/ (CALIBRATOR_CONCENTRATION_MAX / 2));
                            nABSEndX = TABLE_ABS1_COLUMN_PRACTICAL + TABLE_CONCENTRATION_WIDTH * (i/ (CALIBRATOR_CONCENTRATION_MAX / 2));

                            if (TouchState.x > nABSStartX && TouchState.x < nABSEndX )
                            {
                                TouchKey.KeyStatus=1;
                                if (AbsCali.dABS[i] < 0.0f)
                                {
                                    AbsCali.dABS[i] = 0.0f;
                                } //if(abs_cal.dABS[i] < 0.0)

                                if (AbsCali.dABSPractical[i] < 0.0f)
                                {
                                    AbsCali.dABSPractical[i] = 0.0f;
                                } //if(abs_cal.dABSPractical[i] < 0.0f)
                                ExpEnable = EXP_ABS;
                                TouchKey.KeyStatus = 1;
                                WM_Invalidate(AbsWin);
                            }//if (TouchState.x > nABSStartX && TouchState.x < nABSEndX )
                            else
                            {
                                nABSStartX = TABLE_ABS1_COLUMN_PRACTICAL + TABLE_CONCENTRATION_WIDTH * (i/ (CALIBRATOR_CONCENTRATION_MAX / 2));
                                nABSEndX = TABLE_ABS1_COLUMN_ERROR + TABLE_CONCENTRATION_WIDTH * (i/ (CALIBRATOR_CONCENTRATION_MAX / 2));
                                if (TouchState.x > nABSStartX && TouchState.x < nABSEndX )
                                {
                                    if (AbsCali.dABS[i] < 0.0f)
                                    {
                                        AbsCali.dABS[i] = 0.0f;
                                    } //if(abs_cal.dABS[i] < 0.0)

                                    if (AbsCali.dABSPractical[i] < 0.0f)
                                    {
                                        AbsCali.dABSPractical[i] = 0.0f;
                                    } //if(abs_cal.dABSPractical[i] < 0.0)
                                    ExpEnable = EXP_PRACTICAL_ABS;
                                    TouchKey.KeyStatus = 1;
                                    WM_Invalidate(AbsWin);
                                }//  if (TouchState.x > nABSStartX && TouchState.x < nABSEndX )
                            }////if (TouchState.x > nABSStartX && TouchState.x < nABSEndX ) else
                        }//if(i == m_CurrentAbs)
                        else
                        {
                            TouchKey.KeyStatus=1;
                            m_CurrentAbs = i;
                            WM_Invalidate(AbsWin);
                        }
                        break;

                    } //if (TouchState.x > nABSStartX && TouchState.x < nABSEndX  && TouchState.y > rect.y0 && TouchState.y < rect.y1)
                } //for(int i = 0; i < CALIBRATOR_ABS_MAX; i++)
            }//else
        }//else if (TouchState.Pressed)
    }//if (TouchKey.KeyStatus==0)
}


//标准值abs_cal.dABSPractical[i], AbsCali.dAB
//实测值 abs_cal.dABSPractical[i],AbsCali.dABSPractical
//校准偏差=标准值abs_cal.dABSPractical[i]-实测值 abs_cal.dABSPractical[i]
void AbsCalibration_Go(void)
{
    u16 i,j,k;
    float temp,temp_old;
    //低浓度校准
    if (ExpEnable ==EXP_ABS_AUTO_LOW)
    {
			  if(channel_auto_plus_flag==0) //通道自动加（检测多个通道)
        {
            if(AbsCal_si<8)
            {
                if(start_test_flag==0)
                {
                    //if(SystemPrameter.AbsCali[AbsCal_si].dABS_flag==1)//通道启用lugj20180911
										if( ((SystemPrameter.AbsCali[AbsCal_si].dABS_flag==1)&&(SystemPrameter.CaliMode==CALI_MODE_FACTORY))//通道有效lugj20180910
                     || ((SystemPrameter.AbsCali2[AbsCal_si].dABS_flag==1)&&(SystemPrameter.CaliMode!=CALI_MODE_FACTORY)) )
										 //|| ((AbsCal_si<6)&&(SystemPrameter.CaliMode!=CALI_MODE_FACTORY)) )
                    {
                        start_test_flag=1;
                    }
                    else
                    {
                        AbsCal_si++;
                    }
                }
                else //start_test_flag==1
                {
                    if((AbsCalibration_auto_flag_end==0)&&(alrealay_send_move==0))
                    {
                        BoardInf.Filter1Locate=AbsCal_si;//通道1
                        MCU_StartStop(1);//开始测量
                        alrealay_send_move=1;
                    }
                    else if((AbsCalibration_auto_flag_end==1)&&(alrealay_send_move==1))
                    {
											  if(CalibrateFlag==0)//关闭状态下为实测值
                        {
													   if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)  //工厂模式
														 {
																SystemPrameter.AbsCali[AbsCal_si].dABSPractical[0]=(dABS[0][0][3 * 12 + 11]+dABS[0][0][4 * 12 + 11]+dABS[0][0][5 * 12 + 11])/3;//D12+E12+F12
																SystemPrameter.AbsCali[AbsCal_si].dABSPractical[1]=(dABS[0][0][3 * 12 + 9]+dABS[0][0][4 * 12 + 9]+dABS[0][0][5 * 12 + 9])/3;//D10+E10+F10
																SystemPrameter.AbsCali[AbsCal_si].dABSPractical[2]=(dABS[0][0][3 * 12 + 7]+dABS[0][0][4 * 12 + 7]+dABS[0][0][5 * 12 + 7])/3;//D8+E8+F8
																SystemPrameter.AbsCali[AbsCal_si].dABSPractical[3]=(dABS[0][0][3 * 12 + 5]+dABS[0][0][4 * 12 + 5]+dABS[0][0][5 * 12 + 5])/3;//D6+E6+F6
																SystemPrameter.AbsCali[AbsCal_si].dABSError[0]=SystemPrameter.AbsCali[AbsCal_si].dABSPractical[0]-SystemPrameter.AbsCali[AbsCal_si].dABS[0];
																SystemPrameter.AbsCali[AbsCal_si].dABSError[1]=SystemPrameter.AbsCali[AbsCal_si].dABSPractical[1]-SystemPrameter.AbsCali[AbsCal_si].dABS[1];
																SystemPrameter.AbsCali[AbsCal_si].dABSError[2]=SystemPrameter.AbsCali[AbsCal_si].dABSPractical[2]-SystemPrameter.AbsCali[AbsCal_si].dABS[2];
																SystemPrameter.AbsCali[AbsCal_si].dABSError[3]=SystemPrameter.AbsCali[AbsCal_si].dABSPractical[3]-SystemPrameter.AbsCali[AbsCal_si].dABS[3];
											      }
														else
														{
															  			for(i=0; i<6; i++) //6条  4、5、6、7、8、9（C4-C9，D4-D9，E4-E9，F4-F9）
																			{
																				temp=0;
																				if(CalibrateFlag==0) //校准禁用状态下
																				{
																								for(j=2; j<6; j++)//中间4个C、D、E、F
																								{
																										temp=temp+dABS[0][0][j * 12 + 3+i];  //第4列开始
																								}
																								SystemPrameter.AbsCali2[AbsCal_si].dABSPractical[i]=temp/4;//保存到序号4
																								
																								SystemPrameter.AbsCali2[AbsCal_si].dABSError[i]=SystemPrameter.AbsCali2[AbsCal_si].dABSPractical[i]
																																															-SystemPrameter.AbsCali2[AbsCal_si].dABS[i];
																				        
																								if(AbsCal_si<5)
																								{
																									 SystemPrameter.AbsCali[AbsCal_si].dABSPractical[i]=SystemPrameter.AbsCali2[AbsCal_si].dABSPractical[i];
																									 SystemPrameter.AbsCali[AbsCal_si].dABSError[i]=SystemPrameter.AbsCali2[AbsCal_si].dABSError[i];
																								}
																				
																				}
																			}
														}
											  }
                        else	 //存储启用状态下测量值
                        {
													if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)  //工厂模式
													{
                            for(j=0; j<4; j++)
                            {
                                temp_old=0.0;
                                for(i=3; i<6; i++)
                                {
                                    if(dABS[0][0][i * 12 + 11-2*j]>SystemPrameter.AbsCali[AbsCal_si].dABS[0])
                                    {
                                        temp=dABS[0][0][i * 12 + 11-2*j]-SystemPrameter.AbsCali[AbsCal_si].dABS[0];
                                    }
                                    else
                                    {
                                        temp=SystemPrameter.AbsCali[AbsCal_si].dABS[0]-dABS[0][0][i * 12 + 11-2*j];
                                    }
                                    if(temp>=temp_old)
                                    {
                                        temp_old=temp;
                                        Used_AbsCali[AbsCal_si][j]=dABS[0][0][i * 12 + 11-2*j]; //D12+E12+F12 偏差最大值
                                    }
                                }
                            }
													}
													else
													{
																for(i=0; i<6; i++) //6条  4、5、6、7、8、9（C4-C9，D4-D9，E4-E9，F4-F9）
																{
																		temp=0.0;
																		for(j=2; j<6; j++)
																		{
																				temp=temp+dABS[0][0][j * 12 + 3+i];  //第2列开始
																		}
																		Used_AbsCali[AbsCal_si][i]=temp/4;
																}
													}

                        }
												
												if(SystemPrameter.CaliMode!=CALI_MODE_FACTORY) 
												{
														if(CalibrateFlag==0)
														{
																SystemPrameter.AbsCali2[AbsCal_si].dABSPractical[8]=0;  //第九ge为0
																SystemPrameter.AbsCali2[AbsCal_si].dABSError[8]=0;
														}
														else
														{
																Used_AbsCali[AbsCal_si][8]=0;
														}	
											  }
												
                        for(k=0; k<96; k++)
                        {
                            dABS[AbsCal_si+1][0][k]=dABS[0][0][k];
                        }
                        AbsCalibration_auto_flag_end=0;
                        alrealay_send_move=0;
                        start_test_flag=0;
                        SystemPrameter.nChannelCurrent=AbsCal_si;
												if(SystemPrameter.CaliMode==CALI_MODE_FACTORY) 
												{
                           memcpy(&AbsCali, &(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
												}
												else
												{
													 memcpy(&AbsCali, &(SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
												}
                        WM_Invalidate(AbsWin);
                        AbsCal_si++;
                    }//else if((AbsCalibration_auto_flag_end==1)&&(alrealay_send_move==1))
                }
            }//if(AbsCal_si<8)
            else
            {
                AbsCalibration_auto_flag=0; //可以出报告
                AbsCalibration_auto_flag_end=0;//恢复正常
                ExpEnable =0;
                AbsCal_si=8;
                //TouchKey.KeyStatus = 1;
                start_test_flag=0;
            }
        }
        else  // if(channel_auto_plus_flag==0) //通道自动加（检测多个通道)不自动校准
        {
           // if(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABS_flag==1)
						if( ((SystemPrameter.AbsCali[AbsCal_si].dABS_flag==1)&&(SystemPrameter.CaliMode==CALI_MODE_FACTORY))//通道有效lugj20180910
             || ((SystemPrameter.AbsCali2[AbsCal_si].dABS_flag==1)&&(SystemPrameter.CaliMode!=CALI_MODE_FACTORY)) )
						 //|| ((AbsCal_si<6)&&(SystemPrameter.CaliMode!=CALI_MODE_FACTORY)) )
            {
                if((AbsCalibration_auto_flag_end==0)&&(alrealay_send_move==0))
                {
                    AbsCal_si=SystemPrameter.nChannelCurrent;
                    BoardInf.Filter1Locate= SystemPrameter.nChannelCurrent;//通道1
                    MCU_StartStop(1);//开始测量
                    alrealay_send_move=1;
                }
                else if((AbsCalibration_auto_flag_end==1)&&(alrealay_send_move==1))
                {
									  
                    if(CalibrateFlag==0)
                    {
											  if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)  //工厂模式
												{
														SystemPrameter.AbsCali[AbsCal_si].dABSPractical[0]=(dABS[0][0][3 * 12 + 11]+dABS[0][0][4 * 12 + 11]+dABS[0][0][5 * 12 + 11])/3;//D12+E12+F12
														SystemPrameter.AbsCali[AbsCal_si].dABSPractical[1]=(dABS[0][0][3 * 12 + 9]+dABS[0][0][4 * 12 + 9]+dABS[0][0][5 * 12 + 9])/3;//D10+E10+F10
														SystemPrameter.AbsCali[AbsCal_si].dABSPractical[2]=(dABS[0][0][3 * 12 + 7]+dABS[0][0][4 * 12 + 7]+dABS[0][0][5 * 12 + 7])/3;//D8+E8+F8
														SystemPrameter.AbsCali[AbsCal_si].dABSPractical[3]=(dABS[0][0][3 * 12 + 5]+dABS[0][0][4 * 12 + 5]+dABS[0][0][5 * 12 + 5])/3;//D6+E6+F6
														SystemPrameter.AbsCali[AbsCal_si].dABSError[0]=SystemPrameter.AbsCali[AbsCal_si].dABSPractical[0]-SystemPrameter.AbsCali[AbsCal_si].dABS[0];
														SystemPrameter.AbsCali[AbsCal_si].dABSError[1]=SystemPrameter.AbsCali[AbsCal_si].dABSPractical[1]-SystemPrameter.AbsCali[AbsCal_si].dABS[1];
														SystemPrameter.AbsCali[AbsCal_si].dABSError[2]=SystemPrameter.AbsCali[AbsCal_si].dABSPractical[2]-SystemPrameter.AbsCali[AbsCal_si].dABS[2];
														SystemPrameter.AbsCali[AbsCal_si].dABSError[3]=SystemPrameter.AbsCali[AbsCal_si].dABSPractical[3]-SystemPrameter.AbsCali[AbsCal_si].dABS[3];
												}
												else
												{
													 for(i=0; i<6; i++)
													 {
														  temp=0.0;
                              for(j=2; j<6; j++)
                              {
                                temp=temp+dABS[0][0][j * 12 + 3+i];
                              }
                              SystemPrameter.AbsCali2[AbsCal_si].dABSPractical[i]=temp/4; //禁用状态下显示的值
                              SystemPrameter.AbsCali2[AbsCal_si].dABSError[i]=SystemPrameter.AbsCali2[AbsCal_si].dABSPractical[i]
                                                -SystemPrameter.AbsCali2[AbsCal_si].dABS[i];
															if(AbsCal_si<5)
															{
															   SystemPrameter.AbsCali[AbsCal_si].dABSPractical[i]=SystemPrameter.AbsCali2[AbsCal_si].dABSPractical[i];
                                 SystemPrameter.AbsCali[AbsCal_si].dABSError[i]=SystemPrameter.AbsCali2[AbsCal_si].dABSError[i];
															}
													 }
												}
									  } 
                    else	 //(启用状态下测量值)
                    {
											if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)  //工厂模式
											{
                        for(j=0; j<4; j++)
                        {
                            temp_old=0.0;
                            for(i=3; i<6; i++)
                            {
                                if(dABS[0][0][i * 12 + 11-2*j]>SystemPrameter.AbsCali[AbsCal_si].dABS[j])
                                {
                                    temp=dABS[0][0][i * 12 + 11-2*j]-SystemPrameter.AbsCali[AbsCal_si].dABS[j];
                                }
                                else
                                {
                                    temp=SystemPrameter.AbsCali[AbsCal_si].dABS[j]-dABS[0][0][i * 12 + 11-2*j];
                                }
                                if(temp>=temp_old)
                                {
                                    temp_old=temp;
                                    Used_AbsCali[AbsCal_si][j]=dABS[0][0][i * 12 + 11-2*j]; //D12+E12+F12 偏差最大值
                                }
                            }
                        }
											}
											else
											{
													for(i=0; i<6; i++) //6条  4、5、6、7、8、9（C4-C9，D4-D9，E4-E9，F4-F9）
													{
															temp=0.0;
															for(j=2; j<6; j++)//C\D\E\F
															{
																	temp=temp+dABS[0][0][j * 12 + 3+i];  //第2列开始
															}
															Used_AbsCali[AbsCal_si][i]=temp/4;
													}
											}

                    }
                    for(k=0; k<96; k++)
                    {
                        dABS[AbsCal_si+1][0][k]=dABS[0][0][k];
                    }
                    AbsCalibration_auto_flag_end=0;
                    alrealay_send_move=0;
                    start_test_flag=0;
                    //SystemPrameter.nChannelCurrent=AbsCal_si;
										if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)  //工厂模式
										{
                         memcpy(&AbsCali, &(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
										}
										else
										{
											  memcpy(&AbsCali, &(SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
										}
                    WM_Invalidate(AbsWin);
                    AbsCalibration_auto_flag=0; //可以出报告
                    AbsCalibration_auto_flag_end=0;//恢复正常
                    ExpEnable =0;
                    AbsCal_si=8;
                    //TouchKey.KeyStatus = 1;
                    start_test_flag=0;
                }
            }
            else
            {
                AbsCalibration_auto_flag=0; //可以出报告
                AbsCalibration_auto_flag_end=0;//恢复正常
                ExpEnable =0;
                AbsCal_si=8;
                //TouchKey.KeyStatus = 1;
                start_test_flag=0;
            }
        }
    }
    //高浓度校准
    else if (ExpEnable ==EXP_ABS_AUTO_HIGH)
    {
        if(channel_auto_plus_flag==0)//通道自动加(检测多个通道)lugj20180910
        {
            if(AbsCal_si<8)
            {
                if(start_test_flag==0) 
                {
                    if(SystemPrameter.AbsCali[AbsCal_si].dABS_flag==1)
										{
                        start_test_flag=1;
                    }
                    else
                    {
                        AbsCal_si++;
                    }
                }
                else //start_test_flag==1
                {
                    if((AbsCalibration_auto_flag_end==0)&&(alrealay_send_move==0))
                    {
                        BoardInf.Filter1Locate=AbsCal_si;//通道1
                        MCU_StartStop(1);//开始测量
                        alrealay_send_move=1;
                    }
                    else if((AbsCalibration_auto_flag_end==1)&&(alrealay_send_move==1))
                    {
                          for(i=0; i<4; i++) //4条  6、7、8、9（C6-C9，D6-D9，E6-E9，F6-F9）
                          {
                            temp=0;
                            if(CalibrateFlag==0)
                            {
																		for(j=2; j<6; j++)//中间4个C、D、E、F
																		{
																				temp=temp+dABS[0][0][j * 12 + 5+i];  //第6列开始
																		}
																		SystemPrameter.AbsCali[AbsCal_si].dABSPractical[4+i]=temp/4;//保存到序号4
																		
																		SystemPrameter.AbsCali[AbsCal_si].dABSError[4+i]=SystemPrameter.AbsCali[AbsCal_si].dABSPractical[4+i]-SystemPrameter.AbsCali[AbsCal_si].dABS[4+i];
													  }
                            else
                            {
                                temp_old=0.0;
                                for(j=2; j<6; j++)
                                {
                                    if(dABS[0][0][j * 12 + 5+i]>SystemPrameter.AbsCali[AbsCal_si].dABS[4+i])
                                    {
                                        temp=dABS[0][0][j * 12 + 5+i]-SystemPrameter.AbsCali[AbsCal_si].dABS[4+i];
                                    }
                                    else
                                    {
                                        temp=SystemPrameter.AbsCali[AbsCal_si].dABS[4+i]-dABS[0][0][j * 12 + 5+i];
                                    }
                                    if(temp>=temp_old)
                                    {
                                        temp_old=temp;
                                        Used_AbsCali[AbsCal_si][4+i]=dABS[0][0][j * 12 + 5+i];
                                    }
                                }
                            }
                        }
                        if(CalibrateFlag==0)
                        {
                            SystemPrameter.AbsCali[AbsCal_si].dABSPractical[8]=0;  //第九ge为0
                            SystemPrameter.AbsCali[AbsCal_si].dABSError[8]=0;
                        }
                        else
                        {
                            Used_AbsCali[AbsCal_si][8]=0;
                        }
											
											
                        for(k=0; k<96; k++)
                        {
                            dABS[AbsCal_si+1][1][k]=dABS[0][0][k];
                        }
                        AbsCalibration_auto_flag_end=0;
                        alrealay_send_move=0;
                        start_test_flag=0;
                        SystemPrameter.nChannelCurrent=AbsCal_si;
										
                        memcpy(&AbsCali, &(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));
												
                        WM_Invalidate(AbsWin);
                        AbsCal_si++;
                    }
                }
            }
            else
            {
                AbsCalibration_auto_flag=0;     //可以出报告
                AbsCalibration_auto_flag_end=0; //恢复正常
                ExpEnable =0;
                AbsCal_si=8;
                // TouchKey.KeyStatus = 1;
                start_test_flag=0;
            }
        }
        else //不自动校准
        {
            if(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABS_flag==1)
            {
                if((AbsCalibration_auto_flag_end==0)&&(alrealay_send_move==0))
                {
                    AbsCal_si=SystemPrameter.nChannelCurrent;
                    BoardInf.Filter1Locate= SystemPrameter.nChannelCurrent;//通道1
                    MCU_StartStop(1);//开始测量
                    alrealay_send_move=1;
                }
                else if((AbsCalibration_auto_flag_end==1)&&(alrealay_send_move==1))
                {
                    for(i=0; i<4; i++)
                    {
                        temp=0;
                        if(CalibrateFlag==0)
                        {
                            for(j=2; j<6; j++)
                            {
                                temp=temp+dABS[0][0][j * 12 + 5+i];
                            }
                            SystemPrameter.AbsCali[AbsCal_si].dABSPractical[4+i]=temp/4;
                            SystemPrameter.AbsCali[AbsCal_si].dABSError[4+i]=SystemPrameter.AbsCali[AbsCal_si].dABSPractical[4+i]-SystemPrameter.AbsCali[AbsCal_si].dABS[4+i];
                        }
                        else
                        {
                            temp_old=0.0;
                            for(j=2; j<6; j++)
                            {
                                if(dABS[0][0][j * 12 + 5+i]>SystemPrameter.AbsCali[AbsCal_si].dABS[4+i])
                                {
                                    temp=dABS[0][0][j * 12 + 5+i]-SystemPrameter.AbsCali[AbsCal_si].dABS[4+i];
                                }
                                else
                                {
                                    temp=SystemPrameter.AbsCali[AbsCal_si].dABS[4+i]-dABS[0][0][j * 12 + 5+i];
                                }
                                if(temp>=temp_old)
                                {
                                    temp_old=temp;
                                    Used_AbsCali[AbsCal_si][4+i]=dABS[0][0][j * 12 + 5+i];
                                }
                            }
                        }
                    }
                    for(k=0; k<96; k++)
                    {
                        dABS[AbsCal_si+1][1][k]=dABS[0][0][k];
                    }
                    if(CalibrateFlag==0)
                    {
                        SystemPrameter.AbsCali[AbsCal_si].dABSPractical[8]=0;  //第九ge为0
                        SystemPrameter.AbsCali[AbsCal_si].dABSError[8]=0;
                    }
                    else
                    {
                        Used_AbsCali[AbsCal_si][8]=0;
                    }
									
									
                    AbsCalibration_auto_flag_end=0;
                    alrealay_send_move=0;
                    start_test_flag=0;
									
                    memcpy(&AbsCali, &(SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent]), sizeof(ABS_CAL));//不自动校准
									
                    WM_Invalidate(AbsWin);
                    AbsCalibration_auto_flag=0;       //可以出报告
                    AbsCalibration_auto_flag_end=0;   //恢复正常
                    ExpEnable =0;
                    AbsCal_si=8;
                    // TouchKey.KeyStatus = 1;
                    start_test_flag=0;
                }
            }
            else
            {
                AbsCalibration_auto_flag=0; //可以出报告
                AbsCalibration_auto_flag_end=0;//恢复正常
                ExpEnable =0;
                AbsCal_si=8;
                //TouchKey.KeyStatus =1;
                start_test_flag=0;
            }
        }
    }

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

    if (ExpEnable == EXP_ABS)
    {
        sprintf(KeyPadNum.InputValueStr,"%.3f",AbsCali.dABS[m_CurrentAbs]);
        KeyPadNum_Interface(NUM_MENU_FLAG);
        if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
        {
            AbsCali.dABS[m_CurrentAbs]= atof(KeyPadNum.InputValueStr);
					  if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)
						{
               SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABS[m_CurrentAbs]=AbsCali.dABS[m_CurrentAbs];//wwy随时保存
						}
						else
						{
							  SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent].dABS[m_CurrentAbs]=AbsCali.dABS[m_CurrentAbs];//
							
							  SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABS[m_CurrentAbs]=AbsCali.dABS[m_CurrentAbs];//
						}
        }

        ExpEnable =0;
        TouchKey.KeyStatus=1;
        WM_Invalidate(AbsWin);
    }
    else if(ExpEnable == EXP_PRACTICAL_ABS)
    {
        sprintf(KeyPadNum.InputValueStr,"%.3f",AbsCali.dABSPractical[m_CurrentAbs]);
        KeyPadNum_Interface(POINT_MENU_FLAG);
        if ( (KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)&&(KeyPadNum.InputValueStr[0]!=0) )
        {
            AbsCali.dABSPractical[m_CurrentAbs]= atof(KeyPadNum.InputValueStr);
					  if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)
					  {
								SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABSPractical[m_CurrentAbs]=AbsCali.dABSPractical[m_CurrentAbs];  //wwy随时保存
								SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABSError[m_CurrentAbs]=AbsCali.dABSPractical[m_CurrentAbs]-SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABS[m_CurrentAbs];//用于校准
						}
						else//if(SystemPrameter.CaliMode==CALI_MODE_CUSTOMER)
					  {
								SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent].dABSPractical[m_CurrentAbs]=AbsCali.dABSPractical[m_CurrentAbs];  //wwy随时保存
								SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent].dABSError[m_CurrentAbs]=AbsCali.dABSPractical[m_CurrentAbs]
							                                 -SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent].dABS[m_CurrentAbs];//用于校准
							
							  SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABSPractical[m_CurrentAbs]=SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent].dABSPractical[m_CurrentAbs];  
								SystemPrameter.AbsCali[SystemPrameter.nChannelCurrent].dABSError[m_CurrentAbs]=SystemPrameter.AbsCali2[SystemPrameter.nChannelCurrent].dABSError[m_CurrentAbs];
						}
				}
        ExpEnable =0;
        TouchKey.KeyStatus=1;
        WM_Invalidate(AbsWin);
    }
    else if(ExpEnable == EXP_EXPORT)
    {
        //调用文件系统写入U盘
        StartUpPra.EnableUsbCheck=0;
        if(SystemPrameter.CaliMode==CALI_MODE_FACTORY)  //工厂模式
				{
           strcpy(KeyPadAsc.InputValueStr,"AbsCali");
				}
				else //用户模式
				{
					 strcpy(KeyPadAsc.InputValueStr,"AbsCali2");
				}
        KeyPadAscii_Interface(0,PROMPT_RESULT_FILE_NAME);

        if(KeyPadAsc.ReturnKey==KEYPAD_RETURN_ENTER)
        {
            if(ExportAbsCalibrationFile(KeyPadAsc.InputValueStr)== FR_OK)
            {
                strcpy(PromptMenu.InputStr,BUTTON_ABSDLG_DATA_OUTPUT_SUCCESS[SystemPrameter.SystemLanguage]);//数据导出成功
                Prompt_Interface(PROMPT_WARMING);
            }
            else
            {
                strcpy(PromptMenu.InputStr,BUTTON_ABSDLG_U_PAN[SystemPrameter.SystemLanguage]);//请插入U盘
                Prompt_Interface(PROMPT_WARMING);
            }
            StartUpPra.EnableUsbCheck=1;
        }
        ExpEnable =0;
        TouchKey.KeyStatus=1;
    }

}
