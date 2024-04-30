#include "rtcvideoencodervp9.h"
#include "rtcwrappednativevideoencoder.h"

#include "absl/container/inlined_vector.h"
#include "api/video_codecs/sdp_video_format.h"
#include "modules/video_coding/codecs/vp9/include/vp9.h"
#include "modules/video_coding/svc/create_scalability_structure.h"

RTCVideoEncoderVP9::RTCVideoEncoderVP9(QObject *parent) : QObject{parent}
{
}

IRTCVideoEncoder *RTCVideoEncoderVP9::vp9Encoder()
{
    std::unique_ptr<webrtc::VideoEncoder> nativeEncoder(webrtc::VP9Encoder::Create());
    if (!nativeEncoder)
    {
        return nullptr;
    }
    return new RTCWrappedNativeVideoEncoder{std::move(nativeEncoder)};
}

bool RTCVideoEncoderVP9::isSupported()
{
#if defined(RTC_ENABLE_VP9)
    return true;
#else
    return false;
#endif
}

QVector<QString> RTCVideoEncoderVP9::scalabilityModes()
{
    QVector<QString> scalabilityModes;
    for (const auto &scalabilityMode : webrtc::kAllScalabilityModes)
    {
        if (webrtc::ScalabilityStructureConfig(scalabilityMode).has_value())
        {
            if (webrtc::ScalabilityStructureConfig(scalabilityMode).has_value())
            {
                auto scalabilityModeString = webrtc::ScalabilityModeToString(scalabilityMode);
                scalabilityModes.append(
                    QString::fromUtf8(scalabilityModeString.data(), scalabilityModeString.size()));
            }
        }
    }
    return scalabilityModes;
}
