#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "thread_connect.h"
#include "thread_connect_post.h"
#include "thread_data_get.h"
#include "thread_data_post.h"
#include "thread_check_connect.h"
#include "QGraphicsScene"
#include "QGraphicsItem"
#include "data_process.h"


//#include <Qt3DRender/QMaterial>
//#include <Qt3DExtras/QPhongAlphaMaterial>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QGraphicsScene* scene = new QGraphicsScene;


protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void timer_timeout();
    void on_load_g_code_clicked();
    void grid_2d();
    void on_comboBox_currentTextChanged(const QString &arg1);
    void on_btnX1_clicked();
    void on_btnX2_clicked();
    void on_btnX3_clicked();
    void on_btnY1_clicked();
    void on_btnY2_clicked();
    void on_btnY3_clicked();
    void on_btnZ1_clicked();
    void on_btnZ2_clicked();
    void on_btnZ3_clicked();
    void on_btnA1_clicked();
    void on_btnA2_clicked();
    void on_btnA3_clicked();
    void on_btnB1_clicked();
    void on_btnB2_clicked();
    void on_btnB3_clicked();


    void on_btnRS_clicked();

    void on_btnSP_ON_clicked();

    void on_btnSP_OFF_clicked();

    void on_load_g_code_2_clicked();

    void on_btnSTART_clicked();

    void on_btnSTOP_clicked();

    void on_btn_connect_clicked();
    void setSignal(const QString &string);
    void CheckConnect(const QString &check);
    void setData(const QString &string);
    void on_btn_disconnect_clicked();
    void time_connect(const QString &time);



    void on_pushButton_clicked();

    void on_btn_sethome_clicked();
    void on_btn_home_clicked();
    void model3d();

private:
    Ui::MainWindow *ui;
    thread_connect *ThreadConnect;
    thread_connect_post *ThreadConnectPost;
    thread_data_get *ThreadDataGet;
    thread_data_post *ThreadDataPost;
    thread_check_connect *ThreadCheckConnect;
    data_process *Data_Process;
signals:
    void signalGUI(QString);
};
#endif // MAINWINDOW_H
