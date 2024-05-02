#ifndef PROTOCOLOSERIAL_H
#define PROTOCOLOSERIAL_H

#include <QObject>
#include <QDebug>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QVariant>
#include <QByteArray>
#include <QThread>
#include <QUrl>

class Worker : public QSerialPort
{
    Q_OBJECT

signals:
    void valueReady(QByteArray data);



public slots:
    void getData();
    void setPort();
    void closePort();
    void writeByteArray(QByteArray data, int type);

private:
    int m_type;
    QByteArray m_buffer;


};


class ProtocoloSerial : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString portSelected READ portSelected WRITE setPortSelected NOTIFY portSelectedChanged)
    Q_PROPERTY(int speed READ speed WRITE setSpeed NOTIFY speedChanged)
    Q_PROPERTY(int filtro1 READ filtro1 WRITE setFiltro1 NOTIFY filtro1Changed)
    Q_PROPERTY(int filtro2 READ filtro2 WRITE setFiltro2 NOTIFY filtro2Changed)
    Q_PROPERTY(int operacaoL12 READ operacaoL12 WRITE setOperacaoL12 NOTIFY operacaoL12Changed)
    Q_PROPERTY(bool useblankL12 READ useblankL12 WRITE setUseblankL12 NOTIFY useblankL12Changed)

public:
    explicit ProtocoloSerial(QObject *parent = nullptr);
    Q_INVOKABLE QVariant availablePorts();
    Q_INVOKABLE void connectToPC();
    Q_INVOKABLE void disconnectToPC();
    Q_INVOKABLE void initRead();
    Q_INVOKABLE void setParam();
    Q_INVOKABLE void plateInOut();
    Q_INVOKABLE void alertRead(QByteArray data);
    QString portSelected();
    int speed();
    int filtro1();
    int filtro2();
    int operacaoL12();
    bool useblankL12();


    // Q_PROPERTY(bool pocoStatus READ getPocoStatus NOTIFY pocoStatusChanged )
    //Q_INVOKABLE void alertRead();

    ~ProtocoloSerial();

    void configWorker();
    bool getPocoStatus();
    QThread workerThread;

signals:
    void setPort();
    void closePort();
    void writeCommand(QByteArray data, int type);
    void pocoStatusChanged();
    void portSelectedChanged();
    void speedChanged();
    void filtro1Changed();
    void filtro2Changed();
    void operacaoL12Changed();
    void useblankL12Changed();

public slots:
    void setPortSelected(QString);
    void setSpeed(int);
    void setFiltro1(int);
    void setFiltro2(int);
    void setOperacaoL12(int);
    void setUseblankL12(bool);

private:
    bool m_pocoStatus = false;
    QString m_portSelected;
    int m_speed = 0;
    int m_filtro1 = 0;
    int m_filtro2 = 0;
    int m_operacaoL12 = 0;
    bool m_useblankL12 = false;

};

#endif // PROTOCOLOSERIAL_H
