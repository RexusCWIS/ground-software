#ifndef SERIALSIM_H
#define SERIALSIM_H

#include <QThread>

#include "experiment/controlmoduledata.h"

class SerialSim: public QThread
{
    Q_OBJECT
public:
    SerialSim(QObject *parent);

    virtual ~SerialSim();

public slots:
    void start(void);

    void stop(void);

signals:
    void newData(ControlModuleData data);

protected:
    void run();

    bool m_stop;
};

#endif // SERIALSIM_H
