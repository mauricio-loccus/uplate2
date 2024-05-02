#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <protocoloserial.h>
#include <dadosbrutos.h>
#include <calculobranco.h>
#include <exportararquivos.h>
#include <layoutpocos.h>
#include <calculocutoff.h>
#include <calculocq.h>
#include <importararquivos.h>
#include <salvarprotocolo.h>
#include <configfiltros.h>
#include <configpath.h>

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QGuiApplication app(argc, argv);

    ProtocoloSerial protocoloserClass;
    protocoloserClass.configWorker();

    DadosBrutos dadosbrutosClass;
    CalculoBranco calcbrancoClass;
    ExportarArquivos exportClass;
    LayoutPocos layoutClass;
    CalculoCutoff cutoffClass;
    CalculoCQ cqClass;
    ImportarArquivos importClass;
    SalvarProtocolo salvarprotClass;
    ConfigFiltros configfiltClass;
    ConfigPath configpathClass;
    QQmlApplicationEngine engine;
    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
        &app, [url](QObject *obj, const QUrl &objUrl) {
            if (!obj && url == objUrl)
                QCoreApplication::exit(-1);
        }, Qt::QueuedConnection);
    QQmlContext * rootContext = engine.rootContext();
    rootContext->setContextProperty("classSerial", &protocoloserClass);
    rootContext->setContextProperty("classBrutos", &dadosbrutosClass);
    rootContext->setContextProperty("classBranco", &calcbrancoClass);
    rootContext->setContextProperty("classArquivos", &exportClass);
    rootContext->setContextProperty("classLayout", &layoutClass);
    rootContext->setContextProperty("classCutOff", &cutoffClass);
    rootContext->setContextProperty("classCQ", &cqClass);
    rootContext->setContextProperty("classImport", &importClass);
    rootContext->setContextProperty("classSalvarProt", &salvarprotClass);
    rootContext->setContextProperty("classConfigFilt", &configfiltClass);
    rootContext->setContextProperty("classConfigPath", &configpathClass);
    engine.load(url);

    for(int i=0;i<NUM_POCOS;i++){
        L1_pocosArray[i].type= "";
        L1_pocosArray[i].colorWell = "white";
        //L1_pocosArray[i].unique_id = i+1;
        L2_pocosArray[i].type = "";
        L2_pocosArray[i].colorWell = "white";
        //L2_pocosArray[i].unique_id = i+1;
        L12_pocosArray[i].type= "";
        L12_pocosArray[i].colorWell = "white";
        //L12_pocosArray[i].unique_id = i+1;
    }

    for(int i=0; i<8; i++){
        for(int j=0; j<12; j++){
            L1_pocosArray[(12*i+j)].well_id[0] = 65 + i;
            L2_pocosArray[(12*i+j)].well_id[0] = 65 + i;
            L12_pocosArray[(12*i+j)].well_id[0] = 65 + i;
            if(j<9){
                L1_pocosArray[(12*i+j)].well_id[1] = '0';
                L1_pocosArray[(12*i+j)].well_id[2] = 49+j;
                L2_pocosArray[(12*i+j)].well_id[1] = '0';
                L2_pocosArray[(12*i+j)].well_id[2] = 49+j;
                L12_pocosArray[(12*i+j)].well_id[1] = '0';
                L12_pocosArray[(12*i+j)].well_id[2] = 49+j;
            }else{
                L1_pocosArray[(12*i+j)].well_id[1] = '1';
                L1_pocosArray[(12*i+j)].well_id[2] = 49+j-10;
                L2_pocosArray[(12*i+j)].well_id[1] = '1';
                L2_pocosArray[(12*i+j)].well_id[2] = 49+j-10;
                L12_pocosArray[(12*i+j)].well_id[1] = '1';
                L12_pocosArray[(12*i+j)].well_id[2] = 49+j-10;
            }
        }
    }



    return app.exec();
}
