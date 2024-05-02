import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {
    id: itemPopup
    GridLayout{
        id: gridlayoutPopupCQ
        property var tipos1 : ["1", "2", "3", "4", "5"]
        columns: 5
        rows: 1
        Repeater{
            model: gridlayoutPopupCQ.tipos1
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
                onClicked: {
                    if(tecladoCQ.numformula == 0){
                        textfieldFormulaInt1CQ.text += tecladoCQTipos.tipoAtualCQ + modelData
                    }else if(tecladoCQ.numformula == 1){
                        textfieldFormulaInt2CQ.text += tecladoCQTipos.tipoAtualCQ + modelData
                    }else if(tecladoCQ.numformula == 2){
                        textfieldFormulaInt3CQ.text +=  tecladoCQTipos.tipoAtualCQ + modelData
                    }

                 }

              }

           }
        }
    }

}
