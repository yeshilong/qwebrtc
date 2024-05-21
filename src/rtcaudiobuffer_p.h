#ifndef QWEBRTC_RTCAUDIOBUFFER_P_H
#define QWEBRTC_RTCAUDIOBUFFER_P_H

#include "rtcaudiobuffer.h"

#include "modules/audio_processing/audio_buffer.h"

class RTCAudioBufferPrivate
{
  public:
    RTCAudioBufferPrivate(webrtc::AudioBuffer *audioBuffer);
    ~RTCAudioBufferPrivate();

    webrtc::AudioBuffer *audioBuffer() const;

    webrtc::AudioBuffer *audioBuffer_;
};

#endif //QWEBRTC_RTCAUDIOBUFFER_P_H
