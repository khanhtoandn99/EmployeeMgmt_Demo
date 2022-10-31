import QtQuick 2.0

Item {
    // Positioning and Dimension:
    property int    heightSize: 24
    property int    textSize: 24

    // Get from Model:
    property string textCurrentScore: "0"

    TextInput {
        id: id_textInputScore
        width: 80
        height: parent.height
        cursorVisible: true
        cursorPosition: 0
        font.pixelSize: textSize
        verticalAlignment: Text.AlignVCenter
        maximumLength: 1
        text: textCurrentScore
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
