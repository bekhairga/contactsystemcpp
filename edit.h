#ifndef EDIT_H
#define EDIT_H

#include <QDialog>
#include "mainwindow.h"

namespace Ui {
class Edit;
}

class Edit : public QDialog
{
    Q_OBJECT

public:
    explicit Edit(QWidget *parent = nullptr);
    void setData(const QString &id);
    QString currentID = nullptr;
    ~Edit();


private slots:
    void on_buttonBox_2_accepted();

    void on_buttonBox_2_rejected();

private:
    Ui::Edit *ui;
};

#endif // EDIT_H
