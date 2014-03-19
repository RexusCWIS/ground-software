#ifndef STATUSPANEL_H
#define STATUSPANEL_H

#include <QWidget>

#include <QGroupBox>
#include <QVBoxLayout>

class StatusPanel : public QWidget
{
    Q_OBJECT
public:
    explicit StatusPanel(QWidget *parent = 0);

signals:

public slots:

private:
    QGroupBox *m_controlStatusBox;
    QGroupBox *m_cameraStatusBox;

    QVBoxLayout *m_layout;
    QVBoxLayout *m_controlStatusLayout;
    QVBoxLayout *m_cameraStatusLayout;
};

#endif // STATUSPANEL_H
