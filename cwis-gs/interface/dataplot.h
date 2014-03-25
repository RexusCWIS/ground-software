#ifndef DATAPLOT_H
#define DATAPLOT_H

#include "qcustomplot.h"

class DataPlot: public QCustomPlot
{
    Q_OBJECT
public:
    DataPlot(QWidget *parent = 0);

    void addGraph(QCPAxis *keyAxis, QCPAxis *valueAxis);

    void setAutoRangeValue(double range);
    void setAutoRangeOffset(double offset);

public slots:
    void setAutoRange(bool on);
    void updateRange(double max);

protected:
    bool m_autoRange;
    double m_autoRangeValue;
    double m_autoRangeOffset;
};

#endif // DATAPLOT_H
