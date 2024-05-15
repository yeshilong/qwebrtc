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
