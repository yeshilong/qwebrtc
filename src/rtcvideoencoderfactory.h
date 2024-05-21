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

#ifndef RTCVIDEOENCODERFACTORY_H
#define RTCVIDEOENCODERFACTORY_H

#include <QObject>
#include <QVector>

#include "rtcvideocodecinfo.h"
#include "rtcvideoencoder.h"

/**
 * @brief The IRTCVideoEncoderSelector interface.
 */
class IRTCVideoEncoderSelector : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Registers the current encoder info.
     * @param info The encoder info.
     */
    virtual void registerCurrentEncoderInfo(RTCVideoCodecInfo *info) = 0;

    /**
     * @brief Gets the encoder for the specified bitrate.
     * @param bitrate The bitrate.
     * @return The encoder for the specified bitrate.
     */
    virtual RTCVideoCodecInfo *encoderForBitrate(int bitrate) = 0;

    /**
     * @brief Gets the encoder for a broken encoder.
     * @return The encoder for a broken encoder.
     */
    virtual RTCVideoCodecInfo *encoderForBrokenEncoder() = 0;

    /**
     * @brief Gets the encoder for a resolution change by size.
     * @param size The size.
     * @return The encoder for a resolution change by size.
     */
    virtual RTCVideoCodecInfo *encoderForResolutionChangeBySize(QSize size) = 0;
};

/**
 * @brief The IRTCVideoEncoderFactory interface.
 */
class IRTCVideoEncoderFactory : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an IRTCVideoEncoderFactory object.
     */
    explicit IRTCVideoEncoderFactory(QObject *parent = nullptr);

    /**
     * @brief Creates an encoder.
     * @param info The codec info.
     * @return The created encoder.
     */
    virtual IRTCVideoEncoder *createEncoder(RTCVideoCodecInfo *info) = 0;

    /**
     * @brief Gets the supported codecs.
     * @return The supported codecs.
     */
    virtual QVector<RTCVideoCodecInfo *> supportedCodecs() = 0;

    /**
     * @brief Gets the implementations.
     * @return The implementations.
     */
    virtual QVector<RTCVideoCodecInfo *> implementations()
    {
        return QVector<RTCVideoCodecInfo *>();
    }

    /**
     * @brief Gets the encoder selector.
     * @return The encoder selector.
     */
    virtual IRTCVideoEncoderSelector *encoderSelector()
    {
        return nullptr;
    }
};

#endif // RTCVIDEOENCODERFACTORY_H
