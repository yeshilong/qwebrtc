/*
 * Copyright (C) 2024 Deltarion Systems
 *
 * This software is licensed under the terms of the GNU Lesser
 * General Public License (LGPL) version 3 as published by the Free
 * Software Foundation. This license is available at:
 * https://www.gnu.org/licenses/lgpl-3.0.html
 *
 * You are free to modify and distribute this software under the
 * terms of the LGPLv3 license. You are required to make the source
 * code of any modifications available under the same license.
 */
#ifndef RTCVIDEORENDERERADAPTER_H
#define RTCVIDEORENDERERADAPTER_H

#include "rtcvideorenderer.h"

#include <QObject>

class RTCVideoRendererAdapterPrivate;
/**
 * @class RTCVideoRendererAdapter
 * @brief This class is an adapter that adapts calls made to the rtc::VideoSinkInterface to the IRTCVideoRenderer supplied during construction.
 */
class RTCVideoRendererAdapter : public QObject
{
    Q_OBJECT

  public:
    /**
   * @brief Construct a new RTCVideoRendererAdapter object
   * 
   * @param videoRenderer The IRTCVideoRenderer object that calls made to the rtc::VideoSinkInterface will be adapted and passed to.
   * @param parent The parent QObject.
   */
    explicit RTCVideoRendererAdapter(IRTCVideoRenderer *videoRenderer, QObject *parent = nullptr);

    /**
     * @brief Construct a new RTCVideoRendererAdapter object
     * @param d The private implementation.
     * @param parent The parent QObject.
     */
    RTCVideoRendererAdapter(RTCVideoRendererAdapterPrivate &d, QObject *parent = nullptr);

    /**
   * @brief Get the IRTCVideoRenderer object
   * 
   * @return IRTCVideoRenderer* The IRTCVideoRenderer object that calls made to the rtc::VideoSinkInterface will be adapted and passed to.
   */
    IRTCVideoRenderer *videoRenderer() const;

  private:
    RTCVideoRendererAdapterPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCVideoRendererAdapter)

    friend class RTCVideoTrack;
};

#endif // RTCVIDEORENDERERADAPTER_H
