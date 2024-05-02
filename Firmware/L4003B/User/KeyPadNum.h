
//??????????
#define KEYPAD_NUM_CHAR_MAX   15

//??????  ????:KeyPadNumUseFlag
#define KEYPAD_NUM_FREE        0							//??
#define KEYPAD_NUM_BUSY        1							//?

//KeyPadNumReturnValue
#define KEYPAD_NUM_RETURN_ENTER     1                       //??????Enter?
#define KEYPAD_NUM_RETURN_CANCEL    0                       //??????Cancel?


//?????????   ????:KeyPadNumMenuFlag
enum { NUM_MENUFLAG_PASSWORD = 0, NUM_MENUFLAG_2NUM, NUM_MENUFLAG_3NUM,NUM_MENUFLAG_4NUM,NUM_MENU_FLAG,POINT_MENU_FLAG};    //

#ifndef _KEYPAD_NUM_H
#define _KEYPAD_NUM_H

typedef struct
{
    unsigned char MenuFlag;  //??????
    // unsigned short InputValueNum;  //SD?QC
    char InputValueStr[KEYPAD_NUM_CHAR_MAX];   //??????
    unsigned short ReturnKey; //?????
    unsigned char UseFlag;  //???????:1:???,0:???
    unsigned char SelFlag;
} KEYPAD_NUM;

extern KEYPAD_NUM KeyPadNum;


void KeyPadNum_Interface(unsigned char menuflag);
//#else

#endif
