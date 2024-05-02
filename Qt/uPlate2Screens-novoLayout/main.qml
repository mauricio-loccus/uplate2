import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12

Window {
    id:app

    minimumWidth: 1366
    minimumHeight: 768
    title: qsTr("µPlate2")
    color: "#131929"
    //visibility: "FullScreen"
    visible: true

    Component.onDestruction: {
        classSerial.disconnectToPC()
    }
    /*
    maximumHeight: height
    maximumWidth: width

    minimumHeight: height
    minimumWidth: width
    *

    Component.onCompleted: {
        x = Screen.width / 2 - width / 2
        y = Screen.height / 2 - height / 2
    }*/

    /*BarraSuperior{
        id: barraSuperior
    }*/

    Loader{
        id: loaderBarraSuperior
        anchors{

            bottom: loaderLateral.top
            top: parent.top
            right: parent.right
            left: parent.left

        }
        source: "BarraSuperior.qml"
    }

    Loader{
        id: loaderInicio
        x: 100
        y: 100
        width: 256
        height: 256
        source: "MenuInicial.qml"

    }

    Loader{
        id: loaderLateral
        x: 0
        y: 50
        source: "BarraLateral.qml"

    }

    Loader{
        id: loaderLateralDireito
        x: 1100
        y: 50
        property bool visiblePopUp: false
        source: "BarraLateral.qml"
    }


    /*BotoesLaterais{
        id: botoesLaterais

    }
    BarraInferior{
        id: barraInferior
    }*/

    TelaSplash {
        id:splash

        visible: true
        onDoneChanged: {
            splash.visible = false

            app.width = 1024
            app.height = 680

        }
    }

    Popup{
        id: popupLendo
        visible: loaderLateralDireito.visiblePopUp
        enabled: loaderLateralDireito.visiblePopUp
        anchors.centerIn: parent
        width: 250
        height: 250
        closePolicy: Popup.NoAutoClose
        palette.text: "red"
        modal: true
        Text{
            id: textPopUp
            color: "red"
            anchors.centerIn: parent
            text: "Lendo..."
            font.pointSize: 30
        }
        BusyIndicator {
            y: 170
            anchors{
                horizontalCenter: parent.horizontalCenter
            }
            width: 53
            height: 53
            running: loaderLateralDireito.visiblePopUp
        }


    }



}

