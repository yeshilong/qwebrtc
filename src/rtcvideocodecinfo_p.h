#ifndef RTCVIDEOCODECINFO_P_H
#define RTCVIDEOCODECINFO_P_H

#include "rtcvideocodecinfo.h"

#include "absl/container/inlined_vector.h"
#include "api/video_codecs/sdp_video_format.h"
#include "modules/video_coding/svc/scalability_mode_util.h"
#include "modules/video_coding/svc/create_scalability_structure.h"

class RTCVideoCodecInfoPrivate
{
  public:
    RTCVideoCodecInfoPrivate(const webrtc::SdpVideoFormat &format);

    webrtc::SdpVideoFormat nativeSdpVideoFormat() const;

    QString name_;
    QMap<QString, QString> parameters_;
    QVector<QString> scalabilityModes_;
};

#endif // RTCVIDEOCODECINFO_P_H
