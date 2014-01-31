#include "serialportlistener.h"

#include "crc.h"

#include <QDebug>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>

/* Required for memcpy */
#include <cstring>

SerialPortListener::SerialPortListener(QObject *parent) :
        QThread(parent) {

    m_stop   = false;
}

SerialPortListener::~SerialPortListener() {

    stop();
}

void SerialPortListener::start() {

    m_stop = false;
    QThread::start();
}

void SerialPortListener::stop() {

    m_stop = true;
    while(isRunning())
        ;
}

void SerialPortListener::setSerialPort(const QString &device) {

    stop();
    m_serialPort = device;
    start();
}

/** @todo Fix this */
void SerialPortListener::setSerialPort(const QSerialPortInfo &port) {

    stop();
    start();
}

void SerialPortListener::run() {

    QSerialPort serial(m_serialPort);
    unsigned char dataFrame[24];

    ExperimentData_s experimentData;

    qRegisterMetaType<ExperimentData_s>("ExperimentData_s");
    qDebug() << "Thread started";

    bool outOfSync  = true,
         validFrame = true;
    unsigned int time = 0;
    unsigned int sensorData[4] = {0, 0, 0, 0};
    unsigned char status[2] = {0, 0};

    serial.open(QIODevice::ReadOnly);

    /* Default parameters: 57600 bps, 8N1 */
    serial.setBaudRate(QSerialPort::Baud38400);
    serial.setDataBits(QSerialPort::Data8);
    serial.setParity(QSerialPort::NoParity);
    serial.setStopBits(QSerialPort::OneStop);

    while(!m_stop) {

        /** @todo Detect loss of synchronisation */
        outOfSync = true;
        /* Detect start of frame ("UU") */
        while(outOfSync) {

            while(serial.bytesAvailable() < 2) {
                serial.waitForReadyRead(100);
            }
            serial.read((char *) dataFrame, 1);

            if(dataFrame[0] == 'U') {
                serial.read((char *) &dataFrame[1], 1);

                if(dataFrame[1] == 'U') {
                    outOfSync = false;
                }
            }
        }

        while(serial.bytesAvailable() < 22) {
            serial.waitForReadyRead(100);
        }
        /* Read the remaining 22 bytes */
        serial.read((char *) &dataFrame[2], 22);

        validFrame = (crc(dataFrame, 24) == 0);

        if(validFrame) {

            /* Separate data and emit related signals */
            /** @todo Implement unit conversion */
            experimentData.time = (((unsigned int) dataFrame[5]) << 24) + (((unsigned int) dataFrame[4]) << 16) +
                   (((unsigned int) dataFrame[3]) << 8) + ((unsigned int) dataFrame[2]);

            for(int index = 6; index < 12; index += 2) {
                experimentData.temperature[(index >> 1) - 3] = (((unsigned int) dataFrame[index + 1]) << 8) +
                                                ((unsigned int) dataFrame[index]);
            }

            experimentData.pressure = (((unsigned int) dataFrame[13]) << 8) +
                                      ((unsigned int) dataFrame[12]);

            status[0] = dataFrame[14];
            status[1] = dataFrame[15];

            qDebug() << experimentData.time << ": " << status[0] << "\n";
            emit newStatus((status[0] & 0x7));
            emit newSensorData(experimentData);
        }
    }

    serial.close();
}
