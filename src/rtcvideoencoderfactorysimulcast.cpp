#include "rtcvideoencoderfactorysimulcast.h"

#include "rtcvideoencodersimulcast.h"

RTCVideoEncoderFactorySimulcast::RTCVideoEncoderFactorySimulcast(IRTCVideoEncoderFactory *primary,
                                                                 IRTCVideoEncoderFactory *fallback,
                                                                 QObject *parent)
    : IRTCVideoEncoderFactory{parent}
{
    primary_ = primary;
    fallback_ = fallback;
}

IRTCVideoEncoder *RTCVideoEncoderFactorySimulcast::createEncoder(RTCVideoCodecInfo *info)
{
    return RTCVideoEncoderSimulcast::simulcastEncoderWithPrimary(primary_, fallback_, info);
}

QVector<RTCVideoCodecInfo *> RTCVideoEncoderFactorySimulcast::supportedCodecs()
{
    QVector<RTCVideoCodecInfo *> codecs = primary_->supportedCodecs();
    QVector<RTCVideoCodecInfo *> fallbackCodecs = fallback_->supportedCodecs();
    for (RTCVideoCodecInfo *codec : fallbackCodecs)
    {
        if (!codecs.contains(codec))
        {
            codecs.append(codec);
        }
    }
    return codecs;
}
