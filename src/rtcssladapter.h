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

#ifndef RTCSSLADAPTER_H
#define RTCSSLADAPTER_H

#include <QObject>

/**
 * @brief The RTCSSLAdapter class.
 * Initialize and clean up the SSL library. Failure is fatal.
 * These call the corresponding functions in webrtc/rtc_base/ssladapter.h.
 */
class RTCSSLAdapter : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCSSLAdapter object.
     */
    explicit RTCSSLAdapter(QObject *parent = nullptr);

    /**
     * @brief Initialize the SSL library.
     * @return True if the initialization was successful, false otherwise.
     */
    static bool RTCInitializeSSL();

    /**
     * @brief Clean up the SSL library.
     * @return True if the cleanup was successful, false otherwise.
     */
    static bool RTCCleanupSSL();
};

#endif // RTCSSLADAPTER_H
