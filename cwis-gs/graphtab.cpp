#include "graphtab.h"

GraphTab::GraphTab(QWidget *parent) :
    QWidget(parent)
{
    m_temp1CheckBox = new QCheckBox(tr("Cell temperature"), this);
    m_temp2CheckBox = new QCheckBox(tr("Ambient temperature"), this);
    m_temp3CheckBox = new QCheckBox(tr("Temperature 3"), this);
    m_pressureCheckBox = new QCheckBox(tr("Pressure"), this);

    m_plot = new QCustomPlot(this);
    m_plot->addGraph();
    m_plot->xAxis->setLabel("Time [s]");
    m_plot->yAxis->setLabel("Temperature [°C]");
    m_plot->xAxis->setRange(0, 100);
    m_plot->yAxis->setRange(0, 100);
    m_plot->plotLayout()->insertRow(0);
    m_plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_plot, "Experiment Timeline"));
    m_plot->replot();

    m_mainLayout = new QHBoxLayout(this);
    m_checkBoxLayout = new QGridLayout();

    m_checkBoxLayout->addWidget(m_temp1CheckBox, 0, 0);
    m_checkBoxLayout->addWidget(m_temp2CheckBox, 1, 0);
    m_checkBoxLayout->addWidget(m_temp3CheckBox, 2, 0);
    m_checkBoxLayout->addWidget(m_pressureCheckBox, 3, 0);

    m_mainLayout->addLayout(m_checkBoxLayout);
    m_mainLayout->addWidget(m_plot, 1);

    this->setLayout(m_mainLayout);
}
