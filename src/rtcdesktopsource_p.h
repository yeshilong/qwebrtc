/*
 * Copyright (C) 2024 Deltarion Systems
 *
 * This software is licensed under the terms of the GNU Lesser
 * General Public License (LGPL) version 3 as published by the Free
 * Software Foundation. This license is available at:
 * https://www.gnu.org/licenses/lgpl-3.0.html
 *
 * You are free to modify and distribute this software under the
 * terms of the LGPLv3 license. You are required to make the source
 * code of any modifications available under the same license.
 */
#ifndef RTCDESKTOPSOURCE_P_H
#define RTCDESKTOPSOURCE_P_H

#include "rtcdesktopsource.h"

#include "native/objc_desktop_media_list.h"

class RTCDesktopSourcePrivate
{
  public:
    RTCDesktopSourcePrivate();
    RTCDesktopSourcePrivate(webrtc::MediaSource *nativeDesktopSource, RTCDesktopSourceType type);
    webrtc::MediaSource *nativeDesktopSource();

    QString sourceId_;
    QString name_;
    QImage thumbnail_;
    RTCDesktopSourceType sourceType_;
    webrtc::MediaSource *nativeMediaSource_;
};

#endif // RTCDESKTOPSOURCE_P_H
