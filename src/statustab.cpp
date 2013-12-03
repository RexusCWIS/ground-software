#include "statustab.h"

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

    m_cameraLabel = new QLabel(this);
    m_laserLabel  = new QLabel(this);
    m_powerLabel  = new QLabel(this);

    m_cameraStatus = new QLabel(this);
    m_laserStatus  = new QLabel(this);
    m_powerStatus  = new QLabel(this);

    statusLabels[0] = m_powerStatus;
    statusLabels[1] = m_laserStatus;
    statusLabels[2] = m_cameraStatus;

    m_cameraLabel->setText("Camera:");
    m_laserLabel->setText("Laser:");
    m_powerLabel->setText("Power:");


    m_cameraStatus->setText("OFF");
    m_laserStatus->setText("OFF");
    m_powerStatus->setText("OFF");


    m_cameraStatus->setFont(f);
    m_laserStatus->setFont(f);
    m_powerStatus->setFont(f);


    m_layout = new QGridLayout(this);
    m_layout->addWidget(m_powerLabel, 0, 0);
    m_layout->addWidget(m_laserLabel, 1, 0);
    m_layout->addWidget(m_cameraLabel, 2, 0);

    m_layout->addWidget(m_powerStatus, 0, 1);
    m_layout->addWidget(m_laserStatus, 1, 1);
    m_layout->addWidget(m_cameraStatus, 2, 1);

    this->setLayout(m_layout);
}

void StatusTab::statusUpdate(const unsigned char status) {

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
