#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>

#include "statustab.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        StatusTab *m_statusTab;
        QGridLayout *m_layout;
        QWidget *m_centralWidget;
};

#endif // MAINWINDOW_H
