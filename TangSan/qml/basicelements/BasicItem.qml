import QtQuick 2.0
import QtQuick.Window 2.2

Item {
    id: id_item_root
    opacity: 0.5

    width: 100
    height: 100

    Rectangle { width: 80; height: 80; border.width: 1 }
    Rectangle { x: 20; y: 20; width: 80; height: 80; border.width: 1 }
}
