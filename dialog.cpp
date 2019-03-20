#include "dialog.h"
#include "ui_dialog.h"
#include <QMessageBox>
#include <QKeyEvent>
//#include <QCloseEvent>

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),
    key_ctrl_hold(false),
    key_alt_hold(false)
{
    ui->setupUi(this);

    delegate = new Delegate(this);

    ModelManager::setWidget(static_cast<QWidget*>(this));

    ui->tableView->setItemDelegate(delegate);

    QDir dir;

    foreach(QFileInfo fi, dir.entryInfoList())
    {
        if (fi.suffix() == "xml")
        {
            ui->comboBox->addItem(fi.fileName());
        }
    }

    if(ui->comboBox->count() > 0)
    {
        ModelManager::get()->loadFileOrder(ui->comboBox->currentText());
    }

    ui->tableView->setModel(ModelManager::get()->model);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::addFileName(QString txt)
{
    ui->comboBox->addItem(txt);
}

void Dialog::on_comboBox_activated(const QString &arg1)
{
    if (arg1 == "" || ModelManager::get()->last_file_name == arg1)
    {
        return;
    }
    ModelManager::get()->loadFileOrder(arg1);
    ui->tableView->setModel(ModelManager::get()->model);
}



void Dialog::on_pushButton_2_clicked()
{
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    ModelManager::get()->deleteRecordsOrder(selection);
}

void Dialog::on_buttonBox_accepted()
{
    if(ui->comboBox->currentText() == "")
    {
        DialogSave *dialog_save = new DialogSave(this);
        dialog_save->show();
    }
    else
    {
        if ( ModelManager::get()->saveFileOrder(ui->comboBox->currentText()))
        {
            QMessageBox::information(this, "Information", "Current data were saved succesfully");
        }
        else
        {
            QMessageBox::information(this, "Information", "Data were not saved");
        }
    }
}

void Dialog::on_buttonBox_rejected()
{
    ModelManager::get()->loadFileOrder(ui->comboBox->currentText());
    ui->tableView->setModel(ModelManager::get()->model);
}

void Dialog::keyPressEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Delete)
    {
        QModelIndexList selectedRows = ui->tableView->selectionModel()->selectedRows();
        bool result = ModelManager::get()->deleteRecordsOrder(selectedRows);
        if (result == false)
        {
            ModelManager::get()->clearSelected(ui->tableView->selectionModel()->selection());
        }
        return;
    }

    if(event->key() == Qt::Key_Control)
    {
        key_ctrl_hold = true;
    }
    if(event->key() == Qt::Key_Alt)
    {
        key_alt_hold = true;
    }

    if ( key_ctrl_hold && key_alt_hold )
    {
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    }
}

void Dialog::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Control)
    {
        key_ctrl_hold = false;
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    }
    if(event->key() == Qt::Key_Alt)
    {
        key_alt_hold = false;
        ui->tableView->setSelectionBehavior(QAbstractItemView::SelectItems);
    }
}


void Dialog::closeEvent(QCloseEvent *event)
{
    if(ModelManager::get()->modified == true)
    {
        QMessageBox::StandardButton resBtn = QMessageBox::question(this,
            "Quit", "Are You sure You want to quit? Not saved data will not be stored",
            QMessageBox::Cancel | QMessageBox::Close);

        if(resBtn == QMessageBox::Close)
        {
            event->accept();
        }
        else
        {
            event->ignore();
        }
    }
}
