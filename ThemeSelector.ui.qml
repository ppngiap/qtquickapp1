import QtQuick 2.0
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

Item {
    property alias theme: themeGroup
    property alias basic: basicRadioButton
    property alias light: lightRadioButton
    property alias dark: darkRadioButton
    property alias lightRadioButton: lightRadioButton

    height: 54
    width: 300

    GroupBox {
        title: qsTr("Theme")

        RowLayout {
            id: rowLayout
            width: parent.width
            spacing: 10

            ExclusiveGroup {
                id: themeGroup
            }

            RadioButton {
                id: basicRadioButton
                objectName: "basic"
                text: qsTr("Basic")
                checked: true
                exclusiveGroup: themeGroup
            }

            RadioButton {
                id: lightRadioButton
                objectName: "light"
                text: qsTr("Light")
                exclusiveGroup: themeGroup
            }

            RadioButton {
                id: darkRadioButton
                objectName: "dark"
                text: qsTr("Dark")
                exclusiveGroup: themeGroup
            }
        }
    }
}
