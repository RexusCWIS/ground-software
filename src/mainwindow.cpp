#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_centralWidget = new QWidget(this);

    m_statusTab   = new StatusTab(m_centralWidget);
    m_graphTab    = new GraphTab(m_centralWidget);
    m_timelineTab = new TimelineTab(m_centralWidget);

    m_spListener  = new SerialPortListener();

    m_statusTab->setSerialPortListener(m_spListener);

    m_layout = new QGridLayout(m_centralWidget);
    m_layout->addWidget(m_statusTab, 0, 0);
    m_layout->addWidget(m_graphTab, 0, 1);
    m_layout->addWidget(m_timelineTab, 1, 1);
    m_centralWidget->setLayout(m_layout);

    this->setCentralWidget(m_centralWidget);
}

MainWindow::~MainWindow() {

}
