#include "mythread1.h"
#include "QMessageBox"
#include "QCloseEvent"
#include "QTimer"
#include <QJsonDocument>
#include <QUrl>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QNetworkReply>
#include <QNetworkAccessManager>
#include <QTextEdit>
#include "QCloseEvent"


QTimer *timer2;
int sec1 = 0;
mythread1::mythread1(QObject *parent)
    : QThread{parent}
{

}
void mythread1::run()
{
    timer2 = new QTimer(this);
    timer2->setInterval(1);
    connect(timer2, SIGNAL(timeout()), this, SLOT(mythread1::connect()));
    timer2->start();
}
void mythread1::connect()
{
    sec1++;
    if (sec1 % 10 == 0){
        // API nhận dữ liệu
        QUrl req_url("https://77n2pyz8h9.execute-api.ap-southeast-1.amazonaws.com/v1/v1");
        QNetworkRequest req(req_url);

        QNetworkAccessManager *netManager = new QNetworkAccessManager();
        QEventLoop loop;
        QObject::connect(netManager,
                         SIGNAL(finished(QNetworkReply*)),
                         &loop,
                         SLOT(quit()));

        QNetworkReply* netReply = netManager->get(req);
        loop.exec();
        // nhận dữ liệu từ API đưa vào dataBuffer
        QString dataBuffer = netReply->readAll();
        // in dữ liệu nhận được ra command window
//        qDebug() << dataBuffer;


//        // test sensor
            QJsonDocument doc = QJsonDocument::fromJson(dataBuffer.toUtf8());
            QJsonObject obj = doc.object();

            QJsonValue item_val = obj.value(QString("Items"));
            QJsonObject item_obj = item_val[0].toObject();
            QJsonObject status_obj = item_obj["Status"].toObject();
//           qDebug() << status_obj;

            QString status = status_obj.value(QString("S")).toString();

//            QJsonObject status = status_obj.value(QString("S"));
//            QString posX = status.value(QString("X")).toString();
//            qDebug() << status[45];
//            // status là giá trị lấy được cuối cùng
//            // hiển thị ra lcd        X: 7-13     23-29       39-45
//            QString posX, posY, posZ;
//            for (int i = 7; i<=13 ; i++)
//                posX = posX + status[i];
//            for (int i = 23; i<=29 ; i++)
//                posY = posY + status[i];
//            for (int i = 39; i<=45 ; i++)
//                posZ = posZ + status[i];
////            qDebug() << posX;
//            ui->posX->display(posX);
//            ui->posY->display(posY);
//            ui->posZ->display(posZ);
            QString status_iot;
            bool iot_mor, iot_con;
            if (status[1] == '1')
               {

                 for (int i = 4; i<=20 ; i++)
                 {
                    status_iot = status_iot + status[i];
                    if (status[i] == 'K') break;
                 }
                 if (status_iot == "MORNITOR OK") {iot_mor = true; }
                 if (status_iot == "MORNITOR NOT OK") {iot_mor = false;}
                 if (status_iot == "CONTROL OK") {iot_con = true; }
                 if (status_iot == "CONTROL NOT OK") {iot_con = false;}
                 if (iot_mor == true) {ui->Led_6->setPower(true); }
                 else {ui->Led_6->setPower(false);}
                 if (iot_con == true) {ui->Led_8->setPower(true); }
                 else {ui->Led_8->setPower(false);}
            }


//            // hiển thị đèn
//            if (status == "1") {ui->Led_1->setPower(true); }
//            else {ui->Led_1->setPower(false);
    }
        // close test sensor

}
