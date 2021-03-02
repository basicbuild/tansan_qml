/*
 * 可视化按钮
 */
import QtQuick 2.12

Rectangle {
    id: id_button_bg
    opacity: id_button_mouse_area.pressed || !enabled ? 0.6 : 1
    smooth: true
    color: TColors.grayNormal
    radius: 16

    property alias buttonMouseAreaTimer: id_button_mouse_area.buttonMouseAreaTimer

    signal clicked()
    signal validClicked()
    signal pressAndHold()

    TButtonBaseMouseArea{
        id: id_button_mouse_area
        anchors.fill: parent
        onClicked: {
            id_button_bg.clicked()
        }
        onVaildClicked: {
            id_button_bg.validClicked()
        }
        onPressAndHold: {
            id_button_bg.pressAndHold()
        }
        objectName: "TButtonBase.qml_id_button_mouse_area"
    }
}
