import QtQuick 2.0

Item {
    // Positioning and Dimension:
    property int    heightSize: 24
    property int    textSize: 24

    // Get from Model:
    property string imgLanguageIconSource: "value"
    property string textSkillName: "value"


    Image {
        id: id_imgLanguageIcon
        x: 0
        width: heightSize
        height: heightSize
        source: imgLanguageIconSource
    }

    Text {
        id: id_textSkillName
        width: 200
        height: heightSize
        anchors.left: id_imgLanguageIcon.right
        anchors.leftMargin: 10
        anchors.verticalCenter: id_imgLanguageIcon.verticalCenter

        font.pixelSize: textSize
        font.bold: true
        color: "black"
        verticalAlignment: Text.AlignVCenter

        text: textSkillName
    }
}
