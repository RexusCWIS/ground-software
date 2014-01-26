#ifndef SERIALPORTLISTENER_H
#define SERIALPORTLISTENER_H

#include <QThread>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialPortListener: public QThread {

    Q_OBJECT

    public:
        SerialPortListener();
        virtual ~SerialPortListener();

        void start(void);
        void stop(void);

    public slots:
        void setSerialPort(const QString &device);
        void setSerialPort(const QSerialPortInfo &port);

    signals:
        void newStatus(unsigned char);
        void newSensorData(unsigned int, unsigned int, unsigned int, unsigned int);

    protected:
        void run();

    private:
        QSerialPort *m_serial;
        volatile bool m_stop;
};

#endif // SERIALPORTLISTENER_H
