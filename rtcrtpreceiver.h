#ifndef RTCRTPRECEIVER_H
#define RTCRTPRECEIVER_H

#include "rtcmediastreamtrack.h"
#include "rtcrtpparameters.h"
#include <QObject>
#include <QString>

class RTCRtpReceiver;

/**
 * @brief The RTCRtpReceiverDelegate interface.
 */
class IRTCRtpReceiverDelegate
{
  public:
    /**
     * @brief Called when the first RTP packet is received.
     * @param rtpReceiver The RTP receiver.
     * @param mediaType The media type.
     */
    virtual void rtpReceiverDidReceiveFirstPacketForMediaType(RTCRtpReceiver rtpReceiver,
                                                              RTCRtpMediaType mediaType) = 0;
};

/**
 * @brief The RTCRtpReceiver interface.
 */
class IRTCRtpReceiver
{
  public:
    /**
     * @brief Gets the receiver ID.
     * @return The receiver ID.
     */
    virtual QString receiverId() const = 0;

    /**
     * @brief Gets the RTP parameters.
     * @return The RTP parameters.
     */
    virtual RTCRtpParameters parameters() const = 0;

    /**
     * @brief Gets the media stream track.
     * @return The media stream track.
     */
    virtual RTCMediaStreamTrack track() const = 0;

    /**
     * @brief Gets the delegate.
     * @return The delegate.
     */
    virtual IRTCRtpReceiverDelegate *delegate() const = 0;

    /**
     * @brief Sets the delegate.
     * @param delegate The delegate.
     */
    virtual void setDelegate(IRTCRtpReceiverDelegate *delegate) = 0;
};

/**
 * @brief The RTCRtpReceiver class.
 */
class RTCRtpReceiver : public QObject, public IRTCRtpReceiver
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpReceiver object.
     */
    explicit RTCRtpReceiver(QObject *parent = nullptr);
};

#endif // RTCRTPRECEIVER_H
