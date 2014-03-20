#include "graphtab.h"

GraphTab::GraphTab(QWidget *parent) :
    QWidget(parent)
{
    this->plotSetup();
    this->sidePanelSetup();

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addLayout(m_sidePanelLayout);
    m_mainLayout->addWidget(m_plot, 1);

    this->setLayout(m_mainLayout);
}

void GraphTab::plotSetup(void)
{
    m_plot = new QCustomPlot(this);
    m_plot->addGraph();
    m_plot->xAxis->setLabel("Time [s]");
    m_plot->yAxis->setLabel("Temperature [°C]");
    m_plot->xAxis->setRange(0, 100);
    m_plot->yAxis->setRange(0, 100);
    m_plot->plotLayout()->insertRow(0);
    m_plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_plot, "Experiment Timeline"));
    m_plot->setMinimumSize(400, 300);
    m_plot->replot();
}

void GraphTab::sidePanelSetup(void)
{
    m_sidePanelLayout = new QVBoxLayout;

    m_graphBox = new QGroupBox(tr("Plots"), this);
    m_checkBoxLayout = new QVBoxLayout(m_graphBox);
    m_graphBox->setLayout(m_checkBoxLayout);

    m_temp1CheckBox = new QCheckBox(tr("Cell temperature"), this);
    m_temp2CheckBox = new QCheckBox(tr("Ambient temperature"), this);
    m_temp3CheckBox = new QCheckBox(tr("Temperature 3"), this);
    m_pressureCheckBox = new QCheckBox(tr("Pressure"), this);

    m_checkBoxLayout->addWidget(m_temp1CheckBox);
    m_checkBoxLayout->addWidget(m_temp2CheckBox);
    m_checkBoxLayout->addWidget(m_temp3CheckBox);
    m_checkBoxLayout->addWidget(m_pressureCheckBox);

    m_sidePanelLayout->addWidget(m_graphBox);
    m_sidePanelLayout->addStretch(1);
}
