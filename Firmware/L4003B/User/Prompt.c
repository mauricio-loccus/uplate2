
#include  "MainTask.h"
#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>


PROMPT_MENU  PromptMenu;


WM_HWIN PromptWin = NULL;

TEXT_Handle  TxtPrompt;
BUTTON_Handle    BtYes,BtNo;





const char STR_SAME_WAVELENGTH[LANGUAGE_TYPES][50] = {"Filters must have different wavelength.", "滤光轮波长不允许相同"}; //2015-3-16

const char PARAMETER_FILE_NOT_REPORT[LANGUAGE_TYPES][50] = {"No report data in this file!", "该文件没有报告数据!"};
const char TEST_INFO_MESSAGE[LANGUAGE_TYPES][TEST_INFO_MAX][50]
= {{"Scan data is saved.", "Please insert USB disk first.", "Int. data is shown on the report section."}
    , {"扫描数据已保存", "请插入U盘", "光强数据已保存在报告界面"}
};


//系统故障信息
const char SYSTEM_ERROR_MESSAGE[LANGUAGE_TYPES][SYSTEM_ERROR_MAX][50]
= {{"Filter wheel control fails.", "Front position error."
        , "Rear position error.", "EEPROM fails."
        , "Origin data is lost.", "Weak", "Too weak"
        , "Too strong", "Too strong bg." //2015-4-3
        , "Mismatched filter wavelength.", "Wrong intensity data."
    }
    , {"滤光轮不能回到初使位置", "前方位置传感器错误"
        , "后方位置传感器错误", "EEPROM存贮错误"
        , "原点数据丢失", "光强不够大", "光强太弱"
        , "光强太强", "本底光强太强"
        , "滤光片波长不匹配 ", "光强数据错误 "
    }
};

/*

//????
const char FILE_ERROR_MESSAGE[LANGUAGE_TYPES][FILE_ERROR_MAX][64]
= {{"Select files first.", "Do you want to delete the sel. files?"
    , "Please insert USB disk first.", "There is no file to import."
, "There is no file to export.", "There is no file to delete.", "There is no file to open."
, "Please change to USB disk mode first.", "Please change to harddisk mode first."
, "Overwrite existing files?", "Save the modified file first?", "The file is already opened."}
, {"请先选择文件", "???????????Demo??????!"
, "????U??", "U??????????"
, "????????", "????????", "????????"
, "?????U????", "??????????"
, "?????????Demo??????","??????????","???????????"}};

//????
const char ANALYSIS_ERROR_MESSAGE[LANGUAGE_TYPES][ANALYSIS_ERROR_MAX][50]
= {
	{"OK.", "More standard samples are needed.", "Curve fitting fails."
, "Only pos. concentration is allowed.", "Only pos. ABS is allowed."
, "Only log concentration is allowed.", "Log concentration is not allowed."
, "Only pos. log concentration is allowed.", "Neg. ABS is not allowed."
, "No valid NC is found.", "No valid PC is found."
, "No concentration result is calculated.", "No QC is found.", "QC result is invalid."
, "Kinetic data is insufficient."
	},
	{"?????", "????????", "????????"
, "????????", "?????????"
, "????????", "????????"
, "??????????", "?????????"
, "??????????", "??????????"
, "????????", "??????", "???????"
, "????????"
	},
};

//??????
const char RUNNING_STATUS_MESSAGE[LANGUAGE_TYPES][RUN_MODE_MAX][50]
= {{"", "", ""
, "", "Measuring now..."
, "Shaking now...", "", ""
, "Calibrating now...", ""}
, {"", "", ""
, "", "??????..."
, "??????...", "", ""
, "??????...", ""}
};




*/
void DispErrCode(void)
{
    /*
    		      char str[100]={0};
    					unsigned char num=0;

    			    if( (gSystem.SystemErrCode&ERRCODE_E2P)||(gSystem.SystemErrCode&ERRCODE_ADVANCE) )
    					{
    						strcat(str,"E703");  //E2PROM??
    						num++;
    					}
    			    if(gSystem.SystemErrCode&ERRCODE_RTC)
    					{
    						if(num>0)
    						{
    							strcat(str,"-");  //RTC??
    						}
    						strcat(str,"E702");  //RTC??
    						num++;
    					}
    			    if(gSystem.SystemErrCode&ERRCODE_UART)
    					{
    						if(num>0)
    						{
    							strcat(str,"-");  //RTC??
    						}
    						strcat(str,"E801");  //RTC??
    						num++;
    					}
    			    if(gSystem.SystemErrCode&ERRCODE_MOTOR_LEVEL)
    					{
    						if(num>0)
    						{
    							strcat(str,"-");  //
    						}
    						strcat(str,"E403");  //?????????
    						num++;
    					}
    			    if(gSystem.SystemErrCode&ERRCODE_MOTOR_MAGNETIC)
    					{
    						if(num>0)
    						{
    							strcat(str,"-");  //
    						}
    						strcat(str,"E415");  //???????????
    						num++;
    					}
    					if(gSystem.SystemErrCode&ERRCODE_MOTOR_MAGNETIC_ROD)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						   strcat(str,"E425");  //????????????
    						}
    						num++;
    					}


    					if(gSystem.SystemErrCode&ERRCODE_EXHAUST_FAN)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						   strcat(str,"E019");
    					  }
    						num++;

    					}
    					if(gSystem.SystemErrCode&ERRCODE_TEMP_FAN)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						   strcat(str,"E009");
    					  }
    						num++;

    					}
    					if(gSystem.SystemErrCode&ERRCODE_SHAKE_LOCK)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						  strcat(str,"E108");  //RTC??
    						}
    						num++;
    					}
    					if(gSystem.SystemErrCodeTemp&ERRCODE_T1)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						  if(gSystem.SystemErrCodeTemp&ERRCODE_T1_OPEN)strcat(str,"E015");        //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T1_SHORT)strcat(str,"E016");  //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T1_OVER)strcat(str,"E011");   //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T1_HEAT)strcat(str,"E018");   //T1??
    						}
    						  num++;

    					}
    					if(gSystem.SystemErrCodeTemp&ERRCODE_T2)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						  if(gSystem.SystemErrCodeTemp&ERRCODE_T2_OPEN)strcat(str,"E025");        //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T2_SHORT)strcat(str,"E026");  //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T2_OVER)strcat(str,"E021");   //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T2_HEAT)strcat(str,"E028");   //T1??

    					  }
    						 num++;
    					}
    					if(gSystem.SystemErrCodeTemp&ERRCODE_T3)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						  if(gSystem.SystemErrCodeTemp&ERRCODE_T3_OPEN)strcat(str,"E035");        //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T3_SHORT)strcat(str,"E036");  //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T3_OVER)strcat(str,"E031");   //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T3_HEAT)strcat(str,"E038");   //T1??
    						}
    						  num++;

    					}
    					if(gSystem.SystemErrCodeTemp&ERRCODE_T4)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						  if(gSystem.SystemErrCodeTemp&ERRCODE_T4_OPEN)strcat(str,"E045");        //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T4_SHORT)strcat(str,"E046");  //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T4_OVER)strcat(str,"E041");   //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T4_HEAT)strcat(str,"E048");   //T1??

    					  }
    						num++;
    					}
    					if(gSystem.SystemErrCodeTemp&ERRCODE_T5)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						  if(gSystem.SystemErrCodeTemp&ERRCODE_T5_OPEN)strcat(str,"E055");        //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T5_SHORT)strcat(str,"E056");  //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T5_OVER)strcat(str,"E051");   //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T5_HEAT)strcat(str,"E058");   //T1??
    						}
    						  num++;
    					}
    					if(gSystem.SystemErrCodeTemp&ERRCODE_T6)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						  if(gSystem.SystemErrCodeTemp&ERRCODE_T6_OPEN)strcat(str,"E065");        //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T6_SHORT)strcat(str,"E066");  //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T6_OVER)strcat(str,"E061");   //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T6_HEAT)strcat(str,"E068");   //T1??
    						}
    						  num++;

    					}
    					if(gSystem.SystemErrCodeTemp&ERRCODE_T7)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						  if(gSystem.SystemErrCodeTemp&ERRCODE_T7_OPEN)strcat(str,"E075");        //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T7_SHORT)strcat(str,"E076");  //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T7_OVER)strcat(str,"E071");   //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T7_HEAT)strcat(str,"E078");   //T1??

    					  }
    						num++;
    					}
    					if(gSystem.SystemErrCodeTemp&ERRCODE_T8)
    					{
    						if(num==DISP_ERR_ROW_MAX )strcat(str,"\n");
    						else if( (num>0)&&(num<DISP_ERR_MAX) )
    						{
    							strcat(str,"-");  //
    						}
    						if(num<DISP_ERR_MAX)
    						{
    						  if(gSystem.SystemErrCodeTemp&ERRCODE_T8_OPEN)strcat(str,"E085");        //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T8_SHORT)strcat(str,"E086");  //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T8_OVER)strcat(str,"E081");   //T1??
    						  else if(gSystem.SystemErrCodeTemp&ERRCODE_T8_HEAT)strcat(str,"E088");   //T1??

    					  }
    						 num++;
    					}
    					TEXT_SetText(TextPrompt, str);
    	*/

}


void DeletePromptMenu(void)
{
    if(PromptMenu.InterfaceStatus==PROMPT_MENU_BUSY)
    {

        WM_DeleteWindow(PromptWin);
        GUI_Delay(20);
    }
//	PromptMenu.InterfaceStatus=PROMPT_MENU_FREE;//lgj161007
}



void _cbPrompt(WM_MESSAGE * pMsg)
{
    WM_HWIN    hWin, hWinFocus;

    int        Id, IdWinFocus,i;
    int        NCode;
    int        xSize;
    int        ySize;

    hWin = pMsg->hWin;

    hWinFocus = WM_GetFocussedWindow();
    IdWinFocus = WM_GetId(hWinFocus);

    switch (pMsg->MsgId)
    {

    case WM_CREATE:

        switch (PromptMenu.InterfaceFlag)
        {
        case PROMPT_FILTER_SAME:
            BtYes = BUTTON_CreateEx(122, 140, 80, 35, hWin, WM_CF_SHOW, 0, ID_BUTTON_YES);
            BUTTON_SetText(BtYes, "Confirm");

            TxtPrompt = TEXT_CreateEx(20, 70, 282, 50, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, TEXT_CF_HCENTER | TEXT_CF_VCENTER,
                                      ID_TEXT_PROMPT, "");
            //TextPrompt2 = TEXT_CreateEx(20,110, 282, 110, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, TEXT_CF_HCENTER | TEXT_CF_VCENTER, PROMPT_ID_TEXT2, "");

            TEXT_SetTextColor(TxtPrompt, GUI_BLACK);
//			   TEXT_SetText(TxtPrompt, STR_SAME_WAVELENGTH[SystemPrameter.SystemLanguage]);
            break;

        default:
            //if (SystemPrameter.SystemLanguage == LANGUAGE_CH)
            // TEXT_SetText(TextPrompt, "??????!");
            //else
            //TEXT_SetText(TextPrompt, "Please Select Yes Or No!");
            break;
        }
        break;
    case WM_DELETE:
        //WM_DeleteWindow(hWin);



        PromptMenu.InterfaceStatus=PROMPT_MENU_FREE;
        TouchKey.KeyStatus=1;

        break;

    case WM_PAINT:

        xSize = WM_GetWindowSizeX(hWin);
        ySize = WM_GetWindowSizeY(hWin);

        GUI_SetColor(0xffffff);
        GUI_FillRect(0, 0, xSize, ySize);
        GUI_SetColor(COLOR_BUTTON_DEFAULT);
        GUI_DrawRect(0, 0, xSize-1, ySize-1);
        GUI_DrawRect(1, 1, xSize-2, ySize-2);
        //  if(PromptMenu.InterfaceFlag<PROMPT_ERR_END)
        //  GUI_DrawBitmap(&bmBmPromptErr, 126,10);
        //  else
        //   GUI_DrawBitmap(&bmBmPromptWarning, 120,8);
        break;

    case WM_NOTIFY_PARENT:
        Id = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;

        if (NCode == WM_NOTIFICATION_CLICKED)
        {

        }
        else if (NCode == WM_NOTIFICATION_RELEASED)
        {
            if (Id == ID_BUTTON_YES )//Esc
            {
                PromptMenu.KeyReturnValue=PROMPT_MENU_RETURN_ENTER;


                WM_DeleteWindow(hWin);
            }
            else if ( Id == ID_BUTTON_NO)//Esc
            {
                PromptMenu.KeyReturnValue=PROMPT_MENU_RETURN_CANCEL;

                WM_DeleteWindow(hWin);
                //WM_DeleteWindow(Button_no);
                //KeyPadAscFlag = KEYPAD_FREE;
            }
        }
        break;

    default:
        break;
    }
}


unsigned char  Prompt_Interface(unsigned char flag)
{
    //if(PromptMenu.InterfaceStatus==PROMPT_MENU_FREE)
    {
        //	Prompt_Busy=1;
        PromptMenu.KeyReturnValue=PROMPT_MENU_RETURN_NO;
        PromptMenu.InterfaceFlag=flag;//=PROMPT_RUNMENU_STOP
        PromptMenu.InterfaceStatus=PROMPT_MENU_BUSY;
        PromptWin = WM_CreateWindowAsChild(236, 180, 322, 200, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbPrompt, 0);
        WM_BringToTop(PromptWin);
        GUI_Delay(20);
    }
    do
    {
        GUI_Delay(10);
    } while(PromptMenu.InterfaceStatus==PROMPT_MENU_BUSY);
}


