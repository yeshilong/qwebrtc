#ifndef RTCVIDEOSOURCE_H
#define RTCVIDEOSOURCE_H

#include <QObject>

#include "rtcmediasource.h"

class RTCVideoFrame;

/**
 * @brief Represents a video source with a method to adapt the output format.
 */
class RTCVideoSource : public RTCMediaSource
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCVideoSource class.
     */
    explicit RTCVideoSource(QObject *parent = nullptr);

    /**
     * @brief Adapts the output format to the specified width, height, and frames per second (fps).
     * Frames will be scaled down, cropped, and dropped to match the requested parameters.
     * The requested aspect ratio is orientation agnostic and will be adjusted to maintain the input orientation.
     * @param width The width.
     * @param height The height.
     * @param fps The frames per second.
     */
    void adaptOutputFormatToWidth(int width, int height, int fps);

  Q_SIGNALS:
    /**
     * @brief Signal that is emitted when a frame is captured.
     * @param frame The captured frame.
     */
    void frameCaptured(RTCVideoFrame *frame);
};

#endif // RTCVIDEOSOURCE_H
