#include "rtcrtpsender.h"
#include "rtcrtpsender_p.h"

#include "rtcdtmfsender_p.h"
#include "rtcrtpparameters_p.h"
#include "rtcmediastreamtrack_p.h"

#include "api/media_stream_interface.h"

RTCRtpSenderPrivate::RTCRtpSenderPrivate(
    RTCPeerConnectionFactory *factory,
    const rtc::scoped_refptr<webrtc::RtpSenderInterface> nativeRtpSender)
{
    Q_ASSERT(factory);
    Q_ASSERT(nativeRtpSender);
    factory_ = factory;
    nativeRtpSender_ = nativeRtpSender;

    if (nativeRtpSender->media_type() == cricket::MEDIA_TYPE_AUDIO)
    {
        rtc::scoped_refptr<webrtc::DtmfSenderInterface> nativeDtmfSender(
            nativeRtpSender->GetDtmfSender());
        if (nativeDtmfSender)
        {
            dtmfSender_ = new RTCDtmfSender(*new RTCDtmfSenderPrivate(nativeDtmfSender));
        }
    }
}

rtc::scoped_refptr<webrtc::RtpSenderInterface> RTCRtpSenderPrivate::nativeRtpSender() const
{
    return nativeRtpSender_;
}

rtc::scoped_refptr<webrtc::FrameEncryptorInterface> RTCRtpSenderPrivate::frameEncryptor() const
{
    return nativeRtpSender_->GetFrameEncryptor();
}

void RTCRtpSenderPrivate::setFrameEncryptor(
    const rtc::scoped_refptr<webrtc::FrameEncryptorInterface> frameEncryptor)
{
    nativeRtpSender_->SetFrameEncryptor(frameEncryptor);
}

RTCRtpSender::RTCRtpSender(QObject *parent) : QObject{parent}
{
}

RTCRtpSender::RTCRtpSender(RTCRtpSenderPrivate &d, QObject *parent) : QObject{parent}, d_ptr{&d}
{
}

QString RTCRtpSender::senderId() const
{
    Q_D(const RTCRtpSender);
    return QString::fromStdString(d->nativeRtpSender_->id());
}

RTCRtpParameters *RTCRtpSender::parameters() const
{
    Q_D(const RTCRtpSender);
    return new RTCRtpParameters(*new RTCRtpParametersPrivate(d->nativeRtpSender_->GetParameters()));
}

void RTCRtpSender::setParameters(const RTCRtpParameters &parameters)
{
    Q_D(RTCRtpSender);
    if (!d->nativeRtpSender_->SetParameters(parameters.d_ptr->nativeRtpParameters()).ok())
    {
        qCritical() << "Failed to set parameters for rtp sender" << &parameters;
    }
}

RTCMediaStreamTrack *RTCRtpSender::track() const
{
    Q_D(const RTCRtpSender);
    rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeTrack(d->nativeRtpSender_->track());
    if (nativeTrack)
    {
        return RTCMediaStreamTrackPrivate::mediaStreamTrackForNativeMediaStreamTrack(nativeTrack,
                                                                                     d->factory_);
    }
    return nullptr;
}

void RTCRtpSender::setTrack(const RTCMediaStreamTrack &track)
{
    Q_D(RTCRtpSender);
    if (d->nativeRtpSender_->SetTrack(track.d_ptr->nativeMediaStreamTrack().get()))
    {
        qCritical() << "Failed to set track for rtp sender" << &track;
    }
}

QVector<QString> RTCRtpSender::streamIds() const
{
    Q_D(const RTCRtpSender);
    QVector<QString> streamIds;
    for (const auto &streamId : d->nativeRtpSender_->stream_ids())
    {
        streamIds.append(QString::fromStdString(streamId));
    }
    return streamIds;
}

void RTCRtpSender::setStreamIds(const QVector<QString> &streamIds)
{
    Q_D(RTCRtpSender);
    std::vector<std::string> nativeStreamIds;
    for (const auto &streamId : streamIds)
    {
        nativeStreamIds.push_back(streamId.toStdString());
    }
    d->nativeRtpSender_->SetStreams(nativeStreamIds);
}

IRTCDtmfSender *RTCRtpSender::dtmfSender() const
{
    Q_D(const RTCRtpSender);
    return d->dtmfSender_;
}
