#include "rtcmediaconstraints.h"
#include "rtcmediaconstraints_p.h"

RTCMediaConstraintsPrivate::RTCMediaConstraintsPrivate(QMap<QString, QString> mandatory,
                                                       QMap<QString, QString> optional)
    : mandatory_{mandatory}, optional_{optional}
{
}

std::unique_ptr<webrtc::MediaConstraints> RTCMediaConstraintsPrivate::nativeMediaConstraints()
{
    webrtc::MediaConstraints::Constraints nativeMandatory =
        nativeConstraintsForConstraints(mandatory_);
    webrtc::MediaConstraints::Constraints nativeOptional =
        nativeConstraintsForConstraints(optional_);

    return std::make_unique<webrtc::MediaConstraints>(nativeMandatory, nativeOptional);
}

webrtc::MediaConstraints::Constraints RTCMediaConstraintsPrivate::nativeConstraintsForConstraints(
    QMap<QString, QString> constraints)
{
    webrtc::MediaConstraints::Constraints nativeConstraints;
    for (auto it = constraints.begin(); it != constraints.end(); ++it)
    {
        nativeConstraints.push_back({it.key().toStdString(), it.value().toStdString()});
    }
    return nativeConstraints;
}

RTCMediaConstraints::RTCMediaConstraints(QMap<QString, QString> mandatory,
                                         QMap<QString, QString> optional, QObject *parent)
    : QObject{parent}, d_ptr{new RTCMediaConstraintsPrivate{mandatory, optional}}
{
}

QString RTCMediaConstraints::RTCMediaConstraintsAudioNetworkAdaptorConfig()
{
    return webrtc::MediaConstraints::kAudioNetworkAdaptorConfig;
}

QString RTCMediaConstraints::RTCMediaConstraintsIceRestart()
{
    return webrtc::MediaConstraints::kIceRestart;
}

QString RTCMediaConstraints::RTCMediaConstraintsOfferToReceiveAudio()
{
    return webrtc::MediaConstraints::kOfferToReceiveAudio;
}

QString RTCMediaConstraints::RTCMediaConstraintsOfferToReceiveVideo()
{
    return webrtc::MediaConstraints::kOfferToReceiveVideo;
}

QString RTCMediaConstraints::RTCMediaConstraintsVoiceActivityDetection()
{
    return webrtc::MediaConstraints::kVoiceActivityDetection;
}

QString RTCMediaConstraints::RTCMediaConstraintsValueTrue()
{
    return webrtc::MediaConstraints::kValueTrue;
}

QString RTCMediaConstraints::RTCMediaConstraintsValueFalse()
{
    return webrtc::MediaConstraints::kValueFalse;
}
