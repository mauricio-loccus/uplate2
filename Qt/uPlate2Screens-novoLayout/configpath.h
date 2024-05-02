#ifndef CONFIGPATH_H
#define CONFIGPATH_H

#include <QObject>
#include <QDebug>
#include <QVariantList>
#include <QVariant>
#include <QJsonObject>
#include <QJsonDocument>
#include <QDir>
#include <QTextStream>

extern QString last_path_exp;
extern QString last_path_imp;

class ConfigPath : public QObject
{
    Q_OBJECT
public:
    explicit ConfigPath(QObject *parent = nullptr);

public slots:
    Q_INVOKABLE void salvarConfigPath();
    Q_INVOKABLE void carregarConfigPath();

};

#endif // CONFIGPATH_H
