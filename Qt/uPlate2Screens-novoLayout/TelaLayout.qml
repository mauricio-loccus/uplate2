import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item{

    Component.onCompleted: {
        classLayout.setwellID(classLayout.returnWellID(0))
        classLayout.setuniqueID(classLayout.returnUniqueID(0))

        for(var i=0; i<96; i++){
            if(classLayout.colorWell[i]===""){
                classLayout.setcolorWell(classLayout.returnColorWell(i, "white"))
            }
        }
    }

    property int posXPlaca: 60
    property int posYPlaca: 40
    property int recPocoLado: 55

    property int alturaSelecionador
    property int larguraSelecionador
    property int posYSelecionador
    property int posXSelecionador

    property string tipoSelecionado: "DC"
    property string corSelecionada: "purple"

    /* PLACA DE POÇOS */

    Rectangle{
        id: rectanglePlaca
        x: posXPlaca
        y: posYPlaca

        width: recPocoLado*12
        height: recPocoLado*8
        color: "#E6E6FA"
        Column{
            Repeater{
                id: repeaterLinha
                model: 8
                Row{
                    property int rowLayIndex: index
                    Repeater{
                        id: repeaterColuna
                        model: 12
                        Rectangle{
                            property int colLayIndex: index
                            id: rectanglePoco
                            width: recPocoLado
                            height: recPocoLado
                            color: "transparent"
                            Rectangle{
                                property int realLayIndex: (colLayIndex)+(12*rowLayIndex)
                                height: recPocoLado
                                width: recPocoLado
                                radius: recPocoLado
                                color: classLayout.colorWell[realLayIndex]
                                border.width: 2
                                border.color: "#364b7f"
                                Text{
                                    anchors{
                                        verticalCenter: parent.verticalCenter
                                        horizontalCenter: parent.horizontalCenter
                                    }
                                    text: classLayout.typeArr[parent.realLayIndex]
                                }

                                anchors{
                                    verticalCenter: parent.verticalCenter
                                    horizontalCenter: parent.horizontalCenter
                                }
                                MouseArea{
                                    anchors.fill: parent
                                    cursorShape: Qt.PointingHandCursor
                                    acceptedButtons: Qt.LeftButton | Qt.RightButton
                                    onClicked: {
                                            recSelecao.x = colLayIndex*recPocoLado + posXPlaca
                                            recSelecao.y = rowLayIndex*recPocoLado + posYPlaca
                                            recSelecao.width = recPocoLado
                                            recSelecao.height = recPocoLado
                                            classLayout.settypeArr(classLayout.setPocoType(parent.realLayIndex, tipoSelecionado))
                                            classLayout.setcolorWell(classLayout.returnColorWell(parent.realLayIndex, corSelecionada))
                                            classLayout.setuniqueID(classLayout.returnUniqueID(parent.realLayIndex))
                                            classLayout.setwellID(classLayout.returnWellID(parent.realLayIndex))
                                            classLayout.setuniqueID(classLayout.returnUniqueID(parent.realLayIndex))
                                            popupTelaLayout.realPopupIndex = parent.realLayIndex


                                    }

                                }

                            }

                        }

                    }


                }

            }

        }
    }


    Popupwell{
        id: popupTelaLayout
        property int realPopupIndex;
        x: posXPlaca*12 + 25
        y: 250

    }

    GridLayout{
        id: gridNumeroPocos
        x: posXPlaca
        y: posYPlaca - 20
        property var numeros : ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10", "11", "12"]
        columns: 12
        rows: 1
        columnSpacing: 0
        Repeater{
            model: parent.numeros
            Rectangle{
                color: "transparent"
                width: recPocoLado
                height: 20
                Text{
                    anchors.centerIn: parent
                    text: modelData
                    color: "white"
                    font.pixelSize: 20
                }

            }

        }

    }

    GridLayout{
        id: gridLetrasPocos
        x: posXPlaca - 20
        y: posYPlaca
        property var letras : ["A", "B", "C", "D", "E", "F", "G", "H"]
        columns: 1
        rows: 8
        rowSpacing: 0
        Repeater{
            model: parent.letras
            Rectangle{
                color: "transparent"
                width: 20
                height: recPocoLado
                Text{
                    anchors.centerIn: parent
                    text: modelData
                    color: "white"
                    font.pixelSize: 20
                }

            }

        }

    }

    /* RETÂNGULO SELEÇAO */

    Rectangle{
        id: recSelecao
        x: posXPlaca
        y: posYPlaca
        width: recPocoLado
        height: recPocoLado
        border {
            width: 2
            color: "#2DD7EE"
        }
        color: "transparent"

    }

    Rectangle{
        id: recSuperior
        width: 10
        height: 10
        radius: 10
        color: "#2DD7EE"
        anchors{
            verticalCenter: recSelecao.top
            horizontalCenter: recSelecao.horizontalCenter
        }
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.DragMoveCursor
            drag{ target: parent; axis: Drag.YAxis }
            onMouseYChanged: {
                if(drag.active){
                    alturaSelecionador = recSelecao.height - mouseY
                    posYSelecionador = recSelecao.y + mouseY
                    if(posYSelecionador >= posYPlaca){
                        recSelecao.height = Math.ceil(alturaSelecionador/recPocoLado)*recPocoLado;
                        recSelecao.y = Math.floor((posYSelecionador-posYPlaca)/recPocoLado)*recPocoLado + posYPlaca;
                    }
                }
            }
            onReleased: {
                rectangleButtons.auxInicial = (recSelecao.x - posXPlaca)/recPocoLado + 12*((recSelecao.y- posYPlaca)/recPocoLado)
                rectangleButtons.auxLado = recSelecao.width/recPocoLado
                rectangleButtons.auxBaixo = recSelecao.height/recPocoLado
                if(rectangleButtons.auxLado>1){
                    for(var k = (rectangleButtons.auxInicial+12*(rectangleButtons.auxBaixo-1)); k < (rectangleButtons.auxInicial+12*(rectangleButtons.auxBaixo-1)+rectangleButtons.auxLado); k++){
                        classLayout.settypeArr(classLayout.setPocoType(k, ""))
                        classLayout.setcolorWell(classLayout.returnColorWell(k, "white"))
                    }
                }
                for (var j=rectangleButtons.auxInicial; j<(rectangleButtons.auxInicial+rectangleButtons.auxLado);j++){
                    for(var i=j; i<(j+12*rectangleButtons.auxBaixo); i=i+12){
                        classLayout.settypeArr(classLayout.setPocoType(i, tipoSelecionado))
                        classLayout.setcolorWell(classLayout.returnColorWell(i, corSelecionada))
                    }
                }
                classLayout.setuniqueID(classLayout.returnUniqueID(popupTelaLayout.realPopupIndex))
            }

        }

    }

    Rectangle{
        id: recInferior
        width: 10
        height: 10
        radius: 10
        color: "#2DD7EE"
        anchors{
            verticalCenter: recSelecao.bottom
            horizontalCenter: recSelecao.horizontalCenter
        }
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.DragMoveCursor
            drag{ target: parent; axis: Drag.YAxis }
            onMouseYChanged: {
                if(drag.active){
                    alturaSelecionador = recSelecao.height + mouseY
                    if(alturaSelecionador+recSelecao.y<=480){
                        recSelecao.height = Math.ceil(alturaSelecionador/recPocoLado)*recPocoLado
                    }
                }
            }
            onReleased: {
                rectangleButtons.auxInicial = (recSelecao.x - posXPlaca)/recPocoLado + 12*((recSelecao.y- posYPlaca)/recPocoLado)
                rectangleButtons.auxLado = recSelecao.width/recPocoLado
                rectangleButtons.auxBaixo = recSelecao.height/recPocoLado
                if(rectangleButtons.auxLado>1){
                    for(var k = rectangleButtons.auxInicial; k < (rectangleButtons.auxInicial+rectangleButtons.auxLado); k++){
                        classLayout.settypeArr(classLayout.setPocoType(k, ""))
                        classLayout.setcolorWell(classLayout.returnColorWell(k, "white"))
                    }
                }
                for (var j=rectangleButtons.auxInicial; j<(rectangleButtons.auxInicial+rectangleButtons.auxLado);j++){
                    for(var i=j; i<(j+12*rectangleButtons.auxBaixo); i=i+12){
                        classLayout.settypeArr(classLayout.setPocoType(i, tipoSelecionado))
                        classLayout.setcolorWell(classLayout.returnColorWell(i, corSelecionada))
                    }
                }
                classLayout.setuniqueID(classLayout.returnUniqueID(popupTelaLayout.realPopupIndex))
            }

        }
    }

    Rectangle{
        id: recDireita
        width: 10
        height: 10
        radius: 10
        color: "#2DD7EE"
        anchors{
            verticalCenter: recSelecao.verticalCenter
            horizontalCenter: recSelecao.right
        }

        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.DragMoveCursor
            drag{ target: parent; axis: Drag.XAxis }
            onMouseXChanged: {
                if(drag.active){
                   larguraSelecionador = recSelecao.width + mouseX
                   if(larguraSelecionador+recSelecao.x<=700){
                        recSelecao.width = Math.ceil(larguraSelecionador/recPocoLado)*recPocoLado;
                   }

                }
            }
            onReleased: {
                rectangleButtons.auxInicial = (recSelecao.x - posXPlaca)/recPocoLado + 12*((recSelecao.y- posYPlaca)/recPocoLado)
                rectangleButtons.auxLado = recSelecao.width/recPocoLado
                rectangleButtons.auxBaixo = recSelecao.height/recPocoLado
                for (var j=rectangleButtons.auxInicial; j<(rectangleButtons.auxInicial+rectangleButtons.auxLado);j++){
                    for(var i=j; i<(j+12*rectangleButtons.auxBaixo); i=i+12){
                        classLayout.settypeArr(classLayout.setPocoType(i, tipoSelecionado))
                        classLayout.setcolorWell(classLayout.returnColorWell(i, corSelecionada))
                    }
                }
                classLayout.setuniqueID(classLayout.returnUniqueID(popupTelaLayout.realPopupIndex))
            }
        }

    }

    Rectangle{
        id: recEsquerda
        width: 10
        height: 10
        radius: 10
        color: "#2DD7EE"
        anchors{
            verticalCenter: recSelecao.verticalCenter
            horizontalCenter: recSelecao.left
        }
        MouseArea {
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            drag{ target: parent; axis: Drag.XAxis }
            onMouseXChanged: {
                if(drag.active){
                    larguraSelecionador = recSelecao.width - mouseX
                    posXSelecionador = recSelecao.x + mouseX
                    if(posXSelecionador >= posXPlaca){
                        recSelecao.width = Math.ceil(larguraSelecionador/recPocoLado)*recPocoLado;
                        recSelecao.x = Math.floor((posXSelecionador-posXPlaca)/recPocoLado)*recPocoLado + posXPlaca;
                    }

                }
            }
            onReleased: {
                rectangleButtons.auxInicial = (recSelecao.x - posXPlaca)/recPocoLado + 12*((recSelecao.y- posYPlaca)/recPocoLado)
                rectangleButtons.auxLado = recSelecao.width/recPocoLado
                rectangleButtons.auxBaixo = recSelecao.height/recPocoLado
                for (var j=rectangleButtons.auxInicial; j<(rectangleButtons.auxInicial+rectangleButtons.auxLado);j++){
                    for(var i=j; i<(j+12*rectangleButtons.auxBaixo); i=i+12){
                        classLayout.settypeArr(classLayout.setPocoType(i, tipoSelecionado))
                        classLayout.setcolorWell(classLayout.returnColorWell(i, corSelecionada))
                    }
                }
                classLayout.setuniqueID(classLayout.returnUniqueID(popupTelaLayout.realPopupIndex))
            }
        }

    }

     /* BOTÕES TIPOS DE POÇOS */

    Popup{
        id: popupCP
        parent: Overlay.overlay
        x: rectangleButtons.x + 80
        y: 0
        PopupCP {

        }

    }

    Popup{
        id: popupCN
        parent: Overlay.overlay
        x: rectangleButtons.x + 80
        y: 0
        PopupCN {

        }

    }

    Popup{
        id: popupCA
        parent: Overlay.overlay
        x: rectangleButtons.x + 80
        y: 0
        PopupCA {

        }

    }

    Popup{
        id: popupCQ
        parent: Overlay.overlay
        x: rectangleButtons.x + 80
        y: 0
        PopupCQ {

        }

    }


    Rectangle {
        id: rectangleButtons
        x: posXPlaca*12 + 25
        y: posYPlaca
        radius: 10
        width: 200
        height: 191
        color: "#E6E6FA"
        border.width: 2
        border.color: "#364b7f"

        property int auxInicial
        property int auxLado
        property int auxBaixo

        Rectangle{
            id: rectangleBC
            x: 75
            y: 68
            width: 55
            height: 55
            color: "#E6E6FA"
            border.width: 2
            border.color: "#E6E6FA"
            RoundButton {
                id: roundButton1
                anchors.centerIn: parent
                radius: 50
                width: 50
                height: 50
                hoverEnabled: true
                flat: false
                focusPolicy: Qt.ClickFocus
                transformOrigin: Item.TopLeft
                clip: false
                display: AbstractButton.TextOnly
                highlighted: true
                text: "BC"
                background: Rectangle{
                    radius: roundButton1.radius
                    color: "lightgray"
                }
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Branco")
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        rectangleBC.border.color = "#2DD7EE"
                        rectangleCA.border.color = "#E6E6FA"
                        rectangleCN.border.color = "#E6E6FA"
                        rectangleCP.border.color = "#E6E6FA"
                        rectangleCQ.border.color = "#E6E6FA"
                        rectangleDC.border.color = "#E6E6FA"
                        rectanglePD.border.color = "#E6E6FA"
                        rectangleVZ.border.color = "#E6E6FA"
                        tipoSelecionado = "BC"
                        corSelecionada = "lightgray"
                    }
                }


            }
        }

        Rectangle{
            id: rectangleVZ
            x: 75
            y: 128
            width: 55
            height: 55
            color: "#E6E6FA"
            border.width: 2
            border.color: "#E6E6FA"
            RoundButton {
                id: roundButton2
                anchors.centerIn: parent
                radius: 50
                width: 50
                height: 50
                text: "VZ"
                focusPolicy: Qt.ClickFocus
                clip: false
                hoverEnabled: true
                highlighted: true
                flat: false
                transformOrigin: Item.TopLeft
                display: AbstractButton.TextOnly
                background: Rectangle{
                    radius: roundButton1.radius
                    color: "white"
                }
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Vazio")
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        rectangleBC.border.color = "#E6E6FA"
                        rectangleCA.border.color = "#E6E6FA"
                        rectangleCN.border.color = "#E6E6FA"
                        rectangleCP.border.color = "#E6E6FA"
                        rectangleCQ.border.color = "#E6E6FA"
                        rectangleDC.border.color = "#E6E6FA"
                        rectanglePD.border.color = "#E6E6FA"
                        rectangleVZ.border.color = "#2DD7EE"
                        tipoSelecionado = ""
                        corSelecionada = "white"

                    }

                }


            }
        }


        Rectangle{
            id: rectangleCP
            x: 135
            y: 8
            width: 55
            height: 55
            color: "#E6E6FA"
            border.width: 2
            border.color: "#E6E6FA"
            RoundButton {
                id: roundButton3
                anchors.centerIn: parent
                radius: 50
                width: 50
                height: 50
                text: "CP"
                highlighted: true
                focusPolicy: Qt.ClickFocus
                hoverEnabled: true
                flat: false
                clip: false
                display: AbstractButton.TextOnly
                transformOrigin: Item.TopLeft
                background: Rectangle {
                    color: "pink"
                    radius: roundButton3.radius
                }
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Controle Positivo")
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        rectangleBC.border.color = "#E6E6FA"
                        rectangleCA.border.color = "#E6E6FA"
                        rectangleCN.border.color = "#E6E6FA"
                        rectangleCP.border.color = "#2DD7EE"
                        rectangleCQ.border.color = "#E6E6FA"
                        rectangleDC.border.color = "#E6E6FA"
                        rectanglePD.border.color = "#E6E6FA"
                        rectangleVZ.border.color = "#E6E6FA"
                        tipoSelecionado = "CP1"
                        corSelecionada = "pink"
                        popupCP.open()
                    }
                }

             }

        }


        Rectangle{
            id: rectangleCN
            x: 15
            y: 128
            width: 55
            height: 55
            color: "#E6E6FA"
            border.width: 2
            border.color: "#E6E6FA"
            RoundButton {
                id: roundButton4
                anchors.centerIn: parent
                radius: 50
                width: 50
                height: 50
                text: "CN"
                highlighted: true
                focusPolicy: Qt.ClickFocus
                transformOrigin: Item.TopLeft
                display: AbstractButton.TextOnly
                clip: false
                flat: false
                hoverEnabled: true
                background: Rectangle {
                    color: "blue"
                    radius: roundButton4.radius
                }
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Controle Negativo")
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        rectangleBC.border.color = "#E6E6FA"
                        rectangleCA.border.color = "#E6E6FA"
                        rectangleCN.border.color = "#2DD7EE"
                        rectangleCP.border.color = "#E6E6FA"
                        rectangleCQ.border.color = "#E6E6FA"
                        rectangleDC.border.color = "#E6E6FA"
                        rectanglePD.border.color = "#E6E6FA"
                        rectangleVZ.border.color = "#E6E6FA"
                        tipoSelecionado = "CN1"
                        corSelecionada = "blue"
                        popupCN.open()
                    }

                }

            }
        }


        Rectangle{
            id: rectanglePD
            x: 15
            y: 8
            width: 55
            height: 55
            color: "#E6E6FA"
            border.width: 2
            border.color: "#E6E6FA"
            RoundButton {
                id: roundButton5
                anchors.centerIn: parent
                radius: 50
                width: 50
                height: 50
                text: "PD"
                highlighted: true
                focusPolicy: Qt.ClickFocus
                hoverEnabled: true
                flat: false
                clip: false
                display: AbstractButton.TextOnly
                transformOrigin: Item.TopLeft
                background: Rectangle {
                    color: "yellow"
                    radius: roundButton5.radius
                }
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Amostra Padrão")
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        rectangleBC.border.color = "#E6E6FA"
                        rectangleCA.border.color = "#E6E6FA"
                        rectangleCN.border.color = "#E6E6FA"
                        rectangleCP.border.color = "#E6E6FA"
                        rectangleCQ.border.color = "#E6E6FA"
                        rectangleDC.border.color = "#E6E6FA"
                        rectanglePD.border.color = "#2DD7EE"
                        rectangleVZ.border.color = "#E6E6FA"
                        tipoSelecionado = "PD"
                        corSelecionada = "yellow"
                    }

                }

            }
        }


        Rectangle{
            id: rectangleCQ
            x: 135
            y: 68
            width: 55
            height: 55
            color: "#E6E6FA"
            border.width: 2
            border.color: "#E6E6FA"
            RoundButton {
                id: roundButton6
                anchors.centerIn: parent
                radius: 50
                width: 50
                height: 50
                text: "CQ"
                highlighted: true
                focusPolicy: Qt.ClickFocus
                transformOrigin: Item.TopLeft
                display: AbstractButton.TextOnly
                clip: false
                flat: false
                hoverEnabled: true
                background: Rectangle {
                    color: "green"
                    radius: roundButton6.radius
                }
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Controle de Qualidade")
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked:{
                        rectangleBC.border.color = "#E6E6FA"
                        rectangleCA.border.color = "#E6E6FA"
                        rectangleCN.border.color = "#E6E6FA"
                        rectangleCP.border.color = "#E6E6FA"
                        rectangleCQ.border.color = "#2DD7EE"
                        rectangleDC.border.color = "#E6E6FA"
                        rectanglePD.border.color = "#E6E6FA"
                        rectangleVZ.border.color = "#E6E6FA"
                        tipoSelecionado = "CQ1"
                        corSelecionada = "green"
                        popupCQ.open() }

                }

            }
        }


        Rectangle{
            id: rectangleDC
            x: 15
            y: 68
            width: 55
            height: 55
            color: "#E6E6FA"
            border.width: 2
            border.color: "#2DD7EE"
            RoundButton {
                id: roundButton8
                anchors.centerIn: parent
                radius: 50
                width: 50
                height: 50
                text: "DC"
                highlighted: true
                focusPolicy: Qt.ClickFocus
                hoverEnabled: true
                flat: false
                clip: false
                display: AbstractButton.TextOnly
                transformOrigin: Item.TopLeft
                background: Rectangle {
                    color: "purple"
                    radius: roundButton8.radius
                }
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Desconhecido")
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        rectangleBC.border.color = "#E6E6FA"
                        rectangleCA.border.color = "#E6E6FA"
                        rectangleCN.border.color = "#E6E6FA"
                        rectangleCP.border.color = "#E6E6FA"
                        rectangleCQ.border.color = "#E6E6FA"
                        rectangleDC.border.color = "#2DD7EE"
                        rectanglePD.border.color = "#E6E6FA"
                        rectangleVZ.border.color = "#E6E6FA"
                        tipoSelecionado = "DC"
                        corSelecionada = "purple"
                    }
                }

            }
        }

        Rectangle{
            id: rectangleCA
            x: 75
            y: 8
            width: 55
            height: 55
            color: "#E6E6FA"
            border.width: 2
            border.color: "#E6E6FA"
            RoundButton {
                id: roundButton9
                anchors.centerIn: parent
                width: 50
                height: 50
                radius: 50
                text: "CA"
                highlighted: true
                focusPolicy: Qt.ClickFocus
                hoverEnabled: true
                flat: false
                clip: false
                display: AbstractButton.TextOnly
                transformOrigin: Item.TopLeft
                background: Rectangle {
                    color: "lightblue"
                    radius: roundButton9.radius
                }
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Calibrador")
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        rectangleBC.border.color = "#E6E6FA"
                        rectangleCA.border.color = "#2DD7EE"
                        rectangleCN.border.color = "#E6E6FA"
                        rectangleCP.border.color = "#E6E6FA"
                        rectangleCQ.border.color = "#E6E6FA"
                        rectangleDC.border.color = "#E6E6FA"
                        rectanglePD.border.color = "#E6E6FA"
                        rectangleVZ.border.color = "#E6E6FA"
                        tipoSelecionado = "CA1"
                        corSelecionada = "lightblue"
                        popupCA.open()
                    }
                }

                }
        }

        Rectangle{
            id: rectangleCLR
            x: 135
            y: 128
            width: 55
            height: 55
            color: "#E6E6FA"
            border.width: 2
            border.color: "#E6E6FA"
            RoundButton {
                id: roundButton10
                anchors.centerIn: parent
                width: 50
                height: 50
                radius: 50
                text: "CLR"
                highlighted: true
                focusPolicy: Qt.ClickFocus
                hoverEnabled: true
                flat: false
                clip: false
                display: AbstractButton.TextOnly
                transformOrigin: Item.TopLeft
                background: Rectangle {
                    color: "red"
                    radius: roundButton10.radius
                }
                ToolTip.visible: hovered
                ToolTip.text: qsTr("Limpar")
                MouseArea{
                    anchors.fill: parent
                    cursorShape: Qt.PointingHandCursor
                    onClicked: {
                        rectangleBC.border.color = "#E6E6FA"
                        rectangleCA.border.color = "#E6E6FA"
                        rectangleCN.border.color = "#E6E6FA"
                        rectangleCP.border.color = "#E6E6FA"
                        rectangleCQ.border.color = "#E6E6FA"
                        rectangleDC.border.color = "#2DD7EE"
                        rectanglePD.border.color = "#E6E6FA"
                        rectangleVZ.border.color = "#E6E6FA"
                        for(var i=0; i<96; i++){
                            classLayout.settypeArr(classLayout.setPocoType(i, ""))
                            classLayout.setcolorWell(classLayout.returnColorWell(i, "white"))
                            classLayout.setsubjID(classLayout.returnSubjID(i, ""))
                            classLayout.setsampleID(classLayout.returnSampleID(i, ""))
                        }
                        classLayout.setuniqueID(classLayout.returnUniqueID(popupTelaLayout.realPopupIndex))
                        corSelecionada = "purple"
                        tipoSelecionado = "DC"
                        recSelecao.x = posXPlaca
                        recSelecao.y = posYPlaca
                        recSelecao.width = recPocoLado
                        recSelecao.height = recPocoLado
                    }
                    onPressed: {
                        rectangleCLR.border.color = "#2DD7EE"
                    }
                    onReleased:{
                        rectangleCLR.border.color = "#E6E6FA"
                    }
                }

                }
        }


    }

    /* FATOR DE CALIBRAÇÃO */
    Rectangle{
        id: rectangleFatoresCalib
        x: posXPlaca*12 + 25
        y: 398
        radius: 10
        height: 140
        width: 200
        color: "#E6E6FA"
        border.width: 2
        border.color: "#364b7f"
        Text {
            id: fatorCalib
            width: 110
            height: 12
            x: 24
            y: 12
            text: "FATORES DE CALIBRAÇÃO"
            font.pixelSize: 12
            font.family: "Verdana"

        }

        Text{
            id: textCA1
            x: 27
            y: 40
            text: "CA1:"
            font.pixelSize: 12
            font.family: "Verdana"

        }

        TextInput {
            id: fatorCalib_CA1_input
            width: 110
            height: 12
            x: 61
            y: 41
            text: classCutOff.fc_CA[0].toFixed(2)
            font.pixelSize: 12
            font.family: "Verdana"
            onEditingFinished: {
                classCutOff.setfc_CA(classCutOff.returnfc_CA(0, text))
            }
        }

        Text{
            id: textCA2
            x: 113
            y: 40
            width: 28
            height: 14
            text: "CA2:"
            font.pixelSize: 12
            font.family: "Verdana"

        }

        TextInput {
            id: fatorCalib_CA2_input
            width: 110
            height: 12
            x: 147
            y: 41
            text: classCutOff.fc_CA[1].toFixed(2)
            font.pixelSize: 12
            font.family: "Verdana"
            onEditingFinished: {
                classCutOff.setfc_CA(classCutOff.returnfc_CA(1, text))
            }

        }

        Text{
            id: textCA3
            x: 27
            y: 71
            width: 28
            height: 13
            text: "CA3:"
            font.pixelSize: 12
            font.family: "Verdana"

        }

        TextInput {
            id: fatorCalib_CA3_input
            width: 110
            height: 12
            x: 61
            y: 72
            text: classCutOff.fc_CA[2].toFixed(2)
            font.pixelSize: 12
            font.family: "Verdana"
            onEditingFinished: {
                classCutOff.setfc_CA(classCutOff.returnfc_CA(2, text))
            }

        }

        Text{
            id: textCA4
            x: 113
            y: 71
            text: "CA4:"
            font.pixelSize: 12
            font.family: "Verdana"

        }

        TextInput {
            id: fatorCalib_CA4_input
            width: 110
            height: 12
            x: 147
            y: 72
            text: classCutOff.fc_CA[3].toFixed(2)
            font.pixelSize: 12
            font.family: "Verdana"
            onEditingFinished: {
                classCutOff.setfc_CA(classCutOff.returnfc_CA(3, text))
            }

        }

        Text{
            id: textCA5
            x: 27
            y: 101
            text: "CA5:"
            font.pixelSize: 12
            font.family: "Verdana"

        }

        TextInput {
            id: fatorCalib_CA5_input
            width: 110
            height: 12
            x: 61
            y: 103
            text: classCutOff.fc_CA[4].toFixed(2)
            font.pixelSize: 12
            font.family: "Verdana"
            onEditingFinished: {
                classCutOff.setfc_CA(classCutOff.returnfc_CA(4, text))
            }

        }

    }

}



/*##^##
Designer {
    D{i:0;autoSize:true;height:480;width:640}
}
##^##*/
