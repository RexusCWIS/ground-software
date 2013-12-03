#include "graphtab.h"
#include "experiment.h"
#include <QVector>

GraphTab::GraphTab(QWidget *parent) :
    QWidget(parent) {

    m_temperaturePlot1 = new QCustomPlot(this);
    m_temperaturePlot2 = new QCustomPlot(this);
    m_temperaturePlot3 = new QCustomPlot(this);
    m_pressurePlot = new QCustomPlot(this);

    m_temperaturePlot1->xAxis->setLabel("Time [s]");
    m_temperaturePlot1->yAxis->setLabel("Temperature [°C]");
    m_temperaturePlot1->xAxis->setRange(0, EXPERIMENT_DURATION);
    m_temperaturePlot1->yAxis->setRange(-20, 100);
    m_temperaturePlot1->plotLayout()->insertRow(0);
    m_temperaturePlot1->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_temperaturePlot1, "Temperature 1"));
    m_temperaturePlot1->replot();

    m_temperaturePlot2->xAxis->setLabel("Time [s]");
    m_temperaturePlot2->yAxis->setLabel("Temperature [°C]");
    m_temperaturePlot2->xAxis->setRange(0, EXPERIMENT_DURATION);
    m_temperaturePlot2->yAxis->setRange(-20, 100);
    m_temperaturePlot2->plotLayout()->insertRow(0);
    m_temperaturePlot2->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_temperaturePlot2, "Temperature 2"));
    m_temperaturePlot2->replot();

    m_temperaturePlot3->xAxis->setLabel("Time [s]");
    m_temperaturePlot3->yAxis->setLabel("Temperature [°C]");
    m_temperaturePlot3->xAxis->setRange(0, EXPERIMENT_DURATION);
    m_temperaturePlot3->yAxis->setRange(-20, 100);
    m_temperaturePlot3->plotLayout()->insertRow(0);
    m_temperaturePlot3->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_temperaturePlot3, "Temperature 3"));
    m_temperaturePlot3->replot();

    m_pressurePlot->xAxis->setLabel("Time [s]");
    m_pressurePlot->yAxis->setLabel("Pressure [atm]");
    m_pressurePlot->xAxis->setRange(0, EXPERIMENT_DURATION);
    m_pressurePlot->yAxis->setRange(-20, 100);
    m_pressurePlot->plotLayout()->insertRow(0);
    m_pressurePlot->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_pressurePlot, "Ambient pressure"));
    m_pressurePlot->replot();

    m_layout = new QGridLayout(this);

    m_layout->addWidget(m_temperaturePlot1, 0, 0);
    m_layout->addWidget(m_temperaturePlot2, 0, 1);
    m_layout->addWidget(m_temperaturePlot3, 1, 0);
    m_layout->addWidget(m_pressurePlot, 1, 1);

    this->setLayout(m_layout);
    this->setMinimumSize(800, 600);
}
