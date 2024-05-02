#include "calculocq.h"
#include "dadosbrutos.h"

CalculoCQ::CalculoCQ(QObject *parent)
    : QObject{parent}
{

}

QString cq_interp1[2], cq_interp2[2], cq_interp3[2];
QString cq_result;
float CQ[15] = {0};

/*Cálculo CQ*/


void CalculoCQ::cqCalculus(){
    float sum_cq[15] = {0};
    float count_cq[5] = {0};
    for(int i = 0; i<NUM_POCOS; i++){
        if(L1_pocosArray[i].type == "CQ1"){
            sum_cq[0] = sum_cq[0] + L1_pocosArray[i].value_ABS;
            sum_cq[5] = sum_cq[5] + L2_pocosArray[i].value_ABS;
            sum_cq[10] = sum_cq[10] + L12_pocosArray[i].value_ABS;
            count_cq[0] = count_cq[0] + 1;
        }else if(L1_pocosArray[i].type == "CQ2"){
            sum_cq[1] = sum_cq[1] + L1_pocosArray[i].value_ABS;
            sum_cq[6] = sum_cq[6] + L2_pocosArray[i].value_ABS;
            sum_cq[11] = sum_cq[11] + L12_pocosArray[i].value_ABS;
            count_cq[1] = count_cq[1] + 1;
        }else if(L1_pocosArray[i].type == "CQ3"){
            sum_cq[2] = sum_cq[2] + L1_pocosArray[i].value_ABS;
            sum_cq[7] = sum_cq[7] + L2_pocosArray[i].value_ABS;
            sum_cq[12] = sum_cq[12] + L12_pocosArray[i].value_ABS;
            count_cq[2] = count_cq[2] + 1;
        }else if(L1_pocosArray[i].type == "CQ4"){
            sum_cq[3] = sum_cq[3] + L1_pocosArray[i].value_ABS;
            sum_cq[8] = sum_cq[8] + L2_pocosArray[i].value_ABS;
            sum_cq[13] = sum_cq[13] + L12_pocosArray[i].value_ABS;
            count_cq[3] = count_cq[3] + 1;
        }else if(L1_pocosArray[i].type == "CQ5"){
            sum_cq[4] = sum_cq[4] + L1_pocosArray[i].value_ABS;
            sum_cq[9] = sum_cq[9] + L2_pocosArray[i].value_ABS;
            sum_cq[14] = sum_cq[14] + L12_pocosArray[i].value_ABS;
            count_cq[4] = count_cq[4] + 1;
        }
    }

    for(int i=0;i<5;i++){
        if(count_cq[i]!=0){
            CQ[i] = sum_cq[i]/count_cq[i];
            CQ[i+5] = sum_cq[i+5]/count_cq[i];
            CQ[i+10] = sum_cq[i+10]/count_cq[i];
        }
        qDebug() << "CQ" << i+1 << "(L1)" << CQ[i];
        qDebug() << "CQ" << i+1 << "(L2)" << CQ[i+5];
        qDebug() << "CQ" << i+1 << "(L12)" << CQ[i+10];
    }


}

/*Resultado CQ*/

QString CalculoCQ::cqResult(){
    return m_cqResult;
}

void CalculoCQ::setcqResult(QString newcqResult) {
    if(m_cqResult != newcqResult){
        m_cqResult = newcqResult;
        emit cqResultChanged();
    }
}

/*Interpretações*/

QVariantList CalculoCQ::interp(){
    m_interp[0] = cq_interp1[0];
    m_interp[1] = cq_interp1[1];
    m_interp[2] = cq_interp2[0];
    m_interp[3] = cq_interp2[1];
    m_interp[4] = cq_interp3[0];
    m_interp[5] = cq_interp3[1];
    return m_interp;
}

void CalculoCQ::setinterp(QVariantList newinterp){

    for(int i=0;i<newinterp.size();i++){
        m_interp[i]=newinterp[i];
    }

    emit interpChanged();
}

QVariantList CalculoCQ::returnInterp(QString form1, QString int1, QString form2, QString int2, QString form3, QString int3){
    QVariantList interpList;
    cq_interp1[0] = form1;
    cq_interp1[1] = int1;
    cq_interp2[0] = form2;
    cq_interp2[1] = int2;
    cq_interp3[0] = form3;
    cq_interp3[1] = int3;
    interpList.append(cq_interp1[0]);
    interpList.append(cq_interp1[1]);
    interpList.append(cq_interp2[0]);
    interpList.append(cq_interp2[1]);
    interpList.append(cq_interp3[0]);
    interpList.append(cq_interp3[1]);
    return interpList;
}



QString CalculoCQ::interpCalculus(int numFiltro){
    QJSEngine engine;
    QString aux[9] = {0};

    cq_interp1[1] = m_interp[1].toString();
    cq_interp2[1] = m_interp[3].toString();
    cq_interp3[1] = m_interp[5].toString();
    cq_interp1[0] = m_interp[0].toString();
    cq_interp2[0] = m_interp[2].toString();
    cq_interp3[0] = m_interp[4].toString();

    QString CA1 = QString::number(fcCA[0]*CA[0+5*numFiltro]);
    QString CA2 = QString::number(fcCA[1]*CA[1+5*numFiltro]);
    QString CA3 = QString::number(fcCA[2]*CA[2+5*numFiltro]);
    QString CA4 = QString::number(fcCA[3]*CA[3+5*numFiltro]);
    QString CA5 = QString::number(fcCA[4]*CA[4+5*numFiltro]);
    QString CP1 = QString::number(CP[0+5*numFiltro]);
    QString CP2 = QString::number(CP[1+5*numFiltro]);
    QString CP3 = QString::number(CP[2+5*numFiltro]);
    QString CP4 = QString::number(CP[3+5*numFiltro]);
    QString CP5 = QString::number(CP[4+5*numFiltro]);
    QString CN1 = QString::number(CN[0+5*numFiltro]);
    QString CN2 = QString::number(CN[1+5*numFiltro]);
    QString CN3 = QString::number(CN[2+5*numFiltro]);
    QString CN4 = QString::number(CN[3+5*numFiltro]);
    QString CN5 = QString::number(CN[4+5*numFiltro]);
    QString CQ1 = QString::number(CQ[0+5*numFiltro]);
    QString CQ2 = QString::number(CQ[1+5*numFiltro]);
    QString CQ3 = QString::number(CQ[2+5*numFiltro]);
    QString CQ4 = QString::number(CQ[1+5*numFiltro]);
    QString CQ5 = QString::number(CQ[2+5*numFiltro]);
    QString CO_s = QString::number(CO[numFiltro]);
    QString BC = QString::number(blank[numFiltro]);


    cq_interp1[0].replace("CA1",CA1);
    cq_interp1[0].replace("CA2",CA2);
    cq_interp1[0].replace("CA3",CA3);
    cq_interp1[0].replace("CA4", CA4);
    cq_interp1[0].replace("CA5", CA5);
    cq_interp1[0].replace("CP1",CP1);
    cq_interp1[0].replace("CP2",CP2);
    cq_interp1[0].replace("CP3",CP3);
    cq_interp1[0].replace("CP4",CP4);
    cq_interp1[0].replace("CP5",CP5);
    cq_interp1[0].replace("CN1",CN1);
    cq_interp1[0].replace("CN2",CN2);
    cq_interp1[0].replace("CN3",CN3);
    cq_interp1[0].replace("CN4",CN4);
    cq_interp1[0].replace("CN5",CN5);
    cq_interp1[0].replace("CQ1",CQ1);
    cq_interp1[0].replace("CQ2",CQ2);
    cq_interp1[0].replace("CQ3",CQ3);
    cq_interp1[0].replace("CQ4",CQ4);
    cq_interp1[0].replace("CQ5",CQ5);
    cq_interp1[0].replace("CO",CO_s);
    cq_interp1[0].replace("BC",BC);
    cq_interp1[0].replace("x","*");
    cq_interp1[0].replace("^","**");
    cq_interp1[0].replace("÷","/");
    cq_interp1[0].replace(":","/");
    cq_interp1[0].replace("=","==");
    cq_interp1[0].replace(">==",">=");
    cq_interp1[0].replace("<==","<=");
    cq_interp1[0].replace("≠","!=");
    cq_interp1[0].replace("E","&&");
    cq_interp1[0].replace("OU","||");

    cq_interp2[0].replace("CA1",CA1);
    cq_interp2[0].replace("CA2",CA2);
    cq_interp2[0].replace("CA3",CA3);
    cq_interp2[0].replace("CA4",CA4);
    cq_interp2[0].replace("CA5",CA5);
    cq_interp2[0].replace("CP1",CP1);
    cq_interp2[0].replace("CP2",CP2);
    cq_interp2[0].replace("CP3",CP3);
    cq_interp2[0].replace("CP4",CP4);
    cq_interp2[0].replace("CP5",CP5);
    cq_interp2[0].replace("CN1",CN1);
    cq_interp2[0].replace("CN2",CN2);
    cq_interp2[0].replace("CN3",CN3);
    cq_interp2[0].replace("CN4",CN4);
    cq_interp2[0].replace("CN5",CN5);
    cq_interp2[0].replace("CQ1",CQ1);
    cq_interp2[0].replace("CQ2",CQ2);
    cq_interp2[0].replace("CQ3",CQ3);
    cq_interp2[0].replace("CQ4",CQ4);
    cq_interp2[0].replace("CQ5",CQ5);
    cq_interp2[0].replace("CO",CO_s);
    cq_interp2[0].replace("BC",BC);
    cq_interp2[0].replace("x","*");
    cq_interp2[0].replace("^","**");
    cq_interp2[0].replace("÷","/");
    cq_interp2[0].replace(":","/");
    cq_interp2[0].replace("=","==");
    cq_interp2[0].replace(">==",">=");
    cq_interp2[0].replace("<==","<=");
    cq_interp2[0].replace("≠","!=");
    cq_interp2[0].replace("E","&&");
    cq_interp2[0].replace("OU","||");

    cq_interp3[0].replace("CA1",CA1);
    cq_interp3[0].replace("CA2",CA2);
    cq_interp3[0].replace("CA3",CA3);
    cq_interp3[0].replace("CA4",CA4);
    cq_interp3[0].replace("CA5",CA5);
    cq_interp3[0].replace("CP1",CP1);
    cq_interp3[0].replace("CP2",CP2);
    cq_interp3[0].replace("CP3",CP3);
    cq_interp3[0].replace("CP4",CP4);
    cq_interp3[0].replace("CP5",CP5);
    cq_interp3[0].replace("CN1",CN1);
    cq_interp3[0].replace("CN2",CN2);
    cq_interp3[0].replace("CN3",CN3);
    cq_interp3[0].replace("CN4",CN4);
    cq_interp3[0].replace("CN5",CN5);
    cq_interp3[0].replace("CQ1",CQ1);
    cq_interp3[0].replace("CQ2",CQ2);
    cq_interp3[0].replace("CQ3",CQ3);
    cq_interp3[0].replace("CQ4",CQ4);
    cq_interp3[0].replace("CQ5",CQ5);
    cq_interp3[0].replace("CO",CO_s);
    cq_interp3[0].replace("BC",BC);
    cq_interp3[0].replace("x","*");
    cq_interp3[0].replace("^","**");
    cq_interp3[0].replace("÷","/");
    cq_interp3[0].replace(":","/");
    cq_interp3[0].replace("=","==");
    cq_interp2[0].replace(">==",">=");
    cq_interp2[0].replace("<==","<=");
    cq_interp3[0].replace("≠","!=");
    cq_interp3[0].replace("E","&&");
    cq_interp3[0].replace("OU","||");

    if(engine.evaluate(cq_interp1[0]).toBool() == true){
        cq_result = cq_interp1[1];
    }else if(engine.evaluate(cq_interp2[0]).toBool() == true){
        cq_result = cq_interp2[1];
    }else if(engine.evaluate(cq_interp3[0]).toBool() == true){
        cq_result = cq_interp3[1];
    }

    cq_interp1[1] = m_interp[1].toString();
    cq_interp2[1] = m_interp[3].toString();
    cq_interp3[1] = m_interp[5].toString();
    cq_interp1[0] = m_interp[0].toString();
    cq_interp2[0] = m_interp[2].toString();
    cq_interp3[0] = m_interp[4].toString();

    return cq_result;
}
