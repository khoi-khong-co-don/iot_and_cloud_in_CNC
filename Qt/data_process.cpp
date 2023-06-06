#include "data_process.h"
#include "ui_data_process.h"
#include <QBarCategoryAxis>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QTableView>
#include <QtCharts/QChart>
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QVXYModelMapper>
#include <QtCharts/QBarSeries>
#include <QtCharts/QBarSet>
#include <QtCharts/QVBarModelMapper>
#include <QtWidgets/QHeaderView>
#include <QtCharts/QBarCategoryAxis>
#include <QtCharts/QValueAxis>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>>
#include <QTableWidgetItem>>
#include <iostream>
#include <string>
#include <functional>
#include <QQuickView>

QString dateString;
QString id_machine_query = "1";
QBarSet *set0 = new QBarSet("Performance");
QBarSet *set1 = new QBarSet("Target");
QBarSet *machine_set0 = new QBarSet("Performance");
QBarSet *machine_set1 = new QBarSet("Target");
QLineSeries *series_date = new QLineSeries();
int month;

data_process::data_process(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::data_process)
{
    ui->setupUi(this);
    this->setWindowTitle("Data Process");
    ui->date_data->setColumnWidth(0,200);

    ui->generate_data->setColumnWidth(0,80);
    ui->generate_data->setColumnWidth(1,110);
    ui->generate_data->setColumnWidth(2,60);
    ui->generate_data->setColumnWidth(3,150);

    ui->data->setColumnWidth(0,110);
    ui->data->setColumnWidth(1,140);
    ui->data->setColumnWidth(2,90);
    ui->data->setColumnWidth(3,180);
    ui->data->setColumnWidth(4,90);
    //ui->generate_data->setStyleSheet("color: yellow; background-color: blue;");
   // ui->textEdit->insertPlainText(id_machine_query + "\n");
}

data_process::~data_process()
{
    delete ui;
}

void data_process::customtable(const QString &time)
{
    //////////////////////// KHAI BAO ////////////////////////////
    QJsonDocument doc = QJsonDocument::fromJson(time.toUtf8());
    QJsonObject obj = doc.object();
    int dem_machine_1 = 0;
    int dem_machine_2 = 0;
    int objectCount = 0;
    int count_machine = 0;
    int machine[10] = {0};
    QString id_machine = "";
    QString id_machine_pass;
    int rowCount = 0;
    int demobj = 0;
    int j=0;
    bool ok;
    //////////////////////////////////////////////////////////////

    QJsonValue body = obj.value(QString("body"));
    if (body.isArray()) {
            QJsonArray jsonArray = body.toArray();
            objectCount = jsonArray.size();
        } else if (body.isObject()) {
            objectCount = 1;
        }

    for (int i=0 ; i<objectCount; i++)
    {
        QJsonObject body_obj = body[i].toObject();
        QString data_date = body_obj.value(QString("date")).toString();
        id_machine_pass = id_machine;
        id_machine = body_obj.value(QString("id")).toString();
        if (data_date == dateString)
        {
            rowCount++;             // dem so hang cho bang generate_data
        }
        if (id_machine != id_machine_pass)
        {
            count_machine++;
        }
        else
        {
            machine[id_machine.toInt(&ok)]++;
        }

    }
    for (int i=0 ; i<=count_machine ; i++)
    {
        //ui->textEdit->insertPlainText(QString::number(machine[i]+1)+ "  ");
    }
    ui->date_data->setRowCount(rowCount);

    /////////////////////// XU LY BANG DU LIEU TONG //////////////////////
//    ui->generate_data->setRowCount(12);
//    for (int i=1 ; i<=12 ; i++)
//    {
//        QString thang = "";
//        if (i<10)
//        {
//            thang = thang + "0" + QString::number(i);
//        }
//        else
//        {
//            thang = thang + QString::number(i);
//        }
//        int dem_product = 0;
//        for (int j=0 ; j<objectCount ; j++)
//        {
//            QJsonObject body_obj = body[j].toObject();
//            QString data_date = body_obj.value(QString("date")).toString();
//            QString id_machine_get = body_obj.value(QString("id")).toString();
//            QString thang_kt = "";
//            thang_kt = thang_kt + data_date[0] + data_date[1];
//           // ui->textEdit->insertPlainText(id_machine_get);
//            if (id_machine_get == id_machine_query)
//            {
//                if (thang_kt == thang)
//                {
//                    dem_product++;
//                }
//            }
//        }
//        QTableWidgetItem *items[] = {
//            new QTableWidgetItem(QString("Month %1").arg(i)),
//            new QTableWidgetItem(QString(QString::number(dem_product))),
//            new QTableWidgetItem(QString::number(20000)),
//            new QTableWidgetItem(QString::number(dem_product*100/20000)+"%")
//        };
//        const size_t count = sizeof(items) / sizeof(QTableWidgetItem *);
//        for (size_t column = 0 ; column < count; column++)
//        {
//            ui->generate_data->setItem(i-1, column, items[column]);
//            items[column]->setTextAlignment(Qt::AlignCenter);
//        }
    ////////////////////////XU LY DU LIEU THEO TUAN///////////////////////
    ui->generate_data->setRowCount(4);
    for (int i=1; i<=4 ; i++)
    {
        int dem_product1 = 0;
        for (int j=0 ; j<objectCount ; j++)
        {
            QJsonObject body_obj = body[j].toObject();
            QString data_date = body_obj.value(QString("date")).toString();
            QString id_machine_get = body_obj.value(QString("id")).toString();
            QString date_kt = "";
            QString month_kt ="";
            month_kt = month_kt + data_date[0] + data_date[1];
            date_kt = date_kt + data_date[3] + data_date[4];
           // ui->textEdit->insertPlainText(id_machine_get);
            if (id_machine_get == id_machine_query)
            {
                if (month_kt.toInt(&ok) == month)
                {
                    if (date_kt.toInt(&ok) >=7*(i-1) && date_kt.toInt(&ok) <=7*i)
                    {
                        dem_product1++;
                    }
                }

            }
        }
        QTableWidgetItem *items[] = {
            new QTableWidgetItem(QString("week %1").arg(i)),
            new QTableWidgetItem(QString(QString::number(dem_product1))),
            new QTableWidgetItem(QString::number(600)),
            new QTableWidgetItem(QString::number(dem_product1*100/600)+"%")
        };
        const size_t count = sizeof(items) / sizeof(QTableWidgetItem *);
        for (size_t column = 0 ; column < count; column++)
        {
            ui->generate_data->setItem(i-1, column, items[column]);
            items[column]->setTextAlignment(Qt::AlignCenter);
        }
        set0->append(dem_product1);
        set1->append(600);
    }
    ///////////////////////////////////////////////////////////////////////////////////
    ////////////////////////XU LY DU LIEU THEO NGAY///////////////////////
    for (int i=1; i<=30 ; i++)
    {
        int dem_product = 0;
        for (int j=0 ; j<objectCount ; j++)
        {
            QJsonObject body_obj = body[j].toObject();
            QString data_date = body_obj.value(QString("date")).toString();
            QString id_machine_get = body_obj.value(QString("id")).toString();
            QString date_kt = "";
            QString month_kt ="";
            month_kt = month_kt + data_date[0] + data_date[1];
            date_kt = date_kt + data_date[3] + data_date[4];
           // ui->textEdit->insertPlainText(id_machine_get);
            if (id_machine_get == id_machine_query)
            {
                if (month_kt.toInt(&ok) == month)
                {
                    if (date_kt.toInt(&ok) == i)
                    {
                        dem_product++;
                    }
                }
            }
        }
        series_date->append(i,dem_product);
    }
    ///////////////////////////////////////////////////////////////////////////////////

    ////////////////////// XU LY DU LIEU TUNG MAY ///////////////////////////////////
    ui->data->setRowCount(count_machine);
    for (int i=1; i<=count_machine ; i++)
    {
        QTableWidgetItem *items_machine[] = {
            new QTableWidgetItem(QString("Machine %1").arg(i)),
            new QTableWidgetItem(QString::number(machine[i] + 1)),
            new QTableWidgetItem(QString::number(2400)),
            new QTableWidgetItem(QString::number((machine[i]+1)*100/2400)+"%"),
            new QTableWidgetItem(QString::number(15)),
            new QTableWidgetItem(QString::number(20))
        };
        const size_t count = sizeof(items_machine) / sizeof(QTableWidgetItem *);
        for (size_t column = 0 ; column < count; column++)
        {
            ui->data->setItem(i-1, column, items_machine[column]);
            items_machine[column]->setTextAlignment(Qt::AlignCenter);
        }
        machine_set0->append((machine[i]+1));
        machine_set1->append(2400);
    }
    ////////////////////////////////////////////////////////////////////////
    ve_do_thi();
}

void data_process::on_dateEdit_userDateChanged(const QDate &date)
{
    dateString = date.toString("MM/dd/yyyy");
    ThreadGetProduct = new thread_get_product();
    connect(ThreadGetProduct, SIGNAL(signalGUI_get(QString)), this, SLOT(customtable_date(const QString&)));
    ThreadGetProduct->start();
}


void data_process::customtable_date(const QString &time)
{
    /////////////////////////////// BANG THEO NGAY///////////////////////////////
    QJsonDocument doc = QJsonDocument::fromJson(time.toUtf8());
    QJsonObject obj = doc.object();

    int objectCount = 0;
    QJsonValue body = obj.value(QString("body"));
    if (body.isArray()) {
            QJsonArray jsonArray = body.toArray();
            objectCount = jsonArray.size();
        } else if (body.isObject()) {
            objectCount = 1;
        }
    int rowCount = 0;
    for (int i=0 ; i<objectCount; i++)
    {
        QJsonObject body_obj = body[i].toObject();
        QString data_date = body_obj.value(QString("date")).toString();
        QString id_machine_get = body_obj.value(QString("id")).toString();
        if (id_machine_get == id_machine_query)
        {
            if (data_date == dateString)
            {
                rowCount++;
            }
        }
    }
    ui->date_data->setRowCount(rowCount);
    int demobj = 0;
    for (int i = 0; i<objectCount ; i++)
    {
        QJsonObject body_obj = body[i].toObject();
        QJsonValue body_0 = body_obj.value(QString("time"));
        QString data_time = body_0.toString();
        QString data_date = body_obj.value(QString("date")).toString();
        QString id_machine_get = body_obj.value(QString("id")).toString();
        if (id_machine_get == id_machine_query)
        {
            if (data_date == dateString)
            {
                QTableWidgetItem *items[] = {
                    new QTableWidgetItem(QString(data_time + "  " + data_date)),
                };
                const size_t count = sizeof(items) / sizeof(QTableWidgetItem *);
                for (size_t column = 0 ; column < count; column++)
                {
                    ui->date_data->setItem(demobj, column, items[column]);
                    items[column]->setTextAlignment(Qt::AlignCenter);
                }
                demobj++;
            }
        }
    }
    ///////////////////////////////////////////////////////////////////////
}

void data_process::on_comboBox_currentTextChanged(const QString &arg1)
{
    QString str_machine = ui->comboBox->currentText();
   // ui->textEdit->insertPlainText(str_machine);
    if (str_machine == "Machine 1")
    {
        id_machine_query = "1";
        ThreadGetProduct = new thread_get_product();
        connect(ThreadGetProduct, SIGNAL(signalGUI_get(QString)), this, SLOT(customtable(const QString&)));
        connect(ThreadGetProduct, SIGNAL(signalGUI_get(QString)), this, SLOT(customtable_date(const QString&)));
        ThreadGetProduct->start();
    }
    if (str_machine == "Machine 2")
    {
        id_machine_query = "2";
        ThreadGetProduct = new thread_get_product();
        connect(ThreadGetProduct, SIGNAL(signalGUI_get(QString)), this, SLOT(customtable(const QString&)));
        connect(ThreadGetProduct, SIGNAL(signalGUI_get(QString)), this, SLOT(customtable_date(const QString&)));
        ThreadGetProduct->start();
    }
}

void data_process::ve_do_thi()
{
    /////////////////////////////// VE DO THI TUAN //////////////////////////////
    QBarSeries *series = new QBarSeries();
    series -> append(set0);
    series -> append(set1);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle("Data on product by week");

    QStringList categories;
    categories << "Week 1" << "Week 2"<<"Week 3" << "Week 4";
    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);
    QValueAxis *axisY = new QValueAxis();
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    QChartView *chartview = new QChartView (chart);
    chartview->setFixedSize(450, 300);
    chartview->setParent(ui->frame);
    chartview->show();
    ////////////////////////////////////////////////////////////
    ///
    /// /////////////// VE DO THI MAY////////////////////////
    QBarSeries *series1 = new QBarSeries();
    series1 -> append(machine_set0);
    series1 -> append(machine_set1);

    QChart *chart1 = new QChart();
    chart1->addSeries(series1);
    chart1->setAnimationOptions(QChart::SeriesAnimations);
    chart1->setTitle("Data on product by machine");

    QStringList categories1;
    categories1 << "Machine 1" << "Machine 2";
    QBarCategoryAxis *axisX1 = new QBarCategoryAxis();
    axisX1->append(categories1);
    chart1->addAxis(axisX1, Qt::AlignBottom);
    series1->attachAxis(axisX1);
    QValueAxis *axisY1 = new QValueAxis();
    chart1->addAxis(axisY1, Qt::AlignLeft);
    series1->attachAxis(axisY1);

    QChartView *chartview1 = new QChartView (chart1);
    chartview1->setFixedSize(400, 300);
    chartview1->setParent(ui->frame1);
    chartview1->show();
    /////////////////////////////////////////////////////
    /// ///////////////////////// VE DO THI THEO NGAY//////////////////
    QChart *chart2 = new QChart();
   chart2->legend()->hide();
   chart2->addSeries(series_date);
   chart2->createDefaultAxes();
   chart2->setTitle("Data on product by day");
   QChartView *chartView2 = new QChartView(chart2);
   chartView2->setRenderHint(QPainter::Antialiasing);
   chartView2->setFixedSize(400, 300);
   chartView2->setParent(ui->frame2);
   chartView2->show();
}

void data_process::on_choose_month_currentTextChanged(const QString &arg1)
{
    QString str_month = ui->choose_month->currentText();
    if (str_month == "January")
    {
        month = 1;
    }
    if (str_month == "February")
    {
        month = 2;
    }
    if (str_month == "March")
    {
        month = 3;
    }
    if (str_month == "April")
    {
        month = 4;
    }
    if (str_month == "May")
    {
        month = 5;
    }
    if (str_month == "June")
    {
        month = 6;
    }
    if (str_month == "July")
    {
        month = 7;
    }
    if (str_month == "August")
    {
        month = 8;
    }
    if (str_month == "September")
    {
        month = 9;
    }
    if (str_month == "October")
    {
        month = 10;
    }
    if (str_month == "November")
    {
        month = 11;
    }
    if (str_month == "December")
    {
        month = 12;
    }
    ThreadGetProduct = new thread_get_product();
    connect(ThreadGetProduct, SIGNAL(signalGUI_get(QString)), this, SLOT(customtable(const QString&)));
    ThreadGetProduct->start();
}

