#ifndef GRAPHTAB_H
#define GRAPHTAB_H

#include <QWidget>

#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QRadioButton>

#include "qcustomplot.h"

#include "experiment/controlmoduledata.h"

class GraphTab : public QWidget
{
    Q_OBJECT
public:
    explicit GraphTab(QWidget *parent = 0);

signals:

public slots:
    void addData(const ControlModuleData &data);

    void showCellTemperature(bool show);
    void showRoomTemperature(bool show);
    void showTemperature3(bool show);
    void showPressure(bool show);

    void rangeAutoScroll(bool scroll);

private:
    void plotSetup(void);
    void sidePanelSetup(void);

    QCustomPlot *m_plot;
    int m_xAxisRange;
    bool m_rangeAutoScroll;

    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_sidePanelLayout;
    QVBoxLayout *m_checkBoxLayout;

    QGroupBox *m_graphBox;

    QRadioButton *m_globalView;
    QRadioButton *m_autoScrollView;

    QCheckBox *m_temp1CheckBox;
    QCheckBox *m_temp2CheckBox;
    QCheckBox *m_temp3CheckBox;
    QCheckBox *m_pressureCheckBox;
};

#endif // GRAPHTAB_H
