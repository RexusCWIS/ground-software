#include "serialportlistener.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

SerialPortListener::SerialPortListener() {
    m_serial = new QSerialPort();
    m_stop   = false;
}

SerialPortListener::~SerialPortListener() {

    stop();
    delete m_serial;
}

void SerialPortListener::start() {

    m_stop = false;
    QThread::run();
}

void SerialPortListener::stop() {

    m_stop = true;
}

void SerialPortListener::setSerialPort(const QString &device) {

}

void SerialPortListener::run() {

    while(!m_stop) {

    }
}

