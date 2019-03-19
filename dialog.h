#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "delegate.h"
#include "dialogsave.h"
#include "modelmanager.h"

namespace Ui {
class Dialog;
}

class Delegate;

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void addFileName(QString);

private slots:
    void on_comboBox_activated(const QString &arg1);

    void on_pushButton_2_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog *ui;
    Delegate *delegate;
};

#endif // DIALOG_H
