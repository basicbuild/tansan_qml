//import QtQuick 2.0
import QtQuick 2.12

MouseArea {
    id: id_y_mouse_area
    objectName: "YMouseArea.qml"
    acceptedButtons: Qt.LeftButton
    hoverEnabled: false
    scrollGestureEnabled: false

    property bool hotAreaTesting: false // todo use config file open

    function qmlCreateComponent(qmlName) {
        return Qt.createComponent(("qrc:/qml/%1.qml").arg(qmlName))
    }

    onClicked: {
        console.log("                                                        ")
        console.log("YMouseArea.qml===", objectName, "===clicked----------------")
    }

    Loader {
        anchors.fill: parent
       // active: hotAreaTesting && id_y_mouse_area.enabled
         active: true
        sourceComponent: Rectangle {
            id: id_hot_area_test
            color: "#80FF0000"
        }
    }

    property bool isPressAndHold: false

    onPressAndHold: {
        isPressAndHold = true
    }

    onReleased: {
        isPressAndHold = false
    }
}
