#include "rtcvideocodecinfo_p.h"

RTCVideoCodecInfoPrivate::RTCVideoCodecInfoPrivate(const webrtc::SdpVideoFormat &format)
{
    QMap<QString, QString> params;
    for (auto it = format.parameters.begin(); it != format.parameters.end(); ++it)
    {
        params[QString::fromStdString(it->first)] = QString::fromStdString(it->second);
    }
    name_ = QString::fromStdString(format.name);
    parameters_ = params;
}

webrtc::SdpVideoFormat RTCVideoCodecInfoPrivate::nativeSdpVideoFormat() const
{
    std::map<std::string, std::string> parameters;
    for (auto it = parameters_.constBegin(); it != parameters_.constEnd(); ++it)
    {
        std::string key = it.key().toStdString();
        std::string value = it.value().toStdString();
        parameters[key] = value;
    }

    absl::InlinedVector<webrtc::ScalabilityMode, webrtc::kScalabilityModeCount> scalability_modes;
    for (const QString &scalabilityMode : scalabilityModes_)
    {
        auto scalability_mode = webrtc::ScalabilityModeFromString(scalabilityMode.toStdString());
        if (scalability_mode != absl::nullopt)
        {
            scalability_modes.push_back(*scalability_mode);
        }
    }

    return webrtc::SdpVideoFormat(name_.toStdString(), parameters, scalability_modes);
}

RTCVideoCodecInfo::RTCVideoCodecInfo(QString name, QObject *parent) : QObject{parent}
{
    Q_D(RTCVideoCodecInfo);
    d->name_ = name;
}

RTCVideoCodecInfo::RTCVideoCodecInfo(QString name, QMap<QString, QString> parameters,
                                     QObject *parent)
    : QObject{parent}
{
    Q_D(RTCVideoCodecInfo);
    d->name_ = name;
    d->parameters_ = parameters;
}

RTCVideoCodecInfo::RTCVideoCodecInfo(QString name, QMap<QString, QString> parameters,
                                     QVector<QString> scalabilityModes, QObject *parent)
    : QObject{parent}
{
    Q_D(RTCVideoCodecInfo);
    d->name_ = name;
    d->parameters_ = parameters;
    d->scalabilityModes_ = scalabilityModes;
}

RTCVideoCodecInfo::RTCVideoCodecInfo(RTCVideoCodecInfoPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

bool RTCVideoCodecInfo::isEqualToCodecInfo(RTCVideoCodecInfo info)
{
    Q_D(RTCVideoCodecInfo);
    return d->name_ == info.name() && d->parameters_ == info.parameters() &&
           d->scalabilityModes_ == info.scalabilityModes();
}

QString RTCVideoCodecInfo::name() const
{
    Q_D(const RTCVideoCodecInfo);
    return d->name_;
}

QMap<QString, QString> RTCVideoCodecInfo::parameters() const
{
    Q_D(const RTCVideoCodecInfo);
    return d->parameters_;
}

QVector<QString> RTCVideoCodecInfo::scalabilityModes() const
{
    Q_D(const RTCVideoCodecInfo);
    return d->scalabilityModes_;
}
