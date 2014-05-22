#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableWidget>
#include <QGridLayout>
#include <QList>

#include "interface/graphtab.h"
#include "interface/heatercontroltab.h"
#include "interface/tabletab.h"
#include "interface/statuspanel.h"

#include "experiment/controlmoduledata.h"
#include "experiment/controlmoduleserialportlistener.h"

#include "serial/serialportconfig.h"
#include "serial/serialportdialog.h"
#include "test/serialsim.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void newData(ControlModuleData data);
    void clear();

private:
    void closeEvent(QCloseEvent *event);
    void createMenus();
    void createActions();
    void createStatusBar();

    void uplinkRequest(const char data[], int size);

    QList<ControlModuleData> *m_dataBuffer;

    QWidget *m_centralWidget;

    StatusPanel *m_statusPanel;

    QTabWidget *m_tabWidget;
    GraphTab *m_graphTab;
    HeaterControlTab *m_heaterTab;
    TableTab *m_tableTab;

    QGridLayout *m_layout;

    QMenu *m_fileMenu;
    QMenu *m_serialMenu;

    QAction *m_saveAction;
    QAction *m_clearAction;
    QAction *m_saveRawDataAction;
    QAction *m_loadRawDataAction;
    QAction *m_serialConfigAction;
    QAction *m_serialStartAction;
    QAction *m_serialStopAction;

    SerialPortConfig m_currentSerialConfig;
    SerialFrameDescriptor m_sfd;
    SerialPortDialog *m_serialConfigDlg;
    ControlModuleSerialPortListener *m_spListener;
    SerialSim *m_sim;

    QLabel *m_serialStatusLabel;
    QLabel *m_receivedFramesLabel;
    QLabel *m_serialDeviceLabel;

    int m_framesReceived;
    int m_framesDropped;

    bool m_downlinkActive;
    bool m_newData;

private slots:
    void updateStatusBar();
    void saveRecordedData();
    void loadRawData();
    void saveRawData();
    void handleInvalidSerialFrame();

    void uplinkLO();
    void uplinkSODS();
    void uplinkSOE();
    void uplinkLaser(bool);
    void uplinkHeater(int dutyCycle);

    bool serialConfigDlg();
    void startSerialCommunication();
    void stopSerialCommunication();
};

#endif // MAINWINDOW_H
