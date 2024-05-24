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

#ifndef RTCMEDIASTREAM_H
#define RTCMEDIASTREAM_H

#include <QObject>
#include <QVector>
#include <QString>

class RTCAudioTrack;
class RTCVideoTrack;
class RTCPeerConnectionFactory;

class RTCMediaStreamPrivate;
/**
 * @brief Represents a media stream.
 */
class RTCMediaStream : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCMediaStream class.
     */
    explicit RTCMediaStream(QObject *parent = nullptr);

    /**
     * @brief Initializes a new instance of the RTCMediaStream class.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    explicit RTCMediaStream(RTCMediaStreamPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Gets the audio tracks in this stream.
     * @return The audio tracks.
     */
    QVector<RTCAudioTrack *> audioTracks() const;

    /**
     * @brief Gets the video tracks in this stream.
     * @return The video tracks.
     */
    QVector<RTCVideoTrack *> videoTracks() const;

    /**
     * @brief Gets an identifier for this media stream.
     * @return The stream ID.
     */
    QString streamId() const;

    /**
     * @brief Adds the given audio track to this media stream.
     * @param audioTrack The audio track.
     */
    void addAudioTrack(RTCAudioTrack *audioTrack);

    /**
     * @brief Adds the given video track to this media stream.
     * @param videoTrack The video track.
     */
    void addVideoTrack(RTCVideoTrack *videoTrack);

    /**
     * @brief Removes the given audio track from this media stream.
     * @param audioTrack The audio track.
     */
    void removeAudioTrack(RTCAudioTrack *audioTrack);

    /**
     * @brief Removes the given video track from this media stream.
     * @param videoTrack The video track.
     */
    void removeVideoTrack(RTCVideoTrack *videoTrack);

  private:
    RTCMediaStreamPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCMediaStream)

    friend class RTCPeerConnection;
};

#endif // RTCMEDIASTREAM_H
