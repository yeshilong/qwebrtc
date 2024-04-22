#include "rtcvideoencoderfactorysimulcast.h"

RTCVideoEncoderFactorySimulcast::RTCVideoEncoderFactorySimulcast(IRTCVideoEncoderFactory *primary,
                                                                 IRTCVideoEncoderFactory *fallback,
                                                                 QObject *parent)
    : IRTCVideoEncoderFactory{parent}
{
}
