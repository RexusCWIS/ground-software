#ifndef SERIALSIM_H
#define SERIALSIM_H

#include <QThread>

#include <QTimer>

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

    QTimer *m_eventTimer;
    bool m_stop;

protected slots:
    void updateControlModuleStatus();
};

#endif // SERIALSIM_H
