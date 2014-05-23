#include "statuspanel.h"

#include "experiment/controlmoduledata.h"

#include <QDate>
#include <QImage>
#include <QSizePolicy>

StatusPanel::StatusPanel(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QVBoxLayout(this);

    /*
    m_logoLabel  = new QLabel(this);
    QImage logo;
    logo.load("/Users/olivierdez/Documents/PhD/CWIS/code/ground-software/cwis-gs/images/cwis_logo.png");
    m_logoLabel->setPixmap(QPixmap::fromImage(logo));
    m_logoLabel->setScaledContents(true);
    m_logoLabel->setAlignment(Qt::AlignCenter);
    m_logoLabel->setMinimumSize(100, 100);
    m_logoLabel->setMaximumSize(250, 250);
    m_logoLabel->setSizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
    //m_logoLabel->setFixedSize(100, 100);*/

    QDate currentDate = QDate::currentDate();
    m_dateLabel    = new QLabel(currentDate.toString(), this);
    m_dateLabel->setAlignment(Qt::AlignCenter);
    m_analogClock  = new ClockWidget(this);
    m_digitalClock = new DigitalClockWidget(this);
    m_chronometer  = new ChronometerWidget(this);
    QObject::connect(m_digitalClock, SIGNAL(refreshed()),
                     m_chronometer, SLOT(refresh()));

    m_controlStatusBox = new QGroupBox(tr("Control Module"), this);
    m_rexusSignalsBox  = new QGroupBox(tr("RXSM signals"), this);
    m_cameraStatusBox  = new QGroupBox(tr("Camera module"), this);

    m_powerStatusLabel  = new QLabel(tr("Power"), m_controlStatusBox);
    m_laserStatusLabel  = new QLabel(tr("Laser"), m_controlStatusBox);
    m_heaterStatusLabel = new QLabel(tr("Heater"), m_controlStatusBox);

    m_loStatusLabel   = new QLabel(tr("LO"), m_rexusSignalsBox);
    m_sodsStatusLabel = new QLabel(tr("SODS"), m_rexusSignalsBox);
    m_soeStatusLabel  = new QLabel(tr("SOE"), m_rexusSignalsBox);

    m_cameraModuleLabel  = new QLabel(tr("Power"), m_cameraStatusBox);
    m_cameraPowerLabel   = new QLabel(tr("Camera"), m_cameraStatusBox);
    m_cameraAcquisitionLabel  = new QLabel(tr("Acquisition"), m_cameraStatusBox);
    m_cameraCopyLabel    = new QLabel(tr("Copy"), m_cameraStatusBox);
    m_cameraImagesLabel = new QLabel(tr("Images"), m_cameraStatusBox);

    m_powerStatusFlag  = new StatusFlag(m_controlStatusBox);
    m_laserStatusFlag  = new StatusFlag(m_controlStatusBox);
    m_heaterStatusFlag = new StatusFlag(m_controlStatusBox);

    m_loStatusFlag   = new StatusFlag(m_rexusSignalsBox);
    QObject::connect(m_loStatusFlag, SIGNAL(toggled(bool)),
                     this, SLOT(startChronometer(bool)));
    m_sodsStatusFlag = new StatusFlag(m_rexusSignalsBox);
    m_soeStatusFlag  = new StatusFlag(m_rexusSignalsBox);

    m_cameraModuleStatusFlag = new StatusFlag(m_cameraStatusBox);
    m_cameraPowerStatusFlag  = new StatusFlag(m_cameraStatusBox);
    m_cameraAcquisitionStatusFlag = new StatusFlag(m_cameraStatusBox);
    m_cameraCopyStatusFlag   = new StatusFlag(m_cameraStatusBox);
    m_cameraImagesStatus = new QLabel(m_cameraStatusBox);

    m_controlStatusLayout = new QGridLayout(m_controlStatusBox);
    m_rexusSignalsLayout  = new QGridLayout(m_rexusSignalsBox);
    m_cameraStatusLayout  = new QGridLayout(m_cameraStatusBox);

    m_controlStatusLayout->addWidget(m_powerStatusLabel, 0, 0);
    m_controlStatusLayout->addWidget(m_powerStatusFlag, 0, 1);
    m_controlStatusLayout->addWidget(m_laserStatusLabel, 1, 0);
    m_controlStatusLayout->addWidget(m_laserStatusFlag, 1, 1);
    m_controlStatusLayout->addWidget(m_heaterStatusLabel, 2, 0);
    m_controlStatusLayout->addWidget(m_heaterStatusFlag, 2, 1);

    m_rexusSignalsLayout->addWidget(m_loStatusLabel, 0, 0);
    m_rexusSignalsLayout->addWidget(m_loStatusFlag, 0, 1);
    m_rexusSignalsLayout->addWidget(m_sodsStatusLabel, 1, 0);
    m_rexusSignalsLayout->addWidget(m_sodsStatusFlag, 1, 1);
    m_rexusSignalsLayout->addWidget(m_soeStatusLabel, 2, 0);
    m_rexusSignalsLayout->addWidget(m_soeStatusFlag, 2, 1);

    m_cameraStatusLayout->addWidget(m_cameraModuleLabel, 0, 0);
    m_cameraStatusLayout->addWidget(m_cameraModuleStatusFlag, 0, 1);
    m_cameraStatusLayout->addWidget(m_cameraPowerLabel, 1, 0);
    m_cameraStatusLayout->addWidget(m_cameraPowerStatusFlag, 1, 1);
    m_cameraStatusLayout->addWidget(m_cameraAcquisitionLabel, 2, 0);
    m_cameraStatusLayout->addWidget(m_cameraAcquisitionStatusFlag, 2, 1);
    m_cameraStatusLayout->addWidget(m_cameraCopyLabel, 3, 0);
    m_cameraStatusLayout->addWidget(m_cameraCopyStatusFlag, 3, 1);
    m_cameraStatusLayout->addWidget(m_cameraImagesLabel, 4, 0);
    m_cameraStatusLayout->addWidget(m_cameraImagesStatus, 4, 1);

    m_controlStatusBox->setLayout(m_controlStatusLayout);
    m_rexusSignalsBox->setLayout(m_rexusSignalsLayout);
    m_cameraStatusBox->setLayout(m_cameraStatusLayout);

    //m_layout->addWidget(m_logoLabel);
    m_layout->addWidget(m_dateLabel);
    m_layout->addWidget(m_analogClock);
    m_layout->addWidget(m_chronometer);
    m_layout->addWidget(m_digitalClock);
    m_layout->addWidget(m_controlStatusBox);
    m_layout->addWidget(m_cameraStatusBox);
    m_layout->addWidget(m_rexusSignalsBox);
    m_layout->addStretch(1);

    this->setLayout(m_layout);
}

void StatusPanel::updateStatus(int controlModule, int cameraModule)
{
    (void) cameraModule;

    m_powerStatusFlag->setStatus((controlModule & CM_POWER_ON) != 0);
    m_laserStatusFlag->setStatus((controlModule & CM_LASER_ON) != 0);
    m_heaterStatusFlag->setStatus((controlModule & CM_HEATER_ON) != 0);
    m_cameraModuleStatusFlag->setStatus((cameraModule & OBDH_POWER_ON) != 0);
    m_cameraPowerStatusFlag->setStatus((cameraModule & OBDH_CAMERA_ON) != 0);
    m_cameraAcquisitionStatusFlag->setStatus((cameraModule & OBDH_ACQUIRING) != 0);
    m_cameraCopyStatusFlag->setStatus((cameraModule & OBDH_COPYING) != 0);
    m_loStatusFlag->setStatus((controlModule & CM_LO) != 0);
    m_sodsStatusFlag->setStatus((controlModule & CM_SODS) != 0);
    m_soeStatusFlag->setStatus((controlModule & CM_SOE) != 0);
}

void StatusPanel::updateNumberOfImages(int numberOfImages)
{
    if(numberOfImages > 0) {
        m_cameraImagesStatus->setText(tr("%1").arg(numberOfImages));
    }
}

void StatusPanel::clear()
{
    m_chronometer->reset();

    m_powerStatusFlag->setStatus(false);
    m_laserStatusFlag->setStatus(false);
    m_heaterStatusFlag->setStatus(false);
    m_cameraModuleStatusFlag->setStatus(false);
    m_cameraPowerStatusFlag->setStatus(false);
    m_cameraAcquisitionStatusFlag->setStatus(false);
    m_cameraCopyStatusFlag->setStatus(false);
    m_loStatusFlag->setStatus(false);
    m_sodsStatusFlag->setStatus(false);
    m_soeStatusFlag->setStatus(false);

    m_cameraImagesStatus->setText(tr(""));
}

void StatusPanel::startChronometer(bool triggered)
{
    if(triggered) {
        m_chronometer->start();
    }
}
