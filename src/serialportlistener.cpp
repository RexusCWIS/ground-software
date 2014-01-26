#include "serialportlistener.h"

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>

/* Required for memcpy */
#include <cstring>

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

    char dataFrame[24];

    bool outOfSync = true;
    int time = 0;
    unsigned int sensorData[4] = {0, 0, 0, 0};
    unsigned char status[2] = {0, 0};

    m_serial->open(QIODevice::ReadOnly);

    /* Default parameters: 57600 bps, 8N1 */
    m_serial->setBaudRate(QSerialPort::Baud38400);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);

    while(!m_stop) {

        /** @todo Detect loss of synchronisation */
        outOfSync = true;
        /* Detect start of frame ("UU") */
        while(outOfSync) {

            while(m_serial->bytesAvailable() < 2) {
                m_serial->waitForReadyRead(100);
            }
            m_serial->read(dataFrame, 1);

            if(dataFrame[0] == 'U') {
                m_serial->read(&dataFrame[1], 1);

                if(dataFrame[1] == 'U') {
                    outOfSync = false;
                }
            }
        }

        while(m_serial->bytesAvailable() < 22)
        /* Read the remaining 22 bytes */
        m_serial->read(&dataFrame[2], 22);

        /** @todo Implement checksum computation */

        /* Separate data and emit related signals */
        /** @todo Implement unit conversion */
        time = (((int) dataFrame[5]) << 24) + (((int) dataFrame[4]) << 16) +
               (((int) dataFrame[3]) << 8) + ((int) dataFrame[2]);

        for(int index = 6; index < 14; index += 2) {
            sensorData[(index >> 1) - 3] = (((int) dataFrame[index + 1]) << 8) + ((int) dataFrame[index]);
        }

        status[0] = dataFrame[14];
        status[1] = dataFrame[15];

        emit newStatus(status[0]);
        emit newSensorData(sensorData[0], sensorData[1], sensorData[2], sensorData[3]);
    }

    m_serial->close();
}
