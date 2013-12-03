#ifndef EXPERIMENT_H
#define EXPERIMENT_H

/** @brief Experiment duration, in seconds. */
#define EXPERIMENT_DURATION 1000

typedef struct {
    unsigned int time;
    int temperature[3];
    unsigned int pressure;
    unsigned char status;
    unsigned char events;
}ExperimentData_s;

#endif // EXPERIMENT_H
