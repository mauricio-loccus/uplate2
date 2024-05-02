import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle{

    id: barraSuperiorExperimento
    anchors{
        left: parent.left
        top: parent.top
        right: parent.right
    }
    height: 50
    color: "#131929"

    Rectangle{
        id: rectangleInicio
        width: 80
        height: 40
        radius: 5
        color: "#131929"
        x: 410
        y: 5
        border.width: 2
        border.color: "white"
        Text {
            color: "white"
            text: "Início"
            font.pixelSize: 17
            anchors.centerIn: parent
         }
        MouseArea{
               anchors.fill: parent
               cursorShape: Qt.PointingHandCursor
               onClicked: {
                   loaderInicio.source = "MenuInicial.qml"
                   loaderBarraSuperior.source = "BarraSuperior.qml"
                   loaderLateral.source = "BarraLateral.qml"
                   loaderLateralDireito.source = "BarraLateral.qml"
              }
              onPressed:{
                    rectangleInicio.border.color = "#2DD7EE"
              }
        }

    }

    Rectangle{
        id: rectangleGeral
        width: 80
        height: 40
        radius: 5
        color: "#131929"
        x: 510
        y: 5
        border.width: 2
        border.color: "#2DD7EE"
        Text {
            color: "white"
            text: "Geral"
            font.pixelSize: 17
            anchors.centerIn: parent
         }
        MouseArea{
               anchors.fill: parent
               cursorShape: Qt.PointingHandCursor
               onClicked: {
                   loaderInicio.source = "TelaExperimentoGeral.qml"
                   rectangleGeral.border.color = "#2DD7EE"
                   rectangleCutOff.border.color = "white"
                   rectangleCQ.border.color = "white"
              }
        }

    }

    Rectangle{
        id: rectangleCutOff
        width: 80
        height: 40
        radius: 5
        color: "#131929"
        x: 610
        y: 5
        border.width: 2
        border.color: "white"
        Text {
            color: "white"
            text: "Cut-off"
            font.pixelSize: 17
            anchors.centerIn: parent
         }
        MouseArea{
               anchors.fill: parent
               cursorShape: Qt.PointingHandCursor
               onClicked: {
                   loaderInicio.source = "TelaCutOff.qml"
                   rectangleGeral.border.color = "white"
                   rectangleCutOff.border.color = "#2DD7EE"
                   rectangleCQ.border.color = "white"
              }
        }

    }

    Rectangle{
        id: rectangleCQ
        width: 180
        height: 40
        radius: 5
        color: "#131929"
        x: 710
        y: 5
        border.width: 2
        border.color: "white"
        Text {
            color: "white"
            text: "Controle de Qualidade"
            font.pixelSize: 16
            anchors.centerIn: parent
         }
        MouseArea{
               anchors.fill: parent
               cursorShape: Qt.PointingHandCursor
               onClicked: {
                   loaderInicio.source = "TelaCQ.qml"
                   rectangleGeral.border.color = "white"
                   rectangleCutOff.border.color = "white"
                   rectangleCQ.border.color = "#2DD7EE"
               }
        }

    }


}
