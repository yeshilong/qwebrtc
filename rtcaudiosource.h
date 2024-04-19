#ifndef RTCAUDIOSOURCE_H
#define RTCAUDIOSOURCE_H

#include <QObject>

#include "rtcmediasource.h"

class RTCAudioSourcePrivate;

/**
 * @brief Represents an audio source with a volume property.
 */
class RTCAudioSource : public RTCMediaSource
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCAudioSource class.
     */
    explicit RTCAudioSource(QObject *parent = nullptr);

    /**
     * @brief Gets and sets the volume for the RTCAudioSource. `volume` is a gain value in the range [0, 10].
     * Temporary fix to be able to modify volume of remote audio tracks.
     * TODO(kthelgason): Property stays here temporarily until a proper volume-api is available on the surface exposed by webrtc.
     * @return The volume.
     */
    double volume() const;
    void setVolume(double volume);

  protected:
    RTCAudioSource(RTCAudioSourcePrivate &d, QObject *parent = nullptr);

  private:
    double volume_;
};

#endif // RTCAUDIOSOURCE_H
