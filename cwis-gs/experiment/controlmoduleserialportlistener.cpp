#include "controlmoduleserialportlistener.h"

ControlModuleSerialPortListener::ControlModuleSerialPortListener(QObject *parent) :
        SerialPortListener(parent) {

    qRegisterMetaType<ControlModuleData>("ControlModuleData");
}

ControlModuleSerialPortListener::ControlModuleSerialPortListener(QObject *parent,
                                                               const SerialFrameDescriptor &sfd,
                                                               const QString &device,
                                                               QSerialPort::BaudRate baudrate,
                                                               QSerialPort::DataBits dataBits,
                                                               QSerialPort::Parity parity,
                                                               QSerialPort::StopBits stopBits) :
    SerialPortListener(parent, sfd, device, baudrate, dataBits, parity, stopBits) {

    qRegisterMetaType<ControlModuleData>("ControlModuleData");
}

ControlModuleSerialPortListener::ControlModuleSerialPortListener(QObject *parent,
                                                               const SerialFrameDescriptor &sfd,
                                                               const SerialPortConfig &config) :
    SerialPortListener(parent, sfd, config) {

    qRegisterMetaType<ControlModuleData>("ControlModuleData");
}

void ControlModuleSerialPortListener::parseData(const unsigned char *frame) {

    ControlModuleData data;

    data.time = (((unsigned int) frame[5]) << 24) + (((unsigned int) frame[4]) << 16) +
            (((unsigned int) frame[3]) << 8) + ((unsigned int) frame[2]);

    data.temperatures[0] = (((unsigned int) frame[7]) << 8) + ((unsigned int) frame[6]);
    data.temperatures[1] = (((unsigned int) frame[9]) << 8) + ((unsigned int) frame[8]);
    data.temperatures[2] = (((unsigned int) frame[11]) << 8) + ((unsigned int) frame[10]);
    data.pressure = (((unsigned int) frame[13]) << 8) + ((unsigned int) frame[12]);
    data.heating  = (unsigned int) frame[14];

    data.nbOfImages  = (((unsigned int) frame[16]) << 8) + ((unsigned int) frame[17]);
    data.framerate   = (unsigned int) frame[18];
    data.controlModuleStatus = frame[15];
    data.cameraModuleStatus  = frame[19];

    data.currentTime = QTime::currentTime();

    emit newData(data);
}
