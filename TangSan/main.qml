import QtQuick 2.14
import QtQuick.Window 2.14
import QtQuick.Controls 2.2
import tangsan.github 1.0

import "./qml"
import "./qml/test"

Item {
    id: id_item_root
    visible: true
    width: buttonwidth*5 + 80
    height: 320

    property int buttonwidth: 85
    property int buttonheight: 35
    property int titlespacing: 10 // 标题和内容间距
    property int unitspacing: 16 // 两单元(Text+Grid)间距

    Loader{
        id: pageLoader
    }

    Flickable{
        anchors.fill: parent
        anchors.top: parent.top
        anchors.bottom: parent.bottom
        anchors.left: parent.left
        anchors.leftMargin: 16
        contentHeight: id_basic_elements_title.contentHeight + id_grid_basic_elements_container.height
                       + id_component_title.contentHeight + id_grid_component_container.height
                       + id_model_title.contentHeight + id_grid_model_container.height
                       + id_features_title.contentHeight + id_grid_features_container_repeater.height
                       + 20 + 16 + 30 + 16

        Button{
            id: id_button_test
            text: qsTr("Test")
            anchors.top: parent.top
            anchors.topMargin: 20
            implicitWidth: buttonwidth
            implicitHeight: buttonheight

            onClicked: {
                console.warn("onClicked")
                pageLoader.source = ""
                pageLoader.source = "qml/test/MTest.qml"
            }
        }

        Text {
            id: id_basic_elements_title
            text: qsTr("基本元素")
            anchors.top: id_button_test.bottom
            anchors.topMargin: unitspacing
        } // 基本元素

        Grid{
            id:id_grid_basic_elements_container
            anchors.top: id_basic_elements_title.bottom
            anchors.topMargin: titlespacing
            width: 640
            columns: 5
            spacing: 12

            Repeater{
                id:id_grid_basic_elements_container_repeater
                Button{
                    implicitWidth: buttonwidth
                    implicitHeight: buttonheight
                    text: model.modelData

                    onClicked: {
                        console.warn("basic_elements clicked:",index , model.modelData)
                        pageLoader.source = ""
                        switch(index)
                        {
                        case TEnum.BE_Item:
                            pageLoader.source = "qml/basicelements/BasicItem.qml"
                            break;
                        case TEnum.BE_Rectangle:
                            pageLoader.source = "qml/basicelements/BasicRectangle.qml"
                            break;
                        case TEnum.BE_Text:
                            break;
                        case TEnum.BE_Image:
                            break;
                        case TEnum.BE_Button:
                            pageLoader.source = "qml/basicelements/BasicButton.qml"
                            break;
                        }
                    }
                }
            }
        }

        Text {
            id: id_positioning_element_title
            text: qsTr("定位元素")
            anchors.top: id_grid_basic_elements_container.bottom
            anchors.topMargin: unitspacing
        } // 定位元素

        Grid{
            id:id_grid_positioning_elements_container
            anchors.top: id_positioning_element_title.bottom
            anchors.topMargin: titlespacing
            width: 640
            columns: 5
            spacing: 12

            Repeater{
                id:id_grid_positioning_elements_container_repeater
                Button{
                    implicitWidth: buttonwidth
                    implicitHeight: buttonheight
                    text: model.modelData

                    onClicked: {
                        console.warn("positioning_element clicked:",index , model.modelData)
                    }
                }
            }
        }

        Text {
            id: id_component_title
            text: qsTr("组件封装")
            anchors.top: id_grid_positioning_elements_container.bottom
            anchors.topMargin: unitspacing
        } // 组件封装

        Grid{
            id:id_grid_component_container
            anchors.top: id_component_title.bottom
            anchors.topMargin: titlespacing
            width: 640
            columns: 5
            spacing: 12

            Repeater{
                id:id_grid_component_container_repeater
                Button{
                    implicitWidth: buttonwidth
                    implicitHeight: buttonheight
                    text: model.modelData

                    onClicked: {
                        console.warn("component clicked:",index , model.modelData) 
                        pageLoader.source = ""
                        switch(index)
                        {
                        case TEnum.CO_Button:
                            pageLoader.source = "/qml/components/TButtonComponents.qml"
                            break;
                        case TEnum.CO_Text:
                            pageLoader.source = "qml/basicelements/BasicRectangle.qml"
                            break;
                        case TEnum.CO_Image:
                            break;
                        }
                    }
                }
            }
        }

        Text {
            id: id_model_title
            text: qsTr("model view")
            anchors.top: id_grid_component_container.bottom
            anchors.topMargin: unitspacing
        } // model view

        Grid{
            id:id_grid_model_container
            anchors.top: id_model_title.bottom
            anchors.topMargin: titlespacing
            width: 640
            columns: 5
            spacing: 12

            Repeater{
                id:id_grid_model_container_repeater
                Button{
                    implicitWidth: buttonwidth
                    implicitHeight: buttonheight
                    text: model.modelData

                    onClicked: {
                        console.warn("model clicked:",index , model.modelData)
                    }
                }
            }
        }

        Text {
            id: id_features_title
            text: qsTr("功能演示")
            anchors.top: id_grid_model_container.bottom
            anchors.topMargin: unitspacing
        } // 功能演示

        Grid{
            id:id_grid_features_container
            anchors.top: id_features_title.bottom
            anchors.topMargin: titlespacing
            width: 640
            columns: 5
            spacing: 12

            Repeater{
                id:id_grid_features_container_repeater
                Button{
                    implicitWidth: buttonwidth
                    implicitHeight: buttonheight
                    text: model.modelData

                    onClicked: {
                        console.warn("features clicked:",index , model.modelData)
                    }
                }
            }
        }
    }

    Component.onCompleted: {
        const basicElementsList = systemBase.basicElementsList
        id_grid_basic_elements_container_repeater.model = basicElementsList

        const positioningElementList = systemBase.positioningElementList
        id_grid_positioning_elements_container_repeater.model = positioningElementList

        const componentList = systemBase.componentList
        id_grid_component_container_repeater.model = componentList

        const modellist = systemBase.modelList
        id_grid_model_container_repeater.model = modellist

        const featuresList = systemBase.featuresList
        id_grid_features_container_repeater.model = featuresList
    }

}
