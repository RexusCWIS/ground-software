#ifndef GRAPHTAB_H
#define GRAPHTAB_H

#include <QWidget>

#include <QCheckBox>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QRadioButton>

#include "dataplot.h"

#include "experiment/controlmoduledata.h"

class GraphTab : public QWidget
{
    Q_OBJECT
public:
    explicit GraphTab(QWidget *parent = 0);

signals:

public slots:
    void addData(const ControlModuleData &data);
    void clear(void);

    void showCellTemperature(bool show);
    void showRoomTemperature(bool show);
    void showTemperature3(bool show);
    void showPressure(bool show);

private:
    void plotSetup(void);
    void sidePanelSetup(void);

    DataPlot *m_plot;

    QHBoxLayout *m_mainLayout;
    QVBoxLayout *m_sidePanelLayout;
    QVBoxLayout *m_checkBoxLayout;
    QGridLayout *m_dataBoxLayout;

    QGroupBox *m_graphBox;
    QGroupBox *m_dataBox;
    QGroupBox *m_piControlBox;

    QRadioButton *m_globalView;
    QRadioButton *m_autoScrollView;

    QCheckBox *m_temp1CheckBox;
    QCheckBox *m_temp2CheckBox;
    QCheckBox *m_temp3CheckBox;
    QCheckBox *m_pressureCheckBox;

    QLabel *m_temp1TextLabel;
    QLabel *m_temp2TextLabel;
    QLabel *m_temp3TextLabel;
    QLabel *m_pressureTextLabel;

    QLabel *m_temp1ValueLabel;
    QLabel *m_temp2ValueLabel;
    QLabel *m_temp3ValueLabel;
    QLabel *m_pressureValueLabel;
};

#endif // GRAPHTAB_H
