#include "serialsim.h"

#include "experiment/controlmoduledata.h"

typedef enum {
    POWER,
    LIFTOFF,
    LASER_ON,
    START_OF_DATA_STORAGE,
    CAMERA_ON,
    START_OF_EXPERIMENT,
    IMAGE_STORAGE,
    END_OF_EXPERIMENT
} ControlModuleState;

static ControlModuleData data;

SerialSim::SerialSim(QObject *parent): QThread(parent)
{
    qRegisterMetaType<ControlModuleData>("ControlModuleData");

    m_active = false;

    m_eventTimer = new QTimer(this);
    m_eventTimer->setSingleShot(true);

    QObject::connect(m_eventTimer, SIGNAL(timeout()),
                     this, SLOT(updateControlModuleStatus()));
}

SerialSim::~SerialSim()
{
    this->stop();
}

bool SerialSim::isActive() const {
    return m_active;
}

void SerialSim::start()
{
    m_stop = false;
    m_eventTimer->start(60000);
    QThread::start();
}

void SerialSim::stop()
{
    m_eventTimer->stop();

    m_stop = true;
    while(isRunning())
        ;
}

void SerialSim::run()
{
    data.time = 0;
    data.nbOfImages = 0;
    data.temperatures[0] = 644;
    data.temperatures[1] = 468;
    data.temperatures[2] = 293;
    data.pressure = 766;
    data.controlModuleStatus = 0x1;

    int counter = 0;

    m_active = true;

    while(!m_stop)
    {
        data.time += 100;
        counter++;
        if(counter == 3) {
            data.nbOfImages++;
            counter = 0;
        }

        data.currentTime = QTime::currentTime();
        emit newData(data);
        usleep(100000);
    }
}

void SerialSim::updateControlModuleStatus()
{
    static ControlModuleState currentStatus = POWER;

    int callbackTime = 0;

    switch(currentStatus) {
    case POWER:
        data.controlModuleStatus |= CM_LO;
        currentStatus = LIFTOFF;
        callbackTime = 5;
        break;
    case LIFTOFF:
        data.controlModuleStatus |= CM_LASER_ON;
        currentStatus = LASER_ON;
        callbackTime = 75;
        break;
    case LASER_ON:
        data.controlModuleStatus |= CM_SODS;
        currentStatus = START_OF_DATA_STORAGE;
        callbackTime = 5;
        break;
    case START_OF_DATA_STORAGE:
        data.controlModuleStatus |= CM_CAMERA_ON;
        currentStatus = CAMERA_ON;
        callbackTime = 5;
        break;
    case CAMERA_ON:
        data.controlModuleStatus |= CM_SOE;
        currentStatus = START_OF_EXPERIMENT;
        callbackTime = 100;
        break;
    case START_OF_EXPERIMENT:
        currentStatus = IMAGE_STORAGE;
        callbackTime = 132;
        break;
    case IMAGE_STORAGE:
        data.controlModuleStatus &= ~(CM_CAMERA_ON | CM_LASER_ON);
        currentStatus = END_OF_EXPERIMENT;
        break;
    default:
        break;
    }

    m_eventTimer->start(callbackTime * 100);
}
