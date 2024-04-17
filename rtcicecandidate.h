#ifndef RTCICECANDIDATE_H
#define RTCICECANDIDATE_H

#include <QObject>
#include <QString>

class RTCIceCandidatePrivate;

/**
 * @brief The RTCIceCandidate class.
 */
class RTCIceCandidate : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes an RTCIceCandidate from the provided SDP string, media line index, and optional SDP Mid.
     * @param sdp The SDP string representation of the candidate.
     * @param sdpMLineIndex The zero-based index of the associated media description in the SDP.
     * @param sdpMid The optional media stream identifier (SDP Mid) associated with the candidate.
     */
    RTCIceCandidate(const QString &sdp, int sdpMLineIndex, const QString &sdpMid,
                    QObject *parent = nullptr);

    /**
     * @brief Gets the identifier of the "media stream identification" for the media component this candidate is associated with.
     * @return The identifier of the "media stream identification".
     */
    QString sdpMid() const;

    /**
     * @brief Gets the index (starting at zero) of the media description this candidate is associated with in the SDP.
     * @return The index of the media description.
     */
    int sdpMLineIndex() const;

    /**
     * @brief Gets the SDP string for this candidate.
     * @return The SDP string.
     */
    QString sdp() const;

    /**
     * @brief Gets the URL of the ICE server which this candidate is gathered from.
     * @return The URL of the ICE server.
     */
    QString serverUrl() const;

  private:
    Q_DECLARE_PRIVATE(RTCIceCandidate)
    RTCIceCandidatePrivate* const d_ptr;
};

#endif // RTCICECANDIDATE_H
