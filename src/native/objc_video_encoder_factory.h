#ifndef CVIDEOENCODERFACTORY_H
#define CVIDEOENCODERFACTORY_H

#include "api/video_codecs/video_encoder_factory.h"

class IRTCVideoEncoderFactory;

namespace webrtc {

namespace {
class ObjCVideoEncoder;
class ObjCVideoEncoderSelector;
}  // namespace

class ObjCVideoEncoderFactory : public VideoEncoderFactory {
 public:
  explicit ObjCVideoEncoderFactory(IRTCVideoEncoderFactory* encoder_factory);
  ~ObjCVideoEncoderFactory() override;

  IRTCVideoEncoderFactory* wrapped_encoder_factory() const;

  std::vector<SdpVideoFormat> GetSupportedFormats() const override;
  std::vector<SdpVideoFormat> GetImplementations() const override;
  std::unique_ptr<VideoEncoder> CreateVideoEncoder(const SdpVideoFormat& format) override;
  std::unique_ptr<EncoderSelectorInterface> GetEncoderSelector() const override;

 private:
  IRTCVideoEncoderFactory* encoder_factory_;
};

std::unique_ptr<VideoEncoderFactory> CToNativeVideoEncoderFactory(
    IRTCVideoEncoderFactory* c_video_encoder_factory);

}  // namespace webrtc

#endif  // CVIDEOENCODERFACTORY_H
