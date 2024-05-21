/*
 *  Copyright 2022 The WebRTC project authors. All Rights Reserved.
 *
 *  Use of this source code is governed by a BSD-style license
 *  that can be found in the LICENSE file in the root of the source
 *  tree. An additional intellectual property rights grant can be found
 *  in the file PATENTS.  All contributing project authors may
 *  be found in the AUTHORS file in the root of the source tree.
 */

#include "objc_audio_device_module.h"

#include "rtc_base/logging.h"
#include "api/make_ref_counted.h"
#include "api/task_queue/default_task_queue_factory.h"

#if defined(WEBRTC_IOS)
#include "darwin/objc_audio_device.h"
#endif

namespace webrtc {

rtc::scoped_refptr<AudioDeviceModule> CreateAudioDeviceModule(
    std::shared_ptr<RTCAudioDevice> audio_device) {
  RTC_DLOG(LS_INFO) << __FUNCTION__;
#if defined(WEBRTC_IOS)
  return rtc::make_ref_counted<objc_adm::ObjCAudioDeviceModule>(audio_device);
#endif
}

rtc::scoped_refptr<webrtc::AudioDeviceModule> CreateAudioDeviceModule(
    webrtc::TaskQueueFactory* factory) {
  const auto create = [&](webrtc::AudioDeviceModule::AudioLayer layer) {
    return webrtc::AudioDeviceModule::Create(layer, factory);
  };
  const auto check = [&](const rtc::scoped_refptr<webrtc::AudioDeviceModule>& result) {
    return (result && (result->Init() == 0)) ? result : nullptr;
  };
  if (auto result = check(create(webrtc::AudioDeviceModule::kPlatformDefaultAudio))) {
    return result;
  }
  return nullptr;
}

rtc::scoped_refptr<webrtc::AudioDeviceModule> CreateAudioDeviceModule() {
  return CreateAudioDeviceModule(CreateDefaultTaskQueueFactory().get());
}

}  // namespace webrtc
