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

#include "rtcdesktopmedialist_p.h"
#include "rtcdesktopsource_p.h"

RTCDesktopSource *RTCDesktopMediaListPrivate::getSourceById(webrtc::MediaSource *source)
{
    for (RTCDesktopSource *desktopSource : sources_)
    {
        if (desktopSource->d_ptr->nativeMediaSource_ == source)
        {
            return desktopSource;
        }
    }
    return nullptr;
}

void RTCDesktopMediaListPrivate::mediaSourceAdded(webrtc::MediaSource *source)
{
    auto desktopSourcePrivate = new RTCDesktopSourcePrivate(source, sourceType_);
    RTCDesktopSource *desktopSource = new RTCDesktopSource(*desktopSourcePrivate);
    sources_.append(desktopSource);
    delegate_->desktopSourceAdded(desktopSource);
}

void RTCDesktopMediaListPrivate::mediaSourceRemoved(webrtc::MediaSource *source)
{
    RTCDesktopSource *desktopSource = getSourceById(source);
    if (desktopSource != nullptr)
    {
        sources_.removeOne(desktopSource);
        delegate_->desktopSourceRemoved(desktopSource);
    }
}

void RTCDesktopMediaListPrivate::mediaSourceNameChanged(webrtc::MediaSource *source)
{
    RTCDesktopSource *desktopSource = getSourceById(source);
    if (desktopSource != nullptr)
    {
        desktopSource->setName(source->name().c_str());
        delegate_->desktopSourceNameChanged(desktopSource);
    }
}

void RTCDesktopMediaListPrivate::mediaSourceThumbnailChanged(webrtc::MediaSource *source)
{
    RTCDesktopSource *desktopSource = getSourceById(source);
    if (desktopSource != nullptr)
    {
        std::vector<unsigned char> thumbnailVector = source->thumbnail();
        QByteArray thumbnailArray(reinterpret_cast<const char *>(thumbnailVector.data()),
                                  thumbnailVector.size());
        QImage thumbnail = QImage::fromData(thumbnailArray);
        desktopSource->setThumbnail(thumbnail);
        delegate_->desktopSourceThumbnailChanged(desktopSource);
    }
}

std::shared_ptr<webrtc::ObjCDesktopMediaList> RTCDesktopMediaListPrivate::nativeDesktopMediaList()
    const
{
    return nativeDesktopMediaList_;
}

RTCDesktopMediaList::RTCDesktopMediaList(RTCDesktopSourceType type,
                                         RTCDesktopMediaListDelegate *delegate, QObject *parent)
    : QObject{parent}
{
}

RTCDesktopSourceType RTCDesktopMediaList::sourceType() const
{
    Q_D(const RTCDesktopMediaList);
    return d->sourceType_;
}

int RTCDesktopMediaList::updateSourceList(bool forceReload, bool updateThumbnail)
{
    Q_D(RTCDesktopMediaList);
    return d->nativeDesktopMediaList_->UpdateSourceList(forceReload, updateThumbnail);
}

QVector<RTCDesktopSource *> RTCDesktopMediaList::sources()
{
    Q_D(RTCDesktopMediaList);
    QVector<RTCDesktopSource *> sources;
    int sourceCount = d->nativeDesktopMediaList_->GetSourceCount();
    for (int i = 0; i < sourceCount; i++)
    {
        webrtc::MediaSource *mediaSource = d->nativeDesktopMediaList_->GetSource(i);
        auto desktopSourcePrivate = new RTCDesktopSourcePrivate(mediaSource, d->sourceType_);
        sources.append(new RTCDesktopSource(*desktopSourcePrivate));
    }
    return sources;
}
