#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "statustab.h"
#include "graphtab.h"
#include "timelinetab.h"
#include "serialportlistener.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        StatusTab *m_statusTab;
        GraphTab  *m_graphTab;
        TimelineTab *m_timelineTab;

        QGridLayout *m_layout;
        QWidget *m_centralWidget;

        SerialPortListener *m_spListener;
};

#endif // MAINWINDOW_H
