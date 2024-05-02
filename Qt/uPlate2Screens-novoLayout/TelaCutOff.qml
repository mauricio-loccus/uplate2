import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {

    Component.onDestruction: {
        classCutOff.setformulas(classCutOff.returnFormulas(textfieldFormulaCO.text, textfieldFormulaAux1.text, textfieldFormulaAux2.text))
        classCutOff.setinterp(classCutOff.returnInterp(textfieldFormulaInt1.text, textfieldString1.text, textfieldFormulaInt2.text, textfieldString2.text, textfieldFormulaInt3.text, textfieldString3.text))
    }

    CheckBox{
        id: checkboxUsarBrancoCO
        checked: classCutOff.useBlank
        x: 15
        y: 15
        //text: qsTr("Usar cálculo do Branco")
        Text{
            text: "Usar cálculo do Branco"
            color: "white"
            anchors{
                verticalCenter: parent.verticalCenter
                left: parent.right
            }
        }
        onCheckStateChanged: {
            classCutOff.setUseBlank(checked)
        }
    }

    GridLayout{
        id: tecladoCutOffTipos
        x: 500
        y: 1
        property var tipos1 : ["CO", "AUX1", "AUX2"]
        property var tipos2 : ["ABS"]
        columns: 3
        rows: 2
        Repeater{
            model: tecladoCutOffTipos.tipos1
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "black"
                   text: modelData
                   font.pixelSize: 17
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
                        if(tecladoCutOff.numformula == 1){
                             textfieldFormulaAux1.text += modelData
                        }else if(tecladoCutOff.numformula == 2){
                             textfieldFormulaAux2.text += modelData
                        }else if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += modelData
                        }
                     }
               }

           }
        }
        Repeater{
            model: tecladoCutOffTipos.tipos2
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "black"
                   text: modelData
                   font.pixelSize: 17
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
                        if(tecladoCutOff.numformula == 0){
                            textfieldFormulaCO.text += modelData
                        }else if(tecladoCutOff.numformula == 1){
                            textfieldFormulaAux1.text += modelData
                        }else if(tecladoCutOff.numformula == 2){
                            textfieldFormulaAux2.text += modelData
                        }else if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += modelData
                         }
               }

               }
           }
        }

    }

    GridLayout {
        id: tecladoCutOff
        x: 700
        y: 1
        height: 100
        width: 100
        Layout.fillWidth: false
        Layout.fillHeight: false
        property var tipos1 : ["CA", "CP", "CN"]
        //property var tipos2 : ["PD", "BC", "CQ"]
        property var nums1: ["7", "8", "9"]
        property var nums2: ["4", "5", "6"]
        property var nums3: ["1", "2", "3"]
        property var nums4: ["0", "."]
        property var operacoes1 : ["-", "x", "÷"]
        property var operacoes2 : ["^", "(", ")"]
        property var operacoes3 : ["E", "OU", "≠"]
        property var operacoes4 : ["=", ">", "<" ]
        property int numformula: 0
        property string tipoAtual
        columns: 3
        rows: 4

        Repeater{
            model: tecladoCutOff.tipos1
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "black"
                   text: modelData
                   font.pixelSize: 17
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
                        tecladoCutOff.tipoAtual = modelData
                        popupCO.open()
                     }
               }

           }
        }

        Repeater{
            model: tecladoCutOff.nums1
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 17
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
                        if(tecladoCutOff.numformula == 0){
                            textfieldFormulaCO.text += modelData
                        }else if(tecladoCutOff.numformula == 1){
                            textfieldFormulaAux1.text += modelData
                        }else if(tecladoCutOff.numformula == 2){
                            textfieldFormulaAux2.text += modelData
                        }else if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += modelData
                         }

                    }
               }

           }
        }

        Repeater{
            Layout.fillWidth: false
            Layout.fillHeight: false
            model: tecladoCutOff.nums2
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 17
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
                        if(tecladoCutOff.numformula == 0){
                            textfieldFormulaCO.text += modelData
                        }else if(tecladoCutOff.numformula == 1){
                            textfieldFormulaAux1.text += modelData
                        }else if(tecladoCutOff.numformula == 2){
                            textfieldFormulaAux2.text += modelData
                        }else if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += modelData
                         }
                    }
               }

           }
        }

        Repeater{

            model: tecladoCutOff.nums3
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 17
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
                        if(tecladoCutOff.numformula == 0){
                            textfieldFormulaCO.text += modelData
                        }else if(tecladoCutOff.numformula == 1){
                            textfieldFormulaAux1.text += modelData
                        }else if(tecladoCutOff.numformula == 2){
                            textfieldFormulaAux2.text += modelData
                        }else if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += modelData
                         }
                    }
               }

           }
        }

        Repeater{

            model: tecladoCutOff.nums4
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 17
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
                        if(tecladoCutOff.numformula == 0){
                            textfieldFormulaCO.text += modelData
                        }else if(tecladoCutOff.numformula == 1){
                            textfieldFormulaAux1.text += modelData
                        }else if(tecladoCutOff.numformula == 2){
                            textfieldFormulaAux2.text += modelData
                        }else if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += modelData
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
               font.pixelSize: 17
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
                    if(tecladoCutOff.numformula == 0){
                        textfieldFormulaCO.text += "+"
                    }else if(tecladoCutOff.numformula == 1){
                        textfieldFormulaAux1.text += "+"
                    }else if(tecladoCutOff.numformula == 2){
                        textfieldFormulaAux2.text += "+"
                    }else if(tecladoCutOff.numformula == 3){
                        textfieldFormulaInt1.text += "+"
                    }else if(tecladoCutOff.numformula == 4){
                        textfieldFormulaInt2.text += "+"
                    }else if(tecladoCutOff.numformula == 5){
                        textfieldFormulaInt3.text += "+"
                     }
                }
           }

       }
        Repeater{
            model: tecladoCutOff.operacoes1
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 17
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
                        if(tecladoCutOff.numformula == 0){
                            textfieldFormulaCO.text += modelData
                        }else if(tecladoCutOff.numformula == 1){
                            textfieldFormulaAux1.text += modelData
                        }else if(tecladoCutOff.numformula == 2){
                            textfieldFormulaAux2.text += modelData
                        }else if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += modelData
                         }
                    }
               }

           }
        }

        Repeater{
            model: tecladoCutOff.operacoes2
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 17
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
                        if(tecladoCutOff.numformula == 0){
                            textfieldFormulaCO.text += modelData
                        }else if(tecladoCutOff.numformula == 1){
                            textfieldFormulaAux1.text += modelData
                        }else if(tecladoCutOff.numformula == 2){
                            textfieldFormulaAux2.text += modelData
                        }else if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += modelData
                         }
                    }
               }

           }
        }

        Repeater{
            model: tecladoCutOff.operacoes3
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 17
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
                        if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += modelData
                         }
                    }
               }

           }
        }

        Repeater{
            model: tecladoCutOff.operacoes4
            RoundButton{
                Text{
                   anchors.centerIn: parent
                   color: "white"
                   text: modelData
                   font.pixelSize: 17
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
                        if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += modelData
                         }
                    }
               }

           }
        }


    }

    RoundButton{
        x: 730
      anchors{
        top: tecladoCutOff.bottom
        right: tecladoCutOff.right

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
               if(tecladoCutOff.numformula == 0){
                   textfieldFormulaCO.text = ""
               }else if(tecladoCutOff.numformula == 1){
                   textfieldFormulaAux1.text = ""
               }else if(tecladoCutOff.numformula == 2){
                   textfieldFormulaAux2.text = ""
               }else if(tecladoCutOff.numformula == 3){
                 textfieldFormulaInt1.text = ""
               }else if(tecladoCutOff.numformula == 4){
                 textfieldFormulaInt2.text = ""
               }else if(tecladoCutOff.numformula == 5){
                 textfieldFormulaInt3.text = ""
              }
           }
      }

   }

    TextField {
        id: textfieldFormulaCO
        x: 90
        y: 80
        width: 307
        height: 30
        maximumLength: 100
        font.pointSize: 15
        placeholderText: qsTr("Digite a fórmula")
        text: classCutOff.formulas[0]
        onActiveFocusChanged: {
            tecladoCutOff.numformula = 0
        }

    }

    Text{
        id: textFormulaCO
        anchors{
            left: textfieldFormulaCO.left
            bottom: textfieldFormulaCO.top
        }
        text: "Fórmula Cut-Off"
        font.pixelSize: 17
        color: "white"
    }

    Text{
        id: textCO
        anchors{
            top: textfieldFormulaCO.top
            right: textfieldFormulaCO.left
        }
        x: 15
        text: "CO = "
        font.pixelSize: 17
        color: "white"
    }

    TextField {
        id: textfieldFormulaAux1
        x: 90
        y: 150
        width: 307
        height: 30
        maximumLength: 100
        font.pointSize: 15
        placeholderText: qsTr("Digite a fórmula")
        text: classCutOff.formulas[1]
        onActiveFocusChanged: {
            tecladoCutOff.numformula = 1
        }

    }

    Text{
        id: textFormulaAux1
        anchors{
            left: textfieldFormulaAux1.left
            bottom: textfieldFormulaAux1.top
        }
        text: "Fórmula Auxiliar 1"
        font.pixelSize: 17
        color: "white"
    }

    Text{
        id: textAux1
        anchors{
            top: textfieldFormulaAux1.top
            right: textfieldFormulaAux1.left
        }
        x: 15
        text: "AUX1 = "
        font.pixelSize: 17
        color: "white"
    }

    TextField {
        id: textfieldFormulaAux2
        x: 90
        y: 220
        width: 307
        height: 30
        maximumLength: 100
        font.pointSize: 15
        placeholderText: qsTr("Digite a fórmula")
        text: classCutOff.formulas[2]
        onActiveFocusChanged: {
            tecladoCutOff.numformula = 2
        }

    }

    Text{
        id: textFormulaAux2
        anchors{
            left: textfieldFormulaAux2.left
            bottom: textfieldFormulaAux2.top
        }
        text: "Fórmula Auxiliar 2"
        font.pixelSize: 17
        color: "white"
    }

    Text{
        id: textAux2
        anchors{
            top: textfieldFormulaAux2.top
            right: textfieldFormulaAux2.left
        }
        x: 15
        text: "AUX2 = "
        font.pixelSize: 17
        color: "white"
    }

    TextField {
        id: textfieldFormulaInt1
        x: 90
        y: 290
        width: 307
        height: 30
        maximumLength: 100
        font.pointSize: 15
        placeholderText: qsTr("Digite a fórmula")
        text: classCutOff.interp[0]
        onActiveFocusChanged: {
            tecladoCutOff.numformula = 3
        }
    }
    Text{
        id: textFormulaInt1
        anchors{
            left: textfieldFormulaInt1.left
            bottom: textfieldFormulaInt1.top
        }
        text: "Fórmula Interpretação 1"
        font.pixelSize: 17
        color: "white"
    }

    Text{
        id: textEntao1
        anchors{
            top: textfieldFormulaInt1.top
        }
        x: 409
        text: "então"
        font.pixelSize: 17
        anchors.topMargin: 0
        color: "white"
     }

     Text{
         id: textSe1
         anchors{
             top: textfieldFormulaInt1.top
         }
         x: 62
         text: "Se"
         font.pixelSize: 17
         color: "white"
     }

     TextField {
         id: textfieldString1
         x: 460
         y: 290
         width: 200
         height: 30
         maximumLength: 100
         font.pointSize: 15
         text: classCutOff.interp[1]
         placeholderText: qsTr("Digite o nome")

     }

     TextField {
         id: textfieldFormulaInt2
         x: 90
         y: 360
         width: 307
         height: 30
         maximumLength: 100
         font.pointSize: 15
         placeholderText: qsTr("Digite a fórmula")
         text: classCutOff.interp[2]
         onActiveFocusChanged: {
             tecladoCutOff.numformula = 4
         }

     }

     Text{
         id: textFormulaInt2
         anchors{
             left: textfieldFormulaInt2.left
             bottom: textfieldFormulaInt2.top
         }
         text: "Fórmula Interpretação 2"
         font.pixelSize: 17
         color: "white"
     }

     Text{
         id: textEntao2
         anchors{
             top: textfieldFormulaInt2.top
         }
         x: 409
         text: "então"
         font.pixelSize: 17
         anchors.topMargin: 0
         color: "white"
     }

     Text{
         id: textSe2
         anchors{
             top: textfieldFormulaInt2.top
         }
         x: 62
         text: "Se"
         font.pixelSize: 17
         color: "white"
     }

     TextField {
         id: textfieldString2
         x: 460
         y: 355
         width: 200
         height: 30
         maximumLength: 100
         font.pointSize: 15
         text: classCutOff.interp[3]
         placeholderText: qsTr("Digite o nome")

     }

     TextField {
         id: textfieldFormulaInt3
         x: 90
         y: 430
         width: 307
         height: 30
         maximumLength: 100
         font.pointSize: 15
         placeholderText: qsTr("Digite a fórmula")
         text: classCutOff.interp[4]
         onActiveFocusChanged: {
             tecladoCutOff.numformula = 5
         }

     }

     Text{
         id: textFormulaInt3
         anchors{
             left: textfieldFormulaInt3.left
             bottom: textfieldFormulaInt3.top
         }
         text: "Fórmula Interpretação 3"
         font.pixelSize: 17
         color: "white"
     }

     Text{
         id: textEntao3
         anchors{
             top: textfieldFormulaInt3.top
         }
         x: 409
         text: "então"
         font.pixelSize: 17
         anchors.topMargin: 0
         color: "white"
     }

     Text{
         id: textSe3
         anchors{
             top: textfieldFormulaInt3.top
         }
         x: 62
         text: "Se"
         font.pixelSize: 17
         color: "white"
     }

     TextField {
         id: textfieldString3
         x: 460
         y: 430
         width: 200
         height: 30
         maximumLength: 100
         font.pointSize: 15
         text: classCutOff.interp[5]
         placeholderText: qsTr("Digite o nome")

     }


    Popup{
        id: popupCO
        parent: Overlay.overlay
        x: 740
        y: 1
        PopupTelaCO{

        }
    }

    /*Button {
        id: botaoEnviarCutOff
        x: 50
        y: 500
        font.pointSize: 20
        text: "Aplicar"
        palette {
            button: "#4682B4"
        }
        onClicked: {
            classCutOff.setformulas(classCutOff.returnFormulas(textfieldFormulaCO.text, textfieldFormulaAux1.text, textfieldFormulaAux2.text))
            classCutOff.setinterp(classCutOff.returnInterp(textfieldFormulaInt1.text, textfieldString1.text, textfieldFormulaInt2.text, textfieldString2.text, textfieldFormulaInt3.text, textfieldString3.text))
        }

    }*/


}

/*##^##
Designer {
    D{i:0;autoSize:true;height:680;width:1024}
}
##^##*/
