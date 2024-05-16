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
#ifndef RTCPEERCONNECTIONFACTORY_P_H
#define RTCPEERCONNECTIONFACTORY_P_H

#include "rtcpeerconnectionfactory.h"

#include "api/peer_connection_interface.h"
#include "api/scoped_refptr.h"
#include "rtc_base/thread.h"

class RTCPeerConnectionFactoryPrivate
{
  public:
    explicit RTCPeerConnectionFactoryPrivate();

    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> nativePeerConnectionFactory() const;
    rtc::Thread *signalingThread() const;
    rtc::Thread *workerThread() const;
    rtc::Thread *networkThread() const;

    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> nativePeerConnectionFactory_;
    rtc::Thread *signalingThread_;
    rtc::Thread *workerThread_;
    rtc::Thread *networkThread_;
};

#endif // RTCPEERCONNECTIONFACTORY_P_H
