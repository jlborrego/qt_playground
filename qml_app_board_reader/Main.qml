import QtQuick 2.15
import QtQuick.Controls 2.15
import QtQuick.Controls.Material 2.12
import QtQuick.Layouts 1.15

ApplicationWindow {
    visible: true
    width: 500
    height: 600
    Material.theme: Material.Dark
    title: "Aplicación con Botones"

    property int curIndexWitouthZero: 0


    SwipeView {
        id: view
        currentIndex: 0
        anchors.fill: parent

        function createPage(){
            var component = Qt.createComponent("controlPage.qml")
            var page = component.createObject(view)
            return page
        }

        function addPage(page) {
            addItem(page)
            page.visible = true
        }

//        Component.onCompleted: {
//            curIndexWitouthZero = viewSwipe.currentIndex
//            curIndexWitouthZero += 1
//            addPage(createPage())
//        }

        Page{
            id: homePage
            width: view.width
            height: view.height
            visible: true

            ColumnLayout{
                anchors { verticalCenter:  parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
                spacing: 50

                Rectangle {
                    id: toolbox

                    width: titleToolbox.width
                    height: titleToolbox.height + 30
                    color: "beige"
                    //                    anchors { verticalCenter:  parent.verticalCenter; horizontalCenter: parent.horizontalCenter}
                    anchors.topMargin: 20
                    border.color: "black"
                    radius: 10
                    Text {
                        id: titleToolbox
                        text: qsTr("Example Application")
                        font.bold: true
                        font.pixelSize: 40
                        color: "#000000"
                        anchors.centerIn: parent
                    }
                }

                Button {
                    id: buttonAdd1
                    width: toolbox.width / 2
                    height: toolbox.height - 30
                    //                    anchors.bottom: parent.bottom
                    anchors.horizontalCenter: parent.horizontalCenter
                    //                    anchors.right: parent.right
                    font.pixelSize: 13
//                    contentItem: Text {
//                        id: buttonText
//                        text: buttonAdd1.text
//                        font.pixelSize: 30
//                        horizontalAlignment: Text.AlignHCenter
//                        verticalAlignment: Text.AlignVCenter
//                        color: "#000000"
//                    }
                    text: "New instance"
//                    font.pixelSize: 50
//                    font.pixelSize: 30
                    onClicked: {
                        view.addPage(view.createPage())
                    }
                }
            }
        }
    }

    PageIndicator {
        interactive: true
        count: view.count
        currentIndex: view.currentIndex
//        onCurrentIndexChanged: viewSwipe.currentIndex = currentIndex

        anchors.bottom: parent.bottom
        anchors.horizontalCenter: parent.horizontalCenter
    }

}

//        //menu containing two menu items
//           menuBar: MenuBar {
//               Menu {
//                   title: qsTr("File")
//                   MenuItem {
//                       text: qsTr("&Open")
//                       onTriggered: console.log("Open action triggered");
//                   }
//                   MenuItem {
//                       text: qsTr("Exit")
//                       onTriggered: Qt.quit();
//                   }
//               }
//           }
