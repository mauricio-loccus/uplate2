#ifndef __SYSTEM_UPDATE_H
#define __SYSTEM_UPDATE_H
extern int  flag_update;
extern  unsigned char flag_start_update,flag_update_one_ok;
extern unsigned char flag_update_busy;//fmc160924


void SystemUpdate_Interface(void);

#endif
