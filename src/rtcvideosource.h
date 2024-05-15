#ifndef RTCVIDEOSOURCE_H
#define RTCVIDEOSOURCE_H

#include <QObject>

#include "rtcmediasource.h"

class RTCVideoFrame;
class RTCVideoSourcePrivate;

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
     * @brief Initializes a new instance of the RTCVideoSource class.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCVideoSource(RTCVideoSourcePrivate &d, QObject *parent = nullptr);

    /**
     * @brief Adapts the output format to the specified width, height, and frames per second (fps).
     * Frames will be scaled down, cropped, and dropped to match the requested parameters.
     * The requested aspect ratio is orientation agnostic and will be adjusted to maintain the input orientation.
     * @param width The width.
     * @param height The height.
     * @param fps The frames per second.
     */
    void adaptOutputFormatToWidth(int width, int height, int fps);

  public Q_SLOTS:
    /**
     * @brief Slots that is called when a frame is captured.
     * @param frame The captured frame.
     */
    void didCaptureVideoFrame(RTCVideoFrame *frame);
};

#endif // RTCVIDEOSOURCE_H
