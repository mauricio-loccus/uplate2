






#include "includes.h"
#include "MainTask.h"

#include "bsp_rtc.h"
#include "stm32f4xx.h"
#include "demo_ext_sdram.h"

RTC_TIME RtcDateTime;



extern void touch_reset_0(void);
extern void touch_reset_1(void);

unsigned int screen_busy_delay=0,tuch_reset_time=0;
unsigned char tuch_time_over=0;
extern unsigned char flag_usb_disk_connect;//////////

//串口消息定义
//OS_Q queue;                                            //消息
//#define Q_MSG_UART_MAX   10
//void *QmsgUartTab[Q_MSG_UART_MAX];	                   //消息表



#define  debug_print  1 //1 串口7打印输出 0串口7打印不输出
//*********************************
#define BUSY_DELAY  100
static void AppTaskCreate (void);

int main(void)
{
    /*
      在启动调度前，为了防止初始化STM32外设时有中断服务程序执行，这里禁止全局中断(除了NMI和HardFault)。
      这样做的好处是：
      1. 防止执行的中断服务程序中有FreeRTOS的API函数。
      2. 保证系统正常启动，不受别的中断影响。
      3. 关于是否关闭全局中断，大家根据自己的实际情况设置即可。
      在移植文件port.c中的函数prvStartFirstTask中会重新开启全局中断。通过指令cpsie i开启，__set_PRIMASK(1)
      和cpsie i是等效的。
     */



 			DISABLE_INT();
    NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x10000);//*/

    __set_PRIMASK(1);

    /* 硬件初始化 */
    bsp_Init();
    StartUpPra.EnableUsbCheck=0;
    /* 创建任务 */
    AppTaskCreate();

    /* 启动调度，开始执行任务 */
    vTaskStartScheduler();

    /*
      如果系统正常启动是不会运行到这里的，运行到这里极有可能是用于定时器任务或者空闲任务的
      heap空间不足造成创建失败，此要加大FreeRTOSConfig.h文件中定义的heap大小：
      #define configTOTAL_HEAP_SIZE	      ( ( size_t ) ( 30 * 1024 ) )
    */
    while(1);
}

static void AppTaskIntIF(void *pvParameters)
{
    while(1)
    {
        //vTaskDelay(1);

        if(screen_busy_delay>=BUSY_DELAY)//fmc161205
        {
            if(g_tFT5X06.Enable == 1)
            {
                //bsp_KeyScan();fmc161206
                FT5X06_OnePiontScan();
                //OSTimeDly(2, OS_OPT_TIME_DLY, &err);
                vTaskDelay(2);
                //	if(uart_sent_wait50ms<SEND_DELAY50MS)// 25*2
                // uart_sent_wait50ms++;
            }
        }
        vTaskDelay(2);
        //OSTimeDly(2, OS_OPT_TIME_DLY, &err);  //lgj161009
        if(screen_busy_delay<BUSY_DELAY)        //25*2
            screen_busy_delay++;
        //***************************
        //	if(uart_sent_wait50ms<SEND_DELAY50MS)// 25*2
        //  uart_sent_wait50ms++;
        //*************************TUCH 1miao reset fmc161216
        tuch_reset_time++; 
        if(tuch_reset_time>500)//400*3=1.2miao
        {
            tuch_reset_time=0;
            touch_reset_0();
            //OSTimeDly(20, OS_OPT_TIME_DLY, &err);  //lgj161009
            vTaskDelay(20);
            touch_reset_1();

        }
        //  Usb_check();		//
    }
}


static void AppTaskUsb(void *pvParameters)
{
    while(1)
    {
        vTaskDelay(5);
        if( StartUpPra.EnableUsbCheck)
        {
            //if(flag_usb_disk_connect==0)
            //{
            Usb_check();
            //}
            // else
            // {
            // check_usb_connect();
            //}
        }


    }
}
static void AppTaskUserIF(void *pvParameters)
{
	
    uint8_t  i;
		uint8_t  J;
    i=0;
	  J=0;
    while(1)
    {
        if(StartUpPra.TimeCount<20)StartUpPra.TimeCount++;
        else
        {
            StartUpPra.TimeCount=0;
            if( StartUpPra.StartFlag )
            {
								
								if(J==0)
								{
									GUI_SetColor(GUI_WHITE);
									GUI_FillCircle(355,364,5);
									GUI_FillCircle(369,364,5);
									GUI_FillCircle(383,364,5);
									GUI_FillCircle(397,364,5);
									GUI_FillCircle(411,364,5);
									J=10;
								}
                StartUp_Go(i);
                i++;
                if(i>=10)
                    i=0;
                gSystem.SecFlag=1;
                // UartReSend(CMD_CHECK,UART_FLAG_MOTOR);
            }
        }

        //if(	run_status.nRunMode != RUN_MODE_IDLE)//RUN_MODE_PLATE_IN;
        //{
        // if(run_status.nTimeOut>0) //= PLATE_TIMEOUT;
        // {
        //	 run_status.nTimeOut--;
        // }
        // else
        // {
        //gSystem.SystemErrCode=
        // }

        SystemBeep();
        //UART6_Analysis();
        vTaskDelay(12);
        //	UART6_Analysis();
    }
}

static void AppTaskGUI(void *pvParameters)
{
    while(1)
    {
        vTaskDelay(2);
        MainTask();
    }
}


//*********************************************************************************************************

static void AppTaskCreate (void)
{
    //1表示最低优先级
    /* xTaskCreate( AppTaskUsb,
                  "AppTaskUsb",
                  4096,
                  NULL,
                  1,
                  NULL );
    */
    xTaskCreate( AppTaskIntIF,   	/* 任务函数  */
                 "AppTaskIntIF",     	/* 任务名    */
                 8192,//4096,               	/* 任务栈大小，单位word，也就是4字节 */
                 NULL,              	/* 任务参数  */
                 3,                 	/* 任务优先级*/
                 NULL );  /* 任务句柄  */


    xTaskCreate( AppTaskUserIF,    		/* 任务函数  */
                 "AppTaskUserIF",  		/* 任务名    */
                 8192,//4096,         		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,        		/* 任务参数  */
                 3,           		/* 任务优先级*/
                 NULL );          /* 任务句柄  */

    xTaskCreate( AppTaskGUI,     		/* 任务函数  */
                 "AppTaskGUI",   		/* 任务名    */
                 6200,//10240,             		/* 任务栈大小，单位word，也就是4字节 */
                 NULL,           		/* 任务参数  */
                 2,               		/* 任务优先级*/
                 NULL );  /* 任务句柄  */



}


