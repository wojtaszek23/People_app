#ifndef DIALOGSAVE_H
#define DIALOGSAVE_H

#include <QDialog>
#include "dialog.h"

class Dialog;

namespace Ui {
class DialogSave;
}

class DialogSave : public QDialog
{
    Q_OBJECT

public:
    explicit DialogSave(Dialog *parent = 0);
    ~DialogSave();

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

private:
    Ui::DialogSave *ui;
    Dialog *dialog;
};

#endif // DIALOGSAVE_H
