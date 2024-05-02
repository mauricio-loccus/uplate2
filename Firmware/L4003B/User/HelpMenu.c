
//帮助界面
#include "MainTask.h"

#define HELP_MENU1_PAGE_MAX  6
#define HELP_MENU2_PAGE_MAX  1
#define HELP_MENU3_PAGE_MAX  2
#define HELP_MENU4_PAGE_MAX  1

const signed char HELP_MENU_PAGE_MAX[4]= {HELP_MENU1_PAGE_MAX,HELP_MENU2_PAGE_MAX,HELP_MENU3_PAGE_MAX,HELP_MENU4_PAGE_MAX};

//Protocol 界面
#define HELP_PROTOCOL_1_MAX 13
#define HELP_PROTOCEOL_CHAR_MAX 180
const char STR_HELP_PROTOCOL_1[LANGUAGE_TYPES][HELP_PROTOCOL_1_MAX][HELP_PROTOCEOL_CHAR_MAX]
= {""/*{
        "Protocol Interface: ",
        "The Protocol interface allows management of programs and files, parameter setting, and instrument functions.",
        "File Management:",
        "There are two types of program files that can be saved and opened: One type has the parameter of the program",
        "without results attached.  Three \"demo\" programs come installed on the instrument as this type.  The parameter ",
        "setting can be changed and used in measurement.  The other type includes the detection data and analysis results ",
        "attached, these files show the file icon in the data column.  The parameters can't be changed on these files, and",
        "can be used only for measuring after renaming the program file.",
        "Click \"New\" to enter the name of a new program and then click \"OK\" to save the name.  The parameter settings can",
        "be changed per the application requirements, and the program can be saved by pressing SAVE.",
        "Click the \"Save\" button to save the set program and view it in the \"File List\".  If a program is saved before running a",
        "plate, the program is saved without results attached.",
        "1/6"
    },
    {
        "程序界面",
        "该界面用户可进行如下操作：程序文件管理，参数设置以及运行程序。",
        "文件管理",
        "程序文件分为两种类型：一类只有参数设置，未进行检测，即不含检测结果的文件；",
        "另一类包括参数设置，在进行样品检测后，含有检测数据及数据分析结果。",
        "点击“新建”，弹出输入框，可输入程序名称，点击“Enter”，完成命名。此时创建的程序文件，参数设置可以更改。",
        "点击“保存”，则可保存当前程序，在“文件列表”中可以对其进行查看。",
        "点击“另存为”按钮，可将其重新命名，另存为新的程序文件。注意：另存时可修改程序文件名称。",
        "点击“文件列表”按钮，界面中显示所有保存的程序文件。",
        "点击“删除”按钮，可对选中文件进行删除。",
        "点击“U盘”按钮，可对仪器内存储的程序文件和外接U盘内存储的程序文件进行切换显示。",
        "点击“导出”按钮，将仪器内的程序文件导出到外接U盘。",
        "1/6",
    }*/
};

#define HELP_PROTOCOL_2_MAX 12
const char STR_HELP_PROTOCOL_2[LANGUAGE_TYPES][HELP_PROTOCOL_2_MAX][HELP_PROTOCEOL_CHAR_MAX]
= {""/*{
        "Click \"Save As\" to save a program under a new name.",
        "Click \"File List\" to open the program file list to open a program.",
        "\"Delete\" is used to delete a file.",
        "\"USB Drive\" button is used to switch between the internal hard drive (Disk) and external USB drive.",
        "\"Export\" is used to export files from the internal disk drive to the external USB drive.",
        "\"Import\" is used to import files from the external USB drive to the internal disk drive",
        "Function buttons:",
        "\"Run\":  Starts a microplate reading.",
        "\"Stop\": Stops the reading.",
        "\"Plate in/out\": controls the plate holder drawer in and out.",
        " ",
        "2/6"
    },
    {
        "点击“导入”按钮，将外接U盘内的程序文件导入到仪器。",
        "功能按钮",
        "点击“运行”按钮，开始检测读数。",
        "点击“停止”按钮，停止当前检测。",
        "点击“板进/板出”按钮，微孔板架进出仪器控制按键。",
        "程序文件运行步骤",
        "打开一个程序文件（或新建），设置好所需参数。 ",
        "检测之前放置待测微孔板：如果微孔板支架（用于放置微孔板）在仪器内部，请点击“Plate in/out”键，让微孔板",
        "架移出仪器后，放入待测的微孔板，微孔板架上 A1刻字对应微孔板上的A1孔。",
        "点击液晶屏幕上“Start”按钮，弹出程序文件命名窗口，输入文件名（或软件自动生成），点击“Enter”，微孔板自",
        "动移入仪器进行样品检测。",
        "2/6"
    }*/
};
#define HELP_PROTOCOL_3_MAX 13
const char STR_HELP_PROTOCOL_3[LANGUAGE_TYPES][HELP_PROTOCOL_3_MAX][HELP_PROTOCEOL_CHAR_MAX]
= {""/*{
        "Plate reading procedure:",
        "Open an existing program file (or choose New) and set the parameters. ",
        "Click the \"Plate in/out\" button on the screen or the front panel to put the sample plate into position on the plate holder",
        "drawer.  Make sure that the A1 location of the plate is positioned correctly.",
        "Click \"Start\" on the screen or the \"Start\" button on the front panel to start reading the plate.",
        "Protocol setting:",
        "Measurement parameters: Wavelength and mode (reading speed) can be set in the measurement parameters",
        "mode. On the main \"protocols\" interface screen, click \"Measure\" to set the measurement parameters.  Click Filter 1",
        "and Filter 2 to choose the filters to be used.  Click \"Mode\" to choose the reading speed.",
        "Layout Settings:",
        "In the \"Protocols\" interface, click on \"Plate Layout\" to enter the Plate Layout interface.  In the Plate Layout interface ",
        "there are buttons on the right side: \"Concentration\", \"Delete all\" \"OK\", and \"Back\".",
        "3/6"
    },
    {
        "程序参数设置",
        "设置程序测量参数：",
        "1、在测量界面中可以设置仪器检测波长及检测速度模式（Mode）；",
        "2、在“程序”界面中, 点击“测量”区域，进入此参数设置界面；",
        "3、在“滤光片1”旁边浅色区域点击一次，显示出仪器可设置波长选择；",
        "4、本仪器可以进行单、双波长测量，如需要双波长测量时，点击“滤光片2”旁边浅色区域，再次出现可选波长；",
        "5、测量模式有两种：快速、正常，点击“测量模式”旁边浅色区域，出现两种方式选择。",
        "布局设置",
        "在“程序”界面,点击“布局”，出现“微孔板布局”界面，界面右侧有“浓度”、“删除所有”、“确认”、",
        "“返回”4个按键。",
        " ",
        " ",
        "3/6"
    }*/
};
#define HELP_PROTOCOL_4_WORD_MAX 4
#ifndef SOFTWARE_DN
#define HELP_PROTOCOL_4_MAX 12
#else
#define HELP_PROTOCOL_4_MAX 9
#endif
const char STR_HELP_PROTOCOL_4[LANGUAGE_TYPES][HELP_PROTOCOL_4_MAX][HELP_PROTOCEOL_CHAR_MAX]
= {""/*{
        "Setting the plate layout: First choose the well type needed by clicking one of the choices to the right side.  The",
        "selected type will be highlighted with a red frame, then select the well positions on plate layout to match the type ",
        "highlighted.",
	      #ifndef SOFTWARE_DN
        "Choose a Well Type from these seven available options: BK, SD, UD, EP.",
	      #else
	      "Choose a Well Type from these seven available options: BK, SD, QC, UD, EP, NC, PC.",
	      #endif
        ": Blank well for blank control",
        ": Standard sample well to set standard curve",
	      #ifndef SOFTWARE_DN
        ": QC control well",
	      #endif
        ": Unknown sample position",
        ": Empty sample position",
	       #ifndef SOFTWARE_DN
        ": Negative control positions",
        ": Positive control positions",
	       #endif
        "4/6"
    },
    {
        "布局设置的操作方式为：先在板孔类型中选中需要的类型，选中后有白色方形边框标识，然后选择孔板布局区域",
        "的孔位（对应微孔板的96孔相应位置），表示该孔位为选中类型，该孔会显示对应板孔类型的名称及颜色。",
        " ",
			  #ifndef SOFTWARE_DN
        "再从”板孔类型”区域中选择需要的板孔类型。板孔类型有:BK、SD、QC、UD、EP、NC、PC七种类型。各孔类型定义如下：",
			  #else
			  "再从”板孔类型”区域中选择需要的板孔类型。板孔类型有:BK、SD、UD、EP、4种类型。各孔类型定义如下：",
			  #endif
        "：空白孔，用于检测时作为空白对照。",
        "：标准品孔，用于建立标准曲线的样品孔位。",
			  #ifndef SOFTWARE_DN
        "：质控品孔，检测时用于质控的样品孔。",
			  #endif
        "：未知样品孔,可以设置多个孔位未知样品孔。",
        "：无样品孔，表示微孔板中该孔位无任何样品。",
			  #ifndef SOFTWARE_DN
        "：阴性对照孔,可以设置多个孔位为阴性对照孔。",
        "：阳性对照孔,可以设置多个孔位为阳性对照孔。",
			  #endif
        "4/6"
    }*/
};
#define HELP_PROTOCOL_5_MAX 10
const char STR_HELP_PROTOCOL_5[LANGUAGE_TYPES][HELP_PROTOCOL_5_MAX][HELP_PROTOCEOL_CHAR_MAX]
= {""/*{
        "After setting all well type across the plate, press \"OK\" to return to the \"Protocol\" interface and start the plate reading.",
        "Standard sample concentration setting",
        "On the \"Plate Layout\" interface, press the \"Concentration\" button at the top right, and the concentration setting ",
        "interface screen will be displayed.",
        "12 standard samples will be displayed on this interface, only set the concentration for positions which have been set",
        "on the plate layout. Any which have not been set on the layout will not be measured.  You may leave the",
        "concentration values as they are ?do not change them to 0.",
        "After setting standards, press \"OK\" to confirm and return back to main Protocol interface.",
        " ",
        "5/6"
    },
    {
        "设置好微孔板各孔类型后，点击确认后返回程序主界面，可进行检测。如有标准样品则需要输入标样的浓度后返回进",
        "行检测。",
        "标准样品浓度设置",
        "在“微孔板布局”界面中，点击右侧的“浓度”按钮，出现浓度设置界面。",
        "在界面中显示所有12个标准样品的浓度设置，设置时只需对孔板布局中设置过的标准样品（对应序号）浓度值进行设置，",
        "没有在布局中设置的标准样品（对应序号）将不会参与结果运算。",
        "设置浓度时，只需点击标准样品（对应序号）右边的数字进行浓度输入。",
        "在界面右侧的“单位”按钮可进行标准样品浓度单位的选择，点击需要的单位，在原按键处显示当前选择单位。",
        "设置完成后点击“确认”，返回孔板设置界面。",
        "5/6"
    }*/
};
#define HELP_PROTOCOL_6_MAX 13
const char STR_HELP_PROTOCOL_6[LANGUAGE_TYPES][HELP_PROTOCOL_6_MAX][HELP_PROTOCEOL_CHAR_MAX]
= {""/*{
        "Shaker setting:",
        "In order to get more precise measurement result, this instrument incorporates a shaking mechanism.  Shaking can",
        "help ensure that all sample liquid is positioned to the bottom of the wells.",
        "On the \"Protocol\" interface, click \"Shake\" and this will open the \"Shake parameters\" interface for setting On or Off,",
        "speed and time.",

        "Calculate:",
        "The microplate reader can be programmed to calculate testing results (Kinetic, Pre-process, Curves.).  Refer to the",
        "full instruction manual for details.",
        "Interpret:",
        "Used to compare results to negative and positive controls.  In the \"Protocol\" interface, click on \"Interpret\". Click to",
        "the right side of the Interpret button to choose \"On\". Refer to the full instruction manual for details.",
	      #ifndef SOFTWARE_DN
        "Quality:  Refer to the full instruction manual for details.",
	      #else 
	      " ",
	      #endif
        "6/6"
    },
    {
        "振动设置",
        "为防止添加的溶液挂在微孔板的孔壁上，本仪器具有振动功能，可设置在检测前对微孔板进行振动操作，使溶液",
        "存于微孔板孔底部。以提高检测结果的准确性。",
        "在“程序”主界面，点击“振动”，进入“振动参数”界面。点击“振动”右侧浅蓝色区域，弹出打开、",
        "关闭选择，可点击相应功能进行启动振板功能和关闭设置。",
        "计算设置",
        "此部分参数设置主要对样品检测结果的数据处理方式进行详细设置。其中包含“动力学”、“预处理”、“曲线”。",
        "定性设置",
        "板布局中必须使用阴性、阳性设置。在“程序”界面按“定性”。选择“打开”选项，打开定性设置。",
			  #ifndef SOFTWARE_DN
        "质控设置",
			  "细节内容参见完整的仪器操作手册。",
			  #else
			  " ",
			  " ",
			  #endif
        " ",
        "6/6"
    }*/
};



//Result 界面
#define HELP_RESULT_1_MAX 8
const char STR_HELP_RESULT_1[LANGUAGE_TYPES][HELP_RESULT_1_MAX][HELP_PROTOCEOL_CHAR_MAX]
= {""/*{
        "Results Interface:",
        "The Results interface displays the measurement results after reading a plate.",
        "After completion of a plate reading, the \"Results\" interface will be displayed automatically, showing the current",
        "program measurement data. You can also enter the interface by clicking the \"Results\" tab at the top of the screen.",
        "On the \"Protocol\" interface, click \"Shake\" and this will open the \"Shake parameters\" interface for setting On or Off,",
        "Other choices in the Results Interface are \"Interpret\", \"Analysis\" for kinetic results, \"Curve\" and \"QC\".  See the full",
        "instruction manual for details of these results functions.",
        "1/1"
    },
    {
        "报告界面",
        "该界面主要显示检测完成后的各类计算数据结果。也可用于查看各程序最近一次检测保存的历史数据。",
        "在“程序”主界面运行样品检测后，软件自动跳转到“报告”界面，显示当前程序下样品检测的数据分析结果。也",
        "可点击软件界面上方的“报告”直接进入该界面。",
        "显示结果有两种类型，一种为常规检测，对样品进行定性、定量分析时的显示结果；此时显示的数据分析结果有：原",
        "始数据、定性分析、定量分析、标准曲线、质控分析，其中定性分析、定量分析、标准曲线、质控分析会根据“程序”",
        "设置中各项分析是否开启而显示相应计算结果，如果没有开启则仅显示按钮，点击时无数据显示。",
        "1/1"
    }*/
};

//设置界面
#define HELP_SETTING_1_MAX 11
const char STR_HELP_SETTING_1[LANGUAGE_TYPES][HELP_SETTING_1_MAX][HELP_PROTOCEOL_CHAR_MAX]
= {""/*{
        "Settings Interface:",
        "This section covers language settings, filters, maintenance, print, quality control, screen calibration, date and time",
        "settings.",
        "Filter setting:",
        "This instrument is equipped with four standard filters which have positions on the filter wheel from 1-4. Additional ",
        "filters are available, and a maximum of 8 filters can be installed.",
        "Please install new filters prior setting the program.  See the full instruction manual for details on installing new",
        "filters.",
        "After filter installation, click the blank position No. and input the wavelength, default unit is nm.",
        "Click \"Enter\" after setting information on any new filters.",
        "1/2"
    },
    {
        "设置界面",
        "该界面主要包括“语言设置”、“滤光片”、“维护”、“打印”和“日期时间”。",
        " ",
        "滤光片设置",
        "本仪器标准配置为4个滤光片通道，对应滤光片轮上的前4个位置（滤光片轮上有数字序号标识）。根据客户需求，最 ",
        "多可扩展到8个滤光片通道。",
        "有关安装新滤光片的详细信息，请参阅完整的说明书。",
        "滤光片安装后，单击空白位置“无”并输入波长，默认单位为“nm”。",
        "最后点击“确定”完成新滤光片的数据更新。",
        " ",
        "1/2"
    }*/
};

#define HELP_SETTING_2_MAX 11
const char STR_HELP_SETTING_2[LANGUAGE_TYPES][HELP_SETTING_2_MAX][HELP_PROTOCEOL_CHAR_MAX]
= {""/*{
        "Time and Date setting:",
        "Click \"Date & time\" to adjust the date and time.  The date format is month/date/Year, Time format is",
        "hour:minute:second.",
        "Maintenance:",
        "Always store the instrument in an environment that is dry and clean to prevent corrosion or damage from dust.  Also",
        "keep the instrument away from strong electromagnetic interference sources.",
        "The Instrument has been calibrated at the factory. There are no user serviceable parts inside (with the exception of",
        "changing the light source and filters). ",//For service please contact Benchmark Scientific.
        "Always make sure to use the proper input voltage.",
        "Please refer to the full instrument service manual for additional details on maintenance.",
        "2/2"
    },
    {
        "时间日期设置",
        "点击“日期时间”图标，进入时间设置界面。其时间格式为：日期:年/月/日；时间：时：分：秒。",
        " ",
        "仪器维护",
        "仪器必须存放在干燥和清洁的环境中，以防止腐蚀或损坏。同时必须保持仪器远离强电磁干扰源。",
        "该仪器出厂时，已经过校准，请用户勿随意拆卸和调节。当发现本仪器出现异常或不能正常工作时，应及时与厂家联",
        "系。",
        "电源电压必须符合规定范围。",
        "有关维修的其他细节，请参阅完整的仪器维修手册。",
        " ",
        "2/2"
    }*/
};

//关于
#define HELP_ABOUT_MAX 3
const char STR_HELP_ABOUT[LANGUAGE_TYPES][HELP_ABOUT_MAX][HELP_PROTOCEOL_CHAR_MAX]
= {""/*{
        "About:",
	      // #ifdef DEBUG_AS112
	      //  "Version: Debug",
	      #ifdef SOFTWARE_DN
	      "版本: m1.0.0 190318",  //m3.04 181114改为m1.0.0 190318
			   #else
	      "Version: 1.0.3 190619",
	      #endif
        //"Accuris Instruments, a division of Benchmark Scientific",
        // "www.accuris-usa.com",
        // "info@accuris-usa.com",
        //"(908)769-5555",
        "1/1",
    },
    {
        "关于",
			   //#ifdef DEBUG_AS112
	      //  "Version: Debug",
			   #ifdef SOFTWARE_DN
        "版本: m1.0.0 190318",	
			   #else
	      "Version: 1.0.3 190619",
	      #endif
        // "Accuris Instruments, a division of Benchmark Scientific",
        // "www.accuris-usa.com",
        // "info@accuris-usa.com",
        //"(908)769-5555",
        "1/1",
    }*/
};

//内容色定义
#define COLOR_HELP_HEAD    0x000000
#define COLOR_HELP_CONTENT 0xf00000



enum
{
    HELP_MENU_PROTOCOL=0, //步骤
    HELP_MENU_RESULTS,    //结果
    HELP_MENU_SETTINGS,   //设置
    HELP_MENU_ABOUT,      //关于
};
unsigned char HelpMenuFlag;                //帮助菜单标志
unsigned char HelpMenuPage;                //帮助菜单当前页


#define HELP_MENU_INC_Y  10
#define HELP_MENU_PAGE_POSY (HELP_BUTTON_STARTY+7)  //(STATUSBAR_POSY-25)
#define HELP_MENU_PAGE_POSX (HELP_BUTTON_POSX(4)+HELP_BUTTON_WIDTH+20)
//#define HELP_MENU_PAGE_POSX (HELP_BUTTON_POSX(5))
//#define HELP_MENU_PAGE_STARTY HELP_BUTTON_STARTY
//#define HELP_MENU_PAGE_ENDY   HELP_BUTTON_ENDY


#define HELP_LAY_SMALL_DIS  (LAY_SMALL_HIGH+10)
//extern BUTTON_Handle HelpButton[6];//HELP_BUTTON_NUM


extern GUI_MEMDEV_Handle    hBKMempic;
extern GUI_MEMDEV_Handle    hUDMempic;
extern GUI_MEMDEV_Handle    hEPMempic;
extern GUI_MEMDEV_Handle    hNCMempic;
extern GUI_MEMDEV_Handle    hPCMempic;
extern GUI_MEMDEV_Handle    hSDMempic;
extern GUI_MEMDEV_Handle    hQCMempic;


void HelpMenuInit(void)
{
    HelpMenuFlag=HELP_MENU_PROTOCOL;
    HelpMenuPage=0;
}
void DrawHelpLayout(short sx,short sy)
{
    short x,y;
    unsigned char i;
    GUI_RECT rect,rect1;

    x = sx + LAY_SMALL_RADIUS; //2014-8-17项
    y = sy + LAY_SMALL_RADIUS ;


    //	GUI_SetColor(0x000000);
    //BK
    GUI_MEMDEV_WriteAt(hBKMempic,x-LAY_SMALL_RADIUS,y - LAY_SMALL_RADIUS+ TITLESBAR_HEIGHT); //BK
    strcpy(ConvertStr, WELLS_TYPE_STR[WELLS_TYPE_BK]);
    rect.x0 = x - LAY_SMALL_RADIUS;
    rect.x1 = x + LAY_SMALL_RADIUS;
    rect.y0 = y - LAY_SMALL_RADIUS ;
    rect.y1 = y + LAY_SMALL_RADIUS ;
    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //解释说明
    rect1.x0 = rect.x1+10;
    rect1.x1 = rect1.x0+300;
    rect1.y0 = rect.y0 ;
    rect1.y1 = rect.y1 ;
    strcpy(ConvertStr,STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][HELP_PROTOCOL_4_WORD_MAX]);
    GUI_DispStringInRect(ConvertStr, &rect1, GUI_TA_LEFT | GUI_TA_VCENTER);


    //SD
    rect.y0 += HELP_LAY_SMALL_DIS;
    rect.y1 = rect.y0 + LAY_SMALL_RADIUS;

    GUI_MEMDEV_WriteAt(hSDMempic,x-LAY_SMALL_RADIUS,rect.y0  + TITLESBAR_HEIGHT);
    strcpy(ConvertStr, WELLS_TYPE_STR[WELLS_TYPE_SD]);


    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //01
    strcpy(ConvertStr,"1");
    rect.y0 = rect.y1;
    rect.y1 = rect.y0 + LAY_SMALL_RADIUS;
    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);

    //解释说明
    rect1.y0  += HELP_LAY_SMALL_DIS;
    rect1.y1  += HELP_LAY_SMALL_DIS;
    strcpy(ConvertStr,STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][HELP_PROTOCOL_4_WORD_MAX+1]);
    GUI_DispStringInRect(ConvertStr, &rect1, GUI_TA_LEFT | GUI_TA_VCENTER);
#ifndef SOFTWARE_DN
    //QC
    rect.y0 += HELP_LAY_SMALL_DIS- LAY_SMALL_RADIUS;
    rect.y1 = rect.y0 + LAY_SMALL_RADIUS;

    GUI_MEMDEV_WriteAt(hQCMempic,x-LAY_SMALL_RADIUS,rect.y0 + TITLESBAR_HEIGHT);
    strcpy(ConvertStr, WELLS_TYPE_STR[WELLS_TYPE_QC]);

    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);

    strcpy(ConvertStr,"1");
    rect.y0 = rect.y1;
    rect.y1 = rect.y0 + LAY_SMALL_RADIUS;
    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);

    //解释说明
    rect1.y0  += HELP_LAY_SMALL_DIS;
    rect1.y1  += HELP_LAY_SMALL_DIS;
    strcpy(ConvertStr,STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][HELP_PROTOCOL_4_WORD_MAX+2]);
    GUI_DispStringInRect(ConvertStr, &rect1, GUI_TA_LEFT | GUI_TA_VCENTER);

    //UD
    rect.y0 += HELP_LAY_SMALL_DIS- LAY_SMALL_RADIUS;
    rect.y1 = rect.y0 + LAY_SMALL_RADIUS*2;
    GUI_MEMDEV_WriteAt(hUDMempic,x-LAY_SMALL_RADIUS,rect.y0 + TITLESBAR_HEIGHT);
    strcpy(ConvertStr, WELLS_TYPE_STR[WELLS_TYPE_UD]);

    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //解释说明
    rect1.y0  += HELP_LAY_SMALL_DIS;
    rect1.y1  += HELP_LAY_SMALL_DIS;
    strcpy(ConvertStr,STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][HELP_PROTOCOL_4_WORD_MAX+3]);
    GUI_DispStringInRect(ConvertStr, &rect1, GUI_TA_LEFT | GUI_TA_VCENTER);

    //EP(第2行)
    rect.x0 = 400;
    rect.x1 = rect.x0 + LAY_SMALL_RADIUS*2;
    rect.y0 = y - LAY_SMALL_RADIUS ;
    rect.y1 = y + LAY_SMALL_RADIUS ;

    GUI_MEMDEV_WriteAt(hEPMempic,rect.x0,rect.y0+ TITLESBAR_HEIGHT);

    strcpy(ConvertStr, WELLS_TYPE_STR[WELLS_TYPE_EP]);
    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);

    //解释说明
    rect1.y0  = rect.y0;
    rect1.y1  = rect.y1;
    rect1.x0  =rect.x1+10;
    rect1.x1  =799;
    strcpy(ConvertStr,STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][HELP_PROTOCOL_4_WORD_MAX+4]);
    GUI_DispStringInRect(ConvertStr, &rect1, GUI_TA_LEFT | GUI_TA_VCENTER);



    //NC
    rect.y0 += HELP_LAY_SMALL_DIS;
    rect.y1 = rect.y0 + LAY_SMALL_RADIUS*2;
    GUI_MEMDEV_WriteAt(hNCMempic,rect.x0,rect.y0+ TITLESBAR_HEIGHT);
    strcpy(ConvertStr, WELLS_TYPE_STR[WELLS_TYPE_NC]);

    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);

    //解释说明
    rect1.y0  += HELP_LAY_SMALL_DIS;
    rect1.y1  += HELP_LAY_SMALL_DIS;
    strcpy(ConvertStr,STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][HELP_PROTOCOL_4_WORD_MAX+5]);
    GUI_DispStringInRect(ConvertStr, &rect1, GUI_TA_LEFT | GUI_TA_VCENTER);
    //PC
    rect.y0 += HELP_LAY_SMALL_DIS;
    rect.y1 = rect.y0 + LAY_SMALL_RADIUS*2;
    GUI_MEMDEV_WriteAt(hPCMempic,rect.x0,rect.y0+ TITLESBAR_HEIGHT);
    strcpy(ConvertStr, WELLS_TYPE_STR[WELLS_TYPE_PC]);

    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);

    //解释说明
    rect1.y0  += HELP_LAY_SMALL_DIS;
    rect1.y1  += HELP_LAY_SMALL_DIS;
    strcpy(ConvertStr,STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][HELP_PROTOCOL_4_WORD_MAX+6]);
    GUI_DispStringInRect(ConvertStr, &rect1, GUI_TA_LEFT | GUI_TA_VCENTER);
#else
   //UD
    rect.y0 += HELP_LAY_SMALL_DIS- LAY_SMALL_RADIUS;
    rect.y1 = rect.y0 + LAY_SMALL_RADIUS*2;
    GUI_MEMDEV_WriteAt(hUDMempic,x-LAY_SMALL_RADIUS,rect.y0 + TITLESBAR_HEIGHT);
    strcpy(ConvertStr, WELLS_TYPE_STR[WELLS_TYPE_UD]);

    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //解释说明
    rect1.y0  += HELP_LAY_SMALL_DIS;
    rect1.y1  += HELP_LAY_SMALL_DIS;
    strcpy(ConvertStr,STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][HELP_PROTOCOL_4_WORD_MAX+2]);
    GUI_DispStringInRect(ConvertStr, &rect1, GUI_TA_LEFT | GUI_TA_VCENTER);
  //EP
    rect.y0 += HELP_LAY_SMALL_DIS;
    rect.y1 = rect.y0 + LAY_SMALL_RADIUS*2;
    GUI_MEMDEV_WriteAt(hEPMempic,x-LAY_SMALL_RADIUS,rect.y0 + TITLESBAR_HEIGHT);
    strcpy(ConvertStr, WELLS_TYPE_STR[WELLS_TYPE_EP]);

    GUI_DispStringInRect(ConvertStr, &rect, GUI_TA_HCENTER | GUI_TA_VCENTER);
    //解释说明
    rect1.y0  += HELP_LAY_SMALL_DIS;
    rect1.y1  += HELP_LAY_SMALL_DIS;
    strcpy(ConvertStr,STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][HELP_PROTOCOL_4_WORD_MAX+3]);
    GUI_DispStringInRect(ConvertStr, &rect1, GUI_TA_LEFT | GUI_TA_VCENTER);
#endif
}

void DisplayHelp(void)
{
    //char str[5];
    unsigned char i;
    unsigned short y,x,m,y_dis,out_y;


    y_dis=22;
    x=20;
    y=10+CONTENTBAR_TITLE_HEIGHT;
    m=0;


    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        GUI_SetFont(GUI_FONT_16B_ASCII);//GUI_FONT_MED);
    }
    else
    {
        GUI_SetFont(GUI_FONT_HELP_CH);
    }
    switch (HelpMenuFlag)
    {
    case HELP_MENU_PROTOCOL:
        out_y=y;
        if(HelpMenuPage==0)
        {
            for(i=0; i<HELP_PROTOCOL_1_MAX-1; i++)
            {
                if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                {
                    if( (i==0)||(i==2) )GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if(i==10)out_y+=HELP_MENU_INC_Y;
                }
                else
                {
                    if( (i==0)||(i==2) )GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if(i==2)out_y+=HELP_MENU_INC_Y;
                }

                GUI_DispStringAt(STR_HELP_PROTOCOL_1[SystemPrameter.SystemLanguage][i],x,out_y);
                out_y+=y_dis;
            }

            //显示页码,用英文
            GUI_SetFont(GUI_FONT_BIG);
            GUI_SetColor(COLOR_TITLE_WORD);
            GUI_DispStringAt(STR_HELP_PROTOCOL_1[SystemPrameter.SystemLanguage][i],HELP_MENU_PAGE_POSX,HELP_MENU_PAGE_POSY);
        }
        else if(HelpMenuPage==1)
        {
            for(i=0; i<HELP_PROTOCOL_2_MAX-1; i++)
            {
                if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                {
                    if(i==6)GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==2)||(i==6) )out_y+=HELP_MENU_INC_Y;
                }
                else
                {
                    if( (i==1)||(i==5) )GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==1)||(i==5) )out_y+=HELP_MENU_INC_Y;
                }

                GUI_DispStringAt(STR_HELP_PROTOCOL_2[SystemPrameter.SystemLanguage][i],x,out_y);
                out_y+=y_dis;
            }

            GUI_SetFont(GUI_FONT_BIG);
            GUI_SetColor(COLOR_TITLE_WORD);
            GUI_DispStringAt(STR_HELP_PROTOCOL_2[SystemPrameter.SystemLanguage][i],HELP_MENU_PAGE_POSX,HELP_MENU_PAGE_POSY);
        }
        else if(HelpMenuPage==2)
        {
            for(i=0; i<HELP_PROTOCOL_3_MAX-1; i++)
            {
                if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                {
                    if( (i==0)||(i==5)||(i==9)  )GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==3)||(i==9) )out_y+=HELP_MENU_INC_Y;
                }
                else
                {
                    if( (i==0)||(i==1)||(i==7)  )GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if(i==7)out_y+=HELP_MENU_INC_Y;
                }

                GUI_DispStringAt(STR_HELP_PROTOCOL_3[SystemPrameter.SystemLanguage][i],x,out_y);
                out_y+=y_dis;
            }
            GUI_SetFont(GUI_FONT_BIG);
            GUI_SetColor(COLOR_TITLE_WORD);
            GUI_DispStringAt(STR_HELP_PROTOCOL_3[SystemPrameter.SystemLanguage][i],HELP_MENU_PAGE_POSX,HELP_MENU_PAGE_POSY);
        }
        else if(HelpMenuPage==3)
        {

            GUI_SetColor(COLOR_HELP_CONTENT);
            for(i=0; i<HELP_PROTOCOL_4_WORD_MAX; i++)
            {

                if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                {
                    if((i==3)||(i==4) )out_y+=HELP_MENU_INC_Y;
                }
                else
                {
                    //if( (i==0)||(i==2) )GUI_SetColor(COLOR_HELP_HEAD);
                    // else GUI_SetColor(COLOR_HELP_CONTENT);
                    if(i==4)out_y+=HELP_MENU_INC_Y;
                }

                GUI_DispStringAt(STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][i],x,out_y);
                if(i<=4)out_y+=y_dis;
                else out_y+=25;
            }
            DrawHelpLayout(x,out_y+HELP_MENU_INC_Y);  //显示图标及文字
            GUI_SetFont(GUI_FONT_BIG);
            GUI_SetColor(COLOR_TITLE_WORD);
            GUI_DispStringAt(STR_HELP_PROTOCOL_4[SystemPrameter.SystemLanguage][HELP_PROTOCOL_4_MAX-1],HELP_MENU_PAGE_POSX,HELP_MENU_PAGE_POSY);
        }
        else if(HelpMenuPage==4)
        {
            for(i=0; i<HELP_PROTOCOL_5_MAX-1; i++)
            {
                if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                {
                    if(i==1)GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==1)||(i==4)||(i==7) )out_y+=HELP_MENU_INC_Y;
                }
                else
                {
                    if(i==2)GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==2)||(i==4)||(i==6)||(i==7)||(i==8) )out_y+=HELP_MENU_INC_Y;
                }

                GUI_DispStringAt(STR_HELP_PROTOCOL_5[SystemPrameter.SystemLanguage][i],x,out_y);
                out_y+=y_dis;
            }
            GUI_SetFont(GUI_FONT_BIG);
            GUI_SetColor(COLOR_TITLE_WORD);
            GUI_DispStringAt(STR_HELP_PROTOCOL_5[SystemPrameter.SystemLanguage][i],HELP_MENU_PAGE_POSX,HELP_MENU_PAGE_POSY);
        }
        else if(HelpMenuPage==5)
        {
            for(i=0; i<HELP_PROTOCOL_6_MAX-1; i++)
            {
                if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                {
                    if( (i==0)||(i==5)||(i==8)||(i==11) )GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==3)||(i==5) )out_y+=HELP_MENU_INC_Y;
                }
                else
                {
                    if( (i==0)||(i==5)||(i==7)||(i==9))GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==5)||(i==7)||(i==9) )out_y+=HELP_MENU_INC_Y;
                }

                GUI_DispStringAt(STR_HELP_PROTOCOL_6[SystemPrameter.SystemLanguage][i],x,out_y);
                out_y+=y_dis;
            }
            GUI_SetFont(GUI_FONT_BIG);
            GUI_SetColor(COLOR_TITLE_WORD);
            GUI_DispStringAt(STR_HELP_PROTOCOL_6[SystemPrameter.SystemLanguage][i],HELP_MENU_PAGE_POSX,HELP_MENU_PAGE_POSY);
        }
        break;
    case HELP_MENU_RESULTS:
        out_y=y;
        for(i=0; i<HELP_RESULT_1_MAX-1; i++)
        {
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                if(i==0)GUI_SetColor(COLOR_HELP_HEAD);
                else GUI_SetColor(COLOR_HELP_CONTENT);
                // if((i==1)||(i==2) )out_y+=HELP_MENU_INC_Y;
            }
            else
            {
                if(i==0)GUI_SetColor(COLOR_HELP_HEAD);
                else GUI_SetColor(COLOR_HELP_CONTENT);
                if((i==2)||(i==4) )out_y+=HELP_MENU_INC_Y;

            }

            GUI_DispStringAt(STR_HELP_RESULT_1[SystemPrameter.SystemLanguage][i],x,out_y);
            out_y+=y_dis;
        }
        GUI_SetFont(GUI_FONT_BIG);
        GUI_SetColor(COLOR_TITLE_WORD);
        GUI_DispStringAt(STR_HELP_RESULT_1[SystemPrameter.SystemLanguage][i],HELP_MENU_PAGE_POSX,HELP_MENU_PAGE_POSY);
        break;
    case HELP_MENU_SETTINGS:
        //WM_ShowWindow(BtToolsButton[TOOLS_BUTTON_3]);       //???????
        //WM_ShowWindow(BtToolsButton[TOOLS_BUTTON_4]);
        out_y=y;
        if(HelpMenuPage==0)
        {
            for(i=0; i<HELP_SETTING_1_MAX-1; i++)
            {
                if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                {
                    if( (i==0)||(i==3) )GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==6)||(i==8)||(i==9) )out_y+=HELP_MENU_INC_Y;
                }
                else
                {
                    if( (i==0)||(i==3) )GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==6)||(i==7)||(i==8)  )out_y+=HELP_MENU_INC_Y;
                }

                GUI_DispStringAt(STR_HELP_SETTING_1[SystemPrameter.SystemLanguage][i],x,out_y);
                out_y+=y_dis;
            }
            GUI_SetFont(GUI_FONT_BIG);
            GUI_SetColor(COLOR_TITLE_WORD);
            GUI_DispStringAt(STR_HELP_SETTING_1[SystemPrameter.SystemLanguage][i],HELP_MENU_PAGE_POSX,HELP_MENU_PAGE_POSY);
        }
        else if(HelpMenuPage==1)
        {
            for(i=0; i<HELP_SETTING_2_MAX-1; i++)
            {
                if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
                {
                    if( (i==0)||(i==3) )GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==3)||(i==6)||(i==8) )out_y+=HELP_MENU_INC_Y;
                }
                else
                {
                    if( (i==0)||(i==3) )GUI_SetColor(COLOR_HELP_HEAD);
                    else GUI_SetColor(COLOR_HELP_CONTENT);

                    if((i==7)||(i==8) )out_y+=HELP_MENU_INC_Y;
                }

                GUI_DispStringAt(STR_HELP_SETTING_2[SystemPrameter.SystemLanguage][i],x,out_y);
                out_y+=y_dis;
            }
            GUI_SetFont(GUI_FONT_BIG);
            GUI_SetColor(COLOR_TITLE_WORD);
            GUI_DispStringAt(STR_HELP_SETTING_2[SystemPrameter.SystemLanguage][i],HELP_MENU_PAGE_POSX,HELP_MENU_PAGE_POSY);
        }

        break;

    case HELP_MENU_ABOUT:
        out_y=y;
        for(i=0; i<HELP_ABOUT_MAX-1; i++)
        {
            if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
            {
                if(i==0)GUI_SetColor(COLOR_HELP_HEAD);
                else GUI_SetColor(COLOR_HELP_CONTENT);
            }
            else
            {
                if(i==0)GUI_SetColor(COLOR_HELP_HEAD);
                else GUI_SetColor(COLOR_HELP_CONTENT);
            }
            if((i==1)||(i==2) )out_y+=HELP_MENU_INC_Y;
#ifndef DEBUG_SCREEN
            GUI_DispStringAt(STR_HELP_ABOUT[SystemPrameter.SystemLanguage][i],x,out_y);
#endif
            out_y+=y_dis;
        }
        DrawHelpPicture();
        GUI_SetFont(GUI_FONT_BIG);
        GUI_SetColor(COLOR_TITLE_WORD);
        GUI_DispStringAt(STR_HELP_ABOUT[SystemPrameter.SystemLanguage][i],HELP_MENU_PAGE_POSX,HELP_MENU_PAGE_POSY);

        break;
    default:
        break;
    }


}