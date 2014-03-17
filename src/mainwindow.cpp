#include "mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    m_sfd(20, "UU", SerialFrameDescriptor::CRC16_CCITT)
{
    m_centralWidget = new QWidget(this);

    m_statusTab   = new StatusTab(m_centralWidget);
    m_graphTab    = new GraphTab(m_centralWidget);

    /* Serial port structures */
    m_spListener  = new ControlModuleSerialPortListener(this);
    m_spListener->setSerialFrameDescriptor(m_sfd);
    m_serialConfigDlg = new SerialPortDialog();

    m_layout = new QGridLayout(m_centralWidget);
    m_layout->addWidget(m_statusTab, 0, 0);
    m_layout->addWidget(m_graphTab, 0, 1);
    m_centralWidget->setLayout(m_layout);

    QObject::connect(m_spListener, SIGNAL(newStatus(unsigned char, unsigned char)), m_statusTab, SLOT(refresh(unsigned char, unsigned char)));
    QObject::connect(m_spListener, SIGNAL(newData(ControlModuleData)), m_graphTab, SLOT(refresh(ControlModuleData)));

    this->setCentralWidget(m_centralWidget);

    this->createActions();
    this->createMenus();
}

MainWindow::~MainWindow() {
    delete m_serialConfigDlg;
}

void MainWindow::openSaveFileDlg(void) {

    QString filename = QFileDialog::getSaveFileName(this, tr("Save As..."), "", "*.csv");
    m_spListener->saveRecordedData(filename);
}

void MainWindow::showSerialConfigDlg(void) {

    int rvalue = m_serialConfigDlg->exec();

    if(rvalue == QDialog::Accepted) {

        const SerialPortConfig config = m_serialConfigDlg->getSerialPortConfig();
        qDebug() << "New serial configuration:\nDevice: " << config.device <<
                    "\nBaudrate: " << config.baudrate << "\nData bits: " <<
                    config.dataBits << "\nParity: " << config.parity <<
                    "\nStop bits: " << config.stopBits;

        m_spListener->setSerialPortConfig(config);
    }
}

void MainWindow::createActions(void) {
    m_saveAction = new QAction(tr("Save"), this);
    m_saveAction->setShortcut(QKeySequence::Save);
    QObject::connect(m_saveAction, SIGNAL(triggered()), this, SLOT(openSaveFileDlg()));

    m_serialConfigAction = new QAction(tr("Serial"), this);
    QObject::connect(m_serialConfigAction, SIGNAL(triggered()), this, SLOT(showSerialConfigDlg()));
}

void MainWindow::createMenus(void) {

    m_fileMenu   = this->menuBar()->addMenu(tr("&File"));
    m_fileMenu->addAction(m_saveAction);

    m_configMenu = this->menuBar()->addMenu(tr("&Config"));
    m_configMenu->addAction(m_serialConfigAction);
}
