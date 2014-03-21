#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>

#include <QLabel>

class ClockWidget : public QWidget
{
    Q_OBJECT
public:
    ClockWidget(QWidget *parent = 0);
    QSize sizeHint() const;

protected:
    void paintEvent(QPaintEvent *event);
    void resizeEvent(QResizeEvent *event);
};

class DigitalClockWidget: public QLabel
{
    Q_OBJECT
public:
    DigitalClockWidget(QWidget *parent = 0);

protected slots:
    void refresh();
};

#endif // CLOCKWIDGET_H
