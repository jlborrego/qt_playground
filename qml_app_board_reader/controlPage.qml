import QtQuick 2.15
import QtQuick.Layouts 1.15
import QtQuick.Controls 2.15


Page {
    id: controlPage
    width: view.width
    height: view.height
    visible: false

//    rotation: 90

    background: Rectangle{
        color:"transparent"
    }

    function createPage(){
        var component = Qt.createComponent("controlPage.qml")
        var page = component.createObject(view)
        return page
    }

    function addPage(page) {
        addItem(page)
        page.visible = true
    }

    RoundButton {
        id: buttonAdd
        //                    width: 40
        //                    height: 40
        anchors.bottom: parent.bottom
        //                    anchors.horizontalCenter: parent.horizontalCenter
        anchors.right: parent.right
        font.pixelSize: 13
        text: "Add\nnew"
        onClicked: {
            view.addPage(view.createPage())
        }

    }

    Rectangle {
        id: toolbox
        width: name.width * 2
        height: name.height + 30
        color: "beige"
        //        anchors { right: parent.right; top: parent.top;  left: parent.left}
        anchors.horizontalCenter: gridLayout.horizontalCenter
        anchors.top: parent.top
//        anchors.topMargin: 150
//        anchors.bottom: gridLayout.top
//        anchors.bottomMargin: 150
        border.color: "black"
        radius: 10
        Text {
            id: name
            text: qsTr("Placa")
            font.bold: true
            font.pixelSize: 40
            color: "#000000"
            anchors.centerIn: parent
        }
    }


    GridLayout {
        id: gridLayout
//        anchors.top: toolbox.bottom
        anchors.verticalCenter: parent.verticalCenter
        anchors.horizontalCenter: parent.horizontalCenter
//        anchors.topMargin: 200
//        anchors.centerIn: parent
        rowSpacing: 20
        columns: 2
        rows: 8
//        scale: 1.5

        Button {
            id: button1
            text: "Botón 1"
            height: 20
            onClicked: {
                if(rect1.color.toString() === "#ff0000"){
                    rect1.color = "#008000"
                }else{
                    rect1.color = "#ff0000"
                }
            }
        }

        Rectangle {
            id: rect1
            width: 20
            height: 23
            radius: 5
            color: "#ff0000"
        }

        Button {
            id: button2
            text: "Botón 2"
            height: 20
            onClicked: {
                if(rect2.color.toString() === "#ff0000"){
                    rect2.color = "#008000"
                }else{
                    rect2.color = "#ff0000"
                }
            }
        }

        Rectangle {
            id: rect2
            width: 20
            height: 23
            radius: 5
            color: "#ff0000"
        }

        Button {
            id: button3
            text: "Botón 3"
            height: 20
            onClicked: {
                if(rect3.color.toString() === "#ff0000"){
                    rect3.color = "#008000"
                }else{
                    rect3.color = "#ff0000"
                }
            }
        }

        Rectangle {
            id: rect3
            width: 20
            height: 23
            radius: 5
            color: "#ff0000"
        }

        Button {
            id: button4
            text: "Botón 4"
            height: 20
            onClicked: {
                if(rect4.color.toString() === "#ff0000"){
                    rect4.color = "#008000"
                }else{
                    rect4.color = "#ff0000"
                }
            }
        }

        Rectangle {
            id: rect4
            width: 20
            height: 23
            radius: 5
            color: "#ff0000"
        }

        Button {
            id: button5
            text: "Botón 5"
            height: 20
            onClicked: {
                if(rect5.color.toString() === "#ff0000"){
                    rect5.color = "#008000"
                }else{
                    rect5.color = "#ff0000"
                }
            }
        }

        Rectangle {
            id: rect5
            width: 20
            height: 23
            radius: 5
            color: "#ff0000"
        }

        Button {
            id: button6
            text: "Botón 6"
            height: 20
            onClicked: {
                if(rect6.color.toString() === "#ff0000"){
                    rect6.color = "#008000"
                }else{
                    rect6.color = "#ff0000"
                }
            }
        }

        Rectangle {
            id: rect6
            width: 20
            height: 23
            radius: 5
            color: "#ff0000"
        }

        Button {
            id: button7
            text: "Botón 7"
            height: 20
            onClicked: {
                if(rect7.color.toString() === "#ff0000"){
                    rect7.color = "#008000"
                }else{
                    rect7.color = "#ff0000"
                }
            }
        }

        Rectangle {
            id: rect7
            width: 20
            height: 23
            radius: 5
            color: "#ff0000"
        }

        Button {
            id: button8
            text: "Botón 8"
            height: 20
            onClicked: {
                if(rect8.color.toString() === "#ff0000"){
                    rect8.color = "#008000"
                }else{
                    rect8.color = "#ff0000"
                }
            }
        }

        Rectangle {
            id: rect8
            width: 20
            height: 23
            radius: 5
            color: "#ff0000"
        }
    }

}
