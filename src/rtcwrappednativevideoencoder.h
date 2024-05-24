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

#ifndef RTCWRAPPEDNATIVEVIDEOENCODER_H
#define RTCWRAPPEDNATIVEVIDEOENCODER_H

#include <QString>

#include "rtcvideoencoder.h"

#include "api/video_codecs/video_encoder.h"

/**
 * @brief The RTCWrappedNativeVideoEncoder class.
 */
class RTCWrappedNativeVideoEncoder : public IRTCVideoEncoder
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCWrappedNativeVideoEncoder object.
     */
    explicit RTCWrappedNativeVideoEncoder(QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCWrappedNativeVideoEncoder object.
     * @param encoder The encoder.
     */
    explicit RTCWrappedNativeVideoEncoder(std::unique_ptr<webrtc::VideoEncoder> encoder,
                                          QObject *parent = nullptr);

    /**
     * @brief This moves the ownership of the encoder to the caller.
     * @return The encoder.
     */
    std::unique_ptr<webrtc::VideoEncoder> releaseWrappedEncoder();

    /**
     * @brief Sets the callback for the encoder.
     * @param callback The callback.
     */
    void setCallback(RTCVideoEncoderCallback callback);

    /**
     * @brief Starts encoding with the specified settings and number of cores.
     * @param settings The settings.
     * @param numberOfCores The number of cores.
     * @return The result of the operation.
     */
    int startEncodeWithSettings(RTCVideoEncoderSettings *settings, int numberOfCores);

    /**
     * @brief Releases the encoder.
     * @return The result of the operation.
     */
    int releaseEncoder();

    /**
     * @brief Encodes the specified frame with the specified codec specific info and frame types.
     * @param frame The frame.
     * @param info The codec specific info.
     * @param frameTypes The frame types.
     * @return The result of the operation.
     */
    int encode(RTCVideoFrame *frame, IRTCCodecSpecificInfo *info, QVector<int> frameTypes);

    /**
     * @brief Sets the bitrate and framerate for the encoder.
     * @param bitrateKbit The bitrate in kbit.
     * @param framerate The framerate.
     * @return The result of the operation.
     */
    int setBitrate(unsigned int bitrateKbit, unsigned int framerate);

    /**
     * @brief Gets the name of the implementation.
     * @return The name of the implementation.
     */
    QString implementationName();

    /**
     * @brief Gets the QP scaling settings for the encoder.
     * @return The QP scaling settings for the encoder.
     */
    RTCVideoEncoderQpThresholds *scalingSettings();

    /**
     * @brief Gets the value to which resolutions should be aligned.
     * @return The value to which resolutions should be aligned.
     */
    int resolutionAlignment() const;

    /**
     * @brief Gets a value indicating whether resolution alignment is applied to all simulcast layers simultaneously.
     * @return True if resolution alignment is applied to all simulcast layers simultaneously, false otherwise.
     */
    bool applyAlignmentToAllSimulcastLayers() const;

    /**
     * @brief Gets a value indicating whether the receiver is expected to resample/scale the source texture to the expected output size.
     * @return True if the receiver is expected to resample/scale the source texture to the expected output size, false otherwise.
     */
    bool supportsNativeHandle() const;

  private:
    std::unique_ptr<webrtc::VideoEncoder> wrappedEncoder_;
};

#endif // RTCWRAPPEDNATIVEVIDEOENCODER_H
