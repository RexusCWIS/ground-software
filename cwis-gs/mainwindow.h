#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableWidget>
#include <QGridLayout>

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

private:
    QWidget *m_centralWidget;

    StatusPanel *m_statusPanel;

    QTabWidget *m_tabWidget;
    GraphTab *m_graphTab;
    TableTab *m_tableTab;

    QGridLayout *m_layout;

    SerialSim *m_sim;
};

#endif // MAINWINDOW_H
