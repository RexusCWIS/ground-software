#ifndef TIMELINETAB_H
#define TIMELINETAB_H

#include <QWidget>
#include <QVBoxLayout>
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
        QVBoxLayout *m_layout;

};

#endif // TIMELINETAB_H
