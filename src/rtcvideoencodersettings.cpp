// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "rtcvideoencodersettings_p.h"

RTCVideoEncoderSettingsPrivate::RTCVideoEncoderSettingsPrivate()
    : width_{0}, height_{0}, startBitrate_{0}, maxBitrate_{0}, minBitrate_{0}, maxFramerate_{0},
      qpMax_{0}, mode_{RTCVideoCodecMode::RTCVideoCodecModeRealtimeVideo}
{
}

RTCVideoEncoderSettingsPrivate::RTCVideoEncoderSettingsPrivate(
    const webrtc::VideoCodec *nativeVideoCodec)
{
    const char *codecName = CodecTypeToPayloadString(nativeVideoCodec->codecType);
    name_ = QString::fromUtf8(codecName);
    width_ = nativeVideoCodec->width;
    height_ = nativeVideoCodec->height;
    startBitrate_ = nativeVideoCodec->startBitrate;
    maxBitrate_ = nativeVideoCodec->maxBitrate;
    minBitrate_ = nativeVideoCodec->minBitrate;
    maxFramerate_ = nativeVideoCodec->maxFramerate;
    qpMax_ = nativeVideoCodec->qpMax;
    mode_ = static_cast<RTCVideoCodecMode>(nativeVideoCodec->mode);
}

webrtc::VideoCodec RTCVideoEncoderSettingsPrivate::nativeVideoCodec() const
{
    webrtc::VideoCodec nativeVideoCodec;

    nativeVideoCodec.width = width_;
    nativeVideoCodec.height = height_;
    nativeVideoCodec.startBitrate = startBitrate_;
    nativeVideoCodec.maxBitrate = maxBitrate_;
    nativeVideoCodec.minBitrate = minBitrate_;
    nativeVideoCodec.maxFramerate = maxFramerate_;
    nativeVideoCodec.qpMax = qpMax_;
    nativeVideoCodec.mode = static_cast<webrtc::VideoCodecMode>(mode_);

    return nativeVideoCodec;
}

RTCVideoEncoderSettings::RTCVideoEncoderSettings(QObject *parent)
    : QObject{parent}, d_ptr{new RTCVideoEncoderSettingsPrivate{}}
{
}

RTCVideoEncoderSettings::RTCVideoEncoderSettings(RTCVideoEncoderSettingsPrivate &d, QObject *parent)
    : QObject{parent}, d_ptr{&d}
{
}

QString RTCVideoEncoderSettings::name() const
{
    Q_D(const RTCVideoEncoderSettings);
    return d->name_;
}

void RTCVideoEncoderSettings::setName(const QString &name)
{
    Q_D(RTCVideoEncoderSettings);
    d->name_ = name;
}

quint16 RTCVideoEncoderSettings::width() const
{
    Q_D(const RTCVideoEncoderSettings);
    return d->width_;
}

void RTCVideoEncoderSettings::setWidth(quint16 width)
{
    Q_D(RTCVideoEncoderSettings);
    d->width_ = width;
}

quint16 RTCVideoEncoderSettings::height() const
{
    Q_D(const RTCVideoEncoderSettings);
    return d->height_;
}

void RTCVideoEncoderSettings::setHeight(quint16 height)
{
    Q_D(RTCVideoEncoderSettings);
    d->height_ = height;
}

quint32 RTCVideoEncoderSettings::startBitrate() const
{
    Q_D(const RTCVideoEncoderSettings);
    return d->startBitrate_;
}

void RTCVideoEncoderSettings::setStartBitrate(quint32 startBitrate)
{
    Q_D(RTCVideoEncoderSettings);
    d->startBitrate_ = startBitrate;
}

quint32 RTCVideoEncoderSettings::maxBitrate() const
{
    Q_D(const RTCVideoEncoderSettings);
    return d->maxBitrate_;
}

void RTCVideoEncoderSettings::setMaxBitrate(quint32 maxBitrate)
{
    Q_D(RTCVideoEncoderSettings);
    d->maxBitrate_ = maxBitrate;
}

quint32 RTCVideoEncoderSettings::minBitrate() const
{
    Q_D(const RTCVideoEncoderSettings);
    return d->minBitrate_;
}

void RTCVideoEncoderSettings::setMinBitrate(quint32 minBitrate)
{
    Q_D(RTCVideoEncoderSettings);
    d->minBitrate_ = minBitrate;
}

quint32 RTCVideoEncoderSettings::maxFramerate() const
{
    Q_D(const RTCVideoEncoderSettings);
    return d->maxFramerate_;
}

void RTCVideoEncoderSettings::setMaxFramerate(quint32 maxFramerate)
{
    Q_D(RTCVideoEncoderSettings);
    d->maxFramerate_ = maxFramerate;
}

quint32 RTCVideoEncoderSettings::qpMax() const
{
    Q_D(const RTCVideoEncoderSettings);
    return d->qpMax_;
}

RTCVideoCodecMode RTCVideoEncoderSettings::mode() const
{
    Q_D(const RTCVideoEncoderSettings);
    return d->mode_;
}

void RTCVideoEncoderSettings::setMode(RTCVideoCodecMode mode)
{
    Q_D(RTCVideoEncoderSettings);
    d->mode_ = mode;
}
