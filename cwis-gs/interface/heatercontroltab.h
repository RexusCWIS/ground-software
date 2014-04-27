#ifndef HEATERCONTROLTAB_H
#define HEATERCONTROLTAB_H

#include <QWidget>

#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QLineEdit>
#include <QPushButton>

#include "dataplot.h"

#include "experiment/controlmoduledata.h"
#include "experiment/picontroller.h"

class HeaterControlTab : public QWidget
{
    Q_OBJECT
public:
    explicit HeaterControlTab(QWidget *parent = 0);

public slots:
    void addData(const ControlModuleData &data);

    void clear();

signals:
    void uplinkLO();
    void uplinkSODS();
    void uplinkSOE();

    void uplinkHeater(int);

private:
    void plotSetup();
    void sidePanelSetup();

    DataPlot *m_plot;

    PIController *m_piController;
    double m_piSetpoint;
    bool m_simulatePIControl;
    bool m_remoteHeaterControl;

    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_sidePanelLayout;
    QGridLayout *m_uplinkBoxLayout;
    QGridLayout *m_piControlBoxLayout;

    QGroupBox *m_uplinkBox;
    QGroupBox *m_piControlBox;

    QPushButton *m_rxsmLOButton;
    QPushButton *m_rxsmSODSButton;
    QPushButton *m_rxsmSOEButton;

    QLabel *m_heaterDutyCycleTextLabel;
    QLineEdit *m_heaterDutyCycleValueLabel;

    QLabel *m_piKpTextLabel;
    QLabel *m_piKiTextLabel;
    QLabel *m_piSetpointTextLabel;
    QLabel *m_piIntegratorSaturationLabel;

    QLineEdit *m_piKpValueLabel;
    QLineEdit *m_piKiValueLabel;
    QLineEdit *m_piSetpointValueLabel;

    QLabel *m_piIntegratorSaturationValue;

    QCheckBox *m_piRemoteControlCheckBox;

private slots:
    void computeUplinkDutyCycle();
    void setPIKp();
    void setPIKi();
    void setPISetpoint();
    void activatePIControlSimulation(bool on);
};

#endif // HEATERCONTROLTAB_H
