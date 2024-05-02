#include "importararquivos.h"
#include "dadosbrutos.h"

#define LIST_NUM 23
ImportarArquivos::ImportarArquivos(QObject *parent)
    : QObject{parent}
{

}

void ImportarArquivos::paintColorWell(){

    for(int i=0; i<NUM_POCOS; i++){
        if(L1_pocosArray[i].type=="VZ"||L1_pocosArray[i].type==""){
            L1_pocosArray[i].colorWell = "white";
        }else if(L1_pocosArray[i].type=="DC"){
            L1_pocosArray[i].colorWell = "purple";
        }else if(L1_pocosArray[i].type=="PD"){
            L1_pocosArray[i].colorWell = "yellow";
        }else if(L1_pocosArray[i].type=="PD"){
            L1_pocosArray[i].colorWell = "yellow";
        }else if(L1_pocosArray[i].type=="BC"){
            L1_pocosArray[i].colorWell = "lightgray";
        }else if(L1_pocosArray[i].type=="CP1"||L1_pocosArray[i].type=="CP2"||L1_pocosArray[i].type=="CP3"
        ||L1_pocosArray[i].type=="CP4"||L1_pocosArray[i].type=="CP5"){
            L1_pocosArray[i].colorWell = "pink";
        }else if(L1_pocosArray[i].type=="CA1"||L1_pocosArray[i].type=="CA2"||L1_pocosArray[i].type=="CA3"
        ||L1_pocosArray[i].type=="CA4"||L1_pocosArray[i].type=="CA5"){
            L1_pocosArray[i].colorWell = "lightblue";
        }else if(L1_pocosArray[i].type=="CN1"||L1_pocosArray[i].type=="CN2"||L1_pocosArray[i].type=="CN3"
        ||L1_pocosArray[i].type=="CN4"||L1_pocosArray[i].type=="CN5"){
             L1_pocosArray[i].colorWell = "blue";
        }else if(L1_pocosArray[i].type=="CQ1"||L1_pocosArray[i].type=="CQ2"||L1_pocosArray[i].type=="CQ3"
        ||L1_pocosArray[i].type=="CQ4"||L1_pocosArray[i].type=="CQ5"){
              L1_pocosArray[i].colorWell = "green";
        }

    }


}

int ImportarArquivos::importarCSVTXT(int sepCol, QString pathName){
    int error = 0;
    char c = '.';
    switch(sepCol){
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

    QFile file(pathName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        error = 1;
    QTextStream fileCSV(&file);

    QList<QStringList> importData;
    QStringList header;
    int  lineNum = 0;

    while(!fileCSV.atEnd())
    {
        QString line = fileCSV.readLine();
        QStringList rowList = line.split(c);
        qDebug() << "Row list tamanho:";
        qDebug() << rowList.size();

        if (lineNum > 0&&rowList.size()==LIST_NUM){
           importData.append(rowList);
           qDebug() << L1_pocosArray[lineNum-1].unique_id;
           if(rowList.at(1)=="VZ"){
               L1_pocosArray[lineNum-1].type = "";
           }else{
               L1_pocosArray[lineNum-1].type = rowList.at(1);
           }
           L1_pocosArray[lineNum-1].unique_id = rowList.at(2).toInt();
           L1_pocosArray[lineNum-1].sample_id = rowList.at(3);
           L1_pocosArray[lineNum-1].subject_id = rowList.at(4);
           L1_pocosArray[lineNum-1].replicate_id = rowList.at(5);
        }else if(lineNum==0){
           header = rowList;
        }else{
            error = 1;
        }
        ++lineNum;
    }
    paintColorWell();
    qDebug() << header.at(0);
    file.close();
    return error;
}
