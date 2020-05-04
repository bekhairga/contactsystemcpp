#include "addnumber.h"
#include "ui_addnumber.h"
#include <QMessageBox>
Addnumber::Addnumber(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Addnumber)
{
    ui->setupUi(this);
    this->setWindowTitle("Add contact");
    ui->comboBox->addItem("Male");
    ui->comboBox->addItem("Female");
    ui->comboBox->addItem("Something");
    MainWindow connection;
    if(connection.connectionOpen()){
        qDebug()<<"DB connected";
    }else{
        qDebug() << "DB not connected";
    }


}

Addnumber::~Addnumber()
{
    delete ui;
}





void Addnumber::on_buttonBox_accepted()
{
    MainWindow connection;

    QString first_name, last_name, gender, number, description;

    first_name = ui->lineEdit_firstName->text();
    last_name = ui->lineEdit_lastName->text();
    gender = ui->comboBox->currentText();
    number = ui->lineEdit_number->text();
    description = ui->textEdit->toPlainText();
    if(first_name != "" && last_name !="" && gender !="" && number !=""){
        if(number.toInt()){
            connection.connectionOpen();
            QSqlQuery query;
            number = QString::number(number.toInt());
            query.prepare("insert into numbers (first_name, last_name, number, gender, description) values('"+first_name+"', '"+last_name+"', '"+number+"', '"+gender+"', '"+description+"');");

            if(query.exec()){
                QMessageBox::critical(this, tr("Success"), tr("Saved"));
                connection.connectionClose();
            }
            else{
                QMessageBox::critical(this, tr("Error"), query.lastError().text());
            }
        }
        else{
            QMessageBox::StandardButton reply = QMessageBox::critical(this, tr("Error"), tr("Incorrect number"));
            if(reply == QMessageBox::Ok){
                Addnumber::show();
            }
        }

    }
    else{
        QMessageBox::StandardButton reply = QMessageBox::critical(this, tr("Error"), tr("Incorrect input"));
        if(reply == QMessageBox::Ok){
            Addnumber::show();
        }
    }
}
