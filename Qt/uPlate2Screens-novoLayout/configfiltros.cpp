#include "configfiltros.h"

ConfigFiltros::ConfigFiltros(QObject *parent)
    : QObject{parent}
{

}

QString comprimentoFiltro[8] = {"405", "450", "492", "630", "", "", "", ""};

/*Comprimento de onda filtros*/

QVariantList ConfigFiltros::configFilt(){
    for(int i=0;i<m_configFilt.size();i++){
        m_configFilt[i] = comprimentoFiltro[i];
    }
    return m_configFilt;
}

void ConfigFiltros::set_configFilt(QVariantList newConfig){
    for(int i=0;i<newConfig.size();i++){
        if(newConfig[i]!=0){
            newConfig[i]=newConfig[i];
        }
    }

    emit configFiltChanged();
}

QVariantList ConfigFiltros::return_configFilt(int filt1, int filt2, int filt3, int filt4, int filt5, int filt6, int filt7, int filt8){
    QVariantList filtrosList;


    comprimentoFiltro[0] = QString::number(filt1);
    comprimentoFiltro[1] = QString::number(filt2);
    comprimentoFiltro[2] = QString::number(filt3);
    comprimentoFiltro[3] = QString::number(filt4);
    comprimentoFiltro[4] = QString::number(filt5);
    comprimentoFiltro[5] = QString::number(filt6);
    comprimentoFiltro[6] = QString::number(filt7);
    comprimentoFiltro[7] = QString::number(filt8);

    for(int i=0; i<8; i++){
        if(comprimentoFiltro[i] ==  "0"){
            comprimentoFiltro[i] = "";
        }
        filtrosList.append(comprimentoFiltro[i]);
    }

    return filtrosList;
}

/* Configurações de filtro salvas */

QVariantList ConfigFiltros::model_configFilt(){
    QVariantList modelConfig;
    for(int i=0;i<8;i++){
        if(comprimentoFiltro[i] != ""){
            modelConfig.append(comprimentoFiltro[i]+"nm");
        }
    }
    return modelConfig;
}

QVariantList ConfigFiltros::model2_configFilt(){
    QVariantList model2Config;
    model2Config.append("Nenhum");
    for(int i=0;i<8;i++){
        if(comprimentoFiltro[i] != ""&&i!=filtro1_Read){
            model2Config.append(comprimentoFiltro[i]+"nm");
        }
    }
    return model2Config;
}

void ConfigFiltros::salvarConfig(){
    QJsonObject content;
    QJsonObject configfiltros;

    configfiltros.insert("filtro 1", comprimentoFiltro[0]);
    configfiltros.insert("filtro 2", comprimentoFiltro[1]);
    configfiltros.insert("filtro 3", comprimentoFiltro[2]);
    configfiltros.insert("filtro 4", comprimentoFiltro[3]);
    configfiltros.insert("filtro 5", comprimentoFiltro[4]);
    configfiltros.insert("filtro 6", comprimentoFiltro[5]);
    configfiltros.insert("filtro 7", comprimentoFiltro[6]);
    configfiltros.insert("filtro 8", comprimentoFiltro[7]);
    content.insert("config. filtros", configfiltros);
    QJsonDocument document;
    QString path = QDir::current().path() + "/filtros.json";
    document.setObject(content);
    QByteArray bytes = document.toJson( QJsonDocument::Indented );
    QFile file(path);
    if( file.open( QIODevice::ReadWrite | QIODevice::Text | QIODevice::Truncate ) )
    {
        QTextStream stream (&file);
        stream << bytes;
        file.close();
        qDebug() << "fechou";
    }else{
        qDebug() << "deu errado abrir o arquivo :(";
    }
}

void ConfigFiltros::carregarConfig(){
    QFile file("filtros.json");

    if(!file.exists()){
        qDebug() << "Arquivo não existe ainda!";
        salvarConfig();
    }

    if(file.open(QIODevice::ReadWrite)){

        QByteArray bytes = file.readAll();
        file.close();
        QJsonParseError jsonError;
        QJsonDocument document = QJsonDocument::fromJson( bytes, &jsonError );
        if( jsonError.error != QJsonParseError::NoError )
        {
            qDebug() << "ERRO ARQUIVO JSON";
            return ;
        }

        if(document.isObject()){
            QJsonObject jsonObj = document.object();
            if(jsonObj.contains("config. filtros")){
                QJsonObject obj = jsonObj.value("config. filtros").toObject();
                QStringList keys = obj.keys();
                for(auto key: keys){
                    auto value = obj.take(key);
                    if(key == "filtro 1"){
                        comprimentoFiltro[0] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "filtro 2"){
                        comprimentoFiltro[1] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "filtro 3"){
                        comprimentoFiltro[2] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "filtro 4"){
                        comprimentoFiltro[3] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "filtro 5"){
                        comprimentoFiltro[4] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "filtro 6"){
                        comprimentoFiltro[5] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "filtro 7"){
                        comprimentoFiltro[6] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "filtro 8"){
                        comprimentoFiltro[7] = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }
                }
            }
        }

    }else{
        qDebug() << "Erro ao abrir o arquivo:" << file.errorString();
    }

}


