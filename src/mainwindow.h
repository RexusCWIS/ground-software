#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QFileDialog>

#include "statustab.h"
#include "graphtab.h"

#include "serial/serialportdialog.h"
#include "controlmoduleserialportlistener.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    public slots:
        void openSaveFileDlg(void);
        void showSerialConfigDlg(void);

    private:
        void createActions(void);
        void createMenus(void);

        StatusTab *m_statusTab;
        GraphTab  *m_graphTab;

        QGridLayout *m_layout;
        QWidget *m_centralWidget;

        QMenu *m_fileMenu;
        QMenu *m_configMenu;

        QAction *m_saveAction;
        QAction *m_serialConfigAction;

        SerialPortDialog *m_serialConfigDlg;

        ControlModuleSerialPortListener *m_spListener;
        const SerialFrameDescriptor m_sfd;
};

#endif // MAINWINDOW_H
