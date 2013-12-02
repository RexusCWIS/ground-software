#ifndef STATUSTAB_H
#define STATUSTAB_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

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
    void statusUpdate(const unsigned char status);

private:
    QLabel *m_cameraLabel;      /**< @brief Camera label. */
    QLabel *m_laserLabel;       /**< @brief Laser power label. */
    QLabel *m_powerLabel;       /**< @brief General power label. */

    QLabel *m_cameraStatus;
    QLabel *m_laserStatus;
    QLabel *m_powerStatus;

    QGridLayout *m_layout;      /**< @brief Layout of the status tab. */

    unsigned char m_status;     /**< @brief Current experiment status. */
    QLabel * statusLabels[3];
};

#endif // STATUSTAB_H
