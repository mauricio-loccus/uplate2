#include "MainTask.h"
WM_HWIN RemoteWin = NULL;


const char STR_PROMPT_REMOTE[LANGUAGE_TYPES][100] = {"Remote PC is connected.", "PC已连接"};



void DeletePCMenu(void)
{
    WM_DeleteWindow(RemoteWin);
    GUI_Delay(50);
}

void _cbRemote(WM_MESSAGE * pMsg)
{
    WM_HWIN hWin = pMsg->hWin;

    int        xSize;
    int        ySize;

    GUI_RECT rect;

    switch (pMsg->MsgId)
    {
    case WM_CREATE:
    {
        break;
    }


    case WM_DELETE:
        break;

    case WM_PAINT:
        xSize = WM_GetWindowSizeX(hWin);
        ySize = WM_GetWindowSizeY(hWin);

        GUI_SetColor(COLOR_TITLEBAR);
        GUI_FillRect(0, 0, xSize - 1, ySize - 1);
GUI_SetColor(GUI_GRAY);
				GUI_DrawLine(0,0, xSize - 1,0);
				GUI_DrawLine(0,CONTENTBAR_TITLE_HEIGHT - 1, xSize - 1,CONTENTBAR_TITLE_HEIGHT - 1);
        GUI_SetTextMode(GUI_TM_TRANS);

        GUI_SetColor(COLOR_PAINT_TXT);
        //
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            GUI_SetFont(GUI_FONT_BIG);
        }
        else
        {
            GUI_SetFont(GUI_FONT_BIG_CH);
        }

        //"Filter 1"
        rect.x0 = 50;
        rect.y0 = 220;
        rect.x1 = 750;
        rect.y1 = 260;
        GUI_DispStringInRect(STR_PROMPT_REMOTE[SystemPrameter.SystemLanguage], &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);

        break;

    case WM_NOTIFY_PARENT:
    {

        break;
    }

    default:
        //		WM_DefaultProc(pMsg);
        break;
    }
}

void Remote_Interface(void)
{
    RemoteInfo_PC.RemoteFlag=1;
    RemoteWin = WM_CreateWindowAsChild(0, 0, 799, 479, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbRemote, 0);
    WM_BringToTop(RemoteWin);
}

