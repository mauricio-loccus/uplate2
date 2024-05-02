#ifndef DADOSBRUTOS_H
#define DADOSBRUTOS_H

#include <QObject>
#include <QtDebug>
#include <QByteArray>
#include <QRandomGenerator>
#include <QVariantList>

#define INIT_PLATES 32
#define END_PLATES_L1 415
#define END_PLATES_L2 799
#define NUM_POCOS 96

extern uint8_t operacao_L12;
extern bool useblank_L12;
extern uint8_t filtro1_Read;
extern uint8_t filtro2_Read;

extern float CA[15];
extern float CP[15];
extern float CN[15];
extern float CQ[15];
extern float CO[3];
extern float blank[3];

struct pocoInfo{
    char well_id[3];
    int unique_id;
    float value_ABS;
    float value_AUX1;
    float value_AUX2;
    float value_afterBlank;
    QString type;
    QString replicate_id;
    QString sample_id;
    QString subject_id;
    QString string_CO;
    QString string_QC;
    QString colorWell;
};

class DadosBrutos : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList array READ array WRITE setarray NOTIFY arrayChanged)
public:
    explicit DadosBrutos(QObject *parent = nullptr);
    QVariantList array();
    Q_INVOKABLE void genRandomArchive();
    Q_INVOKABLE QVariantList printRawData(int numFiltro);

signals:
    void arrayChanged();

public slots:
    QVariantList bytesToFloat(QByteArray Samples, int TypeRead);
    void setarray(QVariantList);


private:
    QVariantList m_array;

};


#endif // DADOSBRUTOS_H
