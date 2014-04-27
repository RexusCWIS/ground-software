#include "picontroller.h"

PIController::PIController(double kp, double ki, double dt) :
    m_kp(kp), m_ki(ki), m_dt(dt)
{
    m_integral = 0;
    m_integratorSaturated  = 0;
}

void PIController::setIntegratorSaturation(double lower, double upper)
{
    m_integratorSaturationLowerBound = lower;
    m_integratorSaturationUpperBound = upper;
}

void PIController::setOutputSaturation(double lower, double upper)
{
    m_outputSaturationLowerBound = lower;
    m_outputSaturationUpperBound = upper;

    m_saturateOutput = true;
}

double PIController::loop(double error)
{
    double setpoint;

    if((error * m_integratorSaturated) < 0) {
        m_integral += m_ki * m_dt * error;
    }

    this->integratorSaturation();

    setpoint = m_kp * error + m_integral;

    if(m_saturateOutput) {
        this->saturation(setpoint, m_outputSaturationLowerBound, m_outputSaturationUpperBound);
    }

    return setpoint;
}

double PIController::saturation(double value, double lower, double upper)
{
    if(value > upper) {
        return upper;
    }

    if(value < lower) {
        return lower;
    }

    return value;
}

double PIController::integratorSaturation()
{
    if(m_integral > m_integratorSaturationUpperBound) {
        m_integral = m_integratorSaturationUpperBound;
        m_integratorSaturated = 1;
    }

    else if(m_integral < m_integratorSaturationLowerBound) {
        m_integral = m_integratorSaturationLowerBound;
        m_integratorSaturated = -1;
    }

    else {
        m_integratorSaturated = 0;
    }
}
