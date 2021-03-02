import QtQuick 2.0
import QtQuick.Window 2.2

 Window {
    id: id_item_root
    visible: true
    width: 356
    height: 320
    title: qsTr("Test")
    //z: id_item_root + 1

    Item{
        anchors.fill: parent
        //color: "#000000"

        Text {
            id: id_component_title
            text: qsTr("组件封装组件封装组件封装组件封装组件封装组件封装组件封装")
            anchors.top: parent.top
            anchors.topMargin: 20
            width: 70
            wrapMode: Text.Wrap
            horizontalAlignment: Text.Center
        }
    }
}
