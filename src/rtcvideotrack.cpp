#include "rtcvideotrack_p.h"

#include "rtcpeerconnectionfactory_p.h"

RTCVideoTrackPrivate::RTCVideoTrackPrivate(RTCPeerConnectionFactory *factory,
                                           RTCVideoSource *source, QString trackId)
    : RTCMediaStreamTrackPrivate(
          factory,
          factory->d_ptr->nativePeerConnectionFactory()->CreateVideoTrack(
              ((RTCVideoSourcePrivate *)(source->d_ptr))->nativeVideoSource(),
              trackId.toStdString()),
          RTCMediaStreamTrackType::RTCMediaStreamTrackTypeVideo)
{
    Q_ASSERT(factory);
    Q_ASSERT(source);
    Q_ASSERT(!trackId.isEmpty());
    source_ = source;
}

RTCVideoTrackPrivate::RTCVideoTrackPrivate(
    RTCPeerConnectionFactory *factory,
    const rtc::scoped_refptr<webrtc::MediaStreamTrackInterface> nativeVideoTrack,
    RTCMediaStreamTrackType type)
    : RTCMediaStreamTrackPrivate{factory, nativeVideoTrack, type}
{
    Q_ASSERT(factory);
    Q_ASSERT(nativeVideoTrack);
    Q_ASSERT(type == RTCMediaStreamTrackType::RTCMediaStreamTrackTypeVideo);
    adapters_ = QVector<RTCVideoRendererAdapter *>{};
    workerThread_ = factory->d_ptr->workerThread();
}

rtc::scoped_refptr<webrtc::VideoTrackInterface> RTCVideoTrackPrivate::nativeVideoTrack() const
{
    return rtc::scoped_refptr<webrtc::VideoTrackInterface>(
        static_cast<webrtc::VideoTrackInterface *>(this->nativeMediaStreamTrack().get()));
}

RTCVideoTrack::RTCVideoTrack(RTCVideoTrackPrivate &d, QObject *parent)
    : RTCMediaStreamTrack{d, parent}
{
}

RTCVideoTrack::~RTCVideoTrack()
{
    Q_D(RTCMediaStreamTrack);
    RTCVideoTrackPrivate *q = static_cast<RTCVideoTrackPrivate *>(d);
    for (RTCVideoRendererAdapter *adapter : q->adapters_)
    {
        q->nativeVideoTrack()->RemoveSink(adapter->d_ptr->nativeVideoRenderer());
    }
}

RTCVideoSource *RTCVideoTrack::source()
{
    Q_D(RTCMediaStreamTrack);
    RTCVideoTrackPrivate *q = static_cast<RTCVideoTrackPrivate *>(d);
    if (!q->source_)
    {
        rtc::scoped_refptr<webrtc::VideoTrackSourceInterface> source(
            q->nativeVideoTrack()->GetSource());
        if (source)
        {
            q->source_ = new RTCVideoSource(*(new RTCVideoSourcePrivate(q->factory_, source)));
        }
    }
    return q->source_;
}

bool RTCVideoTrack::shouldReceive() const
{
    Q_D(const RTCMediaStreamTrack);
    const RTCVideoTrackPrivate *q = static_cast<const RTCVideoTrackPrivate *>(d);
    return q->nativeVideoTrack()->should_receive();
}

void RTCVideoTrack::setShouldReceive(bool shouldReceive)
{
    Q_D(RTCMediaStreamTrack);
    RTCVideoTrackPrivate *q = static_cast<RTCVideoTrackPrivate *>(d);
    q->nativeVideoTrack()->set_should_receive(shouldReceive);
}

void RTCVideoTrack::addRenderer(IRTCVideoRenderer *renderer)
{
    Q_D(RTCMediaStreamTrack);
    RTCVideoTrackPrivate *q = static_cast<RTCVideoTrackPrivate *>(d);

    if (!q->workerThread_->IsCurrent())
    {
        q->workerThread_->BlockingCall([renderer, this] { addRenderer(renderer); });
        return;
    }

    // Make sure we don't have this renderer yet.
    for (auto adapter : q->adapters_)
    {
        if (adapter->videoRenderer() == renderer)
        {
            RTC_LOG(LS_INFO) << "|renderer| is already attached to this track";
            return;
        }
    }
    // Create a wrapper that provides a native pointer for us.
    auto adapter = std::make_unique<RTCVideoRendererAdapter>(renderer);
    q->adapters_.push_back(adapter.get());
    q->nativeVideoTrack()->AddOrUpdateSink(adapter->d_ptr->nativeVideoRenderer(),
                                           rtc::VideoSinkWants());
}

void RTCVideoTrack::removeRenderer(IRTCVideoRenderer *renderer)
{
    Q_D(RTCMediaStreamTrack);
    RTCVideoTrackPrivate *q = static_cast<RTCVideoTrackPrivate *>(d);

    if (!q->workerThread_->IsCurrent())
    {
        q->workerThread_->BlockingCall([renderer, this] { this->removeRenderer(renderer); });
        return;
    }
    int indexToRemove = -1;
    for (int i = 0; i < q->adapters_.size(); i++)
    {
        if (q->adapters_[i]->videoRenderer() == renderer)
        {
            indexToRemove = i;
            break;
        }
    }
    if (indexToRemove == -1)
    {
        RTC_LOG(LS_INFO)
            << "removeRenderer called with a renderer that has not been previously added";
        return;
    }
    RTCVideoRendererAdapter *adapterToRemove = q->adapters_[indexToRemove];
    q->nativeVideoTrack()->RemoveSink(adapterToRemove->d_ptr->nativeVideoRenderer());
    q->adapters_.erase(q->adapters_.begin() + indexToRemove);
}
