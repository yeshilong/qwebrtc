#ifndef RTCAUDIOPROCESSINGCONFIG_H
#define RTCAUDIOPROCESSINGCONFIG_H

#include <QObject>

/**
 * @brief Represents configuration parameters for audio processing.
 */
class RTCAudioProcessingConfig : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an instance of the RTCAudioProcessingConfig class.
     * @param parent The parent object.
     */
    explicit RTCAudioProcessingConfig(QObject *parent = nullptr);

    /**
     * @brief Gets and sets the state of the echo canceler.
     * @return True if the echo canceler is enabled, false otherwise.
     */
    bool echoCancellerEnabled() const;
    void setEchoCancellerEnabled(bool echoCancellerEnabled);

    /**
     * @brief Gets and sets the state of the echo canceler mobile mode.
     * @return True if the echo canceler mobile mode is enabled, false otherwise.
     */
    bool echoCancellerMobileMode() const;
    void setEchoCancellerMobileMode(bool echoCancellerMobileMode);
};

#endif // RTCAUDIOPROCESSINGCONFIG_H
