#include "statusflag.h"

StatusFlag::StatusFlag(QWidget *parent) :
    QLabel(parent)
{
    this->setStatus(false);
}

void StatusFlag::setStatus(bool status) {

    if(status) {
        this->setText("ON");
        this->setStyleSheet("QLabel {color : green; }");
    }

    else {
        this->setText("OFF");
        this->setStyleSheet("QLabel {color : red; }");
    }

    if(m_status != status) {
        emit toggled(status);
    }

    m_status = status;
}

bool StatusFlag::getStatus() const {
    return m_status;
}
