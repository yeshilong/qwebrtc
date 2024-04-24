#include "rtcvideoencodersettings.h"

RTCVideoEncoderSettings::RTCVideoEncoderSettings(QObject *parent) : QObject{parent}
{
    name_ = QString();
    width_ = 0;
    height_ = 0;
    startBitrate_ = 0;
    maxBitrate_ = 0;
    minBitrate_ = 0;
    maxFramerate_ = 0;
    qpMax_ = 0;
    mode_ = RTCVideoCodecMode::RTCVideoCodecModeRealtimeVideo;
}

QString RTCVideoEncoderSettings::name() const
{
    return name_;
}

void RTCVideoEncoderSettings::setName(const QString &name)
{
    name_ = name;
}

quint16 RTCVideoEncoderSettings::width() const
{
    return width_;
}

void RTCVideoEncoderSettings::setWidth(quint16 width)
{
    width_ = width;
}

quint16 RTCVideoEncoderSettings::height() const
{
    return height_;
}

void RTCVideoEncoderSettings::setHeight(quint16 height)
{
    height_ = height;
}

quint32 RTCVideoEncoderSettings::startBitrate() const
{
    return startBitrate_;
}

void RTCVideoEncoderSettings::setStartBitrate(quint32 startBitrate)
{
    startBitrate_ = startBitrate;
}

quint32 RTCVideoEncoderSettings::maxBitrate() const
{
    return maxBitrate_;
}

void RTCVideoEncoderSettings::setMaxBitrate(quint32 maxBitrate)
{
    maxBitrate_ = maxBitrate;
}

quint32 RTCVideoEncoderSettings::minBitrate() const
{
    return minBitrate_;
}

void RTCVideoEncoderSettings::setMinBitrate(quint32 minBitrate)
{
    minBitrate_ = minBitrate;
}

quint32 RTCVideoEncoderSettings::maxFramerate() const
{
    return maxFramerate_;
}

void RTCVideoEncoderSettings::setMaxFramerate(quint32 maxFramerate)
{
    maxFramerate_ = maxFramerate;
}

quint32 RTCVideoEncoderSettings::qpMax() const
{
    return qpMax_;
}

void RTCVideoEncoderSettings::setQpMax(quint32 qpMax)
{
    qpMax_ = qpMax;
}

RTCVideoCodecMode RTCVideoEncoderSettings::mode() const
{
    return mode_;
}

void RTCVideoEncoderSettings::setMode(RTCVideoCodecMode mode)
{
    mode_ = mode;
}
