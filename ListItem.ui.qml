import QtQuick 2.0
import QtQuick.Controls 2.2
import QtQuick.Layouts 1.3

Item {
    id: root
    width: 120
    height: row.height
    property alias text: label.text
    property color fontColor: '#1f1f1f'
    property color boxColor: '#ffffff'
    RowLayout {
        id: row
        spacing: 5
        Rectangle {
            id : rect
            width:  40
            height: 40
            color: root.boxColor
            border.color: Qt.darker(color, 1.2)
        }
        Text {
            id: label
            font.pixelSize: 14
            color: root.fontColor
            text: "hello"
        }
    }
}
