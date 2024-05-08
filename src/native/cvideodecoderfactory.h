#ifndef QTVIDEODECODERFACTORY_H
#define QTVIDEODECODERFACTORY_H

#include <QObject>
#include <QVector>

#include "api/video_codecs/video_decoder_factory.h"

class IRTCVideoDecoderFactory;

namespace webrtc
{

class CVideoDecoderFactory : public VideoDecoderFactory
{
  public:
    explicit CVideoDecoderFactory(IRTCVideoDecoderFactory *decoder_factory);
    ~CVideoDecoderFactory() override;

    IRTCVideoDecoderFactory *wrapped_decoder_factory() const;

    std::vector<SdpVideoFormat> GetSupportedFormats() const override;
    std::unique_ptr<VideoDecoder> CreateVideoDecoder(const SdpVideoFormat &format) override;

  private:
    IRTCVideoDecoderFactory *decoder_factory_;
};

std::unique_ptr<VideoDecoderFactory> ObjCToNativeVideoDecoderFactory(
    IRTCVideoDecoderFactory *objc_video_decoder_factory);

} // namespace webrtc

#endif // QTVIDEODECODERFACTORY_H
