#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableWidget>
#include <QGridLayout>

#include "graphtab.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    QWidget *m_centralWidget;
    QTabWidget *m_tabWidget;
    GraphTab   *m_graphTab;

    QGridLayout *m_layout;
};

#endif // MAINWINDOW_H
