#ifndef RTCAUDIOBUFFER_H
#define RTCAUDIOBUFFER_H

#include <QObject>
#include <QVector>

/**
 * @brief Represents an audio buffer with multiple properties.
 */
class RTCAudioBuffer : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCAudioBuffer class.
     */
    explicit RTCAudioBuffer(QObject *parent = nullptr);

    /**
     * @brief Returns the number of channels.
     * @return The number of channels.
     */
    uint32_t channels() const;

    /**
     * @brief Returns the number of frames.
     * @return The number of frames.
     */
    uint32_t frames() const;

    /**
     * @brief Returns the number of frames per band.
     * @return The number of frames per band.
     */
    uint32_t framesPerBand() const;

    /**
     * @brief Returns the number of bands.
     * @return The number of bands.
     */
    uint32_t bands() const;

  private:
    unsigned int channels_;
    unsigned int frames_;
    unsigned int framesPerBand_;
    unsigned int bands_;
};

#endif // RTCAUDIOBUFFER_H
