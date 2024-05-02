import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.1

import "appState.js"  as AppState


Rectangle{

    id: botoesConectar

    property int normal1filter: 15000
    property int normal2filters: 28000
    property int fast1filter: 12000
    property int fast2filters: 21000
    anchors {
        right: parent.right
        //verticalCenter: parent.verticalCenter
    }
    height: 600
    width: 100
    color: "#131929"


    Component.onCompleted: {
        if(AppState.onlinePC()===true){
            imagemConectar.color = "red"
            textConectar.text = "Desconectar"
        }else{
            imagemConectar.color = "green"
            textConectar.text = "Conectar"
        }
        if( classSerial.portSelected !== "") {
           var idx = comboboxPortaSerial.indexOfValue(classSerial.portSelected)
            comboboxPortaSerial.currentIndex = idx
        }
    }

    RoundButton{
     id: botaoConectar
     property int flagConectar: 0
     x: 0
     y: 0
     width: 100
     height: 100
     radius: 5
     IconImage{
         id: imagemConectar
         scale: 0.75
         anchors{
            top: parent.top
            horizontalCenter: parent.horizontalCenter
         }
         source: "qrc:/images/connect.svg"
         anchors.topMargin: -13
         color: "green"
     }
     Text{
        id: textConectar
        text: "Conectar"
        anchors.topMargin: -16
        color: "white"
        font.pointSize: 12
        anchors{
            top: imagemConectar.bottom
            horizontalCenter: parent.horizontalCenter
        }
     }
     background: Rectangle{
         id: rectangleBotaoConectar
         radius: botaoConectar.radius
         color: "#131929"
         border.width: 2
         border.color: "white"}

     MouseArea{
         anchors.fill: parent
         cursorShape: Qt.PointingHandCursor
         onClicked:{
           if(AppState.onlinePC() === false){
               imagemConectar.color = "red"
               textConectar.text = "Desconectar"
               classSerial.setPortSelected(comboboxPortaSerial.currentText)
               classSerial.connectToPC()
               AppState.setOnlinePC(true)
               console.log(AppState.onlinePC())
           }else{
              imagemConectar.color = "green"
               textConectar.text = "Conectar"
               classSerial.disconnectToPC()
               AppState.setOnlinePC(false)
               console.log(AppState.onlinePC())
           }

         }
         onPressed: {
             rectangleBotaoConectar.border.color = "#2DD7EE"
         }
         onReleased: {
             rectangleBotaoConectar.border.color = "white"
         }
     }

  }

    ComboBox{
        id: comboboxPortaSerial
        x: 0
        y: 105
        width: 100
        model: classSerial.availablePorts()
        onActivated: {
            classSerial.setPortSelected(currentText)
        }

     }

    RoundButton{
     id: botaoPlateInOut
     x: 0
     y: 150
     width: 100
     height: 100
     radius: 5
     IconImage{
         id: imagemPlateInOut
         source: "qrc:/images/plateInOut.svg"
         anchors.horizontalCenterOffset: 0
         color: "white"
         scale: 0.75
         anchors{
            top: parent.top
            horizontalCenter: parent.horizontalCenter
         }
        anchors.topMargin: -2
     }
     Text{
        id: textPlateOut
        text: "Ejetar/"
        anchors.horizontalCenterOffset: 1
        anchors.topMargin: -7
        color: "white"
        font.pointSize: 12
        anchors{
            top: imagemPlateInOut.bottom
            horizontalCenter: parent.horizontalCenter
        }
     }
     Text{
        id: textPlateIn
        text: "Recolher"
        anchors.topMargin: 1
        color: "white"
        font.pointSize: 12
        anchors{
            top: textPlateOut.bottom
            horizontalCenter: parent.horizontalCenter
        }
     }
     background: Rectangle{
         id: rectangleBotaoPlateInOut
         radius: botaoPlateInOut.radius
         color: "#131929"
         border.width: 2
         border.color: "white"}

     MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: classSerial.plateInOut()

        onPressed: {
            rectangleBotaoPlateInOut.border.color = "#2DD7EE"
        }
        onReleased: {
            rectangleBotaoPlateInOut.border.color = "white"
        }

     }

    }

    RoundButton{
     id: botaoRandomRead
     x: 0
     y: 300
     width: 100
     height: 100
     radius: 5
     IconImage{
         id: imagemRandomRead
         anchors.fill: parent
         source: "qrc:/images/randomRead.svg"
         anchors.bottomMargin: 8
         color: "white"
         scale: 0.75
         anchors{
            top: parent.top
            horizontalCenter: parent.horizontalCenter
         }
        anchors.topMargin: -21
     }
     Text{
        id: textRandomRead
        text: "Aleatórios"
        anchors.topMargin: -16
        color: "white"
        font.pointSize: 12
        anchors{
            top: imagemRandomRead.bottom
            horizontalCenter: parent.horizontalCenter
        }
     }
     background: Rectangle{
         id: rectangleRandomRead
         radius: botaoRandomRead.radius
         color: "#131929"
         border.width: 2
         border.color: "white"
     }
     MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            classBrutos.genRandomArchive();
        }

        onPressed: {
            rectangleRandomRead.border.color = "#2DD7EE"
        }
        onReleased: {
            rectangleRandomRead.border.color = "white"
        }
     }

    }

    RoundButton{
     id: botaoSamplesRead
     x: 0
     y: 450
     width: 100
     height: 100
     radius: 5
     IconImage{
         id: imagemSamplesRead
         anchors.fill: parent
         source: "qrc:/images/readSamples.svg"
         anchors.horizontalCenterOffset: 0
         anchors.rightMargin: 0
         anchors.bottomMargin: 9
         anchors.leftMargin: 0
         color: "white"
         scale: 0.4
         anchors{
            top: parent.top
            horizontalCenter: parent.horizontalCenter
         }
        anchors.topMargin: -22
     }
     Text{
        id: textSamples
        text: "Ler dados"
        anchors.topMargin: -16
        color: "white"
        font.pointSize: 12
        anchors{
            top: imagemSamplesRead.bottom
            horizontalCenter: parent.horizontalCenter
        }
     }
     background: Rectangle{
         id: rectangleSamplesRead
         radius: botaoSamplesRead.radius
         color: "#131929"
         border.width: 2
         border.color: "white"
     }
     MouseArea{
        anchors.fill: parent
        cursorShape: Qt.PointingHandCursor
        onClicked: {
            classSerial.setParam()
            classSerial.initRead();
            if(classSerial.speed === 0&&classSerial.filtro2===0){
                timerPauseTela.interval = normal1filter
            }else if(classSerial.speed === 0&&classSerial.filtro2!==0){
                timerPauseTela.interval = normal2filters
            }else if(classSerial.speed ===1&&classSerial.filtro2===0){
                timerPauseTela.interval = fast1filter
            }else{
                timerPauseTela.interval = fast2filters
            }
            if(AppState.onlinePC() === true){
                loaderLateralDireito.visiblePopUp = true
                timerPauseTela.start();}
        }

        onPressed: {
            rectangleSamplesRead.border.color = "#2DD7EE"
        }
        onReleased: {
            rectangleSamplesRead.border.color = "white"
        }

     }


    }

    Timer{
        id: timerPauseTela
        interval: 1000
        running: false
        repeat: false
        onTriggered: {
            loaderLateralDireito.visiblePopUp = false
        }

    }



}


