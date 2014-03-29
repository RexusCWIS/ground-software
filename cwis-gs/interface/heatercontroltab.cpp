#include "heatercontroltab.h"

HeaterControlTab::HeaterControlTab(QWidget *parent) :
    QWidget(parent)
{
    this->plotSetup();

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addWidget(m_plot, 1);

    this->setLayout(m_mainLayout);
}

void HeaterControlTab::addData(const ControlModuleData &data)
{
    double time = data.getTime();
    double cellTemp1 = data.getTemperature(0);
    double cellTemp2 = data.getTemperature(1);

    /* Cell temperature */
    m_plot->graph(0)->addData(time, cellTemp1);
    m_plot->graph(1)->clearData();
    m_plot->graph(1)->addData(time, cellTemp1);

    /* Room temperature */
    m_plot->graph(2)->addData(time, cellTemp2);
    m_plot->graph(3)->clearData();
    m_plot->graph(3)->addData(time, cellTemp2);

    m_plot->updateRange(time);
}

void HeaterControlTab::clear()
{
    for(int index = 0; index < 4; index++) {
        m_plot->graph(index)->clearData();
    }

    m_plot->replot();
}

void HeaterControlTab::rangeAutoScroll(bool scroll)
{
    m_rangeAutoScroll = scroll;

    if(scroll) {
        m_plot->xAxis->setAutoSubTicks(false);
        m_plot->xAxis->setSubTickCount(10);
        m_plot->xAxis->setAutoTickStep(false);
        m_plot->xAxis->setTickStep(10.0);
    }

    else {
        m_plot->xAxis->setAutoSubTicks(true);
        m_plot->xAxis->setAutoTickStep(true);
    }
}

void HeaterControlTab::plotSetup()
{
    m_plot = new DataPlot(this);

    QFont legendFont = this->font();
    legendFont.setPointSize(9);
    m_plot->legend->setFont(legendFont);
    m_plot->legend->setVisible(true);

    m_plot->xAxis->setLabel("Time [s]");
    m_plot->xAxis->setRange(0, m_xAxisRange);
    m_plot->yAxis->setLabel("Temperature [Celsius]");
    m_plot->yAxis->setRange(0, 60);
    m_plot->yAxis->setAutoTickStep(false);
    m_plot->yAxis->setTickStep(10.0);
    m_plot->yAxis2->setLabel(tr("Heating [%]"));
    m_plot->yAxis2->setRange(0, 100);
    m_plot->yAxis2->setAutoTickStep(false);
    m_plot->yAxis2->setTickStep(10.0);
    m_plot->yAxis2->setVisible(true);

    /* Cell temperature 1 line */
    m_plot->addGraph();
    m_plot->graph(0)->setPen(QPen(Qt::darkRed));
    m_plot->graph(0)->setName(tr("Cell temperature 1"));
    m_plot->graph(0)->addToLegend();

    /* Cell temperature 1 dot */
    m_plot->addGraph();
    m_plot->graph(1)->setPen(QPen(Qt::darkRed));
    m_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(1)->removeFromLegend();

    /* Cell temperature 2 line */
    m_plot->addGraph();
    m_plot->graph(2)->setPen(QPen(Qt::darkCyan));
    m_plot->graph(2)->setName(tr("Cell temperature 2"));
    m_plot->graph(2)->addToLegend();

    /* Cell temperature 2 dot */
    m_plot->addGraph();
    m_plot->graph(3)->setPen(QPen(Qt::darkCyan));
    m_plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(3)->removeFromLegend();

    /* Title */
    m_plot->plotLayout()->insertRow(0);
    m_plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_plot, "Heater control"));
    m_plot->setMinimumSize(400, 300);

    m_plot->setAutoRange(50, 5);

    m_plot->xAxis->setAutoSubTicks(false);
    m_plot->xAxis->setSubTickCount(10);
    m_plot->xAxis->setAutoTickStep(false);
    m_plot->xAxis->setTickStep(10.0);

    m_plot->replot();
}
