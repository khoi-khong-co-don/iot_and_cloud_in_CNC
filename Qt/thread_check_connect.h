#ifndef THREAD_CHECK_CONNECT_H
#define THREAD_CHECK_CONNECT_H

#include <QThread>
#include <QObject>
#include <QWidget>

class thread_check_connect : public QThread
{
    Q_OBJECT
public:
    explicit thread_check_connect(QObject *parent = nullptr);

protected:
    void run() override;
signals:
    void signalGUI(QString);
private:
    bool isStop= false;
};

#endif // THREAD_CHECK_CONNECT_H
