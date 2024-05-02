#ifndef CALCULOBRANCO_H
#define CALCULOBRANCO_H

#include <QObject>
#include <QVariantList>


extern struct pocoInfo L1_pocosArray[96];
extern struct pocoInfo L2_pocosArray[96];
extern struct pocoInfo L12_pocosArray[96];

class CalculoBranco : public QObject
{
    Q_OBJECT
public:
    explicit CalculoBranco(QObject *parent = nullptr);
    Q_INVOKABLE void blankCalculus();
    Q_INVOKABLE QVariantList printBlankData(int numFiltro);

signals:

};

#endif // CALCULOBRANCO_H
