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

#ifndef RTCMEDIASTREAMTRACK_H
#define RTCMEDIASTREAMTRACK_H

#include <QObject>
#include <QString>

#include "rtctypes.h"

namespace webrtc
{
class AudioSinkConverter;
} // namespace webrtc

class RTCMediaStreamTrackPrivate;
/**
 * @brief Represents a media stream track with multiple properties.
 */
class RTCMediaStreamTrack : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCMediaSource class.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCMediaStreamTrack(RTCMediaStreamTrackPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Returns the kind of track. For example, "audio" if this track represents an audio track and "video" if this track represents a video track.
     * @return The kind of track.
     */
    QString kind() const;

    /**
     * @brief Returns the identifier of the track.
     * @return The track identifier.
     */
    QString trackId() const;

    /**
     * @brief Gets and sets the enabled state of the track.
     * @return The enabled state of the track.
     */
    bool isEnabled() const;
    void setIsEnabled(bool isEnabled);

    /**
     * @brief Returns the state of the track.
     * @return The state of the track.
     */
    RTCMediaStreamTrackState readyState() const;

    /**
     * @brief Returns the kind of audio track.
     * @return The kind of audio track.
     */
    static QString RTCMediaStreamTrackKindAudio();

    /**
     * @brief Returns the kind of video track.
     * @return The kind of video track.
     */
    static QString RTCMediaStreamTrackKindVideo();

  protected:
    RTCMediaStreamTrackPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCMediaStreamTrack)

  private:
    friend class RTCRtpSender;
    friend class RTCMediaStreamPrivate;
    friend class RTCPeerConnection;
    friend class webrtc::AudioSinkConverter;
};

#endif // RTCMEDIASTREAMTRACK_H
