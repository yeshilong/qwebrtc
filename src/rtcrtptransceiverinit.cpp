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
