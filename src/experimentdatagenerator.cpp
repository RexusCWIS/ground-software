#include "experimentdatagenerator.h"

void ExperimentDataGenerator::generateData() {

    int generatedData = 0;
    ExperimentData_s data;

    while(generatedData < 100) {

        data.time = generatedData;
        data.temperature[0] = 10;
        data.temperature[1] = -5;
        data.temperature[2] = 30;
        data.pressure = 1;

        //emit send(10);
        generatedData++;
    }
}

