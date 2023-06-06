#include "thread_data_post.h"
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

thread_data_post::thread_data_post(QObject *parent)
    : QThread{parent}
{

}
void thread_data_post::run()
{
}
void thread_data_post::setMes(const QString &string)
{
        QUrl post_url("https://dqb0t0vcw4.execute-api.ap-southeast-1.amazonaws.com/v1/data");
        QNetworkRequest post(post_url);

        QNetworkAccessManager *netManager1 = new QNetworkAccessManager();
        QEventLoop loop1;
        QObject::connect(netManager1,
                         SIGNAL(finished(QNetworkReply*)),
                         &loop1,
                         SLOT(quit()));
        QByteArray requestData = string.toUtf8();
        QNetworkReply* netReply1 = netManager1->post(post, requestData);
        loop1.exec();
}
void thread_data_post::stop()
{
    isStop = true;
}
