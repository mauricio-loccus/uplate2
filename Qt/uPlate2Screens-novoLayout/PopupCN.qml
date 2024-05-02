import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {

    Rectangle{
        id: rectanglePopupCN
        color: "#B0C4DE"
        RoundButton {
            id: roundButtonCN1
            x: 25
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CN1"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "blue"
                radius: roundButtonCN1.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CN1"
                    corSelecionada = "blue"
                }
            }

        }

        RoundButton {
            id: roundButtonCN2
            x: 62
            y: 25
            radius: 50
            width: 50
            height: 50
            text: "CN2"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "blue"
                radius: roundButtonCN2.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CN2"
                    corSelecionada = "blue"
                }
            }

        }

        RoundButton {
            id: roundButtonCN3
            x: 100
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CN3"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "blue"
                radius: roundButtonCN3.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CN3"
                    corSelecionada = "blue"
                }
            }

        }

        RoundButton {
            id: roundButtonCN4
            x: 137
            y: 25
            radius: 50
            width: 50
            height: 50
            text: "CN4"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "blue"
                radius: roundButtonCN4.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CN4"
                    corSelecionada = "blue"
                }
            }

        }

        RoundButton {
            id: roundButtonCN5
            x: 175
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CN5"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "blue"
                radius: roundButtonCN5.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CN5"
                    corSelecionada = "blue"
                }
            }

        }




    }


}

