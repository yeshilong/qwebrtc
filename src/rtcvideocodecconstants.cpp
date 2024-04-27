#include "rtcvideocodecconstants.h"

#include "media/base/media_constants.h"

QString RTCVideoCodecConstants::RTCVideoCodecVp8Name()
{
    return cricket::kVp8CodecName;
}

QString RTCVideoCodecConstants::RTCVideoCodecVp9Name()
{
    return cricket::kVp9CodecName;
}

QString RTCVideoCodecConstants::RTCVideoCodecAv1Name()
{
    return cricket::kAv1CodecName;
}

QString RTCVideoCodecConstants::RTCVideoCodecH264Name()
{
    return cricket::kH264CodecName;
}
