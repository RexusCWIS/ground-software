#include "mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_sfd(24, "UU", SerialFrameDescriptor::CRC16_CCITT)
{
    m_dataBuffer = new QList<ControlModuleData>();
    m_newData = false;

    m_centralWidget = new QWidget(this);
    m_statusPanel = new StatusPanel(this);
    m_tabWidget   = new QTabWidget(this);

    m_layout = new QGridLayout(m_centralWidget);

    /* Tab widgets allocation */
    m_graphTab  = new GraphTab();
    m_heaterTab = new HeaterControlTab();
    m_tableTab  = new TableTab();
    m_tabWidget->addTab(m_graphTab, tr("Timeline"));
    m_tabWidget->addTab(m_heaterTab, tr("Heater"));
    m_tabWidget->addTab(m_tableTab, tr("Data"));

    QObject::connect(m_heaterTab, SIGNAL(uplinkLO()),
                     this, SLOT(uplinkLO()));
    QObject::connect(m_heaterTab, SIGNAL(uplinkSODS()),
                     this, SLOT(uplinkSODS()));
    QObject::connect(m_heaterTab, SIGNAL(uplinkSOE()),
                     this, SLOT(uplinkSOE()));
    QObject::connect(m_heaterTab, SIGNAL(uplinkLaser(bool)),
                     this, SLOT(uplinkLaser(bool)));
    QObject::connect(m_heaterTab, SIGNAL(uplinkHeater(int)),
                     this, SLOT(uplinkHeater(int)));


    m_layout->addWidget(m_statusPanel, 0, 0);
    m_layout->addWidget(m_tabWidget, 0, 1);

    m_centralWidget->setLayout(m_layout);
    this->setCentralWidget(m_centralWidget);

    m_spListener = new ControlModuleSerialPortListener(this);
    m_spListener->setSerialFrameDescriptor(m_sfd);

    // m_sim = new SerialSim(this);
    m_serialConfigDlg = new SerialPortDialog();
    m_currentSerialConfig.device = tr("");

    QObject::connect(m_spListener, SIGNAL(newData(ControlModuleData)),
                     this, SLOT(newData(ControlModuleData)));
    QObject::connect(m_spListener, SIGNAL(timeout()),
                     this, SLOT(updateStatusBar()));
    QObject::connect(m_spListener, SIGNAL(started()),
                     this, SLOT(updateStatusBar()));
    QObject::connect(m_spListener, SIGNAL(finished()),
                     this, SLOT(updateStatusBar()));
    QObject::connect(m_spListener, SIGNAL(frameDropped()),
                     this, SLOT(handleInvalidSerialFrame()));

    this->createActions();
    this->createMenus();

    this->createStatusBar();

    /* Window title creation */
    this->setUnifiedTitleAndToolBarOnMac(true);
    this->setWindowTitle(tr("CWIS Ground Software - Chemical Waves in Soret Effect"));
}

MainWindow::~MainWindow()
{
    m_spListener->stop();

    delete m_graphTab;
    delete m_heaterTab;
    delete m_tableTab;

    delete m_dataBuffer;

    delete m_serialConfigDlg;
}

void MainWindow::newData(ControlModuleData data)
{
    /* Store acquired data */
    m_dataBuffer->append(data);

    /* Display data */
    m_tableTab->addData(data);
    m_heaterTab->addData(data);
    m_graphTab->addData(data);

    /* Update status labels */
    m_statusPanel->updateStatus((int) data.controlModuleStatus, (int) data.cameraModuleStatus);
    m_statusPanel->updateNumberOfImages((int) data.nbOfImages);

    /* Serial communication status */
    m_downlinkActive = true;
    m_framesReceived++;
    this->updateStatusBar();

    m_newData = true;
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
        m_statusPanel->clear();
        m_tableTab->setRowCount(0);
        m_heaterTab->clear();
        m_graphTab->clear();
    }

    m_framesReceived = 0;
    m_framesDropped  = 0;
    this->updateStatusBar();
    statusBar()->showMessage(tr("Cleared all acquired data."), 2);
    m_newData = false;
}

void MainWindow::createMenus()
{
    m_fileMenu = this->menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_saveAction);
    m_fileMenu->addAction(m_saveRawDataAction);
    m_fileMenu->addAction(m_loadRawDataAction);
    m_fileMenu->addSeparator();
    m_fileMenu->addAction(m_clearAction);
    m_saveAction->setShortcut(QKeySequence::Save);

    m_serialMenu = this->menuBar()->addMenu(tr("&Serial"));
    m_serialMenu->addAction(m_serialConfigAction);
    m_serialMenu->addAction(m_serialStartAction);
    m_serialMenu->addAction(m_serialStopAction);
    m_serialStartAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_R));
    m_serialStopAction->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_T));
}

void MainWindow::createActions()
{
    m_saveAction  = new QAction(tr("&Save"), this);
    m_saveRawDataAction = new QAction(tr("Save raw data"), this);
    m_loadRawDataAction = new QAction(tr("Load raw data"), this);
    m_clearAction = new QAction(tr("&Clear"), this);
    QObject::connect(m_saveAction, SIGNAL(triggered()),
                     this, SLOT(saveRecordedData()));
    QObject::connect(m_saveRawDataAction, SIGNAL(triggered()),
                     this, SLOT(saveRawData()));
    QObject::connect(m_loadRawDataAction, SIGNAL(triggered()),
                     this, SLOT(loadRawData()));
    QObject::connect(m_clearAction, SIGNAL(triggered()),
                     this, SLOT(clear()));

    m_serialConfigAction = new QAction(tr("Configuration"), this);
    m_serialStartAction  = new QAction(tr("Sta&rt"), this);
    m_serialStopAction   = new QAction(tr("S&top"), this);
    m_serialConfigAction->setMenuRole(QAction::NoRole);
    QObject::connect(m_serialConfigAction, SIGNAL(triggered()),
                     this, SLOT(serialConfigDlg()));
    QObject::connect(m_serialStartAction, SIGNAL(triggered()),
                     this, SLOT(startSerialCommunication()));
    QObject::connect(m_serialStopAction, SIGNAL(triggered()),
                     this, SLOT(stopSerialCommunication()));
}

void MainWindow::createStatusBar()
{
    m_serialStatusLabel   = new QLabel(this);
    m_receivedFramesLabel = new QLabel(this);
    m_serialDeviceLabel   = new QLabel(this);

    m_receivedFramesLabel->setAlignment(Qt::AlignCenter);

    m_serialDeviceLabel->setAlignment(Qt::AlignRight);
    QFont font = m_serialDeviceLabel->font();
    font.setItalic(true);
    m_serialDeviceLabel->setFont(font);

    statusBar()->addWidget(m_serialStatusLabel, 1);
    statusBar()->addWidget(m_receivedFramesLabel, 1);
    statusBar()->addWidget(m_serialDeviceLabel, 1);

    m_downlinkActive = false;
    m_framesReceived = 0;
    m_framesDropped  = 0;
    this->updateStatusBar();
}

void MainWindow::uplinkRequest(const char data[], int size)
{
    QByteArray request(data, size);
    m_spListener->write(request);
}

void MainWindow::updateStatusBar()
{
    if(m_spListener->isRunning()) {

        if(m_spListener->isActive()) {
            m_serialStatusLabel->setText(tr("Serial communication status: Active"));
        }

        else {
            m_serialStatusLabel->setText(tr("Serial communication status: Waiting"));
        }
    }

    else {
        m_serialStatusLabel->setText(tr("Serial communication status: Stopped"));
    }

    m_receivedFramesLabel->setText(tr("Frames received: %1 dropped: %2").arg(m_framesReceived).arg(m_framesDropped));
    m_serialDeviceLabel->setText(m_currentSerialConfig.device);
}

void MainWindow::saveRecordedData()
{
    if(m_dataBuffer->isEmpty()) {
        return;
    }

    /** @bug On Mac OS X, the filter field is ignored. This is due to Qt. */
    QString filename = QFileDialog::getSaveFileName(this, tr("Save As..."), QDir::homePath(), tr("Text files (*.txt);;All files (*)"));

    if(filename.isEmpty()) {
        return;
    }

    QFile file(filename);
    if(file.open(QFile::WriteOnly | QFile::Truncate | QFile::Text)) {
        QTextStream out(&file);

        out << "System time\tTime [ms]\tTemperature 1\tTemperature2\tTemperature3\tPressure\tHeating\tControl module status\tCamera module status\n";

        QList<ControlModuleData>::iterator item;
        for(item = m_dataBuffer->begin(); item != m_dataBuffer->end(); item++) {

            out << (*item).currentTime.toString("hh:mm:ss.zzz") << "\t" << (*item).time << "\t" << (*item).temperatures[0] << "\t" <<
                   (*item).temperatures[1] << "\t" << (*item).temperatures[2] << "\t" <<
                   (*item).pressure << "\t" << (*item).heating << "\t" << (*item).controlModuleStatus << "\t" << (*item).cameraModuleStatus << "\n";
        }

        file.close();
        statusBar()->showMessage(tr("Saved data to %1.").arg(filename), 2);
        m_newData = false;
    }
}

void MainWindow::loadRawData()
{
    QString filename = QFileDialog::getOpenFileName(this, tr("Open raw data file"), QDir::homePath(), tr("Text files (*.txt);;All files (*)"));

    if(filename.isEmpty()) {
        return;
    }

    QFile file(filename);
    if(file.open(QFile::ReadOnly | QFile::Text)) {
        QTextStream in(&file);

        QString line;
        ControlModuleData data;

        while(!in.atEnd()) {
            line = in.readLine();
            QStringList elements = line.split(" ");

            data.time = (((unsigned int) elements.at(5).toInt()) << 24) + (((unsigned int) elements.at(4).toInt()) << 16) +
                    (((unsigned int) elements.at(3).toInt()) << 8) + ((unsigned int) elements.at(2).toInt());

            data.temperatures[0] = (((unsigned int) elements.at(7).toInt()) << 8) + ((unsigned int) elements.at(6).toInt());
            data.temperatures[1] = (((unsigned int) elements.at(9).toInt()) << 8) + ((unsigned int) elements.at(8).toInt());
            data.temperatures[2] = (((unsigned int) elements.at(11).toInt()) << 8) + ((unsigned int) elements.at(10).toInt());
            data.pressure = (((unsigned int) elements.at(13).toInt()) << 8) + ((unsigned int) elements.at(12).toInt());
            data.heating  = (unsigned int) elements.at(14).toInt();

            data.nbOfImages  = (((unsigned int) elements.at(16).toInt()) << 8) + ((unsigned int) elements.at(17).toInt());
            data.framerate   = (unsigned int) elements.at(18).toInt();
            data.controlModuleStatus = elements.at(15).toInt();
            data.cameraModuleStatus  = elements.at(19).toInt();

            data.currentTime = QTime::currentTime();

            this->newData(data);
        }
    }
}

void MainWindow::saveRawData()
{
    QString filename = QFileDialog::getSaveFileName(this, tr("Save As..."), QDir::homePath(), tr("Text files (*.txt);;All files (*)"));

    if(filename.isEmpty()) {
        return;
    }

    m_spListener->saveData(filename);
    statusBar()->showMessage(tr("Saved raw data frames to %1.").arg(filename), 2);
}

void MainWindow::handleInvalidSerialFrame()
{
    m_framesDropped++;
    this->updateStatusBar();
}

void MainWindow::uplinkLO()
{
    const char frame[4] = {UPLINK_RXSM_COMMAND, 0x1, 0, 0};
    this->uplinkRequest(frame, 4);
}

void MainWindow::uplinkSODS()
{
    const char frame[4] = {UPLINK_RXSM_COMMAND, 0x3, 0, 0};
    this->uplinkRequest(frame, 4);
}

void MainWindow::uplinkSOE()
{
    const char frame[4] = {UPLINK_RXSM_COMMAND, 0x5, 0, 0};
    this->uplinkRequest(frame, 4);
}

void MainWindow::uplinkLaser(bool on)
{
    char command = (on) ? 0xFF : 0x0;

    const char frame[4] = {UPLINK_LASER_COMMAND, command, 0, 0};
    this->uplinkRequest(frame, 4);
}

void MainWindow::uplinkHeater(int dutyCycle)
{
    const char frame[4] = {UPLINK_HEATER_COMMAND,
                           (char) (dutyCycle & 0xFF), 0, 0};
    this->uplinkRequest(frame, 4);
}

bool MainWindow::serialConfigDlg()
{
    int rvalue = m_serialConfigDlg->exec();

    bool configured = (rvalue == QDialog::Accepted);

    if(configured) {

        m_currentSerialConfig = m_serialConfigDlg->getSerialPortConfig();
        qDebug() << "New serial configuration:\nDevice: " << m_currentSerialConfig.device <<
                    "\nBaudrate: " << m_currentSerialConfig.baudrate << "\nData bits: " <<
                    m_currentSerialConfig.dataBits << "\nParity: " << m_currentSerialConfig.parity <<
                    "\nStop bits: " << m_currentSerialConfig.stopBits;

        m_spListener->setSerialPortConfig(m_currentSerialConfig);
    }

    return configured;
}

void MainWindow::startSerialCommunication()
{
    if(!m_spListener->isConfigured()) {
        if(this->serialConfigDlg()) {
            m_spListener->setSerialPortConfig(m_currentSerialConfig);
            m_spListener->start();
        }
    }

    else {
        m_spListener->start();
    }
}

void MainWindow::stopSerialCommunication()
{
    m_spListener->stop();
}

void MainWindow::closeEvent(QCloseEvent *event) {

    if(m_newData) {
        QMessageBox::StandardButton reply;
        reply = QMessageBox::warning(this, tr("Application"),
                                     tr("You have not saved the data.\n"
                                        "Save it?"),
                                     QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

        switch(reply) {
        case QMessageBox::Save:
            this->saveRecordedData();
            this->saveRawData();
        case QMessageBox::Discard:
            event->accept();
            break;
        default:
            event->ignore();
            break;
        }
    }
}
