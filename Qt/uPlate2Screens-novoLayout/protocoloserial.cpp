#include "protocoloserial.h"
#include "dadosbrutos.h"
#include "calculobranco.h"
#include "calculocutoff.h"
#include "calculocq.h"

enum COMMANDS_TYPE {
    CONNECT,
    DISCONECT,
    PLATEINOUT,
    READ_FILTER1,
    SETPARAM
}commands;

#define NUM_POCOS1 418
#define NUM_POCOS12 802


ProtocoloSerial::ProtocoloSerial(QObject *parent)
    : QObject{parent}
{

}

DadosBrutos classBrutos;
CalculoBranco classBranco;
CalculoCutoff classCO;
CalculoCQ classCQ;

uint8_t flag_read = 0;
uint8_t operacao_L12;
uint8_t speed_Read;
uint8_t filtro1_Read;
uint8_t filtro2_Read;
QString port_Selected;
bool useblank_L12;

/*Porta selecionada*/

QString ProtocoloSerial::portSelected(){
    return m_portSelected;
}

void ProtocoloSerial::setPortSelected(QString newPort){
    if(newPort != m_portSelected){
        m_portSelected = newPort;
        port_Selected = newPort;
        emit portSelectedChanged();
    }
}

/*Velocidade Leitura*/

int ProtocoloSerial::speed(){
    m_speed = speed_Read;
    return m_speed;
}

void ProtocoloSerial::setSpeed(int newSpeed){
    if(newSpeed != m_speed){
        m_speed = newSpeed;
        speed_Read = newSpeed;
        emit speedChanged();
    }
}



/*Filtro 1*/

int ProtocoloSerial::filtro1(){
    m_filtro1 = filtro1_Read;
    return m_filtro1;
}

void ProtocoloSerial::setFiltro1(int newFiltro1){
    if(newFiltro1 != m_filtro1){
        m_filtro1 = newFiltro1;
        filtro1_Read = newFiltro1;
        emit filtro1Changed();
    }
}

/*Filtro 2*/

int ProtocoloSerial::filtro2(){
    m_filtro2 = filtro2_Read;
    return m_filtro2;
}

void ProtocoloSerial::setFiltro2(int newFiltro2){
    if(newFiltro2 != m_filtro2){
        m_filtro2 = newFiltro2;
        filtro2_Read = newFiltro2;
        emit filtro2Changed();
    }
}

/*Operação L12*/

int ProtocoloSerial::operacaoL12(){
    m_operacaoL12 = operacao_L12;
    return m_operacaoL12;
}

void ProtocoloSerial::setOperacaoL12(int newOperacaoL12){
    if(newOperacaoL12 != m_operacaoL12){
        m_operacaoL12 = newOperacaoL12;
        operacao_L12 = newOperacaoL12;
        emit operacaoL12Changed();
    }
}

/*Usar branco L12*/

bool ProtocoloSerial::useblankL12(){
    m_useblankL12 = useblank_L12;
    return m_useblankL12;
}

void ProtocoloSerial::setUseblankL12(bool newUseblankL12){
    if(newUseblankL12 != m_useblankL12){
        m_useblankL12 = newUseblankL12;
        useblank_L12 = newUseblankL12;
        emit useblankL12Changed();
    }
}

/*PROTOCOLO SERIAL*/
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

QVariant ProtocoloSerial::availablePorts(){
    QList<QSerialPortInfo> portsAvailable = QSerialPortInfo::availablePorts();
    QStringList names_PortsAvailable;
    for(const QSerialPortInfo& portInfo : portsAvailable) {
        names_PortsAvailable<<portInfo.portName();
    }

    return QVariant::fromValue(names_PortsAvailable);

}


void Worker::setPort() {
    setPortName(port_Selected);
    setBaudRate(QSerialPort::Baud115200);
    setDataBits(QSerialPort::Data8);
    setStopBits(QSerialPort::OneStop);
    setFlowControl(QSerialPort::NoFlowControl);
    setParity(QSerialPort::NoParity);
    setReadBufferSize(1000);
    open(QIODevice::ReadWrite);
}

void Worker::closePort() {
    close();
}

void Worker::getData() {

    m_buffer.append(readAll());

    switch (m_type) {

    case COMMANDS_TYPE::READ_FILTER1:

        if(m_buffer.size() == 470) {
            qDebug() << "LEITURA - FITRO 1";
            m_buffer = m_buffer.last(NUM_POCOS1);
            emit valueReady(m_buffer);
            m_buffer.clear();
        }

         if(m_buffer.size() == 854) {
            qDebug() << "LEITURA - FITRO 1 e 2";
            m_buffer = m_buffer.last(NUM_POCOS12);
            emit valueReady(m_buffer);
            m_buffer.clear();
        }

        break;

    default:
        qDebug() << "envio de dados size:" << m_buffer.size();
        break;
    }

}

void Worker::writeByteArray(QByteArray data, int type) {
    m_type = type;
    m_buffer.clear();
    write(data);
}

ProtocoloSerial::~ProtocoloSerial() {
    workerThread.exit();
}

bool ProtocoloSerial::getPocoStatus() {
    return m_pocoStatus;
}

void ProtocoloSerial::configWorker() {

    Worker *worker = new Worker();
    worker->moveToThread(&workerThread);

    connect(worker, &Worker::readyRead, worker,&Worker::getData);
    connect(worker, &Worker::valueReady, this, &ProtocoloSerial::alertRead);
    connect(this, &ProtocoloSerial::writeCommand, worker, &Worker::writeByteArray);
    connect(this, &ProtocoloSerial::setPort, worker, &Worker::setPort);
    connect(this, &ProtocoloSerial::closePort, worker, &Worker::closePort);
    workerThread.start();

}

void ProtocoloSerial::connectToPC(){
    QByteArray command = QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00\x00\x01\x00\x00\x00\x02\x04\x61");
    emit setPort();
    emit writeCommand(command, COMMANDS_TYPE::CONNECT);
    qDebug() << "Connected";
}

void ProtocoloSerial::disconnectToPC(){
    QByteArray command = QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00\x00\x02\x00\x00\x00\x02\x04\x62");
    //    serial.write(command);
    emit writeCommand(command, COMMANDS_TYPE::DISCONECT);
    QThread::msleep(5);
    emit closePort();
    qDebug() << "Disconnected";
}

void ProtocoloSerial::plateInOut(){
    QByteArray command = QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00\x00\x06\x00\x00\x00\x02\x04\x66");
    //serial.write(command);
    emit writeCommand(command, COMMANDS_TYPE::PLATEINOUT);
    qDebug() << "Plate in/out";
}

void ProtocoloSerial::initRead(){
    QByteArray command = QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00\x00\x03\x00\x00\x00\x06\x00\x00\x00\x01\x04\x68");
    qDebug() << "Inicia a Leitura";
    m_pocoStatus = false;
    emit writeCommand(command, COMMANDS_TYPE::READ_FILTER1);
}

void ProtocoloSerial::setParam(){
    QByteArray command = QByteArrayLiteral("\xFA\xFB\xFC\xFD\x00\x00\x00\x00\x00\x00\x00\x00\x70\x00\x00");
    QByteArray CRC;
    command.resize(53);

    for(int i=15; i<53; i++){
        command[i] = 0;}
    command[15] = 0x8;
    command[19] = 0x23;
    command[23] = 0x1;
    command[47] = 0x1;
    command[35] = speed_Read;
    command[27] = (filtro1_Read+1);

    if(filtro2_Read>0){
        if(filtro2_Read >= filtro1_Read){
            command[31] = (filtro2_Read + 1);
        }else{
             command[31] = filtro2_Read;
        }
    }

    CRC = checksum(command);

    command = command+CRC;
    qDebug() << "Parametros enviados:";
    qDebug() << command.toHex();
    emit writeCommand(command, COMMANDS_TYPE::SETPARAM);

}

void ProtocoloSerial::alertRead(QByteArray data){

    qDebug() << "AlertRead:" << data;
    qDebug() << "AlertRead:" << data.size();

    if(data.size() == NUM_POCOS1){
        classBrutos.bytesToFloat(data, 0);
        classBranco.blankCalculus();
        classCO.caCalculus();
        classCO.cnCalculus();
        classCO.cpCalculus();
        classCQ.cqCalculus();

        m_pocoStatus = true;
        emit pocoStatusChanged();

    }else if(data.size() == NUM_POCOS12){
        classBrutos.bytesToFloat(data, 1);
        classBranco.blankCalculus();
        classCO.caCalculus();
        classCO.cnCalculus();
        classCO.cpCalculus();
        classCQ.cqCalculus();

        m_pocoStatus = true;
        emit pocoStatusChanged();
    }
}
