#include "experimentdatagenerator.h"

void ExperimentDataGenerator::generateData() {

    int generatedData = 0;
    ExperimentData_s data;

    qRegisterMetaType<ExperimentData_s>("ExperimentData_s");
    qDebug("Thread started.");

    data.temperature[0] = 10;
    data.temperature[1] = -5;
    data.temperature[2] = 30;
    data.pressure = 1;

    while(generatedData < 1000) {

        data.time = generatedData;

        if(generatedData == 400) {
            data.temperature[0] = 30;
            data.temperature[1] = -10;
            data.temperature[2] = 70;
        }

        emit newSensorData(data);
        generatedData++;
    }

    qDebug("Thread completed.");
}

