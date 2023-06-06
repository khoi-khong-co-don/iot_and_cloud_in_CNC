#include "thread_data_get.h"
#include "QMessageBox"
#include "QCloseEvent"
#include "QTimer"
#include "QFile"
#include "QTextStream"
#include "QFileDialog"
#include "QGraphicsScene"
#include "QGraphicsItem"
#include <QJsonDocument>
#include <QUrl>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTextEdit>
#include <QEventLoop>
#include <QDebug>
#include <QThread>

thread_data_get::thread_data_get(QObject *parent)
    : QThread{parent}
{

}

void thread_data_get::run()
{
//    timer1 = new QTimer(this);

//    timer1->setInterval(1000);
//    connect(timer1, SIGNAL(timeout()), this, SLOT(timer_timeout()));
//    timer1->start();
    QUrl req_url("https://84jp9m1b56.execute-api.ap-southeast-1.amazonaws.com/v1/data");
    QNetworkRequest req(req_url);

    QNetworkAccessManager *netManager_data_get = new QNetworkAccessManager();
    QEventLoop loop;

    while(isStop == false)
    {
        QObject::connect(netManager_data_get,
                         SIGNAL(finished(QNetworkReply*)),
                         &loop,
                         SLOT(quit()));

        QNetworkReply* netReply = netManager_data_get->get(req);
        loop.exec();
        // nhận dữ liệu từ API đưa vào dataBuffer
        QString dataBuffer = netReply->readAll();
        // in dữ liệu nhận được ra command window
    //        qDebug() << dataBuffer;

            QJsonDocument doc = QJsonDocument::fromJson(dataBuffer.toUtf8());
            QJsonObject obj = doc.object();

            QJsonValue item_val = obj.value(QString("Items"));
            QJsonObject item_obj = item_val[0].toObject();
            QJsonObject status_obj = item_obj["Status"].toObject();

            QString status = status_obj.value(QString("S")).toString();
            emit signalGUI_get(status);
            QThread::sleep(1);
    }
}

void thread_data_get::stop()
{
    isStop = true;
}

void thread_data_get::timer_timeout()
{


}
