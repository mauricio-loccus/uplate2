#ifndef PATHSCONFIG_H
#define PATHSCONFIG_H

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

class PathsConfig : public QObject
{
     Q_OBJECT
public:
    explicit PathsConfig(QObject *parent = nullptr);

public slots:
    Q_INVOKABLE void salvarConfig();
    Q_INVOKABLE void carregarConfig();
};

#endif // PATHSCONFIG_H
