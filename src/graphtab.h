#ifndef GRAPHTAB_H
#define GRAPHTAB_H

#include <QWidget>
#include <QLabel>
#include <QGridLayout>
#include <QThread>

#include "qcustomplot.h"

#include "experiment.h"

class GraphTab : public QWidget
{
    Q_OBJECT
    public:
        explicit GraphTab(QWidget *parent = 0);
        ~GraphTab();

    signals:

    public slots:
        void refresh(const ExperimentData_s data);
        void clear(void);

    private:
        QCustomPlot *m_temperaturePlot1;
        QCustomPlot *m_temperaturePlot2;
        QCustomPlot *m_temperaturePlot3;
        QCustomPlot *m_pressurePlot;

        QGridLayout *m_layout;

        QThread m_workerThread;
};

#endif // GRAPHTAB_H
