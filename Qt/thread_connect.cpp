#include "thread_connect.h"
#include <QDebug>
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
#include <QThread>

thread_connect::thread_connect(QObject *parent)
    : QThread{parent}
{

}
void thread_connect::run()
{
    QUrl req_url("https://izs9emxeyb.execute-api.ap-southeast-1.amazonaws.com/v1/connect");
    QNetworkRequest req(req_url);

    QNetworkAccessManager *netManager_connect = new QNetworkAccessManager();
    QEventLoop loop;
    while(isStop == false)
    {

        QObject::connect(netManager_connect,
                         SIGNAL(finished(QNetworkReply*)),
                         &loop,
                         SLOT(quit()));

        QNetworkReply* netReply = netManager_connect->get(req);
        loop.exec();
        // nhận dữ liệu từ API đưa vào dataBuffer
        QString dataBuffer = netReply->readAll();

        QJsonDocument doc = QJsonDocument::fromJson(dataBuffer.toUtf8());
        QJsonObject obj = doc.object();
        // tách chuỗi mess
        QJsonValue item_val = obj.value(QString("Items"));
        QJsonObject item_obj = item_val[0].toObject();
        QJsonObject status_obj = item_obj["Status"].toObject();

        QString status = status_obj.value(QString("S")).toString();
        QString status_connect;
        for (int i = 9; i<=status.size() ; i++)
        {
            if (status[i] == '"') break;
            status_connect = status_connect + status[i];

        }

        // tách lấy thời gian
        QJsonObject time_obj = item_obj["time"].toObject();

        QString time = time_obj.value(QString("S")).toString();
        emit signalGUI_connect(status_connect);
        emit timeGUI(time);
        QThread::sleep(1);
    }
}
void thread_connect::stop()
{
    isStop = true;
}
