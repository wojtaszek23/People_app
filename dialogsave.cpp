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
    this->close();
}

void DialogSave::on_buttonBox_accepted()
{
    ModelManager::get()->saveFile(ui->lineEdit->text()+".xml");
    dialog->addFileName(ui->lineEdit->text()+".xml");
    this->close();
}
