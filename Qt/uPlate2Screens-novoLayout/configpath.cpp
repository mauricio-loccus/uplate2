#include "configpath.h"

ConfigPath::ConfigPath(QObject *parent)
    : QObject{parent}
{

}


void ConfigPath::salvarConfigPath(){
    QJsonObject content;
    QJsonObject configpath;

    configpath.insert("path import", last_path_imp);
    configpath.insert("path export", last_path_exp);

    content.insert("config. paths", configpath);
    QJsonDocument document;
    QString path = QDir::current().path() + "/paths.json";
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

void ConfigPath::carregarConfigPath(){
    QFile file("paths.json");

    if(!file.exists()){
        qDebug() << "Arquivo não existe ainda!";
        salvarConfigPath();
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
            if(jsonObj.contains("config. paths")){
                QJsonObject obj = jsonObj.value("config. paths").toObject();
                QStringList keys = obj.keys();
                for(auto key: keys){
                    auto value = obj.take(key);
                    if(key == "path import"){
                        last_path_imp = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }else if(key == "path export"){
                        last_path_exp = value.toString();
                        qDebug() << key << " : " << value.toString();
                    }
                }
            }
        }

    }else{
        qDebug() << "Erro ao abrir o arquivo:" << file.errorString();
    }

}
