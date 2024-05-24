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

#ifndef RTCVIDEOCAPTURER_H
#define RTCVIDEOCAPTURER_H

#include <QObject>

class RTCVideoFrame;
class RTCVideoCapturer;

/**
 * @brief The IRTCVideoCapturerDelegate class.
 */
class IRTCVideoCapturerDelegate
{
  public:
    virtual void capturer(std::shared_ptr<RTCVideoCapturer> capturer,
                          std::shared_ptr<RTCVideoFrame> frame) = 0;
};

/**
 * @brief The RTCVideoCapturer class.
 */
class RTCVideoCapturer
{
  public:
    explicit RTCVideoCapturer(std::shared_ptr<IRTCVideoCapturerDelegate> videoCapturerDelegate);

    std::shared_ptr<IRTCVideoCapturerDelegate> delegate() const;
    void setDelegate(const std::shared_ptr<IRTCVideoCapturerDelegate> &delegate);

  private:
    std::shared_ptr<IRTCVideoCapturerDelegate> delegate_;
};

#endif // RTCVIDEOCAPTURER_H
