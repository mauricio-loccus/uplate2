#ifndef CONFIGFILTROS_H
#define CONFIGFILTROS_H

#include <QObject>
#include <QDebug>
#include <QVariantList>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QTextStream>

extern uint8_t filtro1_Read;
extern uint8_t filtro2_Read;

class ConfigFiltros : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QVariantList configFilt READ configFilt WRITE set_configFilt NOTIFY configFiltChanged)
public:
    explicit ConfigFiltros(QObject *parent = nullptr);
    QVariantList configFilt();

signals:
    void configFiltChanged();

public slots:
    Q_INVOKABLE QVariantList return_configFilt(int filt1, int filt2, int filt3, int filt4, int filt5, int filt6, int filt7, int filt8);
    Q_INVOKABLE QVariantList model_configFilt();
    Q_INVOKABLE QVariantList model2_configFilt();
    Q_INVOKABLE void salvarConfig();
    Q_INVOKABLE void carregarConfig();
    void set_configFilt(QVariantList);

private:
     QVariantList m_configFilt = QList<QVariant>() << "405" << "450" << "492" << "630" << "" << "" << "" << "";
};

#endif // CONFIGFILTROS_H
