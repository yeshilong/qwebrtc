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

#include "rtcerror_p.h"

RTCErrorPrivate::RTCErrorPrivate(const webrtc::RTCError &nativeError)
{
    nativeError_ = nativeError;
}

webrtc::RTCError RTCErrorPrivate::nativeError() const
{
    return nativeError_;
}

RTCError::RTCError(QObject *parent) : QObject{parent}
{
}

RTCError::RTCError(RTCErrorPrivate &d, QObject *parent) : QObject{parent}, d_ptr{&d}
{
}

RTCErrorType RTCError::type() const
{
    Q_D(const RTCError);
    return static_cast<RTCErrorType>(d->nativeError_.type());
}

RTCErrorDetailType RTCError::detail() const
{
    Q_D(const RTCError);
    return static_cast<RTCErrorDetailType>(d->nativeError_.error_detail());
}

QString RTCError::message() const
{
    Q_D(const RTCError);
    return QString::fromStdString(d->nativeError_.message());
}

bool RTCError::ok() const
{
    Q_D(const RTCError);
    return d->nativeError_.ok();
}
