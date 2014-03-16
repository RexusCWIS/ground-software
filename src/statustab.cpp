#include "statustab.h"
#include <QSpacerItem>

static inline void setStatusText(QLabel *label, unsigned char status) {

    if(status) {
        label->setText("ON");
        label->setStyleSheet("QLabel {color : green; }");
    }

    else {
        label->setText("OFF");
        label->setStyleSheet("QLabel {color : red; }");
    }
}

StatusTab::StatusTab(QWidget *parent) :
    QWidget(parent)
{
    QFont f("Helvetica", 10, QFont::Bold);

    m_cameraLabel = new QLabel("Camera:", this);
    m_laserLabel  = new QLabel("Laser:", this);
    m_powerLabel  = new QLabel("Power:", this);
    m_loLabel   = new QLabel("LO:", this);
    m_sodsLabel = new QLabel("SODS:", this);
    m_soeLabel  = new QLabel("SOE:", this);

    m_statusLabels[0] = new QLabel("OFF", this);
    m_statusLabels[1] = new QLabel("OFF", this);
    m_statusLabels[2] = new QLabel("OFF", this);
    m_statusLabels[3] = new QLabel("OFF", this);
    m_statusLabels[4] = new QLabel("OFF", this);
    m_statusLabels[5] = new QLabel("OFF", this);

    m_statusLabels[0]->setAlignment(Qt::AlignCenter);
    m_statusLabels[1]->setAlignment(Qt::AlignCenter);
    m_statusLabels[2]->setAlignment(Qt::AlignCenter);
    m_statusLabels[3]->setAlignment(Qt::AlignCenter);
    m_statusLabels[4]->setAlignment(Qt::AlignCenter);
    m_statusLabels[5]->setAlignment(Qt::AlignCenter);

    m_statusLabels[0]->setStyleSheet("QLabel {color : red; }");
    m_statusLabels[1]->setStyleSheet("QLabel {color : red; }");
    m_statusLabels[2]->setStyleSheet("QLabel {color : red; }");
    m_statusLabels[3]->setStyleSheet("QLabel {color : red; }");
    m_statusLabels[4]->setStyleSheet("QLabel {color : red; }");
    m_statusLabels[5]->setStyleSheet("QLabel {color : red; }");

    m_statusLabels[0]->setFont(f);
    m_statusLabels[1]->setFont(f);
    m_statusLabels[2]->setFont(f);
    m_statusLabels[3]->setFont(f);
    m_statusLabels[4]->setFont(f);
    m_statusLabels[5]->setFont(f);

    m_imagesLabel   = new QLabel("Images acquired:");
    m_acquiredLabel = new QLabel("0", this);
    m_acquiredLabel->setAlignment(Qt::AlignCenter);

    m_layout = new QGridLayout(this);
    m_layout->addWidget(m_powerLabel, 0, 0);
    m_layout->addWidget(m_laserLabel, 1, 0);
    m_layout->addWidget(m_cameraLabel, 2, 0);
    m_layout->addWidget(m_loLabel, 3, 0);
    m_layout->addWidget(m_sodsLabel, 4, 0);
    m_layout->addWidget(m_soeLabel, 5, 0);

    m_layout->addWidget(m_statusLabels[0], 0, 1);
    m_layout->addWidget(m_statusLabels[1], 1, 1);
    m_layout->addWidget(m_statusLabels[2], 2, 1);
    m_layout->addWidget(m_statusLabels[3], 3, 1);
    m_layout->addWidget(m_statusLabels[4], 4, 1);
    m_layout->addWidget(m_statusLabels[5], 5, 1);

    m_layout->addWidget(m_imagesLabel, 6, 0);
    m_layout->addWidget(m_acquiredLabel, 6, 1);

    this->setLayout(m_layout);
    this->setMinimumSize(200, 100);
    this->setMaximumSize(250, 250);

    m_status = 0;
}

void StatusTab::refresh(const unsigned char status) {

    unsigned char diff = m_status ^ status;

    if(diff == 0) {
        return;
    }

    unsigned int bit = 0;

    while(diff != 0) {
        bit = __builtin_ffs((unsigned int) diff) - 1;
        setStatusText(m_statusLabels[bit], (status & (1 << bit)));
        diff &= ~(1 << bit);
    }

    m_status = status;
}
