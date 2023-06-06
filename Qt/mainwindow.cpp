#include "mainwindow.h"
#include "ui_mainwindow.h"
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

#include <Qt3DExtras>
#include <Qt3DCore/QEntity>
#include <Qt3DCore/QTransform>
#include <Qt3DRender/QCamera>
#include <QPropertyAnimation>
#include <Qt3DRender/QMesh>
#include <Qt3DExtras/Qt3DWindow>
#include <Qt3DRender/QCameraLens>
#include <Qt3DRender/QMaterial>
#include <Qt3DExtras/QPhongMaterial>
#include "orbittransformcontroller.h"
#include "qorbitcameracontroller.h"

QTimer *timer;
int sec = 0, min = 0, hour = 0, pos = 0, sec1 = 0, sec2 = 0, check = 0;
QString posX, posY, posZ, posA, posB, velX, velY, velZ, velA, velB;
bool allow_connect = false;
bool internet = true;
bool connect_sucess = false;
bool creat_thread = false;
int dem_time = 0;
QString mes_time = "";
bool lost_connect = false;
QString pas_string = "";
int startX = 300, startY = 300;
QString check_pass = "";
QString mes_time_product = "";
QString spindle_status, spindle_speed;
QString string_monitor_pas = "";
bool set_home = false;
float posXConvert = -60, posYConvert = -100, posZConvert = 70;
QString posX_pas = "", posY_pas = "", posZ_pas = "";

Qt3DCore::QTransform *trucytransform = new Qt3DCore::QTransform;
Qt3DCore::QTransform *trucxtransform = new Qt3DCore::QTransform;
Qt3DCore::QTransform *trucztransform = new Qt3DCore::QTransform;

QVector3D trucyStart =QVector3D(3,8,-100);
QVector3D trucxStart =QVector3D(-60,48,-100);
QVector3D truczStart =QVector3D(-58,70,-100);


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("CNC HMI");

    //setup timer
    timer = new QTimer(this);

    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(timer_timeout()));
    grid_2d();
    timer->start();

    //ui->checkBox->setChecked(0);

    ui->comboBox->addItem("Machine 1");
    ui->comboBox->addItem("Machine 2");
    ui->Led_9->setPower(true);


//    ThreadCheckConnect = new thread_check_connect();
//    connect(ThreadCheckConnect, SIGNAL(signalGUI(QString)), this, SLOT(CheckConnect(const QString&)));
//    ThreadCheckConnect->start();

//    ThreadConnect = new thread_connect();
//    connect(ThreadConnect, SIGNAL(signalGUI_connect(QString)), this, SLOT(setSignal(const QString&)));
//    connect(ThreadConnect, SIGNAL(timeGUI(QString)), this, SLOT(time_connect(const QString&)));
//    ThreadConnect->start();

    model3d();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//hộp thoại khi đóng giao diện
void MainWindow::closeEvent(QCloseEvent *event)
{
    if (QMessageBox::question(this,"Confirm", "Are you sure to exit?") == QMessageBox::No)
    {
        event->ignore();
    }
}

// cài timmer
void MainWindow::timer_timeout()
{
//    sec++;
//    if (sec == 60)
//    {
//        min++;
//        sec = 0;
//    }
//    if (hour == 0) ui->labelTimer->setText(QString::number(min) + ":" + QString::number(sec));
//    if (min == 60)
//    {
//        hour++;
//        min = 0;
//    }
//    if (hour != 0) ui->labelTimer->setText(QString::number(hour)+ ":" + QString::number(min) + ":" + QString::number(sec));
//    if (min == 0) ui->labelTimer->setText(QString::number(sec));
//    ui->statusbar->showMessage("CNC is ready");
//    ui->statusbar->addPermanentWidget(ui->labelSay);
//    ui->statusbar->addPermanentWidget(ui->labelTimer);
    //    if ()                       // điều khiện để dừng timer
    //    {
    //       // this->close();
    //    }
}

//load G_code
void MainWindow::on_load_g_code_clicked()
{
    QString filter = "All file (*.*) ;; Text File (*.txt) ;; XML File (*.xml)";
    QString file_name = QFileDialog::getOpenFileName(this, "Open a file", "C://", filter);
    QFile file (file_name);
   // QFile file ("C:/Users/Administrator/Desktop/G_code/g_code.txt");
    if (!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::warning(this, "title", "file not open");
    }
    QTextStream in(&file);
    QString text1 = in.readAll();
    //QString text1 = """ + text + """
//    QString text1 = "{              nn \"khoi\": \"" + text + "\"}";
    ui->textBrowser->setPlainText(text1);
    QJsonDocument g_code = QJsonDocument::fromJson(text1.toUtf8());
    file.close();
}
void MainWindow::model3d()
{
    Qt3DCore::QEntity *rootEntity = new Qt3DCore::QEntity;

    Qt3DExtras::QPhongMaterial * material = new Qt3DExtras::QPhongMaterial();
    material->setAmbient(QColor(51, 51, 255));
    material->setDiffuse(QColor(51, 51, 255));
    material->setSpecular(QColor(51, 51, 255));
    material->setShininess(0);

    Qt3DExtras::QPhongMaterial * material0 = new Qt3DExtras::QPhongMaterial();
    material0->setAmbient(QColor(204, 204, 0));
    material0->setDiffuse(QColor(153, 153, 0));
    material0->setSpecular(QColor(153, 153, 0));
    material0->setShininess(0);

    Qt3DExtras::QPhongMaterial * material1 = new Qt3DExtras::QPhongMaterial();
    material1->setAmbient(QColor(160, 160, 160));
    material1->setDiffuse(QColor(64, 64, 64));
    material1->setSpecular(QColor(64, 64, 64));
    material1->setShininess(0);

    Qt3DExtras::QPhongMaterial * material2 = new Qt3DExtras::QPhongMaterial();
    material2->setAmbient(QColor(255, 51, 51));
    material2->setDiffuse(QColor(153, 0, 0));
    material2->setSpecular(QColor(153, 0, 0));
    material2->setShininess(0);

    Qt3DCore::QEntity *tu_dien = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QMesh *mesh_tudien = new Qt3DRender::QMesh();
    mesh_tudien->setSource(QUrl(QStringLiteral("qrc:/obj/tu_dien.obj")));
    Qt3DCore::QTransform *tu_dien_transform = new Qt3DCore::QTransform;
    tu_dien_transform->setScale3D(QVector3D(0.1, 0.1, 0.1));
    tu_dien_transform->setTranslation(QVector3D(-75,8,-130));

    tu_dien->addComponent(mesh_tudien);
    tu_dien->addComponent(material0);
    tu_dien->addComponent(tu_dien_transform);

    Qt3DCore::QEntity *be_nuoc = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QMesh *mesh_be_nuoc = new Qt3DRender::QMesh();
    mesh_be_nuoc->setSource(QUrl(QStringLiteral("qrc:/obj/be_nuoc.obj")));
    Qt3DCore::QTransform *be_nuoc_transform = new Qt3DCore::QTransform;
    be_nuoc_transform->setScale3D(QVector3D(0.1, 0.1, 0.1));
    be_nuoc_transform->setTranslation(QVector3D(60,8,-130));

    be_nuoc->addComponent(mesh_be_nuoc);
    be_nuoc->addComponent(material);
    be_nuoc->addComponent(be_nuoc_transform);


    Qt3DCore::QEntity *cnc = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QMesh *mesh = new Qt3DRender::QMesh();
        mesh->setSource(QUrl(QStringLiteral("qrc:/obj/assem1.obj")));
    Qt3DCore::QTransform *cnctransform = new Qt3DCore::QTransform;
    cnctransform->setScale3D(QVector3D(0.1, 0.1, 0.1));

    cnc->addComponent(mesh);
    cnc->addComponent(material1);
    cnc->addComponent(cnctransform);


    Qt3DCore::QEntity *trucy = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QMesh *meshtrucy = new Qt3DRender::QMesh();
        meshtrucy->setSource(QUrl(QStringLiteral("qrc:/obj/assem2.obj")));

    trucytransform->setScale3D(QVector3D(0.1, 0.1, 0.1));
    trucytransform->setTranslation(QVector3D(3,8,-100));

    trucy->addComponent(meshtrucy);
    trucy->addComponent(material2);
    trucy->addComponent(trucytransform);

    Qt3DCore::QEntity *trucx = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QMesh *meshtrucx = new Qt3DRender::QMesh();
        meshtrucx->setSource(QUrl(QStringLiteral("qrc:/obj/assem3.obj")));

    trucxtransform->setScale3D(QVector3D(0.1, 0.1, 0.1));
    trucxtransform->setTranslation(QVector3D(-60,48,-100));

    trucx->addComponent(meshtrucx);
    trucx->addComponent(material2);
    trucx->addComponent(trucxtransform);

    Qt3DCore::QEntity *trucz = new Qt3DCore::QEntity(rootEntity);
    Qt3DRender::QMesh *meshtrucz = new Qt3DRender::QMesh();
        meshtrucz->setSource(QUrl(QStringLiteral("qrc:/obj/assem4.obj")));

    trucztransform->setScale3D(QVector3D(0.1, 0.1, 0.1));
    trucztransform->setTranslation(QVector3D(-58,70,-100));

    trucz->addComponent(meshtrucz);
    trucz->addComponent(material1);
    trucz->addComponent(trucztransform);



    Qt3DExtras::Qt3DWindow *view = new  Qt3DExtras::Qt3DWindow;
    view->defaultFrameGraph()->setClearColor(QColor(192,192,192));
     //Camera
    Qt3DRender::QCamera *camera = view->camera();
    camera->lens()->setPerspectiveProjection(45.0f, 16.0f/9.0f, 0.1f, 1000.0f);
    camera->setPosition(QVector3D(-10, 100, 110));
    camera->setViewCenter(QVector3D(-12, 40, 0));



    view->setRootEntity(rootEntity);
    QWidget *container = QWidget::createWindowContainer(view);
    ui->verticalLayout_2->addWidget(container);
}


//ve do thi 2d
void MainWindow::grid_2d()
{
    // grid 2D

    ui->grid_2D->setScene(scene);

    for (int x=0; x<=600; x+=100)
        scene->addLine(x,0,x,600, QPen(Qt::red));

    for (int y=0; y<=600; y+=100)
        scene->addLine(0,y,600,y, QPen(Qt::red));
//    float x,y;
//    x = 152.5; y=152.5;
//    scene->addLine(0,1000-0,x,1000-y, QPen(Qt::green));

    ui->grid_2D->fitInView(scene->itemsBoundingRect());
}

// chon may de hien thong tin
void MainWindow::on_comboBox_currentTextChanged(const QString &arg1)
{
//    timer2 = new QTimer(this);
//    timer2->setInterval(1);
    QString machine = ui->comboBox->currentText();

    if (machine == "Machine 2")
    {
//        check = 1;
//        connect(timer2, SIGNAL(timeout()), this, SLOT(Querry_view_1()));
//        timer2->start();
    }
}




void MainWindow::on_btnX1_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"X+\"}";
            ui->status->insertPlainText(">>X+\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}


void MainWindow::on_btnX2_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"X-\"}";
             ui->status->insertPlainText(">>X-\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnX3_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"STOPX\"}";
            ui->status->insertPlainText(">>STOPX\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnY1_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"Y+\"}";
            ui->status->insertPlainText(">>Y+\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}
void MainWindow::on_btnY2_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"Y-\"}";
            ui->status->insertPlainText(">>Y-\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnY3_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"STOPY\"}";
            ui->status->insertPlainText(">>STOPY\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnZ1_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"Z+\"}";
            ui->status->insertPlainText(">>Z+\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnZ2_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"Z-\"}";
            ui->status->insertPlainText(">>Z-\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnZ3_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"STOPZ\"}";
            ui->status->insertPlainText(">>STOPZ\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnA1_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"A+\"}";
            ui->status->insertPlainText(">>A+\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnA2_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"A-\"}";
            ui->status->insertPlainText(">>A-\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnA3_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"STOPA\"}";
            ui->status->insertPlainText(">>STOPA\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnB1_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"B+\"}";
            ui->status->insertPlainText(">>B+\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnB2_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"B-\"}";
            ui->status->insertPlainText(">>B-\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnB3_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"STOPB\"}";
            ui->status->insertPlainText(">>STOPB\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}

void MainWindow::on_btnRS_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"RESET\"}";
            ui->status->insertPlainText(">>RESET\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}
void MainWindow::on_btnSP_ON_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"SPINDLE ON\"}";
            ui->status->insertPlainText(">>SPINDLE ON\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}


void MainWindow::on_btnSP_OFF_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"SPINDLE OFF\"}";
            ui->status->insertPlainText(">>SPINDLE OFF\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}


void MainWindow::on_load_g_code_2_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"LOAD_G_CODE\"}";
            ui->status->insertPlainText(">>LOAD G CODE\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}


void MainWindow::on_btnSTART_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"START\"}";
            ui->status->insertPlainText(">>START\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet");
    }
}


void MainWindow::on_btnSTOP_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"STOP\"}";
            ui->status->insertPlainText(">>STOP\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect\n");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet\n");
    }
}

void MainWindow::on_btn_sethome_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            set_home = true;
            mes = "{\"MES\": \"SET HOME\"}";
            ui->status->insertPlainText(">>SET HOME\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect\n");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet\n");
    }
}

void MainWindow::on_btn_home_clicked()
{
    if (internet == true)
    {
        if (connect_sucess == true)
        {
            QString mes;
            mes = "{\"MES\": \"HOME\"}";
            ui->status->insertPlainText(">>GO TO HOME\n");
            emit signalGUI(mes);
            ThreadDataPost = new thread_data_post();
            connect(this, SIGNAL(signalGUI(QString)), ThreadDataPost, SLOT(setMes(const QString&)));
        }
        else
        {
            ui->status->insertPlainText(">>Server not connect\n");
        }
    }
    else
    {
       ui->status->insertPlainText(">>Error!!! Not connecting to internet\n");
    }
}

void MainWindow::on_btn_connect_clicked()
{
    if (internet == true)
    {
        if (allow_connect == true)
        {
            ThreadConnectPost = new thread_connect_post();
            ThreadConnectPost->start();
        }
        else
        {
            ui->status->insertPlainText(">>Client not allow connect. Please allow connect in client\n");
        }   
    }
    else
    {
        ui->status->insertPlainText(">>Error!!! Not connecting to internet\n");
    }
}

void MainWindow::on_btn_disconnect_clicked()
{
    if (connect_sucess == true)
    {
        ThreadConnectPost->stop();
        ThreadDataGet->stop();
        ui->Led_8->setPower(false);
        ui->status->insertPlainText(">>Server disconnect\n");
    }
    else
    {
         ui->status->insertPlainText(">>Server not connect\n");
    }

}
void MainWindow::time_connect(const QString &time)
{
    //ui->status_2->insertPlainText(time+"\n");
    if (connect_sucess == true)
    {
        if (mes_time == time)
        {
            dem_time++;
        }
        else
        {
            dem_time = 0;
            lost_connect = false;
        }
        if (dem_time == 50)
        {
            ui->status->insertPlainText(">>Client is lost connect.\n");
            //ui->Led_8->setPower(false);
            lost_connect = true;
            pas_string = "";
        }
        mes_time = time;
    }

}
void MainWindow::setSignal(const QString &string)
{
    if (lost_connect == false)
    {
        if (pas_string != string)
        {
            if (string == "CONNECT SUCCESFULLY")
            {
                ui->Led_8->setPower(true);
                ui->status->insertPlainText(">>Connect to client succesfully\n");
                connect_sucess = true;
                ThreadDataGet = new thread_data_get();
                connect(ThreadDataGet, SIGNAL(signalGUI_get(QString)), this, SLOT(setData(const QString&)));
                ThreadDataGet->start();
            }
            if (string == "ALLOW CONNECT")
            {
                ui->Led_8->setPower(false);
                ui->status->insertPlainText(">>Client allow connect\n");
                allow_connect = true;
                connect_sucess = false;

            }
            if (string == "NOT ALLOW CONNECT")
            {
                ui->Led_8->setPower(false);
                ui->status->insertPlainText(">>Client not allow connect\n");
                allow_connect = false;
                connect_sucess = false;
            }
            pas_string = string;
        }
    }
}

void MainWindow::setData(const QString &string)
{
    if (string != string_monitor_pas)
    {
        posX = "";
        posY = "";
        posZ = "";
        posA = "";
        posB = "";
        velA = "";
        velB = "";
        velX = "";
        velY = "";
        velZ = "";
        spindle_status = "";
        spindle_speed = "";
       // ui->status->insertPlainText(string);
        for (int i = 0 ; i<string.size(); i++)
        {
            if (string[i] == '\"')
            {
                if (string [i+1] == 'X')
                {
                    for (int j = i+6 ; j<i+12 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            posX = posX + string[j];
                        }
                        else
                        {
                            j = i+12;
                        }
                    }
                }
                if (string [i+1] == 'Y')
                {
                    for (int j = i+6 ; j<i+12 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            posY = posY + string[j];
                        }
                        else
                        {
                            j = i+12;
                        }
                    }
                }
                if (string [i+1] == 'Z')
                {
                    for (int j = i+6 ; j<i+12 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            posZ = posZ + string[j];
                        }
                        else
                        {
                            j = i+12 ;
                        }
                    }
                }
                if (string[i+1] == 'A')
                {
                    for (int j = i+6; j<i+12 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            posA = posA + string[j];
                        }
                        else
                        {
                            j = i+12;
                        }
                    }
                }
                if (string[i+1] == 'B')
                {
                    for (int j = i+6; j<i+12 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            posB = posB + string[j];
                        }
                        else
                        {
                            j = i+12;
                        }
                    }
                }
            }

            if (string[i] == 'l')
            {
                if (string [i+1] == 'X')
                {
                    for (int j = i+6 ; j<i+12 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            velX = velX + string[j];
                        }
                        else
                        {
                            j = i+12 ;
                        }
                    }
                }
                if (string [i+1] == 'Y')
                {
                    for (int j = i+6 ; j<i+12 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            velY = velY + string[j];
                        }
                        else
                        {
                            j = i+12 ;
                        }
                    }
                }
                if (string [i+1] == 'Z')
                {
                    for (int j = i+6 ; j<i+12 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            velZ = velZ + string[j];
                        }
                        else
                        {
                            j = i+12 ;
                        }
                    }
                }
                if (string[i+1] == 'A')
                {
                    for (int j = i+6 ; j<i+12 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            velA = velA + string[j];
                        }
                        else
                        {
                            j = i+12;
                        }
                    }
                }
                if (string[i+1] == 'B')
                {
                    for (int j = i+6 ; j<i+12 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            velB = velB + string[j];
                        }
                        else
                        {
                            j = i+12;
                        }
                    }
                }
            }
            if (string[i] == 'L')
            {
                if (string[i+1] == 'E')
                {
                    for (int j = i+6 ; j<i+9 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            spindle_status = spindle_status + string[j];
                        }
                        else
                        {
                            j = i+9;
                        }
                    }
                }
            }
            if (string[i] == 'e')
            {
                if (string[i+1] == 'e')
                {
                    for (int j = i+7 ; j<i+13 ; j++)
                    {
                        if (string[j] != '\"')
                        {
                            spindle_speed = spindle_speed + string[j];
                        }
                        else
                        {
                            j = i+13;
                        }
                    }
                }
            }

        }
        ui->posX->display(posX);
        ui->posY->display(posY);
        ui->posZ->display(posZ);
        ui->posA->display(posA);
        ui->posB->display(posB);

        ui->velX->display(velX);
        ui->velY->display(velY);
        ui->velZ->display(velZ);
        ui->velA->display(velA);
        ui->velB->display(velB);

        ui->splSpeed->display(spindle_speed);
        if (spindle_status == "ON")
        {
            ui->Led_5->setPower(true);
        }
        if (spindle_status == "OFF")
        {
            ui->Led_5->setPower(false);
        }

        //ui->status->insertPlainText(posA+"\n");
        scene->addLine(startX,startY,300-posX.toFloat(),300-posY.toFloat(), QPen(Qt::green));
        ui->grid_2D->fitInView(scene->itemsBoundingRect());
        startX = 300-posX.toFloat();
        startY = 300-posY.toFloat();




        if (set_home == false)
        {
            posXConvert = posXConvert + ((posX.toFloat() - posX_pas.toFloat()) *62 /750);
            posYConvert = -((posY.toFloat() - posY_pas.toFloat()) *75 /750) + posYConvert;
            posZConvert = ((posZ.toFloat() - posZ_pas.toFloat()) *23 /300) + posZConvert;

            QVector3D trucyEnd =QVector3D(3,8,posYConvert);
            QVector3D trucxEnd =QVector3D(posXConvert,48,posYConvert);
            QVector3D truczEnd =QVector3D(posXConvert+2,posZConvert,posYConvert);
            // ve 3d
            OrbitTransformController *controller = new OrbitTransformController(trucytransform);
            controller->setTarget(trucytransform);
            controller->setScale(QVector3D(0.1,0.1,0.1));

            QPropertyAnimation *trucyAnimation = new QPropertyAnimation(trucytransform);
            trucyAnimation->setTargetObject(controller);
            trucyAnimation->setPropertyName("position");
        //    trucyAnimation->setStartValue(QVector3D(3,25,-50));
        //    trucyAnimation->setEndValue(QVector3D(3,25,-40));
            trucyAnimation->setStartValue(trucyStart);
            trucyAnimation->setEndValue(trucyEnd);
            trucyAnimation->setDuration(1000);
            //trucxAnimation->setLoopCount(-1);
            trucyAnimation->start();


            OrbitTransformController *controller1 = new OrbitTransformController(trucxtransform);
            controller1->setTarget(trucxtransform);
            controller1->setScale(QVector3D(0.1,0.1,0.1));

            QPropertyAnimation *trucxAnimation = new QPropertyAnimation(trucxtransform);
            trucxAnimation->setTargetObject(controller1);
            trucxAnimation->setPropertyName("position");
        //    trucxAnimation->setStartValue(QVector3D(-20,63,-45));
        //    trucxAnimation->setEndValue(QVector3D(-5,63,-40));
            trucxAnimation->setStartValue(trucxStart);
            trucxAnimation->setEndValue(trucxEnd);
            trucxAnimation->setDuration(1000);
            //trucxAnimation->setLoopCount(-1);
            trucxAnimation->start();


            OrbitTransformController *controller2 = new OrbitTransformController(trucztransform);
            controller2->setTarget(trucztransform);
            controller2->setScale(QVector3D(0.1,0.1,0.1));

            QPropertyAnimation *truczAnimation = new QPropertyAnimation(trucztransform);
            truczAnimation->setTargetObject(controller2);
            truczAnimation->setPropertyName("position");
        //    truczAnimation->setStartValue(QVector3D(-15,100,-45));
        //    truczAnimation->setEndValue(QVector3D(0,90,-40));
            truczAnimation->setStartValue(truczStart);
            truczAnimation->setEndValue(truczEnd);
            truczAnimation->setDuration(1000);
            //trucxAnimation->setLoopCount(-1);
            truczAnimation->start();

            trucxStart = trucxEnd;
            trucyStart = trucyEnd;
            truczStart = truczEnd;
        }
        else
        {
            set_home = false;
        }



        posX_pas = posX;
        posY_pas = posY;
        posZ_pas = posZ;
        string_monitor_pas = string;
    }
}

void MainWindow::CheckConnect(const QString &check)
{
    if (check_pass != check)
    {
        if (check == "true")
        {
           internet = true;
           ui->Led_9->setPower(true);
           ThreadConnect = new thread_connect();
           connect(ThreadConnect, SIGNAL(signalGUI_connect(QString)), this, SLOT(setSignal(const QString&)));
           connect(ThreadConnect, SIGNAL(timeGUI(QString)), this, SLOT(time_connect(const QString&)));
           ThreadConnect->start();
           creat_thread = true;
           //dem_check_connect = 0;
        }
        if (check == "false")
        {
           internet = false;
           //dem_check_connect++;
//           if (dem_check_connect == 1)
//           {
               ui->status->insertPlainText(">>Error!!! Not connecting to internet\n");
          // }
           ui->Led_9->setPower(false);
           ui->Led_8->setPower(false);
           if (creat_thread == true)
           {
               ThreadConnect->stop();
           }
        }
    }
    check_pass = check;

}

void MainWindow::on_pushButton_clicked()
{
    Data_Process = new data_process(this);
    Data_Process->show();
}

