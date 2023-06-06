#ifndef THREAD_DATA_POST_H
#define THREAD_DATA_POST_H

#include <QThread>
#include <QObject>
#include <QWidget>

class thread_data_post : public QThread
{
    Q_OBJECT
public:
    explicit thread_data_post(QObject *parent = nullptr);
    void stop();

private slots:
    void setMes(const QString &string);

protected:
    void run() override;

signals:
    void signalGUI(QString);
private:
    bool isStop = false;
};

#endif // THREAD_DATA_POST_H
