

#define PLUS_BUTTON_START_X  657
#define PLUS_BUTTON_START_Y  270
#define PLUS_BUTTON_END_X      (PLUS_BUTTON_START_X + 61) //718
#define PLUS_BUTTON_END_Y      (PLUS_BUTTON_START_Y + 36) //306


#define MINUS_BUTTON_START_X  (PLUS_BUTTON_END_X + 5) //723
#define MINUS_BUTTON_START_Y  PLUS_BUTTON_START_Y //270
#define MINUS_BUTTON_END_X      (MINUS_BUTTON_START_X + 61) //784
#define MINUS_BUTTON_END_Y      PLUS_BUTTON_END_Y	//306


#define CYCLE_BUTTON_START_X  (ANALYSIS_LOG_SELECT_START_X)
#define CYCLE_BUTTON_START_Y  (ANALYSIS_LOG_SELECT_START_Y)
#define CYCLE_BUTTON_END_X    (CYCLE_BUTTON_START_X+100)
#define CYCLE_BUTTON_END_Y    (CYCLE_BUTTON_START_Y+45)



#define CURVE_AREA_START_X  0
#define CURVE_AREA_START_Y  (TITLESBAR_HEIGHT)//(122 + 10) 
#define CURVE_AREA_END_X    (CONTENTBAR_CONTENT_WIDTH-1)//630
#define CURVE_AREA_END_Y    (CONTENTBAR_HEIGHT-1) //436

#define CURVE_AREA_AXIS_START_X   70
#define CURVE_AREA_AXIS_END_X     (CURVE_AREA_END_X-10)
#define CURVE_AREA_AXIS_START_Y   (CURVE_AREA_START_Y+10)
#define CURVE_AREA_AXIS_END_Y     (CURVE_AREA_END_Y-40)//20

#define CURVE_AREA_AXIS_TICK_X   10
#define CURVE_AREA_AXIS_TICK_Y   10

#define CURVE_AREA_AXIS_LINE_X   50  //X与最后一个坐标的距离
#define CURVE_AREA_AXIS_LINE_Y   20  //Y与第一个坐标的距离

#define CURVE_AREA_TEXT_START_X   190 //200





#ifndef __REPORT_H
#define __REPORT_H

enum
{
    REPORT_MENU_RAWDATA = 0, //原始数据
    REPORT_MENU_INTERPRET,   //定性分析
    REPORT_MENU_ANALYSIS,    //定量分析
    REPORT_MENU_CURVE,       //标准曲线
    REPORT_MENU_QC,          //质控分析
    REPORT_MENU_MAX
}; //2014-8-19项


enum
{
    ANALYSIS_MODE_RAWDATA = 0, //原始数据
    ANALYSIS_MODE_INTERPRET,   //定性分析
    ANALYSIS_MODE_ANALYSIS,    //定量分析
    ANALYSIS_MODE_CURVE,       //标准曲线
    ANALYSIS_MODE_QC,          //质控分析
    ANALYSIS_MODE_MAX
}; //2014-8-19项


//Abs校准
typedef struct
{
    unsigned char CurrMenu;  //当前界面
    unsigned char ReportReady;
} REPORT_MENU;
extern REPORT_MENU  ReportMenu;


extern const char SELECT_CONTROL_REPORT_FILTER1[LANGUAGE_TYPES][15];
extern const char SELECT_CONTROL_REPORT_FILTER2[LANGUAGE_TYPES][15];
extern const char SELECT_CONTROL_REPORT_FILTER12[LANGUAGE_TYPES][20];




extern const char SELECT_REPORT_CYCLE[LANGUAGE_TYPES][20];
extern const char SELECT_REPORT_SAMPLE_NO[LANGUAGE_TYPES][20];
extern const char SELECT_REPORT_SAMPLE_ALL[LANGUAGE_TYPES][20];


void  DisplayAnalysisFilterExpand(void);
void DisplayAnalysisLogExpand(void);

void DoNormalAnalysis(void);
void InitNormalAnalysis(void) ;

void DoKineticAnalysis(void);

void InitKineticAnalysis(void);

void DisplayQC(void);///////
void DisplayKineticCurve(void);/////////
void DisplayKineticAnalysis(void);//
void DisplayRawInter(void);//
void DisplayReportInterface(void);//



void RefreshReport(void);
void Report_Interface(void);
void Report_Scan(void);
void Report_Go(void);

#endif

