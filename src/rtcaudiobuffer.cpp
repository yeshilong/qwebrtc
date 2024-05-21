#include "rtcaudiobuffer_p.h"

RTCAudioBufferPrivate::RTCAudioBufferPrivate(webrtc::AudioBuffer *audioBuffer)
    : audioBuffer_{audioBuffer}
{
}

RTCAudioBufferPrivate::~RTCAudioBufferPrivate()
{
}

webrtc::AudioBuffer *RTCAudioBufferPrivate::audioBuffer() const
{
    return audioBuffer_;
}

RTCAudioBuffer::RTCAudioBuffer(QObject *parent)
    : QObject{parent}, d_ptr{new RTCAudioBufferPrivate{nullptr}}
{
}

RTCAudioBuffer::RTCAudioBuffer(RTCAudioBufferPrivate *d, QObject *parent)
    : QObject{parent}, d_ptr{d}
{
}

unsigned int RTCAudioBuffer::channels() const
{
    Q_D(const RTCAudioBuffer);
    return d->audioBuffer()->num_channels();
}

unsigned int RTCAudioBuffer::frames() const
{
    Q_D(const RTCAudioBuffer);
    return d->audioBuffer()->num_frames();
}

unsigned int RTCAudioBuffer::framesPerBand() const
{
    Q_D(const RTCAudioBuffer);
    return d->audioBuffer()->num_frames_per_band();
}

unsigned int RTCAudioBuffer::bands() const
{
    Q_D(const RTCAudioBuffer);
    return d->audioBuffer()->num_bands();
}
