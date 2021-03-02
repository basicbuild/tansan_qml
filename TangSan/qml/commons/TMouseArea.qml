import QtQuick 2.12

//The value of 'objectName' shoud be set, for hot area test
MouseArea{
    id: id_t_mouse_area
    objectName: "TMouseArea.qml"
    acceptedButtons: Qt.LeftButton
    hoverEnabled: false  // 默认false，只有按下鼠标键时才处理鼠标事件，为true时即使没有按下鼠标键也会作相应的处理
    scrollGestureEnabled: false // 默认为ture，false 只有当滚轮事件来自带有滚轮的实际鼠标时，才会发出滚轮信号

    property bool isPressAndHold: false

    function qmlCreateComponent(qmlName){
        return Qt.createComponent("qrc:/qml/%1.qml").arg(qmlName)
    }

    // 鼠标单击事件
    onClicked: {
        console.log("TMouseArea.qml===", objectName, "===clicked")
    }

    // 鼠标长按事件
    onPressAndHold: {
        isPressAndHold = true
    }

    // 鼠标释放事件
    onReleased: {
        isPressAndHold = false
    }
}
