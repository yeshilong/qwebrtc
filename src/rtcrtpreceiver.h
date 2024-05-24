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

#ifndef RTCRTPRECEIVER_H
#define RTCRTPRECEIVER_H

#include <QString>

#include "rtcmediastreamtrack.h"
#include "rtcrtpparameters.h"

class RTCRtpReceiverPrivate;
// /**
//  * @brief The RTCRtpReceiver interface.
//  */
// class IRTCRtpReceiver
// {
//   public:
//     /**
//      * @brief Gets the receiver ID.
//      * @return The receiver ID.
//      */
//     virtual QString receiverId() const = 0;

//     /**
//      * @brief Gets the RTP parameters.
//      * @return The RTP parameters.
//      */
//     virtual RTCRtpParameters *parameters() const = 0;

//     /**
//      * @brief Gets the media stream track.
//      * @return The media stream track.
//      */
//     virtual RTCMediaStreamTrack *track() const = 0;

//   Q_SIGNALS:
//     /**
//      * @brief This signal is emitted when the first packet is received for a media type.
//      * @param mediaType The media type.
//      */
//     void didReceiveFirstPacketForMediaType(RTCRtpMediaType mediaType);
// };

/**
 * @brief The RTCRtpReceiver class.
 */
class RTCRtpReceiver : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpReceiver object.
     */
    explicit RTCRtpReceiver(QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCRtpReceiver object.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCRtpReceiver(RTCRtpReceiverPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Gets the receiver ID.
     * @return The receiver ID.
     */
    QString receiverId() const;

    /**
     * @brief Gets the RTP parameters.
     * @return The RTP parameters.
     */
    RTCRtpParameters *parameters() const;

    /**
     * @brief Gets the media stream track.
     * @return The media stream track.
     */
    RTCMediaStreamTrack *track() const;

  Q_SIGNALS:
    /**
     * @brief This signal is emitted when the first packet is received for a media type.
     * @param mediaType The media type.
     */
    void rtpReceiverDidReceiveFirstPacketForMediaType(RTCRtpMediaType mediaType);

  private:
    RTCRtpReceiverPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpReceiver)

    friend class RTCRtpTransceiverPrivate;
    friend class RTCPeerConnection;
};

#endif // RTCRTPRECEIVER_H
