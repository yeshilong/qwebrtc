#include "rtcrtpencodingparameters.h"
#include "rtcrtpencodingparameters_p.h"

void RTCRtpEncodingParametersPrivate::init(
    const webrtc::RtpEncodingParameters &nativeRtpEncodingParameters)
{
    if (!nativeRtpEncodingParameters.rid.empty())
    {
        rid_ = QString::fromStdString(nativeRtpEncodingParameters.rid);
    }
    isActive_ = nativeRtpEncodingParameters.active;
    if (nativeRtpEncodingParameters.max_bitrate_bps)
    {
        maxBitrateBps_ = QVariant::fromValue(*nativeRtpEncodingParameters.max_bitrate_bps);
    }
    if (nativeRtpEncodingParameters.min_bitrate_bps)
    {
        minBitrateBps_ = QVariant::fromValue(*nativeRtpEncodingParameters.min_bitrate_bps);
    }
    if (nativeRtpEncodingParameters.max_framerate)
    {
        maxFramerate_ = QVariant::fromValue(nativeRtpEncodingParameters.max_framerate);
    }
    if (nativeRtpEncodingParameters.num_temporal_layers)
    {
        numTemporalLayers_ = QVariant::fromValue(*nativeRtpEncodingParameters.num_temporal_layers);
    }
    if (nativeRtpEncodingParameters.scale_resolution_down_by)
    {
        scaleResolutionDownBy_ =
            QVariant::fromValue(*nativeRtpEncodingParameters.scale_resolution_down_by);
    }
    if (nativeRtpEncodingParameters.ssrc)
    {
        ssrc_ = QVariant::fromValue(*nativeRtpEncodingParameters.ssrc);
    }
    bitratePriority_ = nativeRtpEncodingParameters.bitrate_priority;
    networkPriority_ = static_cast<RTCPriority>(nativeRtpEncodingParameters.network_priority);
    adaptiveAudioPacketTime_ = nativeRtpEncodingParameters.adaptive_ptime;
    if (nativeRtpEncodingParameters.scalability_mode)
    {
        scalabilityMode_ =
            QString::fromStdString(nativeRtpEncodingParameters.scalability_mode->c_str());
    }
}

RTCRtpEncodingParametersPrivate::RTCRtpEncodingParametersPrivate()
{
    webrtc::RtpEncodingParameters nativeRtpEncodingParameters;
    init(nativeRtpEncodingParameters);
}

RTCRtpEncodingParametersPrivate::RTCRtpEncodingParametersPrivate(
    const webrtc::RtpEncodingParameters &nativeRtpEncodingParameters)
{
    init(nativeRtpEncodingParameters);
}

webrtc::RtpEncodingParameters RTCRtpEncodingParametersPrivate::nativeRtpEncodingParameters() const
{
    webrtc::RtpEncodingParameters nativeRtpEncodingParameters;
    nativeRtpEncodingParameters.rid = rid_.toStdString();
    nativeRtpEncodingParameters.active = isActive_;
    if (maxBitrateBps_.isValid())
    {
        nativeRtpEncodingParameters.max_bitrate_bps =
            absl::optional<int>(maxBitrateBps_.value<int>());
    }
    if (minBitrateBps_.isValid())
    {
        nativeRtpEncodingParameters.min_bitrate_bps =
            absl::optional<int>(minBitrateBps_.value<int>());
    }
    if (maxFramerate_.isValid())
    {
        nativeRtpEncodingParameters.max_framerate = absl::optional<int>(maxFramerate_.value<int>());
    }
    if (numTemporalLayers_.isValid())
    {
        nativeRtpEncodingParameters.num_temporal_layers =
            absl::optional<int>(numTemporalLayers_.value<int>());
    }
    if (scaleResolutionDownBy_.isValid())
    {
        nativeRtpEncodingParameters.scale_resolution_down_by =
            absl::optional<double>(scaleResolutionDownBy_.value<double>());
    }
    if (ssrc_.isValid())
    {
        nativeRtpEncodingParameters.ssrc = absl::optional<uint32_t>(ssrc_.value<uint32_t>());
    }
    nativeRtpEncodingParameters.bitrate_priority = bitratePriority_;
    nativeRtpEncodingParameters.network_priority = static_cast<webrtc::Priority>(networkPriority_);
    nativeRtpEncodingParameters.adaptive_ptime = adaptiveAudioPacketTime_;
    if (!scalabilityMode_.isEmpty())
    {
        nativeRtpEncodingParameters.scalability_mode =
            absl::optional<std::string>(scalabilityMode_.toStdString());
    }
    return nativeRtpEncodingParameters;
}

RTCRtpEncodingParameters::RTCRtpEncodingParameters(QObject *parent)
    : QObject{parent}, d_ptr{new RTCRtpEncodingParametersPrivate{}}
{
}

QString RTCRtpEncodingParameters::rid() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->rid_;
}

void RTCRtpEncodingParameters::setRid(const QString &rid)
{
    Q_D(RTCRtpEncodingParameters);
    d->rid_ = rid;
}

bool RTCRtpEncodingParameters::isActive() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->isActive_;
}

void RTCRtpEncodingParameters::setIsActive(bool isActive)
{
    Q_D(RTCRtpEncodingParameters);
    d->isActive_ = isActive;
}

QVariant RTCRtpEncodingParameters::maxBitrateBps() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->maxBitrateBps_;
}

void RTCRtpEncodingParameters::setMaxBitrateBps(const QVariant &maxBitrateBps)
{
    Q_D(RTCRtpEncodingParameters);
    d->maxBitrateBps_ = maxBitrateBps;
}

QVariant RTCRtpEncodingParameters::minBitrateBps() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->minBitrateBps_;
}

void RTCRtpEncodingParameters::setMinBitrateBps(const QVariant &minBitrateBps)
{
    Q_D(RTCRtpEncodingParameters);
    d->minBitrateBps_ = minBitrateBps;
}

QVariant RTCRtpEncodingParameters::maxFramerate() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->maxFramerate_;
}

void RTCRtpEncodingParameters::setMaxFramerate(const QVariant &maxFramerate)
{
    Q_D(RTCRtpEncodingParameters);
    d->maxFramerate_ = maxFramerate;
}

QVariant RTCRtpEncodingParameters::numTemporalLayers() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->numTemporalLayers_;
}

void RTCRtpEncodingParameters::setNumTemporalLayers(const QVariant &numTemporalLayers)
{
    Q_D(RTCRtpEncodingParameters);
    d->numTemporalLayers_ = numTemporalLayers;
}

QVariant RTCRtpEncodingParameters::scaleResolutionDownBy() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->scaleResolutionDownBy_;
}

void RTCRtpEncodingParameters::setScaleResolutionDownBy(const QVariant &scaleResolutionDownBy)
{
    Q_D(RTCRtpEncodingParameters);
    d->scaleResolutionDownBy_ = scaleResolutionDownBy;
}

QVariant RTCRtpEncodingParameters::ssrc() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->ssrc_;
}

double RTCRtpEncodingParameters::bitratePriority() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->bitratePriority_;
}

void RTCRtpEncodingParameters::setBitratePriority(double bitratePriority)
{
    Q_D(RTCRtpEncodingParameters);
    d->bitratePriority_ = bitratePriority;
}

RTCPriority RTCRtpEncodingParameters::networkPriority() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->networkPriority_;
}

void RTCRtpEncodingParameters::setNetworkPriority(RTCPriority networkPriority)
{
    Q_D(RTCRtpEncodingParameters);
    d->networkPriority_ = networkPriority;
}

bool RTCRtpEncodingParameters::adaptiveAudioPacketTime() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->adaptiveAudioPacketTime_;
}

void RTCRtpEncodingParameters::setAdaptiveAudioPacketTime(bool adaptiveAudioPacketTime)
{
    Q_D(RTCRtpEncodingParameters);
    d->adaptiveAudioPacketTime_ = adaptiveAudioPacketTime;
}

QString RTCRtpEncodingParameters::scalabilityMode() const
{
    Q_D(const RTCRtpEncodingParameters);
    return d->scalabilityMode_;
}

void RTCRtpEncodingParameters::setScalabilityMode(const QString &scalabilityMode)
{
    Q_D(RTCRtpEncodingParameters);
    d->scalabilityMode_ = scalabilityMode;
}
