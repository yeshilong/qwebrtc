#ifndef RTCICECANDIDATE_P_H
#define RTCICECANDIDATE_P_H

#include <QString>

#include "qwebrtcglobal.h"

#include "api/jsep.h"

class QWEBRTC_EXPORT RTCIceCandidatePrivate {
  public:
    RTCIceCandidatePrivate(const QString &sdp, int sdpMLineIndex, const QString &sdpMid);
    RTCIceCandidatePrivate(const webrtc::IceCandidateInterface *candidate);
    std::unique_ptr<webrtc::IceCandidateInterface> getNativeCandidate() const;

    QString sdpMid_;
    int sdpMLineIndex_;
    QString sdp_;
    QString serverUrl_;
};

#endif // RTCICECANDIDATE_P_H
