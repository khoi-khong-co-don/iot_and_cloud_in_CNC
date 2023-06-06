#include "login.h"
#include "ui_login.h"
#include "QMessageBox"

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");

}

Login::~Login()
{
    delete ui;
}

void Login::on_btnLogin_clicked()
{
    QString username = ui->lineEditName->text();
    QString password = ui->lineEditPass->text();
    if (username == "khoi" && password == "khoi")
    {
        this->close();
        mainwindow = new MainWindow(this);
        mainwindow->show();
    }
    else
    {
        QMessageBox::warning(this, "Login","Username hoặc Password không đúng!");
    }

}

