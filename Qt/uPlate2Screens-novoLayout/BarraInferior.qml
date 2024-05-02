import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

import "appState.js"  as AppState

Rectangle{
    id: barraInferior
    anchors{
        left: parent.left
        bottom: parent.bottom
        right: parent.right
    }
    height: 30
    color:"#B0C4DE"

    Text{
        id: textoVersao
        anchors{
            right: parent.right
            bottom: parent.bottom
        }
        text: "1.3.2"
        font.pixelSize: 12
        color: "black"

    }


    Text {
        id: selectedPort
        y: 7
        width: 160
        height: 17
        text: classSerial.portSelected
        anchors.left: parent.left
        anchors.leftMargin: 8
    }

    Image {
        id: image
        x: 0
        y: 0
        width: 38
        height: 30
        source: "qrc:/images/network-config.bmp"
        fillMode: Image.Stretch
        visible: false    }

}
