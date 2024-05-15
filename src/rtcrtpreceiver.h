#ifndef RTCRTPRECEIVER_H
#define RTCRTPRECEIVER_H

#include <QString>

#include "rtcmediastreamtrack.h"
#include "rtcrtpparameters.h"

class RTCRtpReceiverPrivate;
// /**
//  * @brief The RTCRtpReceiver interface.
//  */
// class IRTCRtpReceiver
// {
//   public:
//     /**
//      * @brief Gets the receiver ID.
//      * @return The receiver ID.
//      */
//     virtual QString receiverId() const = 0;

//     /**
//      * @brief Gets the RTP parameters.
//      * @return The RTP parameters.
//      */
//     virtual RTCRtpParameters *parameters() const = 0;

//     /**
//      * @brief Gets the media stream track.
//      * @return The media stream track.
//      */
//     virtual RTCMediaStreamTrack *track() const = 0;

//   Q_SIGNALS:
//     /**
//      * @brief This signal is emitted when the first packet is received for a media type.
//      * @param mediaType The media type.
//      */
//     void didReceiveFirstPacketForMediaType(RTCRtpMediaType mediaType);
// };

/**
 * @brief The RTCRtpReceiver class.
 */
class RTCRtpReceiver : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs an RTCRtpReceiver object.
     */
    explicit RTCRtpReceiver(QObject *parent = nullptr);

    /**
     * @brief Constructs an RTCRtpReceiver object.
     * @param d The private implementation.
     * @param parent The parent object.
     */
    RTCRtpReceiver(RTCRtpReceiverPrivate &d, QObject *parent = nullptr);

    /**
     * @brief Gets the receiver ID.
     * @return The receiver ID.
     */
    QString receiverId() const;

    /**
     * @brief Gets the RTP parameters.
     * @return The RTP parameters.
     */
    RTCRtpParameters *parameters() const;

    /**
     * @brief Gets the media stream track.
     * @return The media stream track.
     */
    RTCMediaStreamTrack *track() const;

  Q_SIGNALS:
    /**
     * @brief This signal is emitted when the first packet is received for a media type.
     * @param mediaType The media type.
     */
    void rtpReceiverDidReceiveFirstPacketForMediaType(RTCRtpMediaType mediaType);

  private:
    friend class RTCRtpTransceiverPrivate;

    RTCRtpReceiverPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCRtpReceiver)
};

#endif // RTCRTPRECEIVER_H
