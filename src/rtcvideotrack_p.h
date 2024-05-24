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

#ifndef RTCVIDEOTRACK_P_H
#define RTCVIDEOTRACK_P_H

#include <QObject>

#include "rtcvideotrack.h"
#include "rtcmediastreamtrack_p.h"
#include "rtcvideosource_p.h"
#include "rtcvideorendereradapter_p.h"

#include "rtc_base/thread.h"

class RTCVideoTrack;
class RTCVideoTrackPrivate : public RTCMediaStreamTrackPrivate
{
  public:
    explicit RTCVideoTrackPrivate(RTCPeerConnectionFactory *factory, RTCVideoSource *source,
                                  QString trackId);
    explicit RTCVideoTrackPrivate(
        RTCPeerConnectionFactory *factory,
        const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeVideoTrack,
        RTCMediaStreamTrackType type);

    rtc::scoped_refptr<webrtc::VideoTrackInterface> nativeVideoTrack() const;

    rtc::Thread *workerThread_;
    RTCVideoSource *source_;
    QVector<RTCVideoRendererAdapter *> adapters_;
};

#endif // RTCVIDEOTRACK_P_H
