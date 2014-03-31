#ifndef STATUSFLAG_H
#define STATUSFLAG_H

#include <QLabel>

class StatusFlag : public QLabel
{
    Q_OBJECT
public:
    explicit StatusFlag(QWidget *parent = 0);

    void setStatus(bool status);
    bool getStatus(void) const;

signals:
    void toggled(bool);

public slots:

protected:
    bool m_status;
};

#endif // STATUSFLAG_H
