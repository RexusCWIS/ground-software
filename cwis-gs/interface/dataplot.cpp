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

    QObject::connect(this, SIGNAL(selectionChangedByUser()),
                     this, SLOT(updateLegend()));
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

void DataPlot::activateMouseOverToolTip(bool on)
{
    if(on) {
        this->setMouseTracking(true);
        QObject::connect(this, SIGNAL(mouseMove(QMouseEvent*)),
                         this, SLOT(displayToolTipOnSelectedGraph(QMouseEvent*)));
    }

    else {
        QObject::disconnect(this, SIGNAL(mouseMove(QMouseEvent*)),
                            this, SLOT(displayToolTipOnSelectedGraph(QMouseEvent*)));
    }
}

void DataPlot::enterEvent(QEvent *event)
{
    (void) event;
    this->legend->setVisible(true);
}

void DataPlot::leaveEvent(QEvent *event)
{
    (void) event;
    this->legend->setVisible(false);
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
        xAxis->setRange(0, max + m_autoRangeOffset);
    }

    this->replot();
}

void DataPlot::displayToolTipOnSelectedGraph(QMouseEvent *event)
{   
    QList<QCPGraph *> list = this->selectedGraphs();

    if(list.isEmpty()) {
        return;
    }

    QCPGraph *selected = list.first();

    double x = this->xAxis->pixelToCoord(event->pos().x());
    double time = 0, value = 0;

    bool ok  = false;
    double m = std::numeric_limits<double>::max();

    foreach(QCPData data, selected->data()->values())
    {
        double d = qAbs(x - data.key);

        if(d < m)
        {
            time = data.key;
            value = data.value;

            ok = true;
            m = d;
        }
    }

    if(ok) {
        QToolTip::hideText();
        QToolTip::showText(event->globalPos(),
                           tr("<table>"
                                "<tr>"
                                  "<th colspan=\"2\">%L1</th>"
                                "</tr>"
                                "<tr>"
                                  "<td>Time:</td>" "<td>%L2</td>"
                                "</tr>"
                                "<tr>"
                                  "<td>Value:</td>" "<td>%L3</td>"
                                "</tr>"
                              "</table>").
                           arg(selected->name().isEmpty() ? "..." : selected->name()).
                           arg(time, 0, 'f', 2).
                           arg(value, 0, 'f', 2));
    }
}

void DataPlot::updateLegend()
{
    QList<QCPAbstractLegendItem*> selectedLegendItems = legend->selectedItems();

    for(int index = 0; index < selectedLegendItems.size(); index++) {
        selectedLegendItems[index]->setSelected(false);
    }

    QList<QCPGraph *> list = this->selectedGraphs();

    if(list.isEmpty()) {
        return;
    }

    QCPGraph *selected = list.first();
    QCPPlottableLegendItem *selectedItem = legend->itemWithPlottable(selected);
    selectedItem->setSelected(true);
}
