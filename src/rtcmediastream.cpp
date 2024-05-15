#include "rtcmediastream_p.h"

#include "rtcaudiotrack_p.h"
#include "rtcvideotrack_p.h"
#include "rtcmediastreamtrack_p.h"
#include "rtcpeerconnectionfactory_p.h"

RTCMediaStreamPrivate::RTCMediaStreamPrivate()
    : nativeMediaStream_{nullptr}, signalingThread_{nullptr}
{
}

RTCMediaStreamPrivate::RTCMediaStreamPrivate(RTCPeerConnectionFactory *factory, QString streamId)
    : nativeMediaStream_{nullptr}, signalingThread_{nullptr}, factory_{factory}
{
    Q_ASSERT(factory);
    Q_ASSERT(!streamId.isEmpty());
    rtc::scoped_refptr<webrtc::MediaStreamInterface> stream =
        factory->d_ptr->nativePeerConnectionFactory()->CreateLocalMediaStream(
            streamId.toStdString());
}

RTCMediaStreamPrivate::RTCMediaStreamPrivate(
    RTCPeerConnectionFactory *factory,
    rtc::scoped_refptr<webrtc::MediaStreamInterface> nativeMediaStream)
{
    Q_ASSERT(factory);
    Q_ASSERT(nativeMediaStream);

    factory_ = factory;
    signalingThread_ = factory->d_ptr->signalingThread();

    webrtc::AudioTrackVector audioTracks = nativeMediaStream->GetAudioTracks();
    webrtc::VideoTrackVector videoTracks = nativeMediaStream->GetVideoTracks();

    audioTracks_.reserve(audioTracks.size());
    videoTracks_.reserve(videoTracks.size());
    nativeMediaStream_ = nativeMediaStream;

    for (const auto &track : audioTracks)
    {
        RTCMediaStreamTrackType type = RTCMediaStreamTrackType::RTCMediaStreamTrackTypeAudio;
        RTCAudioTrack *audioTrack =
            new RTCAudioTrack(*(new RTCAudioTrackPrivate(factory_, track, type)));
        audioTracks_.push_back(audioTrack);
    }

    for (const auto &track : videoTracks)
    {
        RTCMediaStreamTrackType type = RTCMediaStreamTrackType::RTCMediaStreamTrackTypeVideo;
        RTCVideoTrack *videoTrack =
            new RTCVideoTrack(*(new RTCVideoTrackPrivate(factory_, track, type)));
        videoTracks_.push_back(videoTrack);
    }
}

QVector<RTCAudioTrack *> RTCMediaStreamPrivate::audioTracks() const
{
    if (!signalingThread_->IsCurrent())
    {
        return signalingThread_->BlockingCall([this]() { return audioTracks_; });
    }
    return audioTracks_;
}

QVector<RTCVideoTrack *> RTCMediaStreamPrivate::videoTracks() const
{
    if (!signalingThread_->IsCurrent())
    {
        return signalingThread_->BlockingCall([this]() { return videoTracks_; });
    }
    return videoTracks_;
}

void RTCMediaStreamPrivate::addAudioTrack(RTCAudioTrack *audioTrack)
{
    Q_ASSERT(audioTrack);
    if (!signalingThread_->IsCurrent())
    {
        return signalingThread_->BlockingCall(
            [audioTrack, this]() { return this->addAudioTrack(audioTrack); });
    }

    if (nativeMediaStream_->AddTrack(
            ((RTCAudioTrackPrivate *)(audioTrack->d_ptr))->nativeAudioTrack()))
    {
        audioTracks_.push_back(audioTrack);
    }
}

void RTCMediaStreamPrivate::addVideoTrack(RTCVideoTrack *videoTrack)
{
    Q_ASSERT(videoTrack);
    if (!signalingThread_->IsCurrent())
    {
        return signalingThread_->BlockingCall(
            [videoTrack, this]() { return this->addVideoTrack(videoTrack); });
    }

    if (nativeMediaStream_->AddTrack(
            ((RTCVideoTrackPrivate *)(videoTrack->d_ptr))->nativeVideoTrack()))
    {
        videoTracks_.push_back(videoTrack);
    }
}

void RTCMediaStreamPrivate::removeAudioTrack(RTCAudioTrack *audioTrack)
{
    Q_ASSERT(audioTrack);
    if (!signalingThread_->IsCurrent())
    {
        return signalingThread_->BlockingCall(
            [audioTrack, this]() { return this->removeAudioTrack(audioTrack); });
    }

    if (!audioTracks_.contains(audioTrack))
    {
        RTC_LOG(LS_INFO) << "|removeAudioTrack| called on unexpected RTCAudioTrack";
        return;
    }

    if (nativeMediaStream_->RemoveTrack(
            ((RTCAudioTrackPrivate *)(audioTrack->d_ptr))->nativeAudioTrack()))
    {
        audioTracks_.erase(std::remove(audioTracks_.begin(), audioTracks_.end(), audioTrack),
                           audioTracks_.end());
    }
}

void RTCMediaStreamPrivate::removeVideoTrack(RTCVideoTrack *videoTrack)
{
    Q_ASSERT(videoTrack);
    if (!signalingThread_->IsCurrent())
    {
        return signalingThread_->BlockingCall(
            [videoTrack, this]() { return this->removeVideoTrack(videoTrack); });
    }

    if (!videoTracks_.contains(videoTrack))
    {
        RTC_LOG(LS_INFO) << "|removeVideoTrack| called on unexpected RTCVideoTrack";
        return;
    }

    if (nativeMediaStream_->RemoveTrack(
            ((RTCVideoTrackPrivate *)(videoTrack->d_ptr))->nativeVideoTrack()))
    {
        videoTracks_.erase(std::remove(videoTracks_.begin(), videoTracks_.end(), videoTrack),
                           videoTracks_.end());
    }
}

RTCMediaStream::RTCMediaStream(QObject *parent) : QObject{parent}
{
}

RTCMediaStream::RTCMediaStream(RTCMediaStreamPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QVector<RTCAudioTrack *> RTCMediaStream::audioTracks() const
{
    Q_D(const RTCMediaStream);
    if (!d->signalingThread_->IsCurrent())
    {
        return d->signalingThread_->BlockingCall([d]() { return d->audioTracks_; });
    }
    return d->audioTracks_;
}

QVector<RTCVideoTrack *> RTCMediaStream::videoTracks() const
{
    Q_D(const RTCMediaStream);
    if (!d->signalingThread_->IsCurrent())
    {
        return d->signalingThread_->BlockingCall([d]() { return d->videoTracks_; });
    }
    return d->videoTracks_;
}

QString RTCMediaStream::streamId() const
{
    Q_D(const RTCMediaStream);
    return QString::fromStdString(d->nativeMediaStream_->id());
}

void RTCMediaStream::addAudioTrack(RTCAudioTrack *audioTrack)
{
    Q_D(RTCMediaStream);
    d->addAudioTrack(audioTrack);
}

void RTCMediaStream::addVideoTrack(RTCVideoTrack *videoTrack)
{
    Q_D(RTCMediaStream);
    d->addVideoTrack(videoTrack);
}

void RTCMediaStream::removeAudioTrack(RTCAudioTrack *audioTrack)
{
    Q_D(RTCMediaStream);
    d->removeAudioTrack(audioTrack);
}

void RTCMediaStream::removeVideoTrack(RTCVideoTrack *videoTrack)
{
    Q_D(RTCMediaStream);
    d->removeVideoTrack(videoTrack);
}
