import QtQuick 2.15
import QtQuick.Controls 2.15
import QtLocation 6.5
import QtPositioning 6.5
import QtQuick.Layouts
import QtWebEngine




Rectangle {

    visible: true
    width: 1000
    height: 800

    /*Rectangle {
        width: 200 // Space before the map
        height: parent.height
        color: "lightpink"

        Rectangle {
            width: 5 // Space above the small map
            height: parent.height-60
            color: "transparent"
        }


        WebEngineView {
            id:mapOverview
            width: 190 // Map width
            height: 190 // Map height
            //                anchors.centerIn: parent
            anchors.left: parent.left
            anchors.top: parent.top
            anchors.topMargin: 30 // Top margin (30px space above small map)
            anchors.leftMargin: 5 // Left margin
            url: "qrc:/mapOverview.html"
        }

    }*/

    WebEngineView {
        id:map
        width: parent.width // Map width (1000 - 150 - 150)
        height: parent.height  // Map height (800 - 30 - 30)
        anchors.centerIn: parent
        url: "qrc:/map.html"


    }

    /*Rectangle {
        width: 200 // Space after the map
        height: parent.height
        color: "gray"
        anchors.right: parent.right


    }*/

    /*Button {
        text: "Toggle Red Block"
        anchors.left: parent.left
        onClicked: {
            // Toggle the visibility of the red block
            redRectangle.visible = !redRectangle.visible;
        }
    }*/
}

//ApplicationWindow {
//    visible: true
//    width: 1000
//    height: 800

//    Rectangle {
//        width: parent.width
//        height: parent.height
//        color:"lightblue"


//        Rectangle {
//            width: 200 // Space before the map
//            height: parent.height
//            color: "lightpink"

//            Rectangle {
//                width: 5 // Space above the small map
//                height: parent.height-60
//                color: "transparent"
//            }
//            /*Rectangle {
//                width:150 // Space above the small map
//                height: 150
//                color: "blue"
//                anchors.left: parent.left
//                anchors.top: parent.top
//                anchors.topMargin: 30 // Top margin (30px space above small map)
//                anchors.leftMargin: 25 // Left margin
//            }*/

//            WebEngineView {
//                id:mapOverview
//                width: 190 // Map width
//                height: 190 // Map height
////                anchors.centerIn: parent
//                anchors.left: parent.left
//                anchors.top: parent.top
//                anchors.topMargin: 30 // Top margin (30px space above small map)
//                anchors.leftMargin: 5 // Left margin
//                url: "qrc:/mapOverview.html"
//            }

//        }
////        WebEngineView {
////            width: 150 // Map width
////            height: 150 // Map height
////            anchors.centerIn: parent
////            url: "qrc:/mapOverview.html"
////        }
//        WebEngineView {
//            id:map
//            width: parent.width - 400 // Map width (1000 - 150 - 150)
//            height: parent.height - 60 // Map height (800 - 30 - 30)
//            anchors.centerIn: parent
//            url: "qrc:/map.html"


//        }

//        Rectangle {
//            width: 200 // Space after the map
//            height: parent.height
//            color: "gray"
//            anchors.right: parent.right


//        }

//        Button {
//            text: "Toggle Red Block"
//            anchors.left: parent.left
//            onClicked: {
//                // Toggle the visibility of the red block
//                redRectangle.visible = !redRectangle.visible;
//            }
//        }
//    }
//    /*
//    Rectangle {
//        id: redRectangle
//        width: 200
//        height: parent.height
//        color: "red"
//        anchors.right: parent.right
//        visible: true // Initial visibility is set to true

//        Text {
//            text: "QML Overlay"
//            anchors.centerIn: parent
//            font.pointSize: 20
//            color: "white"
//        }
//    }*/
//}
