#include "rtcvideocodecinfo.h"

RTCVideoCodecInfo::RTCVideoCodecInfo(QString name, QObject *parent) : QObject{parent}
{
    name_ = name;
}

RTCVideoCodecInfo::RTCVideoCodecInfo(QString name, QMap<QString, QString> parameters,
                                     QObject *parent)
    : QObject{parent}
{
    name_ = name;
    parameters_ = parameters;
}

RTCVideoCodecInfo::RTCVideoCodecInfo(QString name, QMap<QString, QString> parameters,
                                     QVector<QString> scalabilityModes, QObject *parent)
    : QObject{parent}
{
    name_ = name;
    parameters_ = parameters;
    scalabilityModes_ = scalabilityModes;
}

bool RTCVideoCodecInfo::isEqualToCodecInfo(RTCVideoCodecInfo info)
{
    return name_ == info.name_ && parameters_ == info.parameters_ &&
           scalabilityModes_ == info.scalabilityModes_;
}
