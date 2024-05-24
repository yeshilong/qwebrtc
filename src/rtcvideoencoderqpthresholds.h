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

#ifndef RTCVIDEOENCODERQPTHRESHOLDS_H
#define RTCVIDEOENCODERQPTHRESHOLDS_H

#include <QObject>

/**
 * @brief The RTCVideoEncoderQpThresholds class.
 */
class RTCVideoEncoderQpThresholds : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCVideoEncoderQpThresholds object.
     * @param low The low threshold.
     * @param high The high threshold.
     */
    explicit RTCVideoEncoderQpThresholds(int low, int high, QObject *parent = nullptr);

    /**
     * @brief Gets the low threshold.
     * @return The low threshold.
     */
    int low() const;

    /**
     * @brief Gets the high threshold.
     * @return The high threshold.
     */
    int high() const;

  private:
    int low_;
    int high_;
};

#endif // RTCVIDEOENCODERQPTHRESHOLDS_H
