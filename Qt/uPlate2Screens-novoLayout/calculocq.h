#ifndef CALCULOCQ_H
#define CALCULOCQ_H

#include <QObject>
#include <QJSEngine>
#include <QDebug>
#include <QVariantList>
#include <QVariant>

extern float CA[15];
extern float CP[15];
extern float CN[15];
extern float fcCA[5];
extern float CO[3];
extern float blank[3];
extern struct pocoInfo L1_pocosArray[96];
extern struct pocoInfo L2_pocosArray[96];
extern struct pocoInfo L12_pocosArray[96];

class CalculoCQ : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList interp READ interp WRITE setinterp NOTIFY interpChanged)
    Q_PROPERTY(QString cqResult READ cqResult WRITE setcqResult NOTIFY cqResultChanged)

public:
    explicit CalculoCQ(QObject *parent = nullptr);
    QVariantList interp();
    QString cqResult();

signals:
    void interpChanged();
    void cqResultChanged();


public slots:
    Q_INVOKABLE void cqCalculus();
    Q_INVOKABLE QString interpCalculus(int numFiltro);
    Q_INVOKABLE QVariantList returnInterp(QString form1, QString int1, QString form2, QString int2, QString form3, QString int3);
    void setinterp(QVariantList);
    void setcqResult(QString);


private:
    QVariantList m_interp = QList<QVariant>() << "" << "" << "" << "" << "" << "" ;
    QString m_cqResult = "";
};

#endif // CALCULOCQ_H
