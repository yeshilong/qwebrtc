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
#ifndef RTCDESKTOPMEDIALIST_P_H
#define RTCDESKTOPMEDIALIST_P_H

#include "rtcdesktopmedialist.h"

class RTCDesktopMediaListPrivate
{
  public:
    void mediaSourceAdded(webrtc::MediaSource *source);
    void mediaSourceRemoved(webrtc::MediaSource *source);
    void mediaSourceNameChanged(webrtc::MediaSource *source);
    void mediaSourceThumbnailChanged(webrtc::MediaSource *source);

    RTCDesktopSource *getSourceById(webrtc::MediaSource *source);

    std::shared_ptr<webrtc::ObjCDesktopMediaList> nativeDesktopMediaList() const;
    std::shared_ptr<webrtc::ObjCDesktopMediaList> nativeDesktopMediaList_;

    RTCDesktopSourceType sourceType_;
    RTCDesktopMediaListDelegate *delegate_;
    QVector<RTCDesktopSource *> sources_;
};

#endif // RTCDESKTOPMEDIALIST_P_H
