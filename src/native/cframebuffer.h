#ifndef CFRAMEBUFFER_H
#define CFRAMEBUFFER_H

#include "api/video/video_frame_buffer.h"

class IRTCVideoFrameBuffer;

namespace webrtc
{

class CFrameBuffer : public VideoFrameBuffer
{
  public:
    explicit CFrameBuffer(IRTCVideoFrameBuffer *frame_buffer);
    ~CFrameBuffer() override;

    Type type() const override;

    int width() const override;
    int height() const override;

    rtc::scoped_refptr<I420BufferInterface> ToI420() override;
    rtc::scoped_refptr<VideoFrameBuffer> CropAndScale(int offset_x, int offset_y, int crop_width,
                                                      int crop_height, int scaled_width,
                                                      int scaled_height) override;

    std::shared_ptr<IRTCVideoFrameBuffer> wrapped_frame_buffer() const;

  private:
    std::shared_ptr<IRTCVideoFrameBuffer> frame_buffer_;
    int width_;
    int height_;
};

std::shared_ptr<IRTCVideoFrameBuffer> toCVideoFrameBuffer(
    const rtc::scoped_refptr<VideoFrameBuffer> &buffer);

} // namespace webrtc

#endif // CFRAMEBUFFER_H
