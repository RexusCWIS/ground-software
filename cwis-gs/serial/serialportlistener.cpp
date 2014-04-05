#include "serialportlistener.h"

#include "crc/crc.h"

#include <QDebug>
#include <QFile>
#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>
#include <QByteArray>

SerialPortListener::SerialPortListener(QObject *parent) :
            QThread(parent) {

    m_stop   = false;
    m_active = false;
    m_configured = false;
    m_validFrames   = 0;
    m_invalidFrames = 0;
    m_recordedData  = new QVector<unsigned char>(0);
}

SerialPortListener::SerialPortListener(QObject *parent,
                                       const SerialFrameDescriptor &sfd,
                                       const QString &device,
                                       QSerialPort::BaudRate baudrate,
                                       QSerialPort::DataBits dataBits,
                                       QSerialPort::Parity parity,
                                       QSerialPort::StopBits stopBits) : QThread(parent) {

    m_serialPort = device;

    m_baudrate = baudrate;
    m_dataBits = dataBits;
    m_parity   = parity;
    m_stopBits = stopBits;

    m_stop = false;
    m_active = false;
    m_configured = true;
    m_invalidFrames = 0;
    m_recordedData  = new QVector<unsigned char>(0);

    this->setSerialFrameDescriptor(sfd);

    start();
}

SerialPortListener::SerialPortListener(QObject *parent,
                                       const SerialFrameDescriptor &sfd,
                                       const SerialPortConfig &config) : QThread(parent) {

    this->setSerialPortConfig(config);

    this->setSerialFrameDescriptor(sfd);

    m_stop = false;
    m_active = false;
    m_invalidFrames = 0;
    m_recordedData  = new QVector<unsigned char>(0);

    start();
}

SerialPortListener::~SerialPortListener() {

    stop();
    delete m_recordedData;
}

void SerialPortListener::start() {

    m_stop = false;

    if(!this->isRunning()) {
        QThread::start();
    }
}

void SerialPortListener::stop() {

    m_stop = true;
    while(isRunning())
        ;
    m_active = false;
}

bool SerialPortListener::isActive() const
{
    return m_active;
}

bool SerialPortListener::isConfigured() const
{
    return m_configured;
}

void SerialPortListener::setSerialFrameDescriptor(const SerialFrameDescriptor &sfd) {

    m_sfd = sfd;
}

void SerialPortListener::setSerialPortConfig(const SerialPortConfig &config) {

    bool running = this->isRunning();

    if(running) {
        this->stop();
    }

    m_serialPort = config.device;
    m_baudrate   = config.baudrate;
    m_dataBits   = config.dataBits;
    m_parity     = config.parity;
    m_stopBits   = config.stopBits;

    m_configured = true;

    if(running) {
        this->start();
    }
}

void SerialPortListener::clearRecordedData(void) {

    m_invalidFrames = 0;
    m_recordedData->clear();
}

void SerialPortListener::saveRecordedData(const QString &filename) const {

    if(m_recordedData->isEmpty()) {
        return;
    }

    QFile file(filename);
    if(file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&file);
        out << "Time [ms]\tTemperature 1\tTemperature2\tTemperature3\tPressure\tStatus Flags\n";

        for(int f = 0; f < m_recordedData->size(); f += m_sfd.size()) {
            for(int index = 0; index < m_sfd.size(); index++) {
                out << m_recordedData->at(f * m_sfd.size() + index) << "\t";
            }

            out << "\n";
        }

        file.close();
    }
}

int SerialPortListener::getNumberOfInvalidFrames(void) const {

    return m_invalidFrames;
}

void SerialPortListener::run() {

    qDebug() << "SerialPortListener thread started.";
    QSerialPort serial(m_serialPort);

    m_validFrames   = 0;
    m_invalidFrames = 0;

    bool outOfSync  = true,
         validFrame = true;

    serial.open(QIODevice::ReadOnly);

    serial.setBaudRate(m_baudrate);
    serial.setDataBits(m_dataBits);
    serial.setParity(m_parity);
    serial.setStopBits(m_stopBits);

    unsigned int syncFrameSize = m_sfd.getSynchronisationFrame().size();
    unsigned int frameSize = m_sfd.size();
    //const char* syncFrame  = m_sfd.getSynchronisationFrame().toStdString().c_str();
    const char syncFrame[3] = "UU";
    unsigned char frame[13];
    //unsigned char* frame = new unsigned char[frameSize]();

    while(!m_stop) {

        /** @todo Detect loss of synchronisation */
        outOfSync = true;
        /* Detect start of frame */
        /** Adapt this for synchronization frames longer than 2 bytes */
        while(outOfSync && !m_stop) {

            while((serial.bytesAvailable() < syncFrameSize) && !m_stop) {
                if(!serial.waitForReadyRead(100)) {
                    emit timeout();
                    m_active = false;
                }
            }
            serial.read((char *) frame, 1);

            if(frame[0] == (unsigned char) syncFrame[0]) {

                serial.read((char *) &frame[1], 1);

                if(frame[1] == (unsigned char) syncFrame[1]) {
                    outOfSync = false;
                }
            }
        }

        while((serial.bytesAvailable() < (frameSize - syncFrameSize)) && !m_stop) {
            if(!serial.waitForReadyRead(100)) {
                emit timeout();
                m_active = false;
            }
        }

        /* Exit the thread loop if the m_stop signal was sent */
        if(m_stop) {
            break;
        }

        m_active = true;

        /* Read the rest of the frame */
        serial.read((char *) &frame[syncFrameSize], frameSize - syncFrameSize);

        if(m_sfd.hasCRC()) {
            validFrame = (crc(frame, frameSize) == 0);
        }

        if(validFrame) {

            m_validFrames++;
            qDebug() << "Valid Frames: " << m_validFrames << "\n";

            parseData(frame);

            for(unsigned int index = 0; index < frameSize; index++) {
                m_recordedData->append(frame[index]);
            }
        }

        else {
            m_invalidFrames++;
            qDebug() << "Invalid Frames: " << m_invalidFrames << "\n";
        }
    }

    //delete [] frame;
    serial.close();
    qDebug() << "SerialPortListener thread stopped.";
}

void SerialPortListener::parseData(const unsigned char *frame) {

    (void) frame;
    return;
}
