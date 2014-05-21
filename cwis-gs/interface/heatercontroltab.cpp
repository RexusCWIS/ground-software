#include "heatercontroltab.h"

#include "interface.h"

HeaterControlTab::HeaterControlTab(QWidget *parent) :
    QWidget(parent)
{
    m_piController = new PIController(3.0, 0.00005, 100.0);
    m_piController->setOutputSaturation(0.0, 255.0);
    m_piController->setIntegratorSaturation(0.0, 255.0);
    m_piSetpoint = 0;
    m_simulatePIControl   = false;

    this->plotSetup();
    this->sidePanelSetup();

    m_mainLayout = new QHBoxLayout(this);
    m_mainLayout->addLayout(m_sidePanelLayout);
    m_mainLayout->addWidget(m_plot, 1);

    this->setLayout(m_mainLayout);
}

void HeaterControlTab::addData(const ControlModuleData &data)
{
    double time = data.getTime();
    double cellTemp1 = data.getTemperature(0);
    double cellTemp2 = data.getTemperature(1);
    double heating = data.getHeating();

    /* Cell temperature 1 */
    m_plot->graph(0)->addData(time, cellTemp1);
    m_plot->graph(1)->clearData();
    m_plot->graph(1)->addData(time, cellTemp1);

    /* Cell temperature 2 */
    m_plot->graph(2)->addData(time, cellTemp2);
    m_plot->graph(3)->clearData();
    m_plot->graph(3)->addData(time, cellTemp2);

    /* Heating */
    m_plot->graph(4)->addData(time, heating);
    m_plot->graph(5)->clearData();
    m_plot->graph(5)->addData(time, heating);

    if(m_simulatePIControl) {

        double setpoint = (m_piSetpoint + 10.0) * 1024.0 / 70.0;
        double simHeating = m_piController->loop(setpoint - data.temperatures[0]);
        double dutyCycle  = simHeating / 2.55;

        m_piOutputValueLabel->setText(tr("%1 %").arg(dutyCycle, 0, 'f', 2));
        m_piIntegratorSaturationValue->setText(tr("%1").arg(m_piController->integratorValue(), 0, 'f', 2));

        m_plot->graph(6)->addData(time, dutyCycle);
        m_plot->graph(7)->clearData();
        m_plot->graph(7)->addData(time, dutyCycle);
        m_plot->graph(8)->addData(time, m_piSetpoint);
        m_plot->graph(9)->clearData();
        m_plot->graph(9)->addData(time, m_piSetpoint);

        if(m_piRemoteControlCheckBox->isChecked()) {

            m_heaterDutyCycleValueLabel->setText(tr("%1").arg((int) simHeating));
            emit uplinkHeater(simHeating);
        }
    }

    m_plot->updateRange(time);

    m_temp1ValueLabel->setText(tr("%1").arg(cellTemp1, 0, 'f', 1) +
                               QString::fromUtf8(" \u00B0C"));
    m_temp2ValueLabel->setText(tr("%1").arg(cellTemp2, 0, 'f', 1) +
                               QString::fromUtf8(" \u00B0C"));
}

void HeaterControlTab::clear()
{
    for(int index = 0; index < 10; index++) {
        m_plot->graph(index)->clearData();
    }

    m_plot->replot();

    m_temp1ValueLabel->setText(tr("N/A"));
    m_temp2ValueLabel->setText(tr("N/A"));
}

void HeaterControlTab::plotSetup()
{
    m_plot = new DataPlot(this);

    QFont legendFont = this->font();
    legendFont.setPointSize(9);
    m_plot->legend->setFont(legendFont);
    legendFont.setItalic(true);
    m_plot->legend->setSelectedFont(legendFont);
    m_plot->legend->setSelectedTextColor(QColor(Qt::black));
    m_plot->legend->setVisible(true);

    m_plot->xAxis->setLabel("Time [s]");
    m_plot->yAxis->setLabel("Temperature [Celsius]");
    m_plot->yAxis->setRange(0, 60);
    m_plot->yAxis->setAutoTickStep(false);
    m_plot->yAxis->setTickStep(10.0);
    m_plot->yAxis2->setLabel(tr("Heating [%]"));
    m_plot->yAxis2->setRange(0, 100);
    m_plot->yAxis2->setAutoTickStep(false);
    m_plot->yAxis2->setTickStep(10.0);
    m_plot->yAxis2->setVisible(true);

    /* Cell temperature 1 line */
    m_plot->addGraph();
    m_plot->graph(0)->setPen(QPen(Qt::darkGreen));
    m_plot->graph(0)->setName(TEMPERATURE1_STRING);
    m_plot->graph(0)->addToLegend();

    /* Cell temperature 1 dot */
    m_plot->addGraph();
    m_plot->graph(1)->setPen(QPen(Qt::darkGreen));
    m_plot->graph(1)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(1)->setScatterStyle(QCPScatterStyle::ssDisc);
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
    m_plot->graph(3)->removeFromLegend();

    /* Heating line */
    m_plot->addGraph(m_plot->xAxis, m_plot->yAxis2);
    m_plot->graph(4)->setPen(QPen(Qt::red));
    m_plot->graph(4)->setName(tr("Heating PWM duty cycle (%)"));
    m_plot->graph(4)->addToLegend();

    /* Heating dot */
    m_plot->addGraph(m_plot->xAxis, m_plot->yAxis2);
    m_plot->graph(5)->setPen(QPen(Qt::red));
    m_plot->graph(5)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(5)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(5)->removeFromLegend();

    /* Simulated heating line */
    m_plot->addGraph(m_plot->xAxis, m_plot->yAxis2);
    m_plot->graph(6)->setPen(QPen(Qt::yellow));
    m_plot->graph(6)->setName(tr("Heating simulation (%)"));
    m_plot->graph(6)->setVisible(false);
    m_plot->graph(6)->removeFromLegend();

    /* Simulated heating dot */
    m_plot->addGraph(m_plot->xAxis, m_plot->yAxis2);
    m_plot->graph(7)->setPen(QPen(Qt::yellow));
    m_plot->graph(7)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(7)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(7)->setVisible(false);
    m_plot->graph(7)->removeFromLegend();

    /* Setpoint line */
    m_plot->addGraph();
    m_plot->graph(8)->setPen(QPen(Qt::gray));
    m_plot->graph(8)->setName(tr("Setpoint"));
    m_plot->graph(8)->setVisible(true);
    m_plot->graph(8)->removeFromLegend();

    /* Setpoint dot */
    m_plot->addGraph();
    m_plot->graph(9)->setPen(QPen(Qt::gray));
    m_plot->graph(9)->setLineStyle(QCPGraph::lsNone);
    m_plot->graph(9)->setScatterStyle(QCPScatterStyle::ssDisc);
    m_plot->graph(9)->setVisible(true);
    m_plot->graph(9)->removeFromLegend();

    /* Title */
    m_plot->plotLayout()->insertRow(0);
    m_plot->plotLayout()->addElement(0, 0, new QCPPlotTitle(m_plot, "Heater control"));
    m_plot->setMinimumSize(400, 300);

    m_plot->setAutoRange(100, 5);

    m_plot->replot();
}

void HeaterControlTab::sidePanelSetup()
{
    m_sidePanelLayout = new QVBoxLayout();

    m_uplinkBox = new QGroupBox(tr("Uplink"), this);
    m_uplinkBoxLayout = new QGridLayout(m_uplinkBox);
    m_uplinkBox->setLayout(m_uplinkBoxLayout);

    m_piControlBox = new QGroupBox(tr("PI Control simulation"), this);
    m_piControlBox->setCheckable(true);
    m_piControlBox->setChecked(false);
    m_piControlBoxLayout = new QGridLayout(m_piControlBox);
    m_piControlBox->setLayout(m_piControlBoxLayout);

    m_rxsmLOButton   = new QPushButton(tr("LO"), m_uplinkBox);
    m_rxsmSODSButton = new QPushButton(tr("SODS"), m_uplinkBox);
    m_rxsmSOEButton  = new QPushButton(tr("SOE"), m_uplinkBox);

    QObject::connect(m_rxsmLOButton, SIGNAL(clicked()),
                     this, SIGNAL(uplinkLO()));
    QObject::connect(m_rxsmSODSButton, SIGNAL(clicked()),
                     this, SIGNAL(uplinkSODS()));
    QObject::connect(m_rxsmSOEButton, SIGNAL(clicked()),
                     this, SIGNAL(uplinkSOE()));

    m_heaterDutyCycleTextLabel  = new QLabel(tr("Heater duty cycle: "), m_uplinkBox);
    m_heaterDutyCycleValueLabel = new QLineEdit(m_uplinkBox);

    m_heaterDutyCycleTextLabel->setBuddy(m_heaterDutyCycleValueLabel);
    QValidator *dutyCycleValidator = new QIntValidator(0, 255, m_uplinkBox);
    m_heaterDutyCycleValueLabel->setValidator(dutyCycleValidator);

    QObject::connect(m_heaterDutyCycleValueLabel, SIGNAL(returnPressed()),
                     this, SLOT(computeUplinkDutyCycle()));

    m_uplinkBoxLayout->addWidget(m_rxsmLOButton, 0, 0, 1, 2);
    m_uplinkBoxLayout->addWidget(m_rxsmSODSButton, 1, 0, 1, 2);
    m_uplinkBoxLayout->addWidget(m_rxsmSOEButton, 2, 0, 1, 2);
    m_uplinkBoxLayout->addWidget(m_heaterDutyCycleTextLabel, 3, 0);
    m_uplinkBoxLayout->addWidget(m_heaterDutyCycleValueLabel, 3, 1);

    m_piKpTextLabel = new QLabel(tr("Kp"), m_piControlBox);
    m_piKiTextLabel = new QLabel(tr("Ki"), m_piControlBox);
    m_piSetpointTextLabel = new QLabel(tr("Setpoint"), m_piControlBox);
    m_piOutputTextLabel = new QLabel(tr("Simulated output"), m_piControlBox);
    m_piIntegratorSaturationLabel = new QLabel(tr("Integrator"), m_piControlBox);

    m_piKpValueLabel = new QLineEdit(tr("%1").arg(m_piController->kp()), m_piControlBox);
    m_piKiValueLabel = new QLineEdit(tr("%1").arg(m_piController->ki()), m_piControlBox);
    m_piSetpointValueLabel = new QLineEdit(tr("%1").arg(m_piSetpoint), m_piControlBox);

    m_piOutputValueLabel = new QLabel(tr("N/A"), this);
    m_piIntegratorSaturationValue = new QLabel(tr("N/A"), this);

    m_piRemoteControlCheckBox = new QCheckBox(tr("Remote control"), this);

    QValidator *m_doubleValidator = new QDoubleValidator(m_piControlBox);
    m_piKpValueLabel->setValidator(m_doubleValidator);
    m_piKiValueLabel->setValidator(m_doubleValidator);
    m_piSetpointValueLabel->setValidator(m_doubleValidator);

    QObject::connect(m_piControlBox, SIGNAL(toggled(bool)),
                     this, SLOT(activatePIControlSimulation(bool)));
    QObject::connect(m_piKpValueLabel, SIGNAL(returnPressed()),
                     this, SLOT(setPIKp()));
    QObject::connect(m_piKiValueLabel, SIGNAL(returnPressed()),
                     this, SLOT(setPIKi()));
    QObject::connect(m_piSetpointValueLabel, SIGNAL(returnPressed()),
                     this, SLOT(setPISetpoint()));
    QObject::connect(m_piRemoteControlCheckBox, SIGNAL(toggled(bool)),
                     this, SLOT(remotePIControl(bool)));

    m_piControlBoxLayout->addWidget(m_piRemoteControlCheckBox, 0, 0, 1, 2, Qt::AlignCenter);
    m_piControlBoxLayout->addWidget(m_piKpTextLabel, 1, 0);
    m_piControlBoxLayout->addWidget(m_piKpValueLabel, 1, 1);
    m_piControlBoxLayout->addWidget(m_piKiTextLabel, 2, 0);
    m_piControlBoxLayout->addWidget(m_piKiValueLabel, 2, 1);
    m_piControlBoxLayout->addWidget(m_piSetpointTextLabel, 3, 0);
    m_piControlBoxLayout->addWidget(m_piSetpointValueLabel, 3, 1);
    m_piControlBoxLayout->addWidget(m_piOutputTextLabel, 4, 0);
    m_piControlBoxLayout->addWidget(m_piOutputValueLabel, 4, 1);
    m_piControlBoxLayout->addWidget(m_piIntegratorSaturationLabel, 5, 0);
    m_piControlBoxLayout->addWidget(m_piIntegratorSaturationValue, 5, 1);

    m_dataBox = new QGroupBox(trUtf8("Real-time values"), this);
    m_dataBoxLayout = new QGridLayout(m_dataBox);
    m_dataBox->setLayout(m_dataBoxLayout);

    m_temp1TextLabel = new QLabel(TEMPERATURE1_STRING, m_dataBox);
    m_temp2TextLabel = new QLabel(TEMPERATURE2_STRING, m_dataBox);
    m_temp1ValueLabel = new QLabel(m_dataBox);
    m_temp2ValueLabel = new QLabel(m_dataBox);
    m_temp1TextLabel->setBuddy(m_temp1ValueLabel);
    m_temp2TextLabel->setBuddy(m_temp2ValueLabel);

    QFont font = m_temp1ValueLabel->font();
    font.setBold(true);
    m_temp1ValueLabel->setFont(font);
    m_temp2ValueLabel->setFont(font);
    m_temp1ValueLabel->setText(tr("N/A"));
    m_temp2ValueLabel->setText(tr("N/A"));

    m_dataBoxLayout->addWidget(m_temp1TextLabel, 0, 0);
    m_dataBoxLayout->addWidget(m_temp1ValueLabel, 0, 1);
    m_dataBoxLayout->addWidget(m_temp2TextLabel, 1, 0);
    m_dataBoxLayout->addWidget(m_temp2ValueLabel, 1, 1);

    m_sidePanelLayout->addWidget(m_uplinkBox);
    m_sidePanelLayout->addWidget(m_piControlBox);
    m_sidePanelLayout->addWidget(m_dataBox);
    m_sidePanelLayout->addStretch(1);
}

void HeaterControlTab::computeUplinkDutyCycle()
{
    int dutyCycle = m_heaterDutyCycleValueLabel->text().toInt();
    emit uplinkHeater(dutyCycle);
}

void HeaterControlTab::remotePIControl(bool on)
{
    m_heaterDutyCycleValueLabel->setReadOnly(on);
}

void HeaterControlTab::setPIKp()
{
    m_piController->setKP(m_piKpValueLabel->text().toDouble());
}

void HeaterControlTab::setPIKi()
{
    m_piController->setKI(m_piKiValueLabel->text().toDouble());
}

void HeaterControlTab::setPISetpoint()
{
    m_piSetpoint = m_piSetpointValueLabel->text().toDouble();
    qDebug() << "New setpoint: " << m_piSetpoint;
}

void HeaterControlTab::activatePIControlSimulation(bool on)
{
    m_simulatePIControl = on;

    m_plot->graph(6)->setVisible(on);
    m_plot->graph(7)->setVisible(on);

    if(on) {
        m_plot->graph(6)->addToLegend();
        m_heaterDutyCycleValueLabel->setReadOnly(m_piRemoteControlCheckBox->isChecked());
    }

    else {
        m_plot->graph(6)->removeFromLegend();
        this->remotePIControl(false);
    }
}

