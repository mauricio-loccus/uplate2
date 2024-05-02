import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.1

Item {
    anchors.fill: parent

    Component.onCompleted: {
        if(classArquivos.lastPathExp===""){
            classArquivos.setlastPathExp(StandardPaths.writableLocation(StandardPaths.DocumentsLocation))
            console.log(classArquivos.lastPathExp)
        }

        if(classArquivos.lastPathImp===""){
            classArquivos.setlastPathImp(StandardPaths.writableLocation(StandardPaths.DocumentsLocation))
            console.log(classArquivos.lastPathImp)
        }
    }

    Component.onDestruction: {
        classConfigPath.salvarConfigPath()
    }
    Rectangle{

        id: rectangleExportar
        x: 300
        radius: 10
        height: 500
        width: 500
        color: "#E6E6FA"
        border.width: 2
        border.color: "#364b7f"
        Text{
            id: textExportar
            x: 50
            y: 5
            text: "Exportar:"
            font.pixelSize: 22
            color: "dark blue"

        }

        ComboBox{
            id: comboboxTipoArquivo
            x: 50
            y: 60
            property int fileIndex: comboboxTipoArquivo.currentIndex
            model: ["CSV", "EXCEL", "TXT"]
            currentIndex: classArquivos.fileTypeExp
            onCurrentIndexChanged: {
                classArquivos.setfileTypeExp(currentIndex)
            }
         }

        Text {
            id: textTipoArquivo
            anchors{
             left: comboboxTipoArquivo.left
             bottom: comboboxTipoArquivo.top
            }
            text: "Tipo Arquivo"
            font.pixelSize: 18
            color: "black"
         }

        ComboBox{
            id: comboboxSeparadorColuna
            x: 50
            y: 160
            model: [".", ",", ";", ":", "TAB"]
            currentIndex: classArquivos.sepColExp
            onCurrentIndexChanged: {
                if(comboboxSeparadorColuna.currentIndex === 0){
                    comboboxSeparadorDecimal.model = [","]
                }else if(comboboxSeparadorColuna.currentIndex === 1){
                    comboboxSeparadorDecimal.model = ["."]
                }else{
                    comboboxSeparadorDecimal.model = [".",","]
                }
                classArquivos.setsepColExp(currentIndex)
            }
         }

        Text {
            id: textSeparadorColuna
            anchors{
             left: comboboxSeparadorColuna.left
             bottom: comboboxSeparadorColuna.top
            }
            text: "Separador Coluna"
            font.pixelSize: 18
            color: "black"
         }

        ComboBox{
            id: comboboxSeparadorDecimal
            x: 50
            y: 260
            model: [","]
            currentIndex: classArquivos.sepDecimal
            onCurrentIndexChanged:{
                classArquivos.setsepDecimal(currentIndex)
            }
         }

        Text {
            id: textSeparadorDecimal
            anchors{
             left: comboboxSeparadorDecimal.left
             bottom: comboboxSeparadorDecimal.top
            }
            text: "Separador Decimal"
            font.pixelSize: 18
            color: "black"
         }

        Text{
            id: textImportar
            x: 300
            y: 5
            text: "Importar:"
            font.pixelSize: 22
            color: "dark blue"

        }

        ComboBox{
            id: comboboxTipoArquivoImportar
            x: 300
            y: 60
            model: ["CSV", "TXT"]
            property int fileIndex: comboboxTipoArquivo.currentIndex
            currentIndex: classArquivos.fileTypeImp
            onCurrentIndexChanged: {
                classArquivos.setfileTypeImp(currentIndex)
            }
         }

        Text {
            id: textTipoArquivoImportar
            anchors{
             left: comboboxTipoArquivoImportar.left
             bottom: comboboxTipoArquivoImportar.top
            }
            text: "Tipo Arquivo"
            font.pixelSize: 18
            color: "black"
         }

        ComboBox{
            id: comboboxSeparadorColunaImportar
            x: 300
            y: 160
            model: [".", ",", ";", ":", "TAB"]
            currentIndex: classArquivos.sepColImp
            onCurrentIndexChanged: {
                classArquivos.setsepColImp(currentIndex)
            }
         }

        Text {
            id: textSeparadorColunaImportar
            anchors{
             left: comboboxSeparadorColunaImportar.left
             bottom: comboboxSeparadorColunaImportar.top
            }
            text: "Separador Coluna"
            font.pixelSize: 18
            color: "black"
         }

        Rectangle{
            id: rectanglebuttonExportar
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
                text: "Exportar"
                font.pixelSize: 15
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    filedialogSalvar.open()
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
            id: rectanglebuttonImportar
            width: 80
            height: 40
            radius: 5
            color: "#CD5C5C"
            x: 300
            y: 450
            border.width: 3
            border.color: "#CD5C5C"
            Text {
                color: "white"
                text: "Importar"
                font.pixelSize: 15
                anchors.centerIn: parent
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    fileDialogimportarCSV.open()
                }
                onPressed: {
                    parent.border.color = "red"
                }
                onReleased: {
                    parent.border.color = "#CD5C5C"
                }

            }
        }


        Popup{
            id: popupError
            visible: false
            anchors.centerIn: parent
            width: 200
            height: 200
            closePolicy: Popup.NoAutoClose
            palette.text: "red"
            background: Rectangle{
                color: "white"
            }
            Text{
                id: textPopUp
                color: "red"
                anchors{
                    top: parent.top
                    horizontalCenter: parent.horizontalCenter
                }
                text: "Falha ao importar!"
                font.pointSize: 16
            }
            TextArea{
                id: textpopupdescr
                color: "black"
                anchors.centerIn: parent
                width: parent.width
                text: "Verifique o separador \n de coluna e tente \n novamente."
            }

            Rectangle{
                id: rectanglebuttonOk
                width: 80
                height: 40
                radius: 5
                color: "#CD5C5C"
                anchors{
                    bottom: parent.bottom
                    right: parent.right
                }
                border.width: 3
                border.color: "#CD5C5C"
                Text {
                    color: "white"
                    text: "Ok"
                    font.pixelSize: 15
                    anchors.centerIn: parent
                }
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        popupError.close()
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

    }





    FileDialog {
        id: filedialogSalvar
        title: "Salvar"
        folder: classArquivos.lastPathExp
        fileMode: FileDialog.SaveFile
        //currentFile:StandardPaths.displayName(StandardPaths.DocumentsLocation)
        nameFilters: ["CSV files (*.csv)", "EXCEL files (*.xls)", "TXT files (*.txt)"]
        selectedNameFilter.index: comboboxTipoArquivo.currentIndex
        onAccepted: {
            classArquivos.setlastPathExp(folder)

            classCutOff.coCalculus()
            classCutOff.interpCalculus()

            var path = filedialogSalvar.currentFile.toString();
            console.log(path)
            switch (Qt.platform.os) {

            case "windows":
                path= path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
                console.log(path)

                if(comboboxTipoArquivo.currentIndex === 0){
                    classArquivos.gerarCSVTXT(path)
                }else if(comboboxTipoArquivo.currentIndex === 1){
                    classArquivos.gerarXLS(path)
                }else{
                    classArquivos.gerarCSVTXT(path)
                }
                break;
            default: {
                path= path.replace(/^(file:\/{2})|(qrc:\/{2})|(http:\/{2})/,"");
                console.log(path)

                if(comboboxTipoArquivo.currentIndex === 0){
                    classArquivos.gerarCSVTXT(path+".csv")
                }else if(comboboxTipoArquivo.currentIndex === 1){
                    classArquivos.gerarXLS(path+".xls")
                }else{
                    classArquivos.gerarCSVTXT(path+".txt")
                }
                break;
            }
            }
        }
     }

    FileDialog{
        id: fileDialogimportarCSV
        title: "Importar"
        fileMode: FileDialog.OpenFile
        folder: classArquivos.lastPathImp
        nameFilters: ["CSV files (*.csv)", "TXT files (*.txt)"]
        selectedNameFilter.index: comboboxTipoArquivoImportar.currentIndex
        onAccepted: {
            classArquivos.setlastPathImp(folder)

            var path = fileDialogimportarCSV.currentFile.toString();
            console.log(path)

            switch (Qt.platform.os) {
            case "windows":
                path= path.replace(/^(file:\/{3})|(qrc:\/{2})|(http:\/{2})/,"");
                console.log(path)
                if(classImport.importarCSVTXT(comboboxSeparadorColunaImportar.currentIndex,path)===1){
                    popupError.open()
                }
                break;
            default: {
                path= path.replace(/^(file:\/{2})|(qrc:\/{2})|(http:\/{2})/,"");
                console.log(path)
                if(classImport.importarCSVTXT(comboboxSeparadorColunaImportar.currentIndex,path)===1){
                    popupError.open()
                }
                break;
            }
       }

        }
    }
  }



