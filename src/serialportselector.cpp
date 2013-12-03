#include "serialportselector.h"
#include <QtSerialPort/QSerialPortInfo>

SerialPortSelector::SerialPortSelector(QWidget *parent) :
    QComboBox(parent) {

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        this->addItem(info.portName());
    }

    this->setSizeAdjustPolicy(QComboBox::AdjustToContents);
}
