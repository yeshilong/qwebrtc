cmake_minimum_required(VERSION 3.14)

add_library(qwebrtc SHARED
  qwebrtcglobal.h
  qwebrtc.cpp
  qwebrtc.h
  media_constraints.h media_constraints.cc
  rtctypes.h
  rtcerror.h rtcerror.cpp
  rtccertificate.h rtccertificate.cpp
  rtccryptooptions.h rtccryptooptions.cpp
  rtciceserver.h rtciceserver.cpp
  rtcicecandidate.h rtcicecandidate.cpp
  rtcicecandidateerrorevent.h rtcicecandidateerrorevent.cpp
  rtcaudiobuffer.h rtcaudiobuffer.cpp
  rtcdatabuffer.h rtcdatabuffer.cpp
  rtcdatachannel.h rtcdatachannel.cpp
  rtcdatachannelconfiguration.h rtcdatachannelconfiguration.cpp
  rtcdesktopsource.h rtcdesktopsource.cpp
  rtcdtmfsender.h rtcdtmfsender.cpp
  rtcframecryptor.h rtcframecryptor.cpp
  rtcframecryptorkeyprovider.h rtcframecryptorkeyprovider.cpp
  rtcmediaconstraints.h rtcmediaconstraints.cpp
  rtcmetricssampleinfo.h rtcmetricssampleinfo.cpp
  rtcmetrics.h rtcmetrics.cpp
  rtcpeerconnectionfactoryoptions.h rtcpeerconnectionfactoryoptions.cpp
  rtcconfiguration.h rtcconfiguration.cpp
  rtciodevice.h rtciodevice.cpp
  rtcaudiodevicemodule.h rtcaudiodevicemodule.cpp
  rtcaudioprocessingmodule.h
  rtcaudioprocessingconfig.h rtcaudioprocessingconfig.cpp
  rtcdefaultaudioprocessingmodule.h rtcdefaultaudioprocessingmodule.cpp
  rtcaudiocustomprocessingdelegate.h
  rtcaudiorenderer.h
  rtcaudiotrack.h rtcaudiotrack.cpp
  rtcmediastreamtrack.h rtcmediastreamtrack.cpp
  rtcmediasource.h rtcmediasource.cpp
  rtcaudiosource.h rtcaudiosource.cpp
  rtcvideotrack.h rtcvideotrack.cpp
  rtcvideocapturer.h rtcvideocapturer.cpp
  rtcvideosource.h rtcvideosource.cpp
  rtcvideorenderer.h
  rtcmediastream.h rtcmediastream.cpp
  rtcvideoframebuffer.h
  rtcyuvplanarbuffer.h
  rtci420buffer.h rtci420buffer.cpp
  rtcvideocodecinfo.h rtcvideocodecinfo.cpp
  rtcdesktopmedialist.h rtcdesktopmedialist.cpp
  rtcdesktopcapturer.h rtcdesktopcapturer.cpp
  rtcfilevideocapturer.h rtcfilevideocapturer.cpp
  rtcrtcpparameters.h rtcrtcpparameters.cpp
  rtcrtpcodeccapability.h rtcrtpcodeccapability.cpp
  rtcrtpcapabilities.h rtcrtpcapabilities.cpp
  rtcrtpcodecparameters.h rtcrtpcodecparameters.cpp
  rtcrtpencodingparameters.h rtcrtpencodingparameters.cpp
  rtcrtpheaderextension.h rtcrtpheaderextension.cpp
  rtcrtpparameters.h rtcrtpparameters.cpp
  rtcrtpreceiver.h rtcrtpreceiver.cpp
  rtcrtpsender.h rtcrtpsender.cpp
  rtcrtptransceiverinit.h rtcrtptransceiverinit.cpp
  rtcrtptransceiver.h rtcrtptransceiver.cpp
  rtcsessiondescription.h rtcsessiondescription.cpp
  rtcssladapter.h rtcssladapter.cpp
  rtcfieldtrials.h rtcfieldtrials.cpp
  rtcsslcertificateverifier.h
  rtcstatistics.h rtcstatistics.cpp
  rtcstatisticsreport.h rtcstatisticsreport.cpp
  rtctracing.h rtctracing.cpp
  rtcvideocodecconstants.h rtcvideocodecconstants.cpp
  rtcvideoframe.h rtcvideoframe.cpp
  rtcyuvhelper.h rtcyuvhelper.cpp
  rtcencodedimage.h rtcencodedimage.cpp
  rtcvideoencodersettings.h rtcvideoencodersettings.cpp
  rtcvideodecoder.h rtcvideodecoder.cpp
  rtccodecspecificinfo.h rtccodecspecificinfo.cpp
  rtccodecspecificinfoh264.h rtccodecspecificinfoh264.cpp
  rtccvpixelbuffer.h rtccvpixelbuffer.cpp
  rtcwrappednativevideodecoder.h rtcwrappednativevideodecoder.cpp
  rtcvideodecoderav1.h rtcvideodecoderav1.cpp
  rtcvideodecoderh264.h rtcvideodecoderh264.cpp
  rtcvideodecodervp8.h rtcvideodecodervp8.cpp
  rtcvideodecodervp9.h rtcvideodecodervp9.cpp
  rtcvideodecoderh264mf.h rtcvideodecoderh264mf.cpp
  rtcvideodecoderfactory.h rtcvideodecoderfactory.cpp
  rtcdefaultvideodecoderfactory.h rtcdefaultvideodecoderfactory.cpp
  rtcvideodecoderfactoryh264.h rtcvideodecoderfactoryh264.cpp
  rtcvideoencoderqpthresholds.h rtcvideoencoderqpthresholds.cpp
  rtcvideoencoder.h rtcvideoencoder.cpp
  rtcwrappednativevideoencoder.h rtcwrappednativevideoencoder.cpp
  rtcvideoencoderav1.h rtcvideoencoderav1.cpp
  rtcvideoencoderfactory.h rtcvideoencoderfactory.cpp
  rtcdefaultvideoencoderfactory.h rtcdefaultvideoencoderfactory.cpp
  rtcvideoencoderfactoryh264.h rtcvideoencoderfactoryh264.cpp
  rtcvideoencoderfactorysimulcast.h rtcvideoencoderfactorysimulcast.cpp
  rtcvideoencoderh264.h rtcvideoencoderh264.cpp
  rtcvideoencodersimulcast.h rtcvideoencodersimulcast.cpp
  rtcvideoencodervp8.h rtcvideoencodervp8.cpp
  rtcvideoencodervp9.h rtcvideoencodervp9.cpp
  rtcvideoencoderh264mf.h rtcvideoencoderh264mf.cpp
  rtclogging.h rtclogging.cpp
  rtcfilelogger.h rtcfilelogger.cpp
  rtclegacystatsreport.h rtclegacystatsreport.cpp
  rtcpeerconnectiondelegate.h
  rtcpeerconnectionfactory.h rtcpeerconnectionfactory.cpp
  rtcpeerconnection.h rtcpeerconnection.cpp
  rtcicecandidate_p.h
  rtciceserver_p.h
  rtcdtmfsender_p.h
  rtcmediasource_p.h
  rtcaudiosource_p.h
  rtcmediaconstraints_p.h
  rtcmediastreamtrack_p.h
  rtcaudiotrack_p.h
  rtcvideotrack_p.h
  rtccodecspecificinfoh264_p.h
  rtcdatabuffer_p.h
  rtcdatachannel_p.h
  rtcdatachannelconfiguration_p.h
  rtcmetricssampleinfo_p.h
  rtcrtcpparameters_p.h
  rtcframecryptorkeyprovider_p.h
  rtclegacystatsreport_p.h
)

find_path(WEBRTC_INCLUDE_DIR NAMES api/jsep.h
         HINTS ${PROJECT_SOURCE_DIR}/extern/libwebrtc/include)
list(APPEND WEBRTC_INCLUDE_DIR ${PROJECT_SOURCE_DIR}/extern/libwebrtc/include/third_party/libyuv/include)

if(X86_64)
    set(ARCH_STRING "x64")
elseif(X86)
    set(ARCH_STRING "x86")
elseif(AARCH64)
    set(ARCH_STRING "arm64")
endif()

find_library(WEBRTC_LIBRARY_DEBUG NAMES libwebrtc.a
             HINTS ${PROJECT_SOURCE_DIR}/extern/libwebrtc/lib/${ARCH_STRING}/debug
             PATHS ${CMAKE_SYSTEM_LIBRARY_DIRS})
find_library(WEBRTC_LIBRARY_RELEASE NAMES libwebrtc.a
          HINTS ${PROJECT_SOURCE_DIR}/extern/libwebrtc/lib/${ARCH_STRING}/release
          PATHS ${CMAKE_SYSTEM_LIBRARY_DIRS})

message(STATUS "WEBRTC_INCLUDE_DIR: ${WEBRTC_INCLUDE_DIR}")
message(STATUS "WEBRTC_LIBRARY_DEBUG: ${WEBRTC_LIBRARY_DEBUG}")
message(STATUS "WEBRTC_LIBRARY_RELEASE: ${WEBRTC_LIBRARY_RELEASE}")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  set(WEBRTC_LIBRARY ${WEBRTC_LIBRARY_DEBUG})
  add_definitions(-D__STDC_CONSTANT_MACROS)
  add_definitions(-D__STDC_FORMAT_MACROS)
  add_definitions(-DCR_XCODE_VERSION=1510)
  add_definitions(-D_DEBUG)
  add_definitions(-DDYNAMIC_ANNOTATIONS_ENABLED=1)
  add_definitions(-DWEBRTC_ENABLE_PROTOBUF=1)
  add_definitions(-DWEBRTC_STRICT_FIELD_TRIALS=0)
  add_definitions(-DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE)
  add_definitions(-DRTC_ENABLE_VP9)
  add_definitions(-DRTC_DAV1D_IN_INTERNAL_DECODER_FACTORY)
  add_definitions(-DWEBRTC_HAVE_SCTP)
  add_definitions(-DWEBRTC_ARCH_ARM64)
  add_definitions(-DWEBRTC_HAS_NEON)
  add_definitions(-DWEBRTC_LIBRARY_IMPL)
  add_definitions(-DWEBRTC_ENABLE_SYMBOL_EXPORT)
  add_definitions(-DWEBRTC_ENABLE_AVX2)
  add_definitions(-DWEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0)
  add_definitions(-DWEBRTC_POSIX)
  add_definitions(-DWEBRTC_MAC)
  add_definitions(-DABSL_ALLOCATOR_NOTHROW=1)
  add_definitions(-DGOOGLE_PROTOBUF_NO_RTTI)
  add_definitions(-DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER)
  add_definitions(-DGOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0)
  add_definitions(-DHAVE_PTHREAD)
else()
  set(WEBRTC_LIBRARY ${WEBRTC_LIBRARY_RELEASE})
  add_definitions(-D__STDC_CONSTANT_MACROS)
  add_definitions(-D__STDC_FORMAT_MACROS)
  add_definitions(-D_FORTIFY_SOURCE=2)  # Note the value after the equal sign
  add_definitions(-DCR_XCODE_VERSION=1510)
  add_definitions(-DNDEBUG)  # No value needed, indicates debug mode is off
  add_definitions(-DNVALGRIND)  # No value needed
  add_definitions(-DDYNAMIC_ANNOTATIONS_ENABLED=0)
  add_definitions(-DWEBRTC_ENABLE_PROTOBUF=1)
  add_definitions(-DWEBRTC_STRICT_FIELD_TRIALS=0)
  add_definitions(-DWEBRTC_INCLUDE_INTERNAL_AUDIO_DEVICE)
  add_definitions(-DRTC_ENABLE_VP9)
  add_definitions(-DRTC_DAV1D_IN_INTERNAL_DECODER_FACTORY)
  add_definitions(-DWEBRTC_HAVE_SCTP)
  add_definitions(-DWEBRTC_ARCH_ARM64)
  add_definitions(-DWEBRTC_HAS_NEON)
  add_definitions(-DWEBRTC_LIBRARY_IMPL)
  add_definitions(-DWEBRTC_ENABLE_SYMBOL_EXPORT)
  add_definitions(-DWEBRTC_ENABLE_AVX2)
  add_definitions(-DWEBRTC_NON_STATIC_TRACE_EVENT_HANDLERS=0)
  add_definitions(-DWEBRTC_POSIX)
  add_definitions(-DWEBRTC_MAC)
  add_definitions(-DABSL_ALLOCATOR_NOTHROW=1)
  add_definitions(-DGOOGLE_PROTOBUF_NO_RTTI)
  add_definitions(-DGOOGLE_PROTOBUF_NO_STATIC_INITIALIZER)
  add_definitions(-DGOOGLE_PROTOBUF_INTERNAL_DONATE_STEAL_INLINE=0)
  add_definitions(-DHAVE_PTHREAD)
endif()
add_definitions(-DQT_NO_SIGNALS_SLOTS_KEYWORDS)

if(WEBRTC_INCLUDE_DIR AND (WEBRTC_LIBRARY_DEBUG OR WEBRTC_LIBRARY_RELEASE))
  add_library(WebRTC STATIC IMPORTED)
  set_target_properties(WebRTC PROPERTIES
      IMPORTED_LOCATION "${WEBRTC_LIBRARY}"
      IMPORTED_LOCATION_DEBUG "${WEBRTC_LIBRARY_DEBUG}"
      IMPORTED_LOCATION_RELEASE "${WEBRTC_LIBRARY_RELEASE}"
      IMPORTED_INCLUDE_DIRECTORIES "${WEBRTC_INCLUDE_DIR}")
else()
  message(WARNING "WebRTC library not found. Communication features might be disabled.")
endif()


include_directories(${WEBRTC_INCLUDE_DIR})

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(qwebrtc PRIVATE QWEBRTC_LIBRARY QT_NO_KEYWORDS)
else()
  target_compile_definitions(qwebrtc PRIVATE QWEBRTC_LIBRARY QT_NO_KEYWORDS)
endif()
target_link_libraries(qwebrtc PRIVATE Qt${QT_VERSION_MAJOR}::Core Qt${QT_VERSION_MAJOR}::Gui Qt${QT_VERSION_MAJOR}::Multimedia WebRTC "-framework CoreFoundation")
