#ifndef THREAD_CONNECT_POST_H
#define THREAD_CONNECT_POST_H

#include <QThread>
#include <QObject>
#include <QWidget>

class thread_connect_post : public QThread
{
    Q_OBJECT
public:
    explicit thread_connect_post(QObject *parent = nullptr);
    void stop();
protected:
    void run() override;

signals:
    void signalGUI(QString);
private:
    bool isStop= false;
};

#endif // THREAD_CONNECT_POST_H
