import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12

Rectangle{

    id: barraSuperiorPadrao
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
        border.width: 2
        border.color: "white"
        anchors{
            horizontalCenter: parent.horizontalCenter
        }
        y: 5
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


}
