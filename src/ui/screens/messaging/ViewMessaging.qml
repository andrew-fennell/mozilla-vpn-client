/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

import QtQuick 2.5
import QtQuick.Controls 2.14
import QtQuick.Layouts 1.14

import Mozilla.VPN 1.0
import components 0.1

VPNViewBase {
    id: root
    objectName: "messagingView"

    _menuTitle: "Messages"
    _viewContentData: ColumnLayout {
        Layout.fillWidth: true

        VPNBoldLabel {
            Layout.fillWidth: true
            text: "MESSAGES!"
            horizontalAlignment: Text.AlignHCenter
        }
    }
}