#include "rtcvideoencoderqpthresholds.h"

RTCVideoEncoderQpThresholds::RTCVideoEncoderQpThresholds(int low, int high, QObject *parent)
    : QObject{parent}, low_{low}, high_{high}
{
}

int RTCVideoEncoderQpThresholds::low() const
{
    return low_;
}

int RTCVideoEncoderQpThresholds::high() const
{
    return high_;
}
