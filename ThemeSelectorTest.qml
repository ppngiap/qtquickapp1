import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4

import com.comtechtel.maptool 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MaterialListModel {
        id: materialListModel
        theme: mytheme.theme.current.objectName
    }

    ColumnLayout {

        height: parent.height
        spacing: 20

        ThemeSelector {
            id: mytheme

            basic.onClicked: {
                console.log("basic.onClicked")
                console.log(theme.current)
                console.log("objectName: " + theme.current.objectName)
                console.log("text: " + theme.current.text)
            }

            light.onClicked: {
                console.log("light.onClicked")
                console.log(theme.current)
                console.log("objectName: " + theme.current.objectName)
                console.log("text: " + theme.current.text)
            }

            dark.onClicked: {
                console.log("dark.onClicked")
                console.log(theme.current)
                console.log("objectName: " + theme.current.objectName)
                console.log("text: " + theme.current.text)
            }

            // light is checked
            Component.onCompleted: {
                var str = materalListModel.theme
                if (str == "light") {
                    light.checked = true
                } else if (str == "dark") {
                    dark.checked = true
                }  else {
                    basic.checked = true
                }
            }

        }
        ScrollView {
            anchors.top : mytheme.bottom
            anchors.bottom: cmdBar.top
        ListView {
            id: view
            width: parent.width
            model: materialListModel
            spacing: 5
            clip: true
            delegate: ListItem {
                property Material material: model.data
                text: material.name
                boxColor: material.color
                width: ListView.view.width

                onClicked: {
                    var material = model.data
                }
            }

        }
        }
        RowLayout {
            id : cmdBar
            anchors.bottom: parent.bottom
            anchors.horizontalCenter: parent.horizontalCenter
            Label {
                text: "Object Name"
            }

            TextField {
                text: mytheme.theme.current.text
            }
        }
    }

    // dark will not be checked because light is checked
    // in ThemeSelector.  Why???
    //    Component.onCompleted: {
    //        mytheme.dark.checked = true
    //   }
}
