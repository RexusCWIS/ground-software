#include "graphtab.h"

GraphTab::GraphTab(QWidget *parent) :
    QWidget(parent)
{
    this->plotSetup();
    this->sidePanelSetup();

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addLayout(m_sidePanelLayout);
    m_mainLayout->addWidget(m_plot, 1);

    this->setLayout(m_mainLayout);
}

void GraphTab::addData(const ControlModuleData &data)
{
    double time = data.getTime();
    double cellTemp = data.getTemperature(0);
    double roomTemp = data.getTemperature(1);
    double temp3    = data.getTemperature(2);
    double pressure = data.getPressure();

    /* Cell temperature */
    m_plot->graph(0)->addData(time, cellTemp);
    m_plot->graph(1)->clearData();
    m_plot->graph(1)->addData(time, cellTemp);

    /* Room temperature */
    m_plot->graph(2)->addData(time, roomTemp);
    m_plot->graph(3)->clearData();
    m_plot->graph(3)->addData(time, roomTemp);

    /* Room temperature */
    m_plot->graph(4)->addData(time, temp3);
    m_plot->graph(5)->clearData();
    m_plot->graph(5)->addData(time, temp3);

    /* Room temperature */
    m_plot->graph(6)->addData(time, pressure);
    m_plot->graph(7)->clearData();
    m_plot->graph(7)->addData(time, pressure);

    if(time > m_xAxisRange - 5) {
        if(m_rangeAutoScroll) {
            m_plot->xAxis->setRange(time + 5, m_xAxisRange, Qt::AlignRight);
        }

        else {
            m_plot->xAxis->setRange(0, time + 5);
        }
    }
    m_plot->replot();
}

void GraphTab::clear()
{
    for(int index = 0; index < 8; index++) {
        m_plot->graph(index)->clearData();
    }

    m_plot->replot();
}

void GraphTab::showCellTemperature(bool show)
{
    m_plot->graph(0)->setVisible(show);
    m_plot->graph(1)->setVisible(show);
}

void GraphTab::showRoomTemperature(bool show)
{
    m_plot->graph(2)->setVisible(show);
    m_plot->graph(3)->setVisible(show);
}

void GraphTab::showTemperature3(bool show)
{
    m_plot->graph(4)->setVisible(show);
    m_plot->graph(5)->setVisible(show);
}

void GraphTab::showPressure(bool show)
{
    m_plot->graph(6)->setVisible(show);
    m_plot->graph(7)->setVisible(show);
}

void GraphTab::rangeAutoScroll(bool scroll)
{
    m_rangeAutoScroll = scroll;

    if(scroll) {
        m_plot->xAxis->setAutoSubTicks(false);
        m_plot->xAxis->setSubTickCount(10);
        m_plot->xAxis->setAutoTickStep(false);
        m_plot->xAxis->setTickStep(10.0);
    }

    else {
        m_plot->xAxis->setAutoSubTicks(true);
        m_plot->xAxis->setAutoTickStep(true);
    }
}

void GraphTab::plotSetup(void)
{
    m_xAxisRange = 50;

    m_plot = new QCustomPlot(this);

    QFont legendFont = this->font();
    legendFont.setPointSize(9);
    m_plot->legend->setFont(legendFont);
    // m_plot->legend->setVisible(true);

    m_plot->xAxis->setLabel("Time [s]");
    m_plot->xAxis->setRange(0, m_xAxisRange);
    m_plot->yAxis->setLabel("Temperature [Celsius]");
    m_plot->yAxis->setRange(0, 60);
    m_plot->yAxis->setAutoTickStep(false);
    m_plot->yAxis->setTickStep(10.0);
    m_plot->yAxis2->setLabel(tr("Pressure"));
    m_plot->yAxis2->setRange(0, 1.05);
    m_plot->yAxis2->setAutoTickStep(false);
    m_plot->yAxis2->setTickStep(0.2);
    m_plot->yAxis2->setVisible(true);

    /* Cell temperature line */
    m_plot->addGraph();
    m_plot->graph(0)->setPen(QPen(Qt::darkRed));
    m_plot->graph(0)->setName(tr("Cell temperature"));
    m_plot->graph(0)->addToLegend();

    /* Cell temperature dot */
    m_plot->addGraph();
    m_plot->graph(1)->setPen(QPen(Qt::darkRed));
    m_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(1)->removeFromLegend();

    /* Room temperature line */
    m_plot->addGraph();
    m_plot->graph(2)->setPen(QPen(Qt::darkCyan));
    m_plot->graph(2)->setName(tr("Room temperature"));
    m_plot->graph(2)->addToLegend();

    /* Room temperature dot */
    m_plot->addGraph();
    m_plot->graph(3)->setPen(QPen(Qt::darkCyan));
    m_plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(3)->removeFromLegend();

    /* Third temperature line */
    m_plot->addGraph();
    m_plot->graph(4)->setPen(QPen(Qt::darkGreen));
    m_plot->graph(4)->setName(tr("Temperature 3"));
    m_plot->graph(4)->addToLegend();

    /* Third temperature dot */
    m_plot->addGraph();
    m_plot->graph(5)->setPen(QPen(Qt::darkGreen));
    m_plot->graph(5)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(5)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(5)->removeFromLegend();

    /* Pressure line */
    m_plot->addGraph(m_plot->xAxis, m_plot->yAxis2);
    m_plot->graph(6)->setPen(QPen(Qt::darkMagenta));
    m_plot->graph(6)->setName(tr("Pressure"));
    m_plot->graph(6)->addToLegend();

    /* Pressure dot */
    m_plot->addGraph(m_plot->xAxis, m_plot->yAxis2);
    m_plot->graph(7)->setPen(QPen(Qt::darkMagenta));
    m_plot->graph(7)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(7)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(7)->removeFromLegend();

    /* Title */
    m_plot->plotLayout()->insertRow(0);
    m_plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_plot, "Experiment Timeline"));
    m_plot->setMinimumSize(400, 300);

    this->rangeAutoScroll(true);

    m_plot->replot();
}

void GraphTab::sidePanelSetup(void)
{
    m_sidePanelLayout = new QVBoxLayout;

    m_graphBox = new QGroupBox(tr("Plots"), this);
    m_checkBoxLayout = new QVBoxLayout(m_graphBox);
    m_graphBox->setLayout(m_checkBoxLayout);

    m_globalView = new QRadioButton(tr("Global view"), m_graphBox);
    m_autoScrollView = new QRadioButton(tr("Auto-scroll"), m_graphBox);

    QObject::connect(m_autoScrollView, SIGNAL(toggled(bool)),
                     this, SLOT(rangeAutoScroll(bool)));

    m_autoScrollView->setChecked(true);

    m_temp1CheckBox = new QCheckBox(tr("Cell temperature"), m_graphBox);
    m_temp2CheckBox = new QCheckBox(tr("Ambient temperature"), m_graphBox);
    m_temp3CheckBox = new QCheckBox(tr("Temperature 3"), m_graphBox);
    m_pressureCheckBox = new QCheckBox(tr("Pressure"), m_graphBox);

    m_temp1CheckBox->setChecked(true);
    m_temp2CheckBox->setChecked(true);
    m_temp3CheckBox->setChecked(true);
    m_pressureCheckBox->setChecked(true);

    QObject::connect(m_temp1CheckBox, SIGNAL(toggled(bool)),
                     this, SLOT(showCellTemperature(bool)));
    QObject::connect(m_temp2CheckBox, SIGNAL(toggled(bool)),
                     this, SLOT(showRoomTemperature(bool)));
    QObject::connect(m_temp3CheckBox, SIGNAL(toggled(bool)),
                     this, SLOT(showTemperature3(bool)));
    QObject::connect(m_pressureCheckBox, SIGNAL(toggled(bool)),
                     this, SLOT(showPressure(bool)));

    m_checkBoxLayout->addWidget(m_globalView);
    m_checkBoxLayout->addWidget(m_autoScrollView);

    m_checkBoxLayout->addWidget(m_temp1CheckBox);
    m_checkBoxLayout->addWidget(m_temp2CheckBox);
    m_checkBoxLayout->addWidget(m_temp3CheckBox);
    m_checkBoxLayout->addWidget(m_pressureCheckBox);

    m_sidePanelLayout->addWidget(m_graphBox);
    m_sidePanelLayout->addStretch(1);
}
