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

#ifndef RTCMEDIASTREAMTRACK_P_H
#define RTCMEDIASTREAMTRACK_P_H

#include <QObject>

#include "rtctypes.h"

#include "api/media_stream_interface.h"

class RTCPeerConnectionFactory;
class RTCMediaStreamTrack;

class RTCMediaStreamTrackPrivate
{
  public:
    /**
     * @brief RTCMediaStreamTrackPrivate
     * @param nativeMediaStreamTrack The native media stream track.
     * @param factory The peer connection factory.
     * @param type The type of the media stream track.
     */
    explicit RTCMediaStreamTrackPrivate(
        RTCPeerConnectionFactory *factory,
        const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack,
        RTCMediaStreamTrackType type);

    /**
     * @brief RTCMediaStreamTrackPrivate
     * @param nativeMediaStreamTrack The native media stream track.
     * @param factory The peer connection factory.
     */
    RTCMediaStreamTrackPrivate(
        RTCPeerConnectionFactory *factory,
        const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack);

    /**
     * @brief Returns the native media stream track.
     * @return The native media stream track.
     */
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack() const;

    /**
     * @brief Checks if the media stream track is equal to another media stream track.
     * @return True if the media stream track is equal to the other media stream track, false otherwise.
     */
    bool isEqualToTrack(RTCMediaStreamTrackPrivate *other) const;

    /**
     * @brief Creates a media stream track for a native media stream track.
     * @return The media stream track.
     */
    static RTCMediaStreamTrack *mediaStreamTrackForNativeMediaStreamTrack(
        const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack,
        RTCPeerConnectionFactory *factory);

    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack_;
    RTCPeerConnectionFactory *factory_;
    RTCMediaStreamTrackType type_;
};

#endif // RTCMEDIASTREAMTRACK_P_H
