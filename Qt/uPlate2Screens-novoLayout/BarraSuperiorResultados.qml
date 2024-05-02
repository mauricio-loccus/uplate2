import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle{

    id: barraSuperiorResultados
    anchors{
        left: parent.left
        top: parent.top
        right: parent.right
    }
    height: 50
    color:"#29cde2"



    Rectangle{
        id: inicio
        width: 80
        height: 40
        radius: 5
        color: "#364b7f"
        x: 300
        y: 5
        Text {
            color: "white"
            text: "Início"
            font.pixelSize: 17
            anchors.centerIn: parent
         }
        MouseArea{
               anchors.fill: parent
               onClicked: {
                   loaderInicio.source = "MenuInicial.qml"
                   loaderBarraSuperior.source = "BarraSuperior.qml"
                   loaderLateral.source = "BarraLateral.qml"
                   loaderLateralDireito.source = "BarraLateral.qml"
              }
        }
    }

    Rectangle{
        width: 80
        height: 40
        radius: 5
        color: "#364b7f"
        x: 400
        y: 5
        Text {
            color: "white"
            text: "ABS"
            font.pixelSize: 17
            anchors.centerIn: parent
         }
        MouseArea{
            anchors.fill: parent
            onClicked: {
                classBrutos.setarray(classBrutos.printRawData(itemTelaResultados1.filtronum))
                textType = true
                showHidePocos(true)

              }
        }
    }

    Rectangle{
        width: 80
        height: 40
        radius: 5
        color: "#364b7f"
        x: 500
        y: 5
        Text {
            color: "white"
            text: "Branco"
            font.pixelSize: 17
            anchors.centerIn: parent
         }

    }

    Rectangle{
        width: 80
        height: 40
        radius: 5
        color: "#364b7f"
        x: 600
        y: 5
        Text {
            color: "white"
            text: "Cut-off"
            font.pixelSize: 16
            anchors.centerIn: parent
         }

    }

    Rectangle{
        width: 80
        height: 40
        radius: 5
        color: "#364b7f"
        x: 700
        y: 5
        Text {
            color: "white"
            text: "CQ"
            font.pixelSize: 16
            anchors.centerIn: parent
         }

    }



}
