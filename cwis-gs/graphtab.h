#ifndef GRAPHTAB_H
#define GRAPHTAB_H

#include <QWidget>

#include <QCheckBox>
#include <QHBoxLayout>
#include <QGridLayout>

#include "qcustomplot.h"

class GraphTab : public QWidget
{
    Q_OBJECT
public:
    explicit GraphTab(QWidget *parent = 0);

signals:

public slots:

private:
    QCustomPlot *m_plot;
    QHBoxLayout *m_mainLayout;
    QGridLayout *m_checkBoxLayout;

    QCheckBox *m_temp1CheckBox;
    QCheckBox *m_temp2CheckBox;
    QCheckBox *m_temp3CheckBox;
    QCheckBox *m_pressureCheckBox;
};

#endif // GRAPHTAB_H
