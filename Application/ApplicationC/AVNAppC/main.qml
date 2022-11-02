import QtQuick 2.15
import QtQuick.Window 2.15
import QtQuick.Controls 2.15
import EmpDataModel 1.0
import EmpDataDetailModel 1.0
import EmpDataProxyModel 1.0
import AppHMIService 1.0

Window {
    visible: true
    maximumWidth: 900
    minimumWidth: 900
    maximumHeight: 1200
    minimumHeight: 1200
    title: "AVN Application C (Editor)"

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
    AppHMIService {
        id: id_AppHMIService
        onSignalUpdateScoreModel: {
            console.log("onSignalUpdateScoreModel")
            id_EmployeeDataDetailModel.updateDetailData(asmScore, cppScore, jsScore, qmlScore, openglScore)
        }
    }

    Text {
        id: id_employeeNameOnTitle
        anchors.horizontalCenter: parent.horizontalCenter
        y: 100
        font.pixelSize: 48
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
        width: 300
        height: 400
        x: 200
        y: 200
        spacing: 10

        delegate: SkillNameView_Item {
            height: 36
            heightSize: height
            textSize: 36
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
        y: 200
        anchors.left: id_skillIconNameList.right
        spacing: 10

        delegate: SkillScoreInput_Item {
            height: 36
            heightSize: height
            textSize: 36
            textCurrentScore: skillScore.toString()
        }
    }
    // End Score Input

    // Start Update Button:
    Rectangle {
        id: id_buttonUpdate
        anchors.horizontalCenter: parent.horizontalCenter
        y: 500
        width: 300
        height: 50
        color: "green"
        radius: 10
        Text {
            id: id_buttonTextUpdate
            anchors.fill: parent
            text: "UPDATE"
            font.pixelSize: 36
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

    // Start Search Name Input
    Item {
        id: id_SearchBar
        width: parent.width
        height: 50
        anchors.top: id_buttonUpdate.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        Text {
            id: id_textSearchName
            width: 180
            height: parent.height
            anchors.left: parent.left
            anchors.leftMargin: 20
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: 28
            text: qsTr("Search Name: ")
        }

        Rectangle {
            width: parent.width-id_textSearchName.width
            height: parent.height
            anchors.verticalCenter: parent.verticalCenter
            anchors.left: id_textSearchName.right
            anchors.right: parent.right
            anchors.rightMargin: 20
            border.width: 5
            border.color: "#87CEEB"
            TextInput {
                id: id_inputTextSearch
                anchors.fill: parent
                anchors.leftMargin: 20
                font.pixelSize: 28
                verticalAlignment: Text.AlignVCenter
                color: "black"
            }
        }
    }
    // End Search Name Input


    // Start List Employee Header
    Item {
        id: id_itemHeader
        width: 600
        height: 40
        anchors.top: id_SearchBar.bottom
        anchors.topMargin: 20
        anchors.horizontalCenter: parent.horizontalCenter
        // Header: NAME
        Text {
            id: id_textEmployeeList_NameHeader
            width: parent.width*3/4
            height: parent.height
            color: "black"
            font.pixelSize: 28
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
            font.pixelSize: 28
            font.bold: true

            text: "AVERAGE"
            horizontalAlignment: "AlignHCenter"
        }
    }
    // End List Employee Header

    ListView {
        id: id_employeeList
//        model: id_EmployeeDataModel
        width: 600
        height: parent.height
        anchors.horizontalCenter: parent.horizontalCenter
        anchors.top: id_itemHeader.bottom
        anchors.topMargin: 10

        model: EmployeeDataProxyModel {
            id: id_EmployeeDataProxyModel
            source: id_EmployeeDataModel

            sortCaseSensitivity: Qt.CaseInsensitive
            sortRole: id_EmployeeDataModel.count > 0 ? employeeName : ""

            filterString: "*" + id_inputTextSearch.text + "*"
            filterSyntax: EmployeeDataProxyModel.Wildcard
            filterCaseSensitivity: Qt.CaseInsensitive
        }

        delegate: EmployeeInList_Item {
            id: id_EmployeeInListItem
            width: 600
            height: 45
            textSize: 24

            // Get from model:
            textEmployeeName: employeeName
            textAverageScore: averageScore.toString()
            isChoosing: isSelected

            MouseArea {
                anchors.fill: parent
                onClicked: {
                    currentEmpName = employeeName
                    id_AppHMIService.requestGetScoreData(index, currentEmpName)
                    id_EmployeeDataDetailModel.updateDetailData(index, currentEmpName)
                }
            }
        }
    }
}
