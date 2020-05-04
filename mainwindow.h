#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "addnumber.h"
#include "edit.h"
#include <QtSql>
#include <QtDebug>
#include <QFileInfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    QSqlDatabase contactDB;
    QString tableIndex = "none";
    void connectionClose(){
        contactDB.close();
        contactDB.removeDatabase(QSqlDatabase::defaultConnection);
    };
    bool connectionOpen(){
        contactDB = QSqlDatabase::addDatabase("QSQLITE");

        QString path = QCoreApplication::applicationDirPath() + "/database.db";
        //contactDB.setDatabaseName("/home/klaun/contactsystem/database.db");
        contactDB.setDatabaseName(path);


        qDebug() << path;
        if(contactDB.open()){
           qDebug() << "Connected";
           return true;
        }
        else{
           qDebug() << "Not connected";
           return false;
        }
    }


public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_load_data_clicked();

    void on_addContact_clicked();

    void on_editContact_clicked();

    void on_tableView_clicked(const QModelIndex &index);

    void on_pushButton_2_clicked();


    void on_searchPanel_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
public:
      void refreshData(QString searching);

};
#endif // MAINWINDOW_H
