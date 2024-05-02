
#ifndef _FILE_MANAGE_H
#define _FILE_MANAGE_H
/*
typedef struct
{
unsigned char MenuFlag;  //¼üÅÌ²Ëµ¥±êÖ¾
// unsigned short InputValueNum;  //SD»òQC
char InputValueStr[KEYPAD_ASC_CHAR_MAX];   //´«ÈëµÄ×Ö·û´®
unsigned short ReturnKey; //¼üÅÌ·µ»ØÖµ
unsigned char UseFlag;  //¼üÅÌÊÇ·ñÔÚÊ¹ÓÃ:1:Ê¹ÓÃÖĞ,0:ÎŞĞ§ÖĞ
}FILE_MANAGE;

extern FILE_MANAGE  FileManage;

*/
#define FIND_OK  0
#define FIND_ERR 1
#define FILE_NAND_BLOCK_END   2000
typedef struct
{
    unsigned char Busy;  //Ã¦±êÖ¾


} TASK_MANAGE;

extern TASK_MANAGE  TaskManage;

unsigned char NandGenerateNewFile(void);  //²úÉúĞÂÎÄ¼ş(Ğ´ÈëNandFlash)
void FindCurrBlockEnd(void);              //²éÕÒÖÕÖ¹¿é
unsigned char FindBlankBlock(void);       //²éÕÒ¿Õ¿é
unsigned char FindCurrBlock(void);        //¸ùÕÒµ±Ç°¿éº
unsigned char NandSaveFile(unsigned char new_addr_flag);//±£´æ1¸öÎÄ¼ş

unsigned char NandOpenOneFile(void);      //´ÓNandFlash´ò¿ªÒ»¸öÎÄ¼ş
void NandReadAllHead(void);               //¶ÁÈ¡ËùÓĞÎÄ¼şÍ·
unsigned char NandDeleteFile(void);       //É¾³ı1¸öÎÄ¼ş

unsigned char RestoreFactory(void);       //»Ö¸´³ö³§ÉèÖÃ
void InitDefaultFile(void);               //³õÊ¹»¯Ä¬ÈÏÎÄ¼ş
void GetDefaultFileName(void);            //»ñÈ¡ÎÄ¼şÃû
unsigned char InitNewParaFile(void);               //³õÊ¹»¯ĞÂ½¨µÄÎÄ¼ş²ÎÊı


#endif

