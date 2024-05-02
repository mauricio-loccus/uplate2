/**********************************************************************************
1.ÎÄ¼þ¹¦ÄÜÃèÊö
±¾³ÌÐòÊµÏÖ´®¿ÚÊý¾ÝÊÕ·¢,¶Ë¿Ú:(Òý½Å:PA9 PA10)
2.¾ßÌåº¯Êý
  2.1Ë½ÓÐº¯Êý


  2.2¹«ÓÐº¯Êý


3.IOËµÃ÷
  1)
  2)
4. ´´½¨ÈÕÆÚ-°æ±¾-ÐÕÃû
   2017/01/23-V3.00-Â½¹ú½ð void CAS112_V10Dlg::comReceiveproFromPc(void)
*************************************************************************************/
#include  "includes.h"
#include  "MainTask.h"
//#include "CommProcess_PC.h"

//#include "string.h"


/*************************************************************************************/
#define UART_RE_SEND_TIME_MAX    3 //´®¿ÚÖØ·¢Ê±¼ä
#define UART_RE_SEND_COUNT_MAX   2 //´®¿ÚÖØ·¢´ÎÊý

/*************************************************************************************/
UART_INFO_PC UartInfo_PC   __attribute__((at(SDRAM_PC_COMM_BUF)));
REMOTE_INFO_PC RemoteInfo_PC;  //
COMM_STATUS_PC CommStatus_PC;  //Í¨¶Á×´Ì¬






//-----------------------------------------------------------------//
//	¹¦    ÄÜ:´®¿ÚÖØ·¢PC³õÊ¹»¯
//	Èë¿Ú²ÎÊý:cmd·¢ËÍµÄÃüÁî
//	³ö¿Ú²ÎÊý:
//	È«¾Ö±äÁ¿:
//	±¸    ×¢:
//-----------------------------------------------------------------//
void UartCommInit(void)
{
    CommStatus_PC.CurrentCommand=0;
    CommStatus_PC.SentFlag=0;
    CommStatus_PC.RepeatSendCount=0;
    CommStatus_PC.Timeout=0;

}


//-----------------------------------------------------------------//
//	¹¦    ÄÜ:´®¿ÚÖØ·¢PC³õÊ¹»¯
//	Èë¿Ú²ÎÊý:cmd·¢ËÍµÄÃüÁî
//	³ö¿Ú²ÎÊý:
//	È«¾Ö±äÁ¿:
//	±¸    ×¢:
//-----------------------------------------------------------------//
void UartResendPrepared(unsigned short cmd)
{
    CommStatus_PC.CurrentCommand=cmd;
    CommStatus_PC.SentFlag=1;
    //CommStatus_PC.RepeatSendCount=0;
    CommStatus_PC.Timeout=0;

    //run_status.nRunMode = RUN_MODE_INTENSITY_TEST;
    //run_status.nTimeOut = INTENSITY_TEST_TIMEOUT;
}


//-----------------------------------------------------------------//
//	¹¦    ÄÜ:¼ÆËã½ÓÊÕÊý¾ÝµÄÐ£ÑéºÍ
//	Èë¿Ú²ÎÊý:*pCommand½ÓÊÕµÄÊý¾Ý,ptr½ÓÊÕµÄÊý¾Ý³¤¶È-Ð£Ñé³¤¶È
//	³ö¿Ú²ÎÊý:Ð£ÑéºÍ
//	È«¾Ö±äÁ¿:
//	±¸    ×¢:
//-----------------------------------------------------------------//
uint16 GetRxCheckSum_PC(unsigned char *pCommand, unsigned short ptr)
{
    unsigned short nSum = 0;
    unsigned short i;

    for (i = 0; i < ptr; i++)
    {
        nSum += (unsigned short)pCommand[i];
    }
		pCommand[i++]=(nSum>>8)&0xff;
		pCommand[i++]=nSum&0xff;
    return(nSum);
}

//-----------------------------------------------------------------//
//	¹¦    ÄÜ:¼ÆËã·¢ËÍÊý¾ÝµÄÐ£ÑéºÍ
//	Èë¿Ú²ÎÊý:*pCommand·¢ËÍµÄÊý¾Ý,ptr·¢ËÍµÄÊý¾Ý³¤¶È-Ð£Ñé³¤¶È
//	³ö¿Ú²ÎÊý:
//	È«¾Ö±äÁ¿:
//	±¸    ×¢:
//-----------------------------------------------------------------//
void GetTxCheckSum_PC(unsigned char *pCommand, unsigned short ptr)
{
    unsigned short nSum = 0;
    unsigned short i;

    for (i = 0; i < ptr; i++)
    {
        nSum += (unsigned short)pCommand[i];
    }
    pCommand[ptr++] = nSum>>8;
    pCommand[ptr++] = nSum&0xff;
}


/******************************************************************************
 *	º¯ Êý Ãû: ³õÊ¼»¯µ÷ÊÔ´®¿Ú
 *	¹¦ÄÜËµÃ÷:
 *	ÐÎ    ²Î:
 *	·µ »Ø Öµ:
*******************************************************************************/
void CommInit_PC(void)
{
    /*Initialize Comm-USART4*/
    CommUsartInit_PC();
    UartCommInit();
    /* Initialize FIFO : Send and receive */
    FIFOCommInit_PC(&FIFO_RxData_PC);
}


//-----------------------------------------------------------------//
//	¹¦ÄÜ:´®¿ÚÖ÷¶¯·¢ËÍÃüÁî,ÒªÇó¶Ô·½ÓÐÓ¦´ð
//	Èë¿Ú²ÎÊý: cmdÃüÁî×Ö,*dat´ÓÊý¾Ý¶Î¿ªÊ¼
//	³ö¿Ú²ÎÊý:
//  ±¸×¢:
//-----------------------------------------------------------------//
void UartCmdSend_PC(uint16 cmd)
{
    unsigned short ptr=0;
    unsigned char i,j;
    unsigned int val;
    unsigned char *pCommand;
    pCommand=&UartInfo_PC.SendBuffer[0];

     //ptr=AddCommandHead_PC(cmd,pCommand,COMM_DATA_LEN_POS_PC);
    switch(cmd)
    {
    case COMMAND_UNCONNECT_PC:        //¶Ï¿ª
    {
        ptr=AddCommandHead_PC(cmd,pCommand,2);
        //ÎÞÊý¾Ý
        break;
    }
    case COMMAND_MEASURE_END_PC:      //Îü¹â¶È¼ì²â½áÊø
    {
        //µ±Ç°°åºÅ 1~
			  if(BoardInf.Filter2Locate<=FILTER_NO)
				{
			     ptr=AddCommandHead_PC(cmd,pCommand,14+96*4);
				}
				else
				{
					ptr=AddCommandHead_PC(cmd,pCommand,14+96*8);
				}
        val=RemoteInfo_PC.PlateCurrent+1;
        pCommand[ptr++] = (val>>24)&0xff;  //
        pCommand[ptr++] = (val>>16)&0xff;
        pCommand[ptr++] = (val>>8)&0xff;
        pCommand[ptr++] =  val&0xff;

        //µ±Ç°Ñ­»· 1~
        if(BoardInf.KineticPara.Enable)
        {
            val=BoardInf.KineticPara.kinetic_readings_practical;//BoardInf.KineticPara.kinetic_readings_practical+1
        }
        else
        {
            val=BoardInf.KineticPara.kinetic_readings_practical;
        }
        pCommand[ptr++] = (val>>24)&0xff;//Ñ­»·´ÎÊý
        pCommand[ptr++] = (val>>16)&0xff;
        pCommand[ptr++] = (val>>8)&0xff;
        pCommand[ptr++] =  val&0xff;

        //ÂË¹âÆ¬Êý
        if(BoardInf.Filter2Locate>FILTER_NO)val=2;
        else val=1;
        pCommand[ptr++] = (val>>24)&0xff;  //
        pCommand[ptr++] = (val>>16)&0xff;
        pCommand[ptr++] = (val>>8)&0xff;
        pCommand[ptr++] =  val&0xff;


        //96¿×°åµÄÊý¾Ý
        for(j = 0; j < 2; j++)
        {
            if( (BoardInf.Filter2Locate<=FILTER_NO) && (j > 0) )
            {
                break;
            }

            for(i = 0; i < TUBE_MAX; i++)
            {
                if(BoardInf.KineticPara.Enable)
                {
									 if(BoardInf.KineticPara.kinetic_readings_practical>0)
									 {
                      val=BoardInf.KineticPara.kinetic_readings_practical-1;
									 }
                }
                else
                {
                    val=0;
                }
                FloatValue.f_val=dABSInit[val][j][i];//´ýÈ·ÈÏ
                //	FloatValue.f_val=1;
                pCommand[ptr++]=FloatValue.c_val[3];
                pCommand[ptr++]=FloatValue.c_val[2];
                pCommand[ptr++]=FloatValue.c_val[1];
                pCommand[ptr++]=FloatValue.c_val[0];
            }
        }

        //Èç¹ûÊÇÒ»¸öÂË¹âÆ¬,·¢96*4×Ö½Ú,Èç¹ûÊÇ2¸öÂË¹âÆ¬,Ôò·¢96*2*4¸ö×Ö½Ú
        break;
    }
    case COMMAND_CURR_BOARD_END_PC:   //µ±Ç°°å½áÊø
    {
			   ptr=AddCommandHead_PC(cmd,pCommand,6);
        val=RemoteInfo_PC.PlateCurrent+1;
        pCommand[ptr++] = (val>>24)&0xff;  //
        pCommand[ptr++] = (val>>16)&0xff;
        pCommand[ptr++] = (val>>8)&0xff;
        pCommand[ptr++] =  val&0xff;
        break;
    }
    case COMMAND_ERRCODE_PC:         //¹ÊÕÏ´úÂë
    {
			   ptr=AddCommandHead_PC(cmd,pCommand,6);
        pCommand[ptr++] = (gSystem.SystemErrCode>>24)&0xff;
        pCommand[ptr++] = (gSystem.SystemErrCode>>16)&0xff;
        pCommand[ptr++] = (gSystem.SystemErrCode>>8)&0xff;
        pCommand[ptr++] = gSystem.SystemErrCode&0xff;
        break;
    }
    default:
        return;
    }
    GetTxCheckSum_PC(pCommand, ptr);
    ptr+=COMM_CRC_LEN_PC;

		if(cmd!=COMMAND_UNCONNECT_PC)
		{
			 CommStatus_PC.CurrentCommand=0;
       CommStatus_PC.SentFlag=0;
			 if(CommStatus_PC.RepeatSendCount<=UART_RE_SEND_COUNT_MAX)
			 {
          UartResendPrepared(cmd);//ÏòPC»ú·¢ËÍÊý¾Ý
			 }
			 //else
			 //{
			//	  CommStatus_PC.RepeatSendCount=0;
			// }
		}

    //·¢ËÍÊý¾Ý
    CommSendCommand_PC(pCommand,ptr);
}




unsigned short AddCommandHead_PC( unsigned short nCommandSecond, unsigned char  *pCommand,unsigned short nLength)
{
    unsigned short ptr = 0;
    //±ê¼ÇÎ»(Ö¡Í· 4×Ö½Ú)
    memcpy(pCommand, CONST_COMMAND_HEAD, COMM_SLA_LEN_PC);
    ptr += COMM_SLA_LEN_PC;

    //Çø·Ö×Ö¶Î(ÒÇÆ÷ºÅ 8×Ö½Ú)
    pCommand[ptr++] = 0;
    pCommand[ptr++] = 0;
    pCommand[ptr++] = 0;
    pCommand[ptr++] = 0;
    pCommand[ptr++] = 0;
    pCommand[ptr++] = 0;
    pCommand[ptr++] = 0;
    pCommand[ptr++] = 0;

    //Ö÷ÃüÁî (2×Ö½Ú)
    pCommand[ptr++] = CONST_MAIN_COMMAND[0];
    pCommand[ptr++] = CONST_MAIN_COMMAND[1];

    //×ÓÃüÁî (2×Ö½Ú)
    pCommand[ptr++] = nCommandSecond>>8;
    pCommand[ptr++] = nCommandSecond&0xff;

    //Êý¾Ý³¤¶È (4×Ö½Ú)
    pCommand[ptr++] = 0;
    pCommand[ptr++] = 0;
    pCommand[ptr++] = nLength>>8;
    pCommand[ptr++] = nLength&0xff;
    return ptr;
}
//Á¬½ÓÏìÓ¦ÃüÁî
void PrepareConnectResponseCommand(uint16 cmd,unsigned char *pCommand)
{
    unsigned short ptr=0;
    unsigned char i;
    #ifdef SOFTWARE_DN
    ptr=AddCommandHead_PC(cmd,pCommand,42+8);//COMM_DATA_LEN_POS_PC
	  #else
	  ptr=AddCommandHead_PC(cmd,pCommand,42+15);//COMM_DATA_LEN_POS_PC // esse aqui
	  #endif
    //Á¬½Ó±êÖ¾
    pCommand[ptr++]=0;
    pCommand[ptr++]=0;
    pCommand[ptr++]=0;
    if(run_status.task_busy) //ÏÂÎ»»úÃ¦
    {
        pCommand[ptr++]=1;   //1±íÊ¾Á¬½ÓÊ§°Ü
    }
    else
    {
        pCommand[ptr++]=0;   //Á¬½Ó³É¹¦
    }

    //Ê§°ÜÔ­Òò
    pCommand[ptr++]=0;
    pCommand[ptr++]=0;
    pCommand[ptr++]=0;
    pCommand[ptr++]=MACHINE_BUSY;

    //ÒÇÆ÷ÐòÁÐºÅ
		#ifdef SOFTWARE_DN
		for(i=0; i<8; i++)
    {
        pCommand[ptr++]='1'+i;
    }
		#else
		// esse aqui
		for(i=0; i<PN_LENGTH; i++)
    {
        pCommand[ptr++]=SystemPrameter.PN[i];//'1'+i;
    }
		#endif


    //ÂË¹âÆ¬²ÎÊý
    for(i = 0; i < FILTER_MAX; i++)
    {
        pCommand[ptr++]=0;
        pCommand[ptr++]=0;
        pCommand[ptr++]=FilterLun.Filter[i]>>8;
        pCommand[ptr++]=FilterLun.Filter[i]&0xff;
    }


    GetRxCheckSum_PC(pCommand, ptr);
    ptr+=COMM_CRC_LEN_PC;
    //·¢ËÍÊý¾Ý
    CommSendCommand_PC(pCommand,ptr);
}

//¶Ï¿ªÏìÓ¦ÃüÁî-
void PrepareResponseCommand(uint16 cmd,unsigned char *pCommand,unsigned char okflag)
{
    unsigned short ptr=0,i;



    //Ê§°ÜÔ­Òò
    if( (cmd==COMMAND_UNCONNECT_ACK_PC)||(cmd==COMMAND_RUN_ACK_PC)||(cmd==COMMAND_PLATEIN_ACK_PC)
            ||(cmd==COMMAND_PLATEOUT_ACK_PC) ||(cmd==COMMAND_NEXT_PLATE_ACK_PC)||(cmd==COMMAND_MEASURE_PARA_ACK_PC)
            ||(cmd==COMMAND_KINETIC_ACK_PC)  ||(cmd==COMMAND_KINETIC_ACK_PC)||(cmd==COMMAND_SEND_PN_ACK_PC)  )
    {
			  ptr=AddCommandHead_PC(cmd,pCommand,6);//COMM_DATA_LEN_POS_PC
        pCommand[ptr++]=0;
        pCommand[ptr++]=0;
        pCommand[ptr++]=0;
        pCommand[ptr++]=okflag;//³É¹¦
    }
    else //if(cmd==COMMAND_STOP_ACK_PC)
    {
			  ptr=AddCommandHead_PC(cmd,pCommand,2);//COMM_DATA_LEN_POS_PC
        //ÎÞÊý¾Ý¶Î
    }
    /*else if(cmd==COMMAND_SEND_PN_ACK_PC)
		{
			  for(i=0;i<PN_LENGTH;i++)
			  {
					pCommand[ptr++]=SystemPrameter.PN[i];
				}
		}*/
    GetRxCheckSum_PC(pCommand, ptr);
	  ptr+=COMM_CRC_LEN_PC;
    //ptr+=COMM_CRC_LEN_PC;
    //·¢ËÍÊý¾Ý
    CommSendCommand_PC(pCommand,ptr);
}




//-----------------------------------------------------------------//
//	¹¦ÄÜ:´®¿ÚÊÕµ½À´×ÔPCÃüÁîºó½øÐÐ³õÊ¹»¯
//	Èë¿Ú²ÎÊý: cmdÃüÁî×Ö,*dat´ÓÊý¾Ý¶Î¿ªÊ¼
//	³ö¿Ú²ÎÊý:
//  ±¸×¢:
//-----------------------------------------------------------------//
void UartCmdProcess_PC(unsigned short cmd,uint8 *dat)
{
    switch(cmd)
    {
    case COMMAND_CONNECT_ACK_PC:  //Á¬½Ó
    {
			 // if(run_status.nRunMode != RUN_MODE_SELFTEST)
			if(RemoteInfo_PC.RemoteFlag==0)		//¶Ï¿ª×´Ì¬ÏÂ
		 {
				  if( (run_status.task_busy==0)&&(run_status.nRunMode != RUN_MODE_SELFTEST)
					 &&( (gSystem.SystemInterface == MI_PROTOCOL)||(gSystem.SystemInterface == MI_REPORT) ))// || (gSystem.SystemInterface == MI_ABS_CALIBRATION))

				{
							//run_status.nRunMode = RUN_MODE_IDLE;RemoteInfo_PC.bRemote=1;
					    UartCommInit();
							PrepareConnectResponseCommand(cmd,&UartInfo_PC.SendBuffer[0]);

							BackupMachineStatus();    //±¸·ÝÒÇÆ÷Êý¾Ý
							Remote_Interface();		    //ÏÔÊ¾Á¬½ÓPC½çÃæ
						 //Modify lugj20180803
							BoardInf.PauseTime=0;
					   // GUI_Delay(50);

				}
			}
        break;
    }
    case COMMAND_UNCONNECT_ACK_PC://¶Ï¿ª
    {
			if(RemoteInfo_PC.RemoteFlag)		//Á¬½Ó×´Ì¬ÏÂ
			{
					if(run_status.nRunMode != RUN_MODE_SELFTEST)
					{
							//run_status.nRunMode = RUN_MODE_IDLE;RemoteInfo_PC.bRemote=0;
							//PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_OK);
							//ÊÕµ½PC·¢¹ýÀ´µÄ¶Ï¿ªÃüÁîºó»Ö¸´½çÃæÈí¼þµÄ×´Ì¬
							RestoreMachineStatus();    //»Ö¸´ÒÇÆ÷Êý¾Ý
							run_status.nRunMode = RUN_MODE_IDLE;
						 // if ( RemoteInfo_PC.RunningFlag==RUNNING_FLAG_RUN) //Í£Ö¹ÏÂÎ»»ú
								if(run_status.task_busy)
							{
									run_status.task_busy=0;
									//RemoteInfo_PC.RunningFlag=0;
									MCU_StartStop(0);
							}



							run_status.task_busy=0;
							RemoteInfo_PC.RemoteFlag=0;
							DeletePCMenu();
							gSystem.MenuRefreshFlag=1;
							gSystem.TitleButtonEnable=1;
							// GUI_Delay(50);
					 }
			 }
        break;
    }
    case COMMAND_RUN_ACK_PC:      //ÔËÐÐ
    {
        if(RemoteInfo_PC.RemoteFlag)
        {
            run_status.doorState = dat[3];//ÔËÐÐ½áÊø°å³ö±êÖ¾.intÀàÐÍ,Ö»È¡µÚ4Î»
            if(run_status.doorState>1)run_status.doorState=1;
            PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_OK);
            MCU_StartStop(1);          //????
            run_status.task_busy=1;    //task_busy==1?,???????
        }
        else
        {
            //PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_ERR);
        }
        break;
    }
    case COMMAND_STOP_ACK_PC:     //Í£Ö¹
    {
        if(RemoteInfo_PC.RemoteFlag)
        {
            PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_OK);

            if ( (run_status.task_busy==1 )&&(run_status.nRunMode != RUN_MODE_SELFTEST) )
            {
                run_status.nRunMode = RUN_MODE_IDLE;
                MCU_StartStop(0);
                run_status.task_busy=0;

            }
        }
        else
        {
            //PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_ERR);
        }
        break;
    }
    case COMMAND_PLATEIN_ACK_PC:  //°å½ø
    {
        //run_status.task_busy=0;
        //run_status.nRunMode = RUN_MODE_IDLE;
        // PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0]);

        if( ((run_status.task_busy==0)&&(run_status.nRunMode != RUN_MODE_SELFTEST))&&(RemoteInfo_PC.RemoteFlag) )
        {
            //run_status.doorState=0; //°å½ø
            if(run_status.doorState)run_status.doorState=0;
            else run_status.doorState=1;
            openClosedoor(run_status.doorState);//Ö´ÐÐ°å½øÃüÁî
            PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_OK);
        }
        else
        {
           // PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_ERR);
        }

        break;
    }


    case COMMAND_PLATEOUT_ACK_PC:  //°å³ö
    {
        //run_status.task_busy=0;
        //run_status.nRunMode = RUN_MODE_IDLE;
        if( ((run_status.task_busy==0)&&(run_status.nRunMode != RUN_MODE_SELFTEST) )&&(RemoteInfo_PC.RemoteFlag) )
        {
            //run_status.doorState=1;  //°å³ö
            if(run_status.doorState)run_status.doorState=0;
            else run_status.doorState=1;
            openClosedoor(run_status.doorState);//Ö´ÐÐ°å½øÃüÁî
            PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_OK);
        }
        else
        {
           // PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_ERR);
        }
        break;
    }
    case COMMAND_NEXT_PLATE_ACK_PC://ÏÂÒ»°åÒÑ×¼±¸ºÃ
    {
        //Remote_PC.PlateNumber= UartRevDataPC[3];//ÔËÐÐ½áÊø°å³ö±êÖ¾.intÀàÐÍ,Ö»È¡µÚ4Î»
        if( (RemoteInfo_PC.PlateCurrent+1<dat[3])&&(RemoteInfo_PC.RemoteFlag) )
        {
            RemoteInfo_PC.PlateCurrent=dat[3];
            PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_OK);
            MCU_StartStop(1);          //
            run_status.task_busy=1;    //task_busy==1
        }
        else
        {
           // PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_ERR);
        }
        break;
    }
    case COMMAND_MEASURE_PARA_ACK_PC: //²âÁ¿²½Öè²ÎÊý´«µÝ
    {
        if(RemoteInfo_PC.RemoteFlag)
        {
            //detect_inf.doorOpen= UartRevDataPC[3];	 //°åÊý
            RemoteInfo_PC.PlateCurrent=0;
            RemoteInfo_PC.PlateTotal=dat[3];
            if(RemoteInfo_PC.PlateTotal>100)RemoteInfo_PC.PlateTotal=100;//
            BoardInf.Filter1Locate=(signed char)dat[7]-1;  //Ö÷²¨³¤Î»ÖÃ
            if(BoardInf.Filter1Locate<FILTER_NO)BoardInf.Filter1Locate=FILTER_NO;
            else if(BoardInf.Filter1Locate>=FILTER_MAX)BoardInf.Filter1Locate=FILTER_MAX-1;
            BoardInf.Filter2Locate=(signed char)dat[11]-1; //·ø²¨³¤Î»ÖÃ
            if(BoardInf.Filter2Locate<FILTER_NO)BoardInf.Filter2Locate=FILTER_NO;
            else if(BoardInf.Filter2Locate>=FILTER_MAX)BoardInf.Filter2Locate=FILTER_MAX-1;
            BoardInf.DetectMode=dat[15];   //²âÁ¿Ä£Ê½
            if(BoardInf.DetectMode>1)BoardInf.DetectMode=1;
            BoardInf.ShakeEnable=dat[19]; //Õñ¶¯¿ªÆô
            BoardInf.ShakeSpeed=dat[23];  //Õñ¶¯ËÙ¶È
            if(BoardInf.ShakeSpeed<1)BoardInf.ShakeSpeed=1;
            else if(BoardInf.ShakeSpeed>3)BoardInf.ShakeSpeed=3;
            BoardInf.ShakeSpeed=BoardInf.ShakeSpeed-1;//SHAKE_SPEED_SLOW
            BoardInf.ShakeTime=( ((unsigned long)dat[24]<<24)|((unsigned long)dat[25]<<16)
                                 |((unsigned long)dat[26]<<8)|(unsigned long)dat[27]); //Õñ¶¯Ê±¼ä

						if( (BoardInf.ShakeTime<SHAKE_TIME_MIN)|| (BoardInf.ShakeTime>SHAKE_TIME_MAX) )
						{
								BoardInf.ShakeTime=SHAKE_TIME_MIN;
						}

						#ifdef SOFTWARE_DN
						    BoardInf.ShakeMode=SHAKE_FIRST;  //Ä¬ÈÏÖµ
						    BoardInf.PauseTime=0;
						#else
								BoardInf.ShakeMode=dat[28];      //Õñ¶¯ËÙ¶È
								if( (BoardInf.ShakeMode!=SHAKE_EACH)&&(BoardInf.ShakeMode!=SHAKE_FIRST) )
								{
									BoardInf.ShakeMode=SHAKE_FIRST;
								}

								BoardInf.PauseTime=( ((unsigned long)dat[29]<<24)||((unsigned long)dat[30]<<16)
																		 ||((unsigned long)dat[31]<<8)||(unsigned long)dat[32]); //Õñ¶¯Ê±¼ä
						#endif


						BoardInf.KineticPara.Enable=0; //å…³é—­åŠ¨åŠ›å­¦å‚æ•°

            //·¢ËÍÊý¾Ý
            PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_OK);
        }
        else
        {
           // PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_ERR);
        }
        break;
    }
    case COMMAND_KINETIC_ACK_PC:  //¶à°å¶¯Á¦Ñ§²âÁ¿
    {
        if(RemoteInfo_PC.RemoteFlag)
        {
					  BoardInf.KineticPara.Enable=1; //å¼€å¯åŠ¨åŠ›å­¦å‚æ•°

            RemoteInfo_PC.PlateCurrent=0;
            BoardInf.KineticPara.Readings=dat[3];  //Ñ­»·Êý
            if(BoardInf.KineticPara.Readings>KINETIC_READINGS_MAX)BoardInf.KineticPara.Readings=KINETIC_READINGS_MAX;//
            BoardInf.KineticPara.TimeInterval=((uint32)dat[4]<<24)|((uint32)dat[5]<<16)|((uint32)dat[6]<<8)| dat[7];  //¶¯Á¦Ñ§¼ä¸ôÊ±¼ä

  					RemoteInfo_PC.PlateTotal=dat[11];  //×ÜµÄ°åÊý
					  if(RemoteInfo_PC.PlateTotal>10)RemoteInfo_PC.PlateTotal=10;//

            BoardInf.Filter1Locate=(signed char)dat[15]-1;  //Ö÷²¨³¤Î»ÖÃ
            if(BoardInf.Filter1Locate<FILTER_NO)BoardInf.Filter1Locate=FILTER_NO;
            else if(BoardInf.Filter1Locate>=FILTER_MAX)BoardInf.Filter1Locate=FILTER_MAX-1;
            BoardInf.Filter2Locate=(signed char)dat[19]-1;  //·ø²¨³¤Î»ÖÃ
            if(BoardInf.Filter2Locate<FILTER_NO)BoardInf.Filter2Locate=FILTER_NO;
            else if(BoardInf.Filter2Locate>=FILTER_MAX)BoardInf.Filter2Locate=FILTER_MAX-1;
            BoardInf.DetectMode=dat[23];   //²âÁ¿Ä£Ê½
            if(BoardInf.DetectMode>1)BoardInf.DetectMode=1;

            BoardInf.ShakeEnable=dat[27]; //Õñ¶¯¿ªÆô
            BoardInf.ShakeSpeed=dat[31];  //Õñ¶¯ËÙ¶È
            if(BoardInf.ShakeSpeed<1)BoardInf.ShakeSpeed=1;
            else if(BoardInf.ShakeSpeed>3)BoardInf.ShakeSpeed=3;
            BoardInf.ShakeSpeed=BoardInf.ShakeSpeed-1;//SHAKE_SPEED_SLOW
            BoardInf.ShakeTime=( ((unsigned long)dat[32]<<24)|((unsigned long)dat[33]<<16)
                                 |((unsigned long)dat[34]<<8)|(unsigned long)dat[35]); //Õñ¶¯Ê±¼ä
						if( (BoardInf.ShakeTime<SHAKE_TIME_MIN)|| (BoardInf.ShakeTime>SHAKE_TIME_MAX) )
						{
								BoardInf.ShakeTime=SHAKE_TIME_MIN;
						}

						BoardInf.ShakeMode=dat[36];  //Õñ¶¯ËÙ¶È
            if( (BoardInf.ShakeMode!=SHAKE_EACH)&&(BoardInf.ShakeMode!=SHAKE_FIRST) )
						{
							BoardInf.ShakeMode=SHAKE_FIRST;
						}

            BoardInf.PauseTime=( ((unsigned long)dat[37]<<24)|((unsigned long)dat[38]<<16)
                                 |((unsigned long)dat[39]<<8)|(unsigned long)dat[40]); //Õñ¶¯Ê±¼ä



           // BoardInf.ShakeMode=SHAKE_FIRST;//Ä¬ÈÏÖµ
            //·¢ËÍÊý¾Ý
            PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_OK);
        }
        else
        {
            //PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_ERR);
        }
        break;
    }
    case COMMAND_VIEW_ACK_PC:           //ÐÄÌø°ü
    {
        PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_OK);
        break;
    }
	//	#ifndef SOFTWARE_DN
		case COMMAND_SEND_PN_ACK_PC:           //½ÓÊÕPNºÅ²¢±£´æ
    {
			 unsigned char i;
			   /*else if(cmd==COMMAND_SEND_PN_ACK_PC)
		{
			  for(i=0;i<PN_LENGTH;i++)
			  {
					pCommand[ptr++]=SystemPrameter.PN[i];
				}
		}*/
			for(i=0;i<PN_LENGTH;i++)
			{
			  SystemPrameter.PN[i]=dat[i];
			}
			SpiSavePN();//±£´æPNºÅ
			SpiReadPN();//¶ÁÈ¡PNºÅ
			//±È½ÏPNºÅÊÇ·ñÏàÍ¬
			  for(i=0;i<PN_LENGTH;i++)
				{
					   if(SystemPrameter.PN[i]!=dat[i])
						 {
							   break;
						 }
				}
				if(i==PN_LENGTH)//PNºÅÏàÍ¬
				{
            PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_OK);
				}
				else           //PNºÅ²»Í¬
				{
					  PrepareResponseCommand(cmd,&UartInfo_PC.SendBuffer[0],UART_PC_ERR);
				}
        break;
    }
		//#endif
    default:
    {
        break;
    }
    }
}

void WaitPCResponse(void)//´®¿Ú·¢³öÊý¾ÝºóµÈ´ýÓ¦´ð
{
    uint32 dat;
    //ÏÂÎ»»úÏòPC·¢³öÊý¾ÝºóµÈ´ýÓ¦´ð
    if(CommStatus_PC.SentFlag && RemoteInfo_PC.RemoteFlag)
    {
        CommStatus_PC.CurrentCommand=0; //È¡ÏûÖØ·¢
        CommStatus_PC.SentFlag=0;
        CommStatus_PC.RepeatSendCount=0;
			  CommStatus_PC.Timeout=0;
        //·ÖÎöÊý¾Ý¶Î
        dat=((uint16)UartInfo_PC.RecBuffer[COMM_DATA_POS_PC+2]<<8)+UartInfo_PC.RecBuffer[COMM_DATA_LEN_PC+3];
        if(dat>0)//>0±íÊ¾³ö´í
        {
            if( (UartInfo_PC.Cmd==COMMAND_MEASURE_END_PC)||(UartInfo_PC.Cmd==COMMAND_CURR_BOARD_END_PC)
                    ||(UartInfo_PC.Cmd==COMMAND_UNCONNECT_PC) ) //COMMAND_ERRCODE_PC
            {
                //ÖØ·¢
                UartCmdSend_PC(UartInfo_PC.Cmd);
            }
        }
        else//PCÒÑÊÕµ½Ó¦´ð
        {
           /* if(UartInfo_PC.Cmd== COMMAND_MEASURE_END_PC && run_status.nRunMode == RUN_MODE_IDLE)
            {
                if(RemoteInfo_PC.PlateCurrent+1 >= RemoteInfo_PC.PlateTotal)
                {
                    RemoteInfo_PC.RunningFlag=RUNNING_FLAG_FINISH;
                    UartCmdSend_PC(COMMAND_CURR_BOARD_END_PC);//¼ì²â½áÊø,·¢ËÍµ±Ç°°å½áÊøÃüÁî¸øPC
                }
                else //¿ªÊ¼ÏÂÒ»°å¼ì²â-start
                {
                    if(run_status.nRunMode == RUN_MODE_MEASURE)	//BoardInf.KineticPara.kinetic_reading_current
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
                            }//else if(run_status.bHasData)
                        }//if(BoardInf.KineticPara.Enable)//???
                    }//if(run_status.nRunMode == RUN_MODE_MEASURE)
                }//else //¿ªÊ¼ÏÂÒ»°å¼ì²â-start
            }//if(UartInfo_PC.Cmd== COMMAND_MEASURE_END_PC && run_status.nRunMode == RUN_MODE_IDLE)
            else*/ if(UartInfo_PC.Cmd== COMMAND_UNCONNECT_PC && run_status.nRunMode == RUN_MODE_IDLE)//ÔËÐÐ¹ý³ÌÖÐ²»ÄÜ¶Ï¿ª
            {
                RemoteInfo_PC.RemoteFlag=0;
                UartCmdSend_PC(UartInfo_PC.Cmd);//»Ø
            }//else if(UartInfo_PC.Cmd== COMMAND_UNCONNECT_PC && run_status.nRunMode == RUN_MODE_IDLE)
        }	//else//PCÒÑÊÕµ½Ó¦´ð
    }//if(CommStatus_PC.SentFlag && RemoteInfo_PC.RemoteFlag)
}




/******************************************************************************
*	º¯ Êý Ãû: Comm_Process_PC  void CommRxDataSend_PC(void);
*	¹¦ÄÜËµÃ÷: ²éÑ¯PC´®¿Ú½ÓÊÕ¶ÓÁÐÖÐÊÇ·ñÓÐÐèÒª´¦ÀíµÄÊý¾Ý
*	ÐÎ    ²Î:
*	·µ »Ø Öµ:
*******************************************************************************/
void CommProcess_PC(void)
{
    uint8 Status;
    uint8 i;
    uint16 sum;

    // ´ÓFIFOÖÐ»ñÈ¡Êý¾Ý²¢´¦Àí
    Status = FIFO_RxDataGet_PC(&FIFO_RxData_PC,&UartInfo_PC.RecBuffer[0]);

    // Get Successfully
    if(Status == SUCCESS)
    {
        for(i=0; i<COMM_SLA_LEN_PC; i++) //±ê¼ÇÎ»
        {
            if(UartInfo_PC.RecBuffer[i]!=CONST_COMMAND_HEAD[i])	  //±ê¼ÇÎ»²»Í¬,³ö´í
            {
                return;
            }
        }

        //½ÓÊÕ×ÓÃüÁî,³¤¶ÈÎª2
        UartInfo_PC.Cmd=((uint16)UartInfo_PC.RecBuffer[COMM_SUB_COMMAND_POS_PC]<<8)+UartInfo_PC.RecBuffer[COMM_SUB_COMMAND_POS_PC+1];

        //½ÓÊÕÊý¾Ý³¤¶È,³¤¶ÈÎª2
        UartInfo_PC.DataLen=((uint16)UartInfo_PC.RecBuffer[COMM_DATA_LEN_POS_PC+2]<<8)+UartInfo_PC.RecBuffer[COMM_DATA_LEN_POS_PC+3];
        if(UartInfo_PC.DataLen>COMM_UART_DATA_LEN_MAX_PC) //Êý¾Ý¶Î³¤¶È¹ý´ó
        {
            return;
        }


        //Ð£ÑéºÍ,³¤¶ÈÎª2
        i=COMM_DATA_POS_PC+UartInfo_PC.DataLen-COMM_CRC_LEN_PC;
        sum=((uint16)UartInfo_PC.RecBuffer[i]<<8)+UartInfo_PC.RecBuffer[i+1];
        if(GetRxCheckSum_PC(UartInfo_PC.RecBuffer, COMM_DATA_POS_PC+UartInfo_PC.DataLen-COMM_CRC_LEN_PC)!=sum)
        {
            return;
        }


        if(UartInfo_PC.Cmd<COMMAND_START_PC)//Ó¦´ðPC
        {
            //´®¿ÚÊý¾Ý´¦Àí
            UartCmdProcess_PC(UartInfo_PC.Cmd,&UartInfo_PC.RecBuffer[COMM_DATA_POS_PC]);
        }
        else
        {
            WaitPCResponse();//´®¿Ú·¢³öÊý¾ÝºóµÈ´ýÓ¦´ð
        }
    }//if(Status == SUCCESS)
}





//-----------------------------------------------------------------//
//	¹¦ÄÜ:PC´®¿ÚÖØ·¢×Óº¯Êý
//	Èë¿Ú²ÎÊý: cmdÃüÁî×Ö,
//	³ö¿Ú²ÎÊý:
//  ±¸×¢:
//-----------------------------------------------------------------//
void UartReSend(void)
{
    if( (CommStatus_PC.CurrentCommand>=COMMAND_START_PC)&&(CommStatus_PC.CurrentCommand<=COMMAND_END_PC) )
    {
        if(CommStatus_PC.Timeout<UART_RE_SEND_TIME_MAX)CommStatus_PC.Timeout++;//³¬Ê±¼ÆÊýÆ÷
        else
        {
            CommStatus_PC.Timeout=0;//UART_RE_SEND_TIME_MAX;
            CommStatus_PC.RepeatSendCount++;
            if(CommStatus_PC.RepeatSendCount<UART_RE_SEND_COUNT_MAX)
            {
                UartCmdSend_PC(CommStatus_PC.CurrentCommand);
							  UartResendPrepared(CommStatus_PC.CurrentCommand);//ÖØÖÃÖØ·¢±äÁ¿
            }
            else
            {
                CommStatus_PC.RepeatSendCount=0;
                //gSystem.SystemErrCode |= ERRCODE_UART;
							  //UartCommInit();
            }

        }
    }//if( (CommStatus_PC.CurrentCmd==cmd)&&(CommStatus_PC.CurrentCmd>0) )
}

