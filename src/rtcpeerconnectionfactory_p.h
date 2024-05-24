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

#ifndef RTCPEERCONNECTIONFACTORY_P_H
#define RTCPEERCONNECTIONFACTORY_P_H

#include "rtcpeerconnectionfactory.h"

#include "api/peer_connection_interface.h"
#include "api/scoped_refptr.h"
#include "rtc_base/thread.h"
#include "rtcdefaultaudioprocessingmodule.h"

namespace webrtc
{

class AudioDeviceModule;
class AudioEncoderFactory;
class AudioDecoderFactory;
class NetworkControllerFactoryInterface;
class VideoEncoderFactory;
class VideoDecoderFactory;
class AudioProcessing;
struct PeerConnectionDependencies;

} // namespace webrtc

class RTCPeerConnectionFactoryPrivate
{
  public:
    explicit RTCPeerConnectionFactoryPrivate(bool hasNoMedia = false);
    explicit RTCPeerConnectionFactoryPrivate(
        rtc::scoped_refptr<webrtc::AudioEncoderFactory> audioEncoderFactory,
        rtc::scoped_refptr<webrtc::AudioDecoderFactory> audioDecoderFactory,
        std::unique_ptr<webrtc::VideoEncoderFactory> videoEncoderFactory,
        std::unique_ptr<webrtc::VideoDecoderFactory> videoDecoderFactory,
        webrtc::AudioDeviceModule *audioDeviceModule,
        rtc::scoped_refptr<webrtc::AudioProcessing> audioProcessingModule,
        bool bypassVoiceProcessing);
    explicit RTCPeerConnectionFactoryPrivate(
        rtc::scoped_refptr<webrtc::AudioEncoderFactory> audioEncoderFactory,
        rtc::scoped_refptr<webrtc::AudioDecoderFactory> audioDecoderFactory,
        std::unique_ptr<webrtc::VideoEncoderFactory> videoEncoderFactory,
        std::unique_ptr<webrtc::VideoDecoderFactory> videoDecoderFactory,
        webrtc::AudioDeviceModule *audioDeviceModule,
        rtc::scoped_refptr<webrtc::AudioProcessing> audioProcessingModule,
        std::unique_ptr<webrtc::NetworkControllerFactoryInterface> networkControllerFactory,
        bool bypassVoiceProcessing);

    void initNativePeerConnectionFactory();
    void initNativePeerConnectionFactoryWithNoMedia();

    RTCPeerConnection *peerConnectionWithDependencies(
        RTCConfiguration *configuration, RTCMediaConstraints *constraints,
        std::unique_ptr<webrtc::PeerConnectionDependencies> dependencies,
        IRTCPeerConnectionDelegate *delegate);

    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> nativePeerConnectionFactory() const;
    rtc::Thread *signalingThread() const;
    rtc::Thread *workerThread() const;
    rtc::Thread *networkThread() const;

    rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> nativePeerConnectionFactory_;
    std::unique_ptr<rtc::Thread> signalingThread_;
    std::unique_ptr<rtc::Thread> workerThread_;
    std::unique_ptr<rtc::Thread> networkThread_;
    rtc::scoped_refptr<webrtc::AudioDeviceModule> nativeAudioDeviceModule_;
    RTCDefaultAudioProcessingModule *defaultAudioProcessingModule_;
    RTCAudioDeviceModule *audioDeviceModule_;

    RTCPeerConnectionFactory *q_ptr;
};

#endif // RTCPEERCONNECTIONFACTORY_P_H
