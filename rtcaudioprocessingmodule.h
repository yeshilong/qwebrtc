#ifndef RTCAUDIOPROCESSINGMODULE_H
#define RTCAUDIOPROCESSINGMODULE_H

#include <QObject>

#include "rtcaudioprocessingconfig.h"

/**
 * @brief Represents a module for audio processing.
 */
class RTCAudioProcessingModule : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Applies the specified audio processing configuration.
     * @param config The audio processing configuration.
     */
    virtual void applyConfig(RTCAudioProcessingConfig &config) = 0;
};

#endif // RTCAUDIOPROCESSINGMODULE_H
