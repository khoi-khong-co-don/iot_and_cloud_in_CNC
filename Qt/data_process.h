#ifndef DATA_PROCESS_H
#define DATA_PROCESS_H

#include <QDialog>
#include "customtablemodel.h"
#include "thread_get_product.h"
#include <QtCharts/QBarSet>

namespace Ui {
class data_process;
}

class data_process : public QDialog
{
    Q_OBJECT

public:
    explicit data_process(QWidget *parent = nullptr);
    ~data_process();
    //int hashFunction(string str);


private slots:
    void customtable(const QString &time);
    void on_dateEdit_userDateChanged(const QDate &date);
    void customtable_date(const QString &time);

    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_choose_month_currentTextChanged(const QString &arg1);

private:
    Ui::data_process *ui;
    customtablemodel *m_model;
    thread_get_product *ThreadGetProduct;
    void ve_do_thi();
    int hashFunction(QString str);
};

#endif // DATA_PROCESS_H
