import QtQuick 2.0

Item {
    // Positioning and Dimension:
    property int    heightSize: 24
    property int    textSize: 24

    // Get from Model:
    property string textCurrentScore: "0"

    signal scoreTextChanged()

//    TextInput {
//        id: id_textInputScore
//        width: 80
//        height: parent.height
////        cursorVisible: true
//        cursorPosition: 0
//        font.pixelSize: textSize
//        verticalAlignment: Text.AlignVCenter
//        maximumLength: 1
//        text: textCurrentScore
//    }
    Rectangle {
        id: id_recInputScore
        width: 80
        height: parent.height
        border.width: 1
        TextInput {
            id: id_textInputScore
            anchors.fill: parent
            anchors.verticalCenter: parent.verticalCenter
            cursorPosition: 10
            font.pixelSize: textSize
            verticalAlignment: Text.AlignVCenter
            horizontalAlignment: Text.AlignHCenter
            maximumLength: 1
            text: textCurrentScore
            onTextChanged: {
                textCurrentScore = id_textInputScore.text
//                console.log("id_textInputScore.onTextChanged >> id_textInputScore.text = " + id_textInputScore.text)
//                console.log("id_textInputScore.onTextChanged >> textCurrentScore = " + textCurrentScore)
                scoreTextChanged()
            }
        }
    }

    Image {
        id: id_iconTickImg
        width: parent.height - parent.height*5/100
        height: parent.height - parent.height*5/100
        anchors.left: id_recInputScore.right
        anchors.leftMargin: 30
        anchors.verticalCenter: id_recInputScore.verticalCenter
        source: parseInt(id_textInputScore.text) > 2 ? "file:///home/avn/Desktop/LG_AVN_TEST/Application/Images/icon_greentick.png"
                                                     : "file:///home/avn/Desktop/LG_AVN_TEST/Application/Images/icon_redtick1.png"
    }
}
