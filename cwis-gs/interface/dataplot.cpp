#include "dataplot.h"

DataPlot::DataPlot(QWidget *parent) :
    QCustomPlot(parent)
{
    m_autoRange = false;
    m_autoRangeValue  = 10.0;
    m_autoRangeOffset = 1.0;
    xAxis->setRange(0, m_autoRangeValue);

    this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
    this->axisRect()->setRangeDrag(Qt::Horizontal);
}

void DataPlot::setAutoRangeValue(double range)
{
    m_autoRangeValue = range;

    if(m_autoRange) {
        this->updateRange(xAxis->range().upper - m_autoRangeOffset);
    }
}

void DataPlot::setAutoRangeOffset(double offset)
{
    m_autoRangeOffset = offset;
}

void DataPlot::setAutoRange(bool on)
{
    m_autoRange = on;

    if(m_autoRange) {
        this->setInteractions(QCP::iSelectPlottables);
        this->xAxis->setAutoTickStep(false);
        this->xAxis->setTickStep(m_autoRangeValue/5.0);
        this->xAxis->setAutoSubTicks(false);
        this->xAxis->setSubTickCount(10);
    }

    else {
        this->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);
        this->xAxis->setAutoTickStep(true);
        this->xAxis->setAutoSubTicks(true);
    }

    this->updateRange(xAxis->range().upper - m_autoRangeOffset);
}

void DataPlot::setAutoRange(double range, double offset)
{
    m_autoRangeValue  = range;
    m_autoRangeOffset = offset;

    this->setAutoRange(true);
}

void DataPlot::updateRange(double max)
{
    if(m_autoRange) {
        if(max > (m_autoRangeValue - m_autoRangeOffset)) {
            xAxis->setRange(max + m_autoRangeOffset, m_autoRangeValue, Qt::AlignRight);
        }

        else {
            xAxis->setRange(0, m_autoRangeValue);
        }
    }

    else {
        xAxis->setRangeUpper(max + m_autoRangeOffset);
    }

    this->replot();
}
