#include "rtcwrappednativevideodecoder.h"

RTCWrappedNativeVideoDecoder::RTCWrappedNativeVideoDecoder(QObject *parent)
    : IRTCVideoDecoder{parent}
{
}

RTCWrappedNativeVideoDecoder::RTCWrappedNativeVideoDecoder(
    std::unique_ptr<webrtc::VideoDecoder> decoder, QObject *parent)
    : IRTCVideoDecoder{parent}, wrappedDecoder_{std::move(decoder)}
{
}

std::unique_ptr<webrtc::VideoDecoder> RTCWrappedNativeVideoDecoder::releaseWrappedDecoder()
{
    return std::move(wrappedDecoder_);
}

void RTCWrappedNativeVideoDecoder::setCallback(RTCVideoDecoderCallback callback)
{
    RTC_DCHECK_NOTREACHED();
}

int RTCWrappedNativeVideoDecoder::startDecodeWithNumberOfCores(int numberOfCores)
{
    RTC_DCHECK_NOTREACHED();
    return 0;
}

int RTCWrappedNativeVideoDecoder::releaseDecoder()
{
    RTC_DCHECK_NOTREACHED();
    return 0;
}

int RTCWrappedNativeVideoDecoder::decode(std::shared_ptr<RTCEncodedImage> encodedImage,
                                         bool missingFrames,
                                         std::shared_ptr<IRTCCodecSpecificInfo> info,
                                         qint64 renderTimeMs)
{
    RTC_DCHECK_NOTREACHED();
    return 0;
}

QString RTCWrappedNativeVideoDecoder::implementationName() const
{
    RTC_DCHECK_NOTREACHED();
    return QString{};
}
