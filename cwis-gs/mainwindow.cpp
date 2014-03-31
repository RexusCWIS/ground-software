#include "mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    m_dataBuffer = new QList<ControlModuleData>();

    m_centralWidget = new QWidget(this);
    m_statusPanel = new StatusPanel(this);
    m_tabWidget   = new QTabWidget(this);

    m_layout = new QGridLayout(m_centralWidget);

    m_graphTab  = new GraphTab();
    m_heaterTab = new HeaterControlTab();
    m_tableTab  = new TableTab();
    m_tabWidget->addTab(m_graphTab, tr("Timeline"));
    m_tabWidget->addTab(m_heaterTab, tr("Heater"));
    m_tabWidget->addTab(m_tableTab, tr("Data"));

    m_layout->addWidget(m_statusPanel, 0, 0);
    m_layout->addWidget(m_tabWidget, 0, 1);

    m_centralWidget->setLayout(m_layout);
    this->setCentralWidget(m_centralWidget);

    m_sim = new SerialSim(this);
    QObject::connect(m_sim, SIGNAL(newData(ControlModuleData)),
                     this, SLOT(newData(ControlModuleData)));
    QObject::connect(m_sim, SIGNAL(started()),
                     this, SLOT(updateStatusBar()));
    QObject::connect(m_sim, SIGNAL(finished()),
                     this, SLOT(updateStatusBar()));

    this->createActions();
    this->createMenus();

    this->createStatusBar();
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
    m_heaterTab->addData(data);
    m_graphTab->addData(data);

    m_downlinkActive = true;
    m_framesReceived++;
    this->updateStatusBar();
}

void MainWindow::clear()
{
    if(m_dataBuffer->isEmpty()) {
        return;
    }

    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this, tr("Clear acquired data"),
                                  tr("Are you sure you want to discard all acquired data?"),
                                  QMessageBox::Yes | QMessageBox::No);

    if(reply == QMessageBox::Yes) {
        m_dataBuffer->clear();
        m_tableTab->setRowCount(0);
        m_heaterTab->clear();
        m_graphTab->clear();
    }

    m_framesReceived = 0;
    m_framesDropped  = 0;
    this->updateStatusBar();
}

void MainWindow::createMenus()
{
    m_fileMenu = this->menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_saveAction);
    m_fileMenu->addAction(m_clearAction);
    m_saveAction->setShortcut(QKeySequence::Save);

    m_serialMenu = this->menuBar()->addMenu(tr("&Serial"));
    m_serialMenu->addAction(m_serialStartAction);
    m_serialMenu->addAction(m_serialStopAction);
    m_serialStartAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    m_serialStopAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
}

void MainWindow::createActions()
{
    m_saveAction  = new QAction(tr("&Save"), this);
    m_clearAction = new QAction(tr("&Clear"), this);
    QObject::connect(m_saveAction, SIGNAL(triggered()),
                     this, SLOT(saveRecordedData()));
    QObject::connect(m_clearAction, SIGNAL(triggered()),
                     this, SLOT(clear()));

    m_serialStartAction = new QAction(tr("Sta&rt"), this);
    m_serialStopAction  = new QAction(tr("S&top"), this);
    QObject::connect(m_serialStartAction, SIGNAL(triggered()),
                     m_sim, SLOT(start()));
    QObject::connect(m_serialStopAction, SIGNAL(triggered()),
                     m_sim, SLOT(stop()));
}

void MainWindow::createStatusBar()
{
    m_serialStatusLabel   = new QLabel(this);
    m_receivedFramesLabel = new QLabel(this);
    m_invalidFramesLabel  = new QLabel(this);


    statusBar()->addWidget(m_serialStatusLabel, 2);
    statusBar()->addWidget(m_receivedFramesLabel);
    statusBar()->addWidget(m_invalidFramesLabel, 3);

    m_downlinkActive = false;
    m_framesReceived = 0;
    m_framesDropped  = 0;
    this->updateStatusBar();
}

void MainWindow::updateStatusBar()
{
    if(m_sim->isRunning()) {

        if(m_sim->isActive()) {
            m_serialStatusLabel->setText(tr("Serial communication status: Active"));
        }

        else {
            m_serialStatusLabel->setText(tr("Serial communication status: Waiting"));
        }
    }

    else {
        m_serialStatusLabel->setText(tr("Serial communication status: Stopped"));
    }

    m_receivedFramesLabel->setText(tr("Frames received: %1").arg(m_framesReceived));
    m_invalidFramesLabel->setText(tr("Dropped: %1").arg(m_framesDropped));
}

void MainWindow::saveRecordedData()
{
    if(m_dataBuffer->isEmpty()) {
        return;
    }

    QString filename = QFileDialog::getSaveFileName(this, tr("Save As..."), QDir::homePath(), "CSV files (*.csv)");

    if(filename.isEmpty()) {
        return;
    }

    QFile file(filename);
    if(file.open(QFile::WriteOnly | QFile::Truncate)) {
        QTextStream out(&file);

        out << "System time\tTime [ms]\tTemperature 1\tTemperature2\tTemperature3\tPressure\tControl module status\tCamera module status\n";

        QList<ControlModuleData>::iterator item;
        for(item = m_dataBuffer->begin(); item != m_dataBuffer->end(); item++) {

            out << (*item).currentTime.toString("hh:mm:ss.zzz") << "\t" << (*item).time << "\t" << (*item).temperatures[0] << "\t" <<
                   (*item).temperatures[1] << "\t" << (*item).temperatures[2] << "\t" <<
                   (*item).pressure << (*item).controlModuleStatus << "\t" << (*item).cameraModuleStatus << "\n";
        }

        file.close();
    }
}
