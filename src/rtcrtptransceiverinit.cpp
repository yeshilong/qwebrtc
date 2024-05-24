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

#include "rtcrtptransceiverinit_p.h"

#include "rtcrtpencodingparameters_p.h"

#include <QDebug>

RTCRtpTransceiverInitPrivate::RTCRtpTransceiverInitPrivate()
{
    direction_ = RTCRtpTransceiverDirection::RTCRtpTransceiverDirectionSendRecv;
    streamIds_ = QVector<QString>();
    sendEncodings_ = QVector<RTCRtpEncodingParameters *>();
}

RTCRtpTransceiverInitPrivate::~RTCRtpTransceiverInitPrivate()
{
}

webrtc::RtpTransceiverInit RTCRtpTransceiverInitPrivate::nativeRtpTransceiverInit() const
{
    webrtc::RtpTransceiverInit nativeRtpTransceiverInit;
    nativeRtpTransceiverInit.direction = static_cast<webrtc::RtpTransceiverDirection>(direction_);

    for (const QString &streamId : streamIds_)
    {
        nativeRtpTransceiverInit.stream_ids.push_back(streamId.toStdString());
    }

    for (RTCRtpEncodingParameters *sendEncoding : sendEncodings_)
    {
        nativeRtpTransceiverInit.send_encodings.push_back(
            sendEncoding->d_ptr->nativeRtpEncodingParameters());
    }

    qInfo() << "RTCRtpTransceiver created transceiver" << &nativeRtpTransceiverInit.direction;

    return nativeRtpTransceiverInit;
}

RTCRtpTransceiverInit::RTCRtpTransceiverInit(QObject *parent)
    : QObject{parent}, d_ptr{new RTCRtpTransceiverInitPrivate()}
{
}

RTCRtpTransceiverDirection RTCRtpTransceiverInit::direction() const
{
    Q_D(const RTCRtpTransceiverInit);
    return d->direction_;
}

void RTCRtpTransceiverInit::setDirection(const RTCRtpTransceiverDirection &direction)
{
    Q_D(RTCRtpTransceiverInit);
    d->direction_ = direction;
}

QVector<QString> RTCRtpTransceiverInit::streamIds() const
{
    Q_D(const RTCRtpTransceiverInit);
    return d->streamIds_;
}

void RTCRtpTransceiverInit::setStreamIds(const QVector<QString> &streamIds)
{
    Q_D(RTCRtpTransceiverInit);
    d->streamIds_ = streamIds;
}

QVector<RTCRtpEncodingParameters *> RTCRtpTransceiverInit::sendEncodings() const
{
    Q_D(const RTCRtpTransceiverInit);
    return d->sendEncodings_;
}

void RTCRtpTransceiverInit::setSendEncodings(
    const QVector<RTCRtpEncodingParameters *> &sendEncodings)
{
    Q_D(RTCRtpTransceiverInit);
    d->sendEncodings_ = sendEncodings;
}
