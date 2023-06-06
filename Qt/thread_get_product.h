#ifndef THREAD_GET_PRODUCT_H
#define THREAD_GET_PRODUCT_H

#include <QThread>
#include <QObject>
#include <QWidget>

class thread_get_product : public QThread
{
    Q_OBJECT
public:
    explicit thread_get_product(QObject *parent = nullptr);
    void stop();

protected:
    void run() override;

signals:
    void signalGUI_get(QString);
private:
    bool isStop = false;
};

#endif // THREAD_GET_PRODUCT_H
