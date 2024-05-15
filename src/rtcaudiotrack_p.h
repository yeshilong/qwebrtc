#ifndef RTCAUDIOTRACK_P_H
#define RTCAUDIOTRACK_P_H

#include <QObject>
#include <QSet>

#include "rtcmediastreamtrack_p.h"

#include "rtcaudiotrack.h"
#include "rtcaudiorenderer.h"
#include "rtcaudiosource_p.h"
#include "rtcpeerconnectionfactory_p.h"

#include <QAudioFormat>
#include <QAudioBuffer>

class RTCAudioTrackPrivate : public RTCMediaStreamTrackPrivate
{
  public:
    explicit RTCAudioTrackPrivate(RTCPeerConnectionFactory *factory, RTCAudioSource *source,
                                  QString trackId);
    RTCAudioTrackPrivate(
        RTCPeerConnectionFactory *factory,
        const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeAudioTrack,
        RTCMediaStreamTrackType type);
    ~RTCAudioTrackPrivate();

    rtc::scoped_refptr<webrtc::AudioTrackInterface> nativeAudioTrack() const;

    RTCAudioSource *source_;
    rtc::scoped_refptr<webrtc::AudioSinkConverter> audioSinkConverter_;
    QSet<IRTCAudioRenderer *> renderers_;
    std::mutex lock_;

    RTCAudioTrack *q_ptr;
};

namespace webrtc
{
/**
 * Captures audio data and converts to CMSampleBuffers
 */
class AudioSinkConverter : public rtc::RefCountInterface, public webrtc::AudioTrackSinkInterface
{
  private:
    std::mutex *lock_;
    std::weak_ptr<RTCAudioTrackPrivate> audio_track_;
    int64_t total_frames_ = 0;
    bool attached_ = false;

  public:
    AudioSinkConverter(std::shared_ptr<RTCAudioTrackPrivate> audioTrack, std::mutex *lock)
    {
        RTC_LOG(LS_INFO) << "RTCAudioTrackPrivate.AudioSinkConverter init";
        audio_track_ = audioTrack;
        lock_ = lock;
    }

    ~AudioSinkConverter() override
    {
        RTC_LOG(LS_INFO) << "RTCAudioTrackPrivate.AudioSinkConverter dealloc";
    }

    // Must be called while locked
    void TryAttach()
    {
        if (attached_)
        {
            // Already attached
            return;
        }
        RTC_LOG(LS_INFO) << "RTCAudioTrackPrivate attaching sink...";
        // Reset for creating CMSampleTimingInfo correctly
        auto audio_track = audio_track_.lock();
        if (!audio_track)
        {
            RTC_LOG(LS_ERROR) << "RTCAudioTrackPrivate.AudioSinkConverter audio_track is null";
            return;
        }
        audio_track->nativeAudioTrack()->AddSink(this);
        total_frames_ = 0;
        attached_ = true;
    }

    // Must be called while locked
    void TryDetach()
    {
        if (!attached_)
        {
            // Already detached
            return;
        }
        RTC_LOG(LS_INFO) << "RTCAudioTrackPrivate detaching sink...";

        auto audio_track = audio_track_.lock();
        if (!audio_track)
        {
            RTC_LOG(LS_ERROR) << "RTCAudioTrackPrivate.AudioSinkConverter audio_track is null";
            return;
        }
        audio_track->nativeAudioTrack()->RemoveSink(this);
        attached_ = false;
    }

    void OnData(const void *audio_data, int bits_per_sample, int sample_rate,
                size_t number_of_channels, size_t number_of_frames,
                absl::optional<int64_t> absolute_capture_timestamp_ms) override
    {
        RTC_LOG(LS_INFO) << "RTCAudioTrackPrivate.AudioSinkConverter OnData bits_per_sample: "
                         << bits_per_sample << " sample_rate: " << sample_rate
                         << " number_of_channels: " << number_of_channels
                         << " number_of_frames: " << number_of_frames
                         << " absolute_capture_timestamp_ms: "
                         << (absolute_capture_timestamp_ms ? absolute_capture_timestamp_ms.value()
                                                           : 0);

        bool is_locked = lock_->try_lock();
        if (!is_locked)
        {
            RTC_LOG(LS_INFO)
                << "RTCAudioTrackPrivate.AudioSinkConverter OnData already locked, skipping...";
            return;
        }
        bool is_attached = attached_;
        lock_->unlock();

        if (!is_attached)
        {
            RTC_LOG(LS_INFO)
                << "RTCAudioTrackPrivate.AudioSinkConverter OnData already detached, skipping...";
            return;
        }

        if (!(number_of_channels == 1 || number_of_channels == 2))
        {
            RTC_LOG(LS_INFO)
                << "RTCAudioTrackPrivate: Only mono or stereo is supported currently. numberOfChannels: %zu"
                << number_of_channels;
            return;
        }

        // Set up the audio format
        QAudioFormat format;
        format.setSampleRate(sample_rate);
        format.setChannelCount(number_of_channels);
        format.setChannelConfig(number_of_channels == 2 ? QAudioFormat::ChannelConfigStereo
                                                        : QAudioFormat::ChannelConfigMono);
        format.setSampleFormat(QAudioFormat::UInt8);

        // Create an audio buffer
        QAudioBuffer buffer(number_of_frames, format, absolute_capture_timestamp_ms.value_or(0));

        // Detach the buffer to ensure we can modify it
        buffer.detach();

        // Copy the audio data into the buffer
        std::memcpy(buffer.data<char>(), audio_data,
                    number_of_frames * number_of_channels * (bits_per_sample / 8));

        // Report back to RTCAudioTrack
        auto audio_track = audio_track_.lock();
        if (audio_track)
        {
            audio_track->q_ptr->didCaptureSampleBuffer(buffer);
        }
    }
};
} // namespace webrtc

#endif // RTCAUDIOTRACK_P_H
