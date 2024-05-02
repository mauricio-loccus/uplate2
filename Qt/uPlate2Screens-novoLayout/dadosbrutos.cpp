#include "dadosbrutos.h"
#include "calculobranco.h"
#include "calculocutoff.h"
#include "calculocq.h"

DadosBrutos::DadosBrutos(QObject *parent)
    : QObject{parent}
{

}

CalculoBranco classeBranco;
CalculoCutoff classeCO;
CalculoCQ classeCQ;
int i;


struct pocoInfo L1_pocosArray[NUM_POCOS];
struct pocoInfo L2_pocosArray[NUM_POCOS];
struct pocoInfo L12_pocosArray[NUM_POCOS];


quint8 flag = 0;

static QByteArray checksum(QByteArray array){
    QByteArray CRC;
    CRC.resize(2);
    quint16 sum = 0;
    for(int i=0; i<array.size();i++){
        sum += static_cast<quint8>(array[i]);
    }
    CRC[0] = sum>>8;
    CRC[1] = sum&0xFF;
    return CRC;
}


void DadosBrutos::genRandomArchive()
{
    QByteArray ReadingSamples;
    QByteArray Header = QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00\x01\x00\x00\x00\x01\x8E\x00\x00\x00\x01\x00\x00\x00\x01\x00\x00\x00\x01");
    QByteArray Data;
    if(filtro2_Read==0){
        Data.resize(384);
        for(int i=0;i<Data.size();i++){
            if(i%4==0){
                Data[i] = QRandomGenerator::global()->bounded(0x3c,0x41);
            }else{
                Data[i] = QRandomGenerator::global()->generate();
            }
        }
    }else{
        Data.resize(768);
        for(int i=0;i<Data.size();i++){
            if(i%4==0){
                Data[i] = QRandomGenerator::global()->bounded(0x3c,0x41);
            }else{
                Data[i] = QRandomGenerator::global()->generate();
            }
        }
    }

    ReadingSamples = Header + Data;
    QByteArray CRC = checksum(ReadingSamples);
    ReadingSamples = Header + Data + CRC;
    qDebug() << ReadingSamples.toHex();
    bytesToFloat(ReadingSamples,filtro2_Read);
    for(int countclean=0; countclean<15; countclean++){
        CA[countclean] = 0;
        CP[countclean] = 0;
        CN[countclean] = 0;
        CQ[countclean] = 0;
    }
    for(int countclean=0; countclean<3; countclean++){
        CO[countclean] = 0;
        CP[countclean] = 0;
        blank[countclean] = 0;
    }
    classeBranco.blankCalculus();
    classeCO.caCalculus();
    classeCO.cnCalculus();
    classeCO.cpCalculus();
    classeCQ.cqCalculus();
    //return ReadingSamples;
}


QVariantList DadosBrutos::bytesToFloat(QByteArray Samples, int TypeRead){
    QVariantList FloatList;
    union{
        quint32 intValues[2*NUM_POCOS];
        float floatValues[2*NUM_POCOS];
    }PocosValue;
    quint8 aux;
    float aux_L1[NUM_POCOS]; float aux_L2[NUM_POCOS];
    if(TypeRead==0){
        int j = 0;
        for(int i=INIT_PLATES;i<=END_PLATES_L1;i=i+4){
            aux = static_cast<quint8>(Samples[i]);
            PocosValue.intValues[j] = static_cast<quint32>(aux<<24);
            aux = static_cast<quint8>(Samples[i+1]);
            PocosValue.intValues[j] += static_cast<quint32>(aux<<16);
            aux = static_cast<quint8>(Samples[i+2]);
            PocosValue.intValues[j] += static_cast<quint32>(aux<<8);
            aux = static_cast<quint8>(Samples[i+3]);
            PocosValue.intValues[j] += static_cast<quint32>(aux);
            FloatList.append(PocosValue.floatValues[j]);
            if(L1_pocosArray[j].type!="VZ"&&L1_pocosArray[j].type!=""){
                L1_pocosArray[j].value_ABS = PocosValue.floatValues[j];
            }
            if(j<95){
                j = j + 1;
            }else{
                j = 0;
            }}
    }else{
        int j = 0;
        for(int i=INIT_PLATES;i<=END_PLATES_L2;i=i+4){
            aux = static_cast<quint8>(Samples[i]);
            PocosValue.intValues[j] = static_cast<quint32>(aux<<24);
            aux = static_cast<quint8>(Samples[i+1]);
            PocosValue.intValues[j] += static_cast<quint32>(aux<<16);
            aux = static_cast<quint8>(Samples[i+2]);
            PocosValue.intValues[j] += static_cast<quint32>(aux<<8);
            aux = static_cast<quint8>(Samples[i+3]);
            PocosValue.intValues[j] += static_cast<quint32>(aux);
            FloatList.append(PocosValue.floatValues[j]);
            if(j<96){
                if(L1_pocosArray[j].type!="VZ"&&L1_pocosArray[j].type!=""){
                    L1_pocosArray[j].value_ABS = PocosValue.floatValues[j];
                }
                j = j + 1;
            }else if(j<191){
                if(L2_pocosArray[j-96].type!="VZ"&&L1_pocosArray[j-96].type!=""){
                    L2_pocosArray[j-96].value_ABS = PocosValue.floatValues[j];
                }
                j = j + 1;
            }else{
                if(L2_pocosArray[j-96].type!="VZ"&&L1_pocosArray[j-96].type!=""){
                    L2_pocosArray[j-96].value_ABS = PocosValue.floatValues[j];
                }
                L2_pocosArray[j-96].value_ABS = PocosValue.floatValues[j];
                j = 0;
            }
        }
        classeBranco.blankCalculus();
        if(useblank_L12 == true){
            for(int countAux=0; countAux<NUM_POCOS; countAux++){
                aux_L1[countAux] = L1_pocosArray[countAux].value_afterBlank;
                aux_L2[countAux] = L2_pocosArray[countAux].value_afterBlank;
            }
        }else{
            for(int countAux=0; countAux<NUM_POCOS; countAux++){
                aux_L1[countAux] = L1_pocosArray[countAux].value_ABS;
                aux_L2[countAux] = L2_pocosArray[countAux].value_ABS;
            }

        }
        switch(operacao_L12){
        case 0:
            for(int i=0; i<NUM_POCOS; i++){
                L12_pocosArray[i].value_ABS = aux_L1[i] + aux_L2[i];
            }
            break;

        case 1:
            for(int i=0; i<NUM_POCOS; i++){
                if(aux_L1[i]>aux_L2[i]){
                    L12_pocosArray[i].value_ABS = aux_L1[i] - aux_L2[i];
                }else{
                    L12_pocosArray[i].value_ABS = 0;
                }
            }
            break;

        case 2:
            for(int i=0; i<NUM_POCOS; i++){
                if(aux_L2[i]>aux_L1[i]){
                    L12_pocosArray[i].value_ABS = aux_L2[i] - aux_L1[i];
                 }else{
                    L12_pocosArray[i].value_ABS = 0;
                }
            }
            break;

        case 3:
            for(int i=0; i<NUM_POCOS; i++){
                L12_pocosArray[i].value_ABS = aux_L2[i]*aux_L1[i];
            }
            break;

        case 4:
            for(int i=0; i<NUM_POCOS; i++){
                if(aux_L2[i] != 0){
                    L12_pocosArray[i].value_ABS = aux_L1[i]/aux_L2[i];
                 }else{
                    L12_pocosArray[i].value_ABS = 0;
                }
            }
            break;

        case 5:
            for(int i=0; i<NUM_POCOS; i++){
                if(aux_L1[i] != 0){
                    L12_pocosArray[j].value_ABS = aux_L2[i]/aux_L1[i];
                }else{
                    L12_pocosArray[i].value_ABS = 0;
                }
            }
            break;

        }

    }

    return FloatList;
}

QVariantList DadosBrutos::array(){
    return m_array;
}

void DadosBrutos::setarray(QVariantList newarray){
    if(flag==0){
        for(int i=0; i<newarray.size(); i++){
            if(L1_pocosArray[i].type == ""){
                m_array.append("");
            }else{
                m_array.append(newarray[i]);
            }

        }
        flag = 1;
    }else {
        for(int i=0; i<newarray.size(); i++){
            if(L1_pocosArray[i].type == ""){
                m_array[i]="";
            }else{
                m_array[i]=newarray[i];
            }
            }
    }
    emit arrayChanged();
}

QVariantList DadosBrutos::printRawData(int numFiltro){
    QVariantList RawList;
    int i = 0;
    if(numFiltro == 0){
        for(i=0;i<NUM_POCOS;i++){
            RawList.append(L1_pocosArray[i].value_ABS);
        }
    }else if(numFiltro == 1){
        for(i=0;i<NUM_POCOS;i++){
            RawList.append(L2_pocosArray[i].value_ABS);
        }
    }else{
        for(i=0;i<NUM_POCOS;i++){
            RawList.append(L12_pocosArray[i].value_ABS);
        }
    }
    return RawList;
}
