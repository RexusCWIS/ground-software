#include "timelinetab.h"

TimelineTab::TimelineTab(QWidget *parent) :
    QWidget(parent)
{
    m_timeline = new QCustomPlot(this);

    m_timeline->xAxis->setLabel("Time [s]");
    m_timeline->xAxis->setRange(0, 1000);
    m_timeline->plotLayout()->insertRow(0);
    m_timeline->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_timeline, "Experiment timeline"));
    m_timeline->replot();
}
