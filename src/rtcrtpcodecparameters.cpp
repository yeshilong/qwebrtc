#include "rtcrtpcodecparameters.h"
#include "rtcrtpcodecparameters_p.h"
#include "rtcmediastreamtrack.h"

#include "rtc_base/checks.h"
#include "media/base/media_constants.h"

void RTCRtpCodecParametersPrivate::init(const webrtc::RtpCodecParameters &nativeRtpCodecParameters)
{
    payloadType_ = nativeRtpCodecParameters.payload_type;
    name_ = QString::fromStdString(nativeRtpCodecParameters.name);
    switch (nativeRtpCodecParameters.kind)
    {
    case cricket::MEDIA_TYPE_AUDIO:
        kind_ = RTCMediaStreamTrack::RTCMediaStreamTrackKindAudio();
    case cricket::MEDIA_TYPE_VIDEO:
        kind_ = RTCMediaStreamTrack::RTCMediaStreamTrackKindVideo();
        break;
    case cricket::MEDIA_TYPE_DATA:
        RTC_DCHECK_NOTREACHED();
        break;
    case cricket::MEDIA_TYPE_UNSUPPORTED:
        RTC_DCHECK_NOTREACHED();
        break;
    }
    clockRate_ = QVariant::fromValue(nativeRtpCodecParameters.clock_rate);
    numChannels_ = QVariant::fromValue(nativeRtpCodecParameters.num_channels);

    for (const auto &parameter : nativeRtpCodecParameters.parameters)
    {
        parameters_.insert(QString::fromStdString(parameter.first),
                           QString::fromStdString(parameter.second));
    }
}

RTCRtpCodecParametersPrivate::RTCRtpCodecParametersPrivate()
{
    webrtc::RtpCodecParameters nativeParameters;
    init(nativeParameters);
}

RTCRtpCodecParametersPrivate::RTCRtpCodecParametersPrivate(
    const webrtc::RtpCodecParameters &nativeRtpCodecParameters)
{
    init(nativeRtpCodecParameters);
}

webrtc::RtpCodecParameters RTCRtpCodecParametersPrivate::nativeRtpCodecParameters() const
{
    webrtc::RtpCodecParameters nativeParameters;
    nativeParameters.payload_type = payloadType_;
    nativeParameters.name = name_.toStdString();
    if (kind_ == RTCMediaStreamTrack::RTCMediaStreamTrackKindAudio())
    {
        nativeParameters.kind = cricket::MEDIA_TYPE_AUDIO;
    }
    else if (kind_ == RTCMediaStreamTrack::RTCMediaStreamTrackKindVideo())
    {
        nativeParameters.kind = cricket::MEDIA_TYPE_VIDEO;
    }
    else
    {
        RTC_DCHECK_NOTREACHED();
    }

    if (!clockRate_.isNull())
        nativeParameters.clock_rate = absl::optional<int>(clockRate_.toInt());
    if (!numChannels_.isNull())
        nativeParameters.num_channels = absl::optional<int>(numChannels_.toInt());

    for (auto it = parameters_.keyValueBegin(); it != parameters_.keyValueEnd(); ++it)
    {
        std::string key = it->first.toStdString();
        std::string value = it->second.toStdString();
        nativeParameters.parameters[key] = value;
    }

    return nativeParameters;
}

RTCRtpCodecParameters::RTCRtpCodecParameters(QObject *parent)
    : QObject{parent}, d_ptr{new RTCRtpCodecParametersPrivate{}}
{
}

int RTCRtpCodecParameters::payloadType() const
{
    Q_D(const RTCRtpCodecParameters);
    return d->payloadType_;
}

void RTCRtpCodecParameters::setPayloadType(int payloadType)
{
    Q_D(RTCRtpCodecParameters);
    d->payloadType_ = payloadType;
}

QString RTCRtpCodecParameters::name() const
{
    Q_D(const RTCRtpCodecParameters);
    return d->name_;
}

QString RTCRtpCodecParameters::kind() const
{
    Q_D(const RTCRtpCodecParameters);
    return d->kind_;
}

QVariant RTCRtpCodecParameters::clockRate() const
{
    Q_D(const RTCRtpCodecParameters);
    return d->clockRate_;
}

QVariant RTCRtpCodecParameters::numChannels() const
{
    Q_D(const RTCRtpCodecParameters);
    return d->numChannels_;
}

QMap<QString, QString> RTCRtpCodecParameters::parameters() const
{
    Q_D(const RTCRtpCodecParameters);
    return d->parameters_;
}

QString RTCRtpCodecParameters::RTCRtxCodecName()
{
    return QString::fromStdString(cricket::kRtxCodecName);
}

QString RTCRtpCodecParameters::RTCRedCodecName()
{
    return QString::fromStdString(cricket::kRedCodecName);
}

QString RTCRtpCodecParameters::RTCUlpfecCodecName()
{
    return QString::fromStdString(cricket::kUlpfecCodecName);
}

QString RTCRtpCodecParameters::RTCFlexfecCodecName()
{
    return QString::fromStdString(cricket::kFlexfecCodecName);
}

QString RTCRtpCodecParameters::RTCOpusCodecName()
{
    return QString::fromStdString(cricket::kOpusCodecName);
}

QString RTCRtpCodecParameters::RTCL16CodecName()
{
    return QString::fromStdString(cricket::kL16CodecName);
}

QString RTCRtpCodecParameters::RTCG722CodecName()
{
    return QString::fromStdString(cricket::kG722CodecName);
}

QString RTCRtpCodecParameters::RTCIlbcCodecName()
{
    return QString::fromStdString(cricket::kIlbcCodecName);
}

QString RTCRtpCodecParameters::RTCPcmuCodecName()
{
    return QString::fromStdString(cricket::kPcmuCodecName);
}

QString RTCRtpCodecParameters::RTCPcmaCodecName()
{
    return QString::fromStdString(cricket::kPcmaCodecName);
}

QString RTCRtpCodecParameters::RTCDtmfCodecName()
{
    return QString::fromStdString(cricket::kDtmfCodecName);
}

QString RTCRtpCodecParameters::RTCComfortNoiseCodecName()
{
    return QString::fromStdString(cricket::kComfortNoiseCodecName);
}

QString RTCRtpCodecParameters::RTCVp8CodecName()
{
    return QString::fromStdString(cricket::kVp8CodecName);
}

QString RTCRtpCodecParameters::RTCVp9CodecName()
{
    return QString::fromStdString(cricket::kVp9CodecName);
}

QString RTCRtpCodecParameters::RTCH264CodecName()
{
    return QString::fromStdString(cricket::kH264CodecName);
}

QString RTCRtpCodecParameters::RTCAv1CodecName()
{
    return QString::fromStdString(cricket::kAv1CodecName);
}
