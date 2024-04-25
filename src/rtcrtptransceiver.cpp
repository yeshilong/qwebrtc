#include "rtcrtptransceiver_p.h"

#include "rtcrtpsender_p.h"
#include "rtcrtpreceiver_p.h"
#include "rtcrtpcodeccapability_p.h"
#include "rtcerror_p.h"

RTCRtpTransceiverPrivate::RTCRtpTransceiverPrivate(
    RTCPeerConnectionFactory *factory,
    rtc::scoped_refptr<webrtc::RtpTransceiverInterface> nativeRtpTransceiver)
{
    Q_ASSERT(factory);
    Q_ASSERT(nativeRtpTransceiver);

    factory_ = factory;
    nativeRtpTransceiver_ = nativeRtpTransceiver;

    if (nativeRtpTransceiver_->sender())
    {
        sender_ =
            new RTCRtpSender(*new RTCRtpSenderPrivate(factory_, nativeRtpTransceiver_->sender()));
    }

    if (nativeRtpTransceiver_->receiver())
    {
        receiver_ = new RTCRtpReceiver(
            *new RTCRtpReceiverPrivate(factory_, nativeRtpTransceiver_->receiver()));
    }
}

rtc::scoped_refptr<webrtc::RtpTransceiverInterface> RTCRtpTransceiverPrivate::nativeRtpTransceiver()
    const
{
    return nativeRtpTransceiver_;
}

RTCRtpTransceiver::RTCRtpTransceiver(QObject *parent) : QObject{parent}
{
}

RTCRtpMediaType RTCRtpTransceiver::mediaType() const
{
    Q_D(const RTCRtpTransceiver);
    return static_cast<RTCRtpMediaType>(d->nativeRtpTransceiver_->media_type());
}

QString RTCRtpTransceiver::mid() const
{
    Q_D(const RTCRtpTransceiver);
    return QString::fromStdString(*d->nativeRtpTransceiver_->mid());
}

IRTCRtpSender *RTCRtpTransceiver::sender() const
{
    Q_D(const RTCRtpTransceiver);
    return d->sender_;
}

RTCRtpReceiver *RTCRtpTransceiver::receiver() const
{
    Q_D(const RTCRtpTransceiver);
    return d->receiver_;
}

bool RTCRtpTransceiver::isStopped() const
{
    Q_D(const RTCRtpTransceiver);
    return d->nativeRtpTransceiver_->stopped();
}

RTCRtpTransceiverDirection RTCRtpTransceiver::direction() const
{
    Q_D(const RTCRtpTransceiver);
    return static_cast<RTCRtpTransceiverDirection>(d->nativeRtpTransceiver_->direction());
}

QVector<RTCRtpCodecCapability *> RTCRtpTransceiver::codecPreferences() const
{
    Q_D(const RTCRtpTransceiver);
    QVector<RTCRtpCodecCapability *> codecPreferences;
    for (const webrtc::RtpCodecCapability &nativeCodecCapability :
         d->nativeRtpTransceiver_->codec_preferences())
    {
        codecPreferences.append(
            new RTCRtpCodecCapability(*new RTCRtpCodecCapabilityPrivate(nativeCodecCapability)));
    }
    return codecPreferences;
}

void RTCRtpTransceiver::setCodecPreferences(const QVector<RTCRtpCodecCapability *> &preferences)
{
    Q_D(RTCRtpTransceiver);
    std::vector<webrtc::RtpCodecCapability> nativeCodecCapabilities;
    for (RTCRtpCodecCapability *codecCapability : preferences)
    {
        nativeCodecCapabilities.push_back(codecCapability->d_ptr->nativeRtpCodecCapability());
    }
    d->nativeRtpTransceiver_->SetCodecPreferences(rtc::ArrayView<webrtc::RtpCodecCapability>(
        nativeCodecCapabilities.data(), nativeCodecCapabilities.size()));
}

bool RTCRtpTransceiver::currentDirection(RTCRtpTransceiverDirection *currentDirectionOut) const
{
    Q_D(const RTCRtpTransceiver);
    if (d->nativeRtpTransceiver_->current_direction())
    {
        *currentDirectionOut =
            static_cast<RTCRtpTransceiverDirection>(*d->nativeRtpTransceiver_->current_direction());
        return true;
    }
    return false;
}

void RTCRtpTransceiver::stopInternal()
{
    Q_D(RTCRtpTransceiver);
    d->nativeRtpTransceiver_->StopInternal();
}

void RTCRtpTransceiver::setDirection(RTCRtpTransceiverDirection direction, RTCError **error)
{
    Q_D(RTCRtpTransceiver);
    webrtc::RTCError nativeError = d->nativeRtpTransceiver_->SetDirectionWithError(
        static_cast<webrtc::RtpTransceiverDirection>(direction));

    if (!nativeError.ok())
    {
        *error = new RTCError(*new RTCErrorPrivate(nativeError));
    }
}
