/*
 *  Copyright (c) 2022 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#ifndef SDK_OBJC_NATIVE_SRC_OBJC_AUDIO_DEVICE_DELEGATE_H_
#define SDK_OBJC_NATIVE_SRC_OBJC_AUDIO_DEVICE_DELEGATE_H_

#include "api/scoped_refptr.h"
#include "rtc_base/thread.h"

#include "rtcaudiodevice.h"

namespace webrtc {
namespace objc_adm {
class ObjCAudioDeviceModule;
}  // namespace objc_adm
}  // namespace webrtc

class AudioDeviceDelegateImpl;
class ObjCAudioDeviceDelegate : public RTCAudioDeviceDelegate {
 public:
  ObjCAudioDeviceDelegate(
      rtc::scoped_refptr<webrtc::objc_adm::ObjCAudioDeviceModule> audioDeviceModule,
      rtc::Thread* thread);
  ~ObjCAudioDeviceDelegate() override;

  void resetAudioDeviceModule();

  /**
   * Implementation of RTCAudioSource should call this method to feed recorded PCM (16-bit integer)
   * into native ADM. Stereo data is expected to be interleaved starting with the left channel.
   * Either `inputData` with pre-filled audio data must be provided during method
   * call or `renderBlock` must be provided which must fill provided audio buffer with recorded
   * samples.
   *    * NOTE: Implementation of RTCAudioDevice is expected to call the method on the same thread
   * until `notifyAudioInterrupted` is called. When `notifyAudioInterrupted` is called
   * implementation can call the method on a different thread.
   */
  RTCAudioDeviceDeliverRecordedDataBlock deliverRecordedData() override;

  /**
   * Provides input sample rate preference as it preferred by native ADM.
   */
  double preferredInputSampleRate() const override;

  /**
   * Provides input IO buffer duration preference as it preferred by native ADM.
   */
  double preferredInputIOBufferDuration() const override;

  /**
   * Provides output sample rate preference as it preferred by native ADM.
   */
  double preferredOutputSampleRate() const override;

  /**
   * Provides output IO buffer duration preference as it preferred by native ADM.
   */
  double preferredOutputIOBufferDuration() const override;

  /**
   * Implementation of RTCAudioDevice should call this method to request PCM (16-bit integer)
   * from native ADM to play. Stereo data is interleaved starting with the left channel.
   *    * NOTE: Implementation of RTCAudioDevice is expected to invoke of this method on the
   * same thread until `notifyAudioInterrupted` is called. When `notifyAudioInterrupted` is called
   * implementation can call the method from a different thread.
   */
  RTCAudioDeviceGetPlayoutDataBlock getPlayoutData() override;

 private:
  rtc::scoped_refptr<webrtc::objc_adm::ObjCAudioDeviceModule> audio_device_module_;
  rtc::Thread* audio_device_thread_;
  rtc::scoped_refptr<AudioDeviceDelegateImpl> impl_;

  void notifyAudioInputParametersChange() override;
  void notifyAudioOutputParametersChange() override;
  void notifyAudioInputInterrupted() override;
  void notifyAudioOutputInterrupted() override;
  void dispatchAsync(std::function<void()> block) override;
  void dispatchSync(std::function<void()> block) override;

  double preferredInputSampleRate_;
  double preferredInputIOBufferDuration_;
  double preferredOutputSampleRate_;
  double preferredOutputIOBufferDuration_;

  RTCAudioDeviceDeliverRecordedDataBlock deliverRecordedDataBlock_;
  RTCAudioDeviceGetPlayoutDataBlock getPlayoutDataBlock_;
};

#endif  // SDK_OBJC_NATIVE_SRC_OBJC_AUDIO_DEVICE_DELEGATE_H_
