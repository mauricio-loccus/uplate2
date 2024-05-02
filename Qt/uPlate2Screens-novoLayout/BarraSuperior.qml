import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.1

import "appState.js"  as AppState

Rectangle{
    id: barraSuperior
    anchors{
        left: parent.left
        top: parent.top
        right: parent.right
    }
    height: 50
    color: "#131929"


    /*Button{
        id: botaoInicio
        height: 30
        width: 60
        background: Rectangle {
            color: "#4682A0"
            opacity: enabled
            radius: 2
            border.color: "black"
            border.width: 0.5
        }
        anchors{
            left: parent.left
            top: parent.top
        }
        text: "Início"
        onClicked: loaderInicio.source = "MenuInicial.qml"
    }

     Button{
         id: botaoConectar
         height: 30
         width: 100
         background: Rectangle {
             color: "#c0392b"
             opacity: enabled
             radius: 2
             border.color: "black"
             border.width: 0.5
         }
         anchors{
             left: botaoInicio.right
             top: parent.top
         }
         text: "Conectar PC"
         onClicked: {
             classSerial.connectToPC()
             AppState.setOnlinePC(true)

             console.log(AppState.onlinePC())
         }

     }*/




}
