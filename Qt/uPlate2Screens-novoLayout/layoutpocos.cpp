#include "layoutpocos.h"
#include "dadosbrutos.h"

LayoutPocos::LayoutPocos(QObject *parent)
    : QObject{parent}
{

}
quint8 first_time_layoutpocos = 0;
quint8 first_time_wellcolor = 0;
quint8 first_time_sampleID = 0;
quint8 first_time_subjectID = 0;

quint8 uniqueID_of_DC = 0;
quint8 uniqueID_delete_flag = 0;
quint8 aux_uniqueID[96];

/*TYPE ARRAY*/
QVariantList LayoutPocos::typeArr(){
    if(first_time_layoutpocos == 0){
        for(int i=0;i<96;i++){
            m_typeArr.append(L1_pocosArray[i].type);
        }
        first_time_layoutpocos = 1;
    }else{
        for(int i=0; i<96; i++){
            m_typeArr[i]=L1_pocosArray[i].type;}
    }
    return m_typeArr;
}

void LayoutPocos::settypeArr(QVariantList newtypeArr){
    if(first_time_layoutpocos == 0){
        for(int i=0;i<newtypeArr.size();i++){
            m_typeArr.append(newtypeArr[i]);
        }
        first_time_layoutpocos = 1;
    }else{
        for(int i=0; i<newtypeArr.size(); i++){
            m_typeArr[i]=newtypeArr[i];}
    }
    emit typeArrChanged();
}

QVariantList LayoutPocos::setPocoType(int numPoco, QString typePoco){
    QVariantList TypeList;
    quint8 aux;

    if(typePoco!="DC"&&L1_pocosArray[numPoco].type=="DC"){
        aux_uniqueID[uniqueID_delete_flag] = L1_pocosArray[numPoco].unique_id;
        for(int i=0; i<=uniqueID_delete_flag; i++){
            for(int j=i+1; j<=uniqueID_delete_flag; j++){
                if(aux_uniqueID[j]>aux_uniqueID[i]){
                    aux = aux_uniqueID[i];
                    aux_uniqueID[i] = aux_uniqueID[j];
                    aux_uniqueID[j] = aux;
                }
            }
        }
        uniqueID_delete_flag = uniqueID_delete_flag + 1;
        L1_pocosArray[numPoco].unique_id = 0;
        L2_pocosArray[numPoco].unique_id = 0;
        L12_pocosArray[numPoco].unique_id = 0;
    }

    if(typePoco=="DC"&& L1_pocosArray[numPoco].unique_id==0){
        if(uniqueID_delete_flag>0){
            uniqueID_delete_flag = uniqueID_delete_flag - 1;
            L1_pocosArray[numPoco].unique_id = aux_uniqueID[uniqueID_delete_flag];
            L2_pocosArray[numPoco].unique_id = aux_uniqueID[uniqueID_delete_flag];
            L12_pocosArray[numPoco].unique_id = aux_uniqueID[uniqueID_delete_flag];
        }else{
            uniqueID_of_DC = uniqueID_of_DC + 1;
            L1_pocosArray[numPoco].unique_id = uniqueID_of_DC;
            L2_pocosArray[numPoco].unique_id = uniqueID_of_DC;
            L12_pocosArray[numPoco].unique_id = uniqueID_of_DC;
        }

    }


    L1_pocosArray[numPoco].type = typePoco;
    L2_pocosArray[numPoco].type = typePoco;
    L12_pocosArray[numPoco].type = typePoco;
    for(int i=0; i<NUM_POCOS; i++){
        TypeList.append(L1_pocosArray[i].type);
    }
    return TypeList;
}

/*UNIQUE ID*/

QVariant LayoutPocos::uniqueID(){
    return m_uniqueID;
}

void LayoutPocos::setuniqueID(QVariant new_uniqueID){
    if(new_uniqueID!=m_uniqueID){
        m_uniqueID = new_uniqueID;
    }
    emit uniqueIDChanged();
}

QVariant LayoutPocos::returnUniqueID(int numPoco){
    QVariant new_uniqueID;
    if(L1_pocosArray[numPoco].unique_id==0){
        new_uniqueID = "";
    }else{
        new_uniqueID = L1_pocosArray[numPoco].unique_id;
    }

    return new_uniqueID;
}

/*WELL ID*/

QVariant LayoutPocos::wellID(){
    return m_wellID;
}

void LayoutPocos::setwellID(QVariant new_wellID){
    if(new_wellID!=m_wellID){
        m_wellID = new_wellID;
    }
    emit wellIDChanged();
}

QVariant LayoutPocos::returnWellID(int numPoco){
    QVariant new_wellID(L1_pocosArray[numPoco].well_id);
    return new_wellID;
}

/*SAMPLE ID*/

QVariantList LayoutPocos::sampleID(){
    if(first_time_sampleID == 0){
        for(int i=0;i<96;i++){
            m_sampleID.append(L1_pocosArray[i].sample_id);
        }
        first_time_sampleID= 1;
    }else{
        for(int i=0; i<96; i++){
            m_sampleID[i]=L1_pocosArray[i].sample_id;}
    }
    return m_sampleID;
}

void LayoutPocos::setsampleID(QVariantList new_sampleID){
    if(first_time_sampleID == 0){
        for(int i=0;i<new_sampleID.size();i++){
            m_sampleID.append(new_sampleID[i]);
        }
        first_time_sampleID = 1;
    }else{
        for(int i=0; i<new_sampleID.size(); i++){
            m_sampleID[i]=new_sampleID[i];}
    }
    emit sampleIDChanged();
}

QVariantList LayoutPocos::returnSampleID(int numPoco, QString input){
    L1_pocosArray[numPoco].sample_id = input;
    L2_pocosArray[numPoco].sample_id = input;
    L12_pocosArray[numPoco].sample_id = input;
    QVariantList new_sampleID;
    for(int i=0; i<NUM_POCOS; i++){
        new_sampleID.append(L1_pocosArray[i].sample_id);
    }
    return new_sampleID;
}

/*SUBJECT ID*/

QVariantList LayoutPocos::subjID(){
    if(first_time_subjectID == 0){
        for(int i=0;i<96;i++){
            m_subjID.append(L1_pocosArray[i].subject_id);
        }
        first_time_subjectID = 1;
    }else{
        for(int i=0; i<96; i++){
            m_subjID[i]=L1_pocosArray[i].subject_id;}
    }
    return m_subjID;
}

void LayoutPocos::setsubjID(QVariantList new_subjID){
    if(first_time_subjectID == 0){
        for(int i=0;i<new_subjID.size();i++){
            m_subjID.append(new_subjID[i]);
        }
        first_time_subjectID = 1;
    }else{
        for(int i=0; i<new_subjID.size(); i++){
            m_subjID[i]=new_subjID[i];}
    }
    emit subjIDChanged();
}

QVariantList LayoutPocos::returnSubjID(int numPoco, QString input){
    L1_pocosArray[numPoco].subject_id = input;
    L2_pocosArray[numPoco].subject_id = input;
    L12_pocosArray[numPoco].subject_id = input;
    QVariantList new_subjID;
    for(int i=0; i<NUM_POCOS; i++){
        new_subjID.append(L1_pocosArray[i].subject_id);
    }
    return new_subjID;
}

/*COLOR ARRAY*/
QVariantList LayoutPocos::colorWell(){
    if(first_time_wellcolor == 0){
        for(int i=0;i<96;i++){
            m_colorWell.append(L1_pocosArray[i].colorWell);
        }
        first_time_wellcolor = 1;
    }else{
        for(int i=0; i<96; i++){
            m_colorWell[i]=L1_pocosArray[i].colorWell;}
    }
    return m_colorWell;
}

void LayoutPocos::setcolorWell(QVariantList newcolorWell){
    if(first_time_wellcolor == 0){
        for(int i=0;i<newcolorWell.size();i++){
            m_colorWell.append(newcolorWell[i]);
        }
        first_time_wellcolor = 1;
    }else{
        for(int i=0; i<newcolorWell.size(); i++){
            m_colorWell[i]=newcolorWell[i];}
    }
    emit colorWellChanged();
}

QVariantList LayoutPocos::returnColorWell(int numPoco, QString input){
    QVariantList ColorList;

    L1_pocosArray[numPoco].colorWell = input;
    L2_pocosArray[numPoco].colorWell = input;
    L12_pocosArray[numPoco].colorWell = input;

    for(int i=0; i<NUM_POCOS; i++){
        ColorList.append(L1_pocosArray[i].colorWell);
    }
    return ColorList;
}


