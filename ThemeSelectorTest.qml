import QtQuick 2.6
import QtQuick.Controls 2.1
import QtQuick.Layouts 1.3
import QtQuick.Controls 1.4
import QtQuick.Dialogs 1.2

import com.comtechtel.maptool 1.0

ApplicationWindow {
    visible: true
    width: 640
    height: 480
    title: qsTr("Hello World")

    MaterialListModel {
        id: materialListModel
        //theme: mytheme.theme.current.objectName
    }

    FontSizeModel {
        id: fontSizeModel
    }

    ColorDialog {
        id: colorDialog
        onAccepted: {
            var model = listview.model
            var index = listview.currentIndex
            var item = listview.currentItem
            var data = item.material
            console.log(data)
            console.log(item)
            console.log(listview.model)
            console.log(listview.currentIndex)
            data.color = currentColor
        }
    }
    SplitView {
        id: splitview
        anchors.fill: parent
        orientation: Qt.Horizontal

        Item {
            height: parent.height
            width: 300
            ColumnLayout {
                anchors.fill: parent
                TabView {

                    height: parent.height - cmdBar.height
                    //anchors.fill: parent
                    anchors.top: parent.top
                    anchors.bottom: cmdBar.top
                    anchors.margins: 12
                    Tab {
                        title: "Color Theme"

                        ColumnLayout {
                            id: leftpane
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
                                    materialListModel.theme = theme.current.text
                                }

                                dark.onClicked: {
                                    console.log("dark.onClicked")
                                    console.log(theme.current)
                                    console.log("objectName: " + theme.current.objectName)
                                    console.log("text: " + theme.current.text)
                                    materialListModel.theme = theme.current.text
                                }

                                // light is checked
                                Component.onCompleted: {
                                    var str = materialListModel.theme
                                    if (str == "light") {
                                        light.checked = true
                                    } else if (str == "dark") {
                                        dark.checked = true
                                    } else {
                                        basic.checked = true
                                    }
                                }
                            }
                            ScrollView {
                                anchors.top: mytheme.bottom
                                anchors.bottom: parent.bottom
                                ListView {
                                    id: listview
                                    width: parent.width
                                    model: materialListModel
                                    spacing: 5
                                    clip: true
                                    delegate: ListItem {
                                        property Material material: model.material
                                        text: material.name
                                        boxColor: material.color
                                        width: ListView.view.width

                                        onClicked: {
                                            var material = model.material
                                            colorDialog.color = material.color
                                            colorDialog.open()
                                            listview.currentIndex = index
                                        }
                                    }
                                }
                            }
                        }
                    }
                    Tab {
                        title: "Font Size"
                        Item {
                            //anchors.fill: parent
                            anchors.topMargin: 10
                            RowLayout {
                                anchors.fill: parent
                                Layout.alignment: Qt.AlignLeft
                                spacing: 10
                                Label {
                                    //anchors.leftMargin: 20
                                    anchors.right: fontsize.left
                                    text: "Road"
                                    font.pixelSize: 22
                                }
                                ComboBox {
                                    id: fontsize
                                    anchors.horizontalCenter: parent.horizontalCenter
                                    Layout.leftMargin: 20
                                    //anchors.leftMargin: 20
                                    model: [-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, 5]
                                    editable: true
                                    //currentText: "3"
                                    currentIndex: 6
                                    validator: IntValidator {
                                        top: 5
                                        bottom: -5
                                    }
                                    Component.onCompleted: {
                                        var txt = fontSizeModel.increment
                                        console.log("fontsize.increment : " + txt)
                                        var i = fontsize.find(txt)
                                        if (i !== -1) {
                                            fontsize.currentIndex = i
                                        }
                                    }
                                    onActivated: {
                                        console.log("Combobox::onActivated(" + index + ")")
                                        console.log("ComboBox::onActivated text = "
                                                    + fontsize.textAt(index))
                                        fontSizeModel.increment = fontsize.textAt(
                                                    index)
                                    }
                                }
                            }
                        }
                    }
                }
                RowLayout {
                    id: cmdBar
                    Layout.alignment: Qt.AlignBottom

                    //anchors.bottom: splitview.bottom
                    //anchors.horizontalCenter: parent.horizontalCenter
                    Button {
                        id: preview
                        text: "Preview"
                    }

                    Button {
                        id: save
                        text: "Save"
                        anchors.right: parent.right
                        Layout.alignment: Qt.AlignRight
                    }
                }
            }
        }

        // dark will not be checked because light is checked
        // in ThemeSelector.  Why???
        //    Component.onCompleted: {
        //        mytheme.dark.checked = true
        //   }
        Item {
            Rectangle {
                anchors.fill: parent
                color: "lightsteelblue"
                border.color: "slategrey"
            }
        }
    }
}
