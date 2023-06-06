#include "thread_connect_post.h"
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


thread_connect_post::thread_connect_post(QObject *parent)
    : QThread{parent}
{

}
void thread_connect_post::run()
{
    QUrl post_url("https://htsmhdq277.execute-api.ap-southeast-1.amazonaws.com/v1/connect");
    QNetworkRequest post(post_url);

    QNetworkAccessManager *netManager1 = new QNetworkAccessManager();
    QEventLoop loop1;
    while (isStop == false)
    {

        QObject::connect(netManager1,
                         SIGNAL(finished(QNetworkReply*)),
                         &loop1,
                         SLOT(quit()));

        QNetworkReply* netReply1 = netManager1->post(post, "{\"MES\": \"CONNECT\"}");
        loop1.exec();
    }
}

void thread_connect_post::stop()
{
    isStop = true;
    QUrl post_url("https://i8kgh2b8ef.execute-api.ap-southeast-1.amazonaws.com/test/post");
    QNetworkRequest post(post_url);

    QNetworkAccessManager *netManager1 = new QNetworkAccessManager();
    QEventLoop loop1;
    QObject::connect(netManager1,
                     SIGNAL(finished(QNetworkReply*)),
                     &loop1,
                     SLOT(quit()));

    QNetworkReply* netReply1 = netManager1->post(post, "{\"MES\": \"DISCONNECT\"}");
    loop1.exec();
}
