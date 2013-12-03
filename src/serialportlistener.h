#ifndef SERIALPORTLISTENER_H
#define SERIALPORTLISTENER_H

#include <QThread>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

class SerialPortListener: public QThread {

    public:
        SerialPortListener();
        virtual ~SerialPortListener();

        void start(void);
        void stop(void);

    public slots:
        void setSerialPort(const QString &device);

    protected:
        void run(void);

    private:
        QSerialPort *m_serial;
        volatile bool m_stop;
};

#endif // SERIALPORTLISTENER_H
