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

#ifndef RTCVIDEOCODECINFO_H
#define RTCVIDEOCODECINFO_H

#include <QObject>
#include <QMap>
#include <QVector>
#include <QString>

namespace webrtc
{

namespace
{
class ObjCVideoEncoder;
class ObjCVideoEncoderSelector;
} // namespace

class ObjCVideoDecoderFactory;
class ObjCVideoEncoderFactory;

} // namespace webrtc

class RTCVideoCodecInfoPrivate;
/**
 * @brief Holds information to identify a codec. Corresponds to webrtc::SdpVideoFormat.
 */
class RTCVideoCodecInfo : public QObject
{
  public:
    /**
     * @brief Initializes a new instance of the RTCVideoCodecInfo class with the specified name.
     */
    RTCVideoCodecInfo(QObject *parent = nullptr) = delete;

    /**
     * @brief Initializes a new instance of the RTCVideoCodecInfo class with the specified name.
     */
    RTCVideoCodecInfo(QString name, QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCVideoCodecInfo class with the specified name and parameters.
     */
    RTCVideoCodecInfo(QString name, QMap<QString, QString> parameters, QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCVideoCodecInfo class with the specified name, parameters, and scalability modes.
     */
    RTCVideoCodecInfo(QString name, QMap<QString, QString> parameters,
                      QVector<QString> scalabilityModes, QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCVideoCodecInfo class with the specified private implementation and parent.
     */
    RTCVideoCodecInfo(RTCVideoCodecInfoPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Determines whether the specified RTCVideoCodecInfo is equal to the current RTCVideoCodecInfo.
     */
    bool isEqualToCodecInfo(RTCVideoCodecInfo info);

    /**
     * @brief Gets the name of the codec.
     * @return The name.
     */
    QString name() const;

    /**
     * @brief Gets the parameters of the codec.
     * @return The parameters.
     */
    QMap<QString, QString> parameters() const;

    /**
     * @brief Gets the scalability modes of the codec.
     * @return The scalability modes.
     */
    QVector<QString> scalabilityModes() const;

  protected:
    friend class webrtc::ObjCVideoEncoderSelector;
    friend class webrtc::ObjCVideoDecoderFactory;
    friend class webrtc::ObjCVideoEncoderFactory;

    friend class RTCVideoEncoderSimulcast;
    friend class RTCVideoEncoderH264;

    RTCVideoCodecInfoPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCVideoCodecInfo)
};

#endif // RTCVIDEOCODECINFO_H
