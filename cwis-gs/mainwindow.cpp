#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_dataBuffer = new QList<ControlModuleData>();

    m_centralWidget = new QWidget(this);
    m_statusPanel = new StatusPanel(this);
    m_tabWidget   = new QTabWidget(this);

    m_layout = new QGridLayout(m_centralWidget);

    m_graphTab = new GraphTab();
    m_tableTab = new TableTab();
    m_tabWidget->addTab(m_graphTab, tr("Timeline"));
    m_tabWidget->addTab(m_tableTab, tr("Data"));

    m_layout->addWidget(m_statusPanel, 0, 0);
    m_layout->addWidget(m_tabWidget, 0, 1);

    m_centralWidget->setLayout(m_layout);
    this->setCentralWidget(m_centralWidget);

    this->createActions();
    this->createMenus();

    m_sim = new SerialSim(this);
    QObject::connect(m_sim, SIGNAL(newData(ControlModuleData)),
                     this, SLOT(newData(ControlModuleData)));
    m_sim->start();
}

MainWindow::~MainWindow()
{
    delete m_graphTab;
    delete m_tableTab;

    delete m_dataBuffer;
}

void MainWindow::newData(ControlModuleData data)
{
    m_dataBuffer->append(data);

    m_tableTab->addData(data);
    m_graphTab->addData(data);
}

void MainWindow::clear()
{
    m_dataBuffer->clear();

    m_tableTab->clear();
    m_graphTab->clear();
}

void MainWindow::createMenus()
{
    m_fileMenu = this->menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_clearAction);
}

void MainWindow::createActions()
{
    m_clearAction = new QAction(tr("Clear"), this);
    QObject::connect(m_clearAction, SIGNAL(triggered()),
                     this, SLOT(clear()));
}
