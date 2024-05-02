import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {

    Rectangle{
        id: rectanglePopupCQ1
        color: "#B0C4DE"

        RoundButton {
            id: roundButtonCQ1
            x: 25
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CQ1"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "green"
                radius: roundButtonCQ1.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CQ1"
                    corSelecionada = "green"
                }
            }

        }

        RoundButton {
            id: roundButtonCQ2
            x: 62
            y: 25
            radius: 50
            width: 50
            height: 50
            text: "CQ2"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "green"
                radius: roundButtonCQ2.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CQ2"
                    corSelecionada = "green"
                }

            }

        }

        RoundButton {
            id: roundButtonCQ3
            x: 100
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CQ3"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "green"
                radius: roundButtonCQ3.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CQ3"
                    corSelecionada = "green"
                }
            }

        }

        RoundButton {
            id: roundButtonCQ4
            x: 137
            y: 25
            radius: 50
            width: 50
            height: 50
            text: "CQ4"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "green"
                radius: roundButtonCQ4.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CQ4"
                    corSelecionada = "green"
                }
            }

        }

        RoundButton {
            id: roundButtonCQ5
            x: 175
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CQ5"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "green"
                radius: roundButtonCQ5.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CQ5"
                    corSelecionada = "green"
                }
            }

        }





    }


}
