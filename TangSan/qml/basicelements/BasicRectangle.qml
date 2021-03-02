import QtQuick 2.0
import QtQuick.Window 2.2
import QtGraphicalEffects 1.0

Window {
    id: id_item_root
    visible: true
    width: 356
    height: 320

    Rectangle {
        id: id_textbook_delegate_item_root
        width:  150
        height: 150
//        anchors.top: parent.top
//        //anchors.topMargin: 10
//        anchors.bottom: parent.bottom
//        //anchors.bottomMargin: 10
//        anchors.left: parent.left
//        //anchors.leftMargin: 10
//        anchors.right: parent.right
//       // anchors.rightMargin: 10

      //  anchors.margins: 10

        radius: 8
        opacity:  0.6
        color: "#000000"

//        Rectangle {
//            width: parent.width
//            height: 52
//            anchors.bottom: parent.bottom
//            color: "#000000"
//            opacity: 0.5
//            visible:  true
//        }

        Image {
            id: _image
            smooth: true
            visible: true
            anchors.fill: parent
           // source: qmlGlobal.fileExists(model.modelData.icon) ? model.modelData.icon.toLoadFileUrl() : ""
            sourceSize: Qt.size(parent.size, parent.size)
            antialiasing: true

            Rectangle {
                width: parent.width
                height: 52
                anchors.bottom: parent.bottom
                color: "#000000"
                opacity: 0.5
                visible:  true
            }
        }

        OpacityMask {
            id: mask_image
            anchors.fill: _image
            source: _image
            maskSource: parent
            visible: true
            antialiasing: true
        }
    }
}
