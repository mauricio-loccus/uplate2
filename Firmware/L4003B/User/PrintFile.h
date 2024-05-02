#ifndef __PRINT_FILE_H
#define __PRINT_FILE_H

#define PAPER_MAX_WIDTH      384
#define PAPER_MAX_WIDTH_BYTE (384/8) //48

unsigned char PrintScreenXY(short x1,short y1,short x2,short y2,unsigned short colorM);
void PrintFile(void);
void PrintChar(void);
//void ProtocolQuality_Interface(void);
//void ProtocolQuality_Go(void);
//void ProtocolQuality_Scan(void);
#endif




