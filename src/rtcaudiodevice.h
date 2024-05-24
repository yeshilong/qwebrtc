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

#ifndef RTCAUDIODEVICE_H
#define RTCAUDIODEVICE_H

#include <functional>

#include <QByteArray>

#ifdef Q_OS_MAC
#include <AudioUnit/AudioUnit.h>

typedef std::function<OSStatus(AudioUnitRenderActionFlags *actionFlags,
                               const AudioTimeStamp *timestamp, int inputBusNumber,
                               UInt32 frameCount, AudioBufferList *outputData)>
    RTCAudioDeviceGetPlayoutDataBlock;

typedef std::function<OSStatus(AudioUnitRenderActionFlags *actionFlags,
                               const AudioTimeStamp *timestamp, int inputBusNumber,
                               UInt32 frameCount, AudioBufferList *inputData, void *renderContext)>
    RTCAudioDeviceRenderRecordedDataBlock;

typedef std::function<OSStatus(
    AudioUnitRenderActionFlags *actionFlags, const AudioTimeStamp *timestamp, int inputBusNumber,
    UInt32 frameCount, const AudioBufferList *inputData, void *renderContext,
    RTCAudioDeviceRenderRecordedDataBlock renderBlock)>
    RTCAudioDeviceDeliverRecordedDataBlock;
#endif // Q_OS_MAC

/**
 * Delegate object provided by native ADM during RTCAudioDevice initialization.
 * Provides methods to poll playback audio samples from native ADM and to feed
 * recorded audio samples into native ADM.
 */
class RTCAudioDeviceDelegate
{
  public:
    virtual ~RTCAudioDeviceDelegate() = default;

#ifdef Q_OS_MAC
    /**
     * Implementation of RTCAudioSource should call this method to feed recorded PCM (16-bit integer)
     * into native ADM. Stereo data is expected to be interleaved starting with the left channel.
     * Either `inputData` with pre-filled audio data must be provided during method
     * call or `renderBlock` must be provided which must fill provided audio buffer with recorded
     * samples.
     *
     * NOTE: Implementation of RTCAudioDevice is expected to call the method on the same thread until
     * `notifyAudioInterrupted` is called. When `notifyAudioInterrupted` is called implementation
     * can call the method on a different thread.
     */
    virtual RTCAudioDeviceDeliverRecordedDataBlock deliverRecordedData() = 0;

    /**
     * Implementation of RTCAudioDevice should call this method to request PCM (16-bit integer)
     * from native ADM to play. Stereo data is interleaved starting with the left channel.
     *
     * NOTE: Implementation of RTCAudioDevice is expected to invoke of this method on the
     * same thread until `notifyAudioInterrupted` is called. When `notifyAudioInterrupted` is called
     * implementation can call the method from a different thread.
     */
    virtual RTCAudioDeviceGetPlayoutDataBlock getPlayoutData() = 0;
#endif // Q_OS_MAC

    /**
     * Provides input sample rate preference as it preferred by native ADM.
     */
    virtual double preferredInputSampleRate() const = 0;

    /**
     * Provides input IO buffer duration preference as it preferred by native ADM.
     */
    virtual double preferredInputIOBufferDuration() const = 0;

    /**
     * Provides output sample rate preference as it preferred by native ADM.
     */
    virtual double preferredOutputSampleRate() const = 0;

    /**
     * Provides output IO buffer duration preference as it preferred by native ADM.
     */
    virtual double preferredOutputIOBufferDuration() const = 0;

    /**
     * Notifies native ADM that some of the audio input parameters of RTCAudioDevice like
     * sample rate and/or IO buffer duration and/or IO latency had possibly changed.
     * Native ADM will adjust its audio input buffer to match current parameters of audio device.
     *
     * NOTE: Must be called within block executed via `QMetaObject::invokeMethod` with Qt::QueuedConnection or Qt::DirectConnection.
     */
    virtual void notifyAudioInputParametersChange() = 0;

    /**
     * Notifies native ADM that some of the audio output parameters of RTCAudioDevice like
     * sample rate and/or IO buffer duration and/or IO latency had possibly changed.
     * Native ADM will adjust its audio output buffer to match current parameters of audio device.
     *
     * NOTE: Must be called within block executed via `QMetaObject::invokeMethod` with Qt::QueuedConnection or Qt::DirectConnection.
     */
    virtual void notifyAudioOutputParametersChange() = 0;

    /**
     * Notifies native ADM that audio input is interrupted and further audio playout
     * and recording might happen on a different thread.
     *
     * NOTE: Must be called within block executed via `QMetaObject::invokeMethod` with Qt::QueuedConnection or Qt::DirectConnection.
     */
    virtual void notifyAudioInputInterrupted() = 0;
    /**
     * Notifies native ADM that audio output is interrupted and further audio playout
     * and recording might happen on a different thread.
     *
     * NOTE: Must be called within block executed via `QMetaObject::invokeMethod` with Qt::QueuedConnection or Qt::DirectConnection.
     */
    virtual void notifyAudioOutputInterrupted() = 0;

    /**
     * Asynchronously execute block of code within the context of
     * thread which owns native ADM.
     *
     * NOTE: Intended to be used to invoke `notifyAudioInputParametersChange`,
     * `notifyAudioOutputParametersChange`, `notifyAudioInputInterrupted`,
     * `notifyAudioOutputInterrupted` on native ADM thread.
     * Also could be used by `RTCAudioDevice` implementation to tie
     * mutations of underlying audio objects (QAudioEngine, AudioUnit, etc)
     * to the native ADM thread. Could be useful to handle events like audio route change, which
     * could lead to audio parameters change.
     */
    virtual void dispatchAsync(std::function<void()> block) = 0;

    /**
     * Synchronously execute block of code within the context of
     * thread which owns native ADM. Allows reentrancy.
     *
     * NOTE: Intended to be used to invoke `notifyAudioInputParametersChange`,
     * `notifyAudioOutputParametersChange`, `notifyAudioInputInterrupted`,
     * `notifyAudioOutputInterrupted` on native ADM thread and make sure
     * aforementioned is completed before `dispatchSync` returns. Could be useful
     * when implementation of `RTCAudioDevice` tie mutation to underlying audio objects (QAudioEngine,
     * AudioUnit, etc) to own thread to satisfy requirement that native ADM audio parameters
     * must be kept in sync with current audio parameters before audio is actually played or recorded.
     */
    virtual void dispatchSync(std::function<void()> block) = 0;
};

/**
 * Abstract class to abstract platform specific ways to implement playback and recording.
 *
 * NOTE: All the members of this class are called by native ADM from the same thread
 * between calls to `initializeWithDelegate` and `terminate`.
 * NOTE: Implementation is fully responsible for configuring application's QAudioSession.
 * An example implementation of RTCAudioDevice: https://github.com/mstyura/RTCAudioDevice
 * TODO(yura.yaroshevich): Implement custom RTCAudioDevice for AppRTCMobile demo app.
 */
class RTCAudioDevice
{
  public:
    /**
     * Indicates current sample rate of audio recording. Changes to this property
     * must be notified back to native ADM via `RTCAudioDeviceDelegate::notifyAudioParametersChange`.
     */
    virtual double deviceInputSampleRate() const = 0;

    /**
     * Indicates current size of record buffer. Changes to this property
     * must be notified back to native ADM via `RTCAudioDeviceDelegate::notifyAudioParametersChange`.
     */
    virtual double inputIOBufferDuration() const = 0;

    /**
     * Indicates current number of recorded audio channels. Changes to this property
     * must be notified back to native ADM via `RTCAudioDeviceDelegate::notifyAudioParametersChange`.
     */
    virtual int inputNumberOfChannels() const = 0;

    /**
     * Indicates current input latency
     */
    virtual double inputLatency() const = 0;

    /**
     * Indicates current sample rate of audio playback. Changes to this property
     * must be notified back to native ADM via `RTCAudioDeviceDelegate::notifyAudioParametersChange`.
     */
    virtual double deviceOutputSampleRate() const = 0;

    /**
     * Indicates current size of playback buffer. Changes to this property
     * must be notified back to native ADM via `RTCAudioDeviceDelegate::notifyAudioParametersChange`.
     */
    virtual double outputIOBufferDuration() const = 0;

    /**
     * Indicates current number of playback audio channels. Changes to this property
     * must be notified back to WebRTC via `RTCAudioDeviceDelegate::notifyAudioParametersChange`.
     */
    virtual int outputNumberOfChannels() const = 0;

    /**
     * Indicates current output latency
     */
    virtual double outputLatency() const = 0;

    /**
     * Indicates if invocation of `initializeWithDelegate` required before usage of RTCAudioDevice.
     * true indicates that `initializeWithDelegate` was called earlier without subsequent call to
     * `terminate`. false indicates that either `initializeWithDelegate` not called or `terminate` called.
     */
    virtual bool isInitialized() const = 0;

    /**
     * Initializes RTCAudioDevice with RTCAudioDeviceDelegate.
     * Implementation must return true if RTCAudioDevice initialized successfully and false otherwise.
     */
    virtual bool initializeWithDelegate(std::shared_ptr<RTCAudioDeviceDelegate> delegate) = 0;

    /**
     * De-initializes RTCAudioDevice. Implementation should forget about `delegate` provided in
     * `initializeWithDelegate`.
     */
    virtual bool terminateDevice() = 0;

    /**
     * Property to indicate if `initializePlayout` call required before invocation of `startPlayout`.
     * true indicates that `initializePlayout` was successfully invoked earlier or not necessary,
     * false indicates that `initializePlayout` invocation required.
     */
    virtual bool isPlayoutInitialized() const = 0;

    /**
     * Prepares RTCAudioDevice to play audio.
     * Called by native ADM before invocation of `startPlayout`.
     * Implementation is expected to return true in case of successful playout initialization and false
     * otherwise.
     */
    virtual bool initializePlayout() = 0;

    /**
     * Property to indicate if RTCAudioDevice should be playing according to
     * earlier calls of `startPlayout` and `stopPlayout`.
     */
    virtual bool isPlaying() const = 0;

    /**
     * Method is called when native ADM wants to play audio.
     * Implementation is expected to return true if playback start request
     * successfully handled and false otherwise.
     */
    virtual bool startPlayout() = 0;

    /**
     * Method is called when native ADM no longer needs to play audio.
     * Implementation is expected to return true if playback stop request
     * successfully handled and false otherwise.
     */
    virtual bool stopPlayout() = 0;

    /**
     * Property to indicate if `initializeRecording` call required before usage of `startRecording`.
     * true indicates that `initializeRecording` was successfully invoked earlier or not necessary,
     * false indicates that `initializeRecording` invocation required.
     */
    virtual bool isRecordingInitialized() const = 0;

    /**
     * Prepares RTCAudioDevice to record audio.
     * Called by native ADM before invocation of `startRecording`.
     * Implementation may use this method to prepare resources required to record audio.
     * Implementation is expected to return true in case of successful record initialization and false
     * otherwise.
     */
    virtual bool initializeRecording() = 0;

    /**
     * Property to indicate if RTCAudioDevice should record audio according to
     * earlier calls to `startRecording` and `stopRecording`.
     */
    virtual bool isRecording() const = 0;

    /**
     * Method is called when native ADM wants to record audio.
     * Implementation is expected to return true if recording start request
     * successfully handled and false otherwise.
     */
    virtual bool startRecording() = 0;

    /**
     * Method is called when native ADM no longer needs to record audio.
     * Implementation is expected to return true if recording stop request
     * successfully handled and false otherwise.
     */
    virtual bool stopRecording() = 0;
};

#endif // RTCAUDIODEVICE_H
