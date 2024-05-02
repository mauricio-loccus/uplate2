import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {

    Rectangle{
        id: rectanglePopupCP
        color: "#B0C4DE"

        RoundButton {
            id: roundButtonCP1
            x: 25
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CP1"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "pink"
                radius: roundButtonCP1.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CP1"
                    corSelecionada = "pink"
                }
            }

        }

        RoundButton {
            id: roundButtonCP2
            x: 62
            y: 25
            radius: 50
            width: 50
            height: 50
            text: "CP2"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "pink"
                radius: roundButtonCP2.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CP2"
                    corSelecionada = "pink"
                }
            }

        }

        RoundButton {
            id: roundButtonCP3
            x: 100
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CP3"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "pink"
                radius: roundButtonCP3.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CP3"
                    corSelecionada = "pink"
                }
            }

        }

        RoundButton {
            id: roundButtonCP4
            x: 137
            y: 25
            radius: 50
            width: 50
            height: 50
            text: "CP4"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "pink"
                radius: roundButtonCP4.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CP4"
                    corSelecionada = "pink"
                }
            }

        }

        RoundButton {
            id: roundButtonCP5
            x: 175
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CP5"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "pink"
                radius: roundButtonCP5.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CP5"
                    corSelecionada = "pink"
                }
            }

        }





    }


}
