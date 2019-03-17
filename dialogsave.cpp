#include "dialogsave.h"
#include "ui_dialogsave.h"

DialogSave::DialogSave(Dialog *parent) :
    dialog(parent),
    ui(new Ui::DialogSave)
{
    ui->setupUi(this);
}

DialogSave::~DialogSave()
{
    delete ui;
}

void DialogSave::on_buttonBox_rejected()
{
    //dialog->show();
    this->close();
}

void DialogSave::on_buttonBox_accepted()
{
    qDebug() <<"here";
    //dialog->show();
    Dialog::file_arleady_created = true;
    dialog->saveFile(ui->lineEdit->text()+".xml");
    dialog->addItemToCombo(ui->lineEdit->text()+".xml");
    //dialog->setComboBoxText(ui->lineEdit->text()+".xml");
    this->close();
}
