#ifndef SALVARPROTOCOLO_H
#define SALVARPROTOCOLO_H

#include <QObject>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QCoreApplication>
#include <QDate>

extern struct pocoInfo L1_pocosArray[96];
extern struct pocoInfo L2_pocosArray[96];
extern struct pocoInfo L12_pocosArray[96];

extern uint8_t operacao_L12;
extern uint8_t speed_Read;
extern uint8_t filtro1_Read;
extern uint8_t filtro2_Read;
extern bool useblank_L12;

extern float fcCA[5];
extern bool useblank_CO;
extern QString formulaCO, formulaAux1, formulaAux2;
extern QString interp1[2], interp2[2], interp3[2];

extern QString cq_interp1[2], cq_interp2[2], cq_interp3[2];

extern QString last_path_exp, last_path_imp;
extern uint8_t fileType_exp;
extern uint8_t fileType_imp;
extern uint8_t sep_Decimal, sep_ColExp, sep_ColImp;

class SalvarProtocolo : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString protocolName READ protocolName WRITE setprotocolName NOTIFY protocolNameChanged)
    Q_PROPERTY(QString protocolDate READ protocolDate WRITE setprotocolDate NOTIFY protocolDateChanged)

public:
    explicit SalvarProtocolo(QObject *parent = nullptr);
    Q_INVOKABLE void salvar(QString fileName);
    Q_INVOKABLE void abrir(QString fileName);
    Q_INVOKABLE QString imprimirPath();
    QString protocolName();
    QString protocolDate();

signals:
    void protocolNameChanged();
    void protocolDateChanged();

public slots:
    void setprotocolName(QString);
    void setprotocolDate(QString);

private:
    QString m_protocolName = "Novo protocolo";
    QString m_protocolDate = QDate::currentDate().toString("dd.MM.yyyy");
};

#endif // SALVARPROTOCOLO_H
