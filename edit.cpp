#include "edit.h"
#include "ui_edit.h"
#include <QMessageBox>

Edit::Edit(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Edit)
{

    ui->setupUi(this);
    ui->comboBox->addItem("Male");
    ui->comboBox->addItem("Female");
    ui->comboBox->addItem("Something");
    this->setWindowTitle("Edit Page");
    MainWindow connection;
    connection.connectionOpen();
    QSqlQuery query;
    if(currentID != nullptr){
        query.prepare("select * from numbers where id = '"+currentID+"'");
        if(query.exec()){
            while(query.next()){
                ui->lineEdit_firstName->setText(query.value(1).toString());
                ui->lineEdit_lastName->setText(query.value(2).toString());
                ui->lineEdit_number->setText(query.value(3).toString());
                int index = ui->comboBox->findText(query.value(4).toString());
                ui->comboBox->setCurrentIndex(index);
                ui->lineEdit_description->setText(query.value(5).toString());
            }
        }
    }



}

Edit::~Edit()
{
    delete ui;
}

void Edit::setData(const QString &id){
    this->currentID = id;
        MainWindow connection;
        connection.connectionOpen();
        QSqlQuery query;
        if(currentID != nullptr){
            query.prepare("select * from numbers where id = '"+currentID+"';");
            if(query.exec()){
                while(query.next()){
                    ui->lineEdit_firstName->setText(query.value(1).toString());
                    ui->lineEdit_lastName->setText(query.value(2).toString());
                    ui->lineEdit_number->setText(query.value(3).toString());
                    int index = ui->comboBox->findText(query.value(4).toString());
                    ui->comboBox->setCurrentIndex(index);
                    ui->lineEdit_description->setText(query.value(5).toString());
                }
            }
        }
        connection.close();
}


void Edit::on_buttonBox_2_accepted()
{
    MainWindow connection;
    QString first_name, last_name, gender, number, description;
    first_name = ui->lineEdit_firstName->text();
    last_name = ui->lineEdit_lastName->text();
    gender = ui->comboBox->currentText();
    number = ui->lineEdit_number->text();
    description = ui->lineEdit_description->toPlainText();
    connection.connectionOpen();
    QSqlQuery query;
    query.prepare("update numbers set first_name = '"+first_name+"', last_name= '"+last_name+"', number = '"+number+"', gender = '"+gender+"', description = '"+description+"' where id ='"+currentID+"' ;");

    if(first_name != "" && last_name !="" && gender !="" && number !=""){
        if(number.toUInt()){

            if(query.exec()){
                QMessageBox::critical(this, tr("Edited"), tr("Edited"));
                connection.connectionClose();
                this->hide();
            }
            else{
                QMessageBox::critical(this, tr("Error"), query.lastError().text());
            }
        }
        else{
            QMessageBox::StandardButton reply = QMessageBox::critical(this, tr("Error"), tr("Incorrect number"));
            if(reply == QMessageBox::Ok){
                this->show();
            }
        }

    }
    else{
        QMessageBox::StandardButton reply = QMessageBox::critical(this, tr("Error"), tr("Incorrect input"));
        if(reply == QMessageBox::Ok){
            this->show();
        }
    }
}


void Edit::on_buttonBox_2_rejected()
{
    hide();
}
