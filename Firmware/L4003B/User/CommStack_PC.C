/**********************************************************************************
1.文件功能描述
本程序实现串口数据收发,端口:(引脚:PA9 PA10)
2.具体函数
  2.1私有函数


  2.2公有函数


3.IO说明
  1)
  2)
4. 创建日期-版本-姓名
   2017/01/23-V3.00-陆国金 void CAS112_V10Dlg::comReceiveproFromPc(void)
*************************************************************************************/



#include "includes.h"
#include "MainTask.h"
//#include "CommStack_PC.h"
/******************************************************************************/
/* Receive/Send Comm_USART Data FIFO */
COMM_FIFO_PC  FIFO_RxData_PC   __attribute__((at(SDRAM_PC_FIFO_BUF)));

/******************************************************************************
 *	函 数 名: Stack_FIFO_Comm_Init
 *	功能说明: 释放队列
 *	形    参:
 *	返 回 值:
*******************************************************************************/
void FIFOCommInit_PC(COMM_FIFO_PC  *FIFO)
{
    uint8 i;

    FIFO->Error = RESET;
    FIFO->Free = FIFO_COMM_MAX_PC;//COMM_UART_LEN_MAX_PC;  mogidy lugj 20190318
    FIFO->GetPos = RESET;
    FIFO->PutPos = RESET;
    FIFO->Size = FIFO_COMM_MAX_PC;//COMM_UART_LEN_MAX_PC;  mogidy lugj 20190318

    /* FIFO->Buffer Clear */
    for(i = 0; i < FIFO_COMM_MAX_PC; i++)
    {
        memset(&(FIFO->Buffer[i]), 0, COMM_UART_LEN_MAX_PC);
    }
}

/******************************************************************************
 *	函 数 名: Stack_FIFO_Comm_RxDataPut
 *	功能说明: 数据进入队列
 *	形    参:
 *	返 回 值:
*******************************************************************************/
ErrorStatus FIFO_RxDataPut_PC(uint8 *SourceData,
                              COMM_FIFO_PC *DestinationData)
{
    // Copy  into the FIFO
    memcpy(&(DestinationData->Buffer[DestinationData->PutPos]),SourceData, COMM_UART_LEN_MAX_PC);

    // First In address increasing, Free Buffer reducing
    DestinationData->PutPos++;
    DestinationData->Free--;

    // Pointer address increased to the maximum, restarting
    if(DestinationData->PutPos >= DestinationData->Size)
    {
        DestinationData->PutPos = RESET;
    }

    // Data into the stack successfully
    return SUCCESS;
}

/******************************************************************************
 *	函 数 名: Stack_FIFO_Comm_RxDataGet
 *	功能说明: 数据出列
 *	形    参:
 *	返 回 值:
*******************************************************************************/
ErrorStatus FIFO_RxDataGet_PC(COMM_FIFO_PC  *SourceData,
                              uint8 *DestinationData)
{
    uint8* pData;
    uint8* pDest;
    uint8 i;

    /* No can read data */
    if(SourceData->Free == SourceData->Size)
    {
        return ERROR;
    }
    // Copy  into the FIFO
    memcpy(DestinationData,&(SourceData->Buffer[SourceData->GetPos]), COMM_UART_LEN_MAX_PC);

    /* First In address increasing, Free Buffer increasing */
    SourceData->GetPos++;
    SourceData->Free++;

    /* Pointer address increased to the maximum, restarting */
    if(SourceData->GetPos >= SourceData->Size)
    {
        SourceData->GetPos = RESET;
    }

    /* Get data successfully  */
    return SUCCESS;
}
