import QtQuick 2.0

Item {
    property string imgLanguageIconSource: "value"
    property string textSkillName: "value"
    property int textSize: 24

    Image {
        id: id_imgLanguageIcon
        x: 0
        width: parent.height
        height: parent.height
        source: imgLanguageIconSource
    }

    Text {
        id: id_textSkillName
        width: 200
        height: parent.height
        anchors.left: id_imgLanguageIcon.right
        anchors.leftMargin: 10
        anchors.verticalCenter: id_imgLanguageIcon.verticalCenter

        font.pixelSize: textSize
        font.bold: true
        color: "black"
        verticalAlignment: Text.AlignVCenter

        text: textSkillName
    }

    TextInput {
        id: id_textInputScore
        width: 80
        height: parent.height
        anchors.left: id_textSkillName.right
        anchors.leftMargin: 10
        anchors.verticalCenter: id_textSkillName.verticalCenter
        cursorVisible: true
        cursorPosition: 0
        font.pixelSize: textSize
        verticalAlignment: Text.AlignVCenter
        maximumLength: 1
    }

    Image {
        id: id_iconTickImg
        width: parent.height - parent.height*5/100
        height: parent.height - parent.height*5/100
        anchors.left: id_textInputScore.right
        anchors.leftMargin: 10
        anchors.verticalCenter: id_textInputScore.verticalCenter
        source: parseInt(id_textInputScore.text) > 2 ? "file:///home/avn/Desktop/LG_AVN_TEST/Application/Images/icon_greentick.png"
                                                     : "file:///home/avn/Desktop/LG_AVN_TEST/Application/Images/icon_redtick1.png"
    }
}
