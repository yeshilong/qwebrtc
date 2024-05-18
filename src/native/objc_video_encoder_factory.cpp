#include "objc_video_encoder_factory.h"

#include <QVector>

#include "api/video/video_frame.h"
#include "api/video_codecs/sdp_video_format.h"
#include "api/video_codecs/video_encoder.h"
#include "modules/video_coding/include/video_codec_interface.h"
#include "modules/video_coding/include/video_error_codes.h"
#include "objc_video_frame.h"
#include "rtccodecspecificinfoh264_p.h"
#include "rtcencodedimage_p.h"
#include "rtcvideocodecinfo_p.h"
#include "rtcvideoencoder.h"
#include "rtcvideoencoderfactory.h"
#include "rtcvideoencodersettings_p.h"
#include "rtcwrappednativevideoencoder.h"

namespace webrtc {

namespace {

class ObjCVideoEncoder : public VideoEncoder {
 public:
  ObjCVideoEncoder(IRTCVideoEncoder* encoder)
      : encoder_(encoder), implementation_name_(encoder->implementationName().toStdString()) {}

  int32_t InitEncode(const VideoCodec* codec_settings, const Settings& encoder_settings) override {
    auto privateSettings = new RTCVideoEncoderSettingsPrivate(codec_settings);
    RTCVideoEncoderSettings* settings = new RTCVideoEncoderSettings(*privateSettings);
    return encoder_->startEncodeWithSettings(settings, encoder_settings.number_of_cores);
  }

  int32_t RegisterEncodeCompleteCallback(EncodedImageCallback* callback) override {
    if (callback) {
      encoder_->setCallback([callback](RTCEncodedImage* frame, IRTCCodecSpecificInfo* info) {
        EncodedImage encodedImage = frame->d_ptr->nativeEncodedImage();

        // Handle types that can be converted into one of
        // CodecSpecificInfo's hard coded cases.
        CodecSpecificInfo codecSpecificInfo;
        if (dynamic_cast<RTCCodecSpecificInfoH264*>(info)) {
          codecSpecificInfo =
              static_cast<RTCCodecSpecificInfoH264*>(info)->d_ptr->nativeCodecSpecificInfo();
        }

        EncodedImageCallback::Result res =
            callback->OnEncodedImage(encodedImage, &codecSpecificInfo);
        return res.error == EncodedImageCallback::Result::OK;
      });
    } else {
      encoder_->setCallback(nullptr);
    }
    return WEBRTC_VIDEO_CODEC_OK;
  }

  int32_t Release() override { return encoder_->releaseEncoder(); }

  int32_t Encode(const VideoFrame& frame, const std::vector<VideoFrameType>* frame_types) override {
    QVector<int> rtcFrameTypes;
    for (size_t i = 0; i < frame_types->size(); ++i) {
      rtcFrameTypes.push_back(static_cast<int>(frame_types->at(i)));
    }

    return encoder_->encode(NativeToObjCVideoFrame(frame), nullptr, rtcFrameTypes);
  }

  void SetRates(const RateControlParameters& parameters) override {
    const uint32_t bitrate = parameters.bitrate.get_sum_kbps();
    const uint32_t framerate = static_cast<uint32_t>(parameters.framerate_fps + 0.5);
    encoder_->setBitrate(bitrate, framerate);
  }

  VideoEncoder::EncoderInfo GetEncoderInfo() const override {
    EncoderInfo info;
    info.implementation_name = implementation_name_;

    RTCVideoEncoderQpThresholds* qp_thresholds = encoder_->scalingSettings();

    info.scaling_settings = qp_thresholds ?
        ScalingSettings(qp_thresholds->low(), qp_thresholds->high()) :
        ScalingSettings::kOff;

    info.requested_resolution_alignment = encoder_->resolutionAlignment() > 0 ?: 1;
    info.apply_alignment_to_all_simulcast_layers = encoder_->applyAlignmentToAllSimulcastLayers();
    info.supports_native_handle = encoder_->supportsNativeHandle();
    info.is_hardware_accelerated = true;
    return info;
  }

 private:
  IRTCVideoEncoder* encoder_;
  const std::string implementation_name_;
};

class ObjCVideoEncoderSelector : public VideoEncoderFactory::EncoderSelectorInterface {
 public:
  ObjCVideoEncoderSelector(IRTCVideoEncoderSelector* selector) { selector_ = selector; }
  void OnCurrentEncoder(const SdpVideoFormat& format) override {
    RTCVideoCodecInfoPrivate* privateInfo = new RTCVideoCodecInfoPrivate(format);
    RTCVideoCodecInfo* info = new RTCVideoCodecInfo(*privateInfo);
    selector_->registerCurrentEncoderInfo(info);
  }
  absl::optional<SdpVideoFormat> OnEncoderBroken() override {
    RTCVideoCodecInfo* info = selector_->encoderForBrokenEncoder();

    if (info) {
      return info->d_ptr->nativeSdpVideoFormat();
    }

    return absl::nullopt;
  }
  absl::optional<SdpVideoFormat> OnAvailableBitrate(const DataRate& rate) override {
    RTCVideoCodecInfo* info = selector_->encoderForBitrate(rate.kbps<int>());

    if (info) {
      return info->d_ptr->nativeSdpVideoFormat();
    }

    return absl::nullopt;
  }

  absl::optional<SdpVideoFormat> OnResolutionChange(const RenderResolution& resolution) override {
    RTCVideoCodecInfo* info =
        selector_->encoderForResolutionChangeBySize(QSize(resolution.Width(), resolution.Height()));

    if (info) {
      return info->d_ptr->nativeSdpVideoFormat();
    }

    return absl::nullopt;
  }

 private:
  IRTCVideoEncoderSelector* selector_;
};

}  // namespace

ObjCVideoEncoderFactory::ObjCVideoEncoderFactory(IRTCVideoEncoderFactory* encoder_factory)
    : encoder_factory_(encoder_factory) {}

ObjCVideoEncoderFactory::~ObjCVideoEncoderFactory() {}

IRTCVideoEncoderFactory* ObjCVideoEncoderFactory::wrapped_encoder_factory() const {
  return encoder_factory_;
}

std::vector<SdpVideoFormat> ObjCVideoEncoderFactory::GetSupportedFormats() const {
  std::vector<SdpVideoFormat> supported_formats;

  for (auto& supportedCodec : encoder_factory_->supportedCodecs()) {
    SdpVideoFormat format = supportedCodec->d_ptr->nativeSdpVideoFormat();
    supported_formats.push_back(format);
  }

  return supported_formats;
}

std::vector<SdpVideoFormat> ObjCVideoEncoderFactory::GetImplementations() const {
  if (!encoder_factory_->implementations().empty()) {
    std::vector<SdpVideoFormat> supported_formats;
    for (auto& supportedCodec : encoder_factory_->implementations()) {
      SdpVideoFormat format = supportedCodec->d_ptr->nativeSdpVideoFormat();
      supported_formats.push_back(format);
    }
    return supported_formats;
  }

  return GetSupportedFormats();
}

std::unique_ptr<VideoEncoder> ObjCVideoEncoderFactory::CreateVideoEncoder(
    const SdpVideoFormat& format) {
  RTCVideoCodecInfoPrivate* privateInfo = new RTCVideoCodecInfoPrivate(format);
  RTCVideoCodecInfo* info = new RTCVideoCodecInfo(*privateInfo);

  IRTCVideoEncoder* encoder = encoder_factory_->createEncoder(info);

  if (dynamic_cast<RTCWrappedNativeVideoEncoder*>(encoder) != nullptr) {
    return ((RTCWrappedNativeVideoEncoder*)encoder)->releaseWrappedEncoder();
  } else {
    return std::unique_ptr<ObjCVideoEncoder>(new ObjCVideoEncoder(encoder));
  }
}

std::unique_ptr<webrtc::VideoEncoderFactory::EncoderSelectorInterface>
    ObjCVideoEncoderFactory::GetEncoderSelector() const {
  if (encoder_factory_->encoderSelector() != nullptr) {
    return absl::make_unique<ObjCVideoEncoderSelector>(encoder_factory_->encoderSelector());
  }

  return nullptr;
}

std::unique_ptr<VideoEncoderFactory> ObjCToNativeVideoEncoderFactory(
    IRTCVideoEncoderFactory* c_video_encoder_factory) {
  return std::make_unique<ObjCVideoEncoderFactory>(c_video_encoder_factory);
}

}  // namespace webrtc
