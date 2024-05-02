#include  "MainTask.h"



/*
unsigned char CheckSumCPUResponse(int nCommand, unsigned char* pCommand)
{
	unsigned char nCheckSum = 0;
	for(int i = 0; i < RESPONSE_COMMAND_LENGTH[nCommand] - 1; i++)
	{
		nCheckSum += pCommand[i];
	}

	return (nCheckSum == pCommand[RESPONSE_COMMAND_LENGTH[nCommand] - 1]);
}*/


void MCU_RepeatSend(void)
{
    unsigned char i;

    UartSendData[0] = UART_SEND_SLA;//0x55
    UartSendData[1] = CPU_COMMAND_REPEAT;
    //校验和
    UartSendData[2]=0;
    for(i = 0; i < 2; i++)
    {
        UartSendData[2] += UartSendData[i];
    }

    for(i=0; i<3; i++)
    {
        USART_SendData(USART1, UartSendData[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }

    run_status.nRunMode = RUN_MODE_INTENSITY_TEST;
    run_status.nTimeOut = INTENSITY_TEST_TIMEOUT;
}


void  MCU_SendSaveOrigin(unsigned int nOrigin) //2015-2-13
{
    unsigned char i;

    UartSendData[0] = UART_SEND_SLA;//0x55
    UartSendData[1] = CPU_COMMAND_SAVE_ORIGIN;
    UartSendData[2] = nOrigin / 65536;
    UartSendData[3] = (nOrigin % 65536) / 256;
    UartSendData[4] = (nOrigin % 65536) % 256;
    UartSendData[5] = 0;
    //校验和
    for(i = 0; i < 5; i++)
    {
        UartSendData[5] += UartSendData[i];
    }

    for(i=0; i<6; i++)
    {
        USART_SendData(USART1, UartSendData[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }

    //2015-2-13
    run_status.nRunMode = RUN_MODE_SAVE_ORIGIN;
    run_status.nTimeOut = SAVE_TIMEOUT;
}


void MCU_SendSelftest(void)
{
    unsigned char i;

    UartSendData[0] = UART_SEND_SLA;//0x55

    UartSendData[1] = CPU_COMMAND_SELFTEST;
    for(i = 0; i < FILTER_MAX; i++)
    {
        UartSendData[2 + 2 * i] =FilterLun.Filter[i]/ 256;
        UartSendData[2 + 2 * i+1] =FilterLun.Filter[i]% 256;
    }
    UartSendData[2 + 2 * FILTER_MAX] = SystemPrameter.DoorOpen;
    UartSendData[3 + 2 * FILTER_MAX] = 0;
    for(i = 0; i < 3 + 2 * FILTER_MAX; i++)
    {
        UartSendData[3 + 2 * FILTER_MAX] += UartSendData[i];
    }
    for(i=0; i<4 + 2 * FILTER_MAX; i++)
    {
        USART_SendData(USART1, UartSendData[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }

    run_status.task_busy=1;    //task_busy==1?,???????
    run_status.nRunMode = RUN_MODE_SELFTEST;
    run_status.nTimeOut = SELFTEST_TIMEOUT;
}


//运行
//void   CAS112_V10Dlg::SendRunProtocol()
void MCU_SendRun(void)
{
    unsigned char i;
    //Sleep(500);

    UartSendData[0] = UART_SEND_SLA;//0x55
    UartSendData[1] = CPU_COMMAND_MEASURE;
    UartSendData[2] = SystemPrameter.DoorOpen;
    run_status.doorState=SystemPrameter.DoorOpen; //lugj180108
    if(BoardInf.KineticPara.Enable)//动力学打开
    {
        if(BoardInf.KineticPara.kinetic_readings_practical <
                BoardInf.KineticPara.Readings-1)
        {
            UartSendData[2] = 0;
            run_status.doorState=CLOSED;    //lugj180108
        }
    }
    UartSendData[3] = BoardInf.Filter1Locate+1; //下发时OFF为0
    UartSendData[4] = BoardInf.Filter2Locate+1;
    UartSendData[5] = 0x80;
    //if(board_inf.curentKinetic[0] == _T('O')) //?????????????
    if(BoardInf.KineticPara.Enable)//动力学打开
    {
        if(BoardInf.KineticPara.kinetic_readings_practical > 0)
        {
            UartSendData[5] = 0;
        }
    }

    //2015-2-2
    //unsigned char cFast = 0;
    if(BoardInf.DetectMode==MODE_FAST)
        //if(board_inf.detectMode[0] == _T('F'))
    {
        //cFast = 1;
        UartSendData[5] +=1;//1表示快速
    }
    //uartTxBuff[5] += cFast;
    //2015-2-2
    UartSendData[6] = 0;
    //校验和
    for(i = 0; i < 6; i++)
    {
        UartSendData[6] += UartSendData[i];
    }

    for(i=0; i<7; i++)
    {
        USART_SendData(USART1, UartSendData[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }



    run_status.nRunMode = RUN_MODE_MEASURE;
    run_status.nTimeOut = MEASURE_TIMEOUT;
    strcpy(ConvertStr,RUNNING_STATUS_MESSAGE[SystemPrameter.SystemLanguage][RUN_MODE_MEASURE]);
    strcat(ConvertStr,STR_CURRENT_CYCLE[SystemPrameter.SystemLanguage]);
    if(BoardInf.KineticPara.Enable)//动力学打开
    {
        BoardInf.KineticPara.kinetic_time_current=BoardInf.KineticPara.TimeInterval;//当前时间间隔
        sprintf(StrTemp,"%d / %d",BoardInf.KineticPara.kinetic_reading_current+1,BoardInf.KineticPara.Readings);
    }
    else
    {
        strcpy(StrTemp,"1 / 1");
    }
    strcat(ConvertStr,StrTemp);

    if(RemoteInfo_PC.RemoteFlag==0)
    {
        strcpy(PromptMenu.InputStr,ConvertStr);

        if( (BoardInf.KineticPara.Enable)&&(BoardInf.KineticPara.kinetic_reading_current>0) )
        {
            RefreshPromptMenu();
        }
        else
        {
            // strcpy(PromptMenu.InputStr,RUNNING_STATUS_MESSAGE[SystemPrameter.SystemLanguage][RUN_MODE_MEASURE]);
            if(PromptMenu.InterfaceStatus==PROMPT_MENU_BUSY)
            {
                RefreshPromptMenu();
            }
            else
            {
                Prompt_Interface(PROMPT_RUN);
            }
        }
    }
}



//更新界停时间
void RefreshPauseTime(void)
{
    if(RemoteInfo_PC.RemoteFlag==0)
		{
				strcpy(ConvertStr,RUNNING_STATUS_PAUSE[SystemPrameter.SystemLanguage]);

				sprintf(StrTemp,"%02d : %02d : %02d",run_status.PauseTime/3600,run_status.PauseTime%3600/60,run_status.PauseTime%60);

				strcat(ConvertStr,StrTemp);


				strcpy(PromptMenu.InputStr,ConvertStr);
				RefreshPromptMenu();
				//Prompt_Interface(PROMPT_RUN);
		}
}


void InitRunPara(void)
{
    if(BoardInf.KineticPara.Enable)//动力学打开
    {
        run_status.bHasData=0;
        BoardInf.KineticPara.kinetic_time_current=BoardInf.KineticPara.TimeInterval;//当前时间间隔
        BoardInf.KineticPara.kinetic_reading_current = 0;
        BoardInf.KineticPara.kinetic_readings_practical = 0;//lugj180103 modify
    }
}


void SendShakeProtocol(void)
{
    unsigned char i;
    run_status.doorState=SystemPrameter.DoorOpen;
    UartSendData[0] = UART_SEND_SLA;    //0x55
    UartSendData[1] = CPU_COMMAND_SHAKE;
    if(BoardInf.ShakeEnable)
    {
        UartSendData[2] = BoardInf.ShakeTime/3600;
        UartSendData[3] = BoardInf.ShakeTime%3600/60;
        UartSendData[4] = BoardInf.ShakeTime%60;
    }
    else
    {
        UartSendData[2] = 0;
        UartSendData[3] = 0;
        UartSendData[4] = 0;
    }

    UartSendData[5] = UartSendData[2];
    UartSendData[6] = UartSendData[3];
    UartSendData[7] = UartSendData[4];

    UartSendData[8] = 0;
    UartSendData[9] = 0;
    UartSendData[10] = 0;

    if(BoardInf.ShakeSpeed==SHAKE_SPEED_SLOW)
        //if(board_inf.shakeMode[0] == 'S')
    {
        UartSendData[11] = 0;
    }
    else if(BoardInf.ShakeSpeed==SHAKE_SPEED_NORMAL)
    {
        UartSendData[11] = 1;
    }
    else
    {
        UartSendData[11] = 2;
    }

    UartSendData[12] = 0;

    for(i = 0; i < 12; i++)
    {
        UartSendData[12] += UartSendData[i];
    }
    for(i=0; i<13; i++)
    {
        USART_SendData(USART1, UartSendData[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }


    run_status.nRunMode = RUN_MODE_SHAKE;
    run_status.nTimeOut = SHAKE_TIMEOUT + BoardInf.ShakeTime * 2;

		if(RemoteInfo_PC.RemoteFlag==0)//modify lugj20181017
    {
        strcpy(PromptMenu.InputStr,RUNNING_STATUS_MESSAGE[SystemPrameter.SystemLanguage][RUN_MODE_SHAKE]);
        //Prompt_Interface(PROMPT_RUN);
        if(PromptMenu.InterfaceStatus==PROMPT_MENU_BUSY)
        {
            RefreshPromptMenu();
        }
        else
        {
            Prompt_Interface(PROMPT_RUN);
        }
    }

}



//运行或停止 (1表示运行0表示停止)
void MCU_StartStop(unsigned char state)
{
    unsigned char i;

    if (state==STARTED)
    {
        if(run_status.nRunMode == RUN_MODE_IDLE)
        {
            InitRunPara();
            if(BoardInf.ShakeEnable)
            {
                SendShakeProtocol();
            }
            else
            {
                MCU_SendRun();
            }
        }
    }
    else
    {
        run_status.pause_start_flag=0;//停止后清除暂停标志

        UartSendData[0] = UART_SEND_SLA;     //0x55
        UartSendData[1]=CPU_COMMAND_STOP;    //0x04停止
        UartSendData[2]=0x01;
        UartSendData[3]=0;
        for(i = 0; i < 3; i++)
        {
            UartSendData[3] += UartSendData[i];
        }

        for(i=0; i<4; i++)
        {
            USART_SendData(USART1, UartSendData[i]);
            while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
        }



        //uartTxBuff[3]=0xaf;
        //doorState = OPENED;
        run_status.doorState=OPENED;
        //m_Port_MCU->WritePort(uartTxBuff,4);
//#ifdef NEW_PROTOCOL
        run_status.nRunMode = RUN_MODE_STOP;
        run_status.nTimeOut = PLATE_TIMEOUT;
        if(KeyPadAsc.ID>0)
        {
            KeyPadAsc.ID--;
        }

//#endif
    }
    //Sleep(500);//2015-10-26

}


void openClosedoor(unsigned char state)
{
    unsigned char i;
    if (state==CLOSED)
    {
        UartSendData[0]=UART_SEND_SLA;//0x55
        UartSendData[1]=CPU_COMMAND_PLATE_IN;//0x05
        UartSendData[2]=0x01;
    }
    else
    {

        UartSendData[0]=UART_SEND_SLA;//0x55;
        UartSendData[1]=CPU_COMMAND_PLATE_OUT;//0x04
        UartSendData[2]=0x01;

    }
    UartSendData[3]=0;
    for(i = 0; i < 3; i++)
    {
        UartSendData[3] += UartSendData[i];
    }

    for(i=0; i<4; i++)
    {
        USART_SendData(USART1, UartSendData[i]);
        while (USART_GetFlagStatus(USART1, USART_FLAG_TC) == RESET);
    }

    run_status.task_busy=1;  //板进/出执行中
    if(state == CLOSED)
    {
        run_status.nRunMode = RUN_MODE_PLATE_IN;
        run_status.nTimeOut = PLATE_TIMEOUT;
    }
    else
    {
        run_status.nRunMode = RUN_MODE_PLATE_OUT;
        run_status.nTimeOut = PLATE_TIMEOUT;
    }

}


void UartExceedCheck(void)
{
    if(	(run_status.nRunMode > RUN_MODE_IDLE)&&(run_status.pause_start_flag==0) )//RUN_MODE_PLATE_IN;
    {
        if( (run_status.nTimeOut>0)&&(run_status.bHasData==0) )//= PLATE_TIMEOUT;
        {
            run_status.nTimeOut--;
        }
        //else
        //{
        //	 gSystem.SystemErrCode=
        // }


        if(run_status.nRunMode == RUN_MODE_MEASURE)
        {
            if(BoardInf.KineticPara.Enable)//???
            {
                if(BoardInf.KineticPara.kinetic_time_current>0)
                {
                    BoardInf.KineticPara.kinetic_time_current--;
                }
                else if(run_status.bHasData)
                {
                    run_status.bHasData = 0;
                    if( (BoardInf.ShakeEnable)&&(BoardInf.ShakeMode==SHAKE_EACH) ) //
                    {
                        SendShakeProtocol();
                    }
                    else
                    {
                        MCU_SendRun();
                    }
                }
            }
        }

        //超时故障报警
        if(run_status.nTimeOut <= 0)
        {
            run_status.nTimeOut = 0;
            run_status.task_busy = 0;  //2015-2-13
            if( ((PromptMenu.InterfaceStatus==PROMPT_MENU_FREE) && run_status.nRunMode != RUN_MODE_SAVE_ORIGIN
                    && run_status.nRunMode != RUN_MODE_CALIBRATE_ORIGIN
                    && run_status.nRunMode != RUN_MODE_FILTER) || (run_status.nRunMode == RUN_MODE_SELFTEST) )
            {
                run_status.nRunMode = RUN_MODE_IDLE;
                run_status.task_busy = 0;
                //bSerialError = true; //2015-2-13
                //gSystem.SystemErrCode=ERRCODE_UART;

                run_status.bHasData= run_status.bHasDataBack;
                memcpy( &BoardInf, &BoardInfBack, sizeof(BOARD_INF));
                DeletePromptMenu(0);
                strcpy(PromptMenu.InputStr,RUN_COMMAND_RESPONSE_ERROR[SystemPrameter.SystemLanguage]);
                Prompt_Interface(PROMPT_UART_ERR);
                StartUpPra.StartFlag=0;//超时退出
            }
            run_status.nRunMode = RUN_MODE_IDLE;//2015-2-13
        }
    }
}





