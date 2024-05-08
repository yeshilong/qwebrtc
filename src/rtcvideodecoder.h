#ifndef RTCVIDEODECODER_H
#define RTCVIDEODECODER_H

#include <QObject>
#include <QString>

#include <functional>

class RTCVideoFrame;
class RTCEncodedImage;
class IRTCCodecSpecificInfo;

/**
 * @brief The RTCVideoDecoderCallback function pointer.
 */
using RTCVideoDecoderCallback = std::function<void(std::shared_ptr<RTCVideoFrame> frame)>;

/**
 * @brief The IRTCVideoDecoder class.
 */
class IRTCVideoDecoder : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an IRTCVideoDecoder object.
     */
    explicit IRTCVideoDecoder(QObject *parent = nullptr);

    /**
     * @brief Sets the callback.
     * @param callback The callback.
     */
    virtual void setCallback(RTCVideoDecoderCallback callback) = 0;

    /**
     * @brief Starts decode with number of cores.
     * @param numberOfCores The number of cores.
     * @return The result.
     */
    virtual int startDecodeWithNumberOfCores(int numberOfCores) = 0;

    /**
     * @brief Releases the decoder.
     * @return The result.
     */
    virtual int releaseDecoder() = 0;

    /**
     * @brief Decodes the encoded image.
     * @param encodedImage The encoded image.
     * @param missingFrames The missing frames.
     * @param info The codec specific info.
     * @param renderTimeMs The render time in milliseconds.
     * @return The result.
     */
    virtual int decode(std::shared_ptr<RTCEncodedImage> encodedImage, bool missingFrames,
                       std::shared_ptr<IRTCCodecSpecificInfo> info, qint64 renderTimeMs) = 0;

    /**
     * @brief Gets the implementation name.
     * @return The implementation name.
     */
    virtual QString implementationName() const = 0;
};

#endif // RTCVIDEODECODER_H
