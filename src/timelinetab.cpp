#include "timelinetab.h"
#include "experiment.h"

TimelineTab::TimelineTab(QWidget *parent) :
    QWidget(parent)
{
    m_timeline = new QCustomPlot(this);

    m_timeline->xAxis->setLabel("Time [s]");
    m_timeline->xAxis->setRange(0, EXPERIMENT_DURATION);
    m_timeline->yAxis->setVisible(false);
    m_timeline->plotLayout()->insertRow(0);
    m_timeline->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_timeline, "Experiment timeline"));
    m_timeline->replot();

    m_layout = new QVBoxLayout(this);
    m_layout->addWidget(m_timeline);

    this->setLayout(m_layout);
    this->setMinimumSize(800, 200);
}
