#ifndef RTCDEFAULTAUDIOPROCESSINGMODULE_H
#define RTCDEFAULTAUDIOPROCESSINGMODULE_H

#include <QObject>

#include "rtcaudiocustomprocessingdelegate.h"
#include "rtcaudioprocessingmodule.h"

/**
 * @brief Represents the default audio processing module containing various properties and methods.
 */
class RTCDefaultAudioProcessingModule : public RTCAudioProcessingModule
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCDefaultAudioProcessingModule class.
     * @param config The audio processing configuration.
     * @param capturePostProcessingDelegate The capture post-processing delegate.
     * @param renderPreProcessingDelegate The render pre-processing delegate.
     */
    RTCDefaultAudioProcessingModule(RTCAudioProcessingConfig config,
                                    RTCAudioCustomProcessingDelegate *capturePostProcessingDelegate,
                                    RTCAudioCustomProcessingDelegate *renderPreProcessingDelegate);

    /**
     * @brief Gets and sets the capture post-processing delegate.
     * @return The capture post-processing delegate.
     */
    RTCAudioCustomProcessingDelegate capturePostProcessingDelegate() const;
    void setCapturePostProcessingDelegate(
        RTCAudioCustomProcessingDelegate capturePostProcessingDelegate);

    /**
     * @brief Gets and sets the render pre-processing delegate.
     * @return The render pre-processing delegate.
     */
    RTCAudioCustomProcessingDelegate renderPreProcessingDelegate() const;
    void setRenderPreProcessingDelegate(
        RTCAudioCustomProcessingDelegate renderPreProcessingDelegate);
};

#endif // RTCDEFAULTAUDIOPROCESSINGMODULE_H
