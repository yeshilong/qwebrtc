#include "rtcicecandidate.h"

RTCIceCandidate::RTCIceCandidate(const QString &sdp, int sdpMLineIndex, const QString &sdpMid,
                                 QObject *parent)
    : QObject{parent}, sdp_{sdp}, sdpMLineIndex_{sdpMLineIndex}, sdpMid_{sdpMid}
{
}

QString RTCIceCandidate::sdpMid() const
{
    return sdpMid_;
}

int RTCIceCandidate::sdpMLineIndex() const
{
    return sdpMLineIndex_;
}

QString RTCIceCandidate::sdp() const
{
    return sdp_;
}

QString RTCIceCandidate::serverUrl() const
{
    return serverUrl_;
}
