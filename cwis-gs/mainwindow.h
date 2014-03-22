#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableWidget>
#include <QGridLayout>
#include <QList>

#include "interface/graphtab.h"
#include "interface/tabletab.h"
#include "interface/statuspanel.h"

#include "experiment/controlmoduledata.h"

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
    void createMenus();
    void createActions();

    QList<ControlModuleData> *m_dataBuffer;

    QWidget *m_centralWidget;

    StatusPanel *m_statusPanel;

    QTabWidget *m_tabWidget;
    GraphTab *m_graphTab;
    TableTab *m_tableTab;

    QGridLayout *m_layout;

    QMenu *m_fileMenu;
    QMenu *m_serialMenu;

    QAction *m_clearAction;
    QAction *m_serialStartAction;
    QAction *m_serialStopAction;

    SerialSim *m_sim;
};

#endif // MAINWINDOW_H
