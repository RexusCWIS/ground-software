#ifndef DEF_CONTROL_MODULE_DATA_H
#define DEF_CONTROL_MODULE_DATA_H

#include <QTime>

/* Control module status bitfield */
#define CM_POWER_ON     (1 << 0)
#define CM_LASER_ON     (1 << 1)
#define CM_CAMERA_ON    (1 << 2)
#define CM_HEATER_ON    (1 << 3)
#define CM_LO           (1 << 4)
#define CM_SODS         (1 << 5)
#define CM_SOE          (1 << 6)

struct ControlModuleData {
    QTime currentTime;
    unsigned int time;
    unsigned int temperatures[3];
    unsigned int pressure;
    unsigned int heating;
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

    float getHeating(void) const {
        return heating / 2.55f;
    }
};

Q_DECLARE_METATYPE(ControlModuleData)

#endif  /* DEF_CONTROL_MODULE_DATA_H */
