/*
 * Copyright 2014 Canonical Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

import QtQuick 2.0

Rectangle {
    id: root
    color: "pink"

    implicitWidth: units.gu(40)
    implicitHeight: units.gu(70)

    rotation: {
        if (orientation == Qt.PortraitOrientation) return 90;
        else if (orientation == Qt.LandscapeOrientation) return 180;
        else if (orientation == Qt.InvertedPortraitOrientation) return 270;
        else return 0;
    }
    x: parent ? (parent.width - width) / 2 : 0
    y: parent ? (parent.height - height) / 2 : 0
    width: parent ? (rotation == 0 || rotation == 180 ? parent.width : parent.height) : implicitWidth
    height: parent ? (rotation == 0 || rotation == 180 ? parent.height : parent.width) : implicitHeight

    property alias screenshotSource: screenshotImage.source
    property int orientation: Qt.PortraitOrientation

    Image {
        id: screenshotImage
        anchors.fill: parent
        fillMode: Image.Stretch
    }

    Text {
        text: surfaceText.text
        color: "black"
        font: surfaceText.font
        fontSizeMode: Text.Fit
        minimumPixelSize: 10
        verticalAlignment: Text.AlignVCenter
        x: surfaceText.x
        y: surfaceText.y
        width: surfaceText.width
        height: surfaceText.height

        transform: Translate { x: -2; y: -2 }
    }
//    Text {
//        id: surfaceText
//        anchors.fill: parent
//        text: "SURFACE"
//        color: root.parent && root.parent.activeFocus ? "yellow" : "blue"
//        font.bold: true
//        fontSizeMode: Text.Fit
//        minimumPixelSize: 10; font.pixelSize: 200
//        verticalAlignment: Text.AlignVCenter
//    }
}
