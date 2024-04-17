#include "rtcmediaconstraints.h"

RTCMediaConstraints::RTCMediaConstraints(QMap<QString, QString> mandatory,
                                         QMap<QString, QString> optional, QObject *parent)
    : QObject{parent}
{
}

QString RTCMediaConstraints::RTCMediaConstraintsAudioNetworkAdaptorConfig()
{
    return QString{};
}

QString RTCMediaConstraints::RTCMediaConstraintsIceRestart()
{
    return QString{};
}

QString RTCMediaConstraints::RTCMediaConstraintsOfferToReceiveAudio()
{
    return QString{};
}

QString RTCMediaConstraints::RTCMediaConstraintsOfferToReceiveVideo()
{
    return QString{};
}

QString RTCMediaConstraints::RTCMediaConstraintsVoiceActivityDetection()
{
    return QString{};
}

QString RTCMediaConstraints::RTCMediaConstraintsValueTrue()
{
    return QString{};
}

QString RTCMediaConstraints::RTCMediaConstraintsValueFalse()
{
    return QString{};
}
