#ifndef HEATERCONTROLTAB_H
#define HEATERCONTROLTAB_H

#include <QWidget>

#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "qcustomplot.h"

#include "experiment/controlmoduledata.h"

class HeaterControlTab : public QWidget
{
    Q_OBJECT
public:
    explicit HeaterControlTab(QWidget *parent = 0);

public slots:
    void addData(const ControlModuleData &data);

    void clear();

    void rangeAutoScroll(bool scroll);

private:
    void plotSetup();

    QCustomPlot *m_plot;
    int m_xAxisRange;
    bool m_rangeAutoScroll;

    QHBoxLayout *m_mainLayout;
};

#endif // HEATERCONTROLTAB_H
