#ifndef RTCVIDEOENCODERFACTORY_H
#define RTCVIDEOENCODERFACTORY_H

#include <QObject>
#include <QVector>

#include "rtcvideocodecinfo.h"
#include "rtcvideoencoder.h"

/**
 * @brief The IRTCVideoEncoderSelector interface.
 */
class IRTCVideoEncoderSelector : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Registers the current encoder info.
     * @param info The encoder info.
     */
    virtual void registerCurrentEncoderInfo(RTCVideoCodecInfo *info) = 0;

    /**
     * @brief Gets the encoder for the specified bitrate.
     * @param bitrate The bitrate.
     * @return The encoder for the specified bitrate.
     */
    virtual RTCVideoCodecInfo *encoderForBitrate(int bitrate) = 0;

    /**
     * @brief Gets the encoder for a broken encoder.
     * @return The encoder for a broken encoder.
     */
    virtual RTCVideoCodecInfo *encoderForBrokenEncoder() = 0;

    /**
     * @brief Gets the encoder for a resolution change by size.
     * @param size The size.
     * @return The encoder for a resolution change by size.
     */
    virtual RTCVideoCodecInfo *encoderForResolutionChangeBySize(QSize size) = 0;
};

/**
 * @brief The IRTCVideoEncoderFactory interface.
 */
class IRTCVideoEncoderFactory : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an IRTCVideoEncoderFactory object.
     */
    explicit IRTCVideoEncoderFactory(QObject *parent = nullptr);

    /**
     * @brief Creates an encoder.
     * @param info The codec info.
     * @return The created encoder.
     */
    virtual IRTCVideoEncoder *createEncoder(RTCVideoCodecInfo *info) = 0;

    /**
     * @brief Gets the supported codecs.
     * @return The supported codecs.
     */
    virtual QVector<RTCVideoCodecInfo *> supportedCodecs() = 0;

    /**
     * @brief Gets the implementations.
     * @return The implementations.
     */
    virtual QVector<RTCVideoCodecInfo *> implementations() = 0;

    /**
     * @brief Gets the encoder selector.
     * @return The encoder selector.
     */
    virtual IRTCVideoEncoderSelector *encoderSelector() = 0;
};

#endif // RTCVIDEOENCODERFACTORY_H
