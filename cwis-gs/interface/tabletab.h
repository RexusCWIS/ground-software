#ifndef TABLETAB_H
#define TABLETAB_H

#include <QTableWidget>

#include "experiment/controlmoduledata.h"

class TableTab : public QTableWidget
{
    Q_OBJECT
public:
    explicit TableTab(QWidget *parent = 0);

signals:

public slots:
    void addData(const ControlModuleData &data);

private:

};

#endif // TABLETAB_H
