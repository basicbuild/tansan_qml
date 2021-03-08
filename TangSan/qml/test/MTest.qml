import QtQuick 2.0
import QtQuick.Window 2.2

Window {
    id: id_item_root
    visible: true
    width: 356
    height: 140
    title: qsTr("Test")
    //z: id_item_root + 1

    Item {
        id: id_textbook_bought_content
        anchors.fill: parent

        Text
        {
            id:scrollText
            height:500
            width: 150
            color:"red"
            elide: Text.ElideRight
            lineHeightMode: Text.FixedHeight
            lineHeight: 36
            font.bold: true
            font.pixelSize: 12
            wrapMode: Text.WrapAnywhere
            verticalAlignment: Text.AlignVCenter
            text: qsTr("购买后用词典笔扫描课本页码和文本 ，或直接选择”听音频“，即可迅速定位学习内容，进行课本同步的听力和口语训练.")

            Behavior on height {
                NumberAnimation { duration: 10000 }
            }

            MouseArea{
                anchors.fill: parent
                onClicked: {
                        scrollText.height = 10
                }
            }

            //            Behavior on height {
            //                NumberAnimation {
            //                    from:parent.height
            //                    to: 50
            //                    duration: 120 }
            //            }

            //                        SequentialAnimation on height {
            //                            NumberAnimation {
            //                                from:parent.height + 400
            //                                to: 50
            //                                duration: 16000
            //                            }
            //                        }

        }
    }

    //    Rectangle {
    //        id: rect
    //        width: 100;
    //        height: 100
    //        color: "red"

    //        Behavior on width {
    //            NumberAnimation { duration: 1000 }
    //        }

    //        MouseArea {
    //            anchors.fill: parent
    //            onClicked: rect.width = 50
    //        }
    //    }

    //        Text{
    //        id: id_text
    //        width: 100
    //        height: 200
    //        wrapMode: Text.WrapAnywhere
    //        text: qsTr("购买后用词典笔扫描课本页码和文本 ，或直接选择”听音频“，即可迅速定位学习内容，进行课本同步的听力和口语训练.购买后用词典笔扫描课本页码和文本 ，或直接选择”听音频“，即可迅速定位学习内容，进行课本同步的听力和口语训练.")

    //        MouseArea {
    //            anchors.fill: parent
    //            onClicked: {
    //                console.warn("cilcked mousearea id_text.height:", id_text.height)
    //                id_text.height = 100
    ////                if(id_text.height === 75)
    ////                {
    ////                    id_text.height = 150
    ////                }else{
    ////                    id_text.height = 75
    ////                }
    //            }
    //        }

    //        Behavior on height {
    //            NumberAnimation { duration: 1200 }
    //        }

    //    }

    //    TMouseAreaTest {
    //        id: id_button
    //        anchors.fill: parent
    //        signal validClicked()

    //        readonly property alias buttonTimer: id_button_timer

    //        onClicked: {
    //            console.warn("YButtonBaseMouseArea.qml===id_button===onClicked1")
    //            // id_button_timer.stop()

    //            if (!id_button_timer.running) {
    //                console.warn("YButtonBaseMouseArea.qml===id_button===onClicked2")
    //                validClicked()
    //            }
    //            console.warn("YButtonBaseMouseArea.qml===id_button===onClicked3")
    //            id_button_timer.restart()
    //        }
    //        objectName: "YButtonBaseMouseArea.qml_id_button"

    //        Timer {
    //            id: id_button_timer
    //            interval: 200
    //            objectName: "YButtonBaseMouseArea.qml_id_button_timer"

    //            onRunningChanged: {
    //                console.log("YTimer.qml===child===timer===objectName: ",
    //                            objectName, "===running: ", (running ? "start" : "stop--------------------"))
    //            }
    //        }
    //    }

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
