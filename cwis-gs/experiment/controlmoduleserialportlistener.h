#ifndef CONTROLMODULESERIALPORTLISTENER_H
#define CONTROLMODULESERIALPORTLISTENER_H

#include "serial/serialportlistener.h"
#include "experiment/controlmoduledata.h"

class ControlModuleSerialPortListener : public SerialPortListener
{
    Q_OBJECT

public:
    ControlModuleSerialPortListener(QObject *parent);

    ControlModuleSerialPortListener(QObject *parent,
                                   const SerialFrameDescriptor &sfd,
                                   const QString &device,
                                   QSerialPort::BaudRate baudrate,
                                   QSerialPort::DataBits dataBits = QSerialPort::Data8,
                                   QSerialPort::Parity parity = QSerialPort::NoParity,
                                   QSerialPort::StopBits stopBits = QSerialPort::OneStop);

    ControlModuleSerialPortListener(QObject *parent,
                                   const SerialFrameDescriptor &sfd,
                                   const SerialPortConfig &config);

signals:
    void newData(const ControlModuleData &data);

protected:
    void parseData(const unsigned char *frame);
};

#endif // CONTROLMODULESERIALPORTLISTENER_H
