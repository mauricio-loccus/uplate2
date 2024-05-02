import QtQuick 2.15
import QtQuick.Controls

Item {
    width: 1366
    height: 768

    property bool done: false


    Timer
    {
        interval: 1000
        repeat: true
        running: true

        property int  progress : 0
        onTriggered: {
            progress = progress + 1

            if(progress >= 3) {
                console.log("done loading")
                done = true
                running = false
            }
        }
    }


    Image {
        id: boot
        anchors.fill: parent
        source: "qrc:/images/boot.png"
        fillMode: Image.PreserveAspectCrop
    }



    BusyIndicator {
        x: 648
        y: 498
        width: 53
        height: 53
        running: true
    }

}
