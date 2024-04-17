#ifndef RTCIODEVICE_H
#define RTCIODEVICE_H

#include <QObject>

#include "rtctypes.h"

/**
 * @brief Represents a device with multiple properties.
 */
class RTCIODevice : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an instance of the RTCIODevice class.
     * @param parent The parent object.
     */
    explicit RTCIODevice(QObject *parent = nullptr);

    /**
     * @brief Returns the default device with the given type.
     * @param type The type of the device.
     * @return The default device.
     */
    static RTCIODevice defaultDeviceWithType(RTCIODeviceType type);

    /**
     * @brief Returns whether the device is the default device.
     * @return True if the device is the default device, false otherwise.
     */
    bool isDefault() const;

    /**
     * @brief Returns the type of the device.
     * @return The type of the device.
     */
    RTCIODeviceType type() const;

    /**
     * @brief Returns the device ID.
     * @return The device ID.
     */
    QString deviceId() const;

    /**
     * @brief Returns the name of the device.
     * @return The name of the device.
     */
    QString name() const;
};

#endif // RTCIODEVICE_H
