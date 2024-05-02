#ifndef CALCULOCUTOFF_H
#define CALCULOCUTOFF_H

#include <QObject>
#include <QJSEngine>
#include <QDebug>
#include <QVariantList>
#include <QVariant>


extern struct pocoInfo L1_pocosArray[96];
extern struct pocoInfo L2_pocosArray[96];
extern struct pocoInfo L12_pocosArray[96];

class CalculoCutoff : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList fc_CA READ fc_CA WRITE setfc_CA NOTIFY fc_CAChanged)
    Q_PROPERTY(QVariantList formulas READ formulas WRITE setformulas NOTIFY formulasChanged)
    Q_PROPERTY(QVariantList interp READ interp WRITE setinterp NOTIFY interpChanged)
    Q_PROPERTY(bool useBlank READ useBlank WRITE setUseBlank NOTIFY useBlankChanged)
public:
    explicit CalculoCutoff(QObject *parent = nullptr);
    QVariantList fc_CA();
    QVariantList formulas();
    QVariantList interp();
    bool useBlank();



signals:
    void fc_CAChanged();
    void formulasChanged();
    void interpChanged();
    void useBlankChanged();

public slots:
    //Q_INVOKABLE void cutoffFormula(QString formulaCO);
    Q_INVOKABLE void caCalculus();
    Q_INVOKABLE void cpCalculus();
    Q_INVOKABLE void cnCalculus();
    Q_INVOKABLE void coCalculus();
    Q_INVOKABLE void interpCalculus();
    Q_INVOKABLE QVariantList printInterp(int numFiltros);
    Q_INVOKABLE QVariantList returnfc_CA(int numCA, float input);
    Q_INVOKABLE QVariantList returnFormulas(QString form1, QString form2, QString form3);
    Q_INVOKABLE QVariantList returnInterp(QString form1, QString int1, QString form2, QString int2, QString form3, QString int3);
    Q_INVOKABLE QVariantList printAux1Data(int numFiltro);
    Q_INVOKABLE QVariantList printAux2Data(int numFiltro);
    void setfc_CA(QVariantList);
    void setformulas(QVariantList);
    void setinterp(QVariantList);
    void setUseBlank(bool);
    void zerarCO();

private:
    QVariantList m_fcCA = QList<QVariant>() << 1 << 1 << 1 << 1 << 1;
    QVariantList m_formulas = QList<QVariant>() << "" << "" << "";
    QVariantList m_interp = QList<QVariant>() << "" << "" << "" << "" << "" << "" ;
    bool m_useBlank = true;

};

#endif // CALCULOCUTOFF_H
