import QtQuick 2.0

Item {
    // Data properties
    property string textEmployeeName: "value"
    property string textAverageScore: "value"
    property int employeeIndex: 0

    // Dimension properties
    property int textSize: 13

    // Properies Signal
    property bool isChoosing: false

    Rectangle {
        id: id_buttonEmployeeInList
        width: parent.width
        height: parent.height
        color: isChoosing ? "blue" : "white"
        opacity: isChoosing ? 0.5 : 1

        Text {
            id: id_textEmployeeName
            width: parent.width*3/4
            height: parent.height
            anchors.left: parent.left
            verticalAlignment: Text.AlignVCenter
            font.pixelSize: textSize
            color: "black"

            text: textEmployeeName
        }
        Text {
            id: id_textEmployeeAverageScore
            width: parent.width*1/4
            height: parent.height
            anchors.left: id_textEmployeeName.right
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            font.pixelSize: textSize
            color: "black"
            text: averageScore.toString().substr(0,4)

        }
    }
}
