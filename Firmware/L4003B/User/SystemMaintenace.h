//CaliMode
#define  CALI_MODE_FACTORY  0
#define  CALI_MODE_CUSTOMER  1


//m_Zero
#define  ZERO_MIN    1500
#define   ZERO_MAX   8000


#define  PLATE_SEL_WIDTH         75
#define  DOOR_SEL_WIDTH          75

#define  CALI_MODE_SEL_WIDTH1      70
#define  CALI_MODE_SEL_WIDTH2      80

#define  PASSWORD_START_X       (READINGS_START_X)
#define  PASSWORD_START_Y       (READINGS_START_Y)
#define  PASSWORD_END_X           (READINGS_END_X)
#define  PASSWORD_END_Y           (READINGS_END_Y)

#define  PASSWORD_R_START_X     (READINGS_R_START_X )
#define  PASSWORD_R_START_Y     (READINGS_R_START_Y)
#define  PASSWORD_R_END_X         (READINGS_R_END_X )
#define  PASSWORD_R_END_Y         (READINGS_R_END_Y )

//modify start lugj 20180910
#define  CALI_MODE_START_X       (READINGS_START_X)
#define  CALI_MODE_START_Y       (FILTER_2_START_Y)
#define  CALI_MODE_END_X           (READINGS_END_X)
#define  CALI_MODE_END_Y           (FILTER_2_END_Y)

#define  CALI_MODE_R_START_X     (READINGS_R_START_X )
#define  CALI_MODE_R_START_Y     (FILTER_2_START_Y)
#define  CALI_MODE_R_END_X        (CALI_MODE_R_START_X+120 )
#define  CALI_MODE_R_END_Y        (FILTER_2_END_Y)
//modify end lugj 20180910

//modify start lugj 20180910
#define  LOCK_START_X         (READINGS_START_X)
#define  LOCK_START_Y         (MODE_START_Y)
#define  LOCK_END_X           (READINGS_END_X)
#define  LOCK_END_Y           (MODE_END_Y)

#define  LOCK_R_START_X     (READINGS_R_START_X )
#define  LOCK_R_START_Y     (MODE_START_Y)
#define  LOCK_R_END_X        (CALI_MODE_R_START_X+120 )
#define  LOCK_R_END_Y        (MODE_END_Y)
//modify end lugj 20180910

#define  UPDATA_PASSWORD         "246891"
#define  UPDATA_PASSWORD_LOCK    "246891"
#define  FORMAT_PASSWORD         "81828384"

#ifndef  __MAINTENACE_H
#define  __MAINTENACE_H

void SystemMaintenace_Interface(void);
void SystemMaintenace_Go(void);
void SystemMaintenace_Scan(void);
#endif



