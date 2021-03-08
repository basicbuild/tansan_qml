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
    width: 800
    height: 254
    title: qsTr("Test")
    //z: id_item_root + 1
    property int intrImageIndex: 1

    function initPageImage()
    {
        id_timer.stop()
        if(1 === intrImageIndex)
            id_image.source = "qrc:/images/scanread_page1.png"
        else if(2 === intrImageIndex)
            id_image.source = "qrc:/images/scanread_content1.png"
        id_timer.restart()
    }


    Image {
        anchors.fill: parent
        source: "qrc:/images/scanread_introduction"+ intrImageIndex +".png"

        Image {
            id: id_image
            anchors.right: parent.right
            anchors.rightMargin: 40
            anchors.bottom: parent.bottom
            anchors.bottomMargin: {
                console.log("TButtonComponents.qml === anchors.bottomMargin24")
                return 24
            }
            sourceSize: Qt.size(280, 150)
            visible: 1 === intrImageIndex || 2 === intrImageIndex
            source:{
                if(1 === intrImageIndex){
                    console.log("TButtonComponents.qml === id_image page1")
                    return "qrc:/images/scanread_page1.png"
                }else if(2 === intrImageIndex){
                    console.log("TButtonComponents.qml === id_image content1")
                    return "qrc:/images/scanread_content1.png"
                }
            }
        }

        Timer{
            id: id_timer
            interval: 1000
            onTriggered: {
                //id_image.source = "qrc:/images/second.png"
                // id_timer.stop()
                console.warn("TButtonComponents.qml === id_timer")
                // id_timer.restart()
            }

        }

        Component.onCompleted: {
            id_timer.start()
        }

        MouseArea {
            width: 50
            height: 50
            anchors.left: parent.left
            anchors.top: parent.top
            onClicked: {
                //console.log("YVerifyPage.qml === id_introduction_item.last.onClicked")
                if (intrImageIndex > 1) {
                    intrImageIndex -= 1
                }
            }
        }

        MouseArea {
            width: 50
            height: 50
            anchors.right: parent.right
            anchors.top: parent.top
            onClicked: {
                //console.log("YVerifyPage.qml === id_introduction_item.next.onClicked")
                if (intrImageIndex < 4) {
                    intrImageIndex += 1
                } else {

                }
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


    //    AnimatedImage  {
    //        id:animated
    //        anchors.bottom: parent.bottom
    //        anchors.right: parent.right
    //        source: "qrc:/images/beautiful.gif"
    //        width: 100
    //        height: 100
    //        paused: true

    //        MouseArea {  // :/images/home-reading-bkgd.png   qrc:/images/home-reading-bkgd.png
    //            anchors.fill: parent
    //            anchors.left: parent.left
    //            anchors.top: parent.top
    //            onClicked: {
    //                console.log("YVerifyPage.qml === AnimatedImage.last.onClicked")
    //                animated.paused = !animated.paused;
    //            }
    //        }
    //    }


}
