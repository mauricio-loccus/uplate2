import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12

Item{


Rectangle{

    id: rectangleConfFiltros
    radius: 10
    x: 300
    y: 8
    height: 500
    width: 560
    color: "#E6E6FA"
    border.width: 2
    border.color: "#364b7f"

    Rectangle{
        id: rectangleFilto1
        radius: 50
        height: 80
        width: 80
        color: "#5edaab"
        border.width: 2
        border.color: "#5edac9"
        x: 5
        y: 50
        TextInput{
            id: textFieldFiltro1
            width: 80
            height: 40
           validator: RegularExpressionValidator { regularExpression: /[0-9\t]+/ }
            anchors.fill: parent
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 24
            anchors.bottomMargin: 24
            font.pixelSize: 22
            text: classConfigFilt.configFilt[0]
        }
    }

    Text{
        id: textFiltro1
        text: "Filtro 1"
        font.pixelSize: 22
        anchors{
            bottom: rectangleFilto1.top
            horizontalCenter: rectangleFilto1.horizontalCenter
        }
   }

    Text{
        id: textFiltro1nm
        text: "nm"
        font.pixelSize: 22
        anchors{
            verticalCenter: rectangleFilto1.verticalCenter
            left: rectangleFilto1.right
        }
   }

    Rectangle{
        id: rectangleFilto2
        radius: 50
        height: 80
        width: 80
        color: "#5edaab"
        border.width: 2
        border.color: "#5edac9"
        x: 150
        y: 50
        TextInput{
            id: textFieldFiltro2
            width: 80
            height: 40
            validator: RegularExpressionValidator { regularExpression: /[0-9\t]+/ }
            anchors.fill: parent
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 24
            anchors.bottomMargin: 24
            font.pixelSize: 22
            text: classConfigFilt.configFilt[1]
        }
    }

    Text{
        id: textFiltro2
        text: "Filtro 2"
        font.pixelSize: 22
        anchors{
            bottom: rectangleFilto2.top
            horizontalCenter: rectangleFilto2.horizontalCenter
        }
   }

    Text{
        id: textFiltro2nm
        text: "nm"
        font.pixelSize: 22
        anchors{
            verticalCenter: rectangleFilto2.verticalCenter
            left: rectangleFilto2.right
        }
   }

    Rectangle{
        id: rectangleFilto3
        radius: 50
        height: 80
        width: 80
        color: "#5edaab"
        border.width: 2
        border.color: "#5edac9"
        x: 295
        y: 50
        TextInput{
            id: textFieldFiltro3
            width: 80
            height: 40
            validator: RegularExpressionValidator { regularExpression: /[0-9\t]+/ }
            anchors.fill: parent
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 24
            anchors.bottomMargin: 24
            font.pixelSize: 22
            text: classConfigFilt.configFilt[2]
        }
    }

    Text{
        id: textFiltro3
        text: "Filtro 3"
        font.pixelSize: 22
        anchors{
            bottom: rectangleFilto3.top
            horizontalCenter: rectangleFilto3.horizontalCenter
        }
   }

    Text{
        id: textFiltro3nm
        text: "nm"
        font.pixelSize: 22
        anchors{
            verticalCenter: rectangleFilto3.verticalCenter
            left: rectangleFilto3.right
        }
   }

    Rectangle{
        id: rectangleFilto4
        radius: 50
        height: 80
        width: 80
        color: "#5edaab"
        border.width: 2
        border.color: "#5edac9"
        x: 440
        y: 50
        TextInput{
            id: textFieldFiltro4
            width: 80
            height: 40
            validator: RegularExpressionValidator { regularExpression: /[0-9\t]+/ }
            anchors.fill: parent
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 24
            anchors.bottomMargin: 24
            font.pixelSize: 22
            text: classConfigFilt.configFilt[3]
        }
    }

    Text{
        id: textFiltro4
        text: "Filtro 4"
        font.pixelSize: 22
        anchors{
            bottom: rectangleFilto4.top
            horizontalCenter: rectangleFilto4.horizontalCenter
        }
   }

    Text{
        id: textFiltro4nm
        text: "nm"
        font.pixelSize: 22
        anchors{
            verticalCenter: rectangleFilto4.verticalCenter
            left: rectangleFilto4.right
        }
   }

    Rectangle{
        id: rectangleFilto5
        radius: 50
        height: 80
        width: 80
        color: "#5edaab"
        border.width: 2
        border.color: "#5edac9"
        x: 5
        y: 250
        TextInput{
            id: textFieldFiltro5
            width: 80
            height: 40
            validator: RegularExpressionValidator { regularExpression: /[0-9\t]+/ }
            anchors.fill: parent
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 24
            anchors.bottomMargin: 24
            font.pixelSize: 22
            text: classConfigFilt.configFilt[4]
        }
    }

    Text{
        id: textFiltro5
        text: "Filtro 5"
        font.pixelSize: 22
        anchors{
            bottom: rectangleFilto5.top
            horizontalCenter: rectangleFilto5.horizontalCenter
        }
   }

    Text{
        id: textFiltro5nm
        text: "nm"
        font.pixelSize: 22
        anchors{
            verticalCenter: rectangleFilto5.verticalCenter
            left: rectangleFilto5.right
        }
   }

    Rectangle{
        id: rectangleFilto6
        radius: 50
        height: 80
        width: 80
        color: "#5edaab"
        border.width: 2
        border.color: "#5edac9"
        x: 150
        y: 250
        TextInput{
            id: textFieldFiltro6
            width: 80
            height: 40
            validator: RegularExpressionValidator { regularExpression: /[0-9\t]+/ }
            anchors.fill: parent
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 24
            anchors.bottomMargin: 24
            font.pixelSize: 22
            text: classConfigFilt.configFilt[5]
        }
    }

    Text{
        id: textFiltro6
        text: "Filtro 6"
        font.pixelSize: 22
        anchors{
            bottom: rectangleFilto6.top
            horizontalCenter: rectangleFilto6.horizontalCenter
        }
   }

    Text{
        id: textFiltro6nm
        text: "nm"
        font.pixelSize: 22
        anchors{
            verticalCenter: rectangleFilto6.verticalCenter
            left: rectangleFilto6.right
        }
   }

    Rectangle{
        id: rectangleFilto7
        radius: 50
        height: 80
        width: 80
        color: "#5edaab"
        border.width: 2
        border.color: "#5edac9"
        x: 295
        y: 250
        TextInput{
            id: textFieldFiltro7
            width: 80
            height: 40
            validator: RegularExpressionValidator { regularExpression: /[0-9\t]+/ }
            anchors.fill: parent
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 24
            anchors.bottomMargin: 24
            font.pixelSize: 22
            text: classConfigFilt.configFilt[6]
        }
    }

    Text{
        id: textFiltro7
        text: "Filtro 7"
        font.pixelSize: 22
        anchors{
            bottom: rectangleFilto7.top
            horizontalCenter: rectangleFilto7.horizontalCenter
        }
   }

    Text{
        id: textFiltro7nm
        text: "nm"
        font.pixelSize: 22
        anchors{
            verticalCenter: rectangleFilto7.verticalCenter
            left: rectangleFilto7.right
        }
   }

    Rectangle{
        id: rectangleFilto8
        radius: 50
        height: 80
        width: 80
        color: "#5edaab"
        border.width: 2
        border.color: "#5edac9"
        x: 440
        y: 250
        TextInput{
            id: textFieldFiltro8
            width: 80
            height: 40
            validator: RegularExpressionValidator { regularExpression: /[0-9\t]+/ }
            anchors.fill: parent
            anchors.rightMargin: 15
            anchors.leftMargin: 15
            anchors.topMargin: 24
            anchors.bottomMargin: 24
            font.pixelSize: 22
            text: classConfigFilt.configFilt[7]

        }
    }

    Text{
        id: textFiltro8
        text: "Filtro 8"
        font.pixelSize: 22
        anchors{
            bottom: rectangleFilto8.top
            horizontalCenter: rectangleFilto8.horizontalCenter
        }
   }

    Text{
        id: textFiltro8nm
        text: "nm"
        font.pixelSize: 22
        anchors{
            verticalCenter: rectangleFilto8.verticalCenter
            left: rectangleFilto8.right
        }
   }

    Rectangle{
        id: rectangleSalvar
        width: 100
        height: 40
        radius: 5
        color: "#CD5C5C"
        x: 230
        y: 420
        border.width: 3
        border.color: "#CD5C5C"
        Text {
            color: "white"
            text: "Salvar"
            font.pixelSize: 17
            anchors.centerIn: parent
        }
        MouseArea{
            anchors.fill: parent
            cursorShape: Qt.PointingHandCursor
            onClicked: {
                classConfigFilt.set_configFilt(classConfigFilt.return_configFilt(textFieldFiltro1.text, textFieldFiltro2.text, textFieldFiltro3.text, textFieldFiltro4.text, textFieldFiltro5.text, textFieldFiltro6.text, textFieldFiltro7.text, textFieldFiltro8.text))
                classConfigFilt.salvarConfig();
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
