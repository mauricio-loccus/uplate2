



#define LAY_SMALL_WIDTH   35
#define LAY_SMALL_HIGH    35
#define LAY_SMALL_DIS     36

#define LAY_SMALL_START_X 45
#define LAY_SMALL_START_Y 145
#define LAY_SMALL_END_X   (LAY_SMALL_START_X+11*LAY_SMALL_DIS+LAY_SMALL_WIDTH)
#define LAY_SMALL_END_Y (LAY_SMALL_START_Y+7*LAY_SMALL_DIS+LAY_SMALL_HIGH)



#define SD_MAX   12
#define QC_MAX   9

//#define UD_MAX   999
//#define UD_MIN   0


#define SD_SELECT_WIDTH   42
#define QC_SELECT_WIDTH   42

//以下内容全部定义过
#define LAY_BIG_RADIUS     24  //大圆半径
#define LAY_SMALL_RADIUS   16  //小圆半径

#define LAY_BIG_DIS       54  //大圆间距



//BK位置定义
#define LAY_BLANK_START_X   564
#define LAY_BLANK_START_Y   163
#define LAY_BLANK_END_X     613
#define LAY_BLANK_END_Y     (LAY_BLANK_START_Y+LAY_BIG_RADIUS*2)

#define LAY_BLANK_POS_X    (LAY_BLANK_START_X+LAY_BIG_RADIUS)  //圆心
#define LAY_BLANK_POS_Y    (LAY_BLANK_START_Y+LAY_BIG_RADIUS)

//SD位置定义
#define LAY_SD_START_X     (LAY_BLANK_START_X)
#define LAY_SD_START_Y     (LAY_BLANK_START_Y+LAY_BIG_DIS)  //(93+54)
#define LAY_SD_END_X       (LAY_BLANK_END_X)
#define LAY_SD_END_Y       (LAY_SD_START_Y+LAY_BIG_RADIUS*2)

#define LAY_SD_POS_X       (LAY_SD_START_X+LAY_BIG_RADIUS)  //圆心
#define LAY_SD_POS_Y       (LAY_SD_START_Y+LAY_BIG_RADIUS)

//QC位置定义
#define LAY_QC_START_X     (LAY_BLANK_START_X)
#define LAY_QC_START_Y     (LAY_BLANK_START_Y+LAY_BIG_DIS*2) //(301)
#define LAY_QC_END_X       (LAY_BLANK_END_X)
#define LAY_QC_END_Y       (LAY_QC_START_Y+LAY_BIG_RADIUS*2)

#define LAY_QC_POS_X       (LAY_QC_START_X+LAY_BIG_RADIUS)  //圆心
#define LAY_QC_POS_Y       (LAY_QC_START_Y+LAY_BIG_RADIUS)

//UD位置定义
#define LAY_UD_START_X  (LAY_BLANK_START_X)
#define LAY_UD_START_Y  (LAY_BLANK_START_Y+LAY_BIG_DIS*3)
#define LAY_UD_END_X    (LAY_BLANK_END_X)
#define LAY_UD_END_Y    (LAY_UD_START_Y+LAY_BIG_RADIUS*2)

#define LAY_UD_POS_X    (LAY_UD_START_X+LAY_BIG_RADIUS)  //圆心
#define LAY_UD_POS_Y    (LAY_UD_START_Y+LAY_BIG_RADIUS)



//EP位置定义
#define LAY_EP_START_X  (LAY_BLANK_START_X)
#define LAY_EP_START_Y  (LAY_BLANK_START_Y+LAY_BIG_DIS*4)
#define LAY_EP_END_X    (LAY_BLANK_END_X)
#define LAY_EP_END_Y    (LAY_EP_START_Y+LAY_BIG_RADIUS*2)

#define LAY_EP_POS_X    (LAY_EP_START_X+LAY_BIG_RADIUS)  //圆心
#define LAY_EP_POS_Y    (LAY_EP_START_Y+LAY_BIG_RADIUS)




//NC位置定义
#define LAY_NC_START_X      510
#define LAY_NC_START_Y     (LAY_BLANK_START_Y)
#define LAY_NC_END_X       (LAY_NC_START_X+LAY_BIG_RADIUS*2)
#define LAY_NC_END_Y       (LAY_BLANK_END_Y)

#define LAY_NC_POS_X       (LAY_NC_START_X+LAY_BIG_RADIUS)  //圆心
#define LAY_NC_POS_Y       (LAY_NC_START_Y+LAY_BIG_RADIUS)


//PC位置定义
#define LAY_PC_START_X      (LAY_NC_START_X)
#define LAY_PC_START_Y      (LAY_NC_START_Y+LAY_BIG_DIS)
#define LAY_PC_END_X        (LAY_NC_END_X)
#define LAY_PC_END_Y        (LAY_PC_START_Y+LAY_BIG_RADIUS*2)

#define LAY_PC_POS_X       (LAY_PC_START_X+LAY_BIG_RADIUS)  //圆心
#define LAY_PC_POS_Y       (LAY_PC_START_Y+LAY_BIG_RADIUS)




#define LAY_BIG_START_X     510
#define LAY_BIG_START_Y     163
#define LAY_BIG_END_X      LAY_EP_END_X
#define LAY_BIG_END_Y      LAY_EP_END_Y



//#define WELLS_TYPE_NO   -1
#ifndef __PROTOCOL_LAYOUT_H
#define __PROTOCOL_LAYOUT_H

enum
{
    WELLS_TYPE_PC = 0,
    WELLS_TYPE_NC,
    WELLS_TYPE_BK,
    WELLS_TYPE_SD,
    WELLS_TYPE_QC,
    WELLS_TYPE_UD,
    WELLS_TYPE_EP,
    WELLS_TYPE_MAX,// 7
};

extern const char STR_LAYOUT_CONCENTRATION[LANGUAGE_TYPES][20];
extern const char WELLS_TYPE_STR[WELLS_TYPE_MAX][3];
extern const char WELLS_TYPE_STR_PT[WELLS_TYPE_MAX][3];

void ProtocolLayout_Scan(void);
void ProtocolLayout_Go(void);
void ProtocolLayout_Interface(void);

#endif
