import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
//import EmployeeDataModel 1.0

Window {
    visible: true
    width: 600
    height: 800
    maximumHeight: 800
    minimumHeight: 800
    maximumWidth: 600
    minimumWidth: 600
    title: "AVN Application C"

    property int lastEmployeeIndexChoosen: 0

    ListModel {
        id: id_skillDetailModel
        ListElement {
            iImgIconLanguageSource: "file:///home/avn/Desktop/LG_AVN_TEST/Application/Images/icon_asm.png"
            iTextSkillName: "Assembly"
        }
        ListElement {
            iImgIconLanguageSource: "file:///home/avn/Desktop/LG_AVN_TEST/Application/Images/icon_cpp.png"
            iTextSkillName: "C++"
        }
        ListElement {
            iImgIconLanguageSource: "file:///home/avn/Desktop/LG_AVN_TEST/Application/Images/icon_js.png"
            iTextSkillName: "Javascript"
        }
        ListElement {
            iImgIconLanguageSource: "file:///home/avn/Desktop/LG_AVN_TEST/Application/Images/icon_qml.png"
            iTextSkillName: "QML"
        }
        ListElement {
            iImgIconLanguageSource: "file:///home/avn/Desktop/LG_AVN_TEST/Application/Images/icon_opengl.jpg"
            iTextSkillName: "OpenGL"
        }
    }

    ListView { // Employee Skill Detail
        id: id_skillDetailList
        x: 100
        y: 100
        spacing: 5
        width: parent.width
        height: 400
        model: id_skillDetailModel
        delegate: SkillDetail_Item {
            height: 30
            textSize: 24
            imgLanguageIconSource: iImgIconLanguageSource
            textSkillName: iTextSkillName
        }
    }

    Rectangle {
        id: id_buttonUpdate
        anchors.horizontalCenter: parent.horizontalCenter
        y: 300
        width: 150
        height: 30
        color: "green"
        radius: 10
        Text {
            id: id_buttonTextUpdate
            anchors.fill: parent
            text: "UPDATE"
            font.pixelSize: 20
            color: "white"
            font.bold: true
            horizontalAlignment: Text.AlignHCenter
            verticalAlignment: Text.AlignVCenter
        }

        MouseArea {
            anchors.fill: parent
            onPressed: id_buttonUpdate.color = "yellow"
            onReleased: id_buttonUpdate.color = "green"
        }
    }

    Item {
        id: id_itemHeader
        width: 400
        height: 20
        x: 100
        y: 380
        // Header: NAME
        Text {
            id: id_textEmployeeList_NameHeader
            width: parent.width*3/4
            height: parent.height
            color: "black"
            font.pixelSize: 13
            font.bold: true

            text: "NAME"
        }
        // Header: AVERAGE
        Text {
            id: id_textEmployeeList_AverageHeader
            width: parent.width*1/4
            height: parent.height
            anchors.left: id_textEmployeeList_NameHeader.right
            color: "black"
            font.pixelSize: 13
            font.bold: true

            text: "AVERAGE"
            horizontalAlignment: "AlignHCenter"
        }
    }

    ListModel {
        id: id_employeeModel
        ListElement {
            content: "toan4.nguyen"
            score: "0.0"
            isChoosing: false
        }
        ListElement {
            content: "luan1.pham"
            score: "0.0"
            isChoosing: false
        }
        ListElement {
            content: "hoang1.nguyen"
            score: "0.0"
            isChoosing: false
        }
        ListElement {
            content: "viet.mac"
            score: "0.0"
            isChoosing: false
        }
        ListElement {
            content: "tru.vu"
            score: "0.0"
            isChoosing: false
        }
        ListElement {
            content: "hoang2.truong"
            score: "0.0"
            isChoosing: false
        }
    }

//    EmployeeDataModel {
//        id: id_EmployeeDataModel
//    }

    ListView {
        id: id_employeeList
        model: id_employeeModel
        height: parent.height
        x: 100
        y: 400

        delegate: EmployeeInList_Item {
            id: id_EmployeeInListItem
            width: 400
            height: 18
            textSize: 13

            // Get from model:
            textEmployeeName: content
            averageScore: score
            isChoosing: isChoosing

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    id_EmployeeInListItem.employeeIndex = index
                    id_EmployeeInListItem.isChoosing = true
                    // unChossen
//                    id_EmployeeInListItem.isChoosing = false // this code failed ==> maybe implement in C++
                    lastEmployeeIndexChoosen = index
                }
            }
        }
    }
}
