#include "graphtab.h"

#include "interface.h"

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
    double temp1 = data.getTemperature(0);
    double temp2 = data.getTemperature(1);
    double temp3 = data.getTemperature(2);
    double pressure = data.getPressure();
    double heating = data.getHeating();

    /* Cell temperature */
    m_plot->graph(0)->addData(time, temp1);
    m_plot->graph(1)->clearData();
    m_plot->graph(1)->addData(time, temp1);

    /* Room temperature */
    m_plot->graph(2)->addData(time, temp2);
    m_plot->graph(3)->clearData();
    m_plot->graph(3)->addData(time, temp2);

    /* Room temperature */
    m_plot->graph(4)->addData(time, temp3);
    m_plot->graph(5)->clearData();
    m_plot->graph(5)->addData(time, temp3);

    /* Room temperature */
    m_plot->graph(6)->addData(time, pressure);
    m_plot->graph(7)->clearData();
    m_plot->graph(7)->addData(time, pressure);

    m_plot->updateRange(time);

    m_plot->replot();

    m_temp1ValueLabel->setText(tr("%1").arg(temp1, 0, 'f', 1) +
                               QString::fromUtf8(" \u00B0C"));
    m_temp2ValueLabel->setText(tr("%1").arg(temp2, 0, 'f', 1) +
                               QString::fromUtf8(" \u00B0C"));
    m_temp3ValueLabel->setText(tr("%1").arg(temp3, 0, 'f', 1) +
                               QString::fromUtf8(" \u00B0C"));
    m_pressureValueLabel->setText(tr("%1 atm").arg(pressure, 0, 'f', 2));
    m_gradientValueLabel->setText(tr("%1").arg((temp1 - temp3), 0, 'f', 1) +
                               QString::fromUtf8(" \u00B0C"));
    m_heatingValueLabel->setText(tr("%1%").arg(heating, 0, 'f', 1));
}

void GraphTab::clear()
{
    for(int index = 0; index < 8; index++) {
        m_plot->graph(index)->clearData();
    }

    m_plot->replot();

    m_temp1ValueLabel->setText(tr("N/A"));
    m_temp2ValueLabel->setText(tr("N/A"));
    m_temp3ValueLabel->setText(tr("N/A"));
    m_pressureValueLabel->setText(tr("N/A"));
    m_gradientValueLabel->setText(tr("N/A"));
    m_heatingValueLabel->setText(tr("N/A"));
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

void GraphTab::showHeating(bool show)
{
    m_plot->graph(8)->setVisible(show);
    m_plot->graph(9)->setVisible(show);
}

void GraphTab::plotSetup(void)
{
    m_plot = new DataPlot(this);

    m_plot->activateMouseOverToolTip(true);

    QFont legendFont = this->font();
    legendFont.setPointSize(9);
    m_plot->legend->setFont(legendFont);
    legendFont.setItalic(true);
    m_plot->legend->setSelectedFont(legendFont);
    m_plot->legend->setSelectedTextColor(QColor(Qt::black));

    m_plot->xAxis->setLabel("Time [s]");
    m_plot->xAxis->setRange(0, 100);
    m_plot->yAxis->setLabel("Temperature [Celsius]");
    m_plot->yAxis->setRange(0, 60);
    m_plot->yAxis->setAutoTickStep(false);
    m_plot->yAxis->setTickStep(10.0);
    m_plot->yAxis2->setLabel(tr("Pressure"));
    m_plot->yAxis2->setRange(0, 1.05);
    m_plot->yAxis2->setAutoTickStep(false);
    m_plot->yAxis2->setTickStep(0.2);
    m_plot->yAxis2->setVisible(true);

    /* Cell temperature 1 line */
    m_plot->addGraph();
    m_plot->graph(0)->setPen(QPen(Qt::darkRed));
    m_plot->graph(0)->setName(TEMPERATURE1_STRING);
    m_plot->graph(0)->addToLegend();

    /* Cell temperature 1 dot */
    m_plot->addGraph();
    m_plot->graph(1)->setPen(QPen(Qt::darkRed));
    m_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(1)->setSelectable(false);
    m_plot->graph(1)->removeFromLegend();

    /* Cell temperature 2 line */
    m_plot->addGraph();
    m_plot->graph(2)->setPen(QPen(Qt::darkCyan));
    m_plot->graph(2)->setName(TEMPERATURE2_STRING);
    m_plot->graph(2)->addToLegend();

    /* Cell temperature 2 dot */
    m_plot->addGraph();
    m_plot->graph(3)->setPen(QPen(Qt::darkCyan));
    m_plot->graph(3)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(3)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(3)->setSelectable(false);
    m_plot->graph(3)->removeFromLegend();

    /* Room temperature line */
    m_plot->addGraph();
    m_plot->graph(4)->setPen(QPen(Qt::darkGreen));
    m_plot->graph(4)->setName(TEMPERATURE3_STRING);
    m_plot->graph(4)->addToLegend();

    /* Room temperature dot */
    m_plot->addGraph();
    m_plot->graph(5)->setPen(QPen(Qt::darkGreen));
    m_plot->graph(5)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(5)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(5)->setSelectable(false);
    m_plot->graph(5)->removeFromLegend();

    /* Pressure line */
    m_plot->addGraph(m_plot->xAxis, m_plot->yAxis2);
    m_plot->graph(6)->setPen(QPen(Qt::darkMagenta));
    m_plot->graph(6)->setName(PRESSURE_STRING);
    m_plot->graph(6)->addToLegend();

    /* Pressure dot */
    m_plot->addGraph(m_plot->xAxis, m_plot->yAxis2);
    m_plot->graph(7)->setPen(QPen(Qt::darkMagenta));
    m_plot->graph(7)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(7)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(7)->setSelectable(false);
    m_plot->graph(7)->removeFromLegend();

    /* Title */
    m_plot->plotLayout()->insertRow(0);
    m_plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_plot, "Experiment Timeline"));
    m_plot->setMinimumSize(400, 300);

    m_plot->setAutoRange(100, 5);

    m_plot->replot();
}

void GraphTab::sidePanelSetup(void)
{
    m_sidePanelLayout = new QVBoxLayout();

    m_graphBox = new QGroupBox(tr("Plots"), this);
    m_checkBoxLayout = new QVBoxLayout(m_graphBox);
    m_graphBox->setLayout(m_checkBoxLayout);

    m_globalView = new QRadioButton(tr("Global view"), m_graphBox);
    m_autoScrollView = new QRadioButton(tr("Auto-scroll"), m_graphBox);

    QObject::connect(m_autoScrollView, SIGNAL(toggled(bool)),
                     m_plot, SLOT(setAutoRange(bool)));

    m_autoScrollView->setChecked(true);

    m_temp1CheckBox = new QCheckBox(TEMPERATURE1_STRING, m_graphBox);
    m_temp2CheckBox = new QCheckBox(TEMPERATURE2_STRING, m_graphBox);
    m_temp3CheckBox = new QCheckBox(TEMPERATURE3_STRING, m_graphBox);
    m_pressureCheckBox = new QCheckBox(PRESSURE_STRING, m_graphBox);

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

    m_dataBox = new QGroupBox(trUtf8("Real-time values"), this);
    m_dataBoxLayout = new QGridLayout(m_dataBox);
    m_dataBox->setLayout(m_dataBoxLayout);

    m_temp1TextLabel = new QLabel(TEMPERATURE1_STRING, m_dataBox);
    m_temp2TextLabel = new QLabel(TEMPERATURE2_STRING, m_dataBox);
    m_temp3TextLabel = new QLabel(TEMPERATURE3_STRING, m_dataBox);
    m_pressureTextLabel = new QLabel(PRESSURE_STRING, m_dataBox);
    m_gradientTextLabel = new QLabel(tr("Temperature gradient"), m_dataBox);
    m_heatingTextLabel  = new QLabel(tr("Heating"), m_dataBox);

    m_temp1ValueLabel = new QLabel(m_dataBox);
    m_temp2ValueLabel = new QLabel(m_dataBox);
    m_temp3ValueLabel = new QLabel(m_dataBox);
    m_pressureValueLabel = new QLabel(m_dataBox);
    m_gradientValueLabel = new QLabel(m_dataBox);
    m_heatingValueLabel  = new QLabel(m_dataBox);

    m_temp1TextLabel->setBuddy(m_temp1ValueLabel);
    m_temp2TextLabel->setBuddy(m_temp2ValueLabel);
    m_temp3TextLabel->setBuddy(m_temp3ValueLabel);
    m_pressureTextLabel->setBuddy(m_pressureValueLabel);
    m_gradientTextLabel->setBuddy(m_gradientValueLabel);
    m_heatingTextLabel->setBuddy(m_heatingValueLabel);

    QFont font = m_temp1ValueLabel->font();
    font.setBold(true);
    m_temp1ValueLabel->setFont(font);
    m_temp2ValueLabel->setFont(font);
    m_temp3ValueLabel->setFont(font);
    m_pressureValueLabel->setFont(font);
    m_gradientValueLabel->setFont(font);
    m_heatingValueLabel->setFont(font);

    /* Avoid ulterior size changes due to larger texts */
    m_pressureValueLabel->setText("1.00 atm");
    QSize sizeHint = m_pressureValueLabel->sizeHint();
    m_pressureValueLabel->setMinimumSize(sizeHint);

    m_temp1ValueLabel->setText(tr("N/A"));
    m_temp2ValueLabel->setText(tr("N/A"));
    m_temp3ValueLabel->setText(tr("N/A"));
    m_pressureValueLabel->setText(tr("N/A"));
    m_gradientValueLabel->setText(tr("N/A"));
    m_heatingValueLabel->setText(tr("N/A"));

    m_dataBoxLayout->addWidget(m_temp1TextLabel, 0, 0);
    m_dataBoxLayout->addWidget(m_temp1ValueLabel, 0, 1);
    m_dataBoxLayout->addWidget(m_temp2TextLabel, 1, 0);
    m_dataBoxLayout->addWidget(m_temp2ValueLabel, 1, 1);
    m_dataBoxLayout->addWidget(m_temp3TextLabel, 2, 0);
    m_dataBoxLayout->addWidget(m_temp3ValueLabel, 2, 1);
    m_dataBoxLayout->addWidget(m_pressureTextLabel, 3, 0);
    m_dataBoxLayout->addWidget(m_pressureValueLabel, 3, 1);
    m_dataBoxLayout->addWidget(m_gradientTextLabel, 4, 0);
    m_dataBoxLayout->addWidget(m_gradientValueLabel, 4, 1);
    m_dataBoxLayout->addWidget(m_heatingTextLabel, 5, 0);
    m_dataBoxLayout->addWidget(m_heatingValueLabel, 5, 1);

    m_sidePanelLayout->addWidget(m_graphBox);
    m_sidePanelLayout->addWidget(m_dataBox);
    m_sidePanelLayout->addStretch(1);
}
