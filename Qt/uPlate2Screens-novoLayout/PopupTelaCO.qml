import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {
    id: itemPopup
    GridLayout{
        id: gridlayoutPopupCO
        property var tipos1 : ["1", "2", "3", "4", "5"]
        columns: 5
        rows: 1
        Repeater{
            model: gridlayoutPopupCO.tipos1
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
                    onClicked: {
                        if(tecladoCutOff.numformula == 0){
                            textfieldFormulaCO.text += tecladoCutOff.tipoAtual + modelData
                        }else if(tecladoCutOff.numformula == 1){
                            textfieldFormulaAux1.text += tecladoCutOff.tipoAtual + modelData
                        }else if(tecladoCutOff.numformula == 2){
                            textfieldFormulaAux2.text +=  tecladoCutOff.tipoAtual + modelData
                        }else if(tecladoCutOff.numformula == 3){
                            textfieldFormulaInt1.text += tecladoCutOff.tipoAtual + modelData
                        }else if(tecladoCutOff.numformula == 4){
                            textfieldFormulaInt2.text += tecladoCutOff.tipoAtual + modelData
                        }else if(tecladoCutOff.numformula == 5){
                            textfieldFormulaInt3.text += tecladoCutOff.tipoAtual + modelData
                         }
                     }
              }

           }
        }
    }

}
