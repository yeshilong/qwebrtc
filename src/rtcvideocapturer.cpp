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

#include "rtcvideocapturer.h"

RTCVideoCapturer::RTCVideoCapturer(std::shared_ptr<IRTCVideoCapturerDelegate> videoCapturerDelegate)
{
    delegate_ = videoCapturerDelegate;
}

std::shared_ptr<IRTCVideoCapturerDelegate> RTCVideoCapturer::delegate() const
{
    return delegate_;
}

void RTCVideoCapturer::setDelegate(const std::shared_ptr<IRTCVideoCapturerDelegate> &delegate)
{
    delegate_ = delegate;
}
