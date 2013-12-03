#include "statustab.h"
#include <QSpacerItem>

static inline void setStatusText(QLabel *label, unsigned char status) {

    if(status == true) {
        label->setText("ON");
    }

    else {
        label->setText("OFF");
    }
}

StatusTab::StatusTab(QWidget *parent) :
    QWidget(parent)
{
    QFont f("Arial", 10, QFont::Bold);

    m_cameraLabel = new QLabel("Camera:", this);
    m_laserLabel  = new QLabel("Laser:", this);
    m_powerLabel  = new QLabel("Power:", this);

    m_cameraStatus = new QLabel("OFF", this);
    m_laserStatus  = new QLabel("OFF", this);
    m_powerStatus  = new QLabel("OFF", this);

    statusLabels[0] = m_powerStatus;
    statusLabels[1] = m_laserStatus;
    statusLabels[2] = m_cameraStatus;

    m_cameraStatus->setStyleSheet("QLabel {color : red; }");
    m_laserStatus->setStyleSheet("QLabel {color : red; }");
    m_powerStatus->setStyleSheet("QLabel {color : red; }");

    m_cameraStatus->setFont(f);
    m_laserStatus->setFont(f);
    m_powerStatus->setFont(f);

    m_portLabel = new QLabel("Serial port:", this);
    m_portSelector = new SerialPortSelector(this);

    m_layout = new QGridLayout(this);
    m_layout->addWidget(m_powerLabel, 0, 0);
    m_layout->addWidget(m_laserLabel, 1, 0);
    m_layout->addWidget(m_cameraLabel, 2, 0);

    m_layout->addWidget(m_powerStatus, 0, 1);
    m_layout->addWidget(m_laserStatus, 1, 1);
    m_layout->addWidget(m_cameraStatus, 2, 1);

    m_layout->addWidget(m_portLabel, 4, 0);
    m_layout->addWidget(m_portSelector, 4, 1);

    this->setLayout(m_layout);
    this->setMinimumSize(120, 100);
    this->setMaximumSize(200, 100);
}

void StatusTab::refresh(const unsigned char status) {

    unsigned char diff = m_status ^ status;

    if(diff == 0) {
        return;
    }

    unsigned int bit = 0;

    while(diff != 0) {
        bit = __builtin_ffs((unsigned int) diff) - 1;
        setStatusText(statusLabels[bit], (status & bit));
        diff &= ~bit;
    }

    m_status = status;
}
