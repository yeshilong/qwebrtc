#ifndef RTCAUDIOCUSTOMPROCESSINGDELEGATE_H
#define RTCAUDIOCUSTOMPROCESSINGDELEGATE_H

#include <QObject>

#include "rtcaudiobuffer.h"

/**
 * @brief Represents a delegate for custom audio processing.
 */
class RTCAudioCustomProcessingDelegate : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief (Re-)initialize the audio processor. This method can be invoked multiple times.
     * @param sampleRateHz The sample rate in Hz.
     * @param channels The number of channels.
     */
    virtual void audioProcessingInitializeWithSampleRate(unsigned int sampleRateHz,
                                                         unsigned int channels) = 0;

    /**
     * @brief Process (read or write) the audio buffer. RTCAudioBuffer is a simple wrapper for webrtc::AudioBuffer and the valid scope is only inside this method. Do not retain it.
     * @param audioBuffer The audio buffer.
     */
    virtual void audioProcessingProcess(RTCAudioBuffer audioBuffer) = 0;

    /**
     * @brief Set runtime setting. This method can be invoked multiple times.
     * @param setting The runtime setting.
     */
    // TODO: virtual void setRuntimeSetting(AudioProcessing::RuntimeSetting setting) = 0;

    /**
     * @brief Suggests releasing resources allocated by the audio processor.
     */
    virtual void audioProcessingRelease() = 0;
};

#endif // RTCAUDIOCUSTOMPROCESSINGDELEGATE_H
