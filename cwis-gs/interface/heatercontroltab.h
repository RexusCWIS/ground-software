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

class HeaterControlTab : public QWidget
{
    Q_OBJECT
public:
    explicit HeaterControlTab(QWidget *parent = 0);

public slots:
    void addData(const ControlModuleData &data);

    void clear();

private:
    void plotSetup();
    void sidePanelSetup();

    DataPlot *m_plot;

    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_sidePanelLayout;
    QGridLayout *m_uplinkBoxLayout;

    QGroupBox *m_uplinkBox;

    QPushButton *m_rxsmLOButton;
    QPushButton *m_rxsmSODSButton;
    QPushButton *m_rxsmSOEButton;

    QLabel *m_heaterDutyCycleTextLabel;
    QLineEdit *m_heaterDutyCycleValueLabel;
};

#endif // HEATERCONTROLTAB_H
