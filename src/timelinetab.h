#ifndef TIMELINETAB_H
#define TIMELINETAB_H

#include <QWidget>
#include "qcustomplot.h"

class TimelineTab : public QWidget
{
    Q_OBJECT
    public:
        explicit TimelineTab(QWidget *parent = 0);

    signals:

    public slots:

    private:
        QCustomPlot *m_timeline;
};

#endif // TIMELINETAB_H
