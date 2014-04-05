#ifndef DEF_CONTROL_MODULE_DATA_H
#define DEF_CONTROL_MODULE_DATA_H

/** @brief Experiment duration, in seconds. */
#define EXPERIMENT_DURATION 1600

struct ControlModuleData {
    unsigned int time;
    unsigned int temperatures[3];
    unsigned int pressure;
    unsigned int nbOfImages;
    unsigned int framerate;
    unsigned char controlModuleStatus;
    unsigned char cameraModuleStatus;

    float getTime(void) const {
        return (time / 1000.0f);
    }

    float getTemperature(const unsigned int sensor) const {

        if(sensor > 2) {
            return -1.0f;
        }

        return ((temperatures[sensor] * 70.0f / 1024.0f) - 10.0f);
    }

    float getPressure(void) const {

        return ((pressure * 1.276f / 1024.0f) - 0.255f);
    }
};

Q_DECLARE_METATYPE(ControlModuleData);

#endif  /* DEF_CONTROL_MODULE_DATA_H */
