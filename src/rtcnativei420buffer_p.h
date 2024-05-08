#ifndef RTCNATIVEI420BUFFER_P_H
#define RTCNATIVEI420BUFFER_P_H

#include "rtcnativei420buffer.h"

#include "api/video/i420_buffer.h"

class RTCI420BufferPrivate
{
  public:
    RTCI420BufferPrivate();
    RTCI420BufferPrivate(rtc::scoped_refptr<webrtc::I420BufferInterface> nativeI420Buffer);

    rtc::scoped_refptr<webrtc::I420BufferInterface> nativeI420Buffer() const;

    rtc::scoped_refptr<webrtc::I420BufferInterface> nativeI420Buffer_;
};

#endif // RTCNATIVEI420BUFFER_P_H
