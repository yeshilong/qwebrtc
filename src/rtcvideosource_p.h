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

#ifndef RTCVIDEOSOURCE_P_H
#define RTCVIDEOSOURCE_P_H

#include "rtcvideosource.h"
#include "rtcmediasource_p.h"

#include "rtc_base/thread.h"
#include "api/media_stream_interface.h"

/**
 * @brief Private implementation for the RTCVideoSource class.
 */
class RTCVideoSourcePrivate : public RTCMediaSourcePrivate
{
  public:
    /**
     * @brief Initializes a new instance of the RTCVideoSourcePrivate class.
     * @param factory The peer connection factory.
     * @param nativeMediaSource The native video source.
     */
    RTCVideoSourcePrivate(RTCPeerConnectionFactory *factory,
                          rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> nativeVideoSource);

    /**
     * @brief Initializes a new instance of the RTCMediaSourcePrivate class.
     * @param factory The peer connection factory.
     * @param nativeMediaSource The native media source.
     */
    RTCVideoSourcePrivate(RTCPeerConnectionFactory *factory,
                          rtc::scoped_refptr<webrtc::MediaSourceInterface> nativeMediaSource);

    /**
     * @brief Initializes a new instance of the RTCVideoSourcePrivate class.
     * @param factory The peer connection factory.
     * @param signalingThread The signaling thread.
     * @param workerThread The worker thread.
     */
    RTCVideoSourcePrivate(RTCPeerConnectionFactory *factory, rtc::Thread *signalingThread,
                          rtc::Thread *workerThread);

    /**
     * @brief Initializes a new instance of the RTCVideoSourcePrivate class.
     * @param factory The peer connection factory.
     * @param signalingThread The signaling thread.
     * @param workerThread The worker thread.
     * @param isScreenCast Whether the source is a screencast.
     */
    RTCVideoSourcePrivate(RTCPeerConnectionFactory *factory, rtc::Thread *signalingThread,
                          rtc::Thread *workerThread, bool isScreenCast);

    rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> nativeVideoSource() const;
    rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> nativeVideoSource_;
};

#endif // RTCVIDEOSOURCE_P_H
