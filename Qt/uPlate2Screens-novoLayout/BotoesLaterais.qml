import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.12
import QtQuick.Layouts 1.12
import Qt.labs.platform 1.1


Rectangle{
    id: botoesLaterais
    anchors{
        left: parent.left
        verticalCenter: parent.verticalCenter
    }
    height: 600
    width: 100
    color: "#131929"

    Component.onCompleted: {
        gridViewBotoesLaterais.contentItem.children[0].border.color = "#2DD7EE"
    }


    ListModel{
        id: listaBotoesLaterais
        //ListElement { name: "Conectar"; page: "TelaConectar.qml"; barra: "BarraSuperiorPadrao.qml"; lateral:"BotoesLaterais.qml"}
        ListElement { name: "Experimento"; page: "TelaExperimentoGeral.qml"; barra: "BarraSuperiorExperimento.qml"; lateral:"BotoesLaterais.qml" }
        ListElement { name: "Layout"; page: "TelaLayout.qml"; barra: "BarraSuperiorPadrao.qml"; lateral:"BotoesLaterais.qml" }
        ListElement { name: "Resultados"; page: "TelaResultados1.qml"; barra: "BarraSuperiorPadrao.qml"; lateral:"BotoesLaterais.qml" }
        ListElement { name: "Relatórios"; page: "TelaExportar.qml"; barra: "BarraSuperiorPadrao.qml"; lateral:"BotoesLaterais.qml" }
    }

    GridView{
        id: gridViewBotoesLaterais
        anchors.fill: parent
        model: listaBotoesLaterais
        cellHeight: 150
        cellWidth: 100

        delegate: Rectangle{
            width: 100
            height: 100
            radius: 5
            color: "#131929"
            border.width: 2
            border.color: "white"
            Text {
                color: "white"
                text: name
                anchors.centerIn: parent
                font.pixelSize: 16
             }

         MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    for(var i=0; i<4; i++){
                        gridViewBotoesLaterais.contentItem.children[i].border.color = "white"
                    }
                    border.color = "#2DD7EE"
                    loaderBarraSuperior.source = barra
                    loaderInicio.source = page
                    loaderLateral.source = lateral
                }
         }

        }




    }

}
