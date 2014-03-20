#include "statuspanel.h"

StatusPanel::StatusPanel(QWidget *parent) :
    QWidget(parent)
{
    m_layout = new QVBoxLayout(this);

    m_controlStatusBox = new QGroupBox(tr("Control Module"), this);
    m_rexusSignalsBox  = new QGroupBox(tr("RXSM signals"), this);

    m_powerStatusLabel = new QLabel(tr("Power:"), m_controlStatusBox);
    m_laserStatusLabel = new QLabel(tr("Laser:"), m_controlStatusBox);

    m_loStatusLabel   = new QLabel(tr("LO:"), m_rexusSignalsBox);
    m_sodsStatusLabel = new QLabel(tr("SODS:"), m_rexusSignalsBox);
    m_soeStatusLabel  = new QLabel(tr("SOE:"), m_rexusSignalsBox);

    m_powerStatusFlag = new StatusFlag(m_controlStatusBox);
    m_laserStatusFlag = new StatusFlag(m_controlStatusBox);

    m_loStatusFlag   = new StatusFlag(m_rexusSignalsBox);
    m_sodsStatusFlag = new StatusFlag(m_rexusSignalsBox);
    m_soeStatusFlag  = new StatusFlag(m_rexusSignalsBox);

    m_controlStatusLayout = new QGridLayout(m_controlStatusBox);
    m_rexusSignalsLayout  = new QGridLayout(m_rexusSignalsBox);

    m_controlStatusLayout->addWidget(m_powerStatusLabel, 0, 0);
    m_controlStatusLayout->addWidget(m_powerStatusFlag, 0, 1);
    m_controlStatusLayout->addWidget(m_laserStatusLabel, 1, 0);
    m_controlStatusLayout->addWidget(m_laserStatusFlag, 1, 1);

    m_rexusSignalsLayout->addWidget(m_loStatusLabel, 0, 0);
    m_rexusSignalsLayout->addWidget(m_loStatusFlag, 0, 1);
    m_rexusSignalsLayout->addWidget(m_sodsStatusLabel, 1, 0);
    m_rexusSignalsLayout->addWidget(m_sodsStatusFlag, 1, 1);
    m_rexusSignalsLayout->addWidget(m_soeStatusLabel, 2, 0);
    m_rexusSignalsLayout->addWidget(m_soeStatusFlag, 2, 1);

    m_controlStatusBox->setLayout(m_controlStatusLayout);
    m_rexusSignalsBox->setLayout(m_rexusSignalsLayout);

    m_layout->addWidget(m_controlStatusBox);
    m_layout->addWidget(m_rexusSignalsBox);
    m_layout->addStretch(1);

    this->setLayout(m_layout);
}
