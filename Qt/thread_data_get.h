#ifndef THREAD_DATA_GET_H
#define THREAD_DATA_GET_H

#include <QThread>
#include <QObject>
#include <QWidget>

class thread_data_get : public QThread
{
    Q_OBJECT
public:
    explicit thread_data_get(QObject *parent = nullptr);
    void stop();

protected:
    void run() override;

signals:
    void signalGUI_get(QString);
private:
    bool isStop = false;
private slots:
    void timer_timeout();
};

#endif // THREAD_DATA_GET_H
