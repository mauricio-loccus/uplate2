import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {
    id: itemTelaResultados1


    function oneVisible(number) {

        switch (number) {

        case 1:
            telaExperimento1.visible = true
            telaExperimento2.visible = false
            telaExperimento3.visible = false
            telaExperimento1.botaoResultadosAbs.clicked()

            break;

        case 2:
            telaExperimento1.visible = false
            telaExperimento2.visible = true
            telaExperimento3.visible = false
            telaExperimento2.botaoResultadosAbs.clicked()

            break;

        case 3:
            telaExperimento1.visible = false
            telaExperimento2.visible = false
            telaExperimento3.visible = true
            telaExperimento3.botaoResultadosAbs.clicked()

            break;

        default:
            telaExperimento1.visible = true
            telaExperimento2.visible = false
            telaExperimento3.visible = false
            telaExperimento1.botaoResultadosAbs.clicked()

            break;

        }

    }

    Component.onCompleted: oneVisible(1)

    property alias filtronum: comboboxFiltros.currentIndex

    ComboBox{
        id: comboboxFiltros
        x: 50
        y: 0
        model: ["Filtro 1", "Filtro 2", "Filtro 1|2"]
        onCurrentIndexChanged: {
           oneVisible(currentIndex+1)
        }
    }

    TelaResultados2 {
        id: telaExperimento1
        x: -6
        y: 71
        width: 1015
        height: 455
        numFiltro: 0
    }

    TelaResultados2 {
        id: telaExperimento2
        x: -6
        y: 71
        width: 1015
        height: 455
        visible: false
        numFiltro: 1
    }

    TelaResultados2 {
        id: telaExperimento3
        x: -6
        y: 71
        width: 1015
        height: 455
        visible: false
        numFiltro: 2
    }




}

/*##^##
Designer {
    D{i:0;autoSize:true;height:680;width:1024}
}
##^##*/
