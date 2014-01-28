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

    m_statusLabels[0] = new QLabel("OFF", this);
    m_statusLabels[1] = new QLabel("OFF", this);
    m_statusLabels[2] = new QLabel("OFF", this);

    m_statusLabels[0]->setAlignment(Qt::AlignCenter);
    m_statusLabels[1]->setAlignment(Qt::AlignCenter);
    m_statusLabels[2]->setAlignment(Qt::AlignCenter);

    m_statusLabels[0]->setStyleSheet("QLabel {color : red; }");
    m_statusLabels[1]->setStyleSheet("QLabel {color : red; }");
    m_statusLabels[2]->setStyleSheet("QLabel {color : red; }");

    m_statusLabels[0]->setFont(f);
    m_statusLabels[1]->setFont(f);
    m_statusLabels[2]->setFont(f);

    m_imagesLabel   = new QLabel("Images acquired:");
    m_acquiredLabel = new QLabel("0", this);
    m_acquiredLabel->setAlignment(Qt::AlignCenter);

    m_cpuTempLabel = new QLabel("CPU temperature:", this);
    m_thermometer  = new ThermoMeter(this);
    m_thermometer->setMinimum(0);
    m_thermometer->setMaximum(100);

    m_portLabel = new QLabel("Serial port:", this);
    m_portSelector = new SerialPortSelector(this);

    m_layout = new QGridLayout(this);
    m_layout->addWidget(m_powerLabel, 0, 0);
    m_layout->addWidget(m_laserLabel, 1, 0);
    m_layout->addWidget(m_cameraLabel, 2, 0);

    m_layout->addWidget(m_statusLabels[0], 0, 1);
    m_layout->addWidget(m_statusLabels[1], 1, 1);
    m_layout->addWidget(m_statusLabels[2], 2, 1);

    m_layout->addWidget(m_imagesLabel, 3, 0);
    m_layout->addWidget(m_acquiredLabel, 3, 1);

    m_layout->addWidget(m_cpuTempLabel, 5, 0, 1, 2);

    m_layout->addWidget(m_thermometer, 4, 1, 6, 2);

    m_layout->addWidget(m_portLabel, 11, 0);
    m_layout->addWidget(m_portSelector, 11, 1);

    this->setLayout(m_layout);
    this->setMinimumSize(120, 100);
    this->setMaximumSize(250, 350);
}

void StatusTab::refresh(const unsigned char status) {

    unsigned char diff = m_status ^ status;

    if(diff == 0) {
        return;
    }

    unsigned int bit = 0;

    while(diff != 0) {
        bit = __builtin_ffs((unsigned int) diff) - 1;
        setStatusText(m_statusLabels[bit], (status & bit));
        diff &= ~bit;
    }

    m_status = status;
}
