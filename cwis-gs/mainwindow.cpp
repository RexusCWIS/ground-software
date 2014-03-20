#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_centralWidget = new QWidget(this);
    m_tabWidget = new QTabWidget(this);

    m_layout = new QGridLayout(m_centralWidget);

    m_graphTab = new GraphTab();
    m_tableTab = new TableTab();
    m_tabWidget->addTab(m_graphTab, tr("Timeline"));
    m_tabWidget->addTab(m_tableTab, tr("Data"));

    m_layout->addWidget(m_tabWidget, 0, 1);

    m_centralWidget->setLayout(m_layout);
    this->setCentralWidget(m_centralWidget);
}

MainWindow::~MainWindow()
{
    delete m_graphTab;
    delete m_tableTab;
}
