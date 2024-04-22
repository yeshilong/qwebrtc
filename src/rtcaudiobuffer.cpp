#include "rtcaudiobuffer.h"

RTCAudioBuffer::RTCAudioBuffer(QObject *parent) : QObject{parent}
{
}

unsigned int RTCAudioBuffer::channels() const
{
    return channels_;
}

unsigned int RTCAudioBuffer::frames() const
{
    return frames_;
}

unsigned int RTCAudioBuffer::framesPerBand() const
{
    return framesPerBand_;
}

unsigned int RTCAudioBuffer::bands() const
{
    return bands_;
}
