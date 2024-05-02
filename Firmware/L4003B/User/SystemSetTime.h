


#define TIME_SET_R_START_X  120
#define TIME_SET_R_START_Y  FILTER_2_R_START_Y
#define TIME_SET_R_END_X    255
#define TIME_SET_R_END_Y    FILTER_2_R_END_Y

#define DATE_SET_R_START_X  120
#define DATE_SET_R_START_Y  FILTER_1_R_START_Y
#define DATE_SET_R_END_X    255
#define DATE_SET_R_END_Y    FILTER_1_R_END_Y








#ifndef _SYSTEM_SETTIME_H
#define _SYSTEM_SETTIME_H

void SystemSetTime_Interface(void);
void SystemSetTime_Go(void);
void SystemSetTime_Scan(void);
void SystemTimeEnter(void);
void SystemTimeCancel(void);


#endif

