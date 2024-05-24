// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
