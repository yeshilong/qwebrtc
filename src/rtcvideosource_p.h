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
