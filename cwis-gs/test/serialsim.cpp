#include "serialsim.h"

SerialSim::SerialSim(QObject *parent): QThread(parent)
{
    qRegisterMetaType<ControlModuleData>("ControlModuleData");
}

SerialSim::~SerialSim()
{
    this->stop();
}

void SerialSim::start()
{
    m_stop = false;
    QThread::start();
}

void SerialSim::stop()
{
    m_stop = true;
    while(isRunning())
        ;
}

void SerialSim::run()
{
    ControlModuleData data;
    data.time = 0;
    data.nbOfImages = 0;
    data.temperatures[0] = 644;
    data.temperatures[1] = 468;
    data.temperatures[2] = 293;
    data.pressure = 766;

    int counter = 0;

    while(!m_stop)
    {
        data.time += 100;
        counter++;
        if(counter == 3) {
            data.nbOfImages++;
            counter = 0;
        }

        emit newData(data);
        usleep(100000);
    }
}
