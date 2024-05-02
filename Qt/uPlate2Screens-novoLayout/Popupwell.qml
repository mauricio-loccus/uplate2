import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import QtQuick.Layouts 1.12
import QtQuick.Layouts

    ColumnLayout {
        id: columnLayout

    
        Rectangle {
            id: rectangle1
            width: 200
            height: 24
            color: "#E6E6FA"
            border.color: "#1a5276"
            border.width: 2
       

            Text {
                id: well_id_value
                width: 72
                height: 12
                color: "black"
                text: classLayout.wellID
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: well_id_label.right
                font.pixelSize: 13
                anchors.verticalCenterOffset: 0
                anchors.leftMargin: 8
                font.family: "Verdana"
            }

            Text {
                id: well_id_label
                width: 50
                height: 13
                color: "black"
                text: qsTr("Well ID:")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
                anchors.verticalCenterOffset: 0
                anchors.horizontalCenterOffset: -67
                anchors.horizontalCenter: parent.horizontalCenter
                font.family: "Verdana"
            }
        }

        Rectangle {
            id: rectangle2
            width: 200
            height: 24
            color: "#E6E6FA"
            border.color: "#1a5276"
            border.width: 2
            
            Text {
                id: unique_id_value
                width: 60
                height: 12
                color: "black"
                text: classLayout.uniqueID
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: unique_id_label.right
                font.pixelSize: 12
                anchors.leftMargin: 8
                anchors.verticalCenterOffset: 0
                font.family: "Verdana"
            }

            Text {
                id: unique_id_label
                x: 8
                width: 67
                height: 12
                color: "black"
                text: qsTr("Unique ID:")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.horizontalCenter
                font.pixelSize: 12
                anchors.verticalCenterOffset: 0
                anchors.leftMargin: -92
                font.family: "Verdana"
            }
        }

        Rectangle {
            id: rectangle3
            width: 200
            height: 24
            color: "#E6E6FA"
            border.color: "#1a5276"
            border.width: 2
        

            Text {
                id: sample_id_label
                x: 8
                y: 1
                width: 80
                height: 12
                color: "black"
                text: qsTr("Sample ID:")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 8
                font.family: "Verdana"
            }

            TextInput {
                id: sample_id_input
                y: 6
                width: 110
                height: 12
                color: "black"
                text: classLayout.sampleID[popupTelaLayout.realPopupIndex]
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: sample_id_label.right
                font.pixelSize: 12
                anchors.leftMargin: -9
                anchors.verticalCenterOffset: 0
                font.family: "Verdana"
                onTextChanged: {
                    classLayout.setsampleID(classLayout.returnSampleID(popupTelaLayout.realPopupIndex, text))
                }
            }
        }

        Rectangle {
            id: rectangle4
            width: 200
            height: 24
            color: "#E6E6FA"
            border.color: "#1a5276"
            border.width: 2
        
            Text {
                id: subject_id_label
                x: 8
                y: 1
                width: 70
                height: 12
                color: "black"
                text: qsTr("Subject ID:")
                anchors.verticalCenter: parent.verticalCenter
                font.pixelSize: 12
                anchors.verticalCenterOffset: -1
                font.family: "Verdana"
            }

            TextInput {
                id: subject_id_input
                x: 84
                width: 110
                height: 12
                color: "black"
                text: classLayout.subjID[popupTelaLayout.realPopupIndex]
                anchors.verticalCenter: parent.verticalCenter
                anchors.right: subject_id_label.right
                font.pixelSize: 12
                anchors.rightMargin: -116
                anchors.verticalCenterOffset: 0
                font.family: "Verdana"
                onTextChanged: {
                    classLayout.setsubjID(classLayout.returnSubjID(popupTelaLayout.realPopupIndex, text))
                }
            }
        }

        Rectangle {
            id: rectangle5
            width: 200
            height: 24
            color: "#E6E6FA"
            border.color: "#1a5276"
            border.width: 2


            Text {
                id: type_id_label
                x: 8
                y: 1
                width: 34
                height: 12
                color: "black"
                text: qsTr("Tipo:")
                anchors.verticalCenter: parent.verticalCenter
                anchors.left: parent.left
                font.pixelSize: 12
                anchors.leftMargin: 8
                font.family: "Verdana"
            }

            Text {
                id: type_id_value
                x: 71
                y: 2
                width: 72
                height: 12
                color: "black"
                text: classLayout.typeArr[popupTelaLayout.realPopupIndex]
                anchors.verticalCenter: type_id_label.verticalCenter
                anchors.right: type_id_label.right
                font.pixelSize: 12
                anchors.rightMargin: -80
                anchors.verticalCenterOffset: 0
                font.family: "Verdana"
            }
        }
    }
