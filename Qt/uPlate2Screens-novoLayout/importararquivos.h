#ifndef IMPORTARARQUIVOS_H
#define IMPORTARARQUIVOS_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QDir>
#include <QDebug>
#include <QStringList>

extern struct pocoInfo L1_pocosArray[96];

class ImportarArquivos : public QObject
{
    Q_OBJECT
public:
    explicit ImportarArquivos(QObject *parent = nullptr);
    Q_INVOKABLE int importarCSVTXT(int sepCol, QString pathName);
    Q_INVOKABLE void paintColorWell();
signals:

};

#endif // IMPORTARARQUIVOS_H
