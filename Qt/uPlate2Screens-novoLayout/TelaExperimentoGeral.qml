import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.1

Item{

    anchors.fill: parent
    Rectangle{

        id: rectangleEnsaio
        x: 300
        radius: 10
        height: 500
        width: 500
        color: "#E6E6FA"
        border.width: 2
        border.color: "#364b7f"
        Text{
            anchors{
                top: parent.top
                horizontalCenter: parent.horizontalCenter
            }
            text: "Protocolo"
            font.pixelSize: 22
            color: "dark blue"

        }

        /*ComboBox{
            id: comboboxTipoLeitura
            x: 50
            y: 50
            model: ["Normal"]
         }

        Text {
            id: textTipoLeitura
            anchors{
             left: comboboxTipoLeitura.left
             bottom: comboboxTipoLeitura.top
            }
            text: "Tipo de Leitura"
            font.pixelSize: 18
            color: "black"
         }*/

        ComboBox{
            id: comboboxVelocidadeLeitura
            x: 50
            y: 50
            currentIndex: classSerial.speed
            model: ["Normal", "Rápida"]
            onCurrentIndexChanged: {
               classSerial.setSpeed(currentIndex)
            }
         }

        Text {
            id: textVelocidadeLeitura
            y: 105
            anchors{
             left: comboboxVelocidadeLeitura.left
             bottom: comboboxVelocidadeLeitura.top
            }
            text: "Velocidade"
            font.pixelSize: 18
            color: "black"
        }

        ComboBox{
            id: comboboxOperacao
            x: 300
            y: 50
            currentIndex: classSerial.operacaoL12
            model: ["Nenhuma"]
            onCurrentIndexChanged: {
               classSerial.setOperacaoL12(currentIndex)
            }
         }

        Text {
            id: textOperacao
            y: 123
            anchors{
             left: comboboxOperacao.left
             bottom: comboboxOperacao.top
            }
            text: "Operação Leituras"
            font.pixelSize: 18
            anchors.bottomMargin: 6
            anchors.leftMargin: 0
            color: "black"
        }

        CheckBox{
            id: checkboxUsarBrancoDiferencial
            checked: classSerial.useblankL12
            x: 300
            y: 87
            text: qsTr("Usar cálculo do Branco")
            visible: false
            onCheckStateChanged: {
               classSerial.setUseblankL12(checked)
            }
         }




        ComboBox{
            id: comboboxFiltro1
            x: 50
            y: 150
            //model: ["405nm", "450nm", "492nm", "630nm"]
            model: classConfigFilt.model_configFilt()
            currentIndex: classSerial.filtro1
            onCurrentIndexChanged:{
                classSerial.setFiltro1(currentIndex)
                comboboxFiltro2.model = classConfigFilt.model2_configFilt()

          }
         }

        Text {
            id: textFiltro1
            y: 123
            anchors{
             left: comboboxFiltro1.left
             bottom: comboboxFiltro1.top
            }
            text: "Filtro 1"
            font.pixelSize: 18
            anchors.bottomMargin: 6
            anchors.leftMargin: 0
            color: "black"
        }

        ComboBox{
            id: comboboxFiltro2
            x: 300
            y: 150
            model: classConfigFilt.model2_configFilt()
            currentIndex: classSerial.filtro2
            onCurrentIndexChanged: {
             if(currentIndex !== 0){
                 comboboxOperacao.model = ["L1+L2", "L1-L2", "L2-L1", "L1*L2", "L1/L2", "L2/L1"]
                 checkboxUsarBrancoDiferencial.visible = true
             }else{
                 checkboxUsarBrancoDiferencial.visible = false
                 comboboxOperacao.model = ["Nenhum"]
            }
            classSerial.setFiltro2(currentIndex)
           }
         }

        Text {
            id: textFiltro2
            y: 223
            anchors{
             left: comboboxFiltro2.left
             bottom: comboboxFiltro2.top
            }
            text: "Filtro 2"
            font.pixelSize: 18
            anchors.bottomMargin: 6
            anchors.leftMargin: 0
            color: "black"
        }

        Text{
            id: textNomeArquivoProtocolo
            x: 238
            y: 230
            width: 200
            height: 30
            font.pointSize: 15
            text: classSalvarProt.protocolName

        }
        Text{
            id: textIndicadorNomeArquivoProtocolo
            x: 50
            y: 230
            text: "Nome do Protocolo:"
            font.pointSize: 15
        }

        Text{
            id: textDataArquivoProtocolo
            x: 238
            y: 330
            width: 200
            height: 30
            font.pointSize: 15
            text: classSalvarProt.protocolDate

        }
        Text{
            id: textIndicadorDataArquivoProtocolo
            x: 50
            y: 330
            text: "Última Modificação:"
            font.pointSize: 15
        }

        Rectangle{
            id: rectangleSalvar
            width: 80
            height: 40
            radius: 5
            color: "#CD5C5C"
            x: 150
            y: 450
            border.width: 3
            border.color: "#CD5C5C"
            Text {
                color: "white"
                text: "Salvar"
                font.pixelSize: 15
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                   fileDialogSalvarProtocolo.open()

                }
                onPressed: {
                    parent.border.color = "red"
                }
                onReleased: {
                    parent.border.color = "#CD5C5C"
                }
            }

        }

        Rectangle{
            id: rectangleCarregar
            width: 100
            height: 40
            radius: 5
            color: "#CD5C5C"
            x: 260
            y: 450
            border.width: 3
            border.color: "#CD5C5C"
            Text {
                color: "white"
                text: "Carregar"
                font.pixelSize: 15
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    fileDialogCarregarProtocolo.open()

                }
                onPressed: {
                    parent.border.color = "red"
                }
                onReleased: {
                    parent.border.color = "#CD5C5C"
                }

            }

        }

     }

    FileDialog{
        id: fileDialogSalvarProtocolo
        title: "Salvar Protocolo"
        fileMode: FileDialog.SaveFile
        folder: classSalvarProt.imprimirPath()
        nameFilters: ["JSON files (*.json)"]
        onAccepted:{
            var path = fileDialogSalvarProtocolo.currentFile.toString();
            path= path.replace(folder + "/" ,"");
            if(Qt.platform.os === "windows"){
                classSalvarProt.setprotocolName(path.replace(".json",""))
                classSalvarProt.salvar(path)
            }else{
                classSalvarProt.setprotocolName(path)
                classSalvarProt.salvar(path+".json")
            }
        }

    }



    FileDialog{
        id: fileDialogCarregarProtocolo
        title: "Carregar protocolo"
        fileMode: FileDialog.OpenFile
        folder: classSalvarProt.imprimirPath()
        nameFilters: ["JSON files (*.json)"]
        onAccepted:{
            var path = fileDialogCarregarProtocolo.currentFile.toString();
            path= path.replace(folder ,"");
            var auxPath = path
            auxPath = auxPath.replace("/","")
            auxPath = auxPath.replace(".json","")
            classSalvarProt.abrir(path)
            classSalvarProt.setprotocolName(auxPath)
            loaderInicio.source = ""
            loaderInicio.source = "TelaExperimentoGeral.qml"
        }
    }

}




/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
