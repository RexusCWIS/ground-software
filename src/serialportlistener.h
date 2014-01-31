#ifndef SERIALPORTLISTENER_H
#define SERIALPORTLISTENER_H

#include "experiment.h"

#include <QThread>
#include <QtSerialPort/QSerialPortInfo>

class SerialPortListener: public QThread {

    Q_OBJECT

    public:
        SerialPortListener(QObject *parent);
        virtual ~SerialPortListener();

        void start(void);
        void stop(void);

    public slots:
        void setSerialPort(const QString &device);
        void setSerialPort(const QSerialPortInfo &port);

    signals:
        void newStatus(unsigned char);
        void newSensorData(ExperimentData_s);

    protected:
        void run();

    private:
        QString m_serialPort;
        volatile bool m_stop;
};

#endif // SERIALPORTLISTENER_H
