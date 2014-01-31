#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_centralWidget = new QWidget(this);

    m_statusTab   = new StatusTab(m_centralWidget);
    m_graphTab    = new GraphTab(m_centralWidget);
    m_timelineTab = new TimelineTab(m_centralWidget);

    m_spListener  = new SerialPortListener(this);

    m_statusTab->setSerialPortListener(m_spListener);

    m_layout = new QGridLayout(m_centralWidget);
    m_layout->addWidget(m_statusTab, 0, 0);
    m_layout->addWidget(m_graphTab, 0, 1);
    m_layout->addWidget(m_timelineTab, 1, 1);
    m_centralWidget->setLayout(m_layout);

    QObject::connect(m_spListener, SIGNAL(newStatus(unsigned char)), m_statusTab, SLOT(refresh(unsigned char)));
    QObject::connect(m_spListener, SIGNAL(newSensorData(ExperimentData_s)), m_graphTab, SLOT(refresh(ExperimentData_s)));

    this->setCentralWidget(m_centralWidget);
}

MainWindow::~MainWindow() {

}
