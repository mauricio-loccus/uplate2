
/*SystemInOutKeyPress(Id);

SystemUpdateKeyPress(Id);

*/

//#include "GUIDEMO.h"
#include "MainTask.h"
#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>
#include  "bsp.h"
//lgj161013 start
//#define  ID_SYSTEM_UPDATE_BUTTON                   (GUI_ID_USER+228) //+2 //fmc160818
//#define  ID_PROGBAR                             (GUI_ID_USER+231)
//lgj161013 end
#define BUTTON_COLOR_TEXT_DISABLED      0xb1aeae
#define BUTTON_COLOR_TEXT_PRESSED       0xfcfdff
#define BUTTON_COLOR_TEXT_UNPRESSED     0x5b8bd8


WM_HWIN PROGBAR;
WM_HWIN SystemUpdateWin = NULL;                //????
EDIT_Handle EditUpdate;
int flag_update = 0;
unsigned char flag_start_update=0,flag_update_one_ok=0;
//void refresh_PROGBAR(int cent);
//extern u8 Read_write_bin_File(void);
//extern u8 Read_send_bin_File(void);
//extern u8 UART_Send_Buf[600];//FMC160923
extern void bsp_InitIwdg(uint32_t _ulIWDGTime);
extern void IWDG_Feed(void);
extern unsigned char flag_usb_disk_connect;//////////
unsigned char flag_update_busy=0;


const char UPDATE_MAIN_TITLE[LANGUAGE_TYPES][30] = { "Software Upgrade","Software Upgrade"};

/*
typedef struct {
	int          xPos;
	int          yPos;
	int          xSize;
	int          ySize;
	const char * acLabelEn;									 //按钮对应的键码
	const char * acLabelCh;
} BUTTON_DATA;
*/

const BUTTON_DATA _aButtonSystemUpdate[] =
{
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(1), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Upgrade", "Upgrade" },
    { TOOLS1_BUTTON_POSX, TOOLS1_BUTTON_POSY(4), TOOLS1_BUTTON_WIDTH, TOOLS1_BUTTON_HEIGHT, "Back", "Voltar" },
};




void refresh_PROGBAR(int cent)
{
    PROGBAR_SetValue(PROGBAR, cent);
    GUI_Delay(10);
    check_usb_connect();
}
//unsigned char LanguageFlag;
void _cbSystemUpdate(WM_MESSAGE * pMsg)
{
    int        xSize;
    int        ySize;//, Sel;
    WM_HWIN hWin = pMsg->hWin;
//	WM_HWIN hWinFocus;
    BUTTON_Handle hbutton;

    short NCode, Id,  i;

    PROGBAR_SKINFLEX_PROPS   PROGBAR_SKI = {  {COLOR_BUTTON_DEFAULT,COLOR_BUTTON_DEFAULT}, {COLOR_BUTTON_DEFAULT,COLOR_BUTTON_DEFAULT}, {GUI_WHITE,GUI_WHITE},{GUI_WHITE,GUI_WHITE},COLOR_BUTTON_DEFAULT,GUI_BLACK };

    //hWinFocus = WM_GetFocussedWindow();
    //IdWinFocus = WM_GetId(hWinFocus);
    switch (pMsg->MsgId)
    {
    case WM_CREATE:
    {
        //set_button_skin();//fmc161013
        PROGBAR=PROGBAR_CreateEx(220,200,250,35,hWin,WM_CF_SHOW,PROGBAR_CF_HORIZONTAL,ID_PROGBAR);
        PROGBAR_SetValue(PROGBAR, 0);
        // PROGBAR_SetFont(PROGBAR, &SIF_Font24);
        PROGBAR_SetSkinFlexProps(&PROGBAR_SKI,0);//???
        PROGBAR_SetTextColor(PROGBAR,0,GUI_WHITE);
        PROGBAR_SetTextColor(PROGBAR,1,GUI_BLACK);


        for (i = 0; i < GUI_COUNTOF(_aButtonSystemUpdate); i++)
        {
            hbutton = BUTTON_CreateEx(_aButtonSystemUpdate[i].xPos, _aButtonSystemUpdate[i].yPos, _aButtonSystemUpdate[i].xSize, _aButtonSystemUpdate[i].ySize,
                                      hWin, WM_CF_SHOW, 0, ID_SYSTEM_UPDATE_BUTTON + i);
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG);
                BUTTON_SetText(hbutton, _aButtonSystemUpdate[i].acLabelEn);
            }
            else
            {
                BUTTON_SetFont(hbutton, GUI_FONT_BIG_CH);
                BUTTON_SetText(hbutton, _aButtonSystemUpdate[i].acLabelCh);
            }
            BUTTON_SetTextAlign(hbutton, GUI_TA_HCENTER | GUI_TA_VCENTER);
            BUTTON_SetFocussable(hbutton, 0);
        }
        break;
    }
    case WM_DELETE:
        WM_DeleteWindow(PROGBAR);
        break;
    case WM_PAINT:
        //set_button_skin();
        xSize = WM_GetWindowSizeX(hWin);
        ySize = WM_GetWindowSizeY(hWin);

        GUI_SetTextMode(GUI_TM_TRANS);
        GUI_SetFont(GUI_FONT_BIG);

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

        //标题
        GUI_SetColor(COLOR_PAINT_TXT);
        GUI_SetFont(GUI_FONT_BIG);
        GUI_DispStringAt(UPDATE_MAIN_TITLE[SystemPrameter.SystemLanguage], CONTENTBAR_CAPTION_POSX, CONTENTBAR_CAPTION_POSY);



        break;
    case WM_NOTIFY_PARENT:
    {
        if(flag_update_busy==1)
        {
            break;                             //忙时不能再更新
        }
        if(RemoteInfo_PC.RemoteFlag)
        {
            break;
        }
        if( (KeyPadAsc.UseFlag == KEYPAD_BUSY)||(KeyPadNum.UseFlag == KEYPAD_BUSY)||(PromptMenu.InterfaceStatus==PROMPT_MENU_BUSY) )
        {
            break;
        }
        Id = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        switch (NCode)
        {
        case WM_NOTIFICATION_RELEASED:
            // screen_busy_delay=0;
            if (Id == ID_SYSTEM_UPDATE_BUTTON)
            {
                refresh_PROGBAR(0);
                //如果USB未插入
                if(flag_usb_disk_connect==0)
                {
                    Usb_Init();//lugj modify 20180211
                    strcpy(PromptMenu.InputStr,TEST_INFO_MESSAGE[SystemPrameter.SystemLanguage][TEST_INFO_USB_ERROR]);
                    Prompt_Interface(PROMPT_WARMING);
                    break;
                }
                flag_update_busy=1;
                StartUpPra.EnableUsbCheck=0;
                if(Read_write_bin_File())
                {
                    StartUpPra.EnableUsbCheck=1;
                    if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                    {
                        strcpy(PromptMenu.InputStr,"Upgrade is fail.");
                    }
                    else
                    {
                        strcpy(PromptMenu.InputStr,"升级失败.");
                    }
                    Prompt_Interface(PROMPT_ERROR);
                }
                else	 //更新OK
                {
                    StartUpPra.EnableUsbCheck=1;
                    if (SystemPrameter.SystemLanguage == LANGUAGE_EN)
                    {
                        strcpy(PromptMenu.InputStr,"Upgrade is OK.");
                    }
                    else
                    {
                        strcpy(PromptMenu.InputStr,"Atualizado com Sucesso");
                    }
                    Prompt_Interface(PROMPT_OK);
                    GUI_Delay(200);
                    bsp_InitIwdg(1000);
                    IWDG_Feed();
                    while(1); //重启
                }
            }
            if (Id == ID_SYSTEM_UPDATE_BUTTON+1)  //返回
            {
                gSystem.SystemInterface = MI_MAITENACE;
                WM_DeleteWindow(SystemUpdateWin);
            }
        }
    }
    break;
    default:
//		WM_DefaultProc(pMsg);
        break;

    }
}


void SystemUpdate_Interface(void)
{
    flag_update_busy=0;
    SystemUpdateWin = WM_CreateWindowAsChild(CONTENTBAR_POSX, CONTENTBAR_POSY, CONTENTBAR_WIDTH, CONTENTBAR_HEIGHT, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbSystemUpdate, 0);
    WM_BringToTop(SystemUpdateWin);


//gSystem.TitleUpdateFlag = 1;
//gSystem.ContentUpdateFlag = 1;
//gSystem.ToolsUpdateFlag = 1;
//gSystem.StatusUpdateFlag = 1;
}
