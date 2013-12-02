#include "statustab.h"

StatusTab::StatusTab(QWidget *parent) :
    QWidget(parent)
{
    m_cameraLabel = new QLabel(this);
    m_laserLabel = new QLabel(this);
    m_powerLabel = new QLabel(this);

    m_cameraLabel->setText("Camera:");
    m_laserLabel->setText("Laser:");
    m_powerLabel->setText("Power:");

    m_layout = new QGridLayout(this);
    m_layout->addWidget(m_powerLabel, 0, 0);
    m_layout->addWidget(m_laserLabel, 1, 0);
    m_layout->addWidget(m_cameraLabel, 2, 0);

    this->setLayout(m_layout);
}

void StatusTab::statusUpdate(const unsigned char status) {
    (void) status;
}
