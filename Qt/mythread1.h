#ifndef MYTHREAD1_H
#define MYTHREAD1_H

#include <QThread>
#include <QObject>
#include <QWidget>

class mythread1 : public QThread
{
    Q_OBJECT
public:
    explicit mythread1(QObject *parent = nullptr);
protected:
    void run() override;
    void connect();
};

#endif // MYTHREAD1_H
