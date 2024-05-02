#include "calculocutoff.h"
#include "dadosbrutos.h"

CalculoCutoff::CalculoCutoff(QObject *parent)
    : QObject{parent}
{

}

QString formulaCO, formulaAux1, formulaAux2;
QString interp1[2], interp2[2], interp3[2];
bool useblank_CO = true;
float CA[15] = {0};
float CP[15] = {0};
float CN[15] = {0};
float fcCA[5] = {1, 1, 1, 1, 1};
float CO[3];// Aux1[3], Aux2[3];

/*fatores de Calibração*/

QVariantList CalculoCutoff::fc_CA(){
    for(int i=0;i<m_fcCA.size();i++){
        m_fcCA[i] = fcCA[i];
    }
    return m_fcCA;
}

void CalculoCutoff::setfc_CA(QVariantList newfc_CA){
    for(int i=0;i<newfc_CA.size();i++){
        if(newfc_CA[i]!=0){
            m_fcCA[i]=newfc_CA[i];
        }
    }


    emit fc_CAChanged();
}

QVariantList CalculoCutoff::returnfc_CA(int numCA, float input){
    QVariantList fcList;
    fcCA[numCA] = input;
    for(int i=0; i<5; i++){
        fcList.append(fcCA[i]);
    }
    qDebug() << "fcCA atualizado" << fcCA[numCA];
    return fcList;
}

/*Cálculos CAn, CNn e CPn*/
void CalculoCutoff::caCalculus(){
    float sum_ca[15] = {0};
    float count_ca[5] = {0};
    for(int i = 0; i<NUM_POCOS; i++){
        if(L1_pocosArray[i].type == "CA1"){
            sum_ca[0] = sum_ca[0] + L1_pocosArray[i].value_ABS;
            sum_ca[5] = sum_ca[5] + L2_pocosArray[i].value_ABS;
            sum_ca[10] = sum_ca[10] + L12_pocosArray[i].value_ABS;
            count_ca[0] = count_ca[0] + 1;
        }else if(L1_pocosArray[i].type == "CA2"){
            sum_ca[1] = sum_ca[1] + L1_pocosArray[i].value_ABS;
            sum_ca[6] = sum_ca[6] + L2_pocosArray[i].value_ABS;
            sum_ca[11] = sum_ca[11] + L12_pocosArray[i].value_ABS;
            count_ca[1] = count_ca[1] + 1;
        }else if(L1_pocosArray[i].type == "CA3"){
            sum_ca[2] = sum_ca[2] + L1_pocosArray[i].value_ABS;
            sum_ca[7] = sum_ca[7] + L2_pocosArray[i].value_ABS;
            sum_ca[12] = sum_ca[12] + L12_pocosArray[i].value_ABS;
            count_ca[2] = count_ca[2] + 1;
        }else if(L1_pocosArray[i].type == "CA4"){
            sum_ca[3] = sum_ca[3] + L1_pocosArray[i].value_ABS;
            sum_ca[8] = sum_ca[8] + L2_pocosArray[i].value_ABS;
            sum_ca[13] = sum_ca[13] + L12_pocosArray[i].value_ABS;
            count_ca[3] = count_ca[3] + 1;
        }else if(L1_pocosArray[i].type == "CA5"){
            sum_ca[4] = sum_ca[4] + L1_pocosArray[i].value_ABS;
            sum_ca[9] = sum_ca[9] + L2_pocosArray[i].value_ABS;
            sum_ca[14] = sum_ca[14] + L12_pocosArray[i].value_ABS;
            count_ca[4] = count_ca[4] + 1;
        }
    }
    for(int i=0;i<5;i++){
        if(count_ca[i]!=0){
            CA[i] = sum_ca[i]/count_ca[i];
            CA[i+5] = sum_ca[i+5]/count_ca[i];
            CA[i+10] = sum_ca[i+10]/count_ca[i];
        }
        qDebug() << "CA" << i+1 << "(L1)" << CA[i];
        qDebug() << "CA" << i+1 << "(L2)" << CA[i+5];
        qDebug() << "CA" << i+1 << "(L12)" << CA[i+10];
        qDebug() << "fcCA:" <<fcCA[i];
    }
}

void CalculoCutoff::cpCalculus(){
    float sum_cp[15] = {0};
    float count_cp[5] = {0};
    for(int i = 0; i<NUM_POCOS; i++){
        if(L1_pocosArray[i].type == "CP1"){
            sum_cp[0] = sum_cp[0] + L1_pocosArray[i].value_ABS;
            sum_cp[5] = sum_cp[5] + L2_pocosArray[i].value_ABS;
            sum_cp[10] = sum_cp[10] + L12_pocosArray[i].value_ABS;
            count_cp[0] = count_cp[0] + 1;
        }else if(L1_pocosArray[i].type == "CP2"){
            sum_cp[1] = sum_cp[1] + L1_pocosArray[i].value_ABS;
            sum_cp[6] = sum_cp[6] + L2_pocosArray[i].value_ABS;
            sum_cp[11] = sum_cp[11] + L12_pocosArray[i].value_ABS;
            count_cp[1] = count_cp[1] + 1;
        }else if(L1_pocosArray[i].type == "CP3"){
            sum_cp[2] = sum_cp[2] + L1_pocosArray[i].value_ABS;
            sum_cp[7] = sum_cp[7] + L2_pocosArray[i].value_ABS;
            sum_cp[12] = sum_cp[12] + L12_pocosArray[i].value_ABS;
            count_cp[2] = count_cp[2] + 1;
        }else if(L1_pocosArray[i].type == "CP4"){
            sum_cp[3] = sum_cp[3] + L1_pocosArray[i].value_ABS;
            sum_cp[8] = sum_cp[8] + L2_pocosArray[i].value_ABS;
            sum_cp[13] = sum_cp[13] + L12_pocosArray[i].value_ABS;
            count_cp[3] = count_cp[3] + 1;
        }else if(L1_pocosArray[i].type == "CP5"){
            sum_cp[4] = sum_cp[4] + L1_pocosArray[i].value_ABS;
            sum_cp[9] = sum_cp[9] + L2_pocosArray[i].value_ABS;
            sum_cp[14] = sum_cp[14] + L12_pocosArray[i].value_ABS;
            count_cp[4] = count_cp[4] + 1;
        }
    }
    for(int i=0;i<5;i++){
        if(count_cp[i]!=0){
            CP[i] = sum_cp[i]/count_cp[i];
            CP[i+5] = sum_cp[i+5]/count_cp[i];
            CP[i+10] = sum_cp[i+10]/count_cp[i];
        }
        qDebug() << "CP" << i+1 << "(L1)" << CP[i];
        qDebug() << "CP" << i+1 << "(L2)" << CP[i+5];
        qDebug() << "CP" << i+1 << "(L12)" << CP[i+10];
    }
}

void CalculoCutoff::cnCalculus(){
    float sum_cn[15] = {0};
    float count_cn[5] = {0};
    for(int i = 0; i<NUM_POCOS; i++){
        if(L1_pocosArray[i].type == "CN1"){
            sum_cn[0] = sum_cn[0] + L1_pocosArray[i].value_ABS;
            sum_cn[5] = sum_cn[5] + L2_pocosArray[i].value_ABS;
            sum_cn[10] = sum_cn[10] + L12_pocosArray[i].value_ABS;
            count_cn[0] = count_cn[0] + 1;
        }else if(L1_pocosArray[i].type == "CN2"){
            sum_cn[1] = sum_cn[1] + L1_pocosArray[i].value_ABS;
            sum_cn[6] = sum_cn[6] + L2_pocosArray[i].value_ABS;
            sum_cn[11] = sum_cn[11] + L12_pocosArray[i].value_ABS;
            count_cn[1] = count_cn[1] + 1;
        }else if(L1_pocosArray[i].type == "CN3"){
            sum_cn[2] = sum_cn[2] + L1_pocosArray[i].value_ABS;
            sum_cn[7] = sum_cn[7] + L2_pocosArray[i].value_ABS;
            sum_cn[12] = sum_cn[12] + L12_pocosArray[i].value_ABS;
            count_cn[2] = count_cn[2] + 1;
        }else if(L1_pocosArray[i].type == "CN4"){
            sum_cn[3] = sum_cn[3] + L1_pocosArray[i].value_ABS;
            sum_cn[8] = sum_cn[8] + L2_pocosArray[i].value_ABS;
            sum_cn[13] = sum_cn[13] + L12_pocosArray[i].value_ABS;
            count_cn[3] = count_cn[3] + 1;
        }else if(L1_pocosArray[i].type == "CN5"){
            sum_cn[4] = sum_cn[4] + L1_pocosArray[i].value_ABS;
            sum_cn[9] = sum_cn[9] + L2_pocosArray[i].value_ABS;
            sum_cn[14] = sum_cn[14] + L12_pocosArray[i].value_ABS;
            count_cn[4] = count_cn[4] + 1;
        }
    }
    for(int i=0;i<5;i++){
        if(count_cn[i]!=0){
            CN[i] = sum_cn[i]/count_cn[i];
            CN[i+5] = sum_cn[i+5]/count_cn[i];
            CN[i+10] = sum_cn[i+10]/count_cn[i];
        }
        qDebug() << "CN" << i+1 << "(L1)" << CN[i];
        qDebug() << "CN" << i+1 << "(L2)" << CN[i+5];
        qDebug() << "CN" << i+1 << "(L12)" << CN[i+10];
    }
}

/*Formulas*/

QVariantList CalculoCutoff::formulas(){
    m_formulas[0] = formulaCO;
    m_formulas[1] = formulaAux1;
    m_formulas[2] = formulaAux2;
    return m_formulas;
}

void CalculoCutoff::setformulas(QVariantList newformulas){

    for(int i=0;i<newformulas.size();i++){
        m_formulas[i]=newformulas[i];
    }

    emit formulasChanged();
}

QVariantList CalculoCutoff::returnFormulas(QString form1, QString form2, QString form3){
    QVariantList formulasList;
    formulaCO = form1;
    formulaAux1 = form2;
    formulaAux2 = form3;
    formulasList.append(formulaCO);
    formulasList.append(formulaAux1);
    formulasList.append(formulaAux2);
    return formulasList;
}

/*Interpretações*/

QVariantList CalculoCutoff::interp(){
    m_interp[0] = interp1[0];
    m_interp[1] = interp1[1];
    m_interp[2] = interp2[0];
    m_interp[3] = interp2[1];
    m_interp[4] = interp3[0];
    m_interp[5] = interp3[1];
    return m_interp;
}

void CalculoCutoff::setinterp(QVariantList newinterp){

    for(int i=0;i<newinterp.size();i++){
        m_interp[i]=newinterp[i];
    }
    emit interpChanged();
}

QVariantList CalculoCutoff::returnInterp(QString form1, QString int1, QString form2, QString int2, QString form3, QString int3){
    QVariantList interpList;
    interp1[0] = form1;
    interp1[1] = int1;
    interp2[0] = form2;
    interp2[1] = int2;
    interp3[0] = form3;
    interp3[1] = int3;
    interpList.append(interp1[0]);
    interpList.append(interp1[1]);
    interpList.append(interp2[0]);
    interpList.append(interp2[1]);
    interpList.append(interp3[0]);
    interpList.append(interp3[1]);
    return interpList;
}

/*Usar o branco*/

bool CalculoCutoff::useBlank(){
    m_useBlank = useblank_CO;
    return m_useBlank;
}

void CalculoCutoff::setUseBlank(bool newInput){
    if(newInput != m_useBlank){
        m_useBlank = newInput;
        useblank_CO = newInput;
        qDebug() << m_useBlank;
        emit useBlankChanged();
    }
    qDebug() << m_useBlank;
}


/*Cálculo cut-off*/

void CalculoCutoff::zerarCO(){

    for(int i=0; i<96; i++){
       L1_pocosArray[i].string_CO = "";
       L2_pocosArray[i].string_CO = "";
       L12_pocosArray[i].string_CO = "";
    }

}

void CalculoCutoff::coCalculus(){
    QJSEngine engine;
    QString Aux1[3];
    QString Aux2[3];
    QString aux[6];
    QString ABS[3];

    for(int i=0; i<3;i++){
        QString CA1 = QString::number(fcCA[0]*CA[0+5*i]);
        QString CA2 = QString::number(fcCA[1]*CA[1+5*i]);
        QString CA3 = QString::number(fcCA[2]*CA[2+5*i]);
        QString CA4 = QString::number(fcCA[3]*CA[3+5*i]);
        QString CA5 = QString::number(fcCA[4]*CA[4+5*i]);
        QString CP1 = QString::number(CP[0+5*i]);
        QString CP2 = QString::number(CP[1+5*i]);
        QString CP3 = QString::number(CP[2+5*i]);
        QString CP4 = QString::number(CP[3+5*i]);
        QString CP5 = QString::number(CP[4+5*i]);
        QString CN1 = QString::number(CN[0+5*i]);
        QString CN2 = QString::number(CN[1+5*i]);
        QString CN3 = QString::number(CN[2+5*i]);
        QString CN4 = QString::number(CN[3+5*i]);
        QString CN5 = QString::number(CN[4+5*i]);

        formulaCO = m_formulas[0].toString();
        formulaAux1 = m_formulas[1].toString();
        formulaAux2 = m_formulas[2].toString();


        formulaCO.replace("CA1", CA1);
        formulaCO.replace("CA2", CA2);
        formulaCO.replace("CA3", CA3);
        formulaCO.replace("CA4", CA4);
        formulaCO.replace("CA5", CA5);
        formulaCO.replace("CP1", CP1);
        formulaCO.replace("CP2", CP2);
        formulaCO.replace("CP3", CP3);
        formulaCO.replace("CP4", CP4);
        formulaCO.replace("CP5", CP5);
        formulaCO.replace("CN1", CN1);
        formulaCO.replace("CN2", CN2);
        formulaCO.replace("CN3", CN3);
        formulaCO.replace("CN4", CN4);
        formulaCO.replace("CN5", CN5);
        formulaCO.replace("x","*");
        formulaCO.replace("^","**");
        formulaCO.replace("÷","/");
        formulaCO.replace(":","/");
        CO[i] = engine.evaluate(formulaCO).toNumber();
        qDebug() << "CO:" << i+1 << CO;


        formulaAux1.replace("CO", QString::number(CO[i]));
        formulaAux1.replace("CA1", CA1);
        formulaAux1.replace("CA2", CA2);
        formulaAux1.replace("CA3", CA3);
        formulaAux1.replace("CA4", CA4);
        formulaAux1.replace("CA5", CA5);
        formulaAux1.replace("CP1", CP1);
        formulaAux1.replace("CP2", CP2);
        formulaAux1.replace("CP3", CP3);
        formulaAux1.replace("CP4", CP4);
        formulaAux1.replace("CP5", CP5);
        formulaAux1.replace("CN1", CN1);
        formulaAux1.replace("CN2", CN2);
        formulaAux1.replace("CN3", CN3);
        formulaAux1.replace("CN4", CN4);
        formulaAux1.replace("CN5", CN5);
        formulaAux1.replace("x","*");
        formulaAux1.replace("^","**");
        formulaAux1.replace("÷","/");
        formulaAux1.replace(":","/");
        Aux1[i] = formulaAux1;
        qDebug() << "Aux"  << i+1 << ":" << Aux1[i];

        formulaAux2.replace("CO", QString::number(CO[i]));
        formulaAux2.replace("CA1", CA1);
        formulaAux2.replace("CA2", CA2);
        formulaAux2.replace("CA3", CA3);
        formulaAux2.replace("CA4", CA4);
        formulaAux2.replace("CA5", CA5);
        formulaAux2.replace("CP1", CP1);
        formulaAux2.replace("CP2", CP2);
        formulaAux2.replace("CP3", CP3);
        formulaAux2.replace("CP4", CP4);
        formulaAux2.replace("CP5", CP5);
        formulaAux2.replace("CN1", CN1);
        formulaAux2.replace("CN2", CN2);
        formulaAux2.replace("CN3", CN3);
        formulaAux2.replace("CN4", CN4);
        formulaAux2.replace("CN5", CN5);
        formulaAux2.replace("x","*");
        formulaAux2.replace("^","**");
        formulaAux2.replace("÷","/");
        formulaAux2.replace(":","/");
        Aux2[i] = formulaAux2;
        qDebug() << "Aux"  << i+1 << ":" << Aux2[i];

  }

    for(int j=0; j<NUM_POCOS; j++){
        if(m_useBlank == false){
            ABS[0] = QString::number(L1_pocosArray[j].value_ABS);
            ABS[1] = QString::number(L2_pocosArray[j].value_ABS);
            ABS[2] = QString::number(L12_pocosArray[j].value_ABS);
        }else{
            ABS[0] = QString::number(L1_pocosArray[j].value_afterBlank);
            ABS[1] = QString::number(L2_pocosArray[j].value_afterBlank);
            ABS[2] = QString::number(L12_pocosArray[j].value_afterBlank);
        }

        aux[0] = Aux1[0];
        aux[1] = Aux1[1];
        aux[2] = Aux1[2];
        aux[3] = Aux2[0];
        aux[4] = Aux2[1];
        aux[5] = Aux2[2];;

        aux[0].replace("ABS", ABS[0]);
        aux[1].replace("ABS", ABS[1]);
        aux[2].replace("ABS", ABS[2]);
        aux[3].replace("ABS", ABS[0]);
        aux[4].replace("ABS", ABS[1]);
        aux[5].replace("ABS", ABS[2]);

        for(int zeraVazio = 0; zeraVazio<6; zeraVazio++){
            if(aux[zeraVazio] == ""){
                aux[zeraVazio] = "0";
            }

        }

        L1_pocosArray[j].value_AUX1 = engine.evaluate(aux[0]).toNumber();
        L2_pocosArray[j].value_AUX1 = engine.evaluate(aux[1]).toNumber();
        L12_pocosArray[j].value_AUX1 = engine.evaluate(aux[2]).toNumber();
        L1_pocosArray[j].value_AUX2 = engine.evaluate(aux[3]).toNumber();
        L2_pocosArray[j].value_AUX2 = engine.evaluate(aux[4]).toNumber();
        L12_pocosArray[j].value_AUX2 = engine.evaluate(aux[5]).toNumber();

    }

    formulaCO = m_formulas[0].toString();
    formulaAux1 = m_formulas[1].toString();
    formulaAux2 = m_formulas[2].toString();

}

void CalculoCutoff::interpCalculus(){
    QJSEngine engine;
    QString interp[9];
    QString aux[9];
    QString ABS[3];
    QString Aux1[3];
    QString Aux2[3];

    zerarCO();
    for(int j=0; j<3;j++){
        QString CA1 = QString::number(fcCA[0]*CA[0+5*j]);
        QString CA2 = QString::number(fcCA[1]*CA[1+5*j]);
        QString CA3 = QString::number(fcCA[2]*CA[2+5*j]);
        QString CA4 = QString::number(fcCA[3]*CA[3+5*j]);
        QString CA5 = QString::number(fcCA[4]*CA[4+5*j]);
        QString CP1 = QString::number(CP[0+5*j]);
        QString CP2 = QString::number(CP[1+5*j]);
        QString CP3 = QString::number(CP[2+5*j]);
        QString CP4 = QString::number(CP[3+5*j]);
        QString CP5 = QString::number(CP[4+5*j]);
        QString CN1 = QString::number(CN[0+5*j]);
        QString CN2 = QString::number(CN[1+5*j]);
        QString CN3 = QString::number(CN[2+5*j]);
        QString CN4 = QString::number(CN[3+5*j]);
        QString CN5 = QString::number(CN[4+5*j]);

        QString CO_s = QString::number(CO[j]);
        //QString Aux1_s = QString::number(Aux1[j]);
        //QString Aux2_s = QString::number(Aux2[j]);


        interp1[0] = m_interp[0].toString();
        interp1[1] = m_interp[1].toString();
        interp2[0] = m_interp[2].toString();
        interp2[1] = m_interp[3].toString();
        interp3[0] = m_interp[4].toString();
        interp3[1] = m_interp[5].toString();


        interp1[0].replace("CO", CO_s);
        //interp1[0].replace("AUX1", Aux1_s);
        //interp1[0].replace("AUX2", Aux2_s);
        interp1[0].replace("CA1", CA1);
        interp1[0].replace("CA2", CA2);
        interp1[0].replace("CA3", CA3);
        interp1[0].replace("CA4", CA4);
        interp1[0].replace("CA5", CA5);
        interp1[0].replace("CP1", CP1);
        interp1[0].replace("CP2", CP2);
        interp1[0].replace("CP3", CP3);
        interp1[0].replace("CP4", CP4);
        interp1[0].replace("CP5", CP5);
        interp1[0].replace("CN1", CN1);
        interp1[0].replace("CN2", CN2);
        interp1[0].replace("CN3", CN3);
        interp1[0].replace("CN4", CN4);
        interp1[0].replace("CN5", CN5);
        interp1[0].replace("x","*");
        interp1[0].replace("^","**");
        interp1[0].replace("÷","/");
        interp1[0].replace(":","/");
        interp1[0].replace("=","==");
        interp1[0].replace(">==",">=");
        interp1[0].replace("<==","<=");
        interp1[0].replace("≠","!=");
        interp1[0].replace("E","&&");
        interp1[0].replace("OU","||");

        interp2[0].replace("CO", CO_s);
        //interp2[0].replace("AUX1", Aux1_s);
        //interp2[0].replace("AUX2", Aux2_s);
        interp2[0].replace("CA1", CA1);
        interp2[0].replace("CA2", CA2);
        interp2[0].replace("CA3", CA3);
        interp2[0].replace("CA4", CA4);
        interp2[0].replace("CA5", CA5);
        interp2[0].replace("CP1", CP1);
        interp2[0].replace("CP2", CP2);
        interp2[0].replace("CP3", CP3);
        interp2[0].replace("CP4", CP4);
        interp2[0].replace("CP5", CP5);
        interp2[0].replace("CN1", CN1);
        interp2[0].replace("CN2", CN2);
        interp2[0].replace("CN3", CN3);
        interp2[0].replace("CN4", CN4);
        interp2[0].replace("CN5", CN5);
        interp2[0].replace("x","*");
        interp2[0].replace("^","**");
        interp2[0].replace("÷","/");
        interp2[0].replace(":","/");
        interp2[0].replace("=","==");
        interp2[0].replace(">==",">=");
        interp2[0].replace("<==","<=");
        interp2[0].replace("≠","!=");
        interp2[0].replace("E","&&");
        interp2[0].replace("OU","||");


        interp3[0].replace("CO", CO_s);
        //interp3[0].replace("AUX1", Aux1_s);
        //interp3[0].replace("AUX2", Aux2_s);
        interp3[0].replace("CA1", CA1);
        interp3[0].replace("CA1", CA1);
        interp3[0].replace("CA2", CA2);
        interp3[0].replace("CA3", CA3);
        interp3[0].replace("CA4", CA4);
        interp3[0].replace("CA5", CA5);
        interp3[0].replace("CP1", CP1);
        interp3[0].replace("CP2", CP2);
        interp3[0].replace("CP3", CP3);
        interp3[0].replace("CP4", CP4);
        interp3[0].replace("CP5", CP5);
        interp3[0].replace("CN1", CN1);
        interp3[0].replace("CN2", CN2);
        interp3[0].replace("CN3", CN3);
        interp3[0].replace("CN4", CN4);
        interp3[0].replace("CN5", CN5);
        interp3[0].replace("x","*");
        interp3[0].replace("^","**");
        interp3[0].replace("÷","/");
        interp3[0].replace(":","/");
        interp3[0].replace("=","==");
        interp3[0].replace(">==",">=");
        interp3[0].replace("<==","<=");
        interp3[0].replace("≠","!=");
        interp3[0].replace("E","&&");
        interp3[0].replace("OU","||");

        interp[3*j] = interp1[0];
        interp[3*j+1] = interp2[0];
        interp[3*j+2] = interp3[0];

  //     qDebug() << "Interp" << 3j << aux[3*j];
  //      qDebug() << "Interp" << 3j+1 << aux[3*j+1];
  //      qDebug() << "Interp" << 3j+2 << aux[3*j+2];
    }


    for(int i=0; i<NUM_POCOS;i++){
        if(L1_pocosArray[i].type != ""&& L1_pocosArray[i].type != "BC"){
            if(m_useBlank == false){
                ABS[0] = QString::number(L1_pocosArray[i].value_ABS);
                ABS[1] = QString::number(L2_pocosArray[i].value_ABS);
                ABS[2] = QString::number(L12_pocosArray[i].value_ABS);
            }else{
                ABS[0] = QString::number(L1_pocosArray[i].value_afterBlank);
                ABS[1] = QString::number(L2_pocosArray[i].value_afterBlank);
                ABS[2] = QString::number(L12_pocosArray[i].value_afterBlank);
            }
            Aux1[0] = QString::number(L1_pocosArray[i].value_AUX1);
            Aux1[1] = QString::number(L2_pocosArray[i].value_AUX1);
            Aux1[2] = QString::number(L12_pocosArray[i].value_AUX1);

            Aux2[0] = QString::number(L1_pocosArray[i].value_AUX2);
            Aux2[1] = QString::number(L2_pocosArray[i].value_AUX2);
            Aux2[2] = QString::number(L12_pocosArray[i].value_AUX2);

            for(int countAux=0; countAux<9; countAux++){
                aux[countAux] = interp[countAux];
            }

            aux[0].replace("ABS", ABS[0]);
            aux[0].replace("AUX1", Aux1[0]);
            aux[0].replace("AUX2", Aux2[0]);

            aux[1].replace("ABS", ABS[0]);
            aux[1].replace("AUX1", Aux1[0]);
            aux[1].replace("AUX2", Aux2[0]);

            aux[2].replace("ABS", ABS[0]);
            aux[2].replace("AUX1", Aux1[0]);
            aux[2].replace("AUX2", Aux2[0]);

            aux[3].replace("ABS", ABS[1]);
            aux[3].replace("AUX1", Aux1[1]);
            aux[3].replace("AUX2", Aux2[1]);

            aux[4].replace("ABS", ABS[1]);
            aux[4].replace("AUX1", Aux1[1]);
            aux[4].replace("AUX2", Aux2[1]);

            aux[5].replace("ABS", ABS[1]);
            aux[5].replace("AUX1", Aux1[1]);
            aux[5].replace("AUX2", Aux2[1]);

            aux[6].replace("ABS", ABS[2]);
            aux[6].replace("AUX1", Aux1[2]);
            aux[6].replace("AUX2", Aux2[2]);

            aux[7].replace("ABS", ABS[2]);
            aux[7].replace("AUX1", Aux1[2]);
            aux[7].replace("AUX2", Aux2[2]);

            aux[8].replace("ABS", ABS[2]);
            aux[8].replace("AUX1", Aux1[2]);
            aux[8].replace("AUX2", Aux2[2]);


            if(engine.evaluate(aux[0]).toBool() == true){
                L1_pocosArray[i].string_CO = interp1[1];
            }else if(engine.evaluate(aux[1]).toBool() == true){
                L1_pocosArray[i].string_CO = interp2[1];
            }else if(engine.evaluate(aux[2]).toBool() == true){
                L1_pocosArray[i].string_CO = interp3[1];
            }

            if(engine.evaluate(aux[3]).toBool() == true){
                L2_pocosArray[i].string_CO = interp1[1];
            }else if(engine.evaluate(aux[4]).toBool() == true){
                L2_pocosArray[i].string_CO = interp2[1];
            }else if(engine.evaluate(aux[5]).toBool() == true){
                L2_pocosArray[i].string_CO = interp3[1];
            }

            if(engine.evaluate(aux[6]).toBool() == true){
                L12_pocosArray[i].string_CO = interp1[1];
            }else if(engine.evaluate(aux[7]).toBool() == true){
                L12_pocosArray[i].string_CO = interp2[1];
            }else if(engine.evaluate(aux[8]).toBool() == true){
                L12_pocosArray[i].string_CO = interp3[1];
            }
        }
    }

    interp1[0] = m_interp[0].toString();
    interp1[1] = m_interp[1].toString();
    interp2[0] = m_interp[2].toString();
    interp2[1] = m_interp[3].toString();
    interp3[0] = m_interp[4].toString();
    interp3[1] = m_interp[5].toString();


}

QVariantList CalculoCutoff::printInterp(int numFiltros){
    QVariantList InterpList;
    if(numFiltros==0){
        for(int i=0;i<NUM_POCOS;i++){
            InterpList.append(L1_pocosArray[i].string_CO);
        }
    }else if(numFiltros==1){
        for(int i=0;i<NUM_POCOS;i++){
            InterpList.append(L2_pocosArray[i].string_CO);
        }
    }else{
        for(int i=0;i<NUM_POCOS;i++){
            InterpList.append(L12_pocosArray[i].string_CO);
        }
    }

    return InterpList;
}

/* EXIBIR DADOS AUX1 E AUX2*/

QVariantList CalculoCutoff::printAux1Data(int numFiltro){
    QVariantList Aux1List;
    int i = 0;
    if(numFiltro==0){
        for(i=0;i<NUM_POCOS;i++){
            Aux1List.append(L1_pocosArray[i].value_AUX1);
        }
    }else if(numFiltro==1){
        for(i=0;i<NUM_POCOS;i++){
            Aux1List.append(L2_pocosArray[i].value_AUX1);
        }
    }else{
        for(i=0;i<NUM_POCOS;i++){
            Aux1List.append(L12_pocosArray[i].value_AUX1);
        }

    }

    return Aux1List;
}

QVariantList CalculoCutoff::printAux2Data(int numFiltro){
    QVariantList Aux2List;
    int i = 0;
    if(numFiltro==0){
        for(i=0;i<NUM_POCOS;i++){
            Aux2List.append(L1_pocosArray[i].value_AUX2);
        }
    }else if(numFiltro==1){
        for(i=0;i<NUM_POCOS;i++){
            Aux2List.append(L2_pocosArray[i].value_AUX2);
        }
    }else{
        for(i=0;i<NUM_POCOS;i++){
            Aux2List.append(L12_pocosArray[i].value_AUX2);
        }

    }

    return Aux2List;
}
