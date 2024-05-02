#include "salvarprotocolo.h"
#include "dadosbrutos.h"


SalvarProtocolo::SalvarProtocolo(QObject *parent)
    : QObject{parent}
{

}

/*Nome do Protocolo*/
QString SalvarProtocolo::protocolName(){
    return m_protocolName;
}

void SalvarProtocolo::setprotocolName(QString newprotocolName){
    if(m_protocolName!=newprotocolName){
        m_protocolName = newprotocolName;
        emit protocolNameChanged();
    }
}

/*Data do Protocolo*/

QString SalvarProtocolo::protocolDate(){
    return m_protocolDate;
}

void SalvarProtocolo::setprotocolDate(QString newprotocolDate){
    if(m_protocolDate!=newprotocolDate){
        m_protocolDate = newprotocolDate;
        emit protocolDateChanged();
    }
}
/*Outras funções*/

QString SalvarProtocolo::imprimirPath(){
    QString path;

    path = QDir::current().path() + "/protocolos";
    if(QDir(path).exists() == false){
        QDir().mkdir(path);
    }

    return QUrl::fromLocalFile(path).toString();

}

void SalvarProtocolo::salvar(QString fileName){

    QJsonObject pocosDados[96];
    QJsonObject comandos;
    QJsonObject fc_CA;
    QJsonObject cutoff;
    QJsonObject cq;
    QJsonObject exportar;
    QJsonObject content;

    /*Objetos de comandos:*/
    comandos.insert("data", QDate::currentDate().toString("dd.MM.yyyy"));
    comandos.insert("velocidade", speed_Read);
    comandos.insert("usar branco", useblank_L12);
    comandos.insert("operação", operacao_L12);
    comandos.insert("filtro 1", filtro1_Read);
    comandos.insert("filtro 2", filtro2_Read);
    content.insert("comandos", comandos);

    /*Objetos fatores de calibração*/
    fc_CA.insert("fator calibração 1", fcCA[0]);
    fc_CA.insert("fator calibração 2", fcCA[1]);
    fc_CA.insert("fator calibração 3", fcCA[2]);
    fc_CA.insert("fator calibração 4", fcCA[3]);
    fc_CA.insert("fator calibração 5", fcCA[4]);
    content.insert("fatores calibração", fc_CA);

    /*Objetos cut-off*/
    cutoff.insert("usar branco", useblank_CO);
    cutoff.insert("fórmula CO", formulaCO);
    cutoff.insert("fórmula AUX1", formulaAux1);
    cutoff.insert("fórmula AUX2", formulaAux2);
    cutoff.insert("interpretação 1", interp1[0]);
    cutoff.insert("nome 1", interp1[1]);
    cutoff.insert("interpretação 2", interp2[0]);
    cutoff.insert("nome 2", interp2[1]);
    cutoff.insert("interpretação 3", interp3[0]);
    cutoff.insert("nome 3", interp3[1]);
    content.insert("cut-off", cutoff);

    /*Objetos controle de qualidade*/
    cq.insert("interpretação 1", cq_interp1[0]);
    cq.insert("nome 1", cq_interp1[1]);
    cq.insert("interpretação 2", cq_interp2[0]);
    cq.insert("nome 2", cq_interp2[1]);
    cq.insert("interpretação 3", cq_interp3[0]);
    cq.insert("nome 3", cq_interp3[0]);
    content.insert("controle de qualidade", cq);

    /*Objetos exportação*/
    exportar.insert("tipo arquivo exp", fileType_exp);
    exportar.insert("tipo arquivo imp", fileType_imp);
    exportar.insert("separador decimal", sep_Decimal);
    exportar.insert("separador coluna exp", sep_ColExp);
    exportar.insert("separador coluna imp", sep_ColImp);
    exportar.insert("pasta exportar", last_path_exp);
    exportar.insert("pasta importar", last_path_imp);
    content.insert("exportar", exportar);

    /*Objetos caracteristicas dos poços*/
    for(int i=0; i<96; i++){
        pocosDados[i].insert("tipo", L1_pocosArray[i].type);
        pocosDados[i].insert("unique ID", L1_pocosArray[i].unique_id);
        pocosDados[i].insert("sample ID", L1_pocosArray[i].sample_id);
        pocosDados[i].insert("subject ID", L1_pocosArray[i].subject_id);
        pocosDados[i].insert("replicate ID", L1_pocosArray[i].replicate_id);
        pocosDados[i].insert("color", L1_pocosArray[i].colorWell);
        content.insert( QString(L1_pocosArray[i].well_id), pocosDados[i] );
    }

    QJsonDocument document;
    QString path = QDir::current().path() + "/protocolos";
    if(QDir(path).exists() == false){
        QDir().mkdir(path);
    }
    qDebug() << path;
    path = path + "/" + fileName;
    document.setObject( content );
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    QFile file(path);
    QFile(path).setPermissions(QFileDevice::ReadOther | QFileDevice::WriteOther);
    if( file.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream iStream( &file );
        //iStream.setEncoding( "utf-8" );
        iStream << bytes;
        file.close();
        qDebug() << "fechou";
    }
    else
    {
        qDebug() << "deu errado abrir o arquivo :(";
    }

}

void SalvarProtocolo::abrir(QString fileName){

    QString path;
    if(QSysInfo::productType() == "windows"){
        path = QDir::current().path() + "/protocolos" + fileName;
    }else{
        path = "protocolos" + fileName;
    }
    qDebug() << path;

    QFile file(path);
    if( file.open( QIODevice::ReadWrite ) )
    {
        QByteArray bytes = file.readAll();
        file.close();
        qDebug() << "Debug";

        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
        if( jsonError.error != QJsonParseError::NoError )
        {
            qDebug() << "ERRO ARQUIVO JSON";
            return ;
        }

        if(document.isObject()){
            QJsonObject jsonObj = document.object();

            /*Objetos de comandos:*/
            if(jsonObj.contains("comandos")){
                QJsonObject obj = jsonObj.value("comandos").toObject();
                QStringList keys = obj.keys();
                for(auto key: keys){
                    auto value = obj.take(key);
                    if(key == "velocidade"){
                        speed_Read = value.toInt();
                        qDebug() << key << " : " << value.toInt();
                    }else if(key == "usar branco"){
                        useblank_L12 = value.toBool();
                        qDebug() << key << " : " << value.toBool();
                    }else if(key == "operação"){
                        operacao_L12 = value.toInt();
                        qDebug() << key << " : " << value.toInt();
                    }else if(key == "filtro 1"){
                        filtro1_Read = value.toInt();
                        qDebug() << key << " : " << value.toInt();
                    }else if(key == "filtro 2"){
                        filtro2_Read = value.toInt();
                        qDebug() << key << " : " << value.toInt();
                    }else if(key == "data"){
                        m_protocolDate = value.toString();
                    }
                }
            }

            /*Objetos fatores de calibração*/
            if(jsonObj.contains("fatores calibração")){
                QJsonObject obj = jsonObj.value("fatores calibração").toObject();
                QStringList keys = obj.keys();
                for(auto key: keys){
                    auto value = obj.take(key);
                    if(key == "fator calibração 1"){
                        fcCA[0] = value.toDouble();
                        qDebug() << key << " : " << value.toDouble();
                    }else if(key == "fator calibração 2"){
                        fcCA[1] = value.toDouble();
                        qDebug() << key << " : " << value.toDouble();
                    }else if(key == "fator calibração 3"){
                        fcCA[2] = value.toDouble();
                        qDebug() << key << " : " << value.toDouble();
                    }else if(key == "fator calibração 4"){
                        fcCA[3] = value.toDouble();
                        qDebug() << key << " : " << value.toDouble();
                    }else if(key == "fator calibração 5"){
                        fcCA[4] = value.toDouble();
                        qDebug() << key << " : " << value.toDouble();
                    }
                }
            }

            /*Objetos cut-off*/
            if(jsonObj.contains("cut-off")){
                QJsonObject obj = jsonObj.value("cut-off").toObject();
                QStringList keys = obj.keys();
                for(auto key: keys){
                    auto value = obj.take(key);
                   if(key == "usar branco"){
                       useblank_CO = value.toBool();
                       qDebug() << key << " : " << value.toBool();
                   }else if(key == "fórmula CO"){
                        formulaCO = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "fórmula AUX1"){
                        formulaAux1 = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "fórmula AUX2"){
                        formulaAux2 = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "interpretação 1"){
                        interp1[0] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "nome 1"){
                        interp1[1] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "interpretação 2"){
                        interp2[0] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "nome 2"){
                        interp2[1] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "interpretação 3"){
                        interp3[0] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "nome 3"){
                        interp3[1] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }
                }
            }

            /*Objetos controle de qualidade*/
            if(jsonObj.contains("controle de qualidade")){
                QJsonObject obj = jsonObj.value("controle de qualidade").toObject();
                QStringList keys = obj.keys();
                for(auto key: keys){
                    auto value = obj.take(key);
                    if(key == "interpretação 1"){
                        cq_interp1[0] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "nome 1"){
                        cq_interp1[1] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "interpretação 2"){
                        cq_interp2[0] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "nome 2"){
                        cq_interp2[1] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "interpretação 3"){
                        cq_interp3[0] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "nome 3"){
                        cq_interp3[1] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }
                }
            }

            /*Objetos Exportação*/
            if(jsonObj.contains("exportar")){
                QJsonObject obj = jsonObj.value("exportar").toObject();
                QStringList keys = obj.keys();
                for(auto key: keys){
                    auto value = obj.take(key);
                    if(key == "tipo arquivo exp"){
                        fileType_exp = value.toInt();
                        qDebug() << key << " : " << value.toInt();
                    }else if(key == "tipo arquivo imp"){
                        fileType_imp = value.toInt();
                        qDebug() << key << " : " << value.toInt();
                    }else if(key == "separador decimal"){
                        sep_Decimal = value.toInt();
                        qDebug() << key << " : " << value.toInt();
                    }else if(key == "separador coluna exp"){
                        sep_ColExp = value.toInt();
                        qDebug() << key << " : " << value.toInt();
                    }else if(key == "separador coluna imp"){
                        sep_ColImp = value.toInt();
                        qDebug() << key << " : " << value.toInt();
                    }else if(key == "pasta exportar"){
                        last_path_exp = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "pasta importar"){
                        last_path_imp = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }
                }
            }

            /*Objetos caracteristicas dos poços*/
            for(int i=0; i<96; i++){
                if(jsonObj.contains(QString(L1_pocosArray[i].well_id))){
                    QJsonObject obj = jsonObj.value(QString(L1_pocosArray[i].well_id)).toObject();
                    QStringList keys = obj.keys();
                    for(auto key: keys){
                        auto value = obj.take(key);
                        if(key == "tipo"){
                            L1_pocosArray[i].type = value.toString();
                            qDebug() << key << " : " << value.toString();
                        }else if(key == "unique ID"){
                            L1_pocosArray[i].unique_id = value.toInt();
                            qDebug() << key << " : " << value.toInt();
                        }else if(key == "sample ID"){
                            L1_pocosArray[i].sample_id = value.toString();
                            qDebug() << key << " : " << value.toString();
                        }else if(key == "subject ID"){
                            L1_pocosArray[i].subject_id = value.toString();
                            qDebug() << key << " : " << value.toString();
                        }else if(key == "replicate ID"){
                            L1_pocosArray[i].replicate_id = value.toString();
                            qDebug() << key << " : " << value.toString();
                        }else if(key == "color"){
                            L1_pocosArray[i].colorWell = value.toString();
                            qDebug() << key << " : " << value.toString();
                        }
                    }
                }
            }




        }


    }else{
        qDebug() << "Erro:" << file.errorString();
    }

}
