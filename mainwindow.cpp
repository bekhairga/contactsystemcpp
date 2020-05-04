#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Contacts Page");
    if(connectionOpen()){
        qDebug()<<"Connected";
    }
    else{
        qDebug()<<"Not Connected";
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::refreshData(QString searching){
     connectionOpen();
     QSqlQueryModel *model = new QSqlQueryModel();
     QSqlQuery *query = new QSqlQuery(contactDB);
    if(searching == ""){
        query->prepare("select * from numbers order by first_name;");
        query->exec();
        model->setQuery(*query);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setModel(model);
        ui->tableView->setColumnHidden(0,true);
        ui->tableView->setColumnHidden(5,true);

    }
    else{
        query->prepare("select * from numbers where first_name like '"+searching+"%' or last_name like '"+searching+"%' order by first_name;");
        query->exec();
        model->setQuery(*query);
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
        ui->tableView->setModel(model);
        ui->tableView->setColumnHidden(0,true);
        ui->tableView->setColumnHidden(5,true);
    }
     connectionClose();

}

void MainWindow::on_load_data_clicked()
{
  MainWindow::refreshData("");

}



void MainWindow::on_addContact_clicked()
{
    Addnumber addnumber;
    addnumber.setModal(true);
    addnumber.exec();
    this->refreshData("");

}

void MainWindow::on_editContact_clicked()
{
    Edit edit;
    edit.setModal(true);
    if(tableIndex != "none"){
        edit.setData(tableIndex);
        edit.exec();
    }
    this->refreshData("");
    tableIndex = "none";

}





void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    QModelIndexList mySelection = ui->tableView->selectionModel()->selectedIndexes();
    QString selected = mySelection[0].data().toString();
    tableIndex = selected;
    qDebug() << tableIndex;
    ui->fname_view->setText(mySelection[1].data().toString());
    ui->lname_view->setText(mySelection[2].data().toString());
    ui->gender_view->setText(mySelection[4].data().toString());
    ui->number_view->setText(mySelection[3].data().toString());
    ui->desc_view->setText(mySelection[5].data().toString());
}

void MainWindow::on_pushButton_2_clicked()
{
    connectionOpen();
    QSqlQuery query;
        QMessageBox::StandardButton reply;
        reply =  QMessageBox::question(this, tr("Delete"), tr("Do you want to delete contact"), QMessageBox::Yes | QMessageBox::No);
        if(reply == QMessageBox::Yes){
          query.prepare("delete from numbers where id = '"+tableIndex+"'");
           if(query.exec()){
              QMessageBox::critical(this, tr("Delete"), tr("Deleted"));
           }
           else{
               QMessageBox::critical(this, tr("Error"), query.lastError().text());
           };
        }
        connectionClose();
        this->refreshData("");
    }

void MainWindow::on_searchPanel_textChanged(const QString &arg1)
{

    QString searching = ui->searchPanel->text();
    qDebug() << searching;
       this->refreshData(searching);

}
