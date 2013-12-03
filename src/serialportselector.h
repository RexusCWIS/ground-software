#ifndef SERIALPORTSELECTOR_H
#define SERIALPORTSELECTOR_H

#include <QComboBox>

class SerialPortSelector: public QComboBox {
    Q_OBJECT

public:
    SerialPortSelector(QWidget *parent);
};

#endif // SERIALPORTSELECTOR_H
