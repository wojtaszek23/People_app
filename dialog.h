#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QtCore>
#include <QtGui>
#include <QLineEdit>
#include "delegate.h"
#include "dialogsave.h"

namespace Ui {
class Dialog;
//class DialogSave;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void setComboBoxText(QString text);
    void saveFile(QString);
    void addItemToCombo(QString);

    //
    static bool file_arleady_created;
    //

private slots:
    void on_comboBox_currentTextChanged(const QString &arg1);

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::Dialog *ui;
    QStandardItemModel *model;
    Delegate *delegate;
    QStringList header_labels;
    QString currentFileName;
};

#endif // DIALOG_H
