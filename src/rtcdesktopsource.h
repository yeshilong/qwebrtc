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

#ifndef RTCDESKTOPSOURCE_H
#define RTCDESKTOPSOURCE_H

#include <QObject>
#include <QString>
#include <QImage>

#include "rtctypes.h"

class RTCDesktopSourcePrivate;
/**
 * @brief The RTCDesktopSource class represents a desktop source, such as the entire screen or a specific window.
 */
class RTCDesktopSource : public QObject
{
    Q_OBJECT

  public:
    explicit RTCDesktopSource(QObject *parent = nullptr);
    RTCDesktopSource(RTCDesktopSourcePrivate &d, QObject *parent = nullptr);

    QString sourceId() const;
    QString name() const;
    QImage thumbnail() const;
    RTCDesktopSourceType sourceType() const;

    QImage updateThumbnail();

  private:
    RTCDesktopSourcePrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCDesktopSource)

    void setName(const QString &name);
    void setThumbnail(const QImage &thumbnail);

    friend class RTCDesktopCapturer;
    friend class RTCDesktopMediaList;
    friend class RTCDesktopMediaListPrivate;
};

#endif // RTCDESKTOPSOURCE_H
