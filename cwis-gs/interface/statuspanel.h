#ifndef STATUSPANEL_H
#define STATUSPANEL_H

#include <QWidget>

#include <QGroupBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLabel>

#include "statusflag.h"
#include "clockwidget.h"

class StatusPanel : public QWidget
{
    Q_OBJECT
public:
    explicit StatusPanel(QWidget *parent = 0);

    void updateStatus(int controlModule, int cameraModule);
    void updateNumberOfImages(int numberOfImages);

    void clear(void);
signals:

public slots:

private:
    QLabel *m_logoLabel;

    QLabel *m_dateLabel;
    ClockWidget *m_analogClock;
    DigitalClockWidget *m_digitalClock;
    ChronometerWidget  *m_chronometer;

    QGroupBox *m_controlStatusBox;
    QGroupBox *m_rexusSignalsBox;
    QGroupBox *m_cameraStatusBox;

    QVBoxLayout *m_layout;
    QGridLayout *m_controlStatusLayout;
    QGridLayout *m_rexusSignalsLayout;
    QGridLayout *m_cameraStatusLayout;

    QLabel *m_powerStatusLabel;
    QLabel *m_laserStatusLabel;

    QLabel *m_loStatusLabel;
    QLabel *m_sodsStatusLabel;
    QLabel *m_soeStatusLabel;

    QLabel *m_cameraPowerLabel;
    QLabel *m_cameraImagesLabel;

    StatusFlag *m_powerStatusFlag;
    StatusFlag *m_laserStatusFlag;

    StatusFlag *m_loStatusFlag;
    StatusFlag *m_sodsStatusFlag;
    StatusFlag *m_soeStatusFlag;

    StatusFlag *m_cameraPowerStatusFlag;
    QLabel *m_cameraImagesStatus;

private slots:
    void startChronometer(bool triggered);
};

#endif // STATUSPANEL_H
