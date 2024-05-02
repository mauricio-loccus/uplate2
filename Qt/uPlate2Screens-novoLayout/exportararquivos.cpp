#include "exportararquivos.h"
#include "dadosbrutos.h"
#include "xlsxdocument.h"
#include "xlsxchartsheet.h"
#include "xlsxcellrange.h"
#include "xlsxchart.h"
#include "xlsxrichstring.h"
#include "xlsxworkbook.h"

using namespace QXlsx;

ExportarArquivos::ExportarArquivos(QObject *parent)
    : QObject{parent}
{

}

QString last_path_exp = "";
QString last_path_imp = "";
uint8_t fileType_exp = 0;
uint8_t fileType_imp = 0;
uint8_t sep_Decimal, sep_ColExp, sep_ColImp = 0;

/* Última localização de arquivo - Export*/

QString ExportarArquivos::lastPathExp(){
    m_lastPathExp = last_path_exp;
    return m_lastPathExp;
}

void ExportarArquivos::setlastPathExp(QString newlastPath){
    if(m_lastPathExp!=newlastPath){
        m_lastPathExp = newlastPath;
        last_path_exp = m_lastPathExp;
        emit lastPathExpChanged();
    }
}

/* Última localização de arquivo - Import*/

QString ExportarArquivos::lastPathImp(){
    m_lastPathImp = last_path_imp;
    return m_lastPathImp;
}

void ExportarArquivos::setlastPathImp(QString newlastPath){
    if(m_lastPathImp!=newlastPath){
        m_lastPathImp = newlastPath;
        last_path_imp = m_lastPathImp;
        emit lastPathImpChanged();
    }
}

/* Tipo de arquivo para exportação*/

int ExportarArquivos::fileTypeExp(){
    m_fileTypeExp = fileType_exp;
    return m_fileTypeExp;
}

void ExportarArquivos::setfileTypeExp(int newfileType){
    if(m_fileTypeExp!=newfileType){
        m_fileTypeExp = newfileType;
        fileType_exp = m_fileTypeExp;
        emit fileTypeExpChanged();
    }
}

/*Tipo de arquivo para importação*/

int ExportarArquivos::fileTypeImp(){
    m_fileTypeImp = fileType_imp;
    return m_fileTypeImp;
}

void ExportarArquivos::setfileTypeImp(int newfileType){
    if(m_fileTypeImp != newfileType){
        m_fileTypeImp = newfileType;
        fileType_imp = m_fileTypeImp;
        emit fileTypeImpChanged();
    }
}

/* Separador decimal exportação*/

int ExportarArquivos::sepDecimal(){
    m_sepDecimal = sep_Decimal;
    return m_sepDecimal;
}

void ExportarArquivos::setsepDecimal(int newsepDecimal){
    if(m_sepDecimal!=newsepDecimal){
        m_sepDecimal = newsepDecimal;
        sep_Decimal =  m_sepDecimal;
        emit sepDecimalChanged();
    }
}

/*Separador coluna exportação*/

int ExportarArquivos::sepColExp(){
    m_sepColExp = sep_ColExp;
    return m_sepColExp;
}

void ExportarArquivos::setsepColExp(int newsepCol){
    if(m_sepColExp!=newsepCol){
        m_sepColExp = newsepCol;
        sep_ColExp = m_sepColExp;
        emit sepColExpChanged();
    }
}

/*Separador coluna importação*/

int ExportarArquivos::sepColImp(){
    m_sepColImp =  sep_ColImp;
    return m_sepColImp;
}

void ExportarArquivos::setsepColImp(int newsepCol){
    if(m_sepColImp!=newsepCol){
        m_sepColImp = newsepCol;
        sep_ColImp = m_sepColImp;
        emit sepColImpChanged();
    }
}

/*Funções gerais*/

void ExportarArquivos::replicateID(){
    int count;
    for(int i=0;i<NUM_POCOS;i++){
        if(L1_pocosArray[i].sample_id != ""){
            L1_pocosArray[i].replicate_id = L1_pocosArray[i].sample_id + "_1";
            L2_pocosArray[i].replicate_id = L2_pocosArray[i].sample_id + "_1";
            L12_pocosArray[i].replicate_id = L12_pocosArray[i].sample_id + "_1";
        }
    }
    for(int i=0; i<95; i++){
        count = 1;
        for(int j=i+1; j<NUM_POCOS; j++){
            if((L1_pocosArray[i].sample_id!="")&&(L1_pocosArray[i].sample_id == L1_pocosArray[j].sample_id)){
                if(L1_pocosArray[i].replicate_id==L1_pocosArray[j].replicate_id){
                    count = count + 1;
                    L1_pocosArray[j].replicate_id = L1_pocosArray[j].sample_id + "_" + QString::number(count);
                    L2_pocosArray[j].replicate_id = L2_pocosArray[j].sample_id + "_" + QString::number(count);
                    L12_pocosArray[j].replicate_id = L12_pocosArray[j].sample_id + "_" + QString::number(count);
                 }
            }

        }
    }
}

QString ExportarArquivos::sepDecimalTroca(float num, char decimal){
    QString floatStr = QString::number(num,'f',3);
    if(decimal == ','){
        floatStr = floatStr.replace(".", ",");
    }
   return floatStr;
}


void ExportarArquivos::gerarCSVTXT(QString pathName){
    replicateID();
    char c = '.';
    char d = ',';
    switch(sep_ColExp){
    case 0 :
        c = '.';
        break;
    case 1:
        c = ',';
        break;
    case 2:
        c = ';';
        break;
    case 3:
        c = ':';
        break;
    case 4:
        c = '\t';
        break;
    }

    if((sep_Decimal==0&&sep_ColExp!=0)||sep_ColExp==1){
        d = '.';

    }else{
        d = ',';
    }

    QFile file(pathName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;
    QTextStream fileCSV(&file);
    fileCSV << "Well_ID" << c << "Type" << c << "Unique_ID" << c << "Sample_ID" << c << "Subject_ID" << c << "Replicate_ID" << c <<
               "ABS_Filtro1" << c << "Blank_Filtro1" << c << "Calc_Filtro1" << c << "Aux1_Filtro1" << c << "Aux2_Filtro1" << c <<
               "CO_Filtro1" << c << "ABS_Filtro2" << c << "Blank_Filtro2" << c << "Calc_Filtro2" << c << "Aux1_Filtro2" << c <<
               "Aux2_Filtro2" << c << "CO_Filtro2" << c << "Resultado_Filtro12" << c << "Aux1_Filtro12" << c <<
               "Aux2_Filtro12" << c << "CO_Filtro12" << c << "\n";
    for(int i=0; i<NUM_POCOS; i++){
        if(L1_pocosArray[i].type == ""){
            fileCSV<< L1_pocosArray[i].well_id << c << "VZ" << c << L1_pocosArray[i].unique_id  << c << L1_pocosArray[i].sample_id << c << L1_pocosArray[i].subject_id << c << L1_pocosArray[i].replicate_id << c <<
                      sepDecimalTroca(0,d) << c << sepDecimalTroca(0,d) << c << sepDecimalTroca(0,d) << c << sepDecimalTroca(0,d) << c << sepDecimalTroca(0,d) << c << "" << c <<
                      sepDecimalTroca(0,d) << c << sepDecimalTroca(0,d) << c << sepDecimalTroca(0,d) << c << sepDecimalTroca(0,d) << c << sepDecimalTroca(0,d) << c << "" << c <<
                      sepDecimalTroca(0,d) << c << sepDecimalTroca(0,d) << c << sepDecimalTroca(0,d) << c << "" << c << "\n";
        }else{
            fileCSV<< L1_pocosArray[i].well_id << c << L1_pocosArray[i].type << c << L1_pocosArray[i].unique_id  << c << L1_pocosArray[i].sample_id << c << L1_pocosArray[i].subject_id << c << L1_pocosArray[i].replicate_id << c <<
                      sepDecimalTroca(L1_pocosArray[i].value_ABS,d) << c << sepDecimalTroca(blank[0],d) << c << sepDecimalTroca(L1_pocosArray[i].value_afterBlank,d) << c <<  sepDecimalTroca(L1_pocosArray[i].value_AUX1,d) << c <<
                      sepDecimalTroca(L1_pocosArray[i].value_AUX2,d) << c << L1_pocosArray[i].string_CO << c << sepDecimalTroca(L2_pocosArray[i].value_ABS,d) << c << sepDecimalTroca(blank[1],d) << c <<
                      sepDecimalTroca(L2_pocosArray[i].value_afterBlank,d) << c << sepDecimalTroca(L2_pocosArray[i].value_AUX1,d) << c << sepDecimalTroca(L2_pocosArray[i].value_AUX2,d) << c <<  L2_pocosArray[i].string_CO << c <<
                      sepDecimalTroca(L12_pocosArray[i].value_ABS,d) << c << sepDecimalTroca(L12_pocosArray[i].value_AUX1,d) << c << sepDecimalTroca(L12_pocosArray[i].value_AUX2,d) << c  << L12_pocosArray[i].string_CO << c << "\n";
        }
    }


}

void ExportarArquivos::gerarXLS(QString pathName){
    replicateID();
    char d;

    if(sep_Decimal==0){
        d = '.';

    }else{
        d = ',';
    }


    QFile file(pathName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QXlsx::Document xlsx;



    xlsx.write(1, 1, "Well_ID");
    xlsx.write(1, 2, "Type");
    xlsx.write(1, 3, "Unique_ID");
    xlsx.write(1, 4, "Sample_ID");
    xlsx.write(1, 5, "Subject_ID");
    xlsx.write(1, 6, "Replicate_ID");

    xlsx.write(1, 7, "ABS_Filtro1");
    xlsx.write(1, 8, "Blank_Filtro1");
    xlsx.write(1, 9, "Calc_Filtro1");
    xlsx.write(1,10, "Aux1_Filtro1");
    xlsx.write(1,11, "Aux2_Filtro1");
    xlsx.write(1,12, "CO_Filtro1");

    xlsx.write(1, 13, "ABS_Filtro2");
    xlsx.write(1, 14, "Blank_Filtro2");
    xlsx.write(1, 15, "Calc_Filtro2");
    xlsx.write(1,16, "Aux1_Filtro2");
    xlsx.write(1,17, "Aux2_Filtro2");
    xlsx.write(1,18, "CO_Filtro2");

    xlsx.write(1, 19, "Resultado_Filtro12");
    xlsx.write(1,20, "Aux1_Filtro12");
    xlsx.write(1,21, "Aux2_Filtro12");
    xlsx.write(1,22, "CO_Filtro12");

    int j = 2;

    for (int i=0;i< NUM_POCOS;i++) {

        xlsx.write(j, 1, L1_pocosArray[i].well_id);

        if(L1_pocosArray[i].type==""){
            xlsx.write(j, 2, "VZ");
        }else{
            xlsx.write(j, 2, L1_pocosArray[i].type);
        }

         xlsx.write(j, 3, L1_pocosArray[i].unique_id);
         xlsx.write(j, 4, L1_pocosArray[i].sample_id);
         xlsx.write(j, 5, L1_pocosArray[i].subject_id);
         xlsx.write(j, 6, L1_pocosArray[i].replicate_id);

         xlsx.write(j, 7, sepDecimalTroca(L1_pocosArray[i].value_ABS,d));
         xlsx.write(j, 8, sepDecimalTroca(blank[0],d));
         xlsx.write(j, 9, sepDecimalTroca(L1_pocosArray[i].value_afterBlank,d));
         xlsx.write(j, 10, sepDecimalTroca(L1_pocosArray[i].value_AUX1,d));
         xlsx.write(j, 11, sepDecimalTroca(L1_pocosArray[i].value_AUX2,d));
         xlsx.write(j, 12, L1_pocosArray[i].string_CO);


         xlsx.write(j, 13, sepDecimalTroca(L2_pocosArray[i].value_ABS,d));
         xlsx.write(j, 14, sepDecimalTroca(blank[1],d));
         xlsx.write(j, 15, sepDecimalTroca(L2_pocosArray[i].value_afterBlank,d));
         xlsx.write(j, 16, sepDecimalTroca(L2_pocosArray[i].value_AUX1,d));
         xlsx.write(j, 17, sepDecimalTroca(L2_pocosArray[i].value_AUX2,d));
         xlsx.write(j, 18, L2_pocosArray[i].string_CO);

         xlsx.write(j, 19, sepDecimalTroca(L12_pocosArray[i].value_ABS,d));
         xlsx.write(j, 20, sepDecimalTroca(L12_pocosArray[i].value_AUX1,d));
         xlsx.write(j, 21, sepDecimalTroca(L12_pocosArray[i].value_AUX2,d));
         xlsx.write(j, 22, L12_pocosArray[i].string_CO);

         j++;
    }


    xlsx.saveAs(pathName);
}
