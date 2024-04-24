#ifndef RTCFRAMECRYPTORKEYPROVIDER_H
#define RTCFRAMECRYPTORKEYPROVIDER_H

#include <QObject>
#include <QByteArray>

class RTCFrameCryptorKeyProviderPrivate;
/**
 * @brief The RTCFrameCryptorKeyProvider class provides keys for frame encryption/decryption.
 */
class RTCFrameCryptorKeyProvider : public QObject
{
    Q_OBJECT

  public:
    /**
     * @brief Constructs a RTCFrameCryptorKeyProvider object with the specified parameters.
     * @param salt The ratchet salt data.
     * @param windowSize The ratchet window size.
     * @param sharedKeyMode Indicates whether to use shared key mode.
     * @param uncryptedMagicBytes Optional unencrypted magic bytes.
     * @param parent The parent QObject.
     */
    explicit RTCFrameCryptorKeyProvider(QByteArray salt, int windowSize, bool sharedKeyMode,
                                        QByteArray uncryptedMagicBytes, QObject *parent = nullptr);

    /**
     * @brief Constructs a RTCFrameCryptorKeyProvider object with the specified parameters and failure tolerance.
     * @param salt The ratchet salt data.
     * @param windowSize The ratchet window size.
     * @param sharedKeyMode Indicates whether to use shared key mode.
     * @param uncryptedMagicBytes Optional unencrypted magic bytes.
     * @param failureTolerance The number of consecutive ratchet failures to tolerate.
     * @param keyRingSize The size of the key ring.
     * @param parent The parent QObject.
     */
    explicit RTCFrameCryptorKeyProvider(QByteArray salt, int windowSize, bool sharedKeyMode,
                                        QByteArray uncryptedMagicBytes, int failureTolerance,
                                        int keyRingSize, QObject *parent = nullptr);

    /**
     * @brief Constructs a RTCFrameCryptorKeyProvider object with the specified parameters and failure tolerance.
     * @param salt The ratchet salt data.
     * @param windowSize The ratchet window size.
     * @param sharedKeyMode Indicates whether to use shared key mode.
     * @param uncryptedMagicBytes Optional unencrypted magic bytes.
     * @param failureTolerance The number of consecutive ratchet failures to tolerate.
     * @param keyRingSize The size of the key ring.
     * @param discardFrameWhenCryptorNotReady Indicates whether to discard the frame when the cryptor is not ready.
     * @param parent The parent QObject.
     */
    explicit RTCFrameCryptorKeyProvider(QByteArray salt, int windowSize, bool sharedKeyMode,
                                        QByteArray uncryptedMagicBytes, int failureTolerance,
                                        int keyRingSize, bool discardFrameWhenCryptorNotReady,
                                        QObject *parent = nullptr);

    /**
     * @brief Sets the shared key with the specified index.
     * @param key The shared key data.
     * @param index The index of the key.
     */
    void setSharedKey(QByteArray key, int index);

    /**
     * @brief Gets the ratcheted shared key with the specified index.
     * @param index The index of the key.
     * @return The ratcheted shared key data, or nullptr if unavailable.
     */
    QByteArray ratchetSharedKey(int index);

    /**
     * @brief Exports the shared key with the specified index.
     * @param index The index of the key.
     * @return The exported shared key data, or nullptr if unavailable.
     */
    QByteArray exportSharedKey(int index);

    /**
     * @brief Sets the key for a specific participant with the specified index.
     * @param key The key data.
     * @param index The index of the key.
     * @param participantId The ID of the participant.
     */
    void setKey(QByteArray key, int index, QString participantId);

    /**
     * @brief Gets the ratcheted key for a specific participant with the specified index.
     * @param participantId The ID of the participant.
     * @param index The index of the key.
     * @return The ratcheted key data, or nullptr if unavailable.
     */
    QByteArray ratchetKey(QString participantId, int index);

    /**
     * @brief Exports the key for a specific participant with the specified index.
     * @param participantId The ID of the participant.
     * @param index The index of the key.
     * @return The exported key data, or nullptr if unavailable.
     */
    QByteArray exportKey(QString participantId, int index);

    /**
     * @brief Sets the SIV trailer data.
     * @param trailer The SIV trailer data.
     */
    void setSifTrailer(QByteArray trailer);

  private:
    void init(QByteArray salt, int windowSize, bool sharedKeyMode, QByteArray uncryptedMagicBytes,
              int failureTolerance, int keyRingSize, bool discardFrameWhenCryptorNotReady);

    RTCFrameCryptorKeyProviderPrivate *d_ptr;
    Q_DECLARE_PRIVATE(RTCFrameCryptorKeyProvider)
};

#endif // RTCFRAMECRYPTORKEYPROVIDER_H
