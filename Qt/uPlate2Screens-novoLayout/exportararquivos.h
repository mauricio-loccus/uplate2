#ifndef EXPORTARARQUIVOS_H
#define EXPORTARARQUIVOS_H

#include <QObject>
#include <QTextStream>
#include <QFile>
#include <QDir>


extern struct pocoInfo L1_pocosArray[96];
extern struct pocoInfo L2_pocosArray[96];
extern struct pocoInfo L12_pocosArray[96];
extern float blank[3];

class ExportarArquivos : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int fileTypeExp READ fileTypeExp WRITE setfileTypeExp NOTIFY fileTypeExpChanged)
    Q_PROPERTY(int fileTypeImp READ fileTypeImp WRITE setfileTypeImp NOTIFY fileTypeImpChanged)
    Q_PROPERTY(QString lastPathExp READ lastPathExp WRITE setlastPathExp NOTIFY lastPathExpChanged)
    Q_PROPERTY(QString lastPathImp READ lastPathImp WRITE setlastPathImp NOTIFY lastPathImpChanged)
    Q_PROPERTY(int sepDecimal READ sepDecimal WRITE setsepDecimal NOTIFY sepDecimalChanged)
    Q_PROPERTY(int sepColExp READ sepColExp WRITE setsepColExp NOTIFY sepColExpChanged)
    Q_PROPERTY(int sepColImp READ sepColImp WRITE setsepColImp NOTIFY sepColImpChanged)

public:
    explicit ExportarArquivos(QObject *parent = nullptr);
    Q_INVOKABLE void gerarCSVTXT(QString pathName);
    Q_INVOKABLE void gerarXLS(QString pathName);
    QString sepDecimalTroca(float num, char decimal);
    void replicateID();
    QString lastPathExp();
    QString lastPathImp();
    int fileTypeExp();
    int fileTypeImp();
    int sepDecimal();
    int sepColExp();
    int sepColImp();

public slots:
    void setlastPathExp(QString);
    void setlastPathImp(QString);
    void setfileTypeExp(int);
    void setfileTypeImp(int);
    void setsepDecimal(int);
    void setsepColExp(int);
    void setsepColImp(int);

signals:
    void lastPathExpChanged();
    void lastPathImpChanged();
    void fileTypeExpChanged();
    void fileTypeImpChanged();
    void sepDecimalChanged();
    void sepColExpChanged();
    void sepColImpChanged();

private:
    QString m_lastPathExp;
    QString m_lastPathImp;
    int m_fileTypeExp = 0;
    int m_fileTypeImp = 0;
    int m_sepDecimal = 0;
    int m_sepColExp = 0;
    int m_sepColImp = 0;


};

#endif // EXPORTARARQUIVOS_H
