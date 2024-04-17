#ifndef RTCVIDEOENCODERQPTHRESHOLDS_H
#define RTCVIDEOENCODERQPTHRESHOLDS_H

#include <QObject>

/**
 * @brief The RTCVideoEncoderQpThresholds class.
 */
class RTCVideoEncoderQpThresholds : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderQpThresholds object.
     * @param low The low threshold.
     * @param high The high threshold.
     */
    explicit RTCVideoEncoderQpThresholds(int low, int high, QObject *parent = nullptr);

    /**
     * @brief Gets the low threshold.
     * @return The low threshold.
     */
    int low() const;

    /**
     * @brief Gets the high threshold.
     * @return The high threshold.
     */
    int high() const;
};

#endif // RTCVIDEOENCODERQPTHRESHOLDS_H
