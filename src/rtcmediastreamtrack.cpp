#include "rtcmediastreamtrack.h"
#include "rtcmediastreamtrack_p.h"

#include <QDebug>

RTCMediaStreamTrackPrivate::RTCMediaStreamTrackPrivate(
    const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack,
    RTCPeerConnectionFactory *factory, RTCMediaStreamTrackType type)
{
    Q_ASSERT(nativeMediaStreamTrack);
    Q_ASSERT(factory);
    type_ = type;
}

RTCMediaStreamTrackPrivate::RTCMediaStreamTrackPrivate(
    const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack,
    RTCPeerConnectionFactory *factory)
{
    Q_ASSERT(nativeMediaStreamTrack);
    Q_ASSERT(factory);
    if (nativeMediaStreamTrack->kind() ==
        std::string(webrtc::MediaStreamTrackInterface::kAudioKind))
    {
        type_ = RTCMediaStreamTrackType::RTCMediaStreamTrackTypeAudio;
    }
    else if (nativeMediaStreamTrack->kind() ==
             std::string(webrtc::MediaStreamTrackInterface::kAudioKind))
    {
        type_ = RTCMediaStreamTrackType::RTCMediaStreamTrackTypeVideo;
    }
    else
    {
        qCritical() << "Unknown track type:" << nativeMediaStreamTrack->kind().c_str();
    }
}

bool RTCMediaStreamTrackPrivate::isEqualToTrack(RTCMediaStreamTrackPrivate *other) const
{
    if (!other)
    {
        return false;
    }
    return nativeMediaStreamTrack_ == other->nativeMediaStreamTrack_;
}

RTCMediaStreamTrack *RTCMediaStreamTrackPrivate::mediaStreamTrackForNativeMediaStreamTrack(
    const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeMediaStreamTrack,
    RTCPeerConnectionFactory *factory)
{
    Q_ASSERT(nativeMediaStreamTrack);
    Q_ASSERT(factory);
    if (nativeMediaStreamTrack->kind() ==
        std::string(webrtc::MediaStreamTrackInterface::kAudioKind))
    {
        auto p = new RTCMediaStreamTrackPrivate(
            nativeMediaStreamTrack, factory, RTCMediaStreamTrackType::RTCMediaStreamTrackTypeAudio);
        return new RTCMediaStreamTrack{*p};
    }
    else if (nativeMediaStreamTrack->kind() ==
             std::string(webrtc::MediaStreamTrackInterface::kVideoKind))
    {
        auto p = new RTCMediaStreamTrackPrivate(
            nativeMediaStreamTrack, factory, RTCMediaStreamTrackType::RTCMediaStreamTrackTypeVideo);
        return new RTCMediaStreamTrack{*p};
    }
    else
    {
        qCritical() << "Unknown track type:" << nativeMediaStreamTrack->kind().c_str();
        return nullptr;
    }
}

RTCMediaStreamTrack::RTCMediaStreamTrack(RTCMediaStreamTrackPrivate &nativeMediaStreamTrack,
                                         QObject *parent)
    : QObject{parent}, d_ptr{&nativeMediaStreamTrack}
{
}

QString RTCMediaStreamTrack::kind() const
{
    Q_D(const RTCMediaStreamTrack);
    return QString::fromStdString(d_ptr->nativeMediaStreamTrack_->kind());
}

QString RTCMediaStreamTrack::trackId() const
{
    Q_D(const RTCMediaStreamTrack);
    return QString::fromStdString(d_ptr->nativeMediaStreamTrack_->id());
}

bool RTCMediaStreamTrack::isEnabled() const
{
    Q_D(const RTCMediaStreamTrack);
    return d_ptr->nativeMediaStreamTrack_->enabled();
}

void RTCMediaStreamTrack::setIsEnabled(bool isEnabled)
{
    Q_D(RTCMediaStreamTrack);
    d_ptr->nativeMediaStreamTrack_->set_enabled(isEnabled);
}

RTCMediaStreamTrackState RTCMediaStreamTrack::readyState() const
{
    Q_D(const RTCMediaStreamTrack);
    return static_cast<RTCMediaStreamTrackState>(d_ptr->nativeMediaStreamTrack_->state());
}
