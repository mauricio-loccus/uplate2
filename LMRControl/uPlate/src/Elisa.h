#ifndef ELISA_H
#define ELISA_H

#include <System.hpp>

#include "unStrUtils.h"
#include "unStrSplitJoin.h"

#define CURVE_AREA_START_X  0
#define CURVE_AREA_START_Y  (122 + 10)
#define CURVE_AREA_END_X    630
#define CURVE_AREA_END_Y    436
#define CURVE_AREA_AXIS_START_X   70
#define CURVE_AREA_AXIS_START_Y   (CURVE_AREA_END_Y - 40)
#define CURVE_AREA_AXIS_END_X   40
#define CURVE_AREA_AXIS_END_Y   20
#define CURVE_AREA_AXIS_TICK_X   10
#define CURVE_AREA_AXIS_TICK_Y   10
#define CURVE_AREA_TEXT_START_X   200

#define SYS_LANG_START_X  48
#define SYS_LANG_START_Y  135
#define SYS_LANG_END_X    162
#define SYS_LANG_END_Y    249

#define SYS_FILTER_START_X  236
#define SYS_FILTER_START_Y  135
#define SYS_FILTER_END_X    350
#define SYS_FILTER_END_Y    249

#define SYS_REPAIR_START_X  424
#define SYS_REPAIR_START_Y  135
#define SYS_REPAIR_END_X    538
#define SYS_REPAIR_END_Y    249

#define SYS_PRINT_START_X  612
#define SYS_PRINT_START_Y  135
#define SYS_PRINT_END_X    726
#define SYS_PRINT_END_Y    249

#define SYS_QUALITY_START_X  48
#define SYS_QUALITY_START_Y  269
#define SYS_QUALITY_END_X    162
#define SYS_QUALITY_END_Y    383

//2015-2-13

#define SYS_LCD_START_X  48
#define SYS_LCD_START_Y  269
#define SYS_LCD_END_X    162
#define SYS_LCD_END_Y    383

#define SYS_TIME_START_X  236
#define SYS_TIME_START_Y  269
#define SYS_TIME_END_X    350
#define SYS_TIME_END_Y    383
//2015-2-13

#define SYS_NETWORK_START_X  236+188
#define SYS_NETWORK_START_Y  269
#define SYS_NETWORK_END_X    350+188
#define SYS_NETWORK_END_Y    383

#define IP_CHAR_MAX 40
#define PORT_CHAR_MAX 40
#define ERROR_CHAR_MAX 40
#define ERROR_COLUMN_MAX 40

#define FILTER_COEF_MAX 4

#define IAPP_MAX   (1024 * 56)
#define SERIAL_ACK 0x06
#define SERIAL_NAK 0x15
#define SERIAL_ETX 0x03
#define SERIAL_STX 0x02
#define SERIAL_CR  0x0d
#define SERIAL_LF  0x0a
#define SERIAL_SEND_TIMEOUT  6 //3S
#define SERIAL_REC_TIMEOUT   2 //1S
#define SERIAL_REPEAT_MAX    3
#define EXTERNAL_TX_BUFFER_MAX 1000
#define EXTERNAL_RX_BUFFER_MAX 1000
#define TUBE_MAX 96 //2014-8-10项
#define SCAN_DATA_MAX 20 //2014-8-10项
#define INT_DATA_MAX 12 //2014-8-10项
#define CONNECT_RESPONSE_COMMAND_LENGTH 70

#define NEW_PROTOCOL
#define WM_ORIGIN_START (WM_USER+10)
#define WM_ORIGIN_SAVE (WM_USER+11)
#define WM_CALIBRATION (WM_USER+12)
#define WM_INTENSITY_TEST (WM_USER+16)
#define COPYRIGHT_START_X 175
#define COPYRIGHT_START_Y 166
#define COPYRIGHT_END_X COPYRIGHT_START_X + 449
#define COPYRIGHT_END_Y COPYRIGHT_START_Y + 230
#define CALIBRATOR_ABS_MAX 10
#define ABS_CHANNEL_MAX 8

#define SECOND_COMMAND_MAX 13
#define COMMAND_HEAD_LENGTH 20

#define FILE_NAME_MAX 12 //2014-8-10项
#define ABC_CURSOR_HEIGHT 20 //2014-8-10项
#define NUM_CURSOR_HEIGHT 20 //2014-8-10项
#define EDIT_LINE_MAX 100 //2014-8-10项
#define FILE_NUMBER_MAX 1000 //2014-8-10项
#define FILE_NAME_NUMBER_MAX 200 //2014-8-10项

#define SHAKE_HOUR_MAX 99 //2014-8-10项
#define SHAKE_HOUR_MIN 0 //2014-8-10项
#define SHAKE_MINUTE_MAX 59 //2014-8-10项
#define SHAKE_MINUTE_MIN 0 //2014-8-10项
#define SHAKE_SECOND_MAX 59 //2014-8-10项
#define SHAKE_SECOND_MIN 0 //2014-8-10项
#define SHAKE_HOUR_START 126 //2014-8-10项
#define SHAKE_MINUTE_START 156 //2014-8-10项
#define SHAKE_SECOND_START 184 //2014-8-10项
#define SHAKE_TIME_WIDTH 20 //2014-8-10项

#define DATETIME_HOUR_MAX 23 //2014-8-10项
#define DATETIME_HOUR_MIN 0 //2014-8-10项
#define DATETIME_MINUTE_MAX 59 //2014-8-10项
#define DATETIME_MINUTE_MIN 0 //2014-8-10项
#define DATETIME_SECOND_MAX 59 //2014-8-10项
#define DATETIME_SECOND_MIN 0 //2014-8-10项
#define DATETIME_HOUR_START 126 //2014-8-10项
#define DATETIME_MINUTE_START 156 //2014-8-10项
#define DATETIME_SECOND_START 184 //2014-8-10项
#define DATETIME_TIME_WIDTH 20 //2014-8-10项

#define DATETIME_YEAR_MAX 2999 //2014-8-10项
#define DATETIME_YEAR_MIN 2000 //2014-8-10项
#define DATETIME_MONTH_MAX 12 //2014-8-10项
#define DATETIME_MONTH_MIN 1 //2014-8-10项
#define DATETIME_DAY_MAX 31 //2014-8-10项
#define DATETIME_DAY_MIN 1 //2014-8-10项
//#define DATETIME_MONTH_START 126 //2014-8-10项
//#define DATETIME_DAY_START 156 //2014-8-10项
//#define DATETIME_YEAR_START 184 //2014-8-10项
#define DATETIME_YEAR_WIDTH 40 //2014-8-10项

#define PROGRAM_PREPROCESS_START_X 530 //2014-8-10项
#define PROGRAM_KINETIC_START_X 500 //2014-8-10项
#define PROGRAM_CURVES_START_X 500 //2014-8-10项
#define PROGRAM_FUNCTION_AREA_DX 15 //2014-8-10项
#define PROGRAM_FUNCTION_AREA_DY 15 //2014-8-10项
#define CALCULATION_PARA_START_X 103 //2014-8-10项
#define MEASUREMENT_FILTER1_MAX 8 //2014-8-10项
#define MEASUREMENT_FILTER1_MIN 1 //2014-8-10项
#define MEASUREMENT_FILTER2_MAX 8 //2014-8-10项
#define MEASUREMENT_FILTER2_MIN 0 //2014-8-10项
#define PRINT_REPORT_CHAR_MAX 25 //2014-8-10项
#define FILTER_MAX 8 //2014-8-10项
#define CHINESE 1 //2014-8-10项
#define ENGLISH 0 //2014-8-10项
#define SPAIN 2 //2014-8-10项
#define JAPANESE 3 //2014-8-10项
#define LANGUAGE_CHAR_MAX 50 //2014-8-10项
#define INTERPRETDLG_TITLE_CHAR_MAX 32
#define TESTDLG_TITLE_CHAR_MAX 28
#define ABSDLG_TITLE_CHAR_MAX 40
#define PLATE_IN_OUT_CHAR_MAX 40//2014-8-10项
#define KINETIC_SELECT_CHAR_MAX 40//2014-8-10项
#define LANGUAGE_TYPES 4 //2014-8-10项
#define DOOR_CHAR_MAX 10 //2014-8-10项
#define DOOR_STATUS_MAX 2 //2014-8-10项
#define BUTTON_BMP_MAX 100 //2015-2-13
#define RAW_INTENSITY_CHAR_MAX 40 //2014-8-10项
#define RAW_INTENSITY_STATUS_MAX 2 //2014-8-10项

#define PASSWORD_SET_POS_START (320) //2014-8-10项
#define PASSWORD_START 446 //2014-8-10项
#define PASSWORD_WIDTH 62 //2014-8-10项

#define FILTER_LUN_START_BIAS 7 //2014-8-10项
//2015-3-16
#define WAVELENGTH_MAX 780 //2014-8-10项
//#define WAVELENGTH_MIN 380 //2014-8-10项
#define WAVELENGTH_MIN 340 //2015-11-16项
#define FILTER_TEXTBOX_START 5 //2014-8-10项
#define FILTER_TEXTBOX_WIDTH (FILTER_TEXTBOX_START + 50) //2014-8-10项
#define KINETIC_SET_POS_START (320) //2014-8-10项
#define KINETIC_PARA_POS_START (300) //2014-8-10项
#define KINETIC_PARA_BLANK_START (350) //2014-8-10项
#define KINETIC_READINGS_MAX (100) //2014-8-10项
#define KINETIC_READINGS_MIN (2) //2014-8-10项
#define KINETIC_TIME_MIN (7) //2014-8-10项

#define KINETIC_HOUR_MAX 99 //2014-8-10项
#define KINETIC_HOUR_MIN 0 //2014-8-10项
#define KINETIC_MINUTE_MAX 59 //2014-8-10项
#define KINETIC_MINUTE_MIN 0 //2014-8-10项
#define KINETIC_SECOND_MAX 59 //2014-8-10项
#define KINETIC_SECOND_MIN 0 //2014-8-10项
#define KINETIC_HOUR_START 126 //2014-8-10项
#define KINETIC_READINGS_START 126 //2014-8-10项
#define KINETIC_MINUTE_START 154 //2014-8-10项
#define KINETIC_SECOND_START 182 //2014-8-10项
#define KINETIC_TIME_WIDTH 20 //2014-8-10项
#define KINETIC_READINGS_WIDTH 30 //2014-8-10项
#define KINETIC_CHANGE_WIDTH 66 //2014-8-10项

#define ORIGIN_READINGS_START 126 //2015-2-13
#define ORIGIN_READINGS_WIDTH 70 //2015-2-13

#define CALIBRATORS_MAX 12 //2014-8-10项
#define CONTROLS_MAX 9 //2014-8-10项

#define ANALYSIS_MODE_CHAR_MAX 25 //2014-8-19项

#define NORMAL_ANALYSIS_WELL_SERIAL_NUMBER_START (EDIT_START_X+36) //2014-8-19项
#define NORMAL_ANALYSIS_WELL_DATA_START_X (EDIT_START_X+27) //2014-8-19项
#define NORMAL_ANALYSIS_WELL_DATA_START_Y (160) //2014-8-19项
#define NORMAL_ANALYSIS_WELL_SERIAL_ALPHA_START (EDIT_START_X) //2014-8-19项
#define NORMAL_ANALYSIS_WELL_WIDTH_DX (50) //2014-8-19项
#define NORMAL_ANALYSIS_WELL_HEIGHT_DY (35) //2014-8-19项
#define FILTER_PLATE_MAX 2 //2014-8-19项
#define CHANNEL_MAX 9 //2015-09-08项
#define SCAN_CHANNEL_MAX  8 //2015-09-08项

#define ABS_UPPER_LIMIT 5.0 //2014-8-19项
#define ABS_RANGE_MAX 4.0
#define ABS_RANGE_MIN 0.0

#define KINETIC_RAWDATA_SHIFT 10
#define KINETIC_RAWDATA_SHIFT1 25

#define ANALYSIS_FILTER_SELECT_START_X (MAIN_RET_START_X) //2014-8-19项
#define ANALYSIS_FILTER_SELECT_END_X (MAIN_RET_START_X + 121) //2014-8-19项
#define ANALYSIS_FILTER_SELECT_START_Y (MAIN_RET_START_Y - 230) //2014-8-19项
#define ANALYSIS_FILTER_SELECT_END_Y (MAIN_RET_START_Y - 230 + 46) //2014-8-19项

#define ANALYSIS_LOG_SELECT_START_X (MAIN_RET_START_X) //2014-8-19项
#define ANALYSIS_LOG_SELECT_END_X (MAIN_RET_START_X + 121) //2014-8-19项
#define ANALYSIS_LOG_SELECT_START_Y (MAIN_RET_START_Y - 150) //2014-8-19项
#define ANALYSIS_LOG_SELECT_END_Y (MAIN_RET_START_Y - 150 + 46) //2014-8-19项

#define QUALITY_CONC_SELECT_START_X (MAIN_RET_START_X) //2014-8-19项
#define QUALITY_CONC_SELECT_END_X (MAIN_RET_START_X + 121) //2014-8-19项
#define QUALITY_CONC_SELECT_START_Y (MAIN_RET_START_Y - 230) //2014-8-19项
#define QUALITY_CONC_SELECT_END_Y (MAIN_RET_START_Y - 230 + 46) //2014-8-19项

#define QUALITY_CONC_EXPAND_START_X ( QUALITY_CONC_SELECT_START_X - 140) //2014-8-19项
#define QUALITY_OPEN_EXPAND_START_X ( QUALITY_OPEN_SELECT_START_X - 140) //2014-8-19项

#define QUALITY_OPEN_SELECT_START_X (MAIN_RET_START_X) //2014-8-19项
#define QUALITY_OPEN_SELECT_END_X (MAIN_RET_START_X + 121) //2014-8-19项
#define QUALITY_OPEN_SELECT_START_Y (MAIN_RET_START_Y - 160) //2014-8-19项
#define QUALITY_OPEN_SELECT_END_Y (MAIN_RET_START_Y - 160 + 46) //2014-8-19项

#define FRUTE_BUTTON_2_START_X (FRUTE_BUTTON_3_START_X - 100) //2014-8-19项
#define FRUTE_BUTTON_2_START_Y (FRUTE_BUTTON_3_START_Y)
#define FRUTE_BUTTON_2_END_X (FRUTE_BUTTON_3_END_X - 100)
#define FRUTE_BUTTON_2_END_Y (FRUTE_BUTTON_3_END_Y)

#define FRUTE_BUTTON_1_START_X (FRUTE_BUTTON_3_START_X - 200) //2014-8-19项
#define FRUTE_BUTTON_1_START_Y (FRUTE_BUTTON_3_START_Y)
#define FRUTE_BUTTON_1_END_X (FRUTE_BUTTON_3_END_X - 200)
#define FRUTE_BUTTON_1_END_Y (FRUTE_BUTTON_3_END_Y)

#define FRUTE_BUTTON_0_START_X (FRUTE_BUTTON_3_START_X - 300) //2014-8-19项
#define FRUTE_BUTTON_0_START_Y (FRUTE_BUTTON_3_START_Y)
#define FRUTE_BUTTON_0_END_X (FRUTE_BUTTON_3_END_X - 300)
#define FRUTE_BUTTON_0_END_Y (FRUTE_BUTTON_3_END_Y)

#define FRUTE_BUTTON_A_START_X (FRUTE_BUTTON_3_START_X - 400) //2014-8-19项
#define FRUTE_BUTTON_A_START_Y (FRUTE_BUTTON_3_START_Y)
#define FRUTE_BUTTON_A_END_X (FRUTE_BUTTON_3_END_X - 400)
#define FRUTE_BUTTON_A_END_Y (FRUTE_BUTTON_3_END_Y)

#define NORMAL_ANLYSIS_RAWDATA_FILTER_SELECT_WIDTH 230 //2014-8-19项
#define NORMAL_ANLYSIS_RAWDATA_FILTER_SELECT_UNIT_WIDTH 70 //2014-8-19项

#define NORMAL_ANLYSIS_LOG_SELECT_WIDTH 330 //2014-8-19项
#define NORMAL_ANLYSIS_LOG_SELECT_UNIT_WIDTH 80 //2014-8-19项

#define CONCENTRATION_UNIT_SELECT_WIDTH 350 //2014-8-19项
#define CONCENTRATION_UNIT_SELECT_UNIT_WIDTH 50 //2014-8-19项

#define CONCENTRATION_EDIT_TABLE_WIDTH 320 //2014-8-19项
#define CONCENTRATION_EDIT_TABLE_HEIGHT 270 //2014-8-19项

#define CALIBRATOR_CONCENTRATION_MAX 12
#define CALIBRATOR_CONCENTRATION_UNIT_MAX 7
#define CALIBRATOR_CONCENTRATION_UNIT_CHAR_MAX 8

#define TABLE_CONCENTRATION1_COLUMN_NO  23//2014-8-10项
#define TABLE_CONCENTRATION1_COLUMN_CONCENTRATION  120
#define TABLE_CONCENTRATION_WIDTH 311
#define TABLE_CONCENTRATION_SELECT_WIDTH 279
#define TABLE_CONCENTRATION_SELECT_HEIGHT 31
#define TABLE_CONCENTRATION_ROW_HEIGHT 37
#define TABLE_CONCENTRATION2_COLUMN_NO  (TABLE_CONCENTRATION1_COLUMN_NO + TABLE_CONCENTRATION_WIDTH)//2014-8-10项
#define TABLE_CONCENTRATION2_COLUMN_CONCENTRATION  (TABLE_CONCENTRATION1_COLUMN_CONCENTRATION + TABLE_CONCENTRATION_WIDTH)
#define TABLE_CONCENTRATION_ROW_TITLE_START_Y  154//2014-8-10项
#define TABLE_CONCENTRATION_ROW_TITLE_END_Y  196//2014-8-10项
#define ANALYSIS_ERROR_CHAR_MAX 100
#define FILE_ERROR_CHAR_MAX 100
#define SYSTEM_ERROR_CHAR_MAX 100
#define TEST_INFO_CHAR_MAX 400
#define KINETIC_ANALYSIS_CHAR_MAX 100
#define RUN_ERROR_CHAR_MAX 100
#define RX_BUFFER_MAX 1000
#define ANALYSIS_ERROR 1
#define ANALYSIS_CURVE_POINT_MAX 100

#define TABLE_ABS1_COLUMN_NO TABLE_CONCENTRATION1_COLUMN_NO
#define TABLE_ABS1_COLUMN_CAL TABLE_ABS1_COLUMN_NO + 45
#define TABLE_ABS1_COLUMN_PRACTICAL TABLE_ABS1_COLUMN_CAL + 90
#define TABLE_ABS1_COLUMN_ERROR TABLE_ABS1_COLUMN_PRACTICAL + 85
#define TABLE_ABS2_COLUMN_NO TABLE_CONCENTRATION2_COLUMN_NO
#define TABLE_ABS2_COLUMN_CAL TABLE_ABS2_COLUMN_NO + 45
#define TABLE_ABS2_COLUMN_PRACTICAL TABLE_ABS2_COLUMN_CAL + 90
#define TABLE_ABS2_COLUMN_ERROR TABLE_ABS2_COLUMN_PRACTICAL + 85

#define EQUATION_SOLUTION_ERROR 0.0001
#define CONCENTRATION_VALUE_MIN 1e-9
#define EQUATION_SOLUTION_ITERATE_MAX 1000
#define CONCENTRATION_MAX 9.999e+9
#define INTERPRET_COEF_MAX 9.99e+9
#define SPLINE_EXTEND_TIMES 1.0 //2015-8-7

#define MEASURE_TIMEOUT 60 //测量步骤超时 60 //2015-2-20
#define SELFTEST_TIMEOUT 80 //自检步骤超时 80, 测试时为10
#define PLATE_TIMEOUT 20 //板运动步骤超时
#define CALIBRATE_TIMEOUT 20 //校准原点步骤超时
#define INTENSITY_TEST_TIMEOUT 200 //校准原点步骤超时
#define SAVE_TIMEOUT 5 //保存原点数据步骤超时
#define SHAKE_TIMEOUT 20 //振动步骤超时
#define FILTER_TIMEOUT 5 //滤波参数超时
#define INIT_TIMEOUT 80 //初始化超时 80, 测试时为10

#define QC_MAX 9
#define QC_COEF 2
#define QC_PAGE_NUMBER 5
#define QC_PAGES 2

#define INIT_PROGRESS_START_X 305 //332
#define INIT_PROGRESS_START_Y 344 //358
#define INIT_PROGRESS_START_DX 19//14
#define INIT_PROGRESS_START_SIZE 19 //11

#define SYSSET_BK_START_X  0
#define SYSSET_BK_START_Y  122
#define SYSSET_BK_END_X    800
#define SYSSET_BK_END_Y    436

#define MACHINE_BUSY 1
#define MACHINE_CONNECT_ALREADY 2
#define MACHINE_NAK 3

enum CommandPADStatus
{
	COMMAND_INVALID_PAD,
	COMMAND_CONNECT_PAD,
	COMMAND_RUN_PAD,
	COMMAND_STOP_PAD,
	COMMAND_UNCONNECT_PAD,
	COMMAND_NEXT_PLATE_PAD,
	COMMAND_PHOTOMETRIC_PAD,
	COMMAND_PLATEOUT_PAD,
	COMMAND_SHAKE_PAD,
	COMMAND_PLATEIN_PAD,
	COMMAND_KINETIC_PAD,
	COMMAND_ACK_PAD,
	COMMAND_NAK_PAD,
	COMMAND_RESPONSE_PAD
}; //PC/PAD

enum CommandResponse
{
    COMMAND_NONE,
    COMMAND_ACK,
    COMMAND_NAK,
    COMMAND_CONNECT_RESPONSE,
    COMMAND_PHOTOMETRIC_RESPONSE,
    COMMAND_PLATEIN_RESPONSE,
    COMMAND_PLATEOUT_RESPONSE,
    COMMAND_SHAKE_RESPONSE,
    COMMAND_UNCONNECT,
    COMMAND_ABS_DATA,
    COMMAND_PLATE,
	COMMAND_ERROR,
    COMMAND_KINETIC_RESPONSE
};

enum AnalysisMode
{
	ANALYSIS_MODE_RAWDATA = 0,
    ANALYSIS_MODE_INTERPRET,
    ANALYSIS_MODE_ANALYSIS,
    ANALYSIS_MODE_CURVE,
	ANALYSIS_MODE_QC,
    ANALYSIS_MODE_MAX
};

enum KineticAnalysis
{
    KINETIC_ANALYSIS_AVERAGE_RATE = 0,
    KINETIC_ANALYSIS_MAX_RATE,
    KINETIC_ANALYSIS_TIME_MAX_RATE,
    KINETIC_ANALYSIS_TIME_CHANGE,
    KINETIC_ANALYSIS_MAX_WELL,
    KINETIC_ANALYSIS_TIME_MAX,
    KINETIC_ANALYSIS_MAX,
    KINETIC_ANALYSIS_NONE
};

enum AnalysisError
{
    ANALYSIS_SUCCESS = 0,
    ANALYSIS_ERROR_CALIBRATOR_NUMBER,
    ANALYSIS_ERROR_FITTING_FAIL,
    ANALYSIS_ERROR_LOGX_FAIL,
    ANALYSIS_ERROR_LOGY_FAIL,
    ANALYSIS_ERROR_DISABLE_CONCENTRATION,
    ANALYSIS_ERROR_DISABLE_LOG_CONCENTRATION,
    ANALYSIS_ERROR_LOG_CONCENTRATION,
	ANALYSIS_ERROR_ABS_NEGATIVE,
    ANALYSIS_ERROR_NO_NC,
    ANALYSIS_ERROR_NO_PC,
    ANALYSIS_ERROR_NO_CONCENTRATION,
    ANALYSIS_ERROR_NO_QC,
    ANALYSIS_ERROR_NO_QC_RESULT,
	ANALYSIS_ERROR_KINETIC_DATA,
    ANALYSIS_ERROR_MAX
};

enum SystemError
{
    SYSTEM_ERROR_WHEEL = 0,
    SYSTEM_ERROR_FRONT,
    SYSTEM_ERROR_REAR,
    SYSTEM_ERROR_EEPROM,
    SYSTEM_ERROR_ORIGIN,
    SYSTEM_ERROR_INTENSITY_WEAK,
    SYSTEM_ERROR_INTENSITY_WEAKER,
    SYSTEM_ERROR_INTENSITY_STRONG,
    SYSTEM_ERROR_BACKGROUND_STRONG,
    SYSTEM_ERROR_FILTER_DATA,
    SYSTEM_ERROR_INTENSITY_DATA,
    SYSTEM_ERROR_MAX
};

enum TestInfo
{
    TEST_INFO_SCAN_DATA = 0,
    TEST_INFO_USB_ERROR,
    TEST_INFO_INTENSITY_DATA,
    TEST_INFO_MAX
};

enum FileError
{
	FILE_ERROR_OPEN = 0,
    FILE_ERROR_DELETE,
    FILE_ERROR_DISK,
    FILE_ERROR_IMPORT,
    FILE_ERROR_EXPORT,
    FILE_ERROR_NO_DELETE,
	FILE_ERROR_NO_OPEN,
    FILE_ERROR_DISK_MODE,
    FILE_ERROR_FLASH_MODE,
    FILE_ERROR_OVERWRITE,
	FILE_ERROR_SAVE,
    FILE_ERROR_OPENED,
    FILE_ERROR_MAX
};

enum FrontKeyType
{
    KEY_NONE = 0,
    KEY_PLATE_IN_OUT = 88,
    KEY_STOP = 83,
    KEY_START = 67
};

enum RunMode
{
    RUN_MODE_IDLE = 0,
    RUN_MODE_PLATE_IN,
    RUN_MODE_PLATE_OUT,
    RUN_MODE_STOP,
    RUN_MODE_MEASURE,
    RUN_MODE_SHAKE,
    RUN_MODE_SELFTEST,
    RUN_MODE_FILTER,
    RUN_MODE_CALIBRATE_ORIGIN,
    RUN_MODE_SAVE_ORIGIN,
    RUN_MODE_INTENSITY_TEST,
	RUN_MODE_MAX
};

enum CpuCommand
{
    CPU_COMMAND_NONE = 0,
	CPU_COMMAND_MEASURE,
    CPU_COMMAND_INTENSITY_SET,
    CPU_COMMAND_FAN,
    CPU_COMMAND_STOP,
	CPU_COMMAND_PLATE_OUT = 4, //发给下位机的命令
    CPU_COMMAND_PLATE_IN,
    CPU_COMMAND_INCUBATION,
	CPU_COMMAND_READ_TEMP,
	CPU_COMMAND_SHAKE_NONE,
	CPU_COMMAND_EEPROM,
	CPU_COMMAND_FILTER_ORIGIN,
	CPU_COMMAND_CALIBRATE_ORIGIN,
	CPU_COMMAND_SAVE_ORIGIN,
	CPU_COMMAND_SHAKE,
	CPU_COMMAND_SELFTEST,
	CPU_COMMAND_FILTER,
	CPU_COMMAND_REPEAT,
	CPU_COMMAND_MAX
};

enum CpuResponse
{
	CPU_RESPONSE_NONE = 0,
	CPU_RESPONSE_COMMAND,
	CPU_RESPONSE_TEMP,
	CPU_RESPONSE_INTENSITY_ONE,
	CPU_RESPONSE_INTENSITY_TWO, //下位机的响应
	CPU_RESPONSE_END,
	CPU_RESPONSE_ORIGIN,
	CPU_RESPONSE_ERROR_CODE,
	CPU_RESPONSE_SCAN_DATA,
	CPU_RESPONSE_INTENSITY_DATA,
	CPU_RESPONSE_STOP_END,
	CPU_RESPONSE_MAX
};

struct CONNECT_RESPONSE_DATA
{
	Integer nConnFlag;
	Integer nReason;
	ByteArray cMachineSerial;
	Integer nWaveLength[8];

	CONNECT_RESPONSE_DATA() : nConnFlag(0), nReason(0), cMachineSerial(ByteArray(8, 0))
	{
		ZeroMemory((LPVOID)nWaveLength, sizeof(nWaveLength));
	}
};

inline std::ostream& operator <<(std::ostream& ds, const CONNECT_RESPONSE_DATA& crd)
{
	ds.write((LPCSTR)&crd.nConnFlag, sizeof(crd.nConnFlag));
	ds.write((LPCSTR)&crd.nReason, sizeof(crd.nReason));
	ds.write((LPCSTR)&crd.cMachineSerial, sizeof(crd.cMachineSerial));

	ds.write((LPCSTR)&crd.nWaveLength, sizeof(crd.nWaveLength));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, CONNECT_RESPONSE_DATA& crd)
{
	ds.read((LPSTR)&crd.nConnFlag, sizeof(crd.nConnFlag));
	ds.read((LPSTR)&crd.nReason, sizeof(crd.nReason));
	ds.read((LPSTR)&crd.cMachineSerial, sizeof(crd.cMachineSerial));

	ds.read((LPSTR)&crd.nWaveLength, sizeof(crd.nWaveLength));

	return ds;
}

struct PAD_TYPE
{
	Integer nType1;
	Integer nType2;

	PAD_TYPE() : nType1(0), nType2(0) {}
};

inline std::ostream& operator <<(std::ostream& ds, const PAD_TYPE& pt)
{
	ds.write((LPCSTR)&(pt.nType1), sizeof(pt.nType1));
	ds.write((LPCSTR)&(pt.nType2), sizeof(pt.nType2));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, PAD_TYPE& pt)
{
	ds.read((LPSTR)&(pt.nType1), sizeof(pt.nType1));
	ds.read((LPSTR)&(pt.nType2), sizeof(pt.nType2));

	return ds;
}

struct PHOTOMETRIC_PARA
{
	Integer nPlateCount;
	Integer nPos1;
	Integer nPos2;
	Integer nMode;

	Integer nFlag;
	Integer nSpeed;
	Integer nTime;

	PHOTOMETRIC_PARA() : nPlateCount(0), nPos1(0), nPos2(0), nMode(0),
						 nFlag(0), nSpeed(0), nTime(0) {}
};

inline std::ostream& operator <<(std::ostream& ds, const PHOTOMETRIC_PARA& php)
{
	ds.write((LPCSTR)&php.nPlateCount, sizeof(php.nPlateCount));
	ds.write((LPCSTR)&php.nPos1, sizeof(php.nPos1));
	ds.write((LPCSTR)&php.nPos2, sizeof(php.nPos2));
	ds.write((LPCSTR)&php.nMode, sizeof(php.nMode));
	ds.write((LPCSTR)&php.nFlag, sizeof(php.nFlag));
	ds.write((LPCSTR)&php.nSpeed, sizeof(php.nSpeed));
	ds.write((LPCSTR)&php.nTime, sizeof(php.nTime));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, PHOTOMETRIC_PARA& php)
{
	ds.read((LPSTR)&php.nPlateCount, sizeof(php.nPlateCount));
	ds.read((LPSTR)&php.nPos1, sizeof(php.nPos1));
	ds.read((LPSTR)&php.nPos2, sizeof(php.nPos2));
	ds.read((LPSTR)&php.nMode, sizeof(php.nMode));
	ds.read((LPSTR)&php.nFlag, sizeof(php.nFlag));
	ds.read((LPSTR)&php.nSpeed, sizeof(php.nSpeed));
	ds.read((LPSTR)&php.nTime, sizeof(php.nTime));

	return ds;
}
struct KINETIC_PARA_PAD
{
    Integer nCycles;
    Integer nInterval;
    Integer nPlateCount;
    Integer nPos1;
    Integer nPos2;

    Integer nFlag;
    Integer nSpeed;
	Integer nTime;

    KINETIC_PARA_PAD() : nCycles(0), nInterval(0), nPlateCount(0), nPos1(0), nPos2(0),
                         nFlag(0), nSpeed(0), nTime(0) {}
};

inline std::ostream& operator <<(std::ostream& ds, const KINETIC_PARA_PAD& kpp)
{
	ds.write((LPCSTR)&kpp.nCycles, sizeof(kpp.nCycles));
	ds.write((LPCSTR)&kpp.nInterval, sizeof(kpp.nInterval));
	ds.write((LPCSTR)&kpp.nPlateCount, sizeof(kpp.nPlateCount));
	ds.write((LPCSTR)&kpp.nPos1, sizeof(kpp.nPos1));
	ds.write((LPCSTR)&kpp.nPos2, sizeof(kpp.nPos2));
	ds.write((LPCSTR)&kpp.nFlag, sizeof(kpp.nFlag));
	ds.write((LPCSTR)&kpp.nSpeed, sizeof(kpp.nSpeed));
	ds.write((LPCSTR)&kpp.nTime, sizeof(kpp.nTime));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, KINETIC_PARA_PAD& kpp)
{
	ds.read((LPSTR)&kpp.nCycles, sizeof(kpp.nCycles));
	ds.read((LPSTR)&kpp.nInterval, sizeof(kpp.nInterval));
	ds.read((LPSTR)&kpp.nPlateCount, sizeof(kpp.nPlateCount));
	ds.read((LPSTR)&kpp.nPos1, sizeof(kpp.nPos1));
	ds.read((LPSTR)&kpp.nPos2, sizeof(kpp.nPos2));
	ds.read((LPSTR)&kpp.nFlag, sizeof(kpp.nFlag));
	ds.read((LPSTR)&kpp.nSpeed, sizeof(kpp.nSpeed));
	ds.read((LPSTR)&kpp.nTime, sizeof(kpp.nTime));

    return ds;
}

struct ABS_DATA_PARA
{
    Integer nPlateNumber;
	Integer nCycle;
	Integer nFilters;

	Single fABS[2][TUBE_MAX];

	ABS_DATA_PARA() : nPlateNumber(0), nCycle(0), nFilters(0)
	{
		ZeroMemory((LPVOID)fABS, sizeof(fABS));
	}
};

inline std::ostream& operator <<(std::ostream& ds, const ABS_DATA_PARA& adp)
{
	ds.write((LPCSTR)&adp.nPlateNumber, sizeof(adp.nPlateNumber));
	ds.write((LPCSTR)&adp.nCycle, sizeof(adp.nCycle));
	ds.write((LPCSTR)&adp.nFilters, sizeof(adp.nFilters));

	for (int i = 0; i < 2; i++)
		ds.write((LPCSTR)adp.fABS[i], sizeof(adp.fABS[i]));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, ABS_DATA_PARA& adp)
{
	ds.read((LPSTR)&adp.nPlateNumber, sizeof(adp.nPlateNumber));
	ds.read((LPSTR)&adp.nCycle, sizeof(adp.nCycle));
	ds.read((LPSTR)&adp.nFilters, sizeof(adp.nFilters));


	for (int i = 0; i < 2; i++)
		ds.read((LPSTR)adp.fABS[i], sizeof(adp.fABS[i]));

	return ds;
}

struct COMM_STATUS
{
	Integer nCurrentCommand;
	Integer nRepeatNo;
	Integer nSendTimeoutNo;
	Integer nRecTimeoutNo;
	BOOL   bCommandSent;
	BOOL   bReceiving;
	Integer nRecBufferPoint;
	BOOL   bAcknowledged;
	Integer nCommandLength;

	COMM_STATUS() : nCurrentCommand(0), nRepeatNo(0), nSendTimeoutNo(0), nRecTimeoutNo(0),
					bCommandSent(FALSE), bReceiving(FALSE), nRecBufferPoint(0), bAcknowledged(FALSE),
					nCommandLength(0) {}
};

inline std::ostream& operator <<(std::ostream& ds, const COMM_STATUS& cs)
{
	ds.write((LPCSTR)&cs.nCurrentCommand, sizeof(cs.nCurrentCommand));
	ds.write((LPCSTR)&cs.nRepeatNo, sizeof(cs.nRepeatNo));
	ds.write((LPCSTR)&cs.nSendTimeoutNo, sizeof(cs.nSendTimeoutNo));
	ds.write((LPCSTR)&cs.nRecTimeoutNo, sizeof(cs.nRecTimeoutNo));
	ds.write((LPCSTR)&cs.bCommandSent, sizeof(cs.bCommandSent));
	ds.write((LPCSTR)&cs.bReceiving, sizeof(cs.bReceiving));
	ds.write((LPCSTR)&cs.nRecBufferPoint, sizeof(cs.nRecBufferPoint));
	ds.write((LPCSTR)&cs.bAcknowledged, sizeof(cs.bAcknowledged));
	ds.write((LPCSTR)&cs.nCommandLength, sizeof(cs.nCommandLength));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, COMM_STATUS& cs)
{
	ds.read((LPSTR)&cs.nCurrentCommand, sizeof(cs.nCurrentCommand));
	ds.read((LPSTR)&cs.nRepeatNo, sizeof(cs.nRepeatNo));
	ds.read((LPSTR)&cs.nSendTimeoutNo, sizeof(cs.nSendTimeoutNo));
	ds.read((LPSTR)&cs.nRecTimeoutNo, sizeof(cs.nRecTimeoutNo));
	ds.read((LPSTR)&cs.bCommandSent, sizeof(cs.bCommandSent));
	ds.read((LPSTR)&cs.bReceiving, sizeof(cs.bReceiving));
	ds.read((LPSTR)&cs.nRecBufferPoint, sizeof(cs.nRecBufferPoint));
	ds.read((LPSTR)&cs.bAcknowledged, sizeof(cs.bAcknowledged));
	ds.read((LPSTR)&cs.nCommandLength, sizeof(cs.nCommandLength));

	return ds;
}

struct INTERPRET_PARA
{
    Boolean bOpened;
    Boolean bABS;
    Double dCoef[3];
    Double dGreyValue;
    Boolean bGreater;
    Integer nTotalNC[3];
	Integer nTotalPC[3];
	Double dReferenceNC[3];
	Double dReferencePC[3];
	Double dReference[3];
	Integer nAnalysisResult[3];
    Boolean bWeakPos[3][TUBE_MAX];
	Boolean bPos[3][TUBE_MAX];

    INTERPRET_PARA() : bOpened(false), bABS(false), dGreyValue(0), bGreater(0)
    {
        ZeroMemory((LPVOID)dCoef, sizeof(dCoef));
        ZeroMemory((LPVOID)nTotalNC, sizeof(nTotalNC));
        ZeroMemory((LPVOID)nTotalPC, sizeof(nTotalPC));
        ZeroMemory((LPVOID)dReferenceNC, sizeof(dReferenceNC));
        ZeroMemory((LPVOID)dReferencePC, sizeof(dReferencePC));
        ZeroMemory((LPVOID)dReference, sizeof(dReference));
        ZeroMemory((LPVOID)nAnalysisResult, sizeof(nAnalysisResult));
        ZeroMemory((LPVOID)bWeakPos, sizeof(bWeakPos));
        ZeroMemory((LPVOID)bPos, sizeof(bPos));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const INTERPRET_PARA& ip)
{
	ds.write((LPCSTR)&ip.bOpened, sizeof(ip.bOpened));
	ds.write((LPCSTR)&ip.bABS, sizeof(ip.bABS));
	ds.write((LPCSTR)&ip.dCoef, sizeof(ip.dCoef));
	ds.write((LPCSTR)&ip.dGreyValue, sizeof(ip.dGreyValue));
	ds.write((LPCSTR)&ip.nTotalNC, sizeof(ip.nTotalNC));
    ds.write((LPCSTR)&ip.nTotalPC, sizeof(ip.nTotalPC));
    ds.write((LPCSTR)&ip.dReferenceNC, sizeof(ip.dReferenceNC));
	ds.write((LPCSTR)&ip.dReferencePC, sizeof(ip.dReferencePC));
    ds.write((LPCSTR)&ip.dReference, sizeof(ip.dReference));
    ds.write((LPCSTR)&ip.nAnalysisResult, sizeof(ip.nAnalysisResult));

    for (int i = 0; i < 3; i++)
        ds.write((LPCSTR)&ip.bWeakPos[i], sizeof(ip.bWeakPos[i]));

    for (int i = 0; i < 3; i++)
        ds.write((LPCSTR)&ip.bPos[i], sizeof(ip.bPos[i]));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, INTERPRET_PARA& ip)
{
	ds.read((LPSTR)&ip.bOpened, sizeof(ip.bOpened));
	ds.read((LPSTR)&ip.bABS, sizeof(ip.bABS));
	ds.read((LPSTR)&ip.dCoef, sizeof(ip.dCoef));
	ds.read((LPSTR)&ip.dGreyValue, sizeof(ip.dGreyValue));
	ds.read((LPSTR)&ip.nTotalNC, sizeof(ip.nTotalNC));
	ds.read((LPSTR)&ip.nTotalPC, sizeof(ip.nTotalPC));
	ds.read((LPSTR)&ip.dReferenceNC, sizeof(ip.dReferenceNC));
	ds.read((LPSTR)&ip.dReferencePC, sizeof(ip.dReferencePC));
	ds.read((LPSTR)&ip.dReference, sizeof(ip.dReference));
	ds.read((LPSTR)&ip.nAnalysisResult, sizeof(ip.nAnalysisResult));

	for (int i = 0; i < 3; i++)
		ds.read((LPSTR)&ip.bWeakPos, sizeof(ip.bWeakPos));

	for (int i = 0; i < 3; i++)
		ds.read((LPSTR)&ip.bPos, sizeof(ip.bPos));

	return ds;
}

struct QUALITY_PARA
{
    Boolean   bOpened;
    Boolean   bABS;
    Double  dSD[3][QC_MAX];
    Double  dTarget[2][QC_MAX];
    Double  dUpperLimit[2][QC_MAX];
    Double  dLowerLimit[2][QC_MAX];
    Double  dCV[3][QC_MAX];
    Boolean   bFailed[3][QC_MAX];
    Integer nTotalQC[3][QC_MAX];
    Integer nTotal[3];
	Double  dReferenceQC[3][QC_MAX];
	Boolean   bReferenceOK[3][QC_MAX];
    Integer nAnalysisResult[3];
    Integer nCurrentSelect;
    Integer nCurrentSelectPage;
    Integer nCurrentPage;
    Integer nCurrentPageAnalysis;
	Integer nPageTotalAnalysis;

    QUALITY_PARA() : bOpened(false), bABS(false), nCurrentSelect(0), nCurrentSelectPage(0), nCurrentPage(0),
                     nCurrentPageAnalysis(0), nPageTotalAnalysis(0)
    {
        ZeroMemory((LPVOID)dSD, sizeof(dSD));
        ZeroMemory((LPVOID)dTarget, sizeof(dTarget));
        ZeroMemory((LPVOID)dUpperLimit, sizeof(dUpperLimit));
        ZeroMemory((LPVOID)dLowerLimit, sizeof(dLowerLimit));
        ZeroMemory((LPVOID)dCV, sizeof(dCV));
        ZeroMemory((LPVOID)bFailed, sizeof(bFailed));
        ZeroMemory((LPVOID)nTotalQC, sizeof(nTotalQC));
        ZeroMemory((LPVOID)nTotal, sizeof(nTotal));
        ZeroMemory((LPVOID)dReferenceQC, sizeof(dReferenceQC));
        ZeroMemory((LPVOID)bReferenceOK, sizeof(bReferenceOK));
        ZeroMemory((LPVOID)nAnalysisResult, sizeof(nAnalysisResult));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const QUALITY_PARA& qp)
{
	ds.write((LPCSTR)&qp.bOpened, sizeof(qp.bOpened));
	ds.write((LPCSTR)&qp.bABS, sizeof(qp.bABS));

	for (int i = 0; i < 3; i++)
		ds.write((LPCSTR)&qp.dSD[i], sizeof(qp.dSD[i]));

	for (int i = 0; i < 2; i++)
		ds.write((LPCSTR)&qp.dTarget[i], sizeof(qp.dTarget[i]));

    for (int i = 0; i < 2; i++)
        ds.write((LPCSTR)&qp.dUpperLimit[i], sizeof(qp.dUpperLimit[i]));

    for (int i = 0; i < 2; i++)
        ds.write((LPCSTR)&qp.dLowerLimit[i], sizeof(qp.dLowerLimit[i]));

    for (int i = 0; i < 3; i++)
        ds.write((LPCSTR)&qp.dCV[i], sizeof(qp.dCV[i]));

    for (int i = 0; i < 3; i++)
        ds.write((LPCSTR)&qp.bFailed[i], sizeof(qp.bFailed[i]));

    for (int i = 0; i < 3; i++)
		ds.write((LPCSTR)&qp.dReferenceQC[i], sizeof(qp.dReferenceQC[i]));

    for (int i = 0; i < 3; i++)
        ds.write((LPCSTR)&qp.bReferenceOK, sizeof(qp.bReferenceOK));

    ds.write((LPCSTR)qp.nAnalysisResult, sizeof(qp.nAnalysisResult));
	ds.write((LPCSTR)&qp.nCurrentSelect, sizeof(qp.nCurrentSelect));
	ds.write((LPCSTR)&qp.nCurrentSelectPage, sizeof(qp.nCurrentSelectPage));
	ds.write((LPCSTR)&qp.nCurrentPage, sizeof(qp.nCurrentPage));
	ds.write((LPCSTR)&qp.nCurrentPageAnalysis, sizeof(qp.nCurrentPageAnalysis));
	ds.write((LPCSTR)&qp.nPageTotalAnalysis, sizeof(qp.nPageTotalAnalysis));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, QUALITY_PARA& qp)
{
	ds.read((LPSTR)qp.bOpened, sizeof(qp.bOpened));
	ds.read((LPSTR)qp.bABS, sizeof(qp.bABS));

	for (int i = 0; i < 3; i++)
		ds.read((LPSTR)&qp.dSD[i], sizeof(qp.dSD[i]));

	for (int i = 0; i < 2; i++)
		ds.read((LPSTR)&qp.dTarget[i], sizeof(qp.dTarget[i]));

	for (int i = 0; i < 2; i++)
		ds.read((LPSTR)&qp.dUpperLimit[i], sizeof(qp.dUpperLimit[i]));

	for (int i = 0; i < 2; i++)
		ds.read((LPSTR)&qp.dLowerLimit[i], sizeof(qp.dLowerLimit[i]));

	for (int i = 0; i < 3; i++)
		ds.read((LPSTR)&qp.dCV[i], sizeof(qp.dCV[i]));

	for (int i = 0; i < 3; i++)
		ds.read((LPSTR)&qp.bFailed[i], sizeof(qp.bFailed[i]));

	for (int i = 0; i < 3; i++)
		ds.read((LPSTR)&qp.dReferenceQC[i], sizeof(qp.dReferenceQC[i]));

	for (int i = 0; i < 3; i++)
		ds.read((LPSTR)&qp.bReferenceOK, sizeof(qp.bReferenceOK));

	ds.read((LPSTR)qp.nAnalysisResult, sizeof(qp.nAnalysisResult));

	ds.read((LPSTR)&qp.nCurrentSelect, sizeof(qp.nCurrentSelect));
	ds.read((LPSTR)&qp.nCurrentSelectPage, sizeof(qp.nCurrentSelectPage));
	ds.read((LPSTR)&qp.nCurrentPage, sizeof(qp.nCurrentPage));
	ds.read((LPSTR)&qp.nCurrentPageAnalysis, sizeof(qp.nCurrentPageAnalysis));
	ds.read((LPSTR)&qp.nPageTotalAnalysis, sizeof(qp.nPageTotalAnalysis));

	return ds;
}

struct FILE_SEL
{
	Boolean bSelected[FILE_NUMBER_MAX];
	Boolean bHardDisk;
	Boolean bDelete;
	Boolean bConfirmed;
	Boolean bOverwrite;

	FILE_SEL() : bHardDisk(false), bDelete(false), bConfirmed(false), bOverwrite(false)
	{
		ZeroMemory((LPVOID)bSelected, sizeof(bSelected));
	}
};

inline std::ostream& operator <<(std::ostream& ds, const FILE_SEL& fs)
{
	ds.write((LPCSTR)&fs.bSelected, sizeof(fs.bSelected));
	ds.write((LPCSTR)&fs.bHardDisk, sizeof(fs.bHardDisk));
	ds.write((LPCSTR)&fs.bDelete, sizeof(fs.bDelete));
	ds.write((LPCSTR)&fs.bConfirmed, sizeof(fs.bConfirmed));
	ds.write((LPCSTR)&fs.bOverwrite, sizeof(fs.bOverwrite));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, FILE_SEL& fs)
{
	ds.read((LPSTR)&fs.bSelected, sizeof(fs.bSelected));
	ds.read((LPSTR)&fs.bHardDisk, sizeof(fs.bHardDisk));
	ds.read((LPSTR)&fs.bDelete, sizeof(fs.bDelete));
	ds.read((LPSTR)&fs.bConfirmed, sizeof(fs.bConfirmed));
	ds.read((LPSTR)&fs.bOverwrite, sizeof(fs.bOverwrite));

	return ds;
}

struct ABS_CAL
{
    Double dABS[CALIBRATOR_ABS_MAX];
    Double dABSPractical[CALIBRATOR_ABS_MAX];
	Double dABSError[CALIBRATOR_ABS_MAX];
	Integer nCount[CALIBRATOR_ABS_MAX];

    ABS_CAL() {
        ZeroMemory((LPVOID)dABS, sizeof(dABS));
        ZeroMemory((LPVOID)dABSPractical, sizeof(dABSPractical));
        ZeroMemory((LPVOID)dABSError, sizeof(dABSError));
        ZeroMemory((LPVOID)nCount, sizeof(nCount));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const ABS_CAL& ac)
{
	ds.write((LPCSTR)&ac.dABS, sizeof(ac.dABS));
    ds.write((LPCSTR)&ac.dABSPractical, sizeof(ac.dABSPractical));
    ds.write((LPCSTR)&ac.dABSError, sizeof(ac.dABSError));
    ds.write((LPCSTR)&ac.nCount, sizeof(ac.nCount));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, ABS_CAL& ac)
{
    ds.read((LPSTR)&ac.dABS, sizeof(ac.dABS));
    ds.read((LPSTR)&ac.dABSPractical, sizeof(ac.dABSPractical));
    ds.read((LPSTR)&ac.dABSError, sizeof(ac.dABSError));
    ds.read((LPSTR)&ac.nCount, sizeof(ac.nCount));

    return ds;
}

struct ABS_CAL_PARA
{
    Double dABS[2][CALIBRATOR_ABS_MAX];
	Double dABSError[2][CALIBRATOR_ABS_MAX];
	Integer nCount[2];

    ABS_CAL_PARA()
    {
        ZeroMemory((LPVOID)&dABS, sizeof(dABS));
        ZeroMemory((LPVOID)&dABSError, sizeof(dABSError));
        ZeroMemory((LPVOID)&nCount, sizeof(nCount));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const ABS_CAL_PARA& acp)
{
    ds.write((LPCSTR)&acp.dABS, sizeof(acp.dABS));
    ds.write((LPCSTR)&acp.dABSError, sizeof(acp.dABSError));
	ds.write((LPCSTR)&acp.nCount, sizeof(acp.nCount));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, ABS_CAL_PARA& acp)
{
    ds.read((LPSTR)&acp.dABS, sizeof(acp.dABS));
    ds.read((LPSTR)&acp.dABSError, sizeof(acp.dABSError));
    ds.read((LPSTR)&acp.nCount, sizeof(acp.nCount));

    return ds;
}

struct FILTERLUN
{
	AnsiChar filter[FILTER_MAX][10];
	AnsiChar filter_temp[FILTER_MAX][10];
	AnsiChar curentfilter[10];
	Boolean  Ena;

	FILTERLUN() : Ena(False)
	{
		ZeroMemory(filter, sizeof(filter));
		ZeroMemory(filter_temp, sizeof(filter_temp));
		ZeroMemory(curentfilter, sizeof(curentfilter));
	}

	inline void operator = (const FILTERLUN& rhs)
	{
		ZeroMemory(filter, sizeof(filter));
		ZeroMemory(filter_temp, sizeof(filter_temp));
		ZeroMemory(curentfilter, sizeof(curentfilter));

		for (Integer i = 0; i < FILTER_MAX; i++)
		{
			strncpy(filter[i], rhs.filter[i], strlen(rhs.filter[i]));
			strncpy(filter_temp[i], rhs.filter_temp[i], strlen(rhs.filter_temp[i]));
		}

		strncpy(curentfilter, rhs.curentfilter, strlen(curentfilter));

		Ena = rhs.Ena;
	}
};

inline std::ostream& operator <<(std::ostream& mf, const FILTERLUN& fl)
{
	ByteArrayList filtersList;

	for (size_t i = 0; i < FILTER_MAX; i++)
		filtersList.push_back(std::string(fl.filter[i]));

	for (size_t i = 0; i < FILTER_MAX; i++)
		filtersList.push_back(std::string(fl.filter_temp[i]));

	filtersList.push_back(std::string(fl.curentfilter));

	ByteArray filtersJoined = loccus::join(filtersList, ";");

	mf << filtersJoined << std::string(";") << std::boolalpha << fl.Ena;

	return mf;
}

inline std::istream& operator >>(std::istream& mf, FILTERLUN& fl)
{
	ByteArray filtersJoined(1024, 0);

	mf >> filtersJoined;

	ByteArrayList filterList = loccus::split(filtersJoined, ";");

	ByteArrayList::const_iterator cflIt = filterList.begin();

	for (Integer i = 0; i < FILTER_MAX; i++, cflIt++)
		std::strncpy_s(fl.filter[i], sizeof(fl.filter[i]), cflIt->c_str(), cflIt->length());

	for (Integer i = 0; i < FILTER_MAX; i++, cflIt++)
		std::strncpy_s(fl.filter_temp[i], sizeof(fl.filter_temp[i]), cflIt->c_str(), cflIt->length());

	std::strncpy_s(fl.curentfilter, sizeof(fl.curentfilter), cflIt->c_str(), cflIt->length());

	cflIt++;

	fl.Ena = Boolean(cflIt->substr(0, 4) == "true");

	return mf;
}

struct SYS_PARA
{
	AnsiChar wcFilterWavelength[FILTER_MAX][10];
    Boolean bHeader;
    AnsiChar wcHeader[PRINT_REPORT_CHAR_MAX + 1];
    AnsiChar wcLanguage;
    Boolean bDoorOpen;
    QUALITY_PARA quality_para;
    Integer nOrigin;
    ABS_CAL abs_cal[ABS_CHANNEL_MAX];
	Integer nChannelCurrent;
	Boolean bNotCalibrate;

	SYS_PARA() : bHeader(false), wcLanguage(0), bDoorOpen(false), quality_para(QUALITY_PARA()),
				 nOrigin(0), nChannelCurrent(0), bNotCalibrate(false)
	{
		ZeroMemory((LPVOID)wcFilterWavelength, sizeof(wcFilterWavelength));
		ZeroMemory((LPVOID)wcHeader, sizeof(wcHeader));
		ZeroMemory((LPVOID)abs_cal, sizeof(abs_cal));
	}
};

inline std::ostream& operator <<(std::ostream& ds, const SYS_PARA& sp)
{
	for (int i = 0; i < FILTER_MAX; i++)
		ds.write((LPCSTR)&sp.wcFilterWavelength[i], sizeof(sp.wcFilterWavelength[i]));

	ds.write((LPCSTR)&sp.bHeader, sizeof(sp.bHeader));

	for (int i = 0; i < PRINT_REPORT_CHAR_MAX+1; i++)
		ds.write((LPCSTR)&sp.wcHeader, sizeof(sp.wcHeader[i]));

	ds.write((LPCSTR)&sp.wcLanguage, sizeof(sp.wcLanguage));
	ds.write((LPCSTR)&sp.bDoorOpen, sizeof(sp.bDoorOpen));

	ds << sp.quality_para;

	ds.write((LPCSTR)&sp.nOrigin, sizeof(sp.nOrigin));

	for (int i = 0; i < ABS_CHANNEL_MAX; i++)
		ds << sp.abs_cal[i];

	ds.write((LPCSTR)&sp.nChannelCurrent, sizeof(sp.nChannelCurrent));
	ds.write((LPCSTR)&sp.bNotCalibrate, sizeof(sp.bNotCalibrate));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, SYS_PARA& sp)
{
	for (int i = 0; i < FILTER_MAX; i++)
		ds.read((LPSTR)&sp.wcFilterWavelength[i], sizeof(sp.wcFilterWavelength[i]));

	ds.read((LPSTR)&sp.bHeader, sizeof(sp.bHeader));

	for (int i = 0; i < PRINT_REPORT_CHAR_MAX+1; i++)
		ds.read((LPSTR)&sp.wcHeader[i], sizeof(sp.wcHeader[i]));

	ds.read((LPSTR)&sp.wcLanguage, sizeof(sp.wcLanguage));
	ds.read((LPSTR)&sp.bDoorOpen, sizeof(sp.bDoorOpen));
	ds >> sp.quality_para;

	ds.read((LPSTR)&sp.nOrigin, sizeof(sp.nOrigin));

	for (int i = 0; i < ABS_CHANNEL_MAX; i++)
		ds >> sp.abs_cal[i];

	ds.read((LPSTR)&sp.nChannelCurrent, sizeof(sp.nChannelCurrent));
	ds.read((LPSTR)&sp.bNotCalibrate, sizeof(sp.bNotCalibrate));

	return ds;
}

struct LINEAR_ANALYSIS
{
	Double dSlope;
	Double dIntercept;
	Double dRR;

	LINEAR_ANALYSIS() : dSlope(0), dIntercept(0), dRR(0) {}
};

inline std::ostream& operator <<(std::ostream& ds, const LINEAR_ANALYSIS& la)
{
	ds.write((LPCSTR)&la.dSlope, sizeof(la.dSlope));
	ds.write((LPCSTR)&la.dIntercept, sizeof(la.dIntercept));
	ds.write((LPCSTR)&la.dRR, sizeof(la.dRR));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, LINEAR_ANALYSIS& la)
{
	ds.read((LPSTR)&la.dSlope, sizeof(la.dSlope));
	ds.read((LPSTR)&la.dIntercept, sizeof(la.dIntercept));
	ds.read((LPSTR)&la.dRR, sizeof(la.dRR));

	return ds;
}

struct RUN_STATUS
{
    Integer nRunMode;
	Integer nTimeOut;

    RUN_STATUS() : nRunMode(0), nTimeOut(0) {}
};

inline std::ostream& operator <<(std::ostream& ds, const RUN_STATUS& rs)
{
	ds.write((LPCSTR)&rs.nRunMode, sizeof(rs.nRunMode));
	ds.write((LPCSTR)&rs.nTimeOut, sizeof(rs.nTimeOut));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, RUN_STATUS& rs)
{
	ds.read((LPSTR)&rs.nRunMode, sizeof(rs.nRunMode));
	ds.read((LPSTR)&rs.nTimeOut, sizeof(rs.nTimeOut));

    return ds;
}

struct LOGISTIC_ANALYSIS
{
    Double dCoef[4];
	Double dRR;

    LOGISTIC_ANALYSIS() : dRR(0)
    {
        ZeroMemory((LPVOID)dCoef, sizeof(dCoef));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const LOGISTIC_ANALYSIS& la)
{
    ds.write((LPCSTR)&la.dCoef, sizeof(la.dCoef));
    ds.write((LPCSTR)&la.dRR, sizeof(la.dRR));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, LOGISTIC_ANALYSIS& la)
{
	ds.read((LPSTR)&la.dCoef, sizeof(la.dCoef));
    ds.read((LPSTR)&la.dRR, sizeof(la.dRR));

    return ds;
}

struct FACTOR_ANALYSIS
{
	Double dSlope;

	FACTOR_ANALYSIS() : dSlope(0) {}
};

inline std::ostream& operator <<(std::ostream& ds, const FACTOR_ANALYSIS& fa)
{
	ds.write((LPCSTR)&fa.dSlope, sizeof(fa.dSlope));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, FACTOR_ANALYSIS& fa)
{
	ds.read((LPSTR)&fa.dSlope, sizeof(fa.dSlope));

	return ds;
}

struct PTOP_ANALYSIS
{
    Double dY[CALIBRATOR_CONCENTRATION_MAX];
	Double dX[CALIBRATOR_CONCENTRATION_MAX];

    PTOP_ANALYSIS()
    {
        ZeroMemory((LPVOID)dY, sizeof(dY));
        ZeroMemory((LPVOID)dX, sizeof(dX));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const PTOP_ANALYSIS& pta)
{
    ds.write((LPCSTR)&pta.dY, sizeof(pta.dY));
    ds.write((LPCSTR)&pta.dX, sizeof(pta.dX));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, PTOP_ANALYSIS& pta)
{
	ds.read((LPSTR)&pta.dY, sizeof(pta.dY));
	ds.read((LPSTR)&pta.dX, sizeof(pta.dX));

	return ds;
}

struct SPLINE_ANALYSIS
{
	Double dY[CALIBRATOR_CONCENTRATION_MAX];
	Double dX[CALIBRATOR_CONCENTRATION_MAX];
	Double dM[CALIBRATOR_CONCENTRATION_MAX];
	Double dH[CALIBRATOR_CONCENTRATION_MAX];

	SPLINE_ANALYSIS()
	{
		ZeroMemory((LPVOID)&dY, sizeof(dY));
		ZeroMemory((LPVOID)&dX, sizeof(dX));
		ZeroMemory((LPVOID)&dM, sizeof(dM));
		ZeroMemory((LPVOID)&dH, sizeof(dH));
	}
};

inline std::ostream& operator <<(std::ostream& ds, const SPLINE_ANALYSIS& sa)
{
	ds.write((LPCSTR)&sa.dY, sizeof(sa.dY));
	ds.write((LPCSTR)&sa.dX, sizeof(sa.dX));
	ds.write((LPCSTR)&sa.dM, sizeof(sa.dM));
	ds.write((LPCSTR)&sa.dH, sizeof(sa.dH));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, SPLINE_ANALYSIS& sa)
{
	ds.read((LPSTR)&sa.dY, sizeof(sa.dY));
	ds.read((LPSTR)&sa.dX, sizeof(sa.dX));
	ds.read((LPSTR)&sa.dM, sizeof(sa.dM));
	ds.read((LPSTR)&sa.dH, sizeof(sa.dH));

	return ds;
}

struct INTERFACE_ELEMENT
{
	HDC hdcMem;
	HBITMAP hBitmap;
};

struct KINETIC_MAX_WELL
{
	Double dMaxWell[TUBE_MAX];

	KINETIC_MAX_WELL()
	{
		ZeroMemory((LPVOID)dMaxWell, sizeof(dMaxWell));
	}
};

inline std::ostream& operator <<(std::ostream& ds, const KINETIC_MAX_WELL& kmw)
{
	ds.write((LPCSTR)&kmw.dMaxWell, sizeof(kmw.dMaxWell));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, KINETIC_MAX_WELL& kmw)
{
	ds.read((LPSTR)&kmw.dMaxWell, sizeof(kmw.dMaxWell));

    return ds;
}

struct KINETIC_TIME_MAX
{
	Integer nTime[TUBE_MAX];

    KINETIC_TIME_MAX()
    {
        ZeroMemory((LPVOID)nTime, sizeof(nTime));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const KINETIC_TIME_MAX& ktm)
{
    ds.write((LPCSTR)&ktm.nTime, sizeof(ktm.nTime));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, KINETIC_TIME_MAX& ktm)
{
    ds.read((LPSTR)&ktm.nTime, sizeof(ktm.nTime));

    return ds;
}

struct NORMAL_ANALYSIS
{
	AnsiChar  wcMode;
	AnsiChar  wcModeBack;
	AnsiChar  wcFilterCurrent; //2014-8-19项
	AnsiChar  wcFilterCurrentBack; //2014-8-19项
	Double  dPreCal[KINETIC_READINGS_MAX][TUBE_MAX];
	Boolean   bPreCalOK[KINETIC_READINGS_MAX][TUBE_MAX];
	Double  dCalibratorABS[3][CALIBRATOR_CONCENTRATION_MAX];
	AnsiChar  nCalibratorCount[3][CALIBRATOR_CONCENTRATION_MAX];
	AnsiChar  nCalibratorCountTotal[3];
	Boolean   bFilterSelect;
	Double  dBlank[KINETIC_READINGS_MAX][FILTER_PLATE_MAX];
	Integer nBlankCount[KINETIC_READINGS_MAX][FILTER_PLATE_MAX];
	Integer nAnalysisResult[3];
	LINEAR_ANALYSIS linear_analysis[3];
	FACTOR_ANALYSIS factor_analysis[3];
	LOGISTIC_ANALYSIS logistic_analysis[3];
	PTOP_ANALYSIS ptop_analysis[3];
	SPLINE_ANALYSIS spline_analysis[3];
	Boolean bLogX;
	Boolean bLogY;
	Boolean bLogSelect;
	Double dConcentration[3][TUBE_MAX];

	NORMAL_ANALYSIS() : wcMode(0), wcModeBack(0), wcFilterCurrent(0), wcFilterCurrentBack(0),
						bFilterSelect(false), bLogX(false), bLogY(false), bLogSelect(false)
	{
		ZeroMemory((LPVOID)dPreCal, sizeof(dPreCal));
		ZeroMemory((LPVOID)bPreCalOK, sizeof(bPreCalOK));
		ZeroMemory((LPVOID)dCalibratorABS, sizeof(dCalibratorABS));
		ZeroMemory((LPVOID)nCalibratorCount, sizeof(nCalibratorCount));
		ZeroMemory((LPVOID)nCalibratorCountTotal, sizeof(nCalibratorCountTotal));
		ZeroMemory((LPVOID)dBlank, sizeof(dBlank));
		ZeroMemory((LPVOID)nBlankCount, sizeof(nBlankCount));
        ZeroMemory((LPVOID)nAnalysisResult, sizeof(nAnalysisResult));
        ZeroMemory((LPVOID)dConcentration, sizeof(dConcentration));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const NORMAL_ANALYSIS& na)
{
	ds.write((LPCSTR)&na.wcMode, sizeof(na.wcMode));
	ds.write((LPCSTR)&na.wcModeBack, sizeof(na.wcModeBack));
	ds.write((LPCSTR)&na.wcFilterCurrent, sizeof(na.wcFilterCurrent));
	ds.write((LPCSTR)&na.wcFilterCurrentBack, sizeof(na.wcFilterCurrentBack));

    for (int i = 0; i < KINETIC_READINGS_MAX; i++)
        ds.write((LPCSTR)na.dPreCal[i], sizeof(na.dPreCal[i]));

    for (int i = 0; i < KINETIC_READINGS_MAX; i++)
        ds.write((LPCSTR)na.bPreCalOK[i], sizeof(na.bPreCalOK[i]));

    for (int i = 0; i < 3; i++)
        ds.write((LPCSTR)na.dCalibratorABS[i], sizeof(na.dCalibratorABS[i]));

    ds.write((LPCSTR)na.nCalibratorCount, sizeof(na.nCalibratorCount));

    for (int i = 0; i < 3; i++)
        ds.write((LPCSTR)na.nCalibratorCountTotal[i], sizeof(na.nCalibratorCountTotal));

    ds.write((LPCSTR)&na.bFilterSelect, sizeof(na.bFilterSelect));

    for (int i = 0; i < KINETIC_READINGS_MAX; i++)
        ds.write((LPCSTR)na.dBlank[i], sizeof(na.dBlank[i]));

    for (int i = 0; i < KINETIC_READINGS_MAX; i++)
        ds.write((LPCSTR)na.nBlankCount[i], sizeof(na.nBlankCount[i]));

    ds.write((LPCSTR)na.nAnalysisResult, sizeof(na.nAnalysisResult));

    for (int i = 0; i < 3; i++)
        ds << na.linear_analysis[i];

    for (int i = 0; i < 3; i++)
        ds << na.factor_analysis[i];

    for (int i = 0; i < 3; i++)
        ds << na.logistic_analysis[i];

    for (int i = 0; i < 3; i++)
        ds << na.ptop_analysis[i];

    for (int i = 0; i < 3; i++)
        ds << na.spline_analysis[i];

	ds.write((LPCSTR)&na.bLogX, sizeof(na.bLogX));
	ds.write((LPCSTR)&na.bLogY, sizeof(na.bLogY));
	ds.write((LPCSTR)&na.bLogSelect, sizeof(na.bLogSelect));

    for (int i = 0; i < 3; i++)
        ds.write((LPCSTR)na.dConcentration[i], sizeof(na.dConcentration[i]));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, NORMAL_ANALYSIS& na)
{
	ds.read((LPSTR)&na.wcMode, sizeof(na.wcMode));
	ds.read((LPSTR)&na.wcModeBack, sizeof(na.wcModeBack));
	ds.read((LPSTR)&na.wcFilterCurrent, sizeof(na.wcFilterCurrent));
	ds.read((LPSTR)&na.wcFilterCurrentBack, sizeof(na.wcFilterCurrentBack));

    for (int i = 0; i < KINETIC_READINGS_MAX; i++)
        ds.read((LPSTR)na.dPreCal[i], sizeof(na.dPreCal[i]));

	for (int i = 0; i < KINETIC_READINGS_MAX; i++)
        ds.read((LPSTR)na.bPreCalOK[i], sizeof(na.bPreCalOK[i]));

    for (int i = 0; i < 3; i++)
        ds.read((LPSTR)na.dCalibratorABS[i], sizeof(na.dCalibratorABS[i]));

    for (int i = 0; i < 3; i++)
        ds.read((LPSTR)na.nCalibratorCount[i], sizeof(na.nCalibratorCount[i]));

    ds.read((LPSTR)na.nCalibratorCountTotal, sizeof(na.nCalibratorCountTotal));

    ds.read((LPSTR)&na.bFilterSelect, sizeof(na.bFilterSelect));

    for (int i = 0; i < KINETIC_READINGS_MAX; i++)
        ds.read((LPSTR)na.dBlank[i], sizeof(na.dBlank[i]));

    for (int i = 0; i < KINETIC_READINGS_MAX; i++)
        ds.read((LPSTR)na.nBlankCount[i], sizeof(na.nBlankCount[i]));

    ds.read((LPSTR)na.nAnalysisResult, sizeof(na.nAnalysisResult));

    for (int i = 0; i < 3; i++)
        ds >> na.linear_analysis[i];

    for (int i = 0; i < 3; i++)
        ds >> na.factor_analysis[i];

    for (int i = 0; i < 3; i++)
        ds >> na.logistic_analysis[i];

    for (int i = 0; i < 3; i++)
        ds >> na.ptop_analysis[i];

    for (int i = 0; i < 3; i++)
        ds >> na.spline_analysis[i];

	ds.read((LPSTR)&na.bLogX, sizeof(na.bLogX));
	ds.read((LPSTR)&na.bLogY, sizeof(na.bLogY));
	ds.read((LPSTR)&na.bLogSelect, sizeof(na.bLogSelect));

    for (int i = 0; i < 3; i++)
        ds.read((LPSTR)na.dConcentration[i], sizeof(na.dConcentration[i]));

    return ds;
}

struct COLOR
{
	Integer nRed;
	Integer nGreen;
	Integer nBlue;
};

struct KINETIC_AVERAGE_RATE
{
	Double dAverageRate[TUBE_MAX];

    KINETIC_AVERAGE_RATE()
    {
        ZeroMemory((LPVOID)dAverageRate, sizeof(dAverageRate));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const KINETIC_AVERAGE_RATE& kar)
{
    ds.write((LPCSTR)kar.dAverageRate, sizeof(kar.dAverageRate));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, KINETIC_AVERAGE_RATE& kar)
{
	ds.read((LPSTR)kar.dAverageRate, sizeof(kar.dAverageRate));

	return ds;
}

struct KINETIC_MAX_RATE
{
	Double dMaxRate[TUBE_MAX];

	KINETIC_MAX_RATE()
	{
		ZeroMemory((LPVOID)dMaxRate, sizeof(dMaxRate));
	}
};

inline std::ostream& operator <<(std::ostream& ds, const KINETIC_MAX_RATE& kmr)
{
	ds.write((LPCSTR)kmr.dMaxRate, sizeof(kmr.dMaxRate));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, KINETIC_MAX_RATE& kmr)
{
	ds.read((LPSTR)kmr.dMaxRate, sizeof(kmr.dMaxRate));

	return ds;
}

struct KINETIC_TIME_MAX_RATE
{
	Integer nTime[TUBE_MAX];

    KINETIC_TIME_MAX_RATE()
    {
        ZeroMemory((LPVOID)nTime, sizeof(nTime));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const KINETIC_TIME_MAX_RATE& ktm)
{
    ds.write((LPCSTR)ktm.nTime, sizeof(ktm.nTime));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, KINETIC_TIME_MAX_RATE& ktm)
{
    ds.read((LPSTR)ktm.nTime, sizeof(ktm.nTime));

    return ds;
}

struct KINETIC_TIME_CHANGE
{
	Integer nTime[TUBE_MAX];
	Boolean bOK[TUBE_MAX];

    KINETIC_TIME_CHANGE()
    {
        ZeroMemory((LPVOID)nTime, sizeof(nTime));
        ZeroMemory((LPVOID)bOK, sizeof(bOK));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const KINETIC_TIME_CHANGE& ktc)
{
    ds.write((LPCSTR)ktc.nTime, sizeof(ktc.nTime));
    ds.write((LPCSTR)ktc.bOK, sizeof(ktc.bOK));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, KINETIC_TIME_CHANGE& ktc)
{
    ds.read((LPSTR)ktc.nTime, sizeof(ktc.nTime));
    ds.read((LPSTR)ktc.bOK, sizeof(ktc.bOK));

    return ds;
}

struct KINETIC_PARA
{
    AnsiChar kinetic_time_Hour[3];
    AnsiChar kinetic_time_Min[3];
    AnsiChar kinetic_time_Sec[3];
    AnsiChar kinetic_readings;
    AnsiChar kinetic_readings_practical;
    AnsiChar kinetic_readings_analysis;
    AnsiChar kinetic_time_current;
    AnsiChar kinetic_time_count;
    AnsiChar kinetic_reading_current;
    AnsiChar kinetic_analysis_mode;
    AnsiChar kinetic_first_readings;
    AnsiChar kinetic_last_readings;
    KINETIC_AVERAGE_RATE kinetic_average_rate[3];
    KINETIC_MAX_RATE kinetic_max_rate[3];
    KINETIC_TIME_MAX_RATE kinetic_time_max_rate[3];
    KINETIC_TIME_CHANGE kinetic_time_change[3];
    KINETIC_MAX_WELL kinetic_max_well[3];
	KINETIC_TIME_MAX kinetic_time_max[3];
    Integer nAnalysisResult[3];
    Boolean bPreCalOK[TUBE_MAX];
    Boolean bBeginning;
    Integer nPoints;
    Double dChange;
    Boolean bHasData;
    Boolean bChangeExpand;
	Boolean bTypeExpand;
	Integer nCurrentSample;

    KINETIC_PARA() : bBeginning(false), nPoints(0), dChange(0), bHasData(false), bChangeExpand(false), bTypeExpand(false),
                     nCurrentSample(0), kinetic_readings(0), kinetic_readings_practical(0), kinetic_readings_analysis(0),
                     kinetic_time_current(0), kinetic_time_count(0), kinetic_reading_current(0), kinetic_analysis_mode(0),
                     kinetic_first_readings(0), kinetic_last_readings(0)
    {
        ZeroMemory((LPVOID)kinetic_time_Hour, sizeof(kinetic_time_Hour));
        ZeroMemory((LPVOID)kinetic_time_Min, sizeof(kinetic_time_Min));
        ZeroMemory((LPVOID)kinetic_time_Sec, sizeof(kinetic_time_Sec));
        ZeroMemory((LPVOID)kinetic_average_rate, sizeof(kinetic_average_rate));
        ZeroMemory((LPVOID)kinetic_max_rate, sizeof(kinetic_max_rate));
        ZeroMemory((LPVOID)kinetic_time_max_rate, sizeof(kinetic_time_max_rate));
        ZeroMemory((LPVOID)kinetic_time_change, sizeof(kinetic_time_change));
        ZeroMemory((LPVOID)kinetic_max_well, sizeof(kinetic_max_well));
        ZeroMemory((LPVOID)kinetic_time_max, sizeof(kinetic_time_max));
        ZeroMemory((LPVOID)nAnalysisResult, sizeof(nAnalysisResult));
        ZeroMemory((LPVOID)bPreCalOK, sizeof(bPreCalOK));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const KINETIC_PARA& kp)
{
    ds.write((LPCSTR)kp.kinetic_time_Hour, sizeof(kp.kinetic_time_Hour));
    ds.write((LPCSTR)kp.kinetic_time_Min, sizeof(kp.kinetic_time_Min));
    ds.write((LPCSTR)kp.kinetic_time_Sec, sizeof(kp.kinetic_time_Sec));
	ds.write((LPCSTR)&kp.kinetic_readings, sizeof(kp.kinetic_readings));
	ds.write((LPCSTR)&kp.kinetic_readings_practical, sizeof(kp.kinetic_readings_practical));
	ds.write((LPCSTR)&kp.kinetic_readings_analysis, sizeof(kp.kinetic_readings_analysis));
	ds.write((LPCSTR)&kp.kinetic_time_current, sizeof(kp.kinetic_time_current));
	ds.write((LPCSTR)&kp.kinetic_time_count, sizeof(kp.kinetic_time_count));
	ds.write((LPCSTR)&kp.kinetic_reading_current, sizeof(kp.kinetic_reading_current));
	ds.write((LPCSTR)&kp.kinetic_analysis_mode, sizeof(kp.kinetic_analysis_mode));
	ds.write((LPCSTR)&kp.kinetic_first_readings, sizeof(kp.kinetic_first_readings));
	ds.write((LPCSTR)&kp.kinetic_last_readings, sizeof(kp.kinetic_last_readings));

	for (int i = 0; i < 3; i++)
		ds << kp.kinetic_average_rate[i];

	for (int i = 0; i < 3; i++)
		ds << kp.kinetic_max_rate[i];

	for (int i = 0; i < 3; i++)
		ds << kp.kinetic_time_max_rate[i];

	for (int i = 0; i < 3; i++)
		ds << kp.kinetic_time_change[i];

	for (int i = 0; i < 3; i++)
		ds << kp.kinetic_max_well[i];

	for (int i = 0; i < 3; i++)
		ds << kp.kinetic_time_max[i];

	for (int i = 0; i < 3; i++)
		ds << kp.nAnalysisResult[i];

	ds.write((LPCSTR)kp.bPreCalOK, sizeof(kp.bPreCalOK));

	ds.write((LPCSTR)&kp.bBeginning, sizeof(kp.bBeginning));
	ds.write((LPCSTR)&kp.nPoints, sizeof(kp.nPoints));
	ds.write((LPCSTR)&kp.dChange, sizeof(kp.dChange));
	ds.write((LPCSTR)&kp.bHasData, sizeof(kp.bHasData));
	ds.write((LPCSTR)&kp.bChangeExpand, sizeof(kp.bChangeExpand));
	ds.write((LPCSTR)&kp.bTypeExpand, sizeof(kp.bTypeExpand));
	ds.write((LPCSTR)&kp.nCurrentSample, sizeof(kp.nCurrentSample));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, KINETIC_PARA& kp)
{
	ds.read((LPSTR)kp.kinetic_time_Hour, sizeof(kp.kinetic_time_Hour));
	ds.read((LPSTR)kp.kinetic_time_Min, sizeof(kp.kinetic_time_Min));
	ds.read((LPSTR)kp.kinetic_time_Sec, sizeof(kp.kinetic_time_Sec));

	ds.read((LPSTR)&kp.kinetic_readings, sizeof(kp.kinetic_readings));
	ds.read((LPSTR)&kp.kinetic_readings_practical, sizeof(kp.kinetic_readings_practical));
	ds.read((LPSTR)&kp.kinetic_readings_analysis, sizeof(kp.kinetic_readings_analysis));
	ds.read((LPSTR)&kp.kinetic_time_current, sizeof(kp.kinetic_time_current));
	ds.read((LPSTR)&kp.kinetic_time_count, sizeof(kp.kinetic_time_count));
	ds.read((LPSTR)&kp.kinetic_reading_current, sizeof(kp.kinetic_reading_current));
	ds.read((LPSTR)&kp.kinetic_analysis_mode, sizeof(kp.kinetic_analysis_mode));
	ds.read((LPSTR)&kp.kinetic_first_readings, sizeof(kp.kinetic_first_readings));
	ds.read((LPSTR)&kp.kinetic_last_readings, sizeof(kp.kinetic_last_readings));

    for (int i = 0; i < 3; i++)
        ds >> kp.kinetic_average_rate[i];

    for (int i = 0; i < 3; i++)
        ds >> kp.kinetic_max_rate[i];

    for (int i = 0; i < 3; i++)
        ds >> kp.kinetic_time_max_rate[i];

    for (int i = 0; i < 3; i++)
        ds >> kp.kinetic_time_change[i];

    for (int i = 0; i < 3; i++)
        ds >> kp.kinetic_max_well[i];

	for (int i = 0; i < 3; i++)
		ds >> kp.kinetic_time_max[i];

	for (int i = 0; i < 3; i++)
		ds >> kp.nAnalysisResult[i];

	ds.read((LPSTR)kp.bPreCalOK, sizeof(kp.bPreCalOK));

	ds.read((LPSTR)&kp.bBeginning, sizeof(kp.bBeginning));
	ds.read((LPSTR)&kp.nPoints, sizeof(kp.nPoints));
	ds.read((LPSTR)&kp.dChange, sizeof(kp.dChange));
	ds.read((LPSTR)&kp.bHasData, sizeof(kp.bHasData));
	ds.read((LPSTR)&kp.bChangeExpand, sizeof(kp.bChangeExpand));
	ds.read((LPSTR)&kp.bTypeExpand, sizeof(kp.bTypeExpand));
	ds.read((LPSTR)&kp.nCurrentSample, sizeof(kp.nCurrentSample));

	return ds;
}

typedef struct
{
	SYSTEMTIME stTime;
	AnsiString Sys_date;
}SYS_MAININTERFACE;

struct MAINTENANCE_PARA
{
	Boolean bIntensity;
	Boolean bPlateSelect;
	Boolean bRawIntensitySelect;
	Boolean bResetSelect; //2015-2-13
};

struct UART_INF
{
	Byte cmd;
	Byte len;
	Byte crc;
	Byte crc_h;
	Byte crc_l;
	Byte full;
};

struct HELP_TITLE
{
	Integer nStartLine;
	Integer nCurrentLine;
};

struct RAW_DATA
{
	Integer nIntensity[KINETIC_READINGS_MAX][FILTER_PLATE_MAX][TUBE_MAX+12];
	Integer nInputIntensity[FILTER_PLATE_MAX][CHANNEL_MAX];
	Integer nBackgroundIntensity[FILTER_PLATE_MAX][CHANNEL_MAX];

	RAW_DATA()
	{
		ZeroMemory((LPVOID)nIntensity, sizeof(nIntensity));
		ZeroMemory((LPVOID)nInputIntensity, sizeof(nInputIntensity));
		ZeroMemory((LPVOID)nBackgroundIntensity, sizeof(nBackgroundIntensity));
	}
};

inline std::ostream& operator <<(std::ostream& b, const RAW_DATA& rd)
{
	for (Integer i = 0; i < KINETIC_READINGS_MAX; i++)
        for (Integer j = 0; j < FILTER_PLATE_MAX; j++)
			for (Integer k = 0; k < TUBE_MAX+12; k++)
			{
				Integer ni = rd.nIntensity[i][j][k];
				b.write((LPCSTR)&ni, sizeof(ni));
			}

	for (Integer i = 0; i < FILTER_PLATE_MAX; i++)
		for (Integer j = 0; j < CHANNEL_MAX; j++)
		{
			Integer ni = rd.nInputIntensity[i][j];
			b.write((LPCSTR)&ni, sizeof(ni));
		}

	for (Integer i = 0; i < FILTER_PLATE_MAX; i++)
		for (Integer j = 0; j <	CHANNEL_MAX; j++)
		{
			Integer ni = rd.nBackgroundIntensity[i][j];
			b.write((LPCSTR)&ni, sizeof(ni));
		}

    return b;
}

inline std::istream& operator >>(std::istream& b, RAW_DATA& rd)
{
	for (Integer i = 0; i < KINETIC_READINGS_MAX; i++)
		for (Integer j = 0; j < FILTER_PLATE_MAX; j++)
			for (Integer k = 0; k < TUBE_MAX+12; k++)
			{
				Integer& ni = rd.nIntensity[i][j][k];
				b.read((LPSTR)&ni, sizeof(ni));
			}

	for (Integer i = 0; i < FILTER_PLATE_MAX; i++)
		for (Integer j = 0; j < CHANNEL_MAX; j++)
		{
			Integer& ni = rd.nInputIntensity[i][j];
			b.read((LPSTR)&ni, sizeof(ni));
		}

	for (Integer i = 0; i < FILTER_PLATE_MAX; i++)
		for (Integer j = 0; j < CHANNEL_MAX; j++)
		{
			Integer& ni = rd.nBackgroundIntensity[i][j];
			b.read((LPSTR)&ni, sizeof(ni));
		}

	return b;
}

struct DATE_TIME
{
	Integer nYear;
	Integer nMonth;
	Integer nDay;
	Integer nHour;
	Integer nMinute;
	Integer nSecond;
};

struct WINDOW_INF
{
	Byte topMenu;
	Byte CalibrateLcdWin;
	Byte initFlag;
	Byte setLanguageEna;
};

struct SET_INF
{
	Byte beforWindow;
	Byte currentWindow;
};

struct CUTOFF
{
	Single X;
	Single Y;
	Single fac;
	Single f_cutoff;

	CUTOFF() : X(0), Y(0), fac(0), f_cutoff(0) {}
};

inline std::ostream& operator <<(std::ostream& ds, const CUTOFF& c)
{
	ds.write((LPCSTR)&c.X, sizeof(c.X));
	ds.write((LPCSTR)&c.Y, sizeof(c.Y));
	ds.write((LPCSTR)&c.fac, sizeof(c.fac));
	ds.write((LPCSTR)&c.f_cutoff, sizeof(c.f_cutoff));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, CUTOFF& c)
{
	ds.read((LPSTR)&c.X, sizeof(c.X));
	ds.read((LPSTR)&c.Y, sizeof(c.Y));
	ds.read((LPSTR)&c.fac, sizeof(c.fac));
	ds.read((LPSTR)&c.f_cutoff, sizeof(c.f_cutoff));

	return ds;
}

struct LAYOUT
{
	AnsiChar Type[10];
	AnsiChar curentSelectWell[10];
    AnsiChar Num[10];

    LAYOUT()
    {
        ZeroMemory((LPVOID)Type, sizeof(Type));
        ZeroMemory((LPVOID)curentSelectWell, sizeof(curentSelectWell));
        ZeroMemory((LPVOID)Num, sizeof(Num));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const LAYOUT& l)
{
    ds.write((LPCSTR)l.Type, sizeof(l.Type));
    ds.write((LPCSTR)l.curentSelectWell, sizeof(l.curentSelectWell));
    ds.write((LPCSTR)l.Num, sizeof(l.Num));

    return ds;
}

inline std::istream& operator >>(std::istream& ds, LAYOUT& l)
{
    ds.read((LPSTR)l.Type, sizeof(l.Type));
    ds.read((LPSTR)l.curentSelectWell, sizeof(l.curentSelectWell));
    ds.read((LPSTR)l.Num, sizeof(l.Num));

    return ds;
}

struct QUALITY
{
	Int8 Type;

    QUALITY() : Type(0) {}
};

inline std::ostream& operator <<(std::ostream& ds, const QUALITY& q)
{
	ds.write((LPCSTR)&q.Type, sizeof(q.Type));

	return ds;
}

inline std::istream& operator >>(std::istream& ds, QUALITY& q)
{
	ds.read((LPSTR)&q.Type, sizeof(q.Type));

    return ds;
}

struct SDInf
{
	Int8 Type;
	AnsiChar curentSd[10];
	AnsiChar temp_3[10];
	Int8 temp_2;
	AnsiChar Sd[CALIBRATORS_MAX + 1][10];
	Boolean Ena;

	SDInf() : Type(0), temp_2(0), Ena(false) {}
};

inline std::ostream& operator <<(std::ostream& b, const SDInf& s)
{
	b.write((LPCSTR)&s.Type, sizeof(s.Type));
	b.write((LPCSTR)&s.curentSd, sizeof(s.curentSd));
	b.write((LPCSTR)&s.temp_3, sizeof(s.temp_3));
	b.write((LPCSTR)&s.temp_2, sizeof(s.temp_2));

	for (Integer i = 0; i < CALIBRATORS_MAX+1; i++)
		b.write((LPCSTR)s.Sd[i], sizeof(s.Sd[i]));

	b.write((LPCSTR)&s.Ena, sizeof(s.Ena));

	return b;
}

inline std::istream& operator >>(std::istream& b, SDInf& s)
{
	b.read((LPSTR)&s.Type, sizeof(s.Type));
	b.read((LPSTR)&s.curentSd, sizeof(s.curentSd));
	b.read((LPSTR)&s.temp_3, sizeof(s.temp_3));
	b.read((LPSTR)&s.temp_2, sizeof(s.temp_2));

	for (Integer i = 0; i < CALIBRATORS_MAX+1; i++)
		b.read((LPSTR)s.Sd[i], sizeof(s.Sd[i]));

	b.read((LPSTR)&s.Ena, sizeof(s.Ena));

	return b;
}

struct QCInf
{
	Int8 Type;
	ByteArray curentQc;
	AnsiChar temp_2;
	AnsiChar temp_3[10];
	AnsiChar Qc[CONTROLS_MAX + 1][10];
	Boolean Ena;

	QCInf() : Type(0), temp_2(0), Ena(false) {}
};

inline std::ostream& operator <<(std::ostream& b, const QCInf& q)
{
	b.write((LPCSTR)&q.Type, sizeof(q.Type));
	b.write((LPCSTR)&q.curentQc, sizeof(q.curentQc));
	b.write((LPCSTR)&q.temp_2, sizeof(q.temp_2));
	b.write((LPCSTR)q.temp_3, sizeof(q.temp_3));

	for (int i = 0; i < CONTROLS_MAX + 1; i++)
		b.write((LPCSTR)q.Qc[i], sizeof(q.Qc[i]));

    b.write((LPCSTR)&q.Ena, sizeof(q.Ena));

    return b;
}

inline std::istream& operator >>(std::istream& b, QCInf& q)
{
	b.read((LPSTR)&q.Type, sizeof(q.Type));
	b.read((LPSTR)&q.curentQc, sizeof(q.curentQc));
	b.read((LPSTR)&q.temp_2, sizeof(q.temp_2));
    b.read((LPSTR)q.temp_3, sizeof(q.temp_3));

	for (int i = 0; i < CONTROLS_MAX + 1; i++)
		b.read((LPSTR)q.Qc[i], sizeof(q.Qc[i]));

	b.read((LPSTR)&q.Ena, sizeof(q.Ena));

	return b;
}

struct ConInf
{
	Int8 Type;
	AnsiChar curentcon[10];
	AnsiChar temp_2;
	AnsiChar temp_3[10];
	AnsiChar Qc[10][10];
	Boolean Ena;

	ConInf() : Type(0), temp_2(0), Ena(false) {}
};

inline std::ostream& operator <<(std::ostream& b, const ConInf& c)
{
	b.write((LPCSTR)&c.Type, sizeof(c.Type));
	b.write((LPCSTR)c.curentcon, sizeof(c.curentcon));
	b.write((LPCSTR)&c.temp_2, sizeof(c.temp_2));
	b.write((LPCSTR)c.temp_3, sizeof(c.temp_3));

	for (int i = 0; i < 10; i++)
		b.write((LPCSTR)c.Qc[i], sizeof(c.Qc[i]));

	b.write((LPCSTR)&c.Ena, sizeof(c.Ena));

	return b;
}

inline std::istream& operator >>(std::istream& b, ConInf& c)
{
	b.read((LPSTR)&c.Type, sizeof(c.Type));
	b.read((LPSTR)c.curentcon, sizeof(c.curentcon));
	b.read((LPSTR)&c.temp_2, sizeof(c.temp_2));
	b.read((LPSTR)c.temp_3, sizeof(c.temp_3));

	for (int i = 0; i < 10; i++)
		b.read((LPSTR)c.Qc[i], sizeof(c.Qc[i]));

	b.read((LPSTR)&c.Ena, sizeof(c.Ena));

	return b;
}

struct BOARD_INF
{
    AnsiChar Name[30];
	AnsiChar Filter_1[8];

	AnsiChar Filter_2[8];
	AnsiChar detectMode[8];
	Byte detectCount;
	AnsiChar shakeMode[8];
	AnsiChar shakeEna[8];
	AnsiChar shakeTime[10];
	AnsiChar calculateMode[10];
	AnsiChar preCalculate[10];
	AnsiChar shake_time_Hour[3];
	AnsiChar shake_time_Min[3];
	AnsiChar shake_time_Sec[3];
	AnsiChar curentKinetic[10];
	AnsiChar curentcurve[15]; //2014-8-12项
	AnsiChar curentCStringinter[10];
	AnsiChar curentCStringQc[10];
    AnsiChar curentCStringinter_cutoff[10];
	LAYOUT layout[TUBE_MAX+1];
	QUALITY quality;
	CUTOFF cutoff;
	LongWord Id;
    LongWord upTemprature;
    LongWord DownTemprature;
	LongWord tempratureTime;
	Boolean boardLock_Ena;
	AnsiChar nc_cut_off[8];
	AnsiChar pc_cut_off[8];
	AnsiChar fac_cut_off[8];
	AnsiChar nc_rang_down[8];
	AnsiChar nc_rang_up[8];
	AnsiChar pc_rang_down[8];
	AnsiChar pc_rang_up[8];
	AnsiChar nc_sco[8];
	AnsiChar pc_sco[8];
	AnsiChar ref_rang_sco_down[8];
	AnsiChar ref_rang_sco_up[8];
	AnsiChar Filter_Set_1[8];
	AnsiChar Filter_Set_2[8];
	AnsiChar Filter_Set_3[8];
	AnsiChar Filter_Set_4[8];
	AnsiChar Filter_Set_5[8];
	AnsiChar Filter_Set_6[8];
	AnsiChar Filter_Set_7[8];
	AnsiChar Filter_Set_8[8];
	Integer test;
    Byte Filter1_locate;
	Byte Filter2_locate;
    KINETIC_PARA kinetic_para;
    NORMAL_ANALYSIS normal_analysis; //2014-8-19项
    AnsiChar wcCycles;
    Boolean bHasData;
	Boolean bHasRawData[FILTER_PLATE_MAX]; //2014-8-19项
    Double dConcentration[CALIBRATOR_CONCENTRATION_MAX];
	AnsiChar wcCurrentUnit;
    INTERPRET_PARA interpret_para;
    QUALITY_PARA quality_para;

    BOARD_INF() : detectCount(0), Id(0), upTemprature(0), DownTemprature(0), tempratureTime(0), boardLock_Ena(false),
                  test(0), Filter1_locate(0), Filter2_locate(0), wcCycles(0), bHasData(false), wcCurrentUnit(0)
    {
        ZeroMemory((LPVOID)Name, sizeof(Name));
        ZeroMemory((LPVOID)Filter_1, sizeof(Filter_1));
        ZeroMemory((LPVOID)Filter_2, sizeof(Filter_2));
        ZeroMemory((LPVOID)detectMode, sizeof(detectMode));
        ZeroMemory((LPVOID)shakeMode, sizeof(shakeMode));
        ZeroMemory((LPVOID)shakeEna, sizeof(shakeEna));
        ZeroMemory((LPVOID)shakeTime, sizeof(shakeTime));
        ZeroMemory((LPVOID)calculateMode, sizeof(calculateMode));
        ZeroMemory((LPVOID)preCalculate, sizeof(preCalculate));
        ZeroMemory((LPVOID)shake_time_Hour, sizeof(shake_time_Hour));
        ZeroMemory((LPVOID)shake_time_Min, sizeof(shake_time_Min));
        ZeroMemory((LPVOID)shake_time_Sec, sizeof(shake_time_Sec));
        ZeroMemory((LPVOID)curentKinetic, sizeof(curentKinetic));
        ZeroMemory((LPVOID)curentcurve, sizeof(curentcurve));
        ZeroMemory((LPVOID)curentCStringinter, sizeof(curentCStringinter));
        ZeroMemory((LPVOID)curentCStringQc, sizeof(curentCStringQc));
        ZeroMemory((LPVOID)curentCStringinter_cutoff, sizeof(curentCStringinter_cutoff));
        ZeroMemory((LPVOID)layout, sizeof(layout));
        ZeroMemory((LPVOID)nc_cut_off, sizeof(nc_cut_off));
        ZeroMemory((LPVOID)pc_cut_off, sizeof(pc_cut_off));
        ZeroMemory((LPVOID)fac_cut_off, sizeof(fac_cut_off));
        ZeroMemory((LPVOID)nc_rang_down, sizeof(nc_rang_down));
        ZeroMemory((LPVOID)nc_rang_up, sizeof(nc_rang_up));
        ZeroMemory((LPVOID)pc_rang_down, sizeof(pc_rang_down));
        ZeroMemory((LPVOID)pc_rang_up, sizeof(pc_rang_up));
        ZeroMemory((LPVOID)nc_sco, sizeof(nc_sco));
        ZeroMemory((LPVOID)pc_sco, sizeof(pc_sco));
		ZeroMemory((LPVOID)ref_rang_sco_down, sizeof(ref_rang_sco_down));
        ZeroMemory((LPVOID)ref_rang_sco_up, sizeof(ref_rang_sco_up));
        ZeroMemory((LPVOID)Filter_Set_1, sizeof(Filter_Set_1));
        ZeroMemory((LPVOID)Filter_Set_2, sizeof(Filter_Set_2));
        ZeroMemory((LPVOID)Filter_Set_3, sizeof(Filter_Set_3));
        ZeroMemory((LPVOID)Filter_Set_4, sizeof(Filter_Set_4));
        ZeroMemory((LPVOID)Filter_Set_5, sizeof(Filter_Set_5));
        ZeroMemory((LPVOID)Filter_Set_6, sizeof(Filter_Set_6));
        ZeroMemory((LPVOID)Filter_Set_7, sizeof(Filter_Set_7));
        ZeroMemory((LPVOID)bHasRawData, sizeof(bHasRawData));
        ZeroMemory((LPVOID)dConcentration, sizeof(dConcentration));
    }
};

inline std::ostream& operator <<(std::ostream& ds, const BOARD_INF& bi)
{
	for (Integer i = 0; i < 30; i++)
        ds.write((LPCSTR)bi.Name[i], sizeof(bi.Name));

    ds.write((LPCSTR)bi.Filter_1, sizeof(bi.Filter_1));
    ds.write((LPCSTR)bi.Filter_2, sizeof(bi.Filter_2));
    ds.write((LPCSTR)bi.detectMode, sizeof(bi.detectMode));

    ds.write((LPCSTR)&bi.detectCount, sizeof(bi.detectCount));

    ds.write((LPCSTR)bi.shakeMode, sizeof(bi.shakeMode));
    ds.write((LPCSTR)bi.shakeEna, sizeof(bi.shakeEna));
    ds.write((LPCSTR)bi.shakeTime, sizeof(bi.shakeTime));
    ds.write((LPCSTR)bi.calculateMode, sizeof(bi.calculateMode));
    ds.write((LPCSTR)bi.preCalculate, sizeof(bi.preCalculate));
    ds.write((LPCSTR)bi.shake_time_Hour, sizeof(bi.shake_time_Hour));
    ds.write((LPCSTR)bi.shake_time_Min, sizeof(bi.shake_time_Min));
    ds.write((LPCSTR)bi.shake_time_Sec, sizeof(bi.shake_time_Sec));
    ds.write((LPCSTR)bi.curentKinetic, sizeof(bi.curentKinetic));
    ds.write((LPCSTR)bi.curentcurve, sizeof(bi.curentcurve));
    ds.write((LPCSTR)bi.curentCStringinter, sizeof(bi.curentCStringinter));
	ds.write((LPCSTR)bi.curentCStringQc, sizeof(bi.curentCStringQc));
    ds.write((LPCSTR)bi.curentCStringinter_cutoff, sizeof(bi.curentCStringinter_cutoff));

	for (Integer i = 0; i < TUBE_MAX+1; i++)
        ds << bi.layout[i];

	ds << bi.quality << bi.cutoff;

	ds.write((LPCSTR)&bi.Id, sizeof(bi.Id));
	ds.write((LPCSTR)&bi.upTemprature, sizeof(bi.upTemprature));
	ds.write((LPCSTR)&bi.DownTemprature, sizeof(bi.DownTemprature));
	ds.write((LPCSTR)&bi.tempratureTime, sizeof(bi.tempratureTime));
	ds.write((LPCSTR)&bi.boardLock_Ena, sizeof(bi.boardLock_Ena));
    ds.write((LPCSTR)bi.nc_cut_off, sizeof(bi.nc_cut_off));
    ds.write((LPCSTR)bi.pc_cut_off, sizeof(bi.pc_cut_off));
    ds.write((LPCSTR)bi.fac_cut_off, sizeof(bi.fac_cut_off));
    ds.write((LPCSTR)bi.nc_rang_down, sizeof(bi.nc_rang_down));
    ds.write((LPCSTR)bi.nc_rang_up, sizeof(bi.nc_rang_up));
    ds.write((LPCSTR)bi.pc_rang_down, sizeof(bi.pc_rang_down));
    ds.write((LPCSTR)bi.pc_rang_up, sizeof(bi.pc_rang_up));
    ds.write((LPCSTR)bi.nc_sco, sizeof(bi.nc_sco));
    ds.write((LPCSTR)bi.pc_sco, sizeof(bi.pc_sco));
    ds.write((LPCSTR)bi.ref_rang_sco_down, sizeof(bi.ref_rang_sco_down));
    ds.write((LPCSTR)bi.ref_rang_sco_up, sizeof(bi.ref_rang_sco_up));
    ds.write((LPCSTR)bi.Filter_Set_1, sizeof(bi.Filter_Set_1));
    ds.write((LPCSTR)bi.Filter_Set_2, sizeof(bi.Filter_Set_2));
    ds.write((LPCSTR)bi.Filter_Set_3, sizeof(bi.Filter_Set_3));
    ds.write((LPCSTR)bi.Filter_Set_4, sizeof(bi.Filter_Set_4));
    ds.write((LPCSTR)bi.Filter_Set_5, sizeof(bi.Filter_Set_5));
    ds.write((LPCSTR)bi.Filter_Set_6, sizeof(bi.Filter_Set_6));
    ds.write((LPCSTR)bi.Filter_Set_7, sizeof(bi.Filter_Set_7));
    ds.write((LPCSTR)bi.Filter_Set_8, sizeof(bi.Filter_Set_8));

	ds.write((LPCSTR)&bi.test, sizeof(bi.test));
	ds.write((LPCSTR)&bi.Filter1_locate, sizeof(bi.Filter1_locate));
	ds.write((LPCSTR)&bi.Filter2_locate, sizeof(bi.Filter2_locate));

    ds << bi.kinetic_para;
    ds << bi.normal_analysis;

	ds.write((LPCSTR)&bi.wcCycles, sizeof(bi.wcCycles));
	ds.write((LPCSTR)&bi.bHasData, sizeof(bi.bHasData));

	ds.write((LPCSTR)bi.bHasRawData, sizeof(bi.bHasRawData));
    ds.write((LPCSTR)bi.dConcentration, sizeof(bi.dConcentration));

	ds.write((LPCSTR)&bi.wcCurrentUnit, sizeof(bi.wcCurrentUnit));

	ds << bi.interpret_para << bi.quality_para;

    return ds;
}

inline std::istream& operator >>(std::istream& ds, BOARD_INF& bi)
{
	ds.read((LPSTR)bi.Name, sizeof(bi.Name));
	ds.read((LPSTR)bi.Filter_1, sizeof(bi.Filter_1));
	ds.read((LPSTR)bi.Filter_2, sizeof(bi.Filter_2));
	ds.read((LPSTR)bi.detectMode, sizeof(bi.detectMode));
	ds.read((LPSTR)&bi.detectCount, sizeof(bi.detectCount));
	ds.read((LPSTR)bi.shakeMode, sizeof(bi.shakeMode));
    ds.read((LPSTR)bi.shakeEna, sizeof(bi.shakeEna));
    ds.read((LPSTR)bi.shakeTime, sizeof(bi.shakeTime));
    ds.read((LPSTR)bi.calculateMode, sizeof(bi.calculateMode));
    ds.read((LPSTR)bi.preCalculate, sizeof(bi.preCalculate));
    ds.read((LPSTR)bi.shake_time_Hour, sizeof(bi.shake_time_Hour));
    ds.read((LPSTR)bi.shake_time_Min, sizeof(bi.shake_time_Min));
    ds.read((LPSTR)bi.shake_time_Sec, sizeof(bi.shake_time_Sec));
    ds.read((LPSTR)bi.curentKinetic, sizeof(bi.curentKinetic));
    ds.read((LPSTR)bi.curentcurve, sizeof(bi.curentcurve));
    ds.read((LPSTR)bi.curentCStringinter, sizeof(bi.curentCStringinter));
    ds.read((LPSTR)bi.curentCStringQc, sizeof(bi.curentCStringQc));
    ds.read((LPSTR)bi.curentCStringinter_cutoff, sizeof(bi.curentCStringinter_cutoff));

    for (size_t i = 0; i < TUBE_MAX+1; i++)
        ds >> bi.layout[i];

	ds >> bi.quality >> bi.cutoff;

	ds.read((LPSTR)&bi.Id, sizeof(bi.Id));
	ds.read((LPSTR)&bi.upTemprature, sizeof(bi.upTemprature));
	ds.read((LPSTR)&bi.DownTemprature, sizeof(bi.DownTemprature));
	ds.read((LPSTR)&bi.tempratureTime, sizeof(bi.tempratureTime));
	ds.read((LPSTR)&bi.boardLock_Ena, sizeof(bi.boardLock_Ena));
	ds.read((LPSTR)bi.nc_cut_off, sizeof(bi.nc_cut_off));
	ds.read((LPSTR)bi.pc_cut_off, sizeof(bi.pc_cut_off));
	ds.read((LPSTR)bi.fac_cut_off, sizeof(bi.fac_cut_off));
	ds.read((LPSTR)bi.nc_rang_down, sizeof(bi.nc_rang_down));
	ds.read((LPSTR)bi.nc_rang_up, sizeof(bi.nc_rang_up));
	ds.read((LPSTR)bi.pc_rang_down, sizeof(bi.pc_rang_down));
	ds.read((LPSTR)bi.pc_rang_up, sizeof(bi.pc_rang_up));
	ds.read((LPSTR)bi.nc_sco, sizeof(bi.nc_sco));
	ds.read((LPSTR)bi.pc_sco, sizeof(bi.pc_sco));
	ds.read((LPSTR)bi.ref_rang_sco_down, sizeof(bi.ref_rang_sco_down));
	ds.read((LPSTR)bi.ref_rang_sco_up, sizeof(bi.ref_rang_sco_up));
	ds.read((LPSTR)bi.Filter_Set_1, sizeof(bi.Filter_Set_1));
	ds.read((LPSTR)bi.Filter_Set_2, sizeof(bi.Filter_Set_2));
	ds.read((LPSTR)bi.Filter_Set_3, sizeof(bi.Filter_Set_3));
	ds.read((LPSTR)bi.Filter_Set_4, sizeof(bi.Filter_Set_4));
	ds.read((LPSTR)bi.Filter_Set_5, sizeof(bi.Filter_Set_5));
	ds.read((LPSTR)bi.Filter_Set_6, sizeof(bi.Filter_Set_6));
	ds.read((LPSTR)bi.Filter_Set_7, sizeof(bi.Filter_Set_7));
	ds.read((LPSTR)bi.Filter_Set_8, sizeof(bi.Filter_Set_8));

	ds.read((LPSTR)&bi.test, sizeof(bi.test));
	ds.read((LPSTR)&bi.Filter1_locate, sizeof(bi.Filter1_locate));
	ds.read((LPSTR)&bi.Filter2_locate, sizeof(bi.Filter2_locate));

	ds >> bi.kinetic_para;
	ds >> bi.normal_analysis;

	ds.read((LPSTR)&bi.wcCycles, sizeof(bi.wcCycles));
	ds.read((LPSTR)&bi.bHasData, sizeof(bi.bHasData));
	ds.read((LPSTR)bi.bHasRawData, sizeof(bi.bHasRawData));
	ds.read((LPSTR)bi.dConcentration, sizeof(bi.dConcentration));
	ds.read((LPSTR)bi.wcCurrentUnit, sizeof(bi.wcCurrentUnit));

	ds >> bi.interpret_para >> bi.quality_para;

    return ds;
}

struct BOARD_CURRENT_INF
{
	AnsiChar Name[30];
    AnsiChar Filter_1[8];
    AnsiChar Filter_2[8];
    AnsiChar detectMode[8];
	Byte detectCount;
    AnsiChar shakeMode[8];
    AnsiChar  shakeTime[10];
    AnsiChar calculateMode[10];
	AnsiChar preCalculate[10];
    LAYOUT layout;
    QUALITY quality;
    CUTOFF cutoff;
    LongWord Id;
    LongWord upTemprature;
    LongWord DownTemprature;
	LongWord tempratureTime;
    Boolean boardLock_Ena;

    BOARD_CURRENT_INF() : detectCount(0), Id(0), upTemprature(0), DownTemprature(0),
                          boardLock_Ena(false) {}
};

inline std::ostream& operator <<(std::ostream& b, const BOARD_CURRENT_INF& bc)
{
    b.write((LPCSTR)bc.Name, sizeof(bc.Name));
    b.write((LPCSTR)bc.Filter_1, sizeof(bc.Filter_1));
    b.write((LPCSTR)bc.Filter_2, sizeof(bc.Filter_2));
    b.write((LPCSTR)bc.detectMode, sizeof(bc.detectMode));

    b << bc.detectCount;

    b.write((LPCSTR)bc.shakeMode, sizeof(bc.shakeMode));
    b.write((LPCSTR)bc.shakeTime, sizeof(bc.shakeTime));
    b.write((LPCSTR)bc.calculateMode, sizeof(bc.calculateMode));
    b.write((LPCSTR)bc.preCalculate, sizeof(bc.preCalculate));

	b << bc.layout << bc.quality << bc.cutoff;
    b << bc.Id << bc.upTemprature << bc.DownTemprature << bc.tempratureTime
      << bc.boardLock_Ena;

    return b;
}

inline std::istream& operator >>(std::istream& b, BOARD_CURRENT_INF& bc)
{
	b.read((LPSTR)bc.Name, sizeof(bc.Name));
	b.read((LPSTR)bc.Filter_1, sizeof(bc.Filter_1));
	b.read((LPSTR)bc.Filter_2, sizeof(bc.Filter_2));
	b.read((LPSTR)bc.detectMode, sizeof(bc.detectMode));

	b >> bc.detectCount;

	b.read((LPSTR)bc.shakeMode, sizeof(bc.shakeMode));
	b.read((LPSTR)bc.shakeTime, sizeof(bc.shakeTime));
	b.read((LPSTR)bc.calculateMode, sizeof(bc.calculateMode));
	b.read((LPSTR)bc.preCalculate, sizeof(bc.preCalculate));

	b >> bc.layout >> bc.quality >> bc.cutoff;
	b >> bc.Id >> bc.upTemprature >> bc.DownTemprature >> bc.tempratureTime
	  >> bc.boardLock_Ena;

	return b;
}

struct HISTORY_FILE
{
	SYSTEMTIME stTime;
	AnsiString builtTime;
	AnsiString name;
	AnsiString Num;
};

struct PAGE
{
	Integer currentPage;
	Integer currentSelect;
	Integer selectLocateX;
	Integer selectLocateY[6];
	Integer fileMaxNum;
	Integer start_hang;
	Integer allPage;
	Integer temp;
};

struct UPDATE_FILE
{
	AnsiChar start[20];
	AnsiChar firstName[40];
	AnsiChar lastName[40];
	AnsiChar endNope[20];
};

struct REMOTE_INFO
{
	Byte cMachinSerial[8];
	Byte cIP[IP_CHAR_MAX];
	Byte cPort[PORT_CHAR_MAX];
	Byte cError[ERROR_COLUMN_MAX][ERROR_CHAR_MAX];
	AnsiChar  wcCurrentPlate;
	Boolean   bRemote;
	Boolean   bRunning;
	Boolean   bfinished;
	Boolean   bReconnected;
	Integer nPlateTotal;
	Integer nPlateCurrent;
};

#endif // ELISA_H

