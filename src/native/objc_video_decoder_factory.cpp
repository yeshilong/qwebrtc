#include "objc_video_decoder_factory.h"

#include "api/video_codecs/sdp_video_format.h"
#include "api/video_codecs/video_decoder.h"
#include "modules/video_coding/include/video_error_codes.h"
#include "objc_frame_buffer.h"
#include "rtc_base/time_utils.h"
#include "rtcencodedimage_p.h"
#include "rtcvideocodecinfo_p.h"
#include "rtcvideodecoder.h"
#include "rtcvideodecoderfactory.h"
#include "rtcvideoframe.h"
#include "rtcwrappednativevideodecoder.h"

namespace webrtc {

class ObjCVideoDecoder : public VideoDecoder {
 public:
  ObjCVideoDecoder(std::shared_ptr<IRTCVideoDecoder> decoder)
      : decoder_(decoder), implementation_name_(decoder->implementationName().toStdString()) {}

  bool Configure(const Settings& settings) override {
    return decoder_->startDecodeWithNumberOfCores(settings.number_of_cores()) ==
        WEBRTC_VIDEO_CODEC_OK;
  }

  int32_t Decode(const EncodedImage& input_image,
                 bool missing_frames,
                 int64_t render_time_ms = -1) override {
    auto encodedImagePrivate = new RTCEncodedImagePrivate(input_image);
    auto encodedImage = new RTCEncodedImage(*encodedImagePrivate);
    std::shared_ptr<RTCEncodedImage> encodedImagePtr(encodedImage);

    return decoder_->decode(encodedImagePtr, missing_frames, nullptr, render_time_ms);
  }

  int32_t RegisterDecodeCompleteCallback(DecodedImageCallback* callback) override {
    decoder_->setCallback([callback](std::shared_ptr<RTCVideoFrame> frame) {
      auto buffer = rtc::make_ref_counted<ObjCFrameBuffer>(frame->buffer().get());
      VideoFrame videoFrame = VideoFrame::Builder()
                                  .set_video_frame_buffer(buffer)
                                  .set_timestamp_rtp(static_cast<uint32_t>(
                                      frame->timeStampNs() / rtc::kNumNanosecsPerMicrosec))
                                  .set_timestamp_ms(0)
                                  .set_rotation(static_cast<VideoRotation>(frame->rotation()))
                                  .build();
      videoFrame.set_timestamp(frame->timeStamp());

      callback->Decoded(videoFrame);
    });

    return WEBRTC_VIDEO_CODEC_OK;
  }

  int32_t Release() override { return decoder_->releaseDecoder(); }

  const char* ImplementationName() const override { return implementation_name_.c_str(); }

 private:
  std::shared_ptr<IRTCVideoDecoder> decoder_;
  std::string implementation_name_;
};

ObjCVideoDecoderFactory::ObjCVideoDecoderFactory(IRTCVideoDecoderFactory* decoder_factory)
    : decoder_factory_(decoder_factory) {}

ObjCVideoDecoderFactory::~ObjCVideoDecoderFactory() {}

IRTCVideoDecoderFactory* ObjCVideoDecoderFactory::wrapped_decoder_factory() const {
  return decoder_factory_;
}

std::unique_ptr<VideoDecoder> ObjCVideoDecoderFactory::CreateVideoDecoder(
    const SdpVideoFormat& format) {
  for (auto codecInfo : decoder_factory_->supportedCodecs()) {
    if (codecInfo->name().toStdString() == format.name) {
      IRTCVideoDecoder* decoder = decoder_factory_->createDecoder(codecInfo);

      if (dynamic_cast<RTCWrappedNativeVideoDecoder*>(decoder)) {
        return dynamic_cast<RTCWrappedNativeVideoDecoder*>(decoder)->releaseWrappedDecoder();
      } else
        return std::unique_ptr<VideoDecoder>(
            new ObjCVideoDecoder(std::shared_ptr<IRTCVideoDecoder>(decoder)));
    }
  }

  return nullptr;
}

std::vector<SdpVideoFormat> ObjCVideoDecoderFactory::GetSupportedFormats() const {
  std::vector<SdpVideoFormat> supported_formats;

  for (auto codecInfo : decoder_factory_->supportedCodecs()) {
    SdpVideoFormat format = codecInfo->d_ptr->nativeSdpVideoFormat();
    supported_formats.push_back(format);
  }

  return supported_formats;
}

std::unique_ptr<VideoDecoderFactory> ObjCToNativeVideoDecoderFactory(
    IRTCVideoDecoderFactory* c_video_decoder_factory) {
  return std::make_unique<ObjCVideoDecoderFactory>(c_video_decoder_factory);
}

}  // namespace webrtc
