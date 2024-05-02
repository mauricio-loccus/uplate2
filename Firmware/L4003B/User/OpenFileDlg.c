#include "MainTask.h"
#include "bsp.h"
#include "usbh_bsp_msc.h"
#include "usbh_hid_core.h"

enum
{
    SORT_DATA=0,
    SORT_TIME,
};

//标题栏
const char OPEN_MAIN_TITLE[LANGUAGE_TYPES][24] = {"Assay" , "Ensaios"};
const char BATCH_OPERATE_TITLE[LANGUAGE_TYPES][28] = {"Edit mode", "Modo de Edição"};

//工具栏第1个按钮
const char STR_BUTTON_DELETE[LANGUAGE_TYPES][10] = {"Delete", "Remover"};
const char STR_BATCH_OPERATION[LANGUAGE_TYPES][15] = {"Batch OP", "Editar"};

//工具栏第2个按钮(USB Drive)
const char STR_BUTTON_FLASH[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = {"Disk...", "Memória", };
const char STR_BUTTON_USBDRIVER[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = {"USB Drive", "Disco USB"};

//工具栏第3个按钮(Export Import)
const char STR_BUTTON_IMPORT[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = {"Import","Importar"};
const char STR_BUTTON_EXPORT[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = {"Export","Exportar"};

//工具栏第4个按钮(Export Import)
const char STR_BUTTON_SEL_ALL[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = {"Sel. all", "Sel. Tudo"};
const char STR_BUTTON_DESEL_ALL[LANGUAGE_TYPES][PLATE_IN_OUT_CHAR_MAX] = {"Desel. all", "Limpar"};
const char STR_BUTTON_OPEN[LANGUAGE_TYPES][10] = {"Open", "Abrir"};


//const char TABLE_RECORD_NO[LANGUAGE_TYPES][10] = {"NO.", "序号"};
const char TABLE_RECORD_NAME[LANGUAGE_TYPES][10] = {"Name", "Nome"};
const char TABLE_RECORD_DATA[LANGUAGE_TYPES][10] = {"Data", "Result."};
const char TABLE_RECORD_MODIFIED_TIME[LANGUAGE_TYPES][18] = {"Time", "Modificação"};

//const char FILE_IMPORT_SUCCESS[LANGUAGE_TYPES][RUN_ERROR_CHAR_MAX] = {"The files are imported successfully."
//, "文件导入成功。"};
//const char FILE_EXPORT_SUCCESS[LANGUAGE_TYPES][RUN_ERROR_CHAR_MAX] = {"The files are exported successfully."
//, "文件导出成功。"};
const char ONLY_OPEN_ONE_FILE[LANGUAGE_TYPES][ABSDLG_TITLE_CHAR_MAX] = {"Please select one file", "Selec. um arquivo"};



/*
const char FILE_IMPORT_SUCCESS[LANGUAGE_TYPES][RUN_ERROR_CHAR_MAX] = {"The files are imported successfully."
	, "???????"};
const char FILE_EXPORT_SUCCESS[LANGUAGE_TYPES][RUN_ERROR_CHAR_MAX] = {"The files are exported successfully."
	, "???????"};
const wchar_t ONLY_OPEN_ONE_FILE[LANGUAGE_TYPES][ABSDLG_TITLE_CHAR_MAX] = {_T("Please select one file")
		, _T("???????"), _T("Please select one file"), _T("Please select one file")};
*/

WM_HWIN OpenFileWin = NULL;




const BUTTON_DATA _aButtonOpenFile[] =
{
	  { TOOLS0_BUTTON_POSX(3)-160, TOOLS0_BUTTON_POSY, TOOLS0_BUTTON_WIDTH+80, TOOLS0_BUTTON_HEIGHT,"Export Report", "Exp. Resultados"},   
	  { TOOLS0_BUTTON_POSX(4)-80, TOOLS0_BUTTON_POSY, TOOLS0_BUTTON_WIDTH+80, TOOLS0_BUTTON_HEIGHT,  "Export Assay", "Exp. Ensaios"},  
	  
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(0), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "", "" },//Delete  或 Batch OP
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(1), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "USB Drive", "Disco USB..." },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(2), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Import", "Importar" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(3), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Open", "Abrir" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(4), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Back", "Voltar" }, 
};

static short nCurrentSelect;
static short nCurrentSelectPage;
static short nCurrentPage;
//static short nCurrentSelectBack;
//unsigned short FileMaxNum; //文件最大数量
//unsigned char SortFlag;
static unsigned char BatchOperateFlag;//1表示批量界面，0表示打开文件界面
static unsigned char UsbDriveFlag=0;
static unsigned char SelAllFlag=0;
static unsigned char SortDataUpFlag=0;
static unsigned char SortTimeUpFlag=0;
static unsigned char SelFlag[PROGRAM_MAX]  __attribute__((at(SDRAM_SEL_FLAG_BUF)));

/*
1.读取不带数据的文件,
2.读取带数据的文件
3.排序(数据项)---注:按时间排序要先对数据项排序,再按不带数据和带数据的文件分别按时间项排序
*/
// qsort(ProgramName,ProgramMax,sizeof(ProgramName[0]),cmp);//用此函数可实现排序功能
/*
void SortFileItem()
{
	unsigned short i,j,max,min,tmp;
	if(FileMaxNum < 2)
	{
		 return;
	}

	//wchar_t aa[FILE_NAME_NUMBER_MAX];
	//CFileStatus *tmpFileStatus = new CFileStatus;


	for(i=0; i<FileMaxNum; i++ )
	{
		max = i;
		min = i;
		for(j=i+1; j<FileMaxNum; j++ )
		{
			if(SortFlag)
			{
			//	tmp =  (int)(fileStatus[j].m_mtime.GetTime() - fileStatus[max].m_mtime.GetTime());
				if(tmp > 0)
				{
					max = j;
				}
			}
			else
			{
				//tmp =  (int)(fileStatus[j].m_mtime.GetTime() - fileStatus[min].m_mtime.GetTime());
				if(tmp < 0)
				{
					 min = j;
				}
			}
		}

		if(SortFlag && max> i )
		{
			strcpy(ConvertStr,ProgramName[i].Name);
			strcpy(ProgramName[i].Name,ProgramName[max].Name);
			strcpy(ProgramName[max].Name,ConvertStr);


			//memcpy(tmpFileStatus, &fileStatus[i], sizeof(CFileStatus));
		//	memcpy(&fileStatus[i],&fileStatus[max], sizeof(CFileStatus));
		//	memcpy( &fileStatus[max],tmpFileStatus, sizeof(CFileStatus));

			//tmp = fileFlag[i];
		//	fileFlag[i] = fileFlag[max];
			//fileFlag[max] = tmp;
		}
		else if((SortFlag==0) && (min> i) )
		{
			 strcpy(ConvertStr,ProgramName[i].Name);
			 strcpy(ProgramName[i].Name,ProgramName[min].Name);
			 strcpy(ProgramName[min].Name,ConvertStr);

		//	wsprintf(aa,  fileName[i]);
		//	wsprintf(fileName[i], fileName[min]);
		//	wsprintf(fileName[min], aa);

		//	memcpy(tmpFileStatus, &fileStatus[i], sizeof(CFileStatus));
			//memcpy(&fileStatus[i],&fileStatus[min], sizeof(CFileStatus));
		//	memcpy( &fileStatus[min],tmpFileStatus, sizeof(CFileStatus));

			//tmp = fileFlag[i];
			//fileFlag[i] = fileFlag[min];
		//	fileFlag[min] = tmp;
		}
	}
}
*/



u8 UsbCheckSameName(void)
{
    u16 i;

    for (i = 0; i < gSystem.UsbProgramMax; i++)  //lgj171116 这里要改成gSystem.ProgramMax  PROGRAM_MAX
    {
        if(strcmp(UsbProgramName[i].Name,CmpFileName)==0)
            return 1;
    }
    return 0;
}

void FileImport(unsigned char overwriteflag)
{
    unsigned short i,count=0;
//    bool bHasConfirmed = false;
    for(i = 0; i < gSystem.UsbProgramMax; i++)
    {
        if(SelFlag[i]==0)
        {
            continue;
        }
				#ifdef SOFTWARE_DN
				if( (strcmp(UsbProgramName[i].Name,"MET")==0)||(strcmp(UsbProgramName[i].Name,"MOR")==0)||(strcmp(UsbProgramName[i].Name,"KET")==0) ) //文件名相同
        {
            continue;
        }
				#else
				if( (strcmp(UsbProgramName[i].Name,"Demo_1")==0)||(strcmp(UsbProgramName[i].Name,"Demo_2")==0)||(strcmp(UsbProgramName[i].Name,"Demo_3")==0) ) //文件名相同
        {
            continue;
        }
				#endif
        
        /*
        		if(CString(fileName[i]) == _T("DEMO_1") || CString(fileName[i]) == _T("DEMO_2")
        			|| CString(fileName[i]) == _T("DEMO_3") || CString(fileName[i]) == _T("Demo_1")
        			|| CString(fileName[i]) == _T("Demo_2") || CString(fileName[i]) == _T("Demo_3"))
        		{
        				continue;
        		}

        		CString tempString, strDst;
        		strDst = NANDFLASH_FILE_DIR;
        		tempString = STRING_USB_FILE_PATH;

        		tempString += fileName[i];
        		strDst += fileName[i];
        		if(1 == fileFlag[i])
        		{
        			tempString += _T(".erf");
        			strDst += _T(".erf");
        		}
        		else if(0 == fileFlag[i])
        		{
        			tempString += _T(".dat");
        			strDst += _T(".dat");
        		}
        */

        strcpy(CmpFileName,UsbProgramName[i].Name);
        if(check_same_name(1))//if(UsbCheckSameName())//check_same_name
        {
            // TEXT_SetText(TxtErrPrompt, SAME_FILE_ERROR[SystemPrameter.SystemLanguage]);
            // WM_ShowWindow(TxtErrPrompt);
            //Prompt_Interface(PROMPT_SAME_NAME);//文件名相同
            //WM_SetFocus(EditNameMessage);
            if(overwriteflag)
            {
								if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
								{
                CurrProgramName.DateTime.Year=SystemTimePra.Year;
                CurrProgramName.DateTime.Month=SystemTimePra.Month;
                CurrProgramName.DateTime.Day=SystemTimePra.Day;
                CurrProgramName.DateTime.Hour=SystemTimePra.Hour;
                CurrProgramName.DateTime.Min=SystemTimePra.Min;
                CurrProgramName.DateTime.Sec=SystemTimePra.Sec;
								}
								else
								{
								CurrProgramName.DateTime.Day=SystemTimePra.Day;
                CurrProgramName.DateTime.Month=SystemTimePra.Month;
                CurrProgramName.DateTime.Year=SystemTimePra.Year;
                CurrProgramName.DateTime.Hour=SystemTimePra.Hour;
                CurrProgramName.DateTime.Min=SystemTimePra.Min;
                CurrProgramName.DateTime.Sec=SystemTimePra.Sec;
								}	

                strcpy(CurrProgramName.Name,UsbProgramName[i].Name);
                if(UsbOpenOneFile()== FR_OK)
                {
                    if(NandSaveFile(0)==NAND_OK)//同地址保存文件
                    {
                        count++;
                    }
                }
            }
            // continue;
        }
        else
        {
            //1.从USB打开一个文件
            strcpy(CurrProgramName.Name,UsbProgramName[i].Name);
            if(UsbOpenOneFile()== FR_OK)
            {
                //UsbOpenOneFile();
                //2.将打开的文件存入NandFlash
                //if(gSystem.CreateFlag)
                // {
                if(NandSaveFile(1)==NAND_OK)//查找新地址保存文件
                {
                    count++;
                }
            }
        }

        sprintf(ConvertStr,"%d",(i*100)/gSystem.UsbProgramMax);
        if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
        {
            strcpy(PromptMenu.InputStr, "Please waiting...");
            strcat(PromptMenu.InputStr,ConvertStr);
            strcat(PromptMenu.InputStr,"%");
        }
        else
        {
            strcpy(PromptMenu.InputStr, "Aguarde...");
            strcat(PromptMenu.InputStr,ConvertStr);
            strcat(PromptMenu.InputStr,"%");
        }
        RefreshPromptMenu();
        // gSystem.CreateFlag=0;
        //}
        //	CopyFile(tempString, strDst, !file_sel.bOverwrite);
        //count++;
    }
    DeletePromptMenu(1);
    //提示文件导入OK
//	file_sel.bOverwrite = false;
    if(count > 0)
    {
        strcpy(PromptMenu.InputStr,FILE_IMPORT_SUCCESS[SystemPrameter.SystemLanguage]);
    }
    else
    {
        strcpy(PromptMenu.InputStr,FILE_IMPORT_ERROR[SystemPrameter.SystemLanguage]);
        Usb_Init();
    }
    Prompt_Interface(PROMPT_WARMING);
    //	MessageBoxOne(FILE_IMPORT_SUCCESS[sys_para.wcLanguage]);
}
unsigned char  FindUsbFileSame(void)
{
    unsigned short i,j;
//	unsigned char sameflag=0;
    for(i = 0; i < gSystem.ProgramMax; i++)
    {
        if(SelFlag[i])
        {
            for(j=0; j<gSystem.UsbProgramMax; j++)
            {
                if(strcmp(ProgramName[i].Name,UsbProgramName[j].Name)==0) //文件名相同
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
unsigned char  FindNandFileSame(void)
{
    unsigned short i,j;
//	unsigned char sameflag=0;
    for(i = 0; i < gSystem.UsbProgramMax; i++)
    {
        if(SelFlag[i])
        {
            for(j=0; j<gSystem.ProgramMax; j++)
            {
                if(strcmp(ProgramName[j].Name,UsbProgramName[i].Name)==0) //文件名相同
                {
                    return 1;
                }
            }
        }
    }
    return 0;
}
void  FileExport(unsigned char overwriteflag)
{
    unsigned char okflag=0;
    unsigned short i;
//    bool bHasConfirmed = false;
    for(i = 0; i < gSystem.ProgramMax; i++)
    {
        if(SelFlag[i]==0)
        {
            continue;
        }

        //CString tempString, strDst;//, strFileName;
        //tempString = NANDFLASH_FILE_DIR;
        //strDst = STRING_USB_FILE_PATH;

        //tempString += fileName[i];
        //strDst += fileName[i];
        /*
        	if(1 == fileFlag[i])
        	{
        		tempString += _T(".erf");
        		strDst += _T(".erf");
        	}
        	else if(0 == fileFlag[i])
        	{
        		tempString += _T(".dat");
        		strDst += _T(".dat");
        	}*/
//1.从NandFlash打开文件
        gSystem.CurrBlock=ProgramName[i].BlockAddr;
        if(NandOpenOneFile()==NAND_FAIL)
        {
            //okflag=0;
            continue;
        }
        if(CurrProgramName.BlockAddr!=gSystem.CurrBlock)
        {
            continue;
            //出错
        }
        if(overwriteflag==0)
        {
            strcpy(CmpFileName,ProgramName[i].Name);
            if(UsbCheckSameName())
            {
                continue;
            }
        }

        SpiGenerateBoardFile();

        if(ExportOneFile()==0)
        {
            //导出成功
            //count++;
            okflag=1;
        }
        else
        {
            // okflag=0;
            //导出失败
        }
        sprintf(ConvertStr,"%d",(i*100)/gSystem.ProgramMax);
        if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
        {
            strcpy(PromptMenu.InputStr, "Please waiting...");
            strcat(PromptMenu.InputStr,ConvertStr);
            strcat(PromptMenu.InputStr,"%");
        }
        else
        {
            strcpy(PromptMenu.InputStr, "Aguarde...");
            strcat(PromptMenu.InputStr,ConvertStr);
            strcat(PromptMenu.InputStr,"%");
        }
        RefreshPromptMenu();
        // Prompt_Interface(PROMPT_RUN);



        //存到U盘中
        //CopyFile(tempString, strDst, !file_sel.bOverwrite);
    }
    //提示文件导出成功
    //file_sel.bOverwrite = false;
    //MessageBoxOne(FILE_EXPORT_SUCCESS[SystemPrameter.SystemLanguage]);
    //提示NandFlash已满
    DeletePromptMenu(1);
    if(okflag)
    {
        strcpy(PromptMenu.InputStr,FILE_EXPORT_SUCCESS[SystemPrameter.SystemLanguage]);
    }
    else
    {
        strcpy(PromptMenu.InputStr,FILE_EXPORT_ERROR[SystemPrameter.SystemLanguage]);
        Usb_Init();
    }
    Prompt_Interface(PROMPT_WARMING);
}


signed short cmp_data( const  void *a ,const void *b)
{
    signed char  tt;

    tt=(*(PROGRAMNAME *)a).HasData-(*(PROGRAMNAME *)b).HasData;
    if(tt>0)
    {
        if(SortDataUpFlag)return 1;
        else return -1;
    }
    else if (tt<0)
    {
        if(SortDataUpFlag)return -1;
        else return 1;
    }
    return 0;
}
signed short cmp_time( const  void *a ,const void *b)
{
    signed short tt;

    tt=(*(PROGRAMNAME *)a).DateTime.Year-(*(PROGRAMNAME *)b).DateTime.Year;
    if(tt>0)
    {
        if(SortTimeUpFlag)return 1;
        else return -1;
    }
    else if (tt<0)
    {
        if(SortTimeUpFlag)return -1;
        else return 1;
    }


    tt=(*(PROGRAMNAME *)a).DateTime.Month-(*(PROGRAMNAME *)b).DateTime.Month;
    if(tt>0)
    {
        if(SortTimeUpFlag)return 1;
        else return -1;
    }
    else if (tt<0)
    {
        if(SortTimeUpFlag)return -1;
        else return 1;
    }

    tt=(*(PROGRAMNAME *)a).DateTime.Day-(*(PROGRAMNAME *)b).DateTime.Day;
    if(tt>0)
    {
        if(SortTimeUpFlag)return 1;
        else return -1;
    }
    else if (tt<0)
    {
        if(SortTimeUpFlag)return -1;
        else return 1;
    }

    tt=(*(PROGRAMNAME *)a).DateTime.Hour-(*(PROGRAMNAME *)b).DateTime.Hour;
    if(tt>0)
    {
        if(SortTimeUpFlag)return 1;
        else return -1;
    }
    else if (tt<0)
    {
        if(SortTimeUpFlag)return -1;
        else return 1;
    }

    tt=(*(PROGRAMNAME *)a).DateTime.Min-(*(PROGRAMNAME *)b).DateTime.Min;
    if(tt>0)
    {
        if(SortTimeUpFlag)return 1;
        else return -1;
    }
    else if (tt<0)
    {
        if(SortTimeUpFlag)return -1;
        else return 1;
    }

    tt=(*(PROGRAMNAME *)a).DateTime.Sec-(*(PROGRAMNAME *)b).DateTime.Sec;
    if(tt>0)
    {
        if(SortTimeUpFlag)return 1;
        else return -1;
    }
    else if (tt<0)
    {
        if(SortTimeUpFlag)return -1;
        else return 1;
    }

    return 0;

}



void RefreshButton(void)
{
    if(BatchOperateFlag)//批量操作模式下
    {
        if(UsbDriveFlag==0)  //本机
        {
					  WM_ShowWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON));
					  WM_ShowWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+1));
					
            BUTTON_SetText(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+2), STR_BUTTON_DELETE[SystemPrameter.SystemLanguage]);
            WM_ShowWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+2));

            BUTTON_SetText(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+3), STR_BUTTON_USBDRIVER[SystemPrameter.SystemLanguage]);
            WM_ShowWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+3));

            //BUTTON_SetText(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+4), STR_BUTTON_EXPORT[SystemPrameter.SystemLanguage]);
           // WM_ShowWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+4));
					  WM_HideWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+4));
        }
        else
        {
					  WM_HideWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON));
					  WM_HideWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+1));
            //不显示删除按钮
            WM_HideWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+2));
            //U盘模式下显示本机
            BUTTON_SetText(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+3), STR_BUTTON_FLASH[SystemPrameter.SystemLanguage]);
            WM_ShowWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+3));
            //U盘模式下显示导入
            BUTTON_SetText(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+4), STR_BUTTON_IMPORT[SystemPrameter.SystemLanguage]);
            WM_ShowWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+4));
        }
        if(SelAllFlag)
        {
            BUTTON_SetText(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+5), STR_BUTTON_DESEL_ALL[SystemPrameter.SystemLanguage]);
        }
        else
        {
            BUTTON_SetText(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+5), STR_BUTTON_SEL_ALL[SystemPrameter.SystemLanguage]);
        }
        WM_ShowWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+5));
    }//if(BatchOperateFlag)//批量操作模式下
    else
    {
			  WM_HideWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON));
				WM_HideWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+1));
			
        BUTTON_SetText(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+2), STR_BATCH_OPERATION[SystemPrameter.SystemLanguage]);
        WM_ShowWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+2));

        //不显示按钮
        WM_HideWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+3));
        WM_HideWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+4));
        //打开
        BUTTON_SetText(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+5), STR_BUTTON_OPEN[SystemPrameter.SystemLanguage]);
        WM_ShowWindow(WM_GetDialogItem(OpenFileWin, ID_OPEN_BUTTON+5));
    }
}

unsigned char FindFileSelFlag(void)
{
    unsigned short i;
    unsigned short cmpval;

    if( (BatchOperateFlag)&&(UsbDriveFlag) )
    {
        cmpval=gSystem.UsbProgramMax;
    }
    else
    {
        cmpval=gSystem.ProgramMax;
    }

    for(i=0; i<cmpval; i++)
    {
        if(SelFlag[i])break;
    }
    if(i==cmpval)
    {
        return 0;
    }
    return 1;
}



unsigned char FindFileWithDataSelFlag(void)
{
    unsigned short i,j=0;
	 
    for(i=0; i<gSystem.ProgramMax; i++)
    {
        if( (SelFlag[i])&&(ProgramName[i].HasData))
				{
					j++;
				}
    }
		gSystem.ReportProgramMax=j;
    if(j==0)
    {
        return 0;
    }
    return 1;
}



void _cbOpenFile(WM_MESSAGE * pMsg)
{

    //char str[10];
    WM_HWIN hWin = pMsg->hWin;
    WM_HWIN hWinFocus;
    BUTTON_Handle hbutton;
    unsigned short i,j;
    int        xSize;
    int        ySize;
    short NCode, Id, IdWinFocus;
    GUI_RECT rect;
    //	int  day_max;
    hWinFocus = WM_GetFocussedWindow();
    IdWinFocus = WM_GetId(hWinFocus);

    switch (pMsg->MsgId)
    {

     case WM_CREATE:
    {

        for (i = 0; i < GUI_COUNTOF(_aButtonOpenFile); i++)
        {
            hbutton = BUTTON_CreateEx(_aButtonOpenFile[i].xPos, _aButtonOpenFile[i].yPos, _aButtonOpenFile[i].xSize, _aButtonOpenFile[i].ySize,
                                      hWin, WM_CF_SHOW, 0, ID_OPEN_BUTTON + i);
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG);
                BUTTON_SetText(hbutton, _aButtonOpenFile[i].acLabelEn);
            }
            else
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG_CH);
                BUTTON_SetText(hbutton, _aButtonOpenFile[i].acLabelCh);
            }

            if(i==2)
            {
                if(BatchOperateFlag)
                {
                    BUTTON_SetText(hbutton, STR_BUTTON_DELETE[SystemPrameter.SystemLanguage]);
                }
                else
                {
                    BUTTON_SetText(hbutton, STR_BATCH_OPERATION[SystemPrameter.SystemLanguage]);
                }
            }

            BUTTON_SetTextAlign(hbutton, GUI_TA_HCENTER | GUI_TA_VCENTER);
            BUTTON_SetFocussable(hbutton, 0);
            //打开文件时，第1和第2个按钮不用
            if(BatchOperateFlag==0)
            {
               // if( (i==1)||(i==2) )
								if( (i==0)||(i==1)||(i==3)||(i==4) )
                {
                    WM_HideWindow(hbutton);
                }
            }
        }
        break;
    }
    //删除按钮
    case WM_DELETE:

        gSystem.TitleButtonEnable=1;
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


        //GUI_DrawBitmap(&bmMenuLeft_101_46, FILTER_1_START_X, FILTER_1_START_Y - TITLESBAR_HEIGHT);
        //	GUI_DrawBitmap(&bmMenuLeft_101_46, FILTER_2_START_X, FILTER_2_START_Y - TITLESBAR_HEIGHT);
        //	GUI_DrawBitmap(&bmMenuLeft_101_46, MODE_START_X, MODE_START_Y - TITLESBAR_HEIGHT);

        //GUI_DrawBitmap(&bmMenuRight_120_46, FILTER_1_R_START_X, FILTER_1_R_START_Y - TITLESBAR_HEIGHT);
        //	GUI_DrawBitmap(&bmMenuRight_320_46, FILTER_2_R_START_X, FILTER_2_R_START_Y - TITLESBAR_HEIGHT);
        //GUI_DrawBitmap(&bmMenuRight_90_46, MODE_R_START_X, MODE_START_Y - TITLESBAR_HEIGHT);


        GUI_SetTextMode(GUI_TM_TRANS);

        GUI_SetColor(COLOR_PAINT_TXT);
        GUI_SetFont(GUI_FONT_BIG);
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            GUI_SetFont(GUI_FONT_BIG);
        }
        else
        {
            GUI_SetFont(GUI_FONT_BIG_CH);
        }
        if(BatchOperateFlag)
        {
            GUI_DispStringAt(BATCH_OPERATE_TITLE[SystemPrameter.SystemLanguage], CONTENTBAR_CAPTION_POSX, CONTENTBAR_CAPTION_POSY);
        }
        else
        {
            GUI_DispStringAt(OPEN_MAIN_TITLE[SystemPrameter.SystemLanguage], CONTENTBAR_CAPTION_POSX, CONTENTBAR_CAPTION_POSY);
        }


        //画表格的边框
       // GUI_SetColor(0xe1d8ca);//ok
				GUI_SetColor(GUI_GRAY);
        rect.x0 = TABLE_QUALITY_START_X;
        rect.y0 = TABLE_QUALITY_START_Y - TITLESBAR_HEIGHT;
        rect.x1 =TABLE_QUALITY_END_X;
        rect.y1=TABLE_QUALITY_END_Y - TITLESBAR_HEIGHT;
        GUI_DrawRect(rect.x0, rect.y0, rect.x1, rect.y1);
        //画表格顶行的背景色
        GUI_SetColor(COLOR_TITLEBAR);
        GUI_FillRect(rect.x0 + 2, rect.y0 + 2, rect.x1 - 2, rect.y0 + 35);    //首行
        //画表格翻页图标的背景色
       // GUI_SetColor(0xf4dbb2);0x3e302b
				 GUI_SetColor(0x3e302b);
        GUI_FillRect(rect.x0+2, rect.y1-37, rect.x1-2 , rect.y1-2);                //尾行
        //画表格线(5条）
				GUI_SetColor(GUI_GRAY);
				GUI_DrawLine(0,0, xSize - 1,0);
				GUI_DrawLine(0,CONTENTBAR_TITLE_HEIGHT - 1, xSize - 1,CONTENTBAR_TITLE_HEIGHT - 1);
        GUI_SetColor(COLOR_TITLEBAR);
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
        GUI_SetColor(GUI_WHITE);//
        rect.x0 = TABLE_HITORICAL_COLUMN_NO ;
        rect.y0 = TABLE_QUALITY_START_Y+QUALITY_ROW_TXT_DIS_Y;
        rect.y0=rect.y0 -TITLESBAR_HEIGHT;
        GUI_DispStringAt(STR_TABLE_RECORD_NO[SystemPrameter.SystemLanguage],rect.x0,rect.y0);
        GUI_DispStringAt(TABLE_RECORD_NAME[SystemPrameter.SystemLanguage],
                         TABLE_HITORICAL_COLUMN_FILE_NAME,rect.y0);
        GUI_DispStringAt(TABLE_RECORD_DATA[SystemPrameter.SystemLanguage],
                         TABLE_HITORICAL_COLUMN_FILE_DATA,rect.y0);
        GUI_DispStringAt(TABLE_RECORD_MODIFIED_TIME[SystemPrameter.SystemLanguage],
                         TABLE_HITORICAL_COLUMN_FILE_TIME,rect.y0);

       /* GUI_DrawBitmap(&bmSort, TABLE_HITORICAL_COLUMN_FILE_DATA+40,rect.y0 );//- TITLESBAR_HEIGHT
        GUI_DrawBitmap(&bmSort, TABLE_HITORICAL_COLUMN_FILE_TIME+40,rect.y0 );//- TITLESBAR_HEIGHT*/


        if(gSystem.UsbProgramMax>PROGRAM_MAX)
        {
            gSystem.UsbProgramMax=1;
        }

        if(gSystem.ProgramMax>PROGRAM_MAX)
        {
            gSystem.ProgramMax=1;
        }
        if((BatchOperateFlag)&&(UsbDriveFlag) ) //U盘文件
        {
            if(nCurrentSelect>= gSystem.UsbProgramMax) // //只有九个质控品
            {
                if(gSystem.UsbProgramMax>0)nCurrentSelect=gSystem.UsbProgramMax-1;
                else nCurrentSelect=0;
            }
        }
        else if(nCurrentSelect>= gSystem.ProgramMax) //NandFlash内部文件
        {
            if(gSystem.ProgramMax>0)nCurrentSelect=gSystem.ProgramMax-1;
            else nCurrentSelect=0;
        }
        else if(nCurrentSelect<0)
        {
            nCurrentSelect=0;
        }
        nCurrentPage = nCurrentSelect / FILE_PAGE_NUMBER;
        nCurrentSelectPage = nCurrentSelect % FILE_PAGE_NUMBER;

        //质控打开时的绘制
//if(QualityParaBack.Enable)
//{
        //画当前选中的背景色


        GUI_SetColor(0xA0A0A0);//GUI_SetColor(0xf8ffc6);
        rect.x0=TABLE_HITORICAL_COLUMN_NO;
        rect.x1=TABLE_HITORICAL_COLUMN_NO+SELECT_LEN;
        if( ((gSystem.ProgramMax>0)&&(UsbDriveFlag==0))||
                ((gSystem.UsbProgramMax>0)&&(UsbDriveFlag)) )
        {
            if(BatchOperateFlag)
            {
                for(i=0; i<FILE_PAGE_NUMBER; i++) //if(SelFlag[i]) FILE_PAGE_NUMBER
                {
                    if( (SelFlag[nCurrentPage*FILE_PAGE_NUMBER+i])&&
                            ( ( (nCurrentPage*FILE_PAGE_NUMBER+i<gSystem.ProgramMax)&&(UsbDriveFlag==0) ) ||
                              ( (nCurrentPage*FILE_PAGE_NUMBER+i<gSystem.UsbProgramMax)&&(UsbDriveFlag) ) ))

                    {
                        rect.y0=PAGE_SELECT_START_Y+2-TITLESBAR_HEIGHT+PAGE_SELECT_DIS_Y*i;
                        rect.y1=rect.y0+SELECT_HIGH;
                        GUI_FillRect(rect.x0, rect.y0, rect.x1 , rect.y1);
                    }
                }
            }
            else if(nCurrentPage==nCurrentSelect/FILE_PAGE_NUMBER)
            {
                rect.y0=PAGE_SELECT_START_Y+2-TITLESBAR_HEIGHT+PAGE_SELECT_DIS_Y*nCurrentSelectPage;
                rect.y1=rect.y0+SELECT_HIGH;
                GUI_FillRect(rect.x0, rect.y0, rect.x1 , rect.y1);
            }
        }

        GUI_SetColor(0x0);
        for (i = 0; i < FILE_PAGE_NUMBER; i++)
        {
            j=(i + FILE_PAGE_NUMBER * nCurrentPage );  //首行号
            if( (((gSystem.ProgramMax<=0)||(j >= gSystem.ProgramMax))&&(UsbDriveFlag==0))||
                    (((gSystem.UsbProgramMax<=0)||(j >= gSystem.UsbProgramMax))&&(UsbDriveFlag)) )
            {
                break; //只有九个质控品
            }


            // if(j >= gSystem.ProgramMax)
            // {
            //       break;
            // }
            //SD<0,Target<=0 return
            // if( (QualityParaBack.dSD[QualityParaBack.AbsFlag][i + QC_PAGE_NUMBER * nCurrentPage] < 0.0)&&(QualityParaBack.dTarget [QualityParaBack.AbsFlag][i + QC_PAGE_NUMBER * nCurrentPage]<= 0.0) )
            // {
            //  break;
            // }

            //显示No
            GUI_SetColor(0xffffff);
            rect.x0 = TABLE_HITORICAL_COLUMN_NO;
            rect.y0=PAGE_SELECT_START_Y+2-TITLESBAR_HEIGHT+i*PAGE_SELECT_DIS_Y;
            rect.x1 = rect.x0+55;
            rect.y1 =  rect.y0+SELECT_HIGH;
            sprintf(ConvertStr,"%d",j+1);
            GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);




            //显示名字
            if((BatchOperateFlag)&&(UsbDriveFlag) ) //U盘文件
            {
                strcpy(ConvertStr,UsbProgramName[j].Name);
            }
            else
            {
                strcpy(ConvertStr,ProgramName[j].Name);
            }
            rect.x0 = TABLE_HITORICAL_COLUMN_FILE_NAME;
            rect.x1 = rect.x0+180;//
            GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);


            //显示SD
            rect.x0 = TABLE_HITORICAL_COLUMN_FILE_DATA;
            rect.x1 = rect.x0+90;
            if(ProgramName[j].HasData)
            {
                //画图片
                GUI_DrawBitmap(&bmHaveData, rect.x0, rect.y0+3 );//- TITLESBAR_HEIGHT

            }


            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                sprintf(ConvertStr,"%02d-%02d-%04d  -  %02d:%02d",ProgramName[j].DateTime.Month,ProgramName[j].DateTime.Day,ProgramName[j].DateTime.Year,
                        ProgramName[j].DateTime.Hour,ProgramName[j].DateTime.Min/*,ProgramName[j].DateTime.Sec*/);
                //	sprintf(ConvertStr,"%02d : %02d : %02d",SystemTimePraBack.Hour,SystemTimePraBack.Min,SystemTimePraBack.Sec);
            }
            else
            {
                sprintf(ConvertStr,"%02d-%02d-%04d  -  %02d:%02d",ProgramName[j].DateTime.Day,ProgramName[j].DateTime.Month,ProgramName[j].DateTime.Year,
                        ProgramName[j].DateTime.Hour,ProgramName[j].DateTime.Min/*,ProgramName[j].DateTime.Sec*/);
            }
            rect.x0 = TABLE_HITORICAL_COLUMN_FILE_TIME;
            rect.x1 = rect.x0+230;
            GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_LEFT | GUI_TA_VCENTER);

            rect.y0 +=PAGE_SELECT_DIS_Y;
        }

        //4.画页码
        GUI_SetColor(GUI_WHITE);
        rect.x0=270;
        rect.x1=350;
        rect.y0=TAB_RIGHT_START_Y-10- TITLESBAR_HEIGHT;
        rect.y1=TAB_RIGHT_END_Y+10- TITLESBAR_HEIGHT;

        sprintf(ConvertStr,"%d",nCurrentPage + 1);
        strcat(ConvertStr," / ");
        if((BatchOperateFlag)&&(UsbDriveFlag) ) //U盘文件
        {
            if(gSystem.UsbProgramMax>0)
            {
                sprintf(StrTemp,"%d",(gSystem.UsbProgramMax-1)/FILE_PAGE_NUMBER+1);
            }
            else
            {
                sprintf(StrTemp,"%d",1);
            }
        }
        else if(gSystem.ProgramMax>0)
        {
            sprintf(StrTemp,"%d",(gSystem.ProgramMax-1)/FILE_PAGE_NUMBER+1);
        }
        else
        {
            sprintf(StrTemp,"%d",1);
        }
        strcat(ConvertStr,StrTemp);
        GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);

        //if(board_inf.quality_para.bOpened)
        //{
        //   DisplayList(dc);
        //}





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
        if ( (NCode == WM_NOTIFICATION_RELEASED)&&(BatchOperateFlag==0) )
        {
            if (Id == ID_OPEN_BUTTON+2)   //工具栏第1个按钮  批量操作
            {
                TouchKey.KeyStatus=1;
                BatchOperateFlag=1;
                UsbDriveFlag=0;

                //nCurrentSelectPage = 0;
                //nCurrentSelect = 0;
                SelAllFlag=0;
                for(i=0; i<gSystem.ProgramMax; i++)
                {
                    SelFlag[i]=0;
                }
                RefreshButton();
                WM_Invalidate(OpenFileWin);
            }
            else if (Id == ID_OPEN_BUTTON+5)   //工具栏第4个按钮  打开
            {
                // strcpy(CurrProgramName.Name,ProgramName[nCurrentSelect].Name);
                gSystem.CurrBlock=ProgramName[nCurrentSelect].BlockAddr;
                // OpenOneFile();
                if(NandOpenOneFile()==NAND_OK)
                {
                    WM_DeleteWindow(OpenFileWin);
                    WM_ShowWindow(ProtocolWin);
                    TouchKey.KeyStatus=1;

                    LanguageChange.Report=1;
                    gSystem.MenuRefreshFlag = 1;
                    gSystem.SystemInterface = MI_PROTOCOL;
                    gSystem.TitleButtonEnable = 1;
                }
                else
                {
                    //出错提示
                }
                memcpy(&BoardInfBack,&BoardInf,sizeof(BOARD_INF));//lugj modify 20180223
                if(BoardInf.bHasData)
                {
                    ReportMenu.ReportReady=1;
                }
                TouchKey.KeyStatus=1;
                gSystem.NewFlag=0;		//lugj modify 20180223


            }
            else if (Id == ID_OPEN_BUTTON+6)   //工具栏第4个按钮  返回
            {
                strcpy(CmpFileName,BoardInfBack.Name);
                if(check_same_name(0)/*|| (gSystem.NewFlag==2)*/)//文件相同,文件存在
                {
                    memcpy(&BoardInf,&BoardInfTemp, sizeof(BOARD_INF) ); //
                    gSystem.CurrBlock=gSystem.CurrBlockBack;
                    memcpy(dABS, dABSInit, sizeof(float) * FILTER_PLATE_MAX * TUBE_MAX * KINETIC_READINGS_MAX);

                }
                else
                {
                    //打开Demo_1
                    gSystem.CurrBlock=ProgramName[0].BlockAddr;//
                    if(NandOpenOneFile()==NAND_FAIL)
                    {
                        if(NandOpenOneFile()==NAND_FAIL)//NandFlash是否初使化
                        {
                            gSystem.SystemErrCode=ERRCODE_NAND_FLASH; //NandFlash出错
                        }

                        // NandOpenOneFile();
                        //okflag=0;
                        //continue;
                    }
                }

                if(BoardInf.bHasData)
                {
                    ReportMenu.ReportReady=1;
                }
                WM_DeleteWindow(OpenFileWin);
                WM_ShowWindow(ProtocolWin);


                TouchKey.KeyStatus=1;
                gSystem.MenuRefreshFlag = 1;
                gSystem.SystemInterface = MI_PROTOCOL;
                gSystem.TitleButtonEnable = 1;
                LanguageChange.Report=1;
            }
        }
        else  if( (NCode == WM_NOTIFICATION_RELEASED)&&(BatchOperateFlag) )
        {
					  if( (Id == ID_OPEN_BUTTON)&&(UsbDriveFlag==0) )   //工具栏第1个按钮  导出报告
					{
						    unsigned char errflag=0;
						
						
						     TouchKey.KeyStatus=1;
                if(flag_usb_disk_connect==0)
                {
                    Usb_Init();//lugj modify 20180211
                    strcpy(PromptMenu.InputStr,TEST_INFO_MESSAGE[SystemPrameter.SystemLanguage][TEST_INFO_USB_ERROR]);
                    Prompt_Interface(PROMPT_WARMING);
                    return;
                }
                
                    if( (FindFileWithDataSelFlag()==0)||(gSystem.ProgramMax<=0) ) //没有选中的文件
                    {
                        strcpy(PromptMenu.InputStr,FILE_ERROR_MESSAGE[SystemPrameter.SystemLanguage][0]);
                        Prompt_Interface(PROMPT_WARMING);
                        return;
                    }
										
                #ifndef SOFTWARE_DN
								if(SystemPrameter.LockStatus==LOCK_ENABLE) //LOCK_ENABLE=0
                {
                    strcpy(KeyPadNum.InputValueStr,"");        //Enter Password
                    KeyPadNum_Interface(NUM_MENUFLAG_PASSWORD);//KeyPadNum.InputValueStr
                    if(KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)
										{
									    if ( strcmp(KeyPadNum.InputValueStr, UPDATA_PASSWORD_LOCK)!=0)//密码不正常
										  {
												if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
												{
												   strcpy(PromptMenu.InputStr,"Password is error!");
												}
												else
												{
													 strcpy(PromptMenu.InputStr,"Senha inválida!");
												}
                        Prompt_Interface(PROMPT_WARMING);
											  return;
										  }
									  }
										else
										{
											 return;
										}
                }
								#endif
											
											
							      DeletePromptMenu(0);
                            if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                            {
                                strcpy(PromptMenu.InputStr, "Please waiting...0%");
                            }
                            else
                            {
                                strcpy(PromptMenu.InputStr, "Aguarde...0%");
                            }
                             Prompt_Interface(PROMPT_RUN);
                               
														
					      //20180707 add 导出报告
								//unsigned short r_count=0;
								j=0;
							  for(i=0; i<gSystem.ProgramMax; i++)
                {
                    if( (SelFlag[i])&&(ProgramName[i].HasData) )
										{
											   gSystem.CurrBlock=ProgramName[i].BlockAddr;
                         if(NandOpenOneFile()==NAND_OK)
                         {
													   if(BoardInf.KineticPara.Enable)
                             {
                                InitKineticAnalysis();
                             }
                             else
                             {
                                 InitNormalAnalysis();

                             }
				
														 
														 SetParameterContent();   //设置参数
														 SetRawDataContent();
														 if(BoardInf.KineticPara.Enable)
                             {
                                 SetResultContent();//设置动力学分析结果(注：标准曲线不输出)
                             }
                             else
                             {
                                 SetQualityContent();//设置定量分析
                                 #ifdef SOFTWARE_DN
                                    SetUDContent();
                                 #endif
                             }
                             SetInterContent(); //设置定性分析
														 
														 	#ifndef SOFTWARE_DN
                             //设置标准曲线数据
                             SetCurveContent();
		                         #endif
				
				
                             SetQCContent();//设置质控分析结果
														 
														 //调用文件系统写入U盘
                             StartUpPra.EnableUsbCheck=0;
                             if(ExportOneProgram()==0)//返回成功
                             {
															    if(gSystem.ReportProgramMax<1)gSystem.ReportProgramMax=1;
															    if(j>gSystem.ReportProgramMax)j=gSystem.ReportProgramMax;
															    j++;
													        sprintf(ConvertStr,"%d",((j)*100)/gSystem.ReportProgramMax);
                                  if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
																	{
																			strcpy(PromptMenu.InputStr, "Please waiting...");
																			strcat(PromptMenu.InputStr,ConvertStr);
																			strcat(PromptMenu.InputStr,"%");
																	}
																	else
																	{
																			strcpy(PromptMenu.InputStr, "Aguarde...");
																			strcat(PromptMenu.InputStr,ConvertStr);
																			strcat(PromptMenu.InputStr,"%");
																	}
																	RefreshPromptMenu();
                             }
														 else 
														 {
															   errflag=1;
															   break;
														 }
                             StartUpPra.EnableUsbCheck=1;
                             
                         }
												 else 
												 {
															   errflag=1;
															   break;
													}
                       }
										    
				
				
				
                              //WM_DeleteWindow(OpenFileWin);
                              //WM_ShowWindow(ProtocolWin);
                              //TouchKey.KeyStatus=1;
                    //LanguageChange.Report=1;
                    //gSystem.MenuRefreshFlag = 1;
                    //gSystem.SystemInterface = MI_PROTOCOL;
                    //gSystem.TitleButtonEnable = 1;
 
										}//for(i=0; i<gSystem.ProgramMax; i++)
								DeletePromptMenu(1);
								if(errflag==0)
								{
								    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                    {
                         strcpy(PromptMenu.InputStr,"The current data is exported OK.");
                    }
                    else
                    {
                         strcpy(PromptMenu.InputStr,"Dados exportados com sucesso.");//完成要有字体
                    }
                }
								else
								{
										if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
										{
												strcpy(PromptMenu.InputStr,"The current data is exported Fail.");
										}
										else
										{
												strcpy(PromptMenu.InputStr,"Erro ao exportar dados.");
										}
								}
		            Prompt_Interface(PROMPT_STATUS);
		
								//20180707 add end 导出报告
						}	
						else if( (Id == ID_OPEN_BUTTON+1)&&(UsbDriveFlag==0) )   //工具栏第4个按钮  导出程序
            {
                TouchKey.KeyStatus=1;
                if(flag_usb_disk_connect==0)
                {
                    Usb_Init();//lugj modify 20180211
                    strcpy(PromptMenu.InputStr,TEST_INFO_MESSAGE[SystemPrameter.SystemLanguage][TEST_INFO_USB_ERROR]);
                    Prompt_Interface(PROMPT_WARMING);
                    return;
                }
								#ifndef SOFTWARE_DN
								if(SystemPrameter.LockStatus==LOCK_ENABLE) //LOCK_ENABLE=0
                {
                    strcpy(KeyPadNum.InputValueStr,"");        //Enter Password
                    KeyPadNum_Interface(NUM_MENUFLAG_PASSWORD);//KeyPadNum.InputValueStr
                    if(KeyPadNum.ReturnKey == KEYPAD_NUM_RETURN_ENTER)
										{
									    if ( strcmp(KeyPadNum.InputValueStr, UPDATA_PASSWORD_LOCK)!=0)//密码不正常
										  {
												if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
												{
												   strcpy(PromptMenu.InputStr,"Password is error!");
												}
												else
												{
													 strcpy(PromptMenu.InputStr,"Senha inválida!");
												}
                        Prompt_Interface(PROMPT_WARMING);
											  return;
										  }
									  }
										else
										{
											 return;
										}
                }
								#endif
								
								
                
                    if( (FindFileSelFlag()==0)||(gSystem.ProgramMax<=0) ) //没有选中的文件
                    {
                        strcpy(PromptMenu.InputStr,FILE_ERROR_MESSAGE[SystemPrameter.SystemLanguage][0]);
                        Prompt_Interface(PROMPT_WARMING);
                        return;
                    }
                    else
                    {

                        //导出所有选中的程序
                        DeletePromptMenu(0);
                        if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                        {
                            strcpy(PromptMenu.InputStr, "Please waiting...");
                        }
                        else
                        {
                            strcpy(PromptMenu.InputStr, "Aguarde...");
                        }
                        Prompt_Interface(PROMPT_RUN);


                        gSystem.UsbProgramMax=0;
                        StartUpPra.EnableUsbCheck=0;
                        UsbReadAllProgramHead();
                        StartUpPra.EnableUsbCheck=1;

                        if( (gSystem.UsbProgramMax>0)&&(FindUsbFileSame()) )
                            //if(AskNeedOverwrite(false))//在U盘查找是否有相同的文件
                        {
                            DeletePromptMenu(0);
                            strcpy(PromptMenu.InputStr,FILE_ERROR_MESSAGE[SystemPrameter.SystemLanguage][FILE_ERROR_OVERWRITE]);
                            Prompt_Interface(PROMPT_YES_NO);

                            // GUI_Delay(10);
                            if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                            {
                                strcpy(PromptMenu.InputStr, "Please waiting...0%");
                            }
                            else
                            {
                                strcpy(PromptMenu.InputStr, "Aguarde...0%");
                            }


                            StartUpPra.EnableUsbCheck=0;
                            //	 Create_USB_Dir(FS_VOLUME_USB);
                            if(PromptMenu.KeyReturnValue==PROMPT_MENU_RETURN_ENTER)
                            {
                                Prompt_Interface(PROMPT_RUN);
                                FileExport(1);//1表示overwrite,导出文件并提示文件导出成功或失败
                            }
                            else
                            {
                                Prompt_Interface(PROMPT_RUN);
                                FileExport(0);//0表示不overwrite,
                            }
                            StartUpPra.EnableUsbCheck=1;
                            //重写文件
                        }
                        else
                        {
                            //ExportReportFunction();
                            //StartUpPra.EnableUsbCheck=0;
                            Create_USB_Dir(FS_VOLUME_USB);
                            //StartUpPra.EnableUsbCheck=1;

                            if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                            {
                                strcpy(PromptMenu.InputStr, "Please waiting...0%");
                            }
                            else
                            {
                                strcpy(PromptMenu.InputStr, "Aguarde...0%");
                            }
                            //Prompt_Interface(PROMPT_RUN);
                            RefreshPromptMenu();
                            //	GUI_Delay(10);
                            //StartUpPra.EnableUsbCheck=0;
                            // Create_USB_Dir(FS_VOLUME_USB);
                            //	StartUpPra.EnableUsbCheck=1;
                            //	GUI_Delay(20);
                            StartUpPra.EnableUsbCheck=0;

                            FileExport(0);//导出文件并提示文件导出成功或失败
                            StartUpPra.EnableUsbCheck=1;
                        }
                    }
            }		
								
										
						
						
            else if( (Id == ID_OPEN_BUTTON+2)&&(UsbDriveFlag==0) )   //工具栏第1个按钮  删除
            {
                TouchKey.KeyStatus=1;
                if( (FindFileSelFlag()==0)||(gSystem.ProgramMax<=0) ) //没有选中的文件
                {
                    strcpy(PromptMenu.InputStr,FILE_ERROR_MESSAGE[SystemPrameter.SystemLanguage][0]);
                    Prompt_Interface(PROMPT_WARMING);
                    WM_Invalidate(OpenFileWin);
                    return;
                }
                strcpy(PromptMenu.InputStr,FILE_ERROR_MESSAGE[SystemPrameter.SystemLanguage][FILE_ERROR_DELETE]);
                Prompt_Interface(PROMPT_YES_NO);
                if(PromptMenu.KeyReturnValue!=PROMPT_MENU_RETURN_ENTER)
                {
                    return;
                }
                //WM_Invalidate(OpenFileWin);

                for(i=0; i<gSystem.ProgramMax; i++)
                {
                    if(SelFlag[i])
                    {
											  #ifdef SOFTWARE_DN
												if( (strcmp(ProgramName[i].Name,"MET")==0)||(strcmp(ProgramName[i].Name,"MOR")==0)||(strcmp(ProgramName[i].Name,"KET")==0) ) //文件名相同
												{
														continue;
												}
												#else
                       /* if( (strcmp(ProgramName[i].Name,"Demo_1")==0)||(strcmp(ProgramName[i].Name,"Demo_2")==0)||(strcmp(ProgramName[i].Name,"Demo_3")==0) ) //文件名相同
                        {
                            SelFlag[i]=0;
                            continue;
                        }*/
												#endif

                        gSystem.CurrBlock=ProgramName[i].BlockAddr;
                        NandDeleteFile();
                        SelFlag[i]=0;
                    }
                }				// nCurrentSelectPage = 0;      nCurrentSelect = 0;
                NandReadAllHead();
                if(gSystem.ProgramMax>0)
                {
                    // if(SortDataUpFlag)SortDataUpFlag=0;//按数据排序(先按数据排序,再按时间排序
                    //if(SortDataUpFlag)
                    // {
                    //  qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_data);//用此函数可实现排序功能
                    //  qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_time);//用此函数可实现排序功能
                    // }
                    // else if(SortTimeUpFlag)
                    // {
                    qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_time);//用此函数可实现排序功能
                    // }
                }
                nCurrentSelectPage = 0;
                if(nCurrentSelect+1>gSystem.ProgramMax)
                {
                    if(gSystem.ProgramMax>0) nCurrentSelect=gSystem.ProgramMax-1;
                    else nCurrentSelect=0;
                }
                //DeleleAllSelFile();//先删SPIFLASH,再删NandFlash
                //读取文件,排序
                WM_Invalidate(OpenFileWin);

            }
            else if (Id == ID_OPEN_BUTTON+3)   //工具栏第4个按钮  U盘
            {
                TouchKey.KeyStatus=1;
                if(UsbDriveFlag==0)  //本机
                {
                    if(flag_usb_disk_connect==0)
                    {
                        Usb_Init();//lugj modify 20180211
                        strcpy(PromptMenu.InputStr,TEST_INFO_MESSAGE[SystemPrameter.SystemLanguage][TEST_INFO_USB_ERROR]);
                        Prompt_Interface(PROMPT_WARMING);
                        return;
                    }
                    else
                    {
                        DeletePromptMenu(0);
                        if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                        {
                            strcpy(PromptMenu.InputStr, "Please waiting...");
                        }
                        else
                        {
                            strcpy(PromptMenu.InputStr, "Aguarde...");
                        }
                        Prompt_Interface(PROMPT_RUN);



                        StartUpPra.EnableUsbCheck=0;
                        UsbReadAllProgramHead();
                        StartUpPra.EnableUsbCheck=1;

                        DeletePromptMenu(0);

                        if(gSystem.UsbProgramMax>0)
                        {
                            // if(SortDataUpFlag)
                            //{
                            //   qsort(UsbProgramName,gSystem.UsbProgramMax,sizeof(UsbProgramName[0]),cmp_data);//用此函数可实现排序功能
                            //   qsort(UsbProgramName,gSystem.UsbProgramMax,sizeof(UsbProgramName[0]),cmp_time);//用此函数可实现排序功能
                            //  }
                            // else if(SortTimeUpFlag)
                            // {
                            qsort(UsbProgramName,gSystem.UsbProgramMax,sizeof(UsbProgramName[0]),cmp_time);//用此函数可实现排序功能
                            //  }
                        }
                        for(i=0; i<gSystem.UsbProgramMax; i++)
                        {
                            SelFlag[i]=0;
                        }
                        SelAllFlag=0;
                        nCurrentSelectPage = 0;
                        nCurrentSelect = 0;
                        UsbDriveFlag=1;
                        RefreshButton();
                        //WM_Invalidate(OpenFileWin);

                    }
                    //if(Exist==0)查看U盘是否存在
                    // {
                    //U盘不存在,提示
                    //return;
                    //}



                    //读取U盘文件
                    //读取文件,排序

                }
                else //U盘
                {
                    NandReadAllHead();
                    // if(SortDataUpFlag)SortDataUpFlag=0;//按数据排序(先按数据排序,再按时间排序
                    // if(SortDataUpFlag)
                    //{
                    //   qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_data);//用此函数可实现排序功能
                    //qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_time);//用此函数可实现排序功能
                    // }
                    // else if(SortTimeUpFlag)
                    // {
                    qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_time);//用此函数可实现排序功能
                    // }
                    for(i=0; i<gSystem.ProgramMax; i++)
                    {
                        SelFlag[i]=0;
                    }
                    //读取本机文件
                    //读取文件,排序
                    SelAllFlag=0;
                    nCurrentSelectPage = 0;
                    nCurrentSelect = 0;
                    UsbDriveFlag=0;//本机
                    RefreshButton();
                }


                WM_Invalidate(OpenFileWin);




                //   WM_DeleteWindow(ExportReportWin);
                //   WM_ShowWindow(SettingWin);/////////////////////////////////
                //gSystem.MenuRefreshFlag = 1;
                //  gSystem.SystemInterface = MI_SET;/////////////////
                //  gSystem.TitleButtonEnable = 1;//////////////////////////
            }
            else if (Id == ID_OPEN_BUTTON+4)   //工具栏第4个按钮  导入\导出
            {
                TouchKey.KeyStatus=1;
                if(flag_usb_disk_connect==0)
                {
                    Usb_Init();//lugj modify 20180211
                    strcpy(PromptMenu.InputStr,TEST_INFO_MESSAGE[SystemPrameter.SystemLanguage][TEST_INFO_USB_ERROR]);
                    Prompt_Interface(PROMPT_WARMING);
                    return;
                }
                /*if(UsbDriveFlag==0)  //本机(导出)
                {
                   
                    if( (FindFileSelFlag()==0)||(gSystem.ProgramMax<=0) ) //没有选中的文件
                    {
                        strcpy(PromptMenu.InputStr,FILE_ERROR_MESSAGE[SystemPrameter.SystemLanguage][0]);
                        Prompt_Interface(PROMPT_WARMING);
                        return;
                    }
                    else
                    {

                        //导出所有选中的程序
                        DeletePromptMenu(0);
                        if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                        {
                            strcpy(PromptMenu.InputStr, "Please waiting...");
                        }
                        else
                        {
                            strcpy(PromptMenu.InputStr, "请等待...");
                        }
                        Prompt_Interface(PROMPT_RUN);


                        gSystem.UsbProgramMax=0;
                        StartUpPra.EnableUsbCheck=0;
                        UsbReadAllProgramHead();
                        StartUpPra.EnableUsbCheck=1;

                        if( (gSystem.UsbProgramMax>0)&&(FindUsbFileSame()) )
                            //if(AskNeedOverwrite(false))//在U盘查找是否有相同的文件
                        {
                            DeletePromptMenu(0);
                            strcpy(PromptMenu.InputStr,FILE_ERROR_MESSAGE[SystemPrameter.SystemLanguage][FILE_ERROR_OVERWRITE]);
                            Prompt_Interface(PROMPT_YES_NO);

                            // GUI_Delay(10);
                            if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                            {
                                strcpy(PromptMenu.InputStr, "Please waiting...0%");
                            }
                            else
                            {
                                strcpy(PromptMenu.InputStr, "请等待...0%");
                            }


                            StartUpPra.EnableUsbCheck=0;
                            //	 Create_USB_Dir(FS_VOLUME_USB);
                            if(PromptMenu.KeyReturnValue==PROMPT_MENU_RETURN_ENTER)
                            {
                                Prompt_Interface(PROMPT_RUN);
                                FileExport(1);//1表示overwrite,导出文件并提示文件导出成功或失败
                            }
                            else
                            {
                                Prompt_Interface(PROMPT_RUN);
                                FileExport(0);//0表示不overwrite,
                            }
                            StartUpPra.EnableUsbCheck=1;
                            //重写文件
                        }
                        else
                        {
                            //ExportReportFunction();
                            //StartUpPra.EnableUsbCheck=0;
                            Create_USB_Dir(FS_VOLUME_USB);
                            //StartUpPra.EnableUsbCheck=1;

                            if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                            {
                                strcpy(PromptMenu.InputStr, "Please waiting...0%");
                            }
                            else
                            {
                                strcpy(PromptMenu.InputStr, "请等待...0%");
                            }
                            //Prompt_Interface(PROMPT_RUN);
                            RefreshPromptMenu();
                            //	GUI_Delay(10);
                            //StartUpPra.EnableUsbCheck=0;
                            // Create_USB_Dir(FS_VOLUME_USB);
                            //	StartUpPra.EnableUsbCheck=1;
                            //	GUI_Delay(20);
                            StartUpPra.EnableUsbCheck=0;

                            FileExport(0);//导出文件并提示文件导出成功或失败
                            StartUpPra.EnableUsbCheck=1;
                        }
                    }
                }*/
               // else  //U盘(导入)
                {
                    if( (FindFileSelFlag()==0)||(gSystem.UsbProgramMax<=0) ) //没有选中的文件
                    {
                        strcpy(PromptMenu.InputStr,FILE_ERROR_MESSAGE[SystemPrameter.SystemLanguage][0]);
                        Prompt_Interface(PROMPT_WARMING);
                        return;
                    }

                    if( (gSystem.ProgramMax>0)&&(FindNandFileSame()) )
                        //if( (FindFileSelFlag()==0)||(gSystem.ProgramMax<=0) ) //没有选中的文件
                        //if(AskNeedOverwrite(false))//在U盘查找是否有相同的文件
                    {
                        strcpy(PromptMenu.InputStr,FILE_ERROR_MESSAGE[SystemPrameter.SystemLanguage][FILE_ERROR_OVERWRITE]);
                        Prompt_Interface(PROMPT_YES_NO);


                        if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                        {
                            strcpy(PromptMenu.InputStr, "Please waiting...0%");
                        }
                        else
                        {
                            strcpy(PromptMenu.InputStr, "Aguarde...0%");
                        }



                        StartUpPra.EnableUsbCheck=0;
                        if(PromptMenu.KeyReturnValue==PROMPT_MENU_RETURN_ENTER)
                        {
                            Prompt_Interface(PROMPT_RUN);
                            FileImport(1);//1表示overwrite,导出文件并提示文件导出成功或失败
                        }
                        else
                        {
                            Prompt_Interface(PROMPT_RUN);
                            FileImport(0);//0表示不overwrite,
                        }
                        StartUpPra.EnableUsbCheck=1;
                        //重写文件
                    }
                    else
                    {
                        if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                        {
                            strcpy(PromptMenu.InputStr, "Please waiting...0%");
                        }
                        else
                        {
                            strcpy(PromptMenu.InputStr, "Aguarde...0%");
                        }
                        Prompt_Interface(PROMPT_RUN);


                        StartUpPra.EnableUsbCheck=0;
                        FileImport(0);//导入文件并提示文件导入成功或失败
                        StartUpPra.EnableUsbCheck=1;
                    }
                }
                //   WM_DeleteWindow(ExportReportWin);
                //   WM_ShowWindow(SettingWin);/////////////////////////////////
                //gSystem.MenuRefreshFlag = 1;
                //  gSystem.SystemInterface = MI_SET;/////////////////
                //  gSystem.TitleButtonEnable = 1;//////////////////////////
            }
            else if (Id == ID_OPEN_BUTTON+5)   //工具栏第4个按钮  Sel.all
            {
                TouchKey.KeyStatus=1;
                if(SelAllFlag)SelAllFlag=0;
                else SelAllFlag=1;
                if( (BatchOperateFlag)&&(UsbDriveFlag) )
                {
                    for(i=0; i<gSystem.UsbProgramMax; i++)
                    {
                        if(SelAllFlag)
                        {
                            SelFlag[i]=1;
                        }
                        else
                        {
                            SelFlag[i]=0;
                        }
                    }
                }
                else
                {
                    for(i=0; i<gSystem.ProgramMax; i++)
                    {
                        if(SelAllFlag)
                        {
                            SelFlag[i]=1;
                        }
                        else
                        {
                            SelFlag[i]=0;
                        }
                    }
                }
                RefreshButton();
                WM_Invalidate(OpenFileWin);
            }
            else if (Id == ID_OPEN_BUTTON+6)   //工具栏第4个按钮  返回
            {
                nCurrentSelectPage = 0;
                nCurrentSelect = 0;
//重新读取文件(SPIFLASH,NANDFLASH)

                if(UsbDriveFlag) //(BatchOperateFlag)&&
                {
                    UsbDriveFlag=0;
                    StartUpPra.EnableUsbCheck=0;
                    NandReadAllHead();
                    StartUpPra.EnableUsbCheck=1;
                    // if(SortDataUpFlag)SortDataUpFlag=0;//按数据排序(先按数据排序,再按时间排序
                    // if(SortDataUpFlag)
                    // {
                    //  qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_data);//用此函数可实现排序功能
                    //  qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_time);//用此函数可实现排序功能
                    // }
                    //else if(SortTimeUpFlag)
                    //{
                    qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_time);//用此函数可实现排序功能
                    // }
                }
                for(i=0; i<gSystem.ProgramMax; i++)
                {
                    SelFlag[i]=0;
                }
                //读取本机文件
                //读取文件,排序
                TouchKey.KeyStatus=1;
                SelAllFlag=0;
                BatchOperateFlag=0;
                RefreshButton();
                WM_Invalidate(OpenFileWin);
                // }
                // else
                // {
                //gSystem.CurrBlock=gSystem.CurrBlockBack;
                //memcpy(&BoardInf, &BoardInfBack,sizeof(BOARD_INF));  //程序拷贝

                // WM_DeleteWindow(OpenFileWin);
                //   WM_ShowWindow(SettingWin);/////////////////////////////////
                //gSystem.MenuRefreshFlag = 1;
                // gSystem.SystemInterface = MI_PROTOCOL;/////////////////
                //gSystem.TitleButtonEnable = 1;//////////////////////////

                //}

            }
        }
        break;
    }

    default:
        //		WM_DefaultProc(pMsg);
        break;
    }
}


void OpenFile_Interface(void)
{
    SortTimeUpFlag=1;
    BatchOperateFlag=0;
    UsbDriveFlag=0;
    SortDataUpFlag=0;
    //SystemPrameterBack.PrintHeaderEnable=SystemPrameter.PrintHeaderEnable;
    //strcpy(SystemPrameterBack.StrPrintHeader,SystemPrameter.StrPrintHeader);
    //ReadAllProgramHead();//
    memcpy(&BoardInfTemp,&BoardInf,sizeof(BOARD_INF));  //lugj modify 20180223
    gSystem.CurrBlockBack=gSystem.CurrBlock;

    NandReadAllHead();
    nCurrentSelectPage = 0;
    nCurrentSelect=0;

    if(gSystem.ProgramMax>1)
    {
        qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_time);//用此函数可实现排序功能
    }
    OpenFileWin = WM_CreateWindowAsChild(CONTENTBAR_POSX, CONTENTBAR_POSY, CONTENTBAR_WIDTH, CONTENTBAR_HEIGHT, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbOpenFile, 0);
    WM_BringToTop(OpenFileWin);
}


void OpenFile_Scan(void)
{
    unsigned short i,j;
    unsigned short k;
    if(TouchKey.KeyStatus==0)
    {
        GUI_PID_STATE TouchState;
        GUI_PID_GetState(&TouchState);

        if (TouchState.Pressed)
        {
            //上多页
            if ((TouchState.x>TABPAGE_LEFT_START_X-15)&&(TouchState.x<TABPAGE_LEFT_END_X+15)&&(TouchState.y>TABPAGE_LEFT_START_Y-15)
                    &&(TouchState.y<TABPAGE_LEFT_END_Y+15) )
            {
                if(nCurrentPage > 0)
                {
                    TouchKey.KeyStatus=1;
                    if(nCurrentPage>=5)             //上翻5页
                    {
                        nCurrentPage=nCurrentPage-5;
                    }
                    else
                    {
                        nCurrentPage = 0;
                    }
                    nCurrentSelectPage=0;

                    nCurrentSelect = nCurrentPage * FILE_PAGE_NUMBER + nCurrentSelectPage;
                    /*if(SelFlag[nCurrentSelect])
                     {
                         SelFlag[nCurrentSelect]=0;
                     }
                     else
                     {
                    	    SelFlag[nCurrentSelect]=1;
                     }
                    */
                    WM_Invalidate(OpenFileWin);
                }
            }
            //下多页
            else if ((TouchState.x>TABPAGE_RIGHT_START_X-15)&&(TouchState.x<TABPAGE_RIGHT_END_X+15)&&(TouchState.y>TABPAGE_RIGHT_START_Y-15)
                     &&(TouchState.y<TABPAGE_RIGHT_END_Y+15))
            {
                if( (BatchOperateFlag)&&(UsbDriveFlag) )k=gSystem.UsbProgramMax;
                else k=gSystem.ProgramMax;
                if(nCurrentPage+5 <((signed short)k-1)/FILE_PAGE_NUMBER)
                {
                    TouchKey.KeyStatus=1;
                    nCurrentPage=nCurrentPage+5;
                    nCurrentSelectPage=0;
                    nCurrentSelect = nCurrentPage * FILE_PAGE_NUMBER + nCurrentSelectPage;
                    WM_Invalidate(OpenFileWin);
                }
                else if(nCurrentPage != ((signed short)k-1)/FILE_PAGE_NUMBER)
                {
                    TouchKey.KeyStatus=1;
                    if(gSystem.ProgramMax>0)
                    {
                        nCurrentPage=((signed short)k-1)/FILE_PAGE_NUMBER;
                    }
                    else
                    {
                        nCurrentPage=0;
                    }
                    nCurrentSelectPage=0;
                    nCurrentSelect = nCurrentPage * FILE_PAGE_NUMBER + nCurrentSelectPage;
                    WM_Invalidate(OpenFileWin);
                }
            }
            //上1行(
            else if ((TouchState.x>TAB_LEFT_START_X-15)&&(TouchState.x<TAB_LEFT_END_X+15)&&(TouchState.y>TAB_LEFT_START_Y-15)&&(TouchState.y<TAB_LEFT_END_Y+15))
            {
                // nCurrentSelect--;
                if(nCurrentPage > 0)
                {
                    TouchKey.KeyStatus=1;
                    nCurrentPage--;
                    nCurrentSelectPage=0;//
                    nCurrentSelect = nCurrentPage * FILE_PAGE_NUMBER + nCurrentSelectPage;
                    WM_Invalidate(OpenFileWin);
                }
            }
            //下1页
            else if ((TouchState.x>TAB_RIGHT_START_X-15)&&(TouchState.x<TAB_RIGHT_END_X+15)&&(TouchState.y>TAB_RIGHT_START_Y-15)&&(TouchState.y<TAB_RIGHT_END_Y+15))
            {
                //nCurrentSelect++;
                TouchKey.KeyStatus=1;
                if( (BatchOperateFlag)&&(UsbDriveFlag) )k=gSystem.UsbProgramMax;
                else k=gSystem.ProgramMax;
                if(nCurrentPage+1 <((signed short)k-1)/FILE_PAGE_NUMBER)
                {
                    TouchKey.KeyStatus=1;
                    nCurrentPage=nCurrentPage+1;
                    nCurrentSelectPage=0;//
                    nCurrentSelect = nCurrentPage * FILE_PAGE_NUMBER + nCurrentSelectPage;
                    WM_Invalidate(OpenFileWin);
                }
                else
                {
                    if(gSystem.ProgramMax>0)
                    {
                        nCurrentPage=((signed short)k-1)/FILE_PAGE_NUMBER;
                    }
                    else
                    {
                        nCurrentPage=0;
                    }
                    nCurrentSelectPage=0;
                    nCurrentSelect = nCurrentPage * FILE_PAGE_NUMBER + nCurrentSelectPage;
                    WM_Invalidate(OpenFileWin);
                }
            }
            //输入1行的信息
            else if ((TouchState.x>PAGE_SELECT_START_X)&&(TouchState.x<PAGE_SELECT_END_X)&&(TouchState.y>PAGE_SELECT_START_Y)&&(TouchState.y<PAGE_SELECT_END_Y+PAGE_SELECT_DIS_Y)&&(gSystem.ProgramMax>0))//page.selectLocateY[5]+SELECT_HIGH))//第一行
            {
                TouchKey.KeyStatus=1;
                if(BatchOperateFlag==0)                                      //打开状态下
                {
                    i = (TouchState.y - PAGE_SELECT_START_Y) / PAGE_SELECT_DIS_Y;
                    j = nCurrentPage * FILE_PAGE_NUMBER + i;
                    if(j<gSystem.ProgramMax)
                    {
                        nCurrentSelectPage=i;
                        nCurrentSelect=j;
                        WM_Invalidate(OpenFileWin);
                    }
                }
                else if(BatchOperateFlag) //批量处理模式下
                {
                    nCurrentSelectPage = (TouchState.y - PAGE_SELECT_START_Y) / PAGE_SELECT_DIS_Y;
                    nCurrentSelect = nCurrentPage * FILE_PAGE_NUMBER+ nCurrentSelectPage;
                    if( ((nCurrentSelect<gSystem.ProgramMax)&&(UsbDriveFlag==0))||
                            ((nCurrentSelect<gSystem.UsbProgramMax)&&(UsbDriveFlag)) )
                    {
                        unsigned short sel_flag=0,unsel_flag=0;

                        if(SelFlag[nCurrentSelect])SelFlag[nCurrentSelect]=0;
                        else SelFlag[nCurrentSelect]=1;


                        if(UsbDriveFlag)
                        {
                            for(i=0; i<gSystem.UsbProgramMax; i++)
                            {
                                if(SelFlag[i])
                                {
                                    sel_flag++;
                                }
                                else
                                {
                                    unsel_flag++;
                                }
                            }
                            if((sel_flag==gSystem.UsbProgramMax)&&(gSystem.UsbProgramMax>0) )
                            {
                                SelAllFlag=1;
                                RefreshButton();
                            }
                            else if((unsel_flag==gSystem.UsbProgramMax)&&(gSystem.UsbProgramMax>0) )
                            {
                                SelAllFlag=0;
                                RefreshButton();
                            }
                        }
                        else //if(UsbDriveFlag)
                        {
                            for(i=0; i<gSystem.ProgramMax; i++)
                            {
                                if(SelFlag[i])
                                {
                                    sel_flag++;
                                }
                                else
                                {
                                    unsel_flag++;
                                }
                            }
                            if( (sel_flag==gSystem.ProgramMax)&&(gSystem.ProgramMax>0) )
                            {
                                SelAllFlag=1;
                                RefreshButton();
                            }
                            else if((unsel_flag==gSystem.ProgramMax)&&(gSystem.ProgramMax>0) )
                            {
                                SelAllFlag=0;
                                RefreshButton();
                            }
                        }
                        WM_Invalidate(OpenFileWin);
                    }
                }

            }//else if ((TouchState.x>PAGE_SELECT_START_X)&&(TouchState.x<PAGE_SELECT_END_X)&&(TouchState.y>PAGE_SELECT_START_Y)&&(TouchState.y<PAGE_SELECT_END_Y))//page.selectLocateY[5]+SELECT_HIGH))//第一行
            //按Data和时间排序
            else if ( ((TouchState.x>TABLE_HITORICAL_COLUMN_FILE_DATA)&&(TouchState.x<TABLE_HITORICAL_COLUMN_FILE_TIME)&&(TouchState.y>TABLE_QUALITY_START_Y)&&
                       (TouchState.y<TABLE_QUALITY_START_Y+PAGE_SELECT_DIS_Y)))//page.selectLocateY[5]+SELE
                //初使状态，Batch Op
            {
                //SortFlag=SORT_DATA;
                if(SortDataUpFlag)SortDataUpFlag=0;//按数据排序(先按数据排序,再按时间排序
                else SortDataUpFlag=1;
                if( (BatchOperateFlag)&&(UsbDriveFlag) )
                {
                    qsort(UsbProgramName,gSystem.UsbProgramMax,sizeof(UsbProgramName[0]),cmp_data);//用此函数可实现排序功能
                    //qsort(UsbProgramName,gSystem.UsbProgramMax,sizeof(UsbProgramName[0]),cmp_time);//用此函数可实现排序功能
                }
                else
                {
                    qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_data);//用此函数可实现排序功能
                    // qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_time);//用此函数可实现排序功能
                }
                WM_Invalidate(OpenFileWin);
                TouchKey.KeyStatus=1;
            }
            //按时间排序
            else if ( ((TouchState.x>TABLE_HITORICAL_COLUMN_FILE_TIME)&&(TouchState.x<TABLE_HITORICAL_COLUMN_FILE_TIME+80)&&(TouchState.y>TABLE_QUALITY_START_Y)&&(TouchState.y<TABLE_QUALITY_START_Y+PAGE_SELECT_DIS_Y)))
                //page.selectLocateY[5]+SELE)//初使状态，Batch Op
            {
                //SortFlag=SORT_TIME;
                if(SortTimeUpFlag)SortTimeUpFlag=0;//按时间排序
                else SortTimeUpFlag=1;
                if( (BatchOperateFlag)&&(UsbDriveFlag) )
                {
                    qsort(UsbProgramName,gSystem.UsbProgramMax,sizeof(UsbProgramName[0]),cmp_time);//用此函数可实现排序功能
                }
                else
                {
                    qsort(ProgramName,gSystem.ProgramMax,sizeof(ProgramName[0]),cmp_time);//用此函数可实现排序功能
                }
                WM_Invalidate(OpenFileWin);
                TouchKey.KeyStatus=1;
            }


        }//if (TouchState.Pressed)
    }//if(TouchKey.KeyStatus==0)
}

//#include "RTE_Components.h"             // Component selection
void OpenFile_Go(void)
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
}



