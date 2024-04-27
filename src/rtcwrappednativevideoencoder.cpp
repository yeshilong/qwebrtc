#include "rtcwrappednativevideoencoder.h"

RTCWrappedNativeVideoEncoder::RTCWrappedNativeVideoEncoder(QObject *parent)
    : IRTCVideoEncoder{parent}
{
}

RTCWrappedNativeVideoEncoder::RTCWrappedNativeVideoEncoder(
    std::unique_ptr<webrtc::VideoEncoder> encoder, QObject *parent)
    : IRTCVideoEncoder{parent}
{
    wrappedEncoder_ = std::move(encoder);
}

std::unique_ptr<webrtc::VideoEncoder> RTCWrappedNativeVideoEncoder::releaseWrappedEncoder()
{
    return std::move(wrappedEncoder_);
}

void RTCWrappedNativeVideoEncoder::setCallback(RTCVideoEncoderCallback callback)
{
    RTC_DCHECK_NOTREACHED();
}

int RTCWrappedNativeVideoEncoder::startEncodeWithSettings(RTCVideoEncoderSettings *settings,
                                                          int numberOfCores)
{
    RTC_DCHECK_NOTREACHED();
    return 0;
}

int RTCWrappedNativeVideoEncoder::releaseEncoder()
{
    RTC_DCHECK_NOTREACHED();
    return 0;
}

int RTCWrappedNativeVideoEncoder::encode(RTCVideoFrame *frame, IRTCCodecSpecificInfo *info,
                                         QVector<int> frameTypes)
{
    RTC_DCHECK_NOTREACHED();
    return 0;
}

int RTCWrappedNativeVideoEncoder::setBitrate(unsigned int bitrateKbit, unsigned int framerate)
{
    RTC_DCHECK_NOTREACHED();
    return 0;
}

QString RTCWrappedNativeVideoEncoder::implementationName()
{
    RTC_DCHECK_NOTREACHED();
    return QString{};
}

RTCVideoEncoderQpThresholds *RTCWrappedNativeVideoEncoder::scalingSettings()
{
    RTC_DCHECK_NOTREACHED();
    return nullptr;
}

int RTCWrappedNativeVideoEncoder::resolutionAlignment() const
{
    RTC_DCHECK_NOTREACHED();
    return 1;
}
bool RTCWrappedNativeVideoEncoder::applyAlignmentToAllSimulcastLayers() const
{
    RTC_DCHECK_NOTREACHED();
    return false;
}
bool RTCWrappedNativeVideoEncoder::supportsNativeHandle() const
{
    RTC_DCHECK_NOTREACHED();
    return false;
}
