import QtQuick 2.0
import QtQuick.Window 2.2

 Window {
    id: id_item_root
    visible: true
    width: 356
    height: 320
    title: qsTr("Test")
    //z: id_item_root + 1

    TMouseAreaTest {
        id: id_button
        anchors.fill: parent
        signal validClicked()

        readonly property alias buttonTimer: id_button_timer

        onClicked: {
            console.warn("YButtonBaseMouseArea.qml===id_button===onClicked1")
           // id_button_timer.stop()

            if (!id_button_timer.running) {
                console.warn("YButtonBaseMouseArea.qml===id_button===onClicked2")
                validClicked()
            }
            console.warn("YButtonBaseMouseArea.qml===id_button===onClicked3")
            id_button_timer.restart()
        }
        objectName: "YButtonBaseMouseArea.qml_id_button"

        Timer {
            id: id_button_timer
            interval: 200
            objectName: "YButtonBaseMouseArea.qml_id_button_timer"

            onRunningChanged: {
                console.log("YTimer.qml===child===timer===objectName: ",
                            objectName, "===running: ", (running ? "start" : "stop--------------------"))
            }
        }
    }

//    Item{
//        anchors.fill: parent
//        //color: "#000000"

//        Text {
//            id: id_component_title
//            text: qsTr("组件封装组件封装组件封装组件封装组件封装组件封装组件封装")
//            anchors.top: parent.top
//            anchors.topMargin: 20
//            width: 70
//            wrapMode: Text.Wrap
//            horizontalAlignment: Text.Center
//        }
//    }
}
