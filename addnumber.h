#ifndef ADDNUMBER_H
#define ADDNUMBER_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class Addnumber;
}

class Addnumber : public QDialog
{
    Q_OBJECT

public:

    explicit Addnumber(QWidget *parent = nullptr);
    ~Addnumber();

private slots:
    void on_buttonBox_accepted();

private:
    Ui::Addnumber *ui;
};

#endif // ADDNUMBER_H
