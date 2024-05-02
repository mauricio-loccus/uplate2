import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {
    id: itemTelaResultados2
    property int numFiltro : 0

    property alias botaoResultadosAbs : botaoResultadosABS
    property alias botaoResultadosBranco :  botaoResultadosBranco
    property alias botaoResultadosCutOff : botaoResultadosCutOff
    property alias botaoResultadosCQ : botaoResultadosCQ

    ListModel{
        id: listaTelaExpetimentoLetras
        ListElement { name: "A"}
        ListElement { name: "B"}
        ListElement { name: "C"}
        ListElement { name: "D"}
        ListElement { name: "E"}
        ListElement { name: "F"}
        ListElement { name: "G"}
        ListElement { name: "H"}
    }

    ListModel{
        id: listaTelaExpetimentoNum
        ListElement { name: "1"}
        ListElement { name: "2"}
        ListElement { name: "3"}
        ListElement { name: "4"}
        ListElement { name: "5"}
        ListElement { name: "6"}
        ListElement { name: "7"}
        ListElement { name: "8"}
        ListElement { name: "9"}
        ListElement { name: "10"}
        ListElement { name: "11"}
        ListElement { name: "12"}
    }


    function showHidePocos(val) {

        if(val === true){
            tabelaPocos.visible = true
            gridTelaExperimentoNum.visible = true
            gridTelaExperimentoLetras.visible = true
            //textIndicadorResultadoCQ.visible = false
            rectangleResultadoCQ.visible = false
        }else{
            tabelaPocos.visible = false
            gridTelaExperimentoNum.visible = false
            gridTelaExperimentoLetras.visible = false
            //textIndicadorResultadoCQ.visible = true
            rectangleResultadoCQ.visible = true
        }
    }

    property bool textType : true
    property alias botaoResultadosABS: botaoResultadosABS

    function setText(type) {

        showHidePocos(true)

    }




    Column{
        id: tabelaPocos
        x: 60
        y: 79

        Repeater{
            id: linhaRepeater
            model: 8
            Row{
                //x: 60
                //y: 10
                property int columnIndex: index
                Repeater{
                    id: colunaRepeater
                    model:12


                    Rectangle{
                        property int rowIndex: index
                        id: myRectangleFloat
                        visible: true
                        //x: 22
                        // y: 32
                        width: 70
                        height: 40
                        color: "#ebdef0"
                        border.color: "#10125d"
                        Text {
                            id: textoResultadosBrutosFloat
                            anchors.centerIn: parent
                            font.pixelSize: 10
                            property int realIndex: (rowIndex)+(12*columnIndex)
                            text: textType ? classBrutos.array[realIndex].toFixed(3) : classBrutos.array[realIndex]
                        }
                    }
                }
            }

        }
    }

    GridView {
        id: gridTelaExperimentoNum
        anchors.fill: parent
        anchors.rightMargin: -60
        anchors.bottomMargin: -45
        anchors.leftMargin: 60
        anchors.topMargin: 45
        model: listaTelaExpetimentoNum
        cellWidth:  70
        delegate: Text {
            text: name
            font.pixelSize: 25
            color: "white"
        }

    }

    GridView {
        id: gridTelaExperimentoLetras
        anchors.fill: parent
        anchors.rightMargin: -35
        anchors.bottomMargin: -95
        anchors.leftMargin: 35
        anchors.topMargin: 95
        model: listaTelaExpetimentoLetras
        cellHeight: 40
        cellWidth:  1024
        delegate: Text {
            text: name
            font.pixelSize: 20
            color: "white"
        }

    }



    Rectangle{
        id: rectangleResultadoCQ
        x: 250
        y: 72
        radius: 10
        height: 300
        width: 500
        color: "#E6E6FA"
        border.width: 2
        border.color: "#364b7f"

        Text{
                id: textfieldFormulaInt1CQ
                x: 50
                y: 20
                font.pointSize: 13
                text: classCQ.interp[0]

            }

            Text{
                id: textEntao1
                anchors{
                    top: textfieldFormulaInt1CQ.top
                }
                x: 260
                text: "então"
                font.pixelSize: 17
                anchors.topMargin: 6
                color: "black"
            }

            Text{
                id: textSe1
                anchors{
                    top: textfieldFormulaInt1CQ.top
                }
                x: 22
                text: "se"
                font.pixelSize: 17
                color: "black"
            }

            Text{
                id: textfieldFormulaInt2CQ
                x: 50
                y: 100
                font.pointSize: 13
                text: classCQ.interp[2]
            }

            Text{
                id: textEntao2
                anchors{
                    top: textfieldFormulaInt2CQ.top
                }
                x: 260
                text: "então"
                font.pixelSize: 17
                color: "black"
            }

            Text{
                id: textSe2
                anchors{
                    top: textfieldFormulaInt2CQ.top
                }
                x: 22
                text: "se"
                font.pixelSize: 17
                color: "black"
            }

            Text{
                id: textfieldFormulaInt3CQ
                x: 50
                y: 180
                font.pointSize: 13
                text: classCQ.interp[4]

            }

            Text{
                id: textEntao3
                anchors{
                    top: textfieldFormulaInt3CQ.top
                }
                x: 260
                text: "então"
                font.pixelSize: 17
                color: "black"
            }

            Text{
                id: textSe3
                anchors{
                    top: textfieldFormulaInt3CQ.top
                }
                x: 22
                text: "se"
                font.pixelSize: 17
                color: "black"
            }

            Text{
                id: textfieldString1
                x: 310
                y: 20
                font.pointSize: 13
                text: classCQ.interp[1]
            }

            Text{
                id: textfieldString2
                x: 310
                y: 100
                font.pointSize: 13
                text: classCQ.interp[3]

            }

            Text{
                id: textfieldString3
                x: 310
                y: 180
                font.pointSize: 13
                text: classCQ.interp[5]

            }

        Text{
            id: textIndicadorResultadoCQ
            x: 22
            y: 260
            text: "Resultado:"
            font.pixelSize: 20
            color: "black"


        }

        Text{
            id: textResultadoCQ
            anchors{
                top: textIndicadorResultadoCQ.top
                left: textIndicadorResultadoCQ.right
            }
            text: classCQ.cqResult
            font.pixelSize: 20
            color: "black"
        }


    }




    ButtonGroup {
        buttons: column.children
    }

    Column {

        id: column

        RadioButton{
            id: botaoResultadosABS
            x: 40
            y: -9
            //text: "ABS"
            Text{
                id: textbotaoResultadosABS
                text: "ABS"
                color: "white"
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.right
                }
            }
            onClicked:{
                classBrutos.setarray(classBrutos.printRawData(numFiltro))
                textType = true
                showHidePocos(true)
                checked = true
            }
        }

        RadioButton{
            id: botaoResultadosBranco
            anchors{
                top: botaoResultadosABS.top
            }
            x: 120
            //text: "Branco"
            Text{
                id: textbotaoResultadosBranco
                text: "Branco"
                color: "white"
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.right
                }
            }
            onClicked:{
                classBrutos.setarray(classBranco.printBlankData(numFiltro))
                textType = true
                showHidePocos(true)
                checked = true
            }
        }

        RadioButton{
            id: botaoResultadosCutOff
            anchors{
                top: botaoResultadosABS.top
                //left: botaoResultadosBranco.right
            }
            x: 200
            //text: "Cut-off"
            Text{
                id: textbotaoResultadosCO
                text: "Cut-off"
                color: "white"
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.right
                }
            }
            onClicked:{
                classCutOff.coCalculus()
                classCutOff.interpCalculus()
                classBrutos.setarray(classCutOff.printInterp(numFiltro))
                textType = false
                showHidePocos(true)
                checked = true
            }
        }

        RadioButton{
            id: botaoResultadosAux1
            anchors{
                top: botaoResultadosABS.top
                //left: botaoResultadosBranco.right
            }
            x: 280
            //text: "Cut-off"
            Text{
                id: textbotaoResultadosAux1
                text: "Aux 1"
                color: "white"
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.right
                }
            }

            onClicked:{
                classCutOff.coCalculus()
                classBrutos.setarray(classCutOff.printAux1Data(numFiltro))
                textType = true
                showHidePocos(true)
                checked = true
            }

        }

        RadioButton{
            id: botaoResultadosAux2
            anchors{
                top: botaoResultadosABS.top
                //left: botaoResultadosBranco.right
            }
            x: 360
            //text: "Cut-off"
            Text{
                id: textbotaoResultadosAux2
                text: "Aux 2"
                color: "white"
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.right
                }
            }

            onClicked:{
                classCutOff.coCalculus()
                classBrutos.setarray(classCutOff.printAux2Data(numFiltro))
                textType = true
                showHidePocos(true)
                checked = true
            }

        }

        RadioButton {
            id: botaoResultadosCQ
            //text: "CQ"
            anchors{
                top: botaoResultadosABS.top
            }
            x: 440
            Text{
                id: textbotaoResultadosCQ
                text: "CQ"
                color: "white"
                anchors{
                    verticalCenter: parent.verticalCenter
                    left: parent.right
                }
            }
            onClicked: {
                classCutOff.coCalculus()
                classCQ.setcqResult(classCQ.interpCalculus(numFiltro))
                showHidePocos(false)
                checked = true
            }
        }
    }
}

/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
