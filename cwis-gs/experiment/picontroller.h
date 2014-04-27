#ifndef PICONTROLLER_H
#define PICONTROLLER_H

class PIController
{
public:
    PIController(double kp, double ki, double dt);

    void setKP(double kp);

    void setKI(double ki);

    void setIntegratorSaturation(double lower, double upper);

    void setOutputSaturation(double lower, double upper);

    double loop(double error);

private:
    double saturation(double value, double lower, double upper);
    void integratorSaturation();

    double m_kp;
    double m_ki;
    double m_dt;
    double m_integral;

    int m_integratorSaturated;
    double m_integratorSaturationLowerBound;
    double m_integratorSaturationUpperBound;

    bool m_saturateOutput;
    double m_outputSaturationLowerBound;
    double m_outputSaturationUpperBound;
};

#endif // PICONTROLLER_H
