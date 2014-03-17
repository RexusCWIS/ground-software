#ifndef STATUSTAB_H
#define STATUSTAB_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>

/** @todo Add images taken by the camera, camera framerate...*/
class StatusTab : public QWidget
{
    Q_OBJECT
public:
    explicit StatusTab(QWidget *parent = 0);

signals:

public slots:
    /**
     * @brief Updates the displayed informations to match the given @p status.
     * @param status    Status bitfield.
     */
    void refresh(const unsigned char controlStatus, const unsigned char cameraStatus);

private:
    QLabel *m_cameraLabel;      /**< @brief Camera label. */
    QLabel *m_laserLabel;       /**< @brief Laser power label. */
    QLabel *m_powerLabel;       /**< @brief General power label. */
    QLabel *m_loLabel;
    QLabel *m_sodsLabel;
    QLabel *m_soeLabel;
    QLabel *m_imagesLabel;      /**< @brief Acquired images label. */
    QLabel *m_acquiredLabel;    /**< @brief Displays the number of acquired images. */

    QGridLayout *m_layout;      /**< @brief Layout of the status tab. */

    unsigned char m_controlStatus;     /**< @brief Current experiment status. */
    unsigned char m_cameraStatus;
    QLabel * m_statusLabels[6];
};

#endif // STATUSTAB_H
