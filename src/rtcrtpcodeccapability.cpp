#include "rtcrtpcodeccapability.h"
#include "rtcrtpcodeccapability_p.h"

#include "rtc_base/checks.h"
#include "media/base/media_constants.h"

void RTCRtpCodecCapabilityPrivate::init(const webrtc::RtpCodecCapability &nativeRtpCodecCapability)
{
    nativeRtpCodecCapability_ = nativeRtpCodecCapability;
}

RTCRtpCodecCapabilityPrivate::RTCRtpCodecCapabilityPrivate()
{
    init(webrtc::RtpCodecCapability());
}

RTCRtpCodecCapabilityPrivate::RTCRtpCodecCapabilityPrivate(
    const webrtc::RtpCodecCapability &nativeRtpCodecCapability)
{
    init(nativeRtpCodecCapability);
}

RTCRtpCodecCapability::RTCRtpCodecCapability(QObject *parent)
    : QObject{parent}, d_ptr{new RTCRtpCodecCapabilityPrivate{}}
{
}

RTCRtpCodecCapability::RTCRtpCodecCapability(RTCRtpCodecCapabilityPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QString RTCRtpCodecCapability::mimeType() const
{
    Q_D(const RTCRtpCodecCapability);
    return d->nativeRtpCodecCapability_.mime_type().c_str();
}

QString RTCRtpCodecCapability::name() const
{
    Q_D(const RTCRtpCodecCapability);
    return d->nativeRtpCodecCapability_.name.c_str();
}

void RTCRtpCodecCapability::setName(const QString &name)
{
    Q_D(RTCRtpCodecCapability);
    d->nativeRtpCodecCapability_.name = name.toStdString();
}

RTCRtpMediaType RTCRtpCodecCapability::kind() const
{
    Q_D(const RTCRtpCodecCapability);
    return static_cast<RTCRtpMediaType>(d->nativeRtpCodecCapability_.kind);
}

void RTCRtpCodecCapability::setKind(const RTCRtpMediaType &kind)
{
    Q_D(RTCRtpCodecCapability);
    d->nativeRtpCodecCapability_.kind = static_cast<cricket::MediaType>(kind);
}

QVariant RTCRtpCodecCapability::clockRate() const
{
    Q_D(const RTCRtpCodecCapability);
    if (!d->nativeRtpCodecCapability_.clock_rate)
    {
        return QVariant{};
    }
    return QVariant::fromValue(d->nativeRtpCodecCapability_.clock_rate);
}

void RTCRtpCodecCapability::setClockRate(const QVariant &clockRate)
{
    Q_D(RTCRtpCodecCapability);
    if (clockRate.isNull())
    {
        d->nativeRtpCodecCapability_.clock_rate = absl::optional<int>();
        return;
    }
    d->nativeRtpCodecCapability_.clock_rate = absl::optional<int>{clockRate.toInt()};
}

QVariant RTCRtpCodecCapability::preferredPayloadType() const
{
    Q_D(const RTCRtpCodecCapability);
    if (!d->nativeRtpCodecCapability_.preferred_payload_type)
    {
        return QVariant{};
    }
    return QVariant::fromValue(d->nativeRtpCodecCapability_.preferred_payload_type);
}

void RTCRtpCodecCapability::setPreferredPayloadType(const QVariant &preferredPayloadType)
{
    Q_D(RTCRtpCodecCapability);
    if (preferredPayloadType.isNull())
    {
        d->nativeRtpCodecCapability_.preferred_payload_type = absl::optional<int>();
        return;
    }
    d->nativeRtpCodecCapability_.preferred_payload_type =
        absl::optional<int>{preferredPayloadType.toInt()};
}

QVariant RTCRtpCodecCapability::numChannels() const
{
    Q_D(const RTCRtpCodecCapability);
    if (!d->nativeRtpCodecCapability_.num_channels)
    {
        return QVariant{};
    }
    return QVariant::fromValue(d->nativeRtpCodecCapability_.num_channels);
}

void RTCRtpCodecCapability::setNumChannels(const QVariant &numChannels)
{
    Q_D(RTCRtpCodecCapability);
    if (numChannels.isNull())
    {
        d->nativeRtpCodecCapability_.num_channels = absl::optional<int>();
        return;
    }
    d->nativeRtpCodecCapability_.num_channels = absl::optional<int>{numChannels.toInt()};
}

QMap<QString, QString> RTCRtpCodecCapability::parameters() const
{
    Q_D(const RTCRtpCodecCapability);
    QMap<QString, QString> parameters;
    for (const auto &parameter : d->nativeRtpCodecCapability_.parameters)
    {
        parameters.insert(QString::fromStdString(parameter.first),
                          QString::fromStdString(parameter.second));
    }
    return parameters;
}

void RTCRtpCodecCapability::setParameters(const QMap<QString, QString> &parameters)
{
    Q_D(RTCRtpCodecCapability);
    d->nativeRtpCodecCapability_.parameters.clear();
    for (auto it = parameters.begin(); it != parameters.end(); ++it)
    {
        d->nativeRtpCodecCapability_.parameters.insert(
            std::make_pair(it.key().toStdString(), it.value().toStdString()));
    }
}
