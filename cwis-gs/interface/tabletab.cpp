#include "tabletab.h"

#include <QStringList>
#include <QHeaderView>

TableTab::TableTab(QWidget *parent) :
    QTableWidget(parent)
{
    this->setColumnCount(8);
    this->setRowCount(0);

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

void TableTab::addData(const ControlModuleData &data) {

    int row = this->rowCount();
    this->insertRow(row);

    QTableWidgetItem *time = new QTableWidgetItem(tr("%1").arg(data.time));
    QTableWidgetItem *cellTemp = new QTableWidgetItem(tr("%1").arg(data.getTemperature(0)));
    QTableWidgetItem *roomTemp = new QTableWidgetItem(tr("%1").arg(data.getTemperature(1)));
    QTableWidgetItem *temp3    = new QTableWidgetItem(tr("%1").arg(data.getTemperature(2)));
    QTableWidgetItem *pressure = new QTableWidgetItem(tr("%1").arg(data.getPressure()));
    QTableWidgetItem *controlStatus = new QTableWidgetItem(tr("%1").arg(data.controlModuleStatus));
    QTableWidgetItem *cameraStatus  = new QTableWidgetItem(tr("%1").arg(data.cameraModuleStatus));
    QTableWidgetItem *nbOfImages    = new QTableWidgetItem(tr("%1").arg(data.nbOfImages));

    this->setItem(row, 0, time);
    this->setItem(row, 1, cellTemp);
    this->setItem(row, 2, roomTemp);
    this->setItem(row, 3, temp3);
    this->setItem(row, 4, pressure);
    this->setItem(row, 5, controlStatus);
    this->setItem(row, 6, cameraStatus);
    this->setItem(row, 7, nbOfImages);

    this->scrollToBottom();
}
