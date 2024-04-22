#ifndef RTCCVPIXELBUFFER_H
#define RTCCVPIXELBUFFER_H

#include <QObject>
#include <QVector>
#include <QByteArray>

#include "rtcvideoframebuffer.h"

/**
 * @brief The RTCCVPixelBuffer class.
 */
class RTCCVPixelBuffer : public IRTCVideoFrameBuffer
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCCVPixelBuffer object.
     */
    explicit RTCCVPixelBuffer(QObject *pixelBuffer, QObject *parent = nullptr);
    explicit RTCCVPixelBuffer(QObject *pixelBuffer, int adaptedWidth, int adaptedHeight,
                              int cropWidth, int cropHeight, int cropX, int cropY,
                              QObject *parent = nullptr);

    /**
     * @brief Gets the pixel buffer of the video frame buffer.
     * @return The pixel buffer of the video frame buffer.
     */
    QObject *pixelBuffer() const;

    /**
     * @brief Gets the crop X of the video frame buffer.
     * @return The crop X of the video frame buffer.
     */
    int cropX() const;

    /**
     * @brief Gets the crop Y of the video frame buffer.
     * @return The crop Y of the video frame buffer.
     */
    int cropY() const;

    /**
     * @brief Gets the crop width of the video frame buffer.
     * @return The crop width of the video frame buffer.
     */
    int cropWidth() const;

    /**
     * @brief Gets the crop height of the video frame buffer.
     * @return The crop height of the video frame buffer.
     */
    int cropHeight() const;

    /**
     * @brief Gets the supported pixel formats.
     * @return The supported pixel formats.
     */
    static QVector<int> supportedPixelFormats();

    /**
     * @brief Checks if cropping is required.
     * @return True if cropping is required, false otherwise.
     */
    bool requiresCropping() const;

    /**
     * @brief Checks if scaling to width is required.
     * @param width The width.
     * @param height The height.
     * @return True if scaling to width is required, false otherwise.
     */
    bool requiresScalingToWidth(int width, int height) const;

    /**
     * @brief Gets the buffer size for cropping and scaling to width.
     * @param width The width.
     * @param height The height.
     * @return The buffer size for cropping and scaling to width.
     */
    int bufferSizeForCroppingAndScalingToWidth(int width, int height) const;

    /**
     * @brief Crops and scales to the specified output pixel buffer.
     * @param outputPixelBuffer The output pixel buffer.
     * @param tmpBuffer The temporary buffer.
     * @return True if the operation was successful, false otherwise.
     */
    bool cropAndScaleTo(QObject *outputPixelBuffer, QByteArray tmpBuffer);
};

#endif // RTCCVPIXELBUFFER_H
