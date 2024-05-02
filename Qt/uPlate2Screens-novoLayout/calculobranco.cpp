#include "calculobranco.h"
#include "dadosbrutos.h"

CalculoBranco::CalculoBranco(QObject *parent)
    : QObject{parent}
{

}

float blank[3] = {0};


void CalculoBranco::blankCalculus()
{
    int i = 0;
    float sum_blank[3] = {0};
    float count_blank = 0;
    for(i=0; i<NUM_POCOS; i++){
        if(L1_pocosArray[i].type == "BC"){
            sum_blank[0] = sum_blank[0] + L1_pocosArray[i].value_ABS;
            sum_blank[1] = sum_blank[1] + L2_pocosArray[i].value_ABS;
            sum_blank[2] = sum_blank[2] + L12_pocosArray[i].value_ABS;
            count_blank =  count_blank + 1;
        }
    }
    if(count_blank > 0){
        blank[0] = sum_blank[0]/count_blank;
        blank[1] = sum_blank[1]/count_blank;
        blank[2] = sum_blank[2]/count_blank;
    }else{
        blank[0] = 0;
        blank[1] = 0;
        blank[2] = 0;
    }
    qDebug() << "Branco L1:" << blank[0];
    qDebug() << "Branco L2:" << blank[1];
    qDebug() << "Branco L12:" << blank[2];

    for(i=0; i<NUM_POCOS; i++){
        if(blank[0]<=L1_pocosArray[i].value_ABS){
            L1_pocosArray[i].value_afterBlank = L1_pocosArray[i].value_ABS - blank[0];
        }else{
            L1_pocosArray[i].value_afterBlank = 0;
        }
        if(blank[1]<=L2_pocosArray[i].value_ABS){
            L2_pocosArray[i].value_afterBlank = L2_pocosArray[i].value_ABS - blank[1];
        }else{
            L2_pocosArray[i].value_afterBlank = 0;
        }
        if(blank[2]<=L12_pocosArray[i].value_ABS){
            L12_pocosArray[i].value_afterBlank = L12_pocosArray[i].value_ABS - blank[2];
        }else{
            L12_pocosArray[i].value_afterBlank = 0;
        }
    }

}

QVariantList CalculoBranco::printBlankData(int numFiltro){
    QVariantList BlankList;
    int i = 0;
    if(numFiltro==0){
        for(i=0;i<NUM_POCOS;i++){
            BlankList.append(L1_pocosArray[i].value_afterBlank);
        }
    }else if(numFiltro==1){
        for(i=0;i<NUM_POCOS;i++){
            BlankList.append(L2_pocosArray[i].value_afterBlank);
        }
    }else{
        for(i=0;i<NUM_POCOS;i++){
            BlankList.append(L12_pocosArray[i].value_afterBlank);
        }

    }

    return BlankList;
}
