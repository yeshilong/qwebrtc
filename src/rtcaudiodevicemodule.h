#ifndef RTCAUDIODEVICEMODULE_H
#define RTCAUDIODEVICEMODULE_H

#include <QObject>
#include <QVector>

class RTCIODevice;                // Forward declaration
class RTCOnAudioDevicesDidUpdate; // Forward declaration

/**
 * @brief Represents an audio device module with multiple properties and methods.
 */
class RTCAudioDeviceModule : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an instance of the RTCAudioDeviceModule class.
     * @param parent The parent object.
     */
    explicit RTCAudioDeviceModule(QObject *parent = nullptr);

    /**
     * @brief Returns the output devices.
     * @return The output devices.
     */
    QVector<RTCIODevice> outputDevices() const;

    /**
     * @brief Returns the input devices.
     * @return The input devices.
     */
    QVector<RTCIODevice> inputDevices() const;

    /**
     * @brief Returns whether the module is playing.
     * @return True if the module is playing, false otherwise.
     */
    bool isPlaying() const;

    /**
     * @brief Returns whether the module is recording.
     * @return True if the module is recording, false otherwise.
     */
    bool isRecording() const;

    /**
     * @brief Gets and sets the output device.
     * @return The output device.
     */
    RTCIODevice outputDevice() const;
    void setOutputDevice(const RTCIODevice &outputDevice);

    /**
     * @brief Gets and sets the input device.
     * @return The input device.
     */
    RTCIODevice inputDevice() const;
    void setInputDevice(const RTCIODevice &inputDevice);

    /**
     * @brief Tries to set the output device.
     * @param device The device to set.
     * @return True if the operation was successful, false otherwise.
     */
    bool trySetOutputDevice(const RTCIODevice &device);

    /**
     * @brief Tries to set the input device.
     * @param device The device to set.
     * @return True if the operation was successful, false otherwise.
     */
    bool trySetInputDevice(const RTCIODevice &device);

    /**
     * @brief Sets the devices updated handler.
     * @param handler The handler to set.
     * @return True if the operation was successful, false otherwise.
     */
    bool setDevicesUpdatedHandler(const RTCOnAudioDevicesDidUpdate &handler);

    /**
     * @brief Starts playout.
     * @return True if the operation was successful, false otherwise.
     */
    bool startPlayout();

    /**
     * @brief Stops playout.
     * @return True if the operation was successful, false otherwise.
     */
    bool stopPlayout();

    /**
     * @brief Initializes playout.
     * @return True if the operation was successful, false otherwise.
     */
    bool initPlayout();

    /**
     * @brief Starts recording.
     * @return True if the operation was successful, false otherwise.
     */
    bool startRecording();

    /**
     * @brief Stops recording.
     * @return True if the operation was successful, false otherwise.
     */
    bool stopRecording();

    /**
     * @brief Initializes recording.
     * @return True if the operation was successful, false otherwise.
     */
    bool initRecording();
};

#endif // RTCAUDIODEVICEMODULE_H
