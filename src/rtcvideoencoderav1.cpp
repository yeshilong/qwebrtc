#include "rtcvideoencoderav1.h"
#include "rtcwrappednativevideoencoder.h"

#include "absl/container/inlined_vector.h"
#include "api/video_codecs/sdp_video_format.h"
#include "modules/video_coding/codecs/av1/libaom_av1_encoder.h"
#include "modules/video_coding/svc/create_scalability_structure.h"

RTCVideoEncoderAV1::RTCVideoEncoderAV1(QObject *parent) : QObject{parent}
{
}

IRTCVideoEncoder *RTCVideoEncoderAV1::av1Encoder()
{
    std::unique_ptr<webrtc::VideoEncoder> nativeEncoder(webrtc::CreateLibaomAv1Encoder());
    return new RTCWrappedNativeVideoEncoder{std::move(nativeEncoder)};
}

bool RTCVideoEncoderAV1::isSupported()
{
    return true;
}

QVector<QString> RTCVideoEncoderAV1::scalabilityModes()
{
    QVector<QString> scalabilityModes;
    for (const auto &scalabilityMode : webrtc::kAllScalabilityModes)
    {
        if (webrtc::ScalabilityStructureConfig(scalabilityMode).has_value())
        {
            auto scalabilityModeString = webrtc::ScalabilityModeToString(scalabilityMode);
            scalabilityModes.append(
                QString::fromUtf8(scalabilityModeString.data(), scalabilityModeString.size()));
        }
    }
    return scalabilityModes;
}
