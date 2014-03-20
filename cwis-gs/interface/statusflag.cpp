#include "statusflag.h"

StatusFlag::StatusFlag(QWidget *parent) :
    QLabel(parent)
{
    this->setStatus(false);
}

void StatusFlag::setStatus(bool status) {

    m_status = status;

    if(status) {
        this->setText("ON");
        this->setStyleSheet("QLabel {color : green; }");
    }

    else {
        this->setText("OFF");
        this->setStyleSheet("QLabel {color : red; }");
    }
}

bool StatusFlag::getStatus() const {
    return m_status;
}
