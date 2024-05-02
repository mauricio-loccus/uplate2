#include "includes.h"
#include "MainTask.h"
#include "TouchKeyCode.h"
//#include "MainTask.h"
TOUCH_KEY  TouchKey;
EXT_KEY  Key;

#ifdef DEGUG_SCREEN
extern void Print_Screen(void);
#endif

unsigned char  DoorStatus;
unsigned char  DoorStatusBack;
signed char  DoorStatusDelay;


//****************检查键盘
unsigned char KeyScanPress(void)
{
    unsigned char keyval=0,i;
    //	return 1;
    //检测按键
    GPIO_SetBits   ( GPIOB, GPIO_Pin_1 );  //=1  GPIOH
    GPIO_ResetBits ( GPIOB, GPIO_Pin_0 );  //=0 GPIOI11
    for(i=0; i<200; i++);
    if ((GPIOA->IDR & GPIO_Pin_3) == 0) //K1
    {
        keyval=1;
    }
    if ((GPIOA->IDR & GPIO_Pin_5) == 0) //K2
    {
        keyval |=2;
    }
    GPIO_SetBits   ( GPIOB, GPIO_Pin_0 );  //=1
    GPIO_ResetBits ( GPIOB, GPIO_Pin_1 );  //=0
    //GUI_Delay(1);
    for(i=0; i<200; i++);
    if ((GPIOA->IDR & GPIO_Pin_3) == 0) //K1
    {
        keyval |=4;
    }
    if ((GPIOA->IDR & GPIO_Pin_5) == 0) //K2
    {
        keyval |=8;
    }
    return keyval;  //9 3isok  0c is not ok
}

//TOUCH_KEY  TouchKey;
//	函 数 名: TouchKeyScan
//	功能说明: 触摸屏的按键扫描
//	形    参: 无
//	返 回 值: 无
void KeyScan(void)
{
    Key.KeyStatus=KeyScanPress();
    if (Key.KeyStatus > 0)
    {
        if (Key.KeyStatus == Key.KeyStatusBack)
        {
            if (Key.KeyPressDelay < KEY_DELAY)
            {
                Key.KeyPressDelay++;
                Key.KeyValueBack = 0;
            }
            else
            {
                if (Key.KeyValueBack == 0)
                {
                    Key.KeyValue = Key.KeyStatus;
                    Key.KeyValueBack = Key.KeyStatus;
                }

                else if (Key.KeyStatus == Key.KeyValueBack)
                {   //lgj161014
                    if(gSystem.SecFlag )
                    {
                        if (Key.KeyPressTimes < KEY_REPEAT)Key.KeyPressTimes++;
                        else
                        {
                            //TouchKey.KeyValueBack = 0;
                            //TouchKey.KeyPressTimes = 0;
                            Key.KeyValue = Key.KeyStatus;
                        }
                    }
                }
                else //if (TouchKey.KeyStatus != TouchKey.KeyStatusBack)
                {
                    //TouchKey.KeyValue = TouchKey.KeyStatus;
                    Key.KeyValueBack = Key.KeyStatus;
                    //	TouchKey.KeyPressTimes = 0;
                }
            }
        }
        else
        {
            Key.KeyPressTimes = 0;
            Key.KeyPressDelay = 0;
            Key.KeyValueBack = 0;
        }
        Key.KeyStatusBack = Key.KeyStatus;
    }
    else
    {
        Key.KeyPressTimes = 0;
        Key.KeyPressDelay = 0;
        Key.KeyValueBack = 0;

        Key.KeyStatus = 0;
        Key.KeyStatusBack=0;

    }
}
/*
void PCInit(void)
{
	int i;
		for(i=0;i<100;i++)
	  {
		  USART_SendData(UART4, 'A'+i);
	    while (USART_GetFlagStatus(UART4, USART_FLAG_TC) == RESET);
	  }
}
*/
/*
void ClearUartFlag(void)
{
	 // run_status.nRunMode = RUN_MODE_IDLE;
   // run_status.task_busy=0;

    CommStatus_PC.CurrentCommand=0;
    CommStatus_PC.SentFlag=0;
    CommStatus_PC.RepeatSendCount=0;
    CommStatus_PC.Timeout=0;
	
    UartInfo.Cmd=0;
 		UartInfo.Full=0;
}*/
void KeyProcess(void)
{
    if(RemoteInfo_PC.RemoteFlag)//PC监控中
    {
			  #ifndef DEBUG_SCREEN
        if (Key.KeyValue==EXT_KEY_STOP)//停止
        {
						if(RemoteInfo_PC.RemoteFlag)
						{
							      RemoteInfo_PC.RemoteFlag=0;
							      UartInfo_PC.SendBuffer[0]=0;
                   // PrepareResponseCommand(COMMAND_UNCONNECT_ACK_PC,&UartInfo_PC.SendBuffer[0],UART_PC_OK);
                    UartCmdSend_PC(COMMAND_UNCONNECT_PC);//注虓讖擢l迵募庐
                    RestoreMachineStatus();   
                    run_status.nRunMode = RUN_MODE_IDLE;
                    //if(RemoteInfo_PC.RunningFlag)
										if(run_status.task_busy)
										{
											  MCU_StartStop(0);
//											  RemoteInfo_PC.RunningFlag=0;
											  run_status.task_busy=0;
										}
										//ClearUartFlag(); //lugj modify 20181106 
                    DeletePCMenu();
										gSystem.MenuRefreshFlag=1;
								    gSystem.TitleButtonEnable=1;
						 }
						 else if( (run_status.task_busy==1 )&&(run_status.nRunMode != RUN_MODE_SELFTEST) ) 
					   {
								// RestoreMachineStatus();
								run_status.nRunMode = RUN_MODE_IDLE;
								run_status.task_busy=0;
								MCU_StartStop(0);
							  DeletePromptMenu(0);
							 

								gSystem.MenuRefreshFlag=1;
								gSystem.TitleButtonEnable=1;
					  } 
        }
				#else 
				if (Key.KeyValue==EXT_KEY_STOP)//停止
				{
					   #ifdef DEBUG_SCREEN
                Print_Screen();
             #endif
				}
				#endif
				
        return;
    }
		#ifndef DEBUG_SCREEN
    if( (KeyPadAsc.UseFlag == KEYPAD_BUSY)||(KeyPadNum.UseFlag == KEYPAD_BUSY)) //||(PromptMenu.InterfaceStatus==PROMPT_MENU_BUSY) 
    {
        return;
    }
		
    if( (gSystem.SystemInterface!=MI_PROTOCOL) && (gSystem.SystemInterface!=MI_REPORT)
            && (gSystem.SystemInterface!=MI_SET) && (gSystem.SystemInterface!=MI_HELP)&&(gSystem.SystemInterface != MI_ABS_CALIBRATION) )
    {
        return;
    }
		#endif 


    if ((Key.KeyValue==EXT_KEY_START)&&(PromptMenu.InterfaceStatus!=PROMPT_MENU_BUSY) ) //RUN
    {
			  if(PromptMenu.InterfaceStatus==PROMPT_MENU_BUSY) 
				{
					 return;
				}
        //	PCInit();////////////debug
        if( (run_status.task_busy==0)&&(run_status.nRunMode != RUN_MODE_SELFTEST)
					 &&( (gSystem.SystemInterface == MI_PROTOCOL)||(gSystem.SystemInterface == MI_REPORT) ))// || (gSystem.SystemInterface == MI_ABS_CALIBRATION))
        {
//  ((gSystem.SystemInterface == MI_ABS_CALIBRATION)&&(AbsCalibration_auto_flag)) ))//
            gSystem.RunReqFlag=1;
            /*
              if (BoardInf.Filter1Locate <0)
            {
              strcpy(PromptMenu.InputStr,STR_SEL_FILTER[SystemPrameter.SystemLanguage]);
            		   Prompt_Interface(PROMPT_WARMING);
            		   return;
            }
            else if(FilterLun.Filter[BoardInf.Filter1Locate]==0)
            {
            		   strcpy(PromptMenu.InputStr,STR_SEL_FILTER[SystemPrameter.SystemLanguage]);
            		   Prompt_Interface(PROMPT_WARMING);
            		   return;
            	}
            else if(gSystem.ProgramMax>=PROGRAM_MAX)  //程序已满
            	{
            		   //if(gSystem.ProgramMax>=PROGRAM_MAX)
                   //{
            	        strcpy(PromptMenu.InputStr,STR_NAND_FULL[SystemPrameter.SystemLanguage]);
              Prompt_Interface(PROMPT_WARMING);
            	        return ;
            			 //}
              }



              memcpy(&BoardInfBack, &BoardInf, sizeof(BOARD_INF));
             // gSystem.CurrBlockBack=gSystem.CurrBlock;          //??
              GetDefaultFileName();         //?????
              //gSystem.CurrBlock=gSystem.CurrBlockBack;          //??
              gSystem.CreateFlag=0;         //?????
              KeyPadAscii_Interface(0);     //???????????????
              if(KeyPadAsc.ReturnKey==KEYPAD_RETURN_ENTER)
            	{
            		   strcpy(BoardInf.Name,KeyPadAsc.InputValueStr);
            		  // if(BoardInf.KineticPara.Enable!=BoardInfBack.KineticPara.Enable)
            			 {
            				 LanguageChange.Report=1;
            			 }
                  // memcpy(&BoardInfBack, &BoardInf, sizeof(BOARD_INF));
            		  // gSystem.BeforeHasDataFlag=gSystem.HasDataFlag;
            		   run_status.bHasDataBack=run_status.bHasData;
               MCU_StartStop(1);          //????
               run_status.task_busy=1;    //task_busy==1?,???????
            	}*/
        }
    }
    else if (Key.KeyValue==EXT_KEY_STOP)//停止
    {
			  #ifdef DEBUG_SCREEN
            Print_Screen();
        #endif
        //if (run_status.nRunMode==1 && !remote_info_PAD.bRemote && !remote_info_PC.bRemote)
        if( ( (run_status.task_busy==1 )&&(run_status.nRunMode != RUN_MODE_SELFTEST) )
					|| ((gSystem.SystemInterface == MI_ABS_CALIBRATION)&&(AbsCalibration_auto_flag)) )//
        {
					  

					  ClearAutoCaliFlag();
					
					
            run_status.nRunMode = RUN_MODE_IDLE;
            MCU_StartStop(0);
            run_status.task_busy=0;
				    if((gSystem.SystemInterface == MI_ABS_CALIBRATION)&&(AbsCalibration_auto_flag))
						{
							DeletePromptMenu(0);
							gSystem.MenuRefreshFlag=1;
						}
						else
						{
								//run_status.task_busy=2;
								//gSystem.HasDataFlag=gSystem.BeforeHasDataFlag;
								run_status.bHasData=run_status.bHasDataBack;
								memcpy(&BoardInf, &BoardInfBack, sizeof(BOARD_INF)); //还原数据
								DeletePromptMenu(0);
								gSystem.MenuRefreshFlag=1;
								gSystem.TitleButtonEnable=1;
						}
        }
    }
    else if( (Key.KeyValue==EXT_KEY_INOUT)&&(PromptMenu.InterfaceStatus!=PROMPT_MENU_BUSY) )//板进出
    {
			  if(PromptMenu.InterfaceStatus==PROMPT_MENU_BUSY) 
				{
					 return;
				}
        if( ((run_status.task_busy==0)&&(run_status.nRunMode != RUN_MODE_SELFTEST))
					||((gSystem.SystemInterface == MI_ABS_CALIBRATION)&&(AbsCalibration_auto_flag==0)) )
        {
            if(run_status.doorState==0)
            {
                run_status.doorState=1;
            }
            else
            {
                run_status.doorState=0;
            }

            openClosedoor(run_status.doorState);
        }
				#ifdef DEBUG_SCREEN
            Print_Screen();
       #endif
    }
}
//TOUCH_KEY  TouchKey;
//	函 数 名: TouchKeyScan
//	功能说明: 触摸屏的按键扫描
//	形    参: 无
//	返 回 值: 无
void TouchKeyScan(void)
{
    if (TouchKey.KeyStatus > 0)
    {
        if (TouchKey.KeyStatus == TouchKey.KeyStatusBack)
        {
            if (TouchKey.KeyPressDelay < TOUCH_KEY_DELAY)
            {
                TouchKey.KeyPressDelay++;
                TouchKey.KeyValueBack = 0;
            }
            else
            {
                if (TouchKey.KeyValueBack == 0)
                {
                    TouchKey.KeyValue = TouchKey.KeyStatus;
                    TouchKey.KeyValueBack = TouchKey.KeyStatus;
                }
                else// if (TouchKey.KeyValue == TouchKey.KeyValueBack)
                {
                    if (TouchKey.KeyPressTimes < TOUCH_KEY_REPEAT)TouchKey.KeyPressTimes++;
                    else
                    {
                        //TouchKey.KeyValueBack = 0;
                        TouchKey.KeyPressTimes = 0;
                        TouchKey.KeyValue = TouchKey.KeyStatus;
                    }
                }
                //else //if (TouchKey.KeyStatus != TouchKey.KeyStatusBack)
                //{
                //TouchKey.KeyValue = TouchKey.KeyStatus;
                //TouchKey.KeyValue = TouchKey.KeyStatus;
                // }
            }
        }
        else
        {
            TouchKey.KeyPressTimes = 0;
            TouchKey.KeyPressDelay = 0;
            TouchKey.KeyValueBack = 0;
        }
        TouchKey.KeyStatusBack = TouchKey.KeyStatus;
    }
    else
    {
        TouchKey.KeyPressTimes = 0;
        TouchKey.KeyPressDelay = 0;
        TouchKey.KeyValueBack = 0;

        TouchKey.KeyStatus = 0;
        TouchKey.KeyStatusBack=0;

    }
}
