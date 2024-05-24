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

#ifndef RTCDESKTOPMEDIALIST_H
#define RTCDESKTOPMEDIALIST_H

#include <QObject>
#include <QVector>

#include "rtcdesktopsource.h"
#include "rtctypes.h"

namespace webrtc
{
class ObjCDesktopMediaList;
class MediaSource;
} // namespace webrtc

class RTCDesktopMediaListDelegate
{
  public:
    virtual void desktopSourceAdded(RTCDesktopSource *source) = 0;
    virtual void desktopSourceRemoved(RTCDesktopSource *source) = 0;
    virtual void desktopSourceNameChanged(RTCDesktopSource *source) = 0;
    virtual void desktopSourceThumbnailChanged(RTCDesktopSource *source) = 0;
};

class RTCDesktopMediaListPrivate;
/**
 * @brief RTCDesktopMediaList containing various properties and methods.
 */
class RTCDesktopMediaList : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes a new instance of the RTCDesktopMediaList class with the specified type and delegate.
     */
    RTCDesktopMediaList(RTCDesktopSourceType type, RTCDesktopMediaListDelegate *delegate,
                        QObject *parent = nullptr);

    /**
     * @brief Gets the source type.
     * @return The source type.
     */
    RTCDesktopSourceType sourceType() const;

    /**
     * @brief Updates the source list and returns the result.
     * @return The result.
     */
    int updateSourceList(bool forceReload, bool updateThumbnail);

    /**
     * @brief Gets the sources.
     * @return The sources.
     */
    QVector<RTCDesktopSource *> sources();

  Q_SIGNALS:
    void desktopSourceAdded(RTCDesktopSource *source);
    void desktopSourceRemoved(RTCDesktopSource *source);
    void desktopSourceNameChanged(RTCDesktopSource *source);
    void desktopSourceThumbnailChanged(RTCDesktopSource *source);

  protected:
    RTCDesktopMediaList(RTCDesktopMediaListPrivate &d, QObject *parent = nullptr);

  private:
    friend class webrtc::ObjCDesktopMediaList;

    RTCDesktopMediaListPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCDesktopMediaList)
};

#endif // RTCDESKTOPMEDIALIST_H
