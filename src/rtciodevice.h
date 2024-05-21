// Copyright (C) 2024 Deltarion Systems
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
     * @brief Constructs an instance of the RTCIODevice class.
     * @param type The type of the device.
     * @param deviceId The device ID.
     * @param name The name of the device.
     * @param parent The parent object.
     */
    explicit RTCIODevice(RTCIODeviceType type, const QString deviceId, const QString name,
                         QObject *parent = nullptr);

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

  private:
    RTCIODeviceType type_;
    QString deviceId_;
    QString name_;
};

#endif // RTCIODEVICE_H
