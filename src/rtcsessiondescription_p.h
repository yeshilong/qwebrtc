#ifndef RTCSESSIONDESCRIPTION_P_H
#define RTCSESSIONDESCRIPTION_P_H

#include <QString>

#include "rtcsessiondescription.h"

#include "api/jsep.h"

class RTCSessionDescriptionPrivate
{
  public:
    RTCSessionDescriptionPrivate(RTCSdpType type, QString sdp);
    explicit RTCSessionDescriptionPrivate(
        const webrtc::SessionDescriptionInterface *nativeSessionDescription);
    std::unique_ptr<webrtc::SessionDescriptionInterface> nativeSessionDescription() const;

    RTCSdpType type_;
    QString sdp_;
};

#endif // RTCSESSIONDESCRIPTION_P_H
