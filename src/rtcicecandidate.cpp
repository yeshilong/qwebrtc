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

#include "rtcicecandidate_p.h"

#include <QDebug>

RTCIceCandidatePrivate::RTCIceCandidatePrivate(const QString &sdp, int sdpMLineIndex,
                                               const QString &sdpMid)
    : sdpMid_(sdpMid), sdpMLineIndex_(sdpMLineIndex), sdp_(sdp)
{
}

RTCIceCandidatePrivate::RTCIceCandidatePrivate(const webrtc::IceCandidateInterface *candidate)
{
    // Ensure candidate is not null
    Q_ASSERT(candidate);

    // Get the SDP representation of the candidate
    std::string sdp;
    candidate->ToString(&sdp);

    // Initialize sdpMid, sdpMLineIndex, sdp, and serverUrl from candidate
    sdpMid_ = QString::fromStdString(candidate->sdp_mid());
    sdpMLineIndex_ = candidate->sdp_mline_index();
    sdp_ = QString::fromStdString(sdp);
    serverUrl_ = QString::fromStdString(candidate->server_url());
}

std::unique_ptr<webrtc::IceCandidateInterface> RTCIceCandidatePrivate::nativeIceCandidate() const
{
    webrtc::SdpParseError error;

    webrtc::IceCandidateInterface *candidate = webrtc::CreateIceCandidate(
        sdpMid_.toStdString(), sdpMLineIndex_, sdp_.toStdString(), &error);

    if (!candidate)
    {
        qCritical() << "Failed to create ICE candidate:" << error.description.c_str()
                    << "line:" << error.line.c_str();
    }

    return std::unique_ptr<webrtc::IceCandidateInterface>(candidate);
}

RTCIceCandidate::RTCIceCandidate(const QString &sdp, int sdpMLineIndex, const QString &sdpMid,
                                 QObject *parent)
    : QObject(parent), d_ptr(new RTCIceCandidatePrivate(sdp, sdpMLineIndex, sdpMid))
{
}

RTCIceCandidate::RTCIceCandidate(RTCIceCandidatePrivate &d, QObject *parent)
    : QObject(parent), d_ptr(&d)
{
}

QString RTCIceCandidate::sdpMid() const
{
    Q_D(const RTCIceCandidate);
    return d->sdpMid_;
}

int RTCIceCandidate::sdpMLineIndex() const
{
    Q_D(const RTCIceCandidate);
    return d->sdpMLineIndex_;
}

QString RTCIceCandidate::sdp() const
{
    Q_D(const RTCIceCandidate);
    return d->sdp_;
}

QString RTCIceCandidate::serverUrl() const
{
    Q_D(const RTCIceCandidate);
    return d->serverUrl_;
}
