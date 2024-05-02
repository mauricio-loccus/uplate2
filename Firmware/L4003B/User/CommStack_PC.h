/*
 ******************************************************************************
 *	模块名称 :
 *	文件名称 :
 *	版 本 号 : V1.00A
 *	说    明 :
 *	修改记录 :
 *	日    期 : 2018.1.10
 *  作    者 :
 *  说    明 :
 ******************************************************************************
*/

#ifndef MODULES_COMM_STACK_PC_H_
#define MODULES_COMM_STACK_PC_H_

#include "CommUsart_PC.h"

/******************************************************************************/
// Buffer Series
#define  FIFO_COMM_MAX_PC       (8)

/* FIFO */
typedef struct
{
    /* Data Buffer: Buffer Series Buffer Data Length */
    uint8 Buffer[FIFO_COMM_MAX_PC][COMM_UART_LEN_MAX_PC];

    /* First In Address ,First Out Address */
    uint8 PutPos, GetPos;

    /* Buffer Size, Buffer Free Size, Error Flag Bit */
    uint8 Size, Free, Error;

} COMM_FIFO_PC;

/******************************************************************************/
extern COMM_FIFO_PC  FIFO_RxData_PC;
/******************************************************************************/
void FIFOCommInit_PC(COMM_FIFO_PC  *FIFO);
ErrorStatus FIFO_RxDataPut_PC(uint8 *SourceData,
                              COMM_FIFO_PC *DestinationData);
ErrorStatus FIFO_RxDataGet_PC(COMM_FIFO_PC  *SourceData,
                              uint8 *DestinationData);

#endif
