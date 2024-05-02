import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item {

    Rectangle{
        id: rectanglePopupCA
        color: "#B0C4DE"
        RoundButton {
            id: roundButtonCA1
            x: 25
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CA1"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "lightblue"
                radius: roundButtonCA1.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CA1"
                    corSelecionada = "lightblue"
                }
            }

        }

        RoundButton {
            id: roundButtonCA2
            x: 62
            y: 25
            radius: 50
            width: 50
            height: 50
            text: "CA2"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "lightblue"
                radius: roundButtonCA2.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CA2"
                    corSelecionada = "lightblue"
                }
            }


        }

        RoundButton {
            id: roundButtonCA3
            x: 100
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CA3"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "lightblue"
                radius: roundButtonCA3.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CA3"
                    corSelecionada = "lightblue"
                }
            }

            }


        RoundButton {
            id: roundButtonCA4
            x: 137
            y: 25
            radius: 50
            width: 50
            height: 50
            text: "CA4"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "lightblue"
                radius: roundButtonCA4.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CA4"
                    corSelecionada = "lightblue"
                }
            }


        }

        RoundButton {
            id: roundButtonCA5
            x: 170
            y: 75
            radius: 50
            width: 50
            height: 50
            text: "CA5"
            highlighted: true
            focusPolicy: Qt.ClickFocus
            hoverEnabled: false
            flat: false
            clip: false
            display: AbstractButton.TextOnly
            transformOrigin: Item.TopLeft
            background: Rectangle {
                color: "lightblue"
                radius: roundButtonCA5.radius
            }
            MouseArea{
                anchors.fill: parent
                cursorShape: Qt.PointingHandCursor
                onClicked: {
                    tipoSelecionado = "CA5"
                    corSelecionada = "lightblue"
                }

            }

        }




    }


}
