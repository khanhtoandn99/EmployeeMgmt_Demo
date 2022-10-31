import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import EmpDataModel 1.0
import EmpDataDetailModel 1.0

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
    property string currentEmpName: "value"
    property int currentEmpAsmScore: 0
    property int currentEmpCppScore: 0
    property int currentEmpJsScore: 0
    property int currentEmpQmlScore: 0
    property int currentEmpOpenglScore: 0

    signal getDetailData(string name)


    EmployeeDataModel {
        id: id_EmployeeDataModel
    }

    EmployeeDataDetailModel {
        id: id_EmployeeDataDetailModel
    }

    Text {
        id: id_employeeNameOnTitle
        anchors.horizontalCenter: parent.horizontalCenter
        y: 20
        font.pixelSize: 32
        font.bold: true
        text: currentEmpName
    }

    // Start Icon Language and Name View
    ListModel {
        id: id_skillNameModel
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

    ListView {
        id: id_skillIconNameList
        model: id_skillNameModel
        width: 200
        height: 400
        x: 100
        y: 100
        spacing: 5

        delegate: SkillNameView_Item {
            height: 24
            heightSize: height
            textSize: 24
            imgLanguageIconSource: iImgIconLanguageSource
            textSkillName: iTextSkillName
        }
    }
    // End Icon Language and Name View

    //Start Score Input
    ListView {
        id: id_skillScoreInputList
        model: id_EmployeeDataDetailModel
        height: 400
        y: 100
        anchors.left: id_skillIconNameList.right
        spacing: 5

        delegate: SkillScoreInput_Item {
            height: 24
            heightSize: height
            textSize: 24
            textCurrentScore: skillScore.toString()
        }
    }
    // End Score Input

    // Start Update Button:
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
    // End Update Button

    // Start List Employee Header
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
    // End List Employee Header

    ListView {
        id: id_employeeList
        model: id_EmployeeDataModel
        height: parent.height
        x: 100
        y: 400

        delegate: EmployeeInList_Item {
            id: id_EmployeeInListItem
            width: 400
            height: 18
            textSize: 13

            // Get from model:
            textEmployeeName: employeeName
            textAverageScore: averageScore.toString()
//            isChoosing: isSelected

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    currentEmpName = employeeName
//                    console.log("index = " + index)
//                    console.log("currentEmpName = " + currentEmpName)
//                    console.log("averageScore = " + averageScore)
                    getDetailData(currentEmpName)
                }
            }
        }
    }

    onGetDetailData: {
        id_EmployeeDataDetailModel.updateDetailData(name)
    }
}
