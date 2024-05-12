#include "cvideoframebuffer.h"

#include "rtcnativei420buffer_p.h"
#include "rtcvideoframebuffer.h"

#include "api/make_ref_counted.h"

class RTCI420Buffer;

namespace webrtc
{

namespace
{

/** CVideoFrameBuffer that conforms to I420BufferInterface by wrapping RTC_C_TYPE(RTCI420Buffer) */
class CI420FrameBuffer : public I420BufferInterface
{
  public:
    explicit CI420FrameBuffer(RTCI420Buffer *frame_buffer)
        : frame_buffer_(frame_buffer), width_(frame_buffer->width()),
          height_(frame_buffer->height())
    {
    }
    ~CI420FrameBuffer() override
    {
    }

    int width() const override
    {
        return width_;
    }

    int height() const override
    {
        return height_;
    }

    const uint8_t *DataY() const override
    {
        return frame_buffer_->dataY();
    }

    const uint8_t *DataU() const override
    {
        return frame_buffer_->dataU();
    }

    const uint8_t *DataV() const override
    {
        return frame_buffer_->dataV();
    }

    int StrideY() const override
    {
        return frame_buffer_->strideY();
    }

    int StrideU() const override
    {
        return frame_buffer_->strideU();
    }

    int StrideV() const override
    {
        return frame_buffer_->strideV();
    }

  private:
    std::shared_ptr<RTCI420Buffer> frame_buffer_;
    int width_;
    int height_;
};

} // namespace

CVideoFrameBuffer::CVideoFrameBuffer(IRTCVideoFrameBuffer *frame_buffer)
    : frame_buffer_(frame_buffer), width_(frame_buffer->width()), height_(frame_buffer->height())
{
}

CVideoFrameBuffer::~CVideoFrameBuffer()
{
}

VideoFrameBuffer::Type CVideoFrameBuffer::type() const
{
    return Type::kNative;
}

int CVideoFrameBuffer::width() const
{
    return width_;
}

int CVideoFrameBuffer::height() const
{
    return height_;
}

rtc::scoped_refptr<I420BufferInterface> CVideoFrameBuffer::ToI420()
{
    return rtc::make_ref_counted<CI420FrameBuffer>(frame_buffer_->toI420());
}

rtc::scoped_refptr<VideoFrameBuffer> CVideoFrameBuffer::CropAndScale(int offset_x, int offset_y,
                                                                     int crop_width,
                                                                     int crop_height,
                                                                     int scaled_width,
                                                                     int scaled_height)
{
    if (frame_buffer_->cropAndScaleWith(offset_x, offset_y, crop_width, crop_height, scaled_width,
                                        scaled_height) != nullptr)
    {
        return rtc::make_ref_counted<CVideoFrameBuffer>(frame_buffer_->cropAndScaleWith(
            offset_x, offset_y, crop_width, crop_height, scaled_width, scaled_height));
    }

    // Use the default implementation.
    return webrtc::VideoFrameBuffer::CropAndScale(offset_x, offset_y, crop_width, crop_height,
                                                  scaled_width, scaled_height);
}

std::shared_ptr<IRTCVideoFrameBuffer> CVideoFrameBuffer::wrapped_frame_buffer() const
{
    return frame_buffer_;
}

std::shared_ptr<IRTCVideoFrameBuffer> toCVideoFrameBuffer(
    const rtc::scoped_refptr<webrtc::VideoFrameBuffer> &buffer)
{
    if (buffer->type() == webrtc::VideoFrameBuffer::Type::kNative)
    {
        return static_cast<CVideoFrameBuffer *>(buffer.get())->wrapped_frame_buffer();
    }
    else
    {
        auto privateBuffer = new RTCI420BufferPrivate(buffer->ToI420());
        return std::make_shared<RTCI420Buffer>(*privateBuffer);
    }
}

} // namespace webrtc
