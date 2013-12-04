#ifndef EXPERIMENTDATAGENERATOR_H
#define EXPERIMENTDATAGENERATOR_H

#include <QObject>

#include "experiment.h"

class ExperimentDataGenerator: public QObject {
    Q_OBJECT

    public slots:
        void generateData();

    signals:
        void newSensorData(ExperimentData_s const&);
        void send(int);
};

#endif // EXPERIMENTDATAGENERATOR_H
