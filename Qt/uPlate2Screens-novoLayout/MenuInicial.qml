import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {
    id:menuinicial

    /*function gotoResultados() {
        gridMenuInicial.indexAt(4)
    }

    Component.onCompleted: {
        var ports = classSerial.availablePorts()
        if (classSerial.portSelected === "") {
            console.log(ports)
            classSerial.setPortSelected(ports[0].toString())
        }
        console.log(classSerial.portSelected)
    }*/

    Component.onCompleted: {
        classConfigFilt.carregarConfig();
        classConfigPath.carregarConfigPath()
    }

    Text{
        id: textoVersa
        x: 240
        width: 62
        height: 17
        text: "V1.4.8"
        anchors.top: botaoExit.bottom
        font.pixelSize: 12
        horizontalAlignment: Text.AlignHCenter
        verticalAlignment: Text.AlignVCenter
        anchors.topMargin: 23
        color: "#ffffff"

    }

    RoundButton{
     id: botaoUser
     x: 156
     y: 0
     width: 248
     height: 77
     radius: 50
     IconImage{
         id: imagemUser
         y: 12
         width: 48
         height: 53
         anchors{
             left: parent.left
         }
         source: "qrc:/images/user.svg"
         anchors.leftMargin: 20

     }
     Text{
         x: 86
         y: 19

         font.pixelSize: 35
         color: "black"
        text: "Entrar"

     }
     background: Rectangle{
         id: rectangleUser
         radius: botaoUser.radius
         color: "#E6E6FA"
         border.width: 3
         border.color: "#364b7f"
     }
     MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            loaderInicio.source = "TelaExperimentoGeral.qml"
            loaderLateral.source = "BotoesLaterais.qml"
            loaderBarraSuperior.source = "BarraSuperiorExperimento.qml"
            loaderLateralDireito.source = "BotoesConectar.qml"
        }
        onPressed: {
            rectangleUser.border.color = "white"
        }

        onReleased: {
            rectangleUser.border.color = "#364b7f"
        }
    }


}

    RoundButton{
     id: botaoSettings
     x: 156
     y: 150
     width: 326
     height: 77
     radius: 50
     IconImage{
         id: imagemSettings
         y: 12
         width: 48
         height: 53
         anchors{
             left: parent.left
         }
         source: "qrc:/images/settings.svg"
         anchors.leftMargin: 20

     }
     Text{
         x: 82
         y: 19

         font.pixelSize: 35
         color: "black"
        text: "Configurações"

     }
     background: Rectangle{
         id: rectangeSettings
         radius: botaoSettings.radius
         color: "#E6E6FA"
         border.width: 3
         border.color: "#364b7f"
     }
     MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            loaderInicio.source = "TelaConfFiltros.qml"
            loaderLateral.source = "BarraLateral.qml"
            loaderBarraSuperior.source = "BarraSuperiorPadrao.qml"
        }
        onPressed: {
            rectangeSettings.border.color = "white"
        }

        onReleased: {
            rectangeSettings.border.color = "#364b7f"
        }
     }


}

    RoundButton{
     id: botaoExit
     x: 156
     y: 300
     width: 248
     height: 77
     radius: 50
     IconImage{
         id: imagemExit
         y: 12
         width: 48
         height: 53
         anchors{
             left: parent.left
         }
         source: "qrc:/images/exit.svg"
         anchors.leftMargin: 20

     }
     Text{
         x: 82
         y: 19

         font.pixelSize: 35
         color: "black"
        text: "Sair"

     }
     background: Rectangle{
         id: rectangeExit
         radius: botaoExit.radius
         color: "#E6E6FA"
         border.width: 2
         border.color: "#364b7f"
     }
     MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
           app.close()
        }
        onPressed: {
            rectangeExit.border.color = "white"
        }

        onReleased: {
            rectangeExit.border.color = "#364b7f"
        }
    }


}

    /*RoundButton{
     id: botaoMidia
     x: 550
     y: 400
     width: 70
     height: 70
     radius: 10
     IconImage{
         id: imagemMidia
         anchors.fill: parent
         source: "qrc:/images/midia.svg"

     }
     background: Rectangle{
         id: rectangleMidia
         radius: botaoMidia.radius
         color: "#E6E6FA"
         border.width: 2
         border.color: "#364b7f"
     }

    }*/

    /*RoundButton{
     id: botaoTools
     x: 640
     y: 400
     width: 70
     height: 70
     radius: 10
     IconImage{
         id: imagemTools
         anchors.fill: parent
         source: "qrc:/images/tools.svg"

     }
     background: Rectangle{
         id: rectangleTools
         radius: botaoTools.radius
         color: "#E6E6FA"
         border.width: 2
         border.color: "#364b7f"
     }

    }*/



}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
