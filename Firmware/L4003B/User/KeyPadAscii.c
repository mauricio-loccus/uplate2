
#include "MainTask.h"


#include  <stdarg.h>
#include  <stdio.h>
#include  <stdlib.h>
#include  <math.h>





#define COLOR_BORDER          0xafafaf // 0xBD814F
#define COLOR_KEYPAD0          0xA8D403
#define COLOR_KEYPAD1          0xBF5C00

//?????
#define BUTTON_COLOR_BK_DISABLED      0xe3e3e3
#define BUTTON_COLOR_BK_PRESSED       0xe3855a2
#define BUTTON_COLOR_BK_UNPRESSED     0xd9e9ff

#define BUTTON_COLOR_BORDER_DISABLED   0xb1aeae
#define BUTTON_COLOR_BORDER_PRESSED    0x789fde
#define BUTTON_COLOR_BORDER_UNPRESSED  0x789fde

#define BUTTON_COLOR_TEXT_DISABLED      0xb1aeae
#define BUTTON_COLOR_TEXT_PRESSED       0xfcfdff
#define BUTTON_COLOR_TEXT_UNPRESSED     0x5b8bd8


#define KEYPAD_POSX               0
#define KEYPAD_POSY             (250-45+40)
//#define KEYPAD_POSY             (250-45)
//#define KEYPAD_POSY               209
#define KEYPAD_WIDTH              800
//#define KEYPAD_HEIGHT            231
#define KEYPAD_HEIGHT              480//230//(230)//-45)

#define TXT_PROMPT_POSX            12			// (KEYPAD_POSX+12)
#define TXT_PROMPT_POSY            8+3			// (KEYPAD_POSY+20)
#define TXT_PROMPT_WIDTH           120
#define TXT_PROMPT_HEIGHT          30



#define EDIT_MESSAGE_POSX          (TXT_PROMPT_POSX+TXT_PROMPT_WIDTH+10)
#define EDIT_MESSAGE_POSY           8+5			//(KEYPAD_POSY+35)
#define EDIT_MESSAGE_WIDTH          300
#define EDIT_MESSAGE_HEIGHT         30

#define TXT_ERR_POSX                (EDIT_MESSAGE_POSX+EDIT_MESSAGE_WIDTH+10)
#define TXT_ERR_POSY                TXT_PROMPT_POSY
#define TXT_ERR_WIDTH               300
#define TXT_ERR_HEIGHT              TXT_PROMPT_HEIGHT

#define BUTTON_STARTX              (TXT_PROMPT_POSX)
#define BUTTON_STARTY              (EDIT_MESSAGE_POSY +EDIT_MESSAGE_HEIGHT+15)
#define BUTTON_WIDTH                70  //70
#define BUTTON_HEIGHT               35  //35
#define BUTTON_DISX                (BUTTON_WIDTH+8)
#define BUTTON_DISY                (BUTTON_HEIGHT+5)

#define LINEAR_POSY              (BUTTON_STARTY-10)



#define KEYPAD_ASCII_NUM_ENTER      33
#define KEYPAD_ASCII_ID_ENTER       (KEYPAD_ASCII_ID_BUTTON0+KEYPAD_ASCII_NUM_ENTER)

#define KEYPAD_ASCII_NUM_ESC      29
#define KEYPAD_ASCII_ID_ESC       (KEYPAD_ASCII_ID_BUTTON0+KEYPAD_ASCII_NUM_ESC)

#define KEYPAD_ASCII_NUM_ABC       28
#define KEYPAD_ASCII_ID_ABC       (KEYPAD_ASCII_ID_BUTTON0+KEYPAD_ASCII_NUM_ABC)

#define KEYPAD_ASCII_NUM_DEL      27
#define KEYPAD_ASCII_ID_DEL       (KEYPAD_ASCII_ID_BUTTON0+KEYPAD_ASCII_NUM_DEL)

#define KEYPAD_ASCII_NUM_CAPS       19
#define KEYPAD_ASCII_ID_CAPS       (KEYPAD_ASCII_ID_BUTTON0+KEYPAD_ASCII_NUM_CAPS)


const char ENTER_FILE_NAME_ERROR[LANGUAGE_TYPES][TESTDLG_TITLE_CHAR_MAX] = {"Please enter file name.", "Insira o nome do arquivo."}; //2015-3-16
const char OVERWRITE_DEMO_FILE_ERROR[LANGUAGE_TYPES][RUN_ERROR_CHAR_MAX] = {"A demo file is not allowed to overwrite.", "Substituição Bloqueada!"}; //2015-3-16
const char SAME_FILE_ERROR[LANGUAGE_TYPES][RUN_ERROR_CHAR_MAX] = {"The same file name already exists.","Nome de arquivo existente!"}; //2015-3-16
const char REPORT_TITLE_ERROR[LANGUAGE_TYPES][RUN_ERROR_CHAR_MAX] = {"Please enter report title.", "Insira o nome do Resultado"}; //2015-3-16







typedef struct {
    int          xPos;
    int          yPos;
    int          xSize;
    int          ySize;
    const char * acLabel123;                     //?????????
    const char * acLabelSmall;                   //?????????????
    const char * acLabelBig;                     //?????????
    char         FunctionKey;                    //????????,1:??????,0:??????
} BUTTON_ASCII_DATA;

const BUTTON_ASCII_DATA _aButtonData[] =
{
    //?1???
    { BUTTON_STARTX, BUTTON_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT, "1", "q", "Q", 0 },      //0
    { BUTTON_STARTX + BUTTON_DISX, BUTTON_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT, "2", "w", "W", 0 },
    { BUTTON_STARTX + BUTTON_DISX * 2, BUTTON_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT, "3", "e", "E", 0 },
    { BUTTON_STARTX + BUTTON_DISX * 3, BUTTON_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT, "4", "r", "R", 0 },
    { BUTTON_STARTX + BUTTON_DISX * 4, BUTTON_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT, "5", "t", "T", 0 },
    { BUTTON_STARTX + BUTTON_DISX * 5, BUTTON_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT, "6", "y", "Y", 0 },
    { BUTTON_STARTX + BUTTON_DISX * 6, BUTTON_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT, "7", "u", "U", 0 },
    { BUTTON_STARTX + BUTTON_DISX * 7, BUTTON_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT, "8", "i", "I", 0 },
    { BUTTON_STARTX + BUTTON_DISX * 8, BUTTON_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT, "9", "o", "O", 0 },
    { BUTTON_STARTX + BUTTON_DISX * 9, BUTTON_STARTY, BUTTON_WIDTH, BUTTON_HEIGHT, "0", "p", "P", 0 },//9
    //?2???
    { BUTTON_STARTX + BUTTON_WIDTH/2, BUTTON_STARTY + BUTTON_DISY, BUTTON_WIDTH, BUTTON_HEIGHT, "!", "a", "A", 0 },  //10
    { BUTTON_STARTX + BUTTON_WIDTH/2 + BUTTON_DISX, BUTTON_STARTY + BUTTON_DISY, BUTTON_WIDTH, BUTTON_HEIGHT, "@", "s", "S", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 2, BUTTON_STARTY + BUTTON_DISY, BUTTON_WIDTH, BUTTON_HEIGHT, "#", "d", "D", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 3, BUTTON_STARTY + BUTTON_DISY, BUTTON_WIDTH, BUTTON_HEIGHT, "$", "f", "F", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 4, BUTTON_STARTY + BUTTON_DISY, BUTTON_WIDTH, BUTTON_HEIGHT, "%", "g", "G", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 5, BUTTON_STARTY + BUTTON_DISY, BUTTON_WIDTH, BUTTON_HEIGHT, "&", "h", "H", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 6, BUTTON_STARTY + BUTTON_DISY, BUTTON_WIDTH, BUTTON_HEIGHT, "*", "j", "J", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 7, BUTTON_STARTY + BUTTON_DISY, BUTTON_WIDTH, BUTTON_HEIGHT, "(", "k", "K", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 8, BUTTON_STARTY + BUTTON_DISY, BUTTON_WIDTH, BUTTON_HEIGHT, ")", "l", "L", 0 },//18
    //?3???
    { BUTTON_STARTX, BUTTON_STARTY + BUTTON_DISY * 2, BUTTON_WIDTH/2+BUTTON_WIDTH, BUTTON_HEIGHT, "","","", 1 },    //Capslock  19
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX, BUTTON_STARTY + BUTTON_DISY * 2, BUTTON_WIDTH, BUTTON_HEIGHT, "+", "z", "Z", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 2, BUTTON_STARTY + BUTTON_DISY * 2, BUTTON_WIDTH, BUTTON_HEIGHT, "-", "x", "X", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 3, BUTTON_STARTY + BUTTON_DISY * 2, BUTTON_WIDTH, BUTTON_HEIGHT, "|", "c", "C", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 4, BUTTON_STARTY + BUTTON_DISY * 2, BUTTON_WIDTH, BUTTON_HEIGHT, "/", "v", "V", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 5, BUTTON_STARTY + BUTTON_DISY * 2, BUTTON_WIDTH, BUTTON_HEIGHT, " ? ", "b", "B", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 6, BUTTON_STARTY + BUTTON_DISY * 2, BUTTON_WIDTH, BUTTON_HEIGHT, "<", "n", "N", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 7, BUTTON_STARTY + BUTTON_DISY * 2, BUTTON_WIDTH, BUTTON_HEIGHT, ">", "m", "M", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 8+11, BUTTON_STARTY + BUTTON_DISY * 2, BUTTON_WIDTH+28, BUTTON_HEIGHT, "", "", "", 1 },//27
    //?4???
    { BUTTON_STARTX,               BUTTON_STARTY + BUTTON_DISY * 3, BUTTON_WIDTH, BUTTON_HEIGHT, "abc","123","123", 1 },//ABC  28
    { BUTTON_STARTX + BUTTON_DISX, BUTTON_STARTY + BUTTON_DISY * 3, BUTTON_WIDTH, BUTTON_HEIGHT, "", "", "", 1 },       //29
    { BUTTON_STARTX + BUTTON_DISX * 2, BUTTON_STARTY + BUTTON_DISY * 3, BUTTON_DISX*4+BUTTON_WIDTH/2-8, BUTTON_HEIGHT, " ", " ", " ", 0 }, // Space 30
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 6, BUTTON_STARTY + BUTTON_DISY * 3, BUTTON_WIDTH, BUTTON_HEIGHT, ", ", ",", ",", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 7, BUTTON_STARTY + BUTTON_DISY * 3, BUTTON_WIDTH, BUTTON_HEIGHT, ".",".", ".", 0 },
    { BUTTON_STARTX + BUTTON_WIDTH / 2 + BUTTON_DISX * 8, BUTTON_STARTY + BUTTON_DISY * 3, BUTTON_WIDTH / 2 + BUTTON_DISX, BUTTON_HEIGHT, "", "", "", 1 },//Enter //33
};                                                                                                  //70/2+70+8=113                       //35





KEYPAD_ASC KeyPadAsc;

TEXT_Handle TxtNamePrompt;                      //
TEXT_Handle TxtErrPrompt;                       //
EDIT_Handle EditNameMessage;                    //


char CmpFileName[PROGRAM_NAME_LENGTH];

WM_HWIN KeyPadAsciiWin = NULL;




u8 check_same_name(unsigned char flag)
{
    u16 i;

    for (i = 0; i < gSystem.ProgramMax; i++)  //lgj171116 这里要改成gSystem.ProgramMax  PROGRAM_MAX
    {
        if(strcmp(ProgramName[i].Name,CmpFileName)==0)
        {
            if(flag)
            {
                gSystem.CurrBlock=ProgramName[i].BlockAddr;
            }
            return 1;
        }
    }
    return 0;
}

void SetAsciiBUTTONColor(BUTTON_Handle BUTTON_CENT)
{
    BUTTON_SetBkColor(BUTTON_CENT, BUTTON_CI_DISABLED, GUI_GRAY);
    BUTTON_SetBkColor(BUTTON_CENT, BUTTON_CI_PRESSED, 0X96842c);
    BUTTON_SetBkColor(BUTTON_CENT, BUTTON_CI_UNPRESSED, 0x291913);

    BUTTON_SetTextColor(BUTTON_CENT, BUTTON_CI_DISABLED, GUI_BLACK);
    BUTTON_SetTextColor(BUTTON_CENT, BUTTON_CI_PRESSED, 0XFFFFFF);
    BUTTON_SetTextColor(BUTTON_CENT, BUTTON_CI_UNPRESSED, 0xFFFFFF);
}
void SetAsciiButtonSkin(void)
{
    //BUTTON_SKINFLEX_PROPS   BUTTON_SKI_NORMAL = { { 0xeed72d, 0xeed72d, 0x291913 }, { 0x291913, 0x291913 }, { 0x291913, 0x291913 }, 4 };
		BUTTON_SKINFLEX_PROPS   BUTTON_SKI_NORMAL = { { 0xeed72d, 0xeed72d, 0x130b09 }, { 0x130b09, 0x130b09 }, { 0x130b09, 0x130b09 }, 4 };
    BUTTON_SKINFLEX_PROPS   BUTTON_SKI_PRESS = { { 0xeed72d, 0xeed72d, 0x96842c }, { 0x96842c, 0x96842c }, { 0x96842c, 0x96842c }, 4 };
    BUTTON_SKINFLEX_PROPS   BUTTON_SKI_DISABLE = { { GUI_GRAY, 0x444040, 0x444040 }, { 0x444040, 0x444040 }, { 0x444040, 0x444040 }, 4 };

    BUTTON_SetDefaultSkin(BUTTON_SKIN_FLEX);
    {
        BUTTON_SetSkinFlexProps(&BUTTON_SKI_PRESS, BUTTON_SKINFLEX_PI_PRESSED);
        BUTTON_SetSkinFlexProps(&BUTTON_SKI_NORMAL, BUTTON_SKINFLEX_PI_FOCUSSED);
        BUTTON_SetSkinFlexProps(&BUTTON_SKI_NORMAL, BUTTON_SKINFLEX_PI_ENABLED);
        BUTTON_SetSkinFlexProps(&BUTTON_SKI_DISABLE, BUTTON_SKINFLEX_PI_DISABLED);
    }
}

void _cbKeyPadAscii(WM_MESSAGE * pMsg)
{
    WM_HWIN    hWin, hWinFocus;
    WM_HWIN    hButton;
    int        Id;
    int        NCode;
    int        xSize;
    int        ySize;
    unsigned char  i;
    unsigned char s_Key;
    char s_Textbuf[20] = { 0 };

    hWin = pMsg->hWin;

    hWinFocus = WM_GetFocussedWindow();
//	IdWinFocus = WM_GetId(hWinFocus);


    switch (pMsg->MsgId)
    {
    case WM_CREATE:

        SetAsciiButtonSkin();

        for (i = 0; i < GUI_COUNTOF(_aButtonData); i++)//??????
        {
            hButton = BUTTON_CreateEx(_aButtonData[i].xPos, _aButtonData[i].yPos, _aButtonData[i].xSize, _aButtonData[i].ySize,
                                      hWin, WM_CF_SHOW, 0, KEYPAD_ASCII_ID_BUTTON + i);
            SetAsciiBUTTONColor(hButton);
            BUTTON_SetFont(hButton, &GUI_Font20_ASCII);//SIF_Font24);fmc161118
            //if (KeyPadFlag == KEYPAD_NAME)
            BUTTON_SetText(hButton, _aButtonData[i].acLabelSmall);
            //else
            //BUTTON_SetText(hButton, _aButtonData[i].acLabel123);

            if (i == KEYPAD_ASCII_NUM_ENTER)
                BUTTON_SetBitmapEx(hButton,BUTTON_BI_UNPRESSED, &bmenter,0,0);
            else if (i == KEYPAD_ASCII_NUM_ESC)
                BUTTON_SetBitmapEx(hButton,BUTTON_BI_UNPRESSED, &bmESC,0,0);
            else if (i == KEYPAD_ASCII_NUM_DEL)
            {
              BUTTON_SetBitmapEx(hButton,BUTTON_BI_UNPRESSED, &bmback_space,36,10);
            }
            else if (i == KEYPAD_ASCII_NUM_CAPS)
            {
                BUTTON_SetBitmapEx(hButton,BUTTON_BI_UNPRESSED, &bmBmCAP,40,8);
            }
            BUTTON_SetTextAlign(hButton, GUI_TA_HCENTER | GUI_TA_VCENTER);


            if(i==30||i==31||i==32)
            {
                WM_DisableWindow(hButton);
            }

            BUTTON_SetFocussable(hButton, 0);
        }

        //if (KeyPadFlag == KEYPAD_NAME)  //???????,??????
        //{
        //	EDIT_Create
        //hEdit = EDIT_Create(10, 200, 80, 30, GUI_ID_EDIT0, 20, 0);
        TxtNamePrompt = TEXT_CreateEx(TXT_PROMPT_POSX, TXT_PROMPT_POSY, TXT_PROMPT_WIDTH+120, TXT_PROMPT_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, TEXT_CF_LEFT | TEXT_CF_VCENTER, KEYPAD_ASCII_ID_TEXT, "");
        TEXT_SetTextColor(TxtNamePrompt, GUI_WHITE);

       
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            // BUTTON_SetFont(hbutton, GUI_FONT_BIG);
            TEXT_SetFont(TxtNamePrompt, GUI_FONT_BIG);
            // TEXT_SetText(TxtNamePrompt, "Please input:");
					  if(KeyPadAsc.PromptFlag==PROMPT_TITLE)
						{
							  TEXT_SetText(TxtNamePrompt, "Enter title:");
							  EditNameMessage = EDIT_CreateEx(EDIT_MESSAGE_POSX, EDIT_MESSAGE_POSY, EDIT_MESSAGE_WIDTH, EDIT_MESSAGE_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, KEYPAD_ASCII_ID_EDIT, PROGRAM_NAME_LENGTH-1);
                
							  TxtErrPrompt = TEXT_CreateEx(TXT_ERR_POSX, TXT_ERR_POSY, TXT_ERR_WIDTH, TXT_ERR_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, TEXT_CF_LEFT | TEXT_CF_VCENTER, KEYPAD_ASCII_ID_TEXT, "");
                TEXT_SetTextColor(TxtErrPrompt, GUI_RED);
                WM_HideWindow(TxtErrPrompt);//隐
						}
					  else if(KeyPadAsc.PromptFlag==PROMPT_RESULT_FILE_NAME) 
						{
					      TEXT_SetText(TxtNamePrompt, "Enter results file name:");
							  EditNameMessage = EDIT_CreateEx(EDIT_MESSAGE_POSX+90, EDIT_MESSAGE_POSY, EDIT_MESSAGE_WIDTH, EDIT_MESSAGE_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, KEYPAD_ASCII_ID_EDIT, PROGRAM_NAME_LENGTH-1);
 
							  TxtErrPrompt = TEXT_CreateEx(TXT_ERR_POSX+90, TXT_ERR_POSY, TXT_ERR_WIDTH, TXT_ERR_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, TEXT_CF_LEFT | TEXT_CF_VCENTER, KEYPAD_ASCII_ID_TEXT, "");
                TEXT_SetTextColor(TxtErrPrompt, GUI_RED);
                WM_HideWindow(TxtErrPrompt);//隐
					  }
						else if(KeyPadAsc.PromptFlag==PROMPT_WELLS_NAME) //lugj 20180927
						{
					      TEXT_SetText(TxtNamePrompt, "Enter Well No.:");
							  EditNameMessage = EDIT_CreateEx(EDIT_MESSAGE_POSX+25, EDIT_MESSAGE_POSY, EDIT_MESSAGE_WIDTH, EDIT_MESSAGE_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, KEYPAD_ASCII_ID_EDIT, PROGRAM_NAME_LENGTH-1);
 
							  TxtErrPrompt = TEXT_CreateEx(TXT_ERR_POSX+25, TXT_ERR_POSY, TXT_ERR_WIDTH, TXT_ERR_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, TEXT_CF_LEFT | TEXT_CF_VCENTER, KEYPAD_ASCII_ID_TEXT, "");
                TEXT_SetTextColor(TxtErrPrompt, GUI_RED);
                WM_HideWindow(TxtErrPrompt);//隐
					  }
						else// if(KeyPadAsc.PromptFlag==PROMPT_PROTOCOL_FILE_NAME) 
						{	
                TEXT_SetText(TxtNamePrompt, "Enter protocol file name:");
							  EditNameMessage = EDIT_CreateEx(EDIT_MESSAGE_POSX+100, EDIT_MESSAGE_POSY, EDIT_MESSAGE_WIDTH, EDIT_MESSAGE_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, KEYPAD_ASCII_ID_EDIT, PROGRAM_NAME_LENGTH-1);
 
							  TxtErrPrompt = TEXT_CreateEx(TXT_ERR_POSX+100, TXT_ERR_POSY, TXT_ERR_WIDTH, TXT_ERR_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, TEXT_CF_LEFT | TEXT_CF_VCENTER, KEYPAD_ASCII_ID_TEXT, "");
                TEXT_SetTextColor(TxtErrPrompt, GUI_RED);
                WM_HideWindow(TxtErrPrompt);//隐
						}
						
            TEXT_SetFont(TxtErrPrompt, GUI_FONT_BIG);
        }
        else
        {
            //BUTTON_SetFont(hbutton, GUI_FONT_BIG_CH);
            //BUTTON_SetText(hbutton, _aButtonAbs[i].acLabelCh);
            TEXT_SetFont(TxtNamePrompt, GUI_FONT_BIG_CH);
					
					  TxtErrPrompt = TEXT_CreateEx(TXT_ERR_POSX+15, TXT_ERR_POSY, TXT_ERR_WIDTH, TXT_ERR_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, TEXT_CF_LEFT | TEXT_CF_VCENTER, KEYPAD_ASCII_ID_TEXT, "");
            TEXT_SetTextColor(TxtErrPrompt, GUI_RED);
            WM_HideWindow(TxtErrPrompt);//隐
					
					  if(KeyPadAsc.PromptFlag==PROMPT_TITLE)
						{
							  TEXT_SetText(TxtNamePrompt, "Digite o título:");
							  EditNameMessage = EDIT_CreateEx(EDIT_MESSAGE_POSX, EDIT_MESSAGE_POSY, EDIT_MESSAGE_WIDTH, EDIT_MESSAGE_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, KEYPAD_ASCII_ID_EDIT, PROGRAM_NAME_LENGTH-1);
 
						}
						else if(KeyPadAsc.PromptFlag==PROMPT_RESULT_FILE_NAME) 
						{
							TEXT_SetText(TxtNamePrompt, "Ensaio:");
							EditNameMessage = EDIT_CreateEx(EDIT_MESSAGE_POSX+45, EDIT_MESSAGE_POSY, EDIT_MESSAGE_WIDTH, EDIT_MESSAGE_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, KEYPAD_ASCII_ID_EDIT, PROGRAM_NAME_LENGTH-1);
 
						}
						else if(KeyPadAsc.PromptFlag==PROMPT_WELLS_NAME) //lugj 20180927
						{
							  TEXT_SetText(TxtNamePrompt, "Número do poço:");
							  EditNameMessage = EDIT_CreateEx(EDIT_MESSAGE_POSX+5, EDIT_MESSAGE_POSY, EDIT_MESSAGE_WIDTH, EDIT_MESSAGE_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, KEYPAD_ASCII_ID_EDIT, PROMPT_WELL_NAME_LENGTH-1);
					  }
						else// if(KeyPadAsc.PromptFlag==PROMPT_PROTOCOL_FILE_NAME) 
						{
							TEXT_SetText(TxtNamePrompt, "Ensaio:");
							EditNameMessage = EDIT_CreateEx(EDIT_MESSAGE_POSX-15-20, EDIT_MESSAGE_POSY, EDIT_MESSAGE_WIDTH, EDIT_MESSAGE_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, KEYPAD_ASCII_ID_EDIT, PROGRAM_NAME_LENGTH-1);
						}
						
            TEXT_SetFont(TxtErrPrompt, GUI_FONT_BIG_CH);
        }



       // EditNameMessage = EDIT_CreateEx(EDIT_MESSAGE_POSX, EDIT_MESSAGE_POSY, EDIT_MESSAGE_WIDTH, EDIT_MESSAGE_HEIGHT, hWin, WM_CF_SHOW | WM_CF_STAYONTOP, 0, KEYPAD_ASCII_ID_EDIT, PROGRAM_NAME_LENGTH-1);
        //if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            EDIT_SetFont(EditNameMessage, GUI_FONT_BIG);
            EDIT_SetText(EditNameMessage,KeyPadAsc.InputValueStr);
        }
        //else
        //{
        // TEXT_SetFont(TxtNamePrompt, GUI_FONT_BIG_CH);
        // EDIT_SetText(EditNameMessage,KeyPadAsc.InputValueStr);
        //}
        EDIT_EnableBlink(EditNameMessage, 500, 1);
        WM_SetFocus(EditNameMessage);

        //EDIT_SetMaxLen(EditNameMessage, i);

        EDIT_SetCursorAtChar(EditNameMessage, sizeof(KeyPadAsc.InputValueStr)-1);
        EDIT_SetSel(EditNameMessage, 0, sizeof(KeyPadAsc.InputValueStr)-1);
        //WM_DisableWindow(KeyButton[30]);
        //WM_DisableWindow(KeyButton[32]);
        //}
        break;
        //????
    case WM_DELETE:
        //	KeyPadAscFlag = KEYPAD_FREE;    //??,????
        //if (KeyPadFlag == KEYPAD_NAME)
        //{

        WM_DeleteWindow(TxtNamePrompt);
        WM_DeleteWindow(EditNameMessage);

        SetButtonSkin();
        // SetButtonSkin();
        KeyPadAsc.UseFlag=KEYPAD_FREE;
        //}

        break;
        //????
    case WM_PAINT:
        SetAsciiButtonSkin();
		
		
        xSize = WM_GetWindowSizeX(hWin);
        ySize = WM_GetWindowSizeY(hWin);
        //GUI_SetColor(0xaaaaaa);//(0xc9c5c1);


        GUI_SetColor(0x130b09);//(0xc9c5c1);
        GUI_FillRect(0, 0, xSize,ySize);

       /* GUI_SetColor(0x130b09);//(0xc9c5c1);
        GUI_FillRect(5, LINEAR_POSY, xSize - 10,ySize - 1);*/
				GUI_SetColor(0xeed72d);//(0xc9c5c1);
			  GUI_DrawHLine(1, 0, xSize);
				GUI_DrawHLine(2, 0, xSize);
       // GUI_SetColor(COLOR_BORDER);
       // GUI_DrawRect(0, 0, xSize-1, ySize - 1);
       // GUI_DrawRect(0, 1, xSize-1, ySize - 2);
        //GUI_DrawGradientV(1, 1, xSize - 2, ySize - 2, COLOR_KEYPAD0, COLOR_KEYPAD1);
       // GUI_DrawHLine(LINEAR_POSY, 0, 790);
        //GUI_DrawGradientV(1, 1, xSize - 2, ySize - 2, COLOR_KEYPAD0, COLOR_KEYPAD1);
        break;
        //????????
    case WM_NOTIFY_PARENT:
        Id = WM_GetId(pMsg->hWinSrc);
        NCode = pMsg->Data.v;
        if(TouchKey.KeyStatus)
        {
            break;
        }
        switch (NCode)
        {
        case WM_NOTIFICATION_RELEASED:

            if(Id==KEYPAD_ASCII_ID_EDIT)
            {
                KeyPadAsc.SelFlag=0;
            }
            else if( (KeyPadAsc.SelFlag)&&( Id != KEYPAD_ASCII_ID_ESC)&&(Id != KEYPAD_ASCII_ID_ENTER)&&
                     (Id != KEYPAD_ASCII_ID_CAPS) && (Id != KEYPAD_ASCII_ID_ABC) )
            {
                KeyPadAsc.SelFlag=0;
                strcpy(KeyPadAsc.InputValueStr,"");
                EDIT_SetText(EditNameMessage, KeyPadAsc.InputValueStr);
            }
            WM_HideWindow(TxtErrPrompt);//隐
            if (_aButtonData[Id - KEYPAD_ASCII_ID_BUTTON].FunctionKey == 0)
            {
                if ((Id >= KEYPAD_ASCII_ID_BUTTON) && (Id < KEYPAD_ASCII_ID_BUTTON + KEYPAD_ASCII_BUTTON_MAX ))
                {
                    if (KeyPadAsc.ABC123Flag == FLAG_ABC)
                    {
                        if (KeyPadAsc.CapsLockFlag == FLAG_SMALL)
                            s_Key = _aButtonData[Id - KEYPAD_ASCII_ID_BUTTON].acLabelSmall[0];
                        else if (KeyPadAsc.CapsLockFlag == FLAG_BIG)
                            s_Key = _aButtonData[Id - KEYPAD_ASCII_ID_BUTTON].acLabelBig[0];
                    }

                    if (KeyPadAsc.ABC123Flag == FLAG_123)
                    {
                        s_Key = _aButtonData[Id - KEYPAD_ASCII_ID_BUTTON].acLabel123[0];
                        if (Id > (KEYPAD_ASCII_ID_BUTTON + 10) && Id != (KEYPAD_ASCII_ID_BUTTON + 31))
                            break;
                    }
                    s_Textbuf[0] = s_Key;  //????????
                    s_Textbuf[1] = '\0';

                    EDIT_AddKey(hWinFocus, s_Textbuf[0]);
                }
            }
            else
            {   //19=????   27=BackSpace   28=???????    29=Esc?      33=Enter?       30=Space?(???????)
                //???
                if (Id == (KEYPAD_ASCII_ID_DEL))
                {
                    EDIT_AddKey(hWinFocus, GUI_KEY_BACKSPACE);
                    break;
                }
                else if (Id == (KEYPAD_ASCII_ID_ESC))//Esc
                {
                    //memcpy(&BoardInfBack,&BoardInf, sizeof(BOARD_INF) ); //保存板信息
                    TouchKey.KeyStatus=1;
                    KeyPadAsc.ReturnKey=KEYPAD_RETURN_CANCEL;
                    //gSystem.CurrBlock=gSystem.CurrBlockBack;          //备份
                    WM_DeleteWindow(hWin);
                    //KeyPadAsc.UseFlag = KEYPAD_FREE;
                }
                else if (Id == (KEYPAD_ASCII_ID_ENTER))
                {
                    EDIT_GetText(EditNameMessage,KeyPadAsc.InputValueStr,KEYPAD_ASC_CHAR_MAX-1);
                    if(strlen(KeyPadAsc.InputValueStr)<1)	//请输入文件名
                    {
                        TEXT_SetText(TxtErrPrompt, ENTER_FILE_NAME_ERROR[SystemPrameter.SystemLanguage]);
                        WM_ShowWindow(TxtErrPrompt);
                        // strcpy(PromptMenu.InputStr,ENTER_FILE_NAME_ERROR[SystemPrameter.SystemLanguage]);
                        // Prompt_Interface(PROMPT_WARMING);
                        return;
                    }
                    //Demo_1是不能改变的文件
										#ifdef SOFTWARE_DN
										if( (strcmp(KeyPadAsc.InputValueStr,"MET")==0)||(strcmp(KeyPadAsc.InputValueStr,"MOR")==0)||(strcmp(KeyPadAsc.InputValueStr,"KET")==0) ) //文件名相同
										{
												TEXT_SetText(TxtErrPrompt, OVERWRITE_DEMO_FILE_ERROR[SystemPrameter.SystemLanguage]);
                        WM_ShowWindow(TxtErrPrompt);
                        // strcpy(PromptMenu.InputStr,OVERWRITE_DEMO_FILE_ERROR[SystemPrameter.SystemLanguage]);
                        // Prompt_Interface(PROMPT_WARMING);
                        return;
										}
										#else
                    if( (strcmp(KeyPadAsc.InputValueStr,"Demo_1")==0)||(strcmp(KeyPadAsc.InputValueStr,"Demo_2")==0)||(strcmp(KeyPadAsc.InputValueStr,"Demo_3")==0) ) //?????
                    {
                        TEXT_SetText(TxtErrPrompt, OVERWRITE_DEMO_FILE_ERROR[SystemPrameter.SystemLanguage]);
                        WM_ShowWindow(TxtErrPrompt);
                        // strcpy(PromptMenu.InputStr,OVERWRITE_DEMO_FILE_ERROR[SystemPrameter.SystemLanguage]);
                        // Prompt_Interface(PROMPT_WARMING);
                        return;
                    }
										#endif
                    //打印标头错误  lugj190321
                    if( (strlen(KeyPadAsc.InputValueStr)<1)&&(gSystem.SystemInterface==MI_PRINTER_SET) )
                    {
                        TEXT_SetText(TxtErrPrompt, REPORT_TITLE_ERROR[SystemPrameter.SystemLanguage]);
                        WM_ShowWindow(TxtErrPrompt);
                        // strcpy(PromptMenu.InputStr,REPORT_TITLE_ERROR[SystemPrameter.SystemLanguage]);
                        //Prompt_Interface(PROMPT_WARMING);
                        return;
                    }

                    strcpy(CmpFileName,KeyPadAsc.InputValueStr);
                    if(check_same_name(0))
                    {
                        TEXT_SetText(TxtErrPrompt, SAME_FILE_ERROR[SystemPrameter.SystemLanguage]);
                        WM_ShowWindow(TxtErrPrompt);
                        //Prompt_Interface(PROMPT_SAME_NAME);//文件名相同
                        WM_SetFocus(EditNameMessage);
                        return;
                    }

                    TouchKey.KeyStatus=1;
                    KeyPadAsc.ReturnKey=KEYPAD_RETURN_ENTER;
                    // gSystem.CurrBlock=gSystem.CurrBlockBack;          //备份
                    WM_DeleteWindow(hWin);


                }
                else if (Id == (KEYPAD_ASCII_ID_CAPS))//
                {
                    if ((KeyPadAsc.CapsLockFlag == FLAG_SMALL) && (KeyPadAsc.ABC123Flag == FLAG_ABC))
                    {
                        BUTTON_SetBitmapEx(WM_GetDialogItem(hWin, KEYPAD_ASCII_ID_CAPS),BUTTON_BI_UNPRESSED, &bmBmCAP_big,40,8);//FMC170524

                        for (i = 0; i < GUI_COUNTOF(_aButtonData); i++)
                        {
                            BUTTON_SetText(WM_GetDialogItem(hWin, KEYPAD_ASCII_ID_BUTTON + i), _aButtonData[i].acLabelBig);
                        }
                        KeyPadAsc.CapsLockFlag = FLAG_BIG;
                    }
                    //???????,????????
                    else if ((KeyPadAsc.CapsLockFlag == FLAG_BIG) && (KeyPadAsc.ABC123Flag == FLAG_ABC))
                    {
                        BUTTON_SetBitmapEx(WM_GetDialogItem(hWin, KEYPAD_ASCII_ID_CAPS),BUTTON_BI_UNPRESSED, &bmBmCAP,40,8);//FMC170524

                        for (i = 0; i < GUI_COUNTOF(_aButtonData); i++)
                        {
                            BUTTON_SetText(WM_GetDialogItem(hWin, KEYPAD_ASCII_ID_BUTTON + i), _aButtonData[i].acLabelSmall);
                        }
                        KeyPadAsc.CapsLockFlag = FLAG_SMALL;//SMALL
                    }
                }
                else if (Id == (KEYPAD_ASCII_ID_ABC))// 123 ABC
                {
                    if (KeyPadAsc.ABC123Flag == FLAG_ABC)
                    {
                        for (i = 0; i < GUI_COUNTOF(_aButtonData); i++)
                        {
                            BUTTON_SetText(WM_GetDialogItem(hWin, KEYPAD_ASCII_ID_BUTTON + i), _aButtonData[i].acLabel123);
                        }
                        KeyPadAsc.ABC123Flag = FLAG_123;
                        for (i = 10; i < 33; i++)
                        {
                            if(i==27||i==28||i==29)
                                continue;
                            //if(KeyPadFlag == KEYPAD_NAME&&(i==31))//.???
                            //	continue;
                            WM_DisableWindow(WM_GetDialogItem(hWin, KEYPAD_ASCII_ID_BUTTON + i));
                        }
                    }
                    else
                    {
                        for (i = 0; i < 33; i++)
                        {
                            if(i==30||i==31||i==32)
                                continue;
                            WM_EnableWindow(WM_GetDialogItem(hWin, KEYPAD_ASCII_ID_BUTTON + i));
                        }

                        KeyPadAsc.ABC123Flag = FLAG_ABC;
                        if ((KeyPadAsc.CapsLockFlag == FLAG_SMALL) && (KeyPadAsc.ABC123Flag == FLAG_ABC))
                        {
                            for (i = 0; i < GUI_COUNTOF(_aButtonData); i++)
                            {
                                BUTTON_SetText(WM_GetDialogItem(hWin, KEYPAD_ASCII_ID_BUTTON + i), _aButtonData[i].acLabelSmall);
                            }
                        }
                        //???????,????????
                        else if ((KeyPadAsc.CapsLockFlag == FLAG_BIG) && (KeyPadAsc.ABC123Flag == FLAG_ABC))
                        {
                            for (i = 0; i < GUI_COUNTOF(_aButtonData); i++)
                            {
                                BUTTON_SetText(WM_GetDialogItem(hWin, KEYPAD_ASCII_ID_BUTTON + i), _aButtonData[i].acLabelBig);
                            }
                            //CapsLockFlag = FLAG_BIG;
                        }
                    }
                }
            }//if (_aButtonData[Id - KEYPAD_ASCII_ID_BUTTON].FunctionKey == 0) else
            break;
        default://switch (NCode)
        {
            break;
        }
        }//case WM_NOTIFICATION_RELEASED:
    default:
        break;
    }
}
void KeyPadAscii_Go(void)
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
}
void KeyPadAscii_Interface(unsigned char flag,unsigned char prompt_file)
{
    if (KeyPadAsc.UseFlag != KEYPAD_FREE)
    {
        WM_DeleteWindow(KeyPadAsciiWin);
        return;
    }
    DisplayTitleBar();
    GUI_Delay(5);
		
		KeyPadAsc.PromptFlag=prompt_file;
    //	gSystem.CurrBlockBack=gSystem.CurrBlock;          //备份
    KeyPadAsc.SelFlag=1;
    KeyPadAsc.CapsLockFlag = FLAG_SMALL;
    KeyPadAsc.ABC123Flag = FLAG_ABC;
    KeyPadAsc.KeyPadFlag = flag;
    //
    // if (KeyPadAsc.UseFlag == KEYPAD_FREE)
    // {
    KeyPadAsc.UseFlag = KEYPAD_BUSY;  //???????
	TouchKey.KeyStatus=1;
    KeyPadAsciiWin = WM_CreateWindowAsChild(KEYPAD_POSX, KEYPAD_POSY, KEYPAD_WIDTH, KEYPAD_HEIGHT, WM_HBKWIN, WM_CF_SHOW | WM_CF_STAYONTOP | WM_CF_MEMDEV, _cbKeyPadAscii, 0);
    WM_BringToTop(KeyPadAsciiWin);
    //}
    do {
        Usb_check();
        GUI_Delay(5);
        KeyPadAscii_Go();
#ifdef DEBUG_SCREEN
         KeyScan();
      if(Key.KeyValue>0)
	    {
		     KeyProcess();	
		     Key.KeyValue=0; 
	    }
#endif
    } while(KeyPadAsc.UseFlag == KEYPAD_BUSY);
}
