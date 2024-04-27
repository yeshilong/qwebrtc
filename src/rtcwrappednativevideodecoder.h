#ifndef RTCWRAPPEDNATIVEVIDEODECODER_H
#define RTCWRAPPEDNATIVEVIDEODECODER_H

#include <QObject>

#include "rtcvideodecoder.h"

#include "media/base/codec.h"
#include "api/video_codecs/video_decoder.h"

/**
 * @brief The RTCWrappedNativeVideoDecoder class.
 */
class RTCWrappedNativeVideoDecoder : public IRTCVideoDecoder
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCWrappedNativeVideoDecoder object.
     */
    explicit RTCWrappedNativeVideoDecoder(QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCWrappedNativeVideoDecoder object.
     * @param decoder The decoder.
     */
    explicit RTCWrappedNativeVideoDecoder(std::unique_ptr<webrtc::VideoDecoder> decoder,
                                          QObject *parent = nullptr);

    /**
     * @brief This moves the ownership of the decoder to the caller.
     * @return The decoder.
     */
    std::unique_ptr<webrtc::VideoDecoder> releaseWrappedDecoder();

    /**
     * @brief Sets the callback.
     * @param callback The callback.
     */
    void setCallback(RTCVideoDecoderCallback callback);

    /**
     * @brief Starts decode with number of cores.
     * @param numberOfCores The number of cores.
     * @return The result.
     */
    int startDecodeWithNumberOfCores(int numberOfCores);

    /**
     * @brief Releases the decoder.
     * @return The result.
     */
    int releaseDecoder();

    /**
     * @brief Decodes the encoded image.
     * @param encodedImage The encoded image.
     * @param missingFrames The missing frames.
     * @param info The codec specific info.
     * @param renderTimeMs The render time in milliseconds.
     * @return The result.
     */
    int decode(QSharedPointer<RTCEncodedImage> encodedImage, bool missingFrames,
               QSharedPointer<IRTCCodecSpecificInfo> info, qint64 renderTimeMs);

    /**
     * @brief Gets the implementation name.
     * @return The implementation name.
     */
    QString implementationName() const;

  private:
    std::unique_ptr<webrtc::VideoDecoder> wrappedDecoder_;
};

#endif // RTCWRAPPEDNATIVEVIDEODECODER_H
