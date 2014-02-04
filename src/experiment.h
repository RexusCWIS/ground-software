#ifndef EXPERIMENT_H
#define EXPERIMENT_H

/** @brief Experiment duration, in seconds. */
#define EXPERIMENT_DURATION 1000

struct ExperimentData_s {
    unsigned int time;
    unsigned int temperature[3];
    unsigned int pressure;
    unsigned char status;
    unsigned char events;

    float getTime(void) const {
        return (time / 100.0);
    }

    float getTemperature(const unsigned int sensor) const {

        if(sensor > 2) {
            return -1.0f;
        }

        return ((temperature[sensor] * 70.0f / 1024.0f) - 10.0f);
    }

    float getPressure(void) const {

        return ((pressure * 4.899f / 1024.0f) - 0.25515f);
    }
};

#endif // EXPERIMENT_H
