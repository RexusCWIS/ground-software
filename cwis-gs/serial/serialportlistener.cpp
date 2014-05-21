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
    m_writeRequestsArray = new QList<QByteArray>();
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

    m_writeRequestsArray = new QList<QByteArray>();

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

    m_writeRequestsArray = new QList<QByteArray>();

    start();
}

SerialPortListener::~SerialPortListener() {

    stop();
    delete m_recordedData;
    delete m_writeRequestsArray;
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

void SerialPortListener::write(const QByteArray &data)
{
    if(this->isRunning()) {
        m_writeMutex.lock();
        m_writeRequestsArray->append(data);
        m_writeMutex.unlock();
    }
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

void SerialPortListener::clearData(void) {

    m_invalidFrames = 0;
    m_recordedData->clear();
}

void SerialPortListener::saveData(const QString &filename) const {

    if(m_recordedData->isEmpty()) {
        return;
    }

    QFile file(filename);
    if(file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        QTextStream out(&file);

        for(int f = 0; f < m_recordedData->size() - 24; f += 24) {
            for(int index = 0; index < 24; index++) {
                out << m_recordedData->at(f + index) << " ";
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

    serial.open(QIODevice::ReadWrite);

    serial.setBaudRate(m_baudrate);
    serial.setDataBits(m_dataBits);
    serial.setParity(m_parity);
    serial.setStopBits(m_stopBits);

    unsigned int syncFrameSize = 2;
    unsigned int frameSize = 24;
    //const char* syncFrame  = m_sfd.getSynchronisationFrame().toStdString().c_str();
    const char syncFrame[2] = {'U', 'U'};
    unsigned char frame[24];
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

            parseData(frame);

            for(unsigned int index = 0; index < frameSize; index++) {
                m_recordedData->append(frame[index]);
            }
        }

        else {
            m_invalidFrames++;
            emit frameDropped();
            qDebug() << "Invalid Frames: " << m_invalidFrames << "\n";
        }

        /* Write requests */
        m_writeMutex.lock();
        while(!m_writeRequestsArray->isEmpty()) {
            QByteArray request = m_writeRequestsArray->takeFirst();
            serial.write(request);
        }
        m_writeMutex.unlock();
    }

    //delete [] frame;
    serial.close();
    qDebug() << "SerialPortListener thread stopped.";
}

void SerialPortListener::parseData(const unsigned char *frame) {

    (void) frame;
    return;
}
