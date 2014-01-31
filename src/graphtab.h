#ifndef GRAPHTAB_H
#define GRAPHTAB_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>

#include "qcustomplot.h"

#include "experiment.h"

class GraphTab : public QWidget
{
    Q_OBJECT
    public:
        explicit GraphTab(QWidget *parent = 0);

    signals:

    public slots:
        void refresh(const ExperimentData_s data);

    private:
        QCustomPlot *m_temperaturePlot1;
        QCustomPlot *m_temperaturePlot2;
        QCustomPlot *m_temperaturePlot3;
        QCustomPlot *m_pressurePlot;

        QGridLayout *m_layout;
};

#endif // GRAPHTAB_H
