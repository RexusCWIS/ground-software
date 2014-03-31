#ifndef CLOCKWIDGET_H
#define CLOCKWIDGET_H

#include <QWidget>

#include <QLabel>
#include <QTime>

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

signals:
    void refreshed();

protected slots:
    void refresh();
};

class ChronometerWidget: public QLabel
{
    Q_OBJECT
public:
    ChronometerWidget(QWidget *parent);

    void start();

signals:
    void refreshed();

protected:
    QTime m_startTime;
    bool  m_started;

protected slots:
    void refresh();
};

#endif // CLOCKWIDGET_H
