#ifndef LAYOUTPOCOS_H
#define LAYOUTPOCOS_H

#include <QObject>
#include <QtDebug>
#include <QByteArray>
#include <QVariantList>
#include <QVariant>

extern struct pocoInfo L1_pocosArray[96];
extern struct pocoInfo L2_pocosArray[96];
extern struct pocoInfo L12_pocosArray[96];

class LayoutPocos : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList typeArr READ typeArr WRITE settypeArr NOTIFY typeArrChanged)
    Q_PROPERTY(QVariant uniqueID READ uniqueID WRITE setuniqueID NOTIFY uniqueIDChanged)
    Q_PROPERTY(QVariant wellID READ wellID WRITE setwellID NOTIFY wellIDChanged)
    Q_PROPERTY(QVariantList sampleID READ sampleID WRITE setsampleID NOTIFY sampleIDChanged)
    Q_PROPERTY(QVariantList subjID READ subjID WRITE setsubjID NOTIFY subjIDChanged)
    Q_PROPERTY(QVariantList colorWell READ colorWell WRITE setcolorWell NOTIFY colorWellChanged)
public:
    explicit LayoutPocos(QObject *parent = nullptr);
    QVariantList typeArr();
    QVariant uniqueID();
    QVariant wellID();
    QVariantList sampleID();
    QVariantList subjID();
    QVariantList colorWell();

signals:
    void typeArrChanged();
    void uniqueIDChanged();
    void wellIDChanged();
    void sampleIDChanged();
    void subjIDChanged();
    void colorWellChanged();

public slots:
    Q_INVOKABLE QVariantList setPocoType(int numPoco, QString typePoco);
    Q_INVOKABLE QVariant returnUniqueID(int numPoco);
    Q_INVOKABLE QVariant returnWellID(int numPoco);
    Q_INVOKABLE QVariantList returnSampleID(int numPoco, QString input);
    Q_INVOKABLE QVariantList returnSubjID(int numPoco,  QString input);
    Q_INVOKABLE QVariantList returnColorWell(int numPoco,  QString input);
    void settypeArr(QVariantList);
    void setuniqueID(QVariant);
    void setwellID(QVariant);
    void setsampleID(QVariantList);
    void setsubjID(QVariantList);
    void setcolorWell(QVariantList);

private:
    QVariantList m_typeArr;
    QVariant m_uniqueID;
    QVariant m_wellID;
    QVariantList m_sampleID;
    QVariantList m_subjID;
    QVariantList m_colorWell;
};

#endif // LAYOUTPOCOS_H
