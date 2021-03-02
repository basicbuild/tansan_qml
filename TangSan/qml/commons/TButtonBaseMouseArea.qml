/*
 * 封装按钮有效点击时间间隔（800ms内只能生效一次）
 */
import QtQuick 2.12

TMouseArea {
    id: id_button_mouse_area
    anchors.fill: parent

    readonly property alias buttonMouseAreaTimer: id_button_mouse_area_timer
    signal vaildClicked()

    onClicked: {
        if(!id_button_mouse_area_timer.running)
            vaildClicked()

        id_button_mouse_area_timer.restart()
    }

    TTimer{
        id: id_button_mouse_area_timer
        interval: 800
        objectName: "TButtonBaseMouseArea.qml_id_button_mouse_area_timer"
    }
}
