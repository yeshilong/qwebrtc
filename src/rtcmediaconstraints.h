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

#ifndef RTCMEDIACONSTRAINTS_H
#define RTCMEDIACONSTRAINTS_H

#include <QObject>
#include <QMap>
#include <QString>

class RTCMediaConstraintsPrivate;
/**
 * @brief The RTCMediaConstraints class.
 */
class RTCMediaConstraints : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes an RTCMediaConstraints instance with the specified mandatory and optional constraints.
     * @param mandatory The mandatory constraints.
     * @param optional The optional constraints.
     */
    explicit RTCMediaConstraints(QMap<QString, QString> mandatory, QMap<QString, QString> optional,
                                 QObject *parent = nullptr);

    /**
     * @brief Constraint keys for media sources.
     * The value for this key should be a base64 encoded string containing
     * the data from the serialized configuration proto.
     */
    static QString RTCMediaConstraintsAudioNetworkAdaptorConfig();

    /**
     * @brief Constraint keys for generating offers and answers.
     */
    static QString RTCMediaConstraintsIceRestart();
    static QString RTCMediaConstraintsOfferToReceiveAudio();
    static QString RTCMediaConstraintsOfferToReceiveVideo();
    static QString RTCMediaConstraintsVoiceActivityDetection();

    /**
     * @brief Constraint values for Boolean parameters.
     */
    static QString RTCMediaConstraintsValueTrue();
    static QString RTCMediaConstraintsValueFalse();

  private:
    RTCMediaConstraintsPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCMediaConstraints)

    friend class RTCPeerConnectionPrivate;
    friend class RTCPeerConnection;
    friend class RTCPeerConnectionFactory;
};

#endif // RTCMEDIACONSTRAINTS_H
