#ifndef STATUSTAB_H
#define STATUSTAB_H

#include <QWidget>
#include <QFrame>
#include <QLabel>
#include <QGridLayout>

#include "serialportselector.h"
#include "serialportlistener.h"

#include "thermometer/thermometer.h"

/** @todo Add images taken by the camera, camera framerate...*/
class StatusTab : public QWidget
{
    Q_OBJECT
public:
    explicit StatusTab(QWidget *parent = 0);

    void setSerialPortListener(const SerialPortListener *spListener);

signals:

public slots:
    /**
     * @brief Updates the displayed informations to match the given @p status.
     * @param status    Status bitfield.
     */
    void refresh(const unsigned char status);

private:
    QLabel *m_cameraLabel;      /**< @brief Camera label. */
    QLabel *m_laserLabel;       /**< @brief Laser power label. */
    QLabel *m_powerLabel;       /**< @brief General power label. */
    QLabel *m_imagesLabel;      /**< @brief Acquired images label. */
    QLabel *m_acquiredLabel;    /**< @brief Displays the number of acquired images. */
    QLabel *m_cpuTempLabel;     /**< @brief CPU temperature label. */

    ThermoMeter *m_thermometer; /**< @brief Thermometer indicating the CPU temperature. */

    QGridLayout *m_layout;      /**< @brief Layout of the status tab. */

    unsigned char m_status;     /**< @brief Current experiment status. */
    QLabel * m_statusLabels[3];

    /* Serial port */
    QLabel *m_portLabel;
    SerialPortSelector *m_portSelector;
};

#endif // STATUSTAB_H
