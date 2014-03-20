#ifndef GRAPHTAB_H
#define GRAPHTAB_H

#include <QWidget>

#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>

#include "qcustomplot.h"

class GraphTab : public QWidget
{
    Q_OBJECT
public:
    explicit GraphTab(QWidget *parent = 0);

signals:

public slots:

private:
    void plotSetup(void);
    void sidePanelSetup(void);

    QCustomPlot *m_plot;

    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_sidePanelLayout;
    QVBoxLayout *m_checkBoxLayout;

    QGroupBox *m_graphBox;

    QCheckBox *m_temp1CheckBox;
    QCheckBox *m_temp2CheckBox;
    QCheckBox *m_temp3CheckBox;
    QCheckBox *m_pressureCheckBox;
};

#endif // GRAPHTAB_H
