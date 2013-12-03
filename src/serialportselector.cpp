#include "serialportselector.h"
#include <QtSerialPort/QSerialPortInfo>

SerialPortSelector::SerialPortSelector() {

    foreach(const QSerialPortInfo &info, QSerialPortInfo::availablePorts()) {
        this->addItem(info.portName());
    }
}
