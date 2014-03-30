#include "tabletab.h"

#include "interface.h"

#include <QStringList>
#include <QHeaderView>

TableTab::TableTab(QWidget *parent) :
    QTableWidget(parent)
{
    this->setColumnCount(9);
    this->setRowCount(0);

    QStringList header;
    header.append(tr("Current time"));
    header.append(tr("Module time"));
    header.append(TEMPERATURE1_STRING);
    header.append(TEMPERATURE2_STRING);
    header.append(TEMPERATURE3_STRING);
    header.append(PRESSURE_STRING);
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

    QTableWidgetItem *currentTime = new QTableWidgetItem(data.currentTime.toString());
    QTableWidgetItem *time = new QTableWidgetItem(tr("%1").arg(data.time));
    QTableWidgetItem *cellTemp = new QTableWidgetItem(tr("%1").arg(data.getTemperature(0)));
    QTableWidgetItem *roomTemp = new QTableWidgetItem(tr("%1").arg(data.getTemperature(1)));
    QTableWidgetItem *temp3    = new QTableWidgetItem(tr("%1").arg(data.getTemperature(2)));
    QTableWidgetItem *pressure = new QTableWidgetItem(tr("%1").arg(data.getPressure()));
    QTableWidgetItem *controlStatus = new QTableWidgetItem(tr("%1").arg(data.controlModuleStatus));
    QTableWidgetItem *cameraStatus  = new QTableWidgetItem(tr("%1").arg(data.cameraModuleStatus));
    QTableWidgetItem *nbOfImages    = new QTableWidgetItem(tr("%1").arg(data.nbOfImages));

    this->setItem(row, 0, currentTime);
    this->setItem(row, 1, time);
    this->setItem(row, 2, cellTemp);
    this->setItem(row, 3, roomTemp);
    this->setItem(row, 4, temp3);
    this->setItem(row, 5, pressure);
    this->setItem(row, 6, controlStatus);
    this->setItem(row, 7, cameraStatus);
    this->setItem(row, 8, nbOfImages);

    this->scrollToBottom();
}

void TableTab::clear()
{
    QTableWidget::clear();
    this->setRowCount(0);
}
