#ifndef RTCVIDEOENCODER_H
#define RTCVIDEOENCODER_H

#include <QObject>
#include <QVector>
#include <QSharedPointer>

#include <functional>

#include "rtccodecspecificinfo.h"
#include "rtcvideoencoderqpthresholds.h"
#include "rtcvideoencodersettings.h"
#include "rtcvideoframe.h"
#include "rtcencodedimage.h"

/**
 * @brief The RTCVideoEncoderCallback function.
 */
using RTCVideoEncoderCallback =
    std::function<bool(RTCEncodedImage *frame, IRTCCodecSpecificInfo *sinf)>;

/**
 * @brief The IRTCVideoEncoder interface.
 */
class IRTCVideoEncoder : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an IRTCVideoEncoder object.
     */
    explicit IRTCVideoEncoder(QObject *parent = nullptr);

    /**
     * @brief Sets the callback for the encoder.
     * @param callback The callback.
     */
    virtual void setCallback(RTCVideoEncoderCallback callback) = 0;

    /**
     * @brief Starts encoding with the specified settings and number of cores.
     * @param settings The settings.
     * @param numberOfCores The number of cores.
     * @return The result of the operation.
     */
    virtual int startEncodeWithSettings(RTCVideoEncoderSettings *settings, int numberOfCores) = 0;

    /**
     * @brief Releases the encoder.
     * @return The result of the operation.
     */
    virtual int releaseEncoder() = 0;

    /**
     * @brief Encodes the specified frame with the specified codec specific info and frame types.
     * @param frame The frame.
     * @param info The codec specific info.
     * @param frameTypes The frame types.
     * @return The result of the operation.
     */
    virtual int encode(RTCVideoFrame *frame, IRTCCodecSpecificInfo *info,
                       QVector<int> frameTypes) = 0;

    /**
     * @brief Sets the bitrate and framerate for the encoder.
     * @param bitrateKbit The bitrate in kbit.
     * @param framerate The framerate.
     * @return The result of the operation.
     */
    virtual int setBitrate(unsigned int bitrateKbit, unsigned int framerate) = 0;

    /**
     * @brief Gets the name of the implementation.
     * @return The name of the implementation.
     */
    virtual QString implementationName() = 0;

    /**
     * @brief Gets the QP scaling settings for the encoder.
     * @return The QP scaling settings for the encoder.
     */
    virtual RTCVideoEncoderQpThresholds *scalingSettings() = 0;

    /**
     * @brief Gets the value to which resolutions should be aligned.
     * @return The value to which resolutions should be aligned.
     */
    virtual int resolutionAlignment() const = 0;

    /**
     * @brief Gets a value indicating whether resolution alignment is applied to all simulcast layers simultaneously.
     * @return True if resolution alignment is applied to all simulcast layers simultaneously, false otherwise.
     */
    virtual bool applyAlignmentToAllSimulcastLayers() const = 0;

    /**
     * @brief Gets a value indicating whether the receiver is expected to resample/scale the source texture to the expected output size.
     * @return True if the receiver is expected to resample/scale the source texture to the expected output size, false otherwise.
     */
    virtual bool supportsNativeHandle() const = 0;
};

#endif // RTCVIDEOENCODER_H
