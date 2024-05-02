import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {

    Component.onDestruction: {
        classCQ.setinterp(classCQ.returnInterp(textfieldFormulaInt1CQ.text, textfieldString1.text, textfieldFormulaInt2CQ.text, textfieldString2.text, textfieldFormulaInt3CQ.text, textfieldString3.text))
    }


    GridLayout{
        id: tecladoCQTipos
        x: 500
        y: 1
        property string tipoAtualCQ
        property var tipos1 : ["CA", "CP", "CN"]
        property var tipos2 : ["CQ", "CO", "BC"]
        columns: 3
        rows: 2
        Repeater{
            model: tecladoCQTipos.tipos1
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "black"
                   text: modelData
                   font.pixelSize: 20
              }
              Layout.minimumWidth: 50
              Layout.minimumHeight: 50
               radius: 20
               palette {
                   button: "#ebdef0"
               }
               MouseArea{
                   anchors.fill: parent
                   cursorShape: Qt.PointingHandCursor
                   onClicked:{
                       tecladoCQTipos.tipoAtualCQ = modelData
                       popupTelaCQ.open()
                   }
               }

           }
        }
        Repeater{
            model: tecladoCQTipos.tipos2
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "black"
                   text: modelData
                   font.pixelSize: 20
              }
              Layout.minimumWidth: 50
              Layout.minimumHeight: 50
               radius: 20
               palette {
                   button: "#ebdef0"
               }
               MouseArea{
                   anchors.fill: parent
                   cursorShape: Qt.PointingHandCursor
                   onClicked:{

                       if(modelData !== "CQ"){
                           if(tecladoCQ.numformula == 0){
                               textfieldFormulaInt1CQ.text += modelData
                           }else if(tecladoCQ.numformula == 1){
                               textfieldFormulaInt2CQ.text += modelData
                           }else if(tecladoCQ.numformula == 2){
                               textfieldFormulaInt3CQ.text += modelData
                           }

                       }else{
                            tecladoCQTipos.tipoAtualCQ = modelData
                            popupTelaCQ.open()

                       }

                   }
               }

           }
        }

    }

    Popup{
        x: 600
        y: 1
        id: popupTelaCQ
        parent: Overlay.overlay
        PopupTelaCQ{

        }

    }
    GridLayout {
        id: tecladoCQ
        x: 700
        y: 1
        height: 100
        width: 100
        Layout.fillWidth: false
        Layout.fillHeight: false
        property var nums1: ["7", "8", "9"]
        property var nums2: ["4", "5", "6"]
        property var nums3: ["1", "2", "3"]
        property var nums4: ["0", "."]
        property var operacoes1 : ["-", "x", "÷"]
        property var operacoes2 : ["^", ">", "<"]
        property var operacoes3 : ["E", "OU", "≠"]
        property var operacoes4 : ["=", "(", ")"]
        property int numformula: 0
        columns: 3
        rows: 4

        Repeater{
            model: tecladoCQ.nums1
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 20
              }
              Layout.minimumWidth: 50
              Layout.minimumHeight: 50
               radius: 10
               palette {
                   button: "#1a5276"
               }
               MouseArea{
                   anchors.fill: parent
                   cursorShape: Qt.PointingHandCursor
                   onClicked:{
                       if(tecladoCQ.numformula == 0){
                           textfieldFormulaInt1CQ.text += modelData
                       }else if(tecladoCQ.numformula == 1){
                           textfieldFormulaInt2CQ.text += modelData
                       }else if(tecladoCQ.numformula == 2){
                           textfieldFormulaInt3CQ.text += modelData
                       }

                   }
               }

           }
        }

        Repeater{
            Layout.fillWidth: false
            Layout.fillHeight: false
            model: tecladoCQ.nums2
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 20
              }
               Layout.minimumWidth: 50
               Layout.minimumHeight: 50
               radius: 10
               palette {
                   button: "#1a5276"
               }
               MouseArea{
                   anchors.fill: parent
                   cursorShape: Qt.PointingHandCursor
                   onClicked:{
                       if(tecladoCQ.numformula == 0){
                           textfieldFormulaInt1CQ.text += modelData
                       }else if(tecladoCQ.numformula == 1){
                           textfieldFormulaInt2CQ.text += modelData
                       }else if(tecladoCQ.numformula == 2){
                           textfieldFormulaInt3CQ.text += modelData
                       }
                   }
               }

           }
        }

        Repeater{

            model: tecladoCQ.nums3
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 20
              }
               Layout.minimumWidth: 50
               Layout.minimumHeight: 50
               radius: 10
               palette {
                   button: "#1a5276"
               }
               MouseArea{
                   anchors.fill: parent
                   cursorShape: Qt.PointingHandCursor
                   onClicked:{
                       if(tecladoCQ.numformula == 0){
                           textfieldFormulaInt1CQ.text += modelData
                       }else if(tecladoCQ.numformula == 1){
                           textfieldFormulaInt2CQ.text += modelData
                       }else if(tecladoCQ.numformula == 2){
                           textfieldFormulaInt3CQ.text += modelData
                       }
                   }
               }

           }
        }

        Repeater{

            model: tecladoCQ.nums4
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 20
              }
               Layout.minimumWidth: 50
               Layout.minimumHeight: 50
               radius: 10
               palette {
                   button: "#1a5276"
               }
               MouseArea{
                   anchors.fill: parent
                   cursorShape: Qt.PointingHandCursor
                   onClicked:{
                       if(tecladoCQ.numformula == 0){
                           textfieldFormulaInt1CQ.text += modelData
                       }else if(tecladoCQ.numformula == 1){
                           textfieldFormulaInt2CQ.text += modelData
                       }else if(tecladoCQ.numformula == 2){
                           textfieldFormulaInt3CQ.text += modelData
                       }
                   }
               }

           }
        }

        RoundButton{
            Text{
               anchors.centerIn: parent
               color: "white"
               text: "+"
               font.pixelSize: 20
          }
           Layout.minimumWidth: 50
           Layout.minimumHeight: 50
           radius: 10
           palette {
               button: "#c0392b"
           }
           MouseArea{
               anchors.fill: parent
               cursorShape: Qt.PointingHandCursor
               onClicked:{
                   if(tecladoCQ.numformula == 0){
                       textfieldFormulaInt1CQ.text += "+"
                   }else if(tecladoCQ.numformula == 1){
                       textfieldFormulaInt2CQ.text += "+"
                   }else if(tecladoCQ.numformula == 2){
                       textfieldFormulaInt3CQ.text += "+"
                   }
               }
           }

       }
        Repeater{
            model: tecladoCQ.operacoes1
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 20
              }
              Layout.minimumWidth: 50
              Layout.minimumHeight: 50
               radius: 10
               palette {
                   button: "#c0392b"
               }
               MouseArea{
                   anchors.fill: parent
                   cursorShape: Qt.PointingHandCursor
                   onClicked:{
                       if(tecladoCQ.numformula == 0){
                           textfieldFormulaInt1CQ.text += modelData
                       }else if(tecladoCQ.numformula == 1){
                           textfieldFormulaInt2CQ.text += modelData
                       }else if(tecladoCQ.numformula == 2){
                           textfieldFormulaInt3CQ.text += modelData
                       }
                   }
               }

           }
        }

        Repeater{
            model: tecladoCQ.operacoes2
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 20
              }
              Layout.minimumWidth: 50
              Layout.minimumHeight: 50
               radius: 10
               palette {
                   button: "#c0392b"
               }
               MouseArea{
                   anchors.fill: parent
                   cursorShape: Qt.PointingHandCursor
                   onClicked:{
                       if(tecladoCQ.numformula == 0){
                           textfieldFormulaInt1CQ.text += modelData
                       }else if(tecladoCQ.numformula == 1){
                           textfieldFormulaInt2CQ.text += modelData
                       }else if(tecladoCQ.numformula == 2){
                           textfieldFormulaInt3CQ.text += modelData
                       }
                   }
               }

           }
        }

        Repeater{
            model: tecladoCQ.operacoes3
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 20
              }
              Layout.minimumWidth: 50
              Layout.minimumHeight: 50
               radius: 10
               palette {
                   button: "#c0392b"
               }
               MouseArea{
                   anchors.fill: parent
                   cursorShape: Qt.PointingHandCursor
                   onClicked:{
                       if(tecladoCQ.numformula == 0){
                           textfieldFormulaInt1CQ.text += modelData
                       }else if(tecladoCQ.numformula == 1){
                           textfieldFormulaInt2CQ.text += modelData
                       }else if(tecladoCQ.numformula == 2){
                           textfieldFormulaInt3CQ.text += modelData
                       }
                   }
               }

           }
        }

        Repeater{
            model: tecladoCQ.operacoes4
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 20
              }
              Layout.minimumWidth: 50
              Layout.minimumHeight: 50
               radius: 10
               palette {
                   button: "#c0392b"
               }
               MouseArea{
                   anchors.fill: parent
                   cursorShape: Qt.PointingHandCursor
                   onClicked:{
                       if(tecladoCQ.numformula == 0){
                           textfieldFormulaInt1CQ.text += modelData
                       }else if(tecladoCQ.numformula == 1){
                           textfieldFormulaInt2CQ.text += modelData
                       }else if(tecladoCQ.numformula == 2){
                           textfieldFormulaInt3CQ.text += modelData
                       }
                   }
               }

           }
        }

    }

    RoundButton{
        x: 730
      anchors{
        top: tecladoCQ.bottom
        right: tecladoCQ.right

      }
      Text{
           anchors.centerIn: parent
           color: "black"
           text: "LIMPAR"
           font.pixelSize: 20
      }

      width: 160
      height: 50
      radius: 10
      anchors.rightMargin: -60
      anchors.topMargin: 393
      palette {
           button: "#EEDD82"
       }
      MouseArea{
          anchors.fill: parent
          cursorShape: Qt.PointingHandCursor
          onClicked:{
              if(tecladoCQ.numformula == 0){
                  textfieldFormulaInt1CQ.text = ""
              }else if(tecladoCQ.numformula == 1){
                  textfieldFormulaInt2CQ.text = ""
              }else if(tecladoCQ.numformula == 2){
                  textfieldFormulaInt3CQ.text = ""
              }
          }
      }

   }
    TextField {
            id: textfieldFormulaInt1CQ
            x: 50
            y: 130
            width: 307
            height: 30
            maximumLength: 100
            font.pointSize: 15
            placeholderText: qsTr("Digite a fórmula")
            text: classCQ.interp[0]
            onActiveFocusChanged: {
                tecladoCQ.numformula = 0
            }

        }
    Text{
            id: textFormulaInt1
            anchors{
                left: textfieldFormulaInt1CQ.left
                bottom: textfieldFormulaInt1CQ.top
            }
            text: "Fórmula Interpretação 1"
            font.pixelSize: 17
            color: "white"
        }

        Text{
            id: textEntao1
            anchors{
                top: textfieldFormulaInt1CQ.top
            }
            x: 375
            text: "então"
            font.pixelSize: 17
            anchors.topMargin: 0
            color: "white"
        }

        Text{
            id: textSe1
            anchors{
                top: textfieldFormulaInt1CQ.top
            }
            x: 22
            text: "se"
            font.pixelSize: 17
            color: "white"
        }

        TextField {
            id: textfieldFormulaInt2CQ
            x: 50
            y: 230
            width: 307
            height: 30
            maximumLength: 100
            font.pointSize: 15
            placeholderText: qsTr("Digite a fórmula")
            text: classCQ.interp[2]
            onActiveFocusChanged: {
                tecladoCQ.numformula = 1
            }

        }

        Text{
            id: textFormulaInt2
            anchors{
                left: textfieldFormulaInt2CQ.left
                bottom: textfieldFormulaInt2CQ.top
            }
            text: "Fórmula Interpretação 2"
            font.pixelSize: 17
            color: "white"
        }

        Text{
            id: textEntao2
            anchors{
                top: textfieldFormulaInt2CQ.top
            }
            x: 375
            text: "então"
            font.pixelSize: 17
            anchors.topMargin: 0
            color: "white"
        }

        Text{
            id: textSe2
            anchors{
                top: textfieldFormulaInt2CQ.top
            }
            x: 22
            text: "se"
            font.pixelSize: 17
            color: "white"
        }

        TextField {
            id: textfieldFormulaInt3CQ
            x: 50
            y: 330
            width: 307
            height: 30
            maximumLength: 100
            font.pointSize: 15
            placeholderText: qsTr("Digite a fórmula")
            text: classCQ.interp[4]
            onActiveFocusChanged: {
                tecladoCQ.numformula = 2
            }

        }

        Text{
            id: textFormulaInt3
            anchors{
                left: textfieldFormulaInt3CQ.left
                bottom: textfieldFormulaInt3CQ.top
            }
            text: "Fórmula Interpretação 3"
            font.pixelSize: 17
            color: "white"
        }

        Text{
            id: textEntao3
            anchors{
                top: textfieldFormulaInt3CQ.top
            }
            x: 375
            text: "então"
            font.pixelSize: 17
            anchors.topMargin: 0
            color: "white"
        }

        Text{
            id: textSe3
            anchors{
                top: textfieldFormulaInt3CQ.top
            }
            x: 22
            text: "se"
            font.pixelSize: 17
            color: "white"
        }

        TextField {
            id: textfieldString1
            x: 432
            y: 130
            width: 200
            height: 30
            maximumLength: 100
            font.pointSize: 15
            text: classCQ.interp[1]
            placeholderText: qsTr("Digite o nome")

        }

        TextField {
            id: textfieldString2
            x: 432
            y: 225
            width: 200
            height: 30
            maximumLength: 100
            font.pointSize: 15
            text: classCQ.interp[3]
            placeholderText: qsTr("Digite o nome")

        }

        TextField {
            id: textfieldString3
            x: 432
            y: 325
            width: 200
            height: 30
            maximumLength: 100
            font.pointSize: 15
            text: classCQ.interp[5]
            placeholderText: qsTr("Digite o nome")

        }

        /*Button {
            id: botaoEnviarCutOff2
            x: 50
            y: 500
            font.pointSize: 20
            text: "Aplicar"
            palette {
                button: "#4682B4"
            }
            onClicked:{
                classCQ.setinterp(classCQ.returnInterp(textfieldFormulaInt1CQ.text, textfieldString1.text, textfieldFormulaInt2CQ.text, textfieldString2.text, textfieldFormulaInt3CQ.text, textfieldString3.text))
            }
        }*/


}


/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
