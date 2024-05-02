#include "bsp.h"
#include "MainTask.h"


const char CH_STR_FILTER[LANGUAGE_TYPES][20] = {"Filter: ", "Filtro: "};//{"Filter :", "ÂË  ¹â  Æ¬£º"};
const char CH_STR_NO[LANGUAGE_TYPES][10] = {"No", "Nao"};
const char CH_STR_OFF[LANGUAGE_TYPES][8] = {"Off","Off"};
const char CH_STR_MODE[LANGUAGE_TYPES][20] = {"Mode: ", "Modo: "};
const char CH_STR_MODE_NORMAL[LANGUAGE_TYPES][10] = {"Normal", "Normal"};
const char CH_STR_MODE_FAST[LANGUAGE_TYPES][10] = {"Fast", "Rapido"};
const char CH_SETUP_SHAKE_SHAKE[LANGUAGE_TYPES][20] = {"Shake: ", "Agitacao: "};
const char CH_SETUP_SHAKE_SPEED[LANGUAGE_TYPES][20] = {"Speed: ", "velocidade: "};
const char CH_SETUP_SHAKE_TIME[LANGUAGE_TYPES][20] = {"Time: ", "Duracao: "};

const char CH_STR_SHAKE_SPEED_SLOW[LANGUAGE_TYPES][15] = {"Slow", "Lento"};
const char CH_STR_SHAKE_SPEED_NORMAL[LANGUAGE_TYPES][15] = {"Normal", "Normal"};
const char CH_STR_SHAKE_SPEED_FAST[LANGUAGE_TYPES][15] = {"Fast","Rapido"};
const char CH_STR_OPEN[LANGUAGE_TYPES][10] = {"On", "On"};
const char CH_STR_CLOSE[LANGUAGE_TYPES][10] = {"Off", "Off"};
const char CH_STR_PREPROCESS[LANGUAGE_TYPES][20] = {"Preprocess: ", "Modo: "};
const char CH_STR_KINETIC[LANGUAGE_TYPES][20] = {"Kinetic: ", "Cinetica: "};
const char CH_STR_CURVE[LANGUAGE_TYPES][20] = {"Curve: ","Curva: "};
const char CH_CALCULATE_READINGS[LANGUAGE_TYPES][20] = {"Readings", "Leituras"};
const char CH_CALCULATE_CURVES[LANGUAGE_TYPES][10] = {"Curve", "Curva"};
const char CH_CALCULATE_INTERVAL[LANGUAGE_TYPES][15] = {"Interval" , "Intervalo"};
const char CH_CALCULATE_KINETIC[LANGUAGE_TYPES][10] = {"Kinetic", "Cinetica"};
const char CH_CALCULATE_PREPROCESS[LANGUAGE_TYPES][12] = {"Preprocess", "Modo"};
//Interpret
const char CH_STR_INTERPRET[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = {"Interpret", "Qualitativo"};
const char CH_STR_ABS[LANGUAGE_TYPES][20] = {"ABS","Absorbancia"};
const char CH_STR_CONC[LANGUAGE_TYPES][20] = {"Conc.","Concentracao"};
const char CH_STR_CUTOFF[LANGUAGE_TYPES][10] = {"Cutoff", "Cutoff"};
const char CH_STR_LAYOUT[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = {"Layout","Layout"};
const char CH_STR_INTERPRET_SOURCE[LANGUAGE_TYPES][15] = {"Source", "Origem"};
const char CH_STR_QUALITY_TITLE[LANGUAGE_TYPES][LANGUAGE_CHAR_MAX] = {"QC","CQ"};
const char CH_STR_INTERPRET_CUTOFF[LANGUAGE_TYPES][15] = {"Cutoff: ", "Cutoff: "};
const char CH_STR_INTERPRET_POS[LANGUAGE_TYPES][20] = {"Positive: ", "Positivo: "};
const char CH_STR_INTERPRET_WEAK_POS[LANGUAGE_TYPES][40] = {"Weak Postive: (+/- Cutoff %)", "Positivo Fraco: (+/- Cutoff %)"};


const char CH_STR_TABLE_RECORD_NO[LANGUAGE_TYPES][10] = {"No", "No."};
const char CH_QUALITY_TABLE_TARGET[LANGUAGE_TYPES][10] = {"Target", "Alvo"};
const char CH_QUALITY_TABLE_SD[LANGUAGE_TYPES][15] = {"SD", "PD"};
const char CH_QUALITY_TABLE_CV[LANGUAGE_TYPES][15] = {"CV%", "CV%"};
const char CH_QUALITY_TABLE_UPPER_LIMIT[LANGUAGE_TYPES][17] = {"Upper limit", "Limite superior"};
const char CH_QUALITY_TABLE_LOWER_LIMIT[LANGUAGE_TYPES][17] = {"Lower limit", "Limite inferior"};
const char CH_QUALITY_TABLE_RESULT[LANGUAGE_TYPES][10]= {"Result","Resultado"};
const char CH_SELECT_CONTROL_REPORT_FILTER1[LANGUAGE_TYPES][15] = {"Filter 1", "Filtro 1"};
const char CH_SELECT_CONTROL_REPORT_FILTER2[LANGUAGE_TYPES][15] = {"Filter 2", "Filtro 2"};
const char CH_SELECT_CONTROL_REPORT_FILTER12[LANGUAGE_TYPES][20] = {"Filter 1&2", "Filtro 1&2"};
const char CH_REFERENCE_SELECT[LANGUAGE_TYPES][2][10] = {{"Conc.", "ABS"}, {"Conc.", "ABS"}};
const char CH_KINETIC_READINGS[LANGUAGE_TYPES][10] = {"Readings", "Leituras"};
const char CH_STR_QUALITY_RESULT[LANGUAGE_TYPES][2][10] = {{"Passed","Failed"}, {"Aprovado"," Falhou"}}; //½á¹ûÏÔÊ¾

const char CH_KINETIC_ANALYSIS_SELECTION[2][LANGUAGE_TYPES][KINETIC_ANALYSIS_MAX][20]
= {{{"Average", "Max.", "Time to", "Time to", "Well Max.", "Time to"}
        , {"Taxa ", "Taxa. ", "Tempo de ", "Tempo de ", "Conc. Max. ", "Tempo de "}
    }
    , {{"rate", "rate", "Max. Rate", "Change", "Conc.", "Max. Conc."}
        , {"Media", "Max.", "Taxa Max.", "Mudanca", "de Poco", "Conc. Max."}
    }
};

char CH_BASE_INFORAMTION[LANGUAGE_TYPES][32] = {"Base Info:", "Informacoes basicas:"};
//File Name
const char CH_FILE_NAME[LANGUAGE_TYPES][32] = {"File Name:", "Nome do arquivo:"};


const char CH_SETUP_PAUSE_TIME[LANGUAGE_TYPES][30] = {"Pause Time: ", "Tempo de pausa: "};
const char CH_SHAKE_MODE[LANGUAGE_TYPES][2][10]= {{"First", "Each"}, {"Primeiro ","Cada"}};

const char STR_INTERPRET_POS_DN2[LANGUAGE_TYPES][20] = {"Positive: > ", "Positivo: > "};  //DN???ó
const char STR_INTERPRET_WEAK_POS_DN2[LANGUAGE_TYPES][40] = {"Weak Positive: > ", "Positivo Fraco: > "};//DN???ó
const char STR_INTERPRET_LIMIT_DN2[LANGUAGE_TYPES][20] = {"Limit: > ", "Limite: > "};//DN???ó


void AddInterpretAbs(void)
{
    //strcat(CsvConvertStr,ConvertStr);
    //6.3.定性参数-临界值
    strcpy(ConvertStr,CH_STR_INTERPRET_CUTOFF[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,"\n");
    //阴性对照
    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        strcat(ConvertStr,"NC Coef: ");
    }
    else
    {
        strcat(ConvertStr,"CN Coef: ");
    }
    strcat(CsvConvertStr,ConvertStr);
    sprintf(ConvertStr,"%1.2f",BoardInf.InterpretPara.fCoef[0]);
    strcat(ConvertStr,"\n");

    //阳性对照
    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        strcat(ConvertStr,"PC Coef: ");
    }
    else
    {
        strcat(ConvertStr,"CP Coef:");
    }Limit:
    strcat(CsvConvertStr,ConvertStr);

    sprintf(ConvertStr,"%1.2f",BoardInf.InterpretPara.fCoef[1]);
    strcat(ConvertStr,"\n");

    //常数
    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        strcat(ConvertStr,"Constant: ");
    }
    else
    {
        strcat(ConvertStr,"Constante: ");
    }
    strcat(CsvConvertStr,ConvertStr);
    sprintf(ConvertStr,"%1.2f",BoardInf.InterpretPara.fCoef[2]);
    strcat(ConvertStr,"\n");
    //strcat(CsvConvertStr,ConvertStr);

    //6.4.定性参数-弱阳性
    strcat(ConvertStr,CH_STR_INTERPRET_WEAK_POS[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,": ");
    strcat(CsvConvertStr,ConvertStr);


    sprintf(ConvertStr,"%1.2f",BoardInf.InterpretPara.fWeakPValue);
    strcat(ConvertStr,"\n");
    //strcat(CsvConvertStr,ConvertStr);

    //6.5.定性参数-阳性条件
    strcat(ConvertStr,CH_STR_INTERPRET_POS[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,"  ");
    if(BoardInf.InterpretPara.GreatFlag)
    {
        strcat(ConvertStr,">");
    }
    else
    {
        strcat(ConvertStr,"<");
    }
    strcat(ConvertStr,"\n\n");
    strcat(CsvConvertStr,ConvertStr);
}


void SetParameterContent(void)
{
    unsigned char i,j;

    strcpy(CsvConvertStr,"");//先清空
    //1.标题，基本信息
    strcat(CsvConvertStr,"\n");
    strcat(CsvConvertStr,CH_BASE_INFORAMTION[SystemPrameter.SystemLanguage]);
    strcat(CsvConvertStr,"\n");
    //文件名
    strcat(CsvConvertStr,CH_FILE_NAME[SystemPrameter.SystemLanguage]);
    strcat(CsvConvertStr,BoardInf.Name);
    strcat(CsvConvertStr,"\n");

    //2.测量参数-滤光片
    strcat(CsvConvertStr,CH_STR_FILTER[SystemPrameter.SystemLanguage]);
    if(BoardInf.Filter1Locate<0)
    {
        strcpy(ConvertStr,CH_STR_NO[SystemPrameter.SystemLanguage]);
    }
    else
    {
        sprintf(ConvertStr,"%d",FilterLun.Filter[BoardInf.Filter1Locate]);
        strcat(ConvertStr,"nm");
    }
    strcat(ConvertStr," / ");
    strcat(CsvConvertStr,ConvertStr);
    if(BoardInf.Filter2Locate<0)
    {
        strcpy(ConvertStr,CH_STR_OFF[SystemPrameter.SystemLanguage]);//Off
    }
    else
    {
        sprintf(ConvertStr,"%d",FilterLun.Filter[BoardInf.Filter2Locate]);
        strcat(ConvertStr,"nm");
    }

    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);

    //3.测量参数-检测模式
    strcpy(ConvertStr,CH_STR_MODE[SystemPrameter.SystemLanguage]);
    if(BoardInf.DetectMode==MODE_NORMAL)
    {
        strcat(ConvertStr,CH_STR_MODE_NORMAL[SystemPrameter.SystemLanguage]);
    }
    else
    {
        strcat(ConvertStr,CH_STR_MODE_FAST[SystemPrameter.SystemLanguage]);
    }
    strcat(ConvertStr,"\n\n");
    strcat(CsvConvertStr,ConvertStr);

    //4.1.振动参数-是否开启
    strcpy(ConvertStr,CH_SETUP_SHAKE_SHAKE[SystemPrameter.SystemLanguage]);
    if(BoardInf.ShakeEnable)
    {
        strcat(ConvertStr,CH_STR_OPEN[SystemPrameter.SystemLanguage]);
    }
    else
    {
        strcat(ConvertStr,CH_STR_CLOSE[SystemPrameter.SystemLanguage]);
    }
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);


    //4.2.振动参数-振动速度
    strcpy(ConvertStr,CH_SETUP_SHAKE_SPEED[SystemPrameter.SystemLanguage]);
    if(BoardInf.ShakeSpeed==SHAKE_SPEED_SLOW)
    {
        strcat(ConvertStr,CH_STR_SHAKE_SPEED_SLOW[SystemPrameter.SystemLanguage]);
    }
    else if(BoardInf.ShakeSpeed==SHAKE_SPEED_NORMAL)
    {
        strcat(ConvertStr,CH_STR_SHAKE_SPEED_NORMAL[SystemPrameter.SystemLanguage]);
    }
    else
    {
        strcat(ConvertStr,CH_STR_SHAKE_SPEED_FAST[SystemPrameter.SystemLanguage]);
    }
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);

    //4.3.振动参数-振动时间
    strcat(CsvConvertStr,CH_SETUP_SHAKE_TIME[SystemPrameter.SystemLanguage]);
    sprintf(ConvertStr,"%02d : %02d : %02d",BoardInf.ShakeTime/3600,BoardInf.ShakeTime%3600/60,BoardInf.ShakeTime%60);
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);

    //4.4.振动模式-首次 每次

    if( (BoardInf.ShakeMode==SHAKE_FIRST)||(BoardInf.ShakeMode==SHAKE_EACH) )
    {
        strcpy(ConvertStr,CH_STR_MODE[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,CH_SHAKE_MODE[SystemPrameter.SystemLanguage][BoardInf.ShakeMode]);
        strcat(ConvertStr,"\n");
        strcat(CsvConvertStr,ConvertStr);
    }



    //4.5.振动参数-暂停时间
    strcat(CsvConvertStr,CH_SETUP_PAUSE_TIME[SystemPrameter.SystemLanguage]);
    sprintf(ConvertStr,"%02d : %02d : %02d",BoardInf.PauseTime/3600,BoardInf.PauseTime%3600/60,BoardInf.PauseTime%60);
    strcat(ConvertStr,"\n\n");
    strcat(CsvConvertStr,ConvertStr);

    //5.1.计算参数-预处理
    strcpy(ConvertStr,CH_STR_PREPROCESS[SystemPrameter.SystemLanguage]);
    if ((BoardInf.KineticPara.PreProcess<PRE_CALCULATE_MAX) && (BoardInf.KineticPara.PreProcess >PRE_CALCULATE_NO ))
        //if(BoardInf.KineticPara.PreProcess<PRE_CALCULATE_MAX)
    {
        strcat(ConvertStr,PRE_CALCULATE_STR[ BoardInf.KineticPara.PreProcess]);
    }
    else //if (BoardInf.KineticPara.PreProcess == 0)
    {
        strcat(ConvertStr,CH_STR_CLOSE[SystemPrameter.SystemLanguage]);// "Off");
    }
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);


    //5.2.计算参数-动力学
    strcpy(ConvertStr,CH_STR_KINETIC[SystemPrameter.SystemLanguage]);
    if (BoardInf.KineticPara.Enable)
        //if(BoardInf.KineticPara.PreProcess<PRE_CALCULATE_MAX)
    {
        strcat(ConvertStr,CH_STR_OPEN[SystemPrameter.SystemLanguage]);
    }
    else //if (BoardInf.KineticPara.PreProcess == 0)
    {
        strcat(ConvertStr,CH_STR_CLOSE[SystemPrameter.SystemLanguage]);// "Off");
    }
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);


    //5.3.计算参数-动力学读数
    strcpy(ConvertStr,CH_CALCULATE_READINGS[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,": ");
    sprintf(StrTemp,"%d",BoardInf.KineticPara.Readings);
    strcat(ConvertStr,StrTemp);
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);
    //5.4.计算参数-动力学间隔时间
    strcpy(ConvertStr,CH_CALCULATE_INTERVAL[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,": ");
    sprintf(StrTemp,"%02d : %02d : %02d",BoardInf.KineticPara.TimeInterval/3600,BoardInf.KineticPara.TimeInterval%3600/60,BoardInf.KineticPara.TimeInterval%60);
    strcat(ConvertStr,StrTemp);
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);

    //5.5.计算参数-标准曲线
    strcpy(ConvertStr,CH_STR_CURVE[SystemPrameter.SystemLanguage]);
    if(BoardInf.KineticPara.Curve==CURVE_NO)////////
    {
        strcat(ConvertStr,CH_STR_OFF[SystemPrameter.SystemLanguage]);
    }
    else
    {
        strcat(ConvertStr,CH_STR_OPEN[SystemPrameter.SystemLanguage]);
    }
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);

    //6.1.定性参数-打开
    strcpy(ConvertStr,CH_STR_INTERPRET[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,": ");
    if(BoardInf.InterpretPara.Enable)
    {
        strcat(ConvertStr,CH_STR_OPEN[SystemPrameter.SystemLanguage]);
    }
    else
    {
        strcat(ConvertStr,CH_STR_OFF[SystemPrameter.SystemLanguage]);
    }
    //strcat(ConvertStr,FUNCTION_STATUS[sys_para.wcLanguage][BoardInf.KineticPara.Enable]);
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);


    //6.2.定性参数-数据源
    strcpy(ConvertStr,CH_STR_INTERPRET_SOURCE[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,": ");
    if(BoardInf.InterpretPara.AbsFlag)
    {
        strcat(ConvertStr,CH_STR_ABS[SystemPrameter.SystemLanguage]);
    }
    else
    {
        strcat(ConvertStr,CH_STR_CONC[SystemPrameter.SystemLanguage]);
    }
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);

#ifdef SOFTWARE_DN
    if(BoardInf.InterpretPara.Mode==INTER_SPECIAL)
    {
        strcpy(ConvertStr,STR_INTERPRET_LIMIT_DN2[SystemPrameter.SystemLanguage]);
        strcat(CsvConvertStr,ConvertStr);

        sprintf(ConvertStr,"%1.2f",BoardInf.InterpretPara.fCoef_DN[0]);//Limit
        strcat(ConvertStr,"\n");
        strcat(CsvConvertStr,ConvertStr);

        strcpy(ConvertStr,STR_INTERPRET_POS_DN2[SystemPrameter.SystemLanguage]);
        strcat(CsvConvertStr,ConvertStr);

        sprintf(ConvertStr,"%1.2f",BoardInf.InterpretPara.fCoef_DN[1]);//Limit
        strcat(ConvertStr,"\n");
        strcat(CsvConvertStr,ConvertStr);


        strcpy(ConvertStr,STR_INTERPRET_WEAK_POS_DN2[SystemPrameter.SystemLanguage]);
        strcat(CsvConvertStr,ConvertStr);

        sprintf(ConvertStr,"%1.2f",BoardInf.InterpretPara.fCoef_DN[2]);//Limit
        strcat(ConvertStr,"\n\n");
        strcat(CsvConvertStr,ConvertStr);
    }
    else
    {
        AddInterpretAbs();
    }
#else

    AddInterpretAbs();
#endif
    //7.1.质控-打开
    strcpy(ConvertStr,CH_STR_QUALITY_TITLE[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,": ");
    if(BoardInf.QualityPara.Enable)
    {
        strcat(ConvertStr,CH_STR_OPEN[SystemPrameter.SystemLanguage]);
    }
    else
    {
        strcat(ConvertStr,CH_STR_OFF[SystemPrameter.SystemLanguage]);
    }

    //strcat(ConvertStr,FUNCTION_STATUS[SystemPrameter.SystemLanguage][board_inf.quality_para.bOpened]);
    strcat(ConvertStr,"\n");
    //7.2.质控-数据源
    strcat(ConvertStr,CH_STR_INTERPRET_SOURCE[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,": ");
    if(BoardInf.QualityPara.AbsFlag)
    {
        strcat(ConvertStr,CH_STR_ABS[SystemPrameter.SystemLanguage]);
    }
    else
    {
        strcat(ConvertStr,CH_STR_CONC[SystemPrameter.SystemLanguage]);
    }
    //strcat(ConvertStr,REFERENCE_SELECT[SystemPrameter.SystemLanguage][board_inf.quality_para.bABS]);
    strcat(ConvertStr,"\n");

    //7.3.质控-表格
    //序号
    strcat(ConvertStr,CH_STR_TABLE_RECORD_NO[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");
    //目标值
    strcat(ConvertStr,CH_QUALITY_TABLE_TARGET[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");
    //标准偏差
    strcat(ConvertStr,CH_QUALITY_TABLE_SD[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");

    //变异系数
    strcat(ConvertStr,CH_QUALITY_TABLE_CV[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");

    //上限
    strcat(ConvertStr,CH_QUALITY_TABLE_UPPER_LIMIT[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");

    //下限
    strcat(ConvertStr,CH_QUALITY_TABLE_LOWER_LIMIT[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);

    for (i = 0; i < QC_MAX; i++)
    {
        //if(BoardInf.QualityPara.dTarget[BoardInf.QualityPara.AbsFlag][i] < 0) //目标值<0，表示结束
        if(BoardInf.QualityPara.dTarget[BoardInf.QualityPara.AbsFlag][i] <= 0) //目标值<0，表示结束
        {
            break;
        }
        sprintf(ConvertStr,"%d",i + 1); //序号
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);
        sprintf(ConvertStr,"%1.3f",BoardInf.QualityPara.dTarget[BoardInf.QualityPara.AbsFlag][i]); //目标值
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);
        sprintf(ConvertStr,"%1.3f",BoardInf.QualityPara.dSD[BoardInf.QualityPara.AbsFlag][i]);    //标准偏差
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);
        sprintf(ConvertStr,"%1.3f",BoardInf.QualityPara.dCV[BoardInf.QualityPara.AbsFlag][i]);     //变异系数
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);
        sprintf(ConvertStr,"%1.3f",BoardInf.QualityPara.dUpperLimit[BoardInf.QualityPara.AbsFlag][i]); //上限
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);
        sprintf(ConvertStr,"%1.3f",BoardInf.QualityPara.dLowerLimit[BoardInf.QualityPara.AbsFlag][i]); //下限
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);
        strcat(CsvConvertStr,"\n");
    }

    //8.1.布局
    strcat(CsvConvertStr,"\n");

    //标题-布局
    strcpy(ConvertStr,CH_STR_LAYOUT[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,"\n");

    //序号：1-12
    strcat(ConvertStr,", ");
    strcat(CsvConvertStr,ConvertStr);
    for(i = 0; i < 12; i++)
    {
        sprintf(ConvertStr,"%d",i + 1); //序号
        if(i < 11)
        {
            strcat(ConvertStr,", ");
        }
        else
        {
            strcat(ConvertStr,"  \n");
        }
        strcat(CsvConvertStr,ConvertStr);
    }


    for(j = 0; j < 8; j++)
    {
        for(i = 0; i < 13; i++)
        {
            if(i == 0)
            {
                sprintf(ConvertStr,"%c",'A' + j);
                strcat(ConvertStr,", ");
                strcat(CsvConvertStr,ConvertStr);
                continue;
            }
            strcat(CsvConvertStr,WELLS_TYPE_STR[BoardInf.Layout.WellType[j*12+i-1]]);
						#ifdef SOFTWARE_DN
						if( (BoardInf.Layout.WellType[j*12+i-1]==WELLS_TYPE_SD)||(BoardInf.Layout.WellType[j*12+i-1]==WELLS_TYPE_QC) )
            {
                sprintf(ConvertStr,"%d",BoardInf.Layout.Num[j*12+i-1]+1);
                strcat(CsvConvertStr,ConvertStr);
            }
						else if(BoardInf.Layout.WellType[j*12+i-1]==WELLS_TYPE_UD)
            {
                sprintf(ConvertStr,"%3d",BoardInf.Layout.Num[j*12+i-1]);
                strcat(CsvConvertStr,ConvertStr);
            }
						#else
						if( (BoardInf.Layout.WellType[j*12+i-1]==WELLS_TYPE_SD)||(BoardInf.Layout.WellType[j*12+i-1]==WELLS_TYPE_QC) )
            {
                sprintf(ConvertStr,"%d",BoardInf.Layout.Num[j*12+i-1]+1);
                strcat(CsvConvertStr,ConvertStr);
            }
						#endif
            
            strcat(CsvConvertStr,", ");

            if(i >= 12)
            {
                strcat(CsvConvertStr,"\n");
            }
        }
    }
    strcat(CsvConvertStr,"\n");
}

//导出原始数据
void SetRawDataContent(void)
{
    unsigned char i,j,k;
    unsigned char max_cyc;

// if(NormalAnalysis.wcMode == ANALYSIS_MODE_RAWDATA && BoardInf.bHasData)
    {
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            strcat(CsvConvertStr,"Absorbance data:\n");
        }
        else
        {
            strcat(CsvConvertStr,"Dados de Absorbancia:\n");
        }
        //滤光片
        if(NormalAnalysis.FilterCurrent == 0)
        {
            strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER1[SystemPrameter.SystemLanguage]);
            strcat(ConvertStr,":");
            if(BoardInf.Filter1Locate>=0)
            {
                sprintf(StrTemp,"%d",FilterLun.Filter[BoardInf.Filter1Locate]);
                strcat(ConvertStr,StrTemp);
                strcat(ConvertStr,"nm");
            }

        }
        else if(NormalAnalysis.FilterCurrent == 1)
        {
            //strTemp += (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
            strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER2[SystemPrameter.SystemLanguage]);
            strcat(ConvertStr,":");
            if(BoardInf.Filter2Locate>=0)
            {
                sprintf(StrTemp,"%d",FilterLun.Filter[BoardInf.Filter2Locate]);
                strcat(ConvertStr,StrTemp);
                strcat(ConvertStr,"nm");
            }

        }
        else
        {
            strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER12[SystemPrameter.SystemLanguage]);
            strcat(ConvertStr,":");
            if(BoardInf.KineticPara.PreProcess>=0)
            {
                strcat(ConvertStr,PRE_CALCULATE_STR[BoardInf.KineticPara.PreProcess]);
            }
            //strTemp += (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
        }
        strcat(ConvertStr,"\n");
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);



        for(i = 0; i < 12; i++)
        {
            sprintf(ConvertStr,"%d",i+1);
           //strcat(ConvertStr,StrTemp);
            if(i < 11)
            {
                strcat(ConvertStr,", ");
            }
            else
            {
                strcat(ConvertStr," \n");
            }
            strcat(CsvConvertStr,ConvertStr);
        }

        max_cyc=1;
        if(BoardInf.KineticPara.Enable)
        {
            max_cyc=BoardInf.KineticPara.kinetic_readings_practical;
        }

        for(k=0; k<max_cyc; k++)
        {
            //strcat(CsvConvertStr,"readings: ");
            strcat(CsvConvertStr,CH_KINETIC_READINGS[SystemPrameter.SystemLanguage]);
            strcat(CsvConvertStr,": ");
            sprintf(StrTemp,"%d",k+1);
            strcat(CsvConvertStr,StrTemp);
            strcat(CsvConvertStr,"\n");

            //Start
            for(j = 0; j < 8; j++)
            {
                for(i = 0; i < 13; i++)
                {
                    if(i == 0)
                    {
                        sprintf(ConvertStr,"%c",'A' + j);
                    }
                    else
                    {
                        unsigned char bHasResult = 1;
                        float fTemp;
//						signed char nCycle = 0;            //No use
                        //if(BoardInf.KineticPara.Enable)
                        //{  //No use
                        //	nCycle = BoardInf.KineticPara.kinetic_reading_current;  //kinetic_para.kinetic_readings  //No use
                        //}  //No use

                        if(NormalAnalysis.FilterCurrent < 2)
                        {
                            //   dTemp = dABS[nCycle][normal_analysis.wcFilterCurrent][j * 12 + i - 1];
                            fTemp = dABS[k][NormalAnalysis.FilterCurrent][j * 12 + i - 1];
                        }
                        else if(NormalAnalysis.bPreCalOK[k][j * 12 + i - 1])
                        {
                            fTemp = NormalAnalysis.dPreCal[k][j * 12 + i -1];
                        }
                        else
                        {
                            bHasResult = 0;
                        }

                        if(bHasResult)
                        {
                            sprintf(ConvertStr,"%1.3f",fTemp);
                        }
                        else
                        {
                            strcpy(ConvertStr,"N.A.");
                        }

                        if( (BoardInf.Layout.WellType[j * 12 + i-1]==WELLS_TYPE_EP) || (BoardInf.Layout.WellType[j * 12 + i-1]>=WELLS_TYPE_MAX) )
                        {
                            strcpy(ConvertStr,"EP");
                        }
                    }
                    if(i < 12)
                    {
                        strcat(ConvertStr,", ");
                    }
                    else
                    {
                        strcat(ConvertStr,"\n");
                    }
                    strcat(CsvConvertStr,ConvertStr);
                }
            }
        }
        strcat(CsvConvertStr,"\n");
    }//if(NormalAnalysis.wcMode == ANALYSIS_MODE_RAWDATA && BoardInf.bHasData)
}
#ifndef SOFTWARE_DN
//设置标准曲线
void SetCurveContent(void)
{
	  unsigned char i,j;
	  if( ((BoardInf.KineticPara.Enable==0)&&(BoardInf.KineticPara.Curve<=CURVE_NO))||(BoardInf.KineticPara.Enable) )
    {
        //1.标题
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            strcat(CsvConvertStr,"Curve Data: no data! \n");
        }
        else
        {
            strcat(CsvConvertStr,"Dados da curva: sem dados!\n");
        }
        return;
    }
		
    //1.
    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        strcat(CsvConvertStr,"Standard Curve\n");
    }
    else
    {
        strcat(CsvConvertStr,"Curva Padrao\n"); //  Þ¡Ú»Ë½ß(Å¨×ˆ)
    }
		
		if(BoardInf.KineticPara.Curve==CURVE_LOGISTIC)
		{
			      //函数
			      strcpy(ConvertStr,"Logistic");
            sprintf(StrTemp,": y=%1.3f+(%1.3f-%1.3f)/(1+(x/%1.3f)^%1.3f)"
                    , NormalAnalysis.LogisticAnalysis[NormalAnalysis.FilterCurrent].dCoef[3]
                    , NormalAnalysis.LogisticAnalysis[NormalAnalysis.FilterCurrent].dCoef[0]
                    , NormalAnalysis.LogisticAnalysis[NormalAnalysis.FilterCurrent].dCoef[3]
                    , NormalAnalysis.LogisticAnalysis[NormalAnalysis.FilterCurrent].dCoef[2]
                    , NormalAnalysis.LogisticAnalysis[NormalAnalysis.FilterCurrent].dCoef[1]);
            strcat(ConvertStr,StrTemp);
			      strcat(CsvConvertStr,ConvertStr);
            strcat(CsvConvertStr,"\n");
            //R2
            sprintf(ConvertStr,"R2: %1.3f",NormalAnalysis.LogisticAnalysis[NormalAnalysis.FilterCurrent].dRR);
			      strcat(CsvConvertStr,ConvertStr);
			      strcat(CsvConvertStr,"\n");	
		}
		else if(BoardInf.KineticPara.Curve==CURVE_LINEAR)
		{
			      //函数
			      strcpy(ConvertStr,"Linear");
          
            sprintf(StrTemp,": y = %1.3f * x + %1.3f"
                    , NormalAnalysis.LinearAnalysis[NormalAnalysis.FilterCurrent].dSlope
                    , NormalAnalysis.LinearAnalysis[NormalAnalysis.FilterCurrent].dIntercept);
            strcat(ConvertStr,StrTemp);
            strcat(CsvConvertStr,ConvertStr);
            strcat(CsvConvertStr,"\n");
			
            //R2
            sprintf(ConvertStr,"R2: %1.3f",NormalAnalysis.LinearAnalysis[NormalAnalysis.FilterCurrent].dRR);
			      strcat(CsvConvertStr,ConvertStr);
			      strcat(CsvConvertStr,"\n");	
           
		}
		else if(BoardInf.KineticPara.Curve==CURVE_FACTOR)
		{
			      //函数
			      strcpy(ConvertStr,"Factor");
            sprintf(StrTemp,": y = %1.3f * x"
                    , NormalAnalysis.FactorAnalysis[NormalAnalysis.FilterCurrent].dSlope);
            strcat(ConvertStr,StrTemp);
			      strcat(CsvConvertStr,ConvertStr);
            strcat(CsvConvertStr,"\n");
			
            //R2
            sprintf(ConvertStr,"R2: %1.3f",NormalAnalysis.FactorAnalysis[NormalAnalysis.FilterCurrent].dRR);
			      strcat(CsvConvertStr,ConvertStr);
			      strcat(CsvConvertStr,"\n");	
		}
		else if(BoardInf.KineticPara.Curve==CURVE_PTOP)
		{
			     strcat(CsvConvertStr,"Point to point");
			     strcat(CsvConvertStr,"\n");	
		}
		else if(BoardInf.KineticPara.Curve==CURVE_CUBIC)
		{
			    strcat(CsvConvertStr,"Cubic Spline");
			    strcat(CsvConvertStr,"\n");
#ifdef SOFTWARE_DN
					sprintf(ConvertStr,"IC50: %1.3f",NormalAnalysis.SplineAnalysis[NormalAnalysis.FilterCurrent].IC50);
					strcat(CsvConvertStr,ConvertStr);
					strcat(CsvConvertStr,"\n");	
#endif
		}
		if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
		{
			 strcat(CsvConvertStr,"NO.,ABS,Conc.\n");
		}
		else
		{
		   strcat(CsvConvertStr,"NO., ABS, Conc.\n");
		}
		
		for(i = 0; i < CALIBRATOR_CONCENTRATION_MAX; i++)
    {
        if(NormalAnalysis.nCalibratorCount[NormalAnalysis.FilterCurrent][i] > 0)
        {
					  sprintf(ConvertStr,"SD%d,",i+1);
					  strcat(CsvConvertStr,ConvertStr);
					  sprintf(ConvertStr,"%.3f,", NormalAnalysis.dCalibratorABS[NormalAnalysis.FilterCurrent][i]);
					  strcat(CsvConvertStr,ConvertStr);
					  sprintf(ConvertStr,"%.3f,", BoardInf.dConcentration[i]);
					  strcat(CsvConvertStr,ConvertStr);
					  strcat(CsvConvertStr,"\n");	
				}
		}
}
#endif


//设置定量参数
void SetQualityContent(void)
{
    unsigned char i,j;
    //1.标题
    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        strcat(CsvConvertStr,"Result data(Concentration)\n");
    }
    else
    {
        strcat(CsvConvertStr,"Dados do resultado (concentracao)\n"); //  ½á¹ûÊý¾Ý(Å¨¶È)
    }
    //2.滤光片
    if(NormalAnalysis.FilterCurrent == 0)
    {
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER1[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.Filter1Locate>=0)
        {
            sprintf(StrTemp,"%d",FilterLun.Filter[BoardInf.Filter1Locate]);
            strcat(ConvertStr," ");
            strcat(ConvertStr,StrTemp);
            strcat(ConvertStr,"nm");
        }
        //strTemp += (CString(_T("Filter 1: ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
    }
    else if(NormalAnalysis.FilterCurrent == 1)
    {
        //strTemp += (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER2[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.Filter2Locate>=0)
        {
            sprintf(StrTemp,"%d",FilterLun.Filter[BoardInf.Filter2Locate]);
            strcat(ConvertStr," ");
            strcat(ConvertStr,StrTemp);
            strcat(ConvertStr,"nm");
        }

    }
    else
    {
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER12[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.KineticPara.PreProcess>=0)
        {
            strcat(ConvertStr,PRE_CALCULATE_STR[BoardInf.KineticPara.PreProcess]);
        }
        //strTemp += (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
    }
    strcat(ConvertStr,"\n");
    strcat(ConvertStr,", ");
    strcat(CsvConvertStr,ConvertStr);

    //3.定量分析表
    strcpy(ConvertStr,"");
    for(i = 0; i < 12; i++)
    {
        sprintf(StrTemp,"%d",i+1);
        strcat(ConvertStr,StrTemp);
        if(i < 11)
        {
            strcat(ConvertStr,",");
        }
        else
        {
            strcat(ConvertStr,"\n");
        }
    }
    strcat(CsvConvertStr,ConvertStr);


    for(j = 0; j < 8; j++)
    {
        for(i = 0; i < 13; i++)
        {
            if(i == 0)
            {
                sprintf(ConvertStr,"%c",'A' + j);
                strcat(ConvertStr,", ");
                strcat(CsvConvertStr,ConvertStr);
                continue;
            }
            //  bool bHasResult = true;

            if(NormalAnalysis.dConcentration[NormalAnalysis.FilterCurrent][j * 12 + i - 1] < 0.0f)
            {
                //bHasResult = 0;
                strcpy(ConvertStr,"N.A.");
            }
						
						
            else
            {
                sprintf(ConvertStr,"%1.3f",NormalAnalysis.dConcentration[NormalAnalysis.FilterCurrent][j * 12 + i - 1] );
            }

            if( (BoardInf.Layout.WellType[j * 12 + i-1]==WELLS_TYPE_EP) || (BoardInf.Layout.WellType[j * 12 + i-1]>=WELLS_TYPE_MAX) )
            {
                strcpy(ConvertStr,"EP");
            }
            if(i < 12)
            {
                strcat(ConvertStr,", ");
            }
            else
            {
                strcat(ConvertStr,"\n");
            }
            strcat(CsvConvertStr,ConvertStr);
        }
    }
    strcat(CsvConvertStr,"\n");
}



#ifdef SOFTWARE_DN
void SetUDContent(void)
{
    unsigned short i;
    strcpy(ConvertStr,"");
    for(i=UD_MIN; i<=UD_MAX; i++)
    {
        if(NormalAnalysis.dUD_Conc[NormalAnalysis.FilterCurrent][i] > 0.0f) //有浓度数据
        {
            //3.UD定量分析表
            // strcpy(ConvertStr,"N.A.");
            //}
            // else
            // {
            strcpy(ConvertStr,"UD");
            sprintf(StrTemp,"%03d",i);
            strcat(ConvertStr,StrTemp);
            strcat(ConvertStr,": ");
            sprintf(StrTemp,"%.3f",NormalAnalysis.dUD_Conc[NormalAnalysis.FilterCurrent][i]);
            strcat(ConvertStr,StrTemp);
            strcat(ConvertStr,"\n");
            strcat(CsvConvertStr,ConvertStr);
        }

    }
    strcat(CsvConvertStr,"\n");
}
#endif

//设置定性参数
void SetInterContent(void)
{
    float dTemp;
    unsigned char i,j,bHasResult = 1;

    if(BoardInf.InterpretPara.Enable==0)
    {
        //1.标题
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            strcat(CsvConvertStr,"Interpret result: no data! \n");
        }
        else
        {
            strcat(CsvConvertStr,"Interpretar resultado: sem dados!\n");
        }
        return;
    }

    if(BoardInf.InterpretPara.AbsFlag)
    {
        //1.标题
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            strcat(CsvConvertStr,"Absorbance Interpret result\n");
        }
        else
        {
            strcat(CsvConvertStr,"Resultado da interpretacao de absorbancia\n");
        }
    }
    else
    {
        //1.标题
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            strcat(CsvConvertStr,"Concentration Interpret result\n");
        }
        else
        {
            strcat(CsvConvertStr,"Concentracao Interpretar resultado\n");
        }
    }
    //2.滤光片
    if(NormalAnalysis.FilterCurrent == 0)
    {
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER1[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.Filter1Locate>=0)
        {
            sprintf(StrTemp,"%d",FilterLun.Filter[BoardInf.Filter1Locate]);
            strcat(ConvertStr," ");
            strcat(ConvertStr,StrTemp);
            strcat(ConvertStr,"nm");
        }
        //strTemp += (CString(_T("Filter 1: ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
    }
    else if(NormalAnalysis.FilterCurrent == 1)
    {
        //strTemp += (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER2[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.Filter2Locate>=0)
        {
            sprintf(StrTemp,"%d",FilterLun.Filter[BoardInf.Filter2Locate]);
            strcat(ConvertStr," ");
            strcat(ConvertStr,StrTemp);
            strcat(ConvertStr,"nm");
        }

    }
    else
    {
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER12[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.KineticPara.PreProcess>=0)
        {
            strcat(ConvertStr,PRE_CALCULATE_STR[BoardInf.KineticPara.PreProcess]);
        }
        //strTemp += (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
    }
    strcat(ConvertStr,"\n");
    strcat(ConvertStr,", ");
    strcat(CsvConvertStr,ConvertStr);
		
		
    if(BoardInf.InterpretPara.nAnalysisResult[NormalAnalysis.FilterCurrent]!=ANALYSIS_SUCCESS)
		{
			      strcat(CsvConvertStr,"\n");
					  return;
		}
				
				
				
    //3.定性分析表
    strcpy(ConvertStr,"");
    for(i = 0; i < 12; i++)
    {
        sprintf(StrTemp,"%d",i+1);
        strcat(ConvertStr,StrTemp);
        if(i < 11)
        {
            strcat(ConvertStr,",");
        }
        else
        {
            strcat(ConvertStr,"\n");
        }
    }
    strcat(CsvConvertStr,ConvertStr);


    for(j = 0; j < 8; j++)
    {
        for(i = 0; i < 13; i++)
        {
            if(i == 0)
            {
                sprintf(ConvertStr,"%c",'A' + j);
                strcat(ConvertStr,", ");
                strcat(CsvConvertStr,ConvertStr);
                continue;
            }
            if(NormalAnalysis.FilterCurrent < 2)
            {
                dTemp = dABS[0][NormalAnalysis.FilterCurrent][j * 12 + i - 1];
            }
            else if(NormalAnalysis.bPreCalOK[0][j * 12 + i - 1])
            {
                dTemp = NormalAnalysis.dPreCal[0][j * 12 + i - 1];
            }
            else
            {
                bHasResult = 0;
            }
            if((BoardInf.InterpretPara.AbsFlag==0) && bHasResult)
            {
                dTemp = NormalAnalysis.dConcentration[NormalAnalysis.FilterCurrent][j * 12 + i - 1];
                if(dTemp < 0.0f)
                {
                    bHasResult = 0;
                }
            }

            if(bHasResult==0)
            {
                //bHasResult = 0;
                strcpy(ConvertStr,"N.A.");
            }
            else
            {
#ifdef SOFTWARE_DN
                if( (BoardInf.InterpretPara.AbsFlag==0)&&(dTemp>BoardInf.InterpretPara.fCoef_DN[0]) )//Limit
                {
                    strcpy(ConvertStr,">");

                    sprintf(StrTemp,"%.3f",BoardInf.InterpretPara.fCoef_DN[0]);
                    strcat(ConvertStr,StrTemp);
                }
                else
                {
                    sprintf(ConvertStr,"%1.3f",dTemp);
                }
#else
                sprintf(ConvertStr,"%1.3f",dTemp);
#endif

            }

            if( (BoardInf.Layout.WellType[j * 12 + i-1]==WELLS_TYPE_EP) || (BoardInf.Layout.WellType[j * 12 + i-1]>=WELLS_TYPE_MAX) )
            {
                strcpy(ConvertStr,"EP");
                bHasResult=0;
            }

            if(bHasResult)
            {
                if(BoardInf.InterpretPara.bPos[NormalAnalysis.FilterCurrent][j * 12 + i - 1])
                {
                    strcat(ConvertStr,"P");//"++"
                }
                else if(BoardInf.InterpretPara.bWeakPos[NormalAnalysis.FilterCurrent][j * 12 + i - 1])
                {
                    strcat(ConvertStr,"+");//"++"
                }
            }
            //strTemp += strTemp1 + _T(" ") + strPos;
            if(i < 12)
            {
                strcat(ConvertStr,", ");
            }
            else
            {
                strcat(ConvertStr,"\n");
            }
            strcat(CsvConvertStr,ConvertStr);
        }
    }
    strcat(CsvConvertStr,"\n");
}


//设置质控参数
void SetQCContent(void)
{
    unsigned char i;
    float fTemp;

    if(BoardInf.QualityPara.Enable==0)
    {
        //1.标题
        if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
        {
            strcat(CsvConvertStr,"QC result: no data! \n");
        }
        else
        {
            strcat(CsvConvertStr,"Resultado do CQ: sem dados!\n");
        }
        return;
    }

    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        strcat(CsvConvertStr,"QC result:\n");
    }
    else
    {
        strcat(CsvConvertStr,"Resultado CQ:\n");
    }

    //2.滤光片
    if(NormalAnalysis.FilterCurrent == 0)
    {
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER1[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.Filter1Locate>=0)
        {
            sprintf(StrTemp,"%d",FilterLun.Filter[BoardInf.Filter1Locate]);
            strcat(ConvertStr," ");
            strcat(ConvertStr,StrTemp);
            strcat(ConvertStr,"nm");
        }
        //strTemp += (CString(_T("Filter 1: ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
    }
    else if(NormalAnalysis.FilterCurrent == 1)
    {
        //strTemp += (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER2[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.Filter2Locate>=0)
        {
            sprintf(StrTemp,"%d",FilterLun.Filter[BoardInf.Filter2Locate]);
            strcat(ConvertStr," ");
            strcat(ConvertStr,StrTemp);
            strcat(ConvertStr,"nm");
        }

    }
    else
    {
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER12[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.KineticPara.PreProcess>=0)
        {
            strcat(ConvertStr,PRE_CALCULATE_STR[BoardInf.KineticPara.PreProcess]);
        }
        //strTemp += (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
    }
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);



    //7.3.质控-表格
    //序号
    strcpy(ConvertStr,CH_STR_TABLE_RECORD_NO[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");
    //目标值-浓度/吸光度
    strcat(ConvertStr,CH_REFERENCE_SELECT[SystemPrameter.SystemLanguage][BoardInf.QualityPara.AbsFlag]);
    strcat(ConvertStr,", ");
    //标准偏差
    strcat(ConvertStr,CH_QUALITY_TABLE_SD[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");

    //变异系数
    strcat(ConvertStr,CH_QUALITY_TABLE_CV[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");

    //上限
    strcat(ConvertStr,CH_QUALITY_TABLE_UPPER_LIMIT[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");

    //下限
    strcat(ConvertStr,CH_QUALITY_TABLE_LOWER_LIMIT[SystemPrameter.SystemLanguage]);
    strcat(ConvertStr,", ");

    //结论
    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        strcat(ConvertStr,"Result\n");
    }
    else
    {
        strcat(ConvertStr,"Resultado\n");
    }
    strcat(CsvConvertStr,ConvertStr);



    for (i = 0; i < QC_MAX; i++)
    {
        if(BoardInf.QualityResult.nTotal[NormalAnalysis.FilterCurrent]<1) //只有九个质控品
        {
            break;
        }
        if(BoardInf.QualityResult.nTotalQC[NormalAnalysis.FilterCurrent][i]==0)
        {
            continue;
        }
        
				if(BoardInf.QualityResult.nAnalysisResult[NormalAnalysis.FilterCurrent]!=ANALYSIS_SUCCESS)
				{
					  break;
				}

        sprintf(ConvertStr,"%d",i + 1); //序号
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);


        //float dTemp1=BoardInf.QualityPara.dReferenceQC[normal_analysis.wcFilterCurrent][i];
        //sprintf(ConvertStr,"%1.3f",);
        fTemp=BoardInf.QualityResult.dReferenceQC[NormalAnalysis.FilterCurrent][i];//浓度/吸光度
        if(fTemp > 1000.0f || fTemp < -1000.0f)
        {
            sprintf(ConvertStr,"%.3e",fTemp);
            EConvert(ConvertStr);
        }
        else
        {
            sprintf(ConvertStr,"%1.3f",fTemp);
        }
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);

        //	dTemp =BoardInf.QualityPara.dSD[normal_analysis.wcFilterCurrent][i] ;
        //sprintf(ConvertStr,"%1.3f",BoardInf.QualityPara.dSD[normal_analysis.wcFilterCurrent][i]); //标准偏差
        fTemp=BoardInf.QualityResult.dSD[NormalAnalysis.FilterCurrent][i ];
        if(fTemp > 1000.0f || fTemp < -1000.0f)
        {
            sprintf(ConvertStr,"%.3e",fTemp);
            EConvert(ConvertStr);
        }
        else
        {
            sprintf(ConvertStr,"%1.3f",fTemp);
        }
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);


        if(BoardInf.QualityResult.dReferenceQC[NormalAnalysis.FilterCurrent][i] < CONCENTRATION_VALUE_MIN && BoardInf.QualityResult.dReferenceQC[NormalAnalysis.FilterCurrent][i] > -CONCENTRATION_VALUE_MIN)
        {
            strcpy(ConvertStr,"N.A.");
        }
        else
        {
            fTemp=BoardInf.QualityResult.dSD[NormalAnalysis.FilterCurrent][i ] /BoardInf.QualityResult.dReferenceQC[NormalAnalysis.FilterCurrent][i];
            if(fTemp > 1000.0f || fTemp < -1000.0f)
            {
                sprintf(ConvertStr,"%.3e",fTemp);
                EConvert(ConvertStr);
            }
            else
            {
                sprintf(ConvertStr,"%1.3f",fTemp);
            }
        }
        //sprintf(ConvertStr,"%1.3f",BoardInf.QualityPara.dCV[BoardInf.QualityPara.AbsFlag][i]); //变异系数
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);


        //sprintf(ConvertStr,"%1.3f",BoardInf.QualityPara.dUpperLimit[BoardInf.QualityPara.AbsFlag][i]); //上限
        fTemp=BoardInf.QualityPara.dUpperLimit[BoardInf.QualityPara.AbsFlag][i];
        if(fTemp > 1000.0f || fTemp < -1000.0f)
        {
            sprintf(ConvertStr,"%.3e",fTemp);
            EConvert(ConvertStr);
        }
        else
        {
            sprintf(ConvertStr,"%1.3f",fTemp);
        }
        strcat(ConvertStr,", ");
        strcat(CsvConvertStr,ConvertStr);

        // sprintf(ConvertStr,"%1.3f",BoardInf.QualityPara.dLowerLimit[BoardInf.QualityPara.AbsFlag][i]); //下限
        fTemp=BoardInf.QualityPara.dLowerLimit[BoardInf.QualityPara.AbsFlag][i ];
        if(fTemp > 1000.0f || fTemp < -1000.0f)
        {
            sprintf(ConvertStr,"%.3e",fTemp);
            EConvert(ConvertStr);
        }
        else
        {
            sprintf(ConvertStr,"%1.3f",fTemp);
        }
        strcat(ConvertStr,", ");

        strcat(CsvConvertStr,ConvertStr);

        strcat(CsvConvertStr,CH_STR_QUALITY_RESULT[SystemPrameter.SystemLanguage][BoardInf.QualityResult.bFailed[NormalAnalysis.FilterCurrent][i]]);
        strcat(CsvConvertStr,"\n");
    }
    strcat(CsvConvertStr,"\n");
}




void SetResultContent(void)
{
    unsigned char i,j;
    //标题,平均速率
    if(SystemPrameter.SystemLanguage==LANGUAGE_EN)
    {
        strcpy(ConvertStr,CH_KINETIC_ANALYSIS_SELECTION[0][SystemPrameter.SystemLanguage][BoardInf.KineticPara.kinetic_analysis_mode]);
        strcat(ConvertStr," ");
        strcat(ConvertStr,CH_KINETIC_ANALYSIS_SELECTION[1][SystemPrameter.SystemLanguage][BoardInf.KineticPara.kinetic_analysis_mode]);
        strcat(ConvertStr,":");
    }
    else
    {
        strcpy(ConvertStr,CH_KINETIC_ANALYSIS_SELECTION[0][SystemPrameter.SystemLanguage][BoardInf.KineticPara.kinetic_analysis_mode]);
        strcat(ConvertStr,CH_KINETIC_ANALYSIS_SELECTION[1][SystemPrameter.SystemLanguage][BoardInf.KineticPara.kinetic_analysis_mode]);
        strcat(ConvertStr,":");
    }
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);
    //2.滤光片
    if(NormalAnalysis.FilterCurrent == 0)
    {
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER1[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.Filter1Locate>=0)
        {
            sprintf(StrTemp,"%d",FilterLun.Filter[BoardInf.Filter1Locate]);
            strcat(ConvertStr," ");
            strcat(ConvertStr,StrTemp);
            strcat(ConvertStr,"nm");
        }
        //strTemp += (CString(_T("Filter 1: ")) + CString(filterLun.filter[board_inf.Filter1_locate]));
    }
    else if(NormalAnalysis.FilterCurrent == 1)
    {
        //strTemp += (CString(_T("Filter 2: ")) + CString(filterLun.filter[board_inf.Filter2_locate]));
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER2[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.Filter2Locate>=0)
        {
            sprintf(StrTemp,"%d",FilterLun.Filter[BoardInf.Filter2Locate]);
            strcat(ConvertStr," ");
            strcat(ConvertStr,StrTemp);
            strcat(ConvertStr,"nm");
        }

    }
    else
    {
        strcpy(ConvertStr,CH_SELECT_CONTROL_REPORT_FILTER12[SystemPrameter.SystemLanguage]);
        strcat(ConvertStr,":");
        if(BoardInf.KineticPara.PreProcess>=0)
        {
            strcat(ConvertStr,PRE_CALCULATE_STR[BoardInf.KineticPara.PreProcess]);
        }
        //strTemp += (CString(_T("Filter 1&2: ")) + CString(board_inf.preCalculate));
    }
    strcat(ConvertStr,"\n");
    strcat(CsvConvertStr,ConvertStr);


    //3.动力学分析结果表
    strcpy(ConvertStr,"\n");
    strcat(ConvertStr,",");
    for(i = 0; i < 12; i++)
    {
        sprintf(StrTemp,"%d",i+1);
        strcat(ConvertStr,StrTemp);
        if(i < 11)
        {
            strcat(ConvertStr,",");
        }
        else
        {
            strcat(ConvertStr,"\n");
        }
    }
    strcat(CsvConvertStr,ConvertStr);


    for(j = 0; j < 8; j++)
    {
        for(i = 0; i < 13; i++) //2014-8-20项
        {
            float dTemp;
            unsigned char bHasResult = 1;

            if(i == 0)
            {
                sprintf(ConvertStr,"%c",'A' + j);
                strcat(ConvertStr,", ");
                strcat(CsvConvertStr,ConvertStr);
                continue;
            }
            if(BoardInf.KineticPara.kinetic_analysis_mode == KINETIC_ANALYSIS_AVERAGE_RATE)
            {
                if(NormalAnalysis.FilterCurrent < 2)
                {
                    dTemp = BoardInf.KineticPara.KineticAverageRate[NormalAnalysis.FilterCurrent].dAverageRate[j * 12 + i - 1];
                }
                else if(BoardInf.KineticPara.bPreCalOK[j * 12 + i - 1])
                {
                    dTemp = BoardInf.KineticPara.KineticAverageRate[NormalAnalysis.FilterCurrent].dAverageRate[j * 12 + i - 1];
                }
                else
                {
                    bHasResult = 0;
                }

            }
            else if(BoardInf.KineticPara.kinetic_analysis_mode == KINETIC_ANALYSIS_MAX_RATE)
            {
                if(NormalAnalysis.FilterCurrent < 2)
                {
                    dTemp = BoardInf.KineticPara.KineticMaxRate[NormalAnalysis.FilterCurrent].dMaxRate[j * 12 + i - 1];
                }
                else if(BoardInf.KineticPara.bPreCalOK[j * 12 + i - 1])
                {
                    dTemp = BoardInf.KineticPara.KineticMaxRate[NormalAnalysis.FilterCurrent].dMaxRate[j * 12 + i - 1];
                }
                else
                {
                    bHasResult = 0;
                }

            }
            else if(BoardInf.KineticPara.kinetic_analysis_mode== KINETIC_ANALYSIS_MAX_WELL)
            {
                if(NormalAnalysis.FilterCurrent < 2)
                {
                    dTemp = BoardInf.KineticPara.KineticMaxWell[NormalAnalysis.FilterCurrent].dMaxWell[j * 12 + i - 1];
                }
                else if(BoardInf.KineticPara.bPreCalOK[j * 12 + i - 1])
                {
                    dTemp = BoardInf.KineticPara.KineticMaxWell[NormalAnalysis.FilterCurrent].dMaxWell[j * 12 + i - 1];
                }
                else
                {
                    bHasResult = 0;
                }

            }
            else if(BoardInf.KineticPara.kinetic_analysis_mode == KINETIC_ANALYSIS_TIME_MAX_RATE)
            {
                if(NormalAnalysis.FilterCurrent < 2)
                {
                    dTemp = BoardInf.KineticPara.KineticTimeMaxRate[NormalAnalysis.FilterCurrent].nTime[j * 12 + i - 1];
                }
                else if(BoardInf.KineticPara.bPreCalOK[j * 12 + i - 1])
                {
                    dTemp = BoardInf.KineticPara.KineticTimeMaxRate[NormalAnalysis.FilterCurrent].nTime[j * 12 + i - 1];
                }
                else
                {
                    bHasResult = 0;
                }

            }
            if(BoardInf.KineticPara.kinetic_analysis_mode == KINETIC_ANALYSIS_TIME_MAX)
            {
                if(NormalAnalysis.FilterCurrent < 2)
                {
                    dTemp = BoardInf.KineticPara.KineticTimeMax[NormalAnalysis.FilterCurrent].nTime[j * 12 + i - 1];
                }
                else if(BoardInf.KineticPara.bPreCalOK[j * 12 + i - 1])
                {
                    dTemp = BoardInf.KineticPara.KineticTimeMax[NormalAnalysis.FilterCurrent].nTime[j * 12 + i - 1];
                }
                else
                {
                    bHasResult = 0;
                }
            }

            else if(BoardInf.KineticPara.kinetic_analysis_mode == KINETIC_ANALYSIS_TIME_CHANGE)
            {
                if(NormalAnalysis.FilterCurrent < 2)
                {
                    dTemp = BoardInf.KineticPara.KineticTimeChange[NormalAnalysis.FilterCurrent].nTime[j * 12 + i - 1];
                    bHasResult = BoardInf.KineticPara.KineticTimeChange[NormalAnalysis.FilterCurrent].bOK[j * 12 + i - 1];
                }
                else if(BoardInf.KineticPara.bPreCalOK[j * 12 + i - 1])
                {
                    dTemp = BoardInf.KineticPara.KineticTimeChange[NormalAnalysis.FilterCurrent].nTime[j * 12 + i - 1];
                    bHasResult = BoardInf.KineticPara.KineticTimeChange[NormalAnalysis.FilterCurrent].bOK[j * 12 + i - 1];
                }
                else
                {
                    bHasResult = 0;
                }
            }

            if(bHasResult)
            {
                // strTemp1.Format(_T("%1.3f"), dTemp);
                sprintf(ConvertStr,"%1.3f",dTemp);
            }
            else
            {
                strcpy(ConvertStr,"N.A.");
                // strTemp1 = _T("N.A.");
            }
            if( (BoardInf.Layout.WellType[j * 12 + i-1]==WELLS_TYPE_EP) || (BoardInf.Layout.WellType[j * 12 + i-1]>=WELLS_TYPE_MAX) )
            {
                strcpy(ConvertStr,"EP");
            }

            if(i < 12)
            {
                strcat(ConvertStr,", ");
            }
            else
            {
                strcat(ConvertStr,"\n");
            }
            strcat(CsvConvertStr,ConvertStr);
        }
    }
    strcat(ConvertStr,"\n");
}


