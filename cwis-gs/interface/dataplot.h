#ifndef DATAPLOT_H
#define DATAPLOT_H

#include "qcustomplot.h"

class DataPlot: public QCustomPlot
{
    Q_OBJECT
public:
    DataPlot(QWidget *parent = 0);

    void setAutoRangeValue(double range);
    void setAutoRangeOffset(double offset);

    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

public slots:
    void setAutoRange(bool on);
    void setAutoRange(double range, double offset);
    void updateRange(double max);

protected:
    bool m_autoRange;
    double m_autoRangeValue;
    double m_autoRangeOffset;

protected slots:
    void displayToolTipOnSelectedGraph();
};

#endif // DATAPLOT_H
