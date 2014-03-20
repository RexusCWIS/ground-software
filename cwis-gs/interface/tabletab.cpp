#include "tabletab.h"

#include <QStringList>
#include <QHeaderView>

TableTab::TableTab(QWidget *parent) :
    QTableWidget(parent)
{
    this->setColumnCount(8);
    this->setRowCount(100);

    QStringList header;
    header.append(tr("Time"));
    header.append(tr("Cell temperature"));
    header.append(tr("Room temperature"));
    header.append(tr("Temperature 3"));
    header.append(tr("Pressure"));
    header.append(tr("Control status"));
    header.append(tr("Camera status"));
    header.append(tr("Number of images"));

    this->setHorizontalHeaderLabels(header);
    this->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    this->setEditTriggers(QAbstractItemView::NoEditTriggers);
}
