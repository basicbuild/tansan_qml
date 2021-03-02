import QtQuick 2.12

Timer {
    onRunningChanged: {
        console.log("TTimer.qml===", objectName, "===running", (running ? "start" : "stop"))
    }
}
