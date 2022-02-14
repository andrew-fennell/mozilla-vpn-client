/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

import QtQuick 2.0
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import Mozilla.VPN 1.0
import components 0.1

TextField {
    // TODO Add strings for Accessible.description, Accessible.name
    property bool hasError: false
    property bool showInteractionStates: true
    property bool forceBlurOnOutsidePress: true
    property bool isPassword: false
    property bool charactersMasked: isPassword
    property alias _placeholderText: centeredPlaceholderText.text

    id: textField

    background: VPNInputBackground {
        id: textFieldBackground
    }

    font.pixelSize: VPNTheme.theme.fontSizeSmall
    font.family: VPNTheme.theme.fontInterFamily
    color: VPNTheme.colors.input.default.text
    echoMode: charactersMasked ? TextInput.Password : TextInput.Normal
    inputMethodHints: Qt.ImhNoPredictiveText | Qt.ImhSensitiveData
    onActiveFocusChanged: if (focus && typeof(vpnFlickable) !== "undefined" && vpnFlickable.ensureVisible) vpnFlickable.ensureVisible(textField)
    selectByMouse: true
    Layout.preferredHeight: VPNTheme.theme.rowHeight
    Layout.alignment: Qt.AlignVCenter
    verticalAlignment: Text.AlignVCenter
    placeholderTextColor: VPNTheme.colors.grey40
    leftPadding: VPNTheme.theme.windowMargin
    rightPadding: VPNTheme.theme.windowMargin

    PlaceholderText {
        id: centeredPlaceholderText
        verticalAlignment: textField.verticalAlignment
        width: textField.width - (textField.leftPadding + textField.rightPadding)
        height: textField.height
        elide: Text.ElideRight
        x: textField.leftPadding
        visible: !textField.length && !textField.preeditText
        font: textField.font
        color: textField.placeholderTextColor
    }

    VPNIconButton {
        id: iconButton

        // TODO: Add accesibleName string
        accessibleName: ""
        anchors {
            right: parent.right
            rightMargin: VPNTheme.theme.listSpacing / 2
            verticalCenter: parent.verticalCenter
        }
        height: parent.height - VPNTheme.theme.listSpacing
        visible: isPassword
        width: parent.height - VPNTheme.theme.listSpacing
        onClicked: {
            charactersMasked = !charactersMasked
        }

        Image {
            id: backImage

            anchors.centerIn: iconButton
            fillMode: Image.PreserveAspectFit
            source: charactersMasked ? "qrc:/nebula/resources/eye-hidden.svg" : "qrc:/nebula/resources/eye-visible.svg"
            sourceSize.height: VPNTheme.theme.iconSize * 1.5
            sourceSize.width: VPNTheme.theme.iconSize * 1.5
        }
    }

    VPNInputStates {
        id: textFieldState
        itemToTarget: textField
    }
}
