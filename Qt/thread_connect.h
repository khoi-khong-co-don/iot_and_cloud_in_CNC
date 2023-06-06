#ifndef THREAD_CONNECT_H
#define THREAD_CONNECT_H

#include <QThread>
#include <QObject>
#include <QWidget>

class thread_connect : public QThread
{
    Q_OBJECT
public:
    explicit thread_connect(QObject *parent = nullptr);
    void stop();
protected:
    void run() override;

signals:
    void signalGUI_connect(QString);
    void timeGUI(QString);
private:
    bool isStop= false;
};

#endif // THREAD_CONNECT_H
