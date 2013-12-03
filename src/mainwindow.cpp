#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_centralWidget = new QWidget(this);

    m_statusTab = new StatusTab(m_centralWidget);
    m_graphTab  = new GraphTab(this);

    m_layout = new QGridLayout(m_centralWidget);
    m_layout->addWidget(m_statusTab, 0, 0);
    m_layout->addWidget(m_graphTab, 0, 1);
    m_centralWidget->setLayout(m_layout);

    this->setCentralWidget(m_centralWidget);
}

MainWindow::~MainWindow() {

}
