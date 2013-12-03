#include "serialportlistener.h"
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

SerialPortListener::SerialPortListener() {

    m_stop   = false;

    m_serial = new QSerialPort();
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
    while(isRunning())
        ;
}

void SerialPortListener::setSerialPort(const QString &device) {

    stop();
    m_serial->setPortName(device);
    start();
}

void SerialPortListener::setSerialPort(const QSerialPortInfo &port) {

    stop();
    m_serial->setPort(port);
    start();
}

void SerialPortListener::run() {

    m_serial->open(QIODevice::ReadOnly);

    /* Default parameters: 57600 bps, 8N1 */
    m_serial->setBaudRate(QSerialPort::Baud57600);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);

    while(!m_stop) {
    }

    m_serial->close();
}

