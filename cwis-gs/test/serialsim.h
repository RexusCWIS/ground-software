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

    bool isActive() const;

public slots:
    void start(void);

    void stop(void);

signals:
    void newData(ControlModuleData data);
    void timeout();

protected:
    void run();

    QTimer *m_eventTimer;
    bool m_stop;
    bool m_active;

protected slots:
    void updateControlModuleStatus();
};

#endif // SERIALSIM_H
