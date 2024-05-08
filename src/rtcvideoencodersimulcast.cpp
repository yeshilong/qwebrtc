#include "rtcvideoencodersimulcast.h"

#include "rtcwrappednativevideoencoder.h"
#include "rtcvideocodecinfo_p.h"

#include "native/cvideoencoderfactory.h"

#include "media/engine/simulcast_encoder_adapter.h"

IRTCVideoEncoder *RTCVideoEncoderSimulcast::simulcastEncoderWithPrimary(
    IRTCVideoEncoderFactory *primary, IRTCVideoEncoderFactory *fallback,
    RTCVideoCodecInfo *videoCodecInfo)
{
    auto nativePrimary = webrtc::ObjCToNativeVideoEncoderFactory(primary);
    auto nativeFallback = webrtc::ObjCToNativeVideoEncoderFactory(fallback);
    auto nativeFormat = videoCodecInfo->d_ptr->nativeSdpVideoFormat();

    return new RTCWrappedNativeVideoEncoder(std::make_unique<webrtc::SimulcastEncoderAdapter>(
        nativePrimary.release(), nativeFallback.release(), std::move(nativeFormat)));
}
