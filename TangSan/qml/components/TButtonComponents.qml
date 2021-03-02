import QtQuick 2.0
import QtQuick.Window 2.2
import "../commons"

/*
 * 按钮种类

 * 基础按钮 TButtonBase
 * 带文字按钮 TTextButton
 * 带单一背景图按钮 TIconButton
 * 带大图 TImageButton
 * 选中按钮 TPressButton

 * 其他复杂按钮不需要封装 Item Rectangle Image
*/

Window {
    id: id_item_root
    visible: true
    width: 356
    height: 320
    title: qsTr("Test")
    //z: id_item_root + 1


    Image {
        anchors.fill: parent
        source: "qrc:/images/home-reading-bkgd.png"
        //sourceSize: Qt.size(36, 36)

        AnimatedImage  {
            id:animated
            anchors.bottom: parent.bottom
            anchors.right: parent.right
            source: "qrc:/images/beautiful.gif"
            width: 100
            height: 100
            paused: true

            MouseArea {  // :/images/home-reading-bkgd.png   qrc:/images/home-reading-bkgd.png
                anchors.fill: parent
                anchors.left: parent.left
                anchors.top: parent.top
                onClicked: {
                    console.log("YVerifyPage.qml === AnimatedImage.last.onClicked")
                    animated.paused = !animated.paused;
                }
            }
        }

        MouseArea {  // :/images/home-reading-bkgd.png   qrc:/images/home-reading-bkgd.png
            width: 50
            height: 50
            anchors.left: parent.left
            anchors.top: parent.top
            onClicked: {
                console.log("YVerifyPage.qml === id_introduction_item.last.onClicked")
                //                if (id_introduction_item.intrImageIndex > 1) {
                //                    id_introduction_item.intrImageIndex -= 1
                //                }
            }
        }

        MouseArea {
            width: 50
            height: 50
            anchors.right: parent.right
            anchors.top: parent.top
            onClicked: {
                console.log("YVerifyPage.qml === id_introduction_item.next.onClicked")
                //                if (id_introduction_item.intrImageIndex < 4) {
                //                    id_introduction_item.intrImageIndex += 1
                //                } else {
                //                    verifyManager.openMainPage()
                //                }
            }
        }
    }

    //    TButtonBase{
    //        id: id_button_base
    //        width: 100
    //        height: 100
    //        anchors.left: parent.left
    //        anchors.leftMargin: 30

    //        Text {
    //            id: id__title
    //            text: qsTr("TButtonBase")
    //            anchors.centerIn: parent
    //            width: 70
    //            wrapMode: Text.Wrap

    //            color: TColors.white
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
