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
#include "rtcvideorendereradapter_p.h"
#include "rtcvideoframe.h"

RTCVideoRendererAdapter::RTCVideoRendererAdapter(IRTCVideoRenderer *videoRenderer, QObject *parent)
    : QObject(parent)
{
    d_ptr = new RTCVideoRendererAdapterPrivate(videoRenderer);
    d_ptr->q_ptr = this;
}
