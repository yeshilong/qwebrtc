#ifndef RTCMEDIACONSTRAINTS_H
#define RTCMEDIACONSTRAINTS_H

#include <QObject>
#include <QMap>
#include <QString>

class RTCMediaConstraintsPrivate;
/**
 * @brief The RTCMediaConstraints class.
 */
class RTCMediaConstraints : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Initializes an RTCMediaConstraints instance with the specified mandatory and optional constraints.
     * @param mandatory The mandatory constraints.
     * @param optional The optional constraints.
     */
    explicit RTCMediaConstraints(QMap<QString, QString> mandatory, QMap<QString, QString> optional,
                                 QObject *parent = nullptr);

    /**
     * @brief Constraint keys for media sources.
     * The value for this key should be a base64 encoded string containing
     * the data from the serialized configuration proto.
     */
    static QString RTCMediaConstraintsAudioNetworkAdaptorConfig();

    /**
     * @brief Constraint keys for generating offers and answers.
     */
    static QString RTCMediaConstraintsIceRestart();
    static QString RTCMediaConstraintsOfferToReceiveAudio();
    static QString RTCMediaConstraintsOfferToReceiveVideo();
    static QString RTCMediaConstraintsVoiceActivityDetection();

    /**
     * @brief Constraint values for Boolean parameters.
     */
    static QString RTCMediaConstraintsValueTrue();
    static QString RTCMediaConstraintsValueFalse();

  private:
    Q_DECLARE_PRIVATE(RTCMediaConstraints)
    RTCMediaConstraintsPrivate *d_ptr;
};

#endif // RTCMEDIACONSTRAINTS_H
