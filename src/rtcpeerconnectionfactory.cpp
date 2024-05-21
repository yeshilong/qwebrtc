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

#include "rtcpeerconnectionfactory_p.h"

#include "rtcaudiodevicemodule_p.h"
#include "rtcmediaconstraints_p.h"
#include "rtcaudiosource_p.h"
#include "rtcvideosource_p.h"
#include "rtcaudiotrack_p.h"
#include "rtcvideotrack_p.h"
#include "rtcmediastream_p.h"
#include "rtcpeerconnection_p.h"
#include "rtcrtpcapabilities_p.h"
#include "rtcpeerconnectionfactoryoptions_p.h"
#include "rtcvideodecoderfactoryh264.h"
#include "rtcvideoencoderfactoryh264.h"
#include "rtcdefaultaudioprocessingmodule_p.h"

#include "rtc_base/checks.h"
#include "system_wrappers/include/field_trial.h"
#include "api/audio_codecs/builtin_audio_decoder_factory.h"
#include "api/audio_codecs/builtin_audio_encoder_factory.h"
#include "api/rtc_event_log/rtc_event_log_factory.h"
#include "api/task_queue/default_task_queue_factory.h"
#include "api/transport/field_trial_based_config.h"
#include "media/engine/webrtc_media_engine.h"
#include "modules/audio_device/include/audio_device.h"
#include "modules/audio_processing/include/audio_processing.h"

#include "native/network_monitor_factory.h"
#include "native/ssl_certificate_verifier.h"

#include "native/objc_audio_device_module.h"
#include "native/objc_video_decoder_factory.h"
#include "native/objc_video_encoder_factory.h"

#if defined(WEBRTC_IOS)
#import "native/audio_device_module.h"
#endif // WEBRTC_IOS

rtc::scoped_refptr<webrtc::AudioDeviceModule> createAudioDeviceModule(bool bypassVoiceProcessing)
{
#if defined(WEBRTC_IOS)
    return webrtc::CreateAudioDeviceModule(bypassVoiceProcessing);
#else
    return nullptr;
#endif
}

void RTCPeerConnectionFactoryPrivate::initNativePeerConnectionFactory()
{
    networkThread_ = rtc::Thread::CreateWithSocketServer();
    networkThread_->SetName("network_thread", networkThread_.get());
    bool result = networkThread_->Start();
    RTC_DCHECK(result) << "Failed to start network thread.";

    workerThread_ = rtc::Thread::Create();
    workerThread_->SetName("worker_thread", workerThread_.get());
    result = workerThread_->Start();
    RTC_DCHECK(result) << "Failed to start worker thread.";

    signalingThread_ = rtc::Thread::Create();
    signalingThread_->SetName("signaling_thread", signalingThread_.get());
    result = signalingThread_->Start();
    RTC_DCHECK(result) << "Failed to start signaling thread.";
}

void RTCPeerConnectionFactoryPrivate::initNativePeerConnectionFactoryWithNoMedia()
{
    initNativePeerConnectionFactory();

    webrtc::PeerConnectionFactoryDependencies dependencies;
    dependencies.network_thread = networkThread_.get();
    dependencies.worker_thread = workerThread_.get();
    dependencies.signaling_thread = signalingThread_.get();
    if (webrtc::field_trial::IsEnabled("WebRTC-Network-UseNWPathMonitor"))
    {
        dependencies.network_monitor_factory = webrtc::CreateNetworkMonitorFactory();
    }
    nativePeerConnectionFactory_ =
        webrtc::CreateModularPeerConnectionFactory(std::move(dependencies));
    Q_ASSERT_X(nativePeerConnectionFactory_ != nullptr, "RTCPeerConnectionFactoryPrivate",
               "Failed to initialize PeerConnectionFactory!");
}

RTCPeerConnectionFactoryPrivate::RTCPeerConnectionFactoryPrivate(bool hasNoMedia)
{
    if (hasNoMedia)
    {
        initNativePeerConnectionFactoryWithNoMedia();
    }
    else
    {
        initNativePeerConnectionFactory();
    }
}

RTCPeerConnectionFactoryPrivate::RTCPeerConnectionFactoryPrivate(
    rtc::scoped_refptr<webrtc::AudioEncoderFactory> audioEncoderFactory,
    rtc::scoped_refptr<webrtc::AudioDecoderFactory> audioDecoderFactory,
    std::unique_ptr<webrtc::VideoEncoderFactory> videoEncoderFactory,
    std::unique_ptr<webrtc::VideoDecoderFactory> videoDecoderFactory,
    webrtc::AudioDeviceModule *audioDeviceModule,
    rtc::scoped_refptr<webrtc::AudioProcessing> audioProcessingModule, bool bypassVoiceProcessing)
    : RTCPeerConnectionFactoryPrivate(
          audioEncoderFactory, audioDecoderFactory, std::move(videoEncoderFactory),
          std::move(videoDecoderFactory), audioDeviceModule, audioProcessingModule, nullptr, false)
{
}

RTCPeerConnectionFactoryPrivate::RTCPeerConnectionFactoryPrivate(
    rtc::scoped_refptr<webrtc::AudioEncoderFactory> audioEncoderFactory,
    rtc::scoped_refptr<webrtc::AudioDecoderFactory> audioDecoderFactory,
    std::unique_ptr<webrtc::VideoEncoderFactory> videoEncoderFactory,
    std::unique_ptr<webrtc::VideoDecoderFactory> videoDecoderFactory,
    webrtc::AudioDeviceModule *audioDeviceModule,
    rtc::scoped_refptr<webrtc::AudioProcessing> audioProcessingModule,
    std::unique_ptr<webrtc::NetworkControllerFactoryInterface> networkControllerFactory,
    bool bypassVoiceProcessing)
{
    initNativePeerConnectionFactory();

    webrtc::PeerConnectionFactoryDependencies dependencies;
    dependencies.network_thread = networkThread_.get();
    dependencies.worker_thread = workerThread_.get();
    dependencies.signaling_thread = signalingThread_.get();
    if (webrtc::field_trial::IsEnabled("WebRTC-Network-UseNWPathMonitor"))
    {
        dependencies.network_monitor_factory = webrtc::CreateNetworkMonitorFactory();
    }
    dependencies.trials = std::make_unique<webrtc::FieldTrialBasedConfig>();
    dependencies.task_queue_factory =
        webrtc::CreateDefaultTaskQueueFactory(dependencies.trials.get());
    cricket::MediaEngineDependencies media_deps;

    // always create ADM on worker thread
    nativeAudioDeviceModule_ =
        workerThread_->BlockingCall([&dependencies, &bypassVoiceProcessing]() {
            return webrtc::AudioDeviceModule::Create(
                webrtc::AudioDeviceModule::AudioLayer::kPlatformDefaultAudio,
                dependencies.task_queue_factory.get(), bypassVoiceProcessing == true);
        });

    audioDeviceModule_ = new RTCAudioDeviceModule(
        new RTCAudioDeviceModulePrivate(nativeAudioDeviceModule_, workerThread_.get()));

    media_deps.adm = nativeAudioDeviceModule_;
    media_deps.task_queue_factory = dependencies.task_queue_factory.get();
    media_deps.audio_encoder_factory = std::move(audioEncoderFactory);
    media_deps.audio_decoder_factory = std::move(audioDecoderFactory);
    media_deps.video_encoder_factory = std::move(videoEncoderFactory);
    media_deps.video_decoder_factory = std::move(videoDecoderFactory);
    if (audioProcessingModule)
    {
        media_deps.audio_processing = std::move(audioProcessingModule);
    }
    else
    {
        media_deps.audio_processing = webrtc::AudioProcessingBuilder().Create();
    }
    media_deps.trials = dependencies.trials.get();
    dependencies.media_engine = cricket::CreateMediaEngine(std::move(media_deps));
    dependencies.call_factory = webrtc::CreateCallFactory();
    dependencies.event_log_factory =
        std::make_unique<webrtc::RtcEventLogFactory>(dependencies.task_queue_factory.get());
    dependencies.network_controller_factory = std::move(networkControllerFactory);
    nativePeerConnectionFactory_ =
        webrtc::CreateModularPeerConnectionFactory(std::move(dependencies));
    Q_ASSERT_X(nativePeerConnectionFactory_ != nullptr, "RTCPeerConnectionFactoryPrivate",
               "Failed to initialize PeerConnectionFactory!");
}

RTCPeerConnection *RTCPeerConnectionFactoryPrivate::peerConnectionWithDependencies(
    RTCConfiguration *configuration, RTCMediaConstraints *constraints,
    std::unique_ptr<webrtc::PeerConnectionDependencies> dependencies,
    IRTCPeerConnectionDelegate *delegate)
{
    return new RTCPeerConnection(*(new RTCPeerConnectionPrivate(
        q_ptr, configuration, constraints, std::move(dependencies), delegate)));
}

rtc::scoped_refptr<webrtc::PeerConnectionFactoryInterface> RTCPeerConnectionFactoryPrivate::
    nativePeerConnectionFactory() const
{
    return nativePeerConnectionFactory_;
}

rtc::Thread *RTCPeerConnectionFactoryPrivate::signalingThread() const
{
    return signalingThread_.get();
}

rtc::Thread *RTCPeerConnectionFactoryPrivate::workerThread() const
{
    return workerThread_.get();
}

rtc::Thread *RTCPeerConnectionFactoryPrivate::networkThread() const
{
    return networkThread_.get();
}

RTCPeerConnectionFactory::RTCPeerConnectionFactory(QObject *parent)
    : QObject{parent},
      d_ptr(new RTCPeerConnectionFactoryPrivate(
          webrtc::CreateBuiltinAudioEncoderFactory(), webrtc::CreateBuiltinAudioDecoderFactory(),
          webrtc::ObjCToNativeVideoEncoderFactory(new RTCVideoEncoderFactoryH264()),
          webrtc::ObjCToNativeVideoDecoderFactory(new RTCVideoDecoderFactoryH264()),
          createAudioDeviceModule(false).get(), webrtc::AudioProcessingBuilder().Create(), nullptr,
          false))
{
    d_ptr->q_ptr = this;
}

RTCPeerConnectionFactory::RTCPeerConnectionFactory(RTCPeerConnectionFactoryPrivate &d,
                                                   QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
    d_ptr->q_ptr = this;
}

RTCPeerConnectionFactory::RTCPeerConnectionFactory(IRTCVideoEncoderFactory *encoderFactory,
                                                   IRTCVideoDecoderFactory *decoderFactory,
                                                   QObject *parent)
    : RTCPeerConnectionFactory(encoderFactory, decoderFactory, nullptr, parent)
{
}

RTCPeerConnectionFactory::RTCPeerConnectionFactory(IRTCVideoEncoderFactory *encoderFactory,
                                                   IRTCVideoDecoderFactory *decoderFactory,
                                                   IRTCAudioDevice *audioDevice, QObject *parent)
    : QObject{parent}
{
#ifdef HAVE_NO_MEDIA
    d_ptr = new RTCPeerConnectionFactoryPrivate(true);
#else
    std::unique_ptr<webrtc::VideoEncoderFactory> native_encoder_factory;
    std::unique_ptr<webrtc::VideoDecoderFactory> native_decoder_factory;
    if (encoderFactory)
    {
        native_encoder_factory = webrtc::ObjCToNativeVideoEncoderFactory(encoderFactory);
    }
    if (decoderFactory)
    {
        native_decoder_factory = webrtc::ObjCToNativeVideoDecoderFactory(decoderFactory);
    }
    rtc::scoped_refptr<webrtc::AudioDeviceModule> audio_device_module;
    if (audioDevice)
    {
#if defined(WEBRTC_IOS)
        audio_device_module = webrtc::CreateAudioDeviceModule(audioDevice);
#else
        audio_device_module = webrtc::CreateAudioDeviceModule();
#endif // WEBRTC_IOS
    }
    else
    {
        audio_device_module = createAudioDeviceModule(false);
    }
    d_ptr = new RTCPeerConnectionFactoryPrivate(
        webrtc::CreateBuiltinAudioEncoderFactory(), webrtc::CreateBuiltinAudioDecoderFactory(),
        std::move(native_encoder_factory), std::move(native_decoder_factory),
        audio_device_module.get(), nullptr, false);
    d_ptr->q_ptr = this;
#endif // HAVE_NO_MEDIA
}

RTCPeerConnectionFactory::RTCPeerConnectionFactory(IRTCVideoEncoderFactory *encoderFactory,
                                                   IRTCVideoDecoderFactory *decoderFactory,
                                                   IRTCAudioProcessingModule *audioProcessingModule,
                                                   bool bypassVoiceProcessing, QObject *parent)
    : QObject{parent}
{
#ifdef HAVE_NO_MEDIA
    d_ptr = new RTCPeerConnectionFactoryPrivate(true);
#else
    std::unique_ptr<webrtc::VideoEncoderFactory> native_encoder_factory;
    std::unique_ptr<webrtc::VideoDecoderFactory> native_decoder_factory;
    if (encoderFactory)
    {
        native_encoder_factory = webrtc::ObjCToNativeVideoEncoderFactory(encoderFactory);
    }
    if (decoderFactory)
    {
        native_decoder_factory = webrtc::ObjCToNativeVideoDecoderFactory(decoderFactory);
    }
    rtc::scoped_refptr<webrtc::AudioDeviceModule> audio_device_module =
        createAudioDeviceModule(bypassVoiceProcessing);

    RTCDefaultAudioProcessingModule *defaultAudioProcessingModule = nullptr;
    if (dynamic_cast<RTCDefaultAudioProcessingModule *>(audioProcessingModule))
    {
        defaultAudioProcessingModule =
            dynamic_cast<RTCDefaultAudioProcessingModule *>(audioProcessingModule);
    }
    else
    {
        defaultAudioProcessingModule = new RTCDefaultAudioProcessingModule();
    }

    d_ptr = new RTCPeerConnectionFactoryPrivate(
        webrtc::CreateBuiltinAudioEncoderFactory(), webrtc::CreateBuiltinAudioDecoderFactory(),
        std::move(native_encoder_factory), std::move(native_decoder_factory),
        audio_device_module.get(),
        defaultAudioProcessingModule->d_ptr->nativeAudioProcessingModule(), bypassVoiceProcessing);
    d_ptr->q_ptr = this;
#endif
}

RTCAudioDeviceModule *RTCPeerConnectionFactory::audioDeviceModule() const
{
    Q_D(const RTCPeerConnectionFactory);
    return d->audioDeviceModule_;
}

RTCRtpCapabilities *RTCPeerConnectionFactory::rtpSenderCapabilitiesFor(RTCRtpMediaType mediaType)
{
    Q_D(RTCPeerConnectionFactory);
    webrtc::RtpCapabilities capabilities =
        d->nativePeerConnectionFactory_->GetRtpSenderCapabilities(
            static_cast<cricket::MediaType>(mediaType));
    return new RTCRtpCapabilities(*(new RTCRtpCapabilitiesPrivate(capabilities)));
}

RTCRtpCapabilities *RTCPeerConnectionFactory::rtpReceiverCapabilitiesFor(RTCRtpMediaType mediaType)
{
    Q_D(RTCPeerConnectionFactory);
    webrtc::RtpCapabilities capabilities =
        d->nativePeerConnectionFactory_->GetRtpReceiverCapabilities(
            static_cast<cricket::MediaType>(mediaType));
    return new RTCRtpCapabilities(*(new RTCRtpCapabilitiesPrivate(capabilities)));
}

RTCAudioSource *RTCPeerConnectionFactory::audioSourceWithConstraints(
    RTCMediaConstraints *constraints)
{
    Q_D(RTCPeerConnectionFactory);
    std::unique_ptr<webrtc::MediaConstraints> nativeConstraints;
    if (constraints)
    {
        nativeConstraints = constraints->d_ptr->nativeMediaConstraints();
    }
    cricket::AudioOptions options;
    CopyConstraintsIntoAudioOptions(nativeConstraints.get(), &options);

    rtc::scoped_refptr<webrtc::AudioSourceInterface> source =
        d->nativePeerConnectionFactory_->CreateAudioSource(options);
    return new RTCAudioSource(*(new RTCAudioSourcePrivate(this, source)));
}

RTCAudioTrack *RTCPeerConnectionFactory::audioTrackWithSource(RTCAudioSource *source,
                                                              QString trackId)
{
    Q_D(RTCPeerConnectionFactory);
    return new RTCAudioTrack(*(new RTCAudioTrackPrivate(this, source, trackId)));
}

RTCAudioTrack *RTCPeerConnectionFactory::audioTrackWithTrackId(QString trackId)
{
    Q_D(RTCPeerConnectionFactory);
    RTCAudioSource *source = audioSourceWithConstraints(nullptr);
    return new RTCAudioTrack(*(new RTCAudioTrackPrivate(this, source, trackId)));
}

RTCVideoSource *RTCPeerConnectionFactory::videoSource()
{
    Q_D(RTCPeerConnectionFactory);
    return new RTCVideoSource(
        *(new RTCVideoSourcePrivate(this, d->signalingThread_.get(), d->workerThread_.get())));
}

RTCVideoSource *RTCPeerConnectionFactory::videoSourceForScreenCast(bool forScreenCast)
{
    Q_D(RTCPeerConnectionFactory);
    return new RTCVideoSource(*(new RTCVideoSourcePrivate(this, d->signalingThread_.get(),
                                                          d->workerThread_.get(), forScreenCast)));
}

RTCVideoTrack *RTCPeerConnectionFactory::videoTrackWithSource(RTCVideoSource *source,
                                                              QString trackId)
{
    Q_D(RTCPeerConnectionFactory);
    return new RTCVideoTrack(*(new RTCVideoTrackPrivate(this, source, trackId)));
}

RTCMediaStream *RTCPeerConnectionFactory::mediaStreamWithStreamId(QString streamId)
{
    Q_D(RTCPeerConnectionFactory);
    return new RTCMediaStream(*(new RTCMediaStreamPrivate(this, streamId)));
}

RTCPeerConnection *RTCPeerConnectionFactory::peerConnectionWithConfiguration(
    RTCConfiguration *configuration, RTCMediaConstraints *constraints,
    IRTCPeerConnectionDelegate *peerConnectionDelegate)
{
    Q_D(RTCPeerConnectionFactory);
    return new RTCPeerConnection(*(new RTCPeerConnectionPrivate(this, configuration, constraints,
                                                                nullptr, peerConnectionDelegate)));
}

RTCPeerConnection *RTCPeerConnectionFactory::peerConnectionWithConfiguration(
    RTCConfiguration *configuration, RTCMediaConstraints *constraints,
    IRTCSSLCertificateVerifier *certificateVerifier,
    IRTCPeerConnectionDelegate *peerConnectionDelegate)
{
    Q_D(RTCPeerConnectionFactory);
    return new RTCPeerConnection(*(new RTCPeerConnectionPrivate(
        this, configuration, constraints, certificateVerifier, peerConnectionDelegate)));
}

void RTCPeerConnectionFactory::setOptions(RTCPeerConnectionFactoryOptions *options)
{
    RTC_DCHECK(options != nullptr);
    Q_D(RTCPeerConnectionFactory);
    d->nativePeerConnectionFactory_->SetOptions(
        options->d_ptr->nativePeerConnectionFactoryOptions());
}

bool RTCPeerConnectionFactory::startAecDumpWithFilePath(QString filePath, qint64 maxSizeInBytes)
{
    Q_D(RTCPeerConnectionFactory);

    RTC_DCHECK(filePath.size());
    RTC_DCHECK_GT(maxSizeInBytes, 0);

    if (hasStartedAecDump_)
    {
        RTCLogError("Aec dump already started.");
        return false;
    }
    FILE *f = fopen(filePath.toUtf8(), "wb");
    if (!f)
    {
        RTCLogError("Error opening file: %@. Error: %s", filePath, strerror(errno));
        return false;
    }
    hasStartedAecDump_ = d->nativePeerConnectionFactory_->StartAecDump(f, maxSizeInBytes);
    return hasStartedAecDump_;
}

void RTCPeerConnectionFactory::stopAecDump()
{
    Q_D(RTCPeerConnectionFactory);
    d->nativePeerConnectionFactory_->StopAecDump();
    hasStartedAecDump_ = false;
}
