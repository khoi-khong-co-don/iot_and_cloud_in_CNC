#include "thread_check_connect.h"
#include <QEventLoop>
#include <QNetworkAccessManager>
#include <QUrl>
#include <QObject>
#include <QNetworkReply>
#include <QEventLoop>

thread_check_connect::thread_check_connect(QObject *parent)
    : QThread{parent}
{

}

void thread_check_connect::run()
{
    QString t;
    QUrl req_url("https://9duyvsq855.execute-api.ap-southeast-1.amazonaws.com/v1/check");
    QNetworkRequest req(req_url);

    QNetworkAccessManager *netManager_check_connect = new QNetworkAccessManager();
    QEventLoop loop;
    while(isStop == false)
    {

        QObject::connect(netManager_check_connect,
                         SIGNAL(finished(QNetworkReply*)),
                         &loop,
                         SLOT(quit()));

        QNetworkReply* netReply = netManager_check_connect->get(req);
        loop.exec();
        if (netReply->bytesAvailable())
        {
            t = "true";
        }
        else
        {
            t = "false";
        }
         emit signalGUI(t);
    }
}
