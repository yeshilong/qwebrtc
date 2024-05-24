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

#ifndef RTCMEDIASTREAM_P_H
#define RTCMEDIASTREAM_P_H

#include "rtcmediastream.h"

#include "rtc_base/thread.h"
#include "api/media_stream_interface.h"

class RTCMediaStreamPrivate
{
  public:
    explicit RTCMediaStreamPrivate();
    explicit RTCMediaStreamPrivate(RTCPeerConnectionFactory *factory, QString streamId);
    explicit RTCMediaStreamPrivate(
        RTCPeerConnectionFactory *factory,
        rtc::scoped_refptr<webrtc::MediaStreamInterface> nativeMediaStream);

    /**
     * @brief Gets the audio tracks in this stream.
     * @return The audio tracks.
     */
    QVector<RTCAudioTrack *> audioTracks() const;

    /**
     * @brief Gets the video tracks in this stream.
     * @return The video tracks.
     */
    QVector<RTCVideoTrack *> videoTracks() const;

    /**
     * @brief Adds the given audio track to this media stream.
     * @param audioTrack The audio track.
     */
    void addAudioTrack(RTCAudioTrack *audioTrack);

    /**
     * @brief Adds the given video track to this media stream.
     * @param videoTrack The video track.
     */
    void addVideoTrack(RTCVideoTrack *videoTrack);

    /**
     * @brief Removes the given audio track from this media stream.
     * @param audioTrack The audio track.
     */
    void removeAudioTrack(RTCAudioTrack *audioTrack);

    /**
     * @brief Removes the given video track from this media stream.
     * @param videoTrack The video track.
     */
    void removeVideoTrack(RTCVideoTrack *videoTrack);

    /**
     * @brief Gets the native media stream.
     * @return The native media stream.
     */
    rtc::scoped_refptr<webrtc::MediaStreamInterface> nativeMediaStream() const;

    rtc::scoped_refptr<webrtc::MediaStreamInterface> nativeMediaStream_;
    rtc::Thread *signalingThread_;
    QVector<RTCAudioTrack *> audioTracks_;
    QVector<RTCVideoTrack *> videoTracks_;
    RTCPeerConnectionFactory *factory_;
};

#endif // RTCMEDIASTREAM_P_H
