#include "dialog.h"
#include "ui_dialog.h"
#include "xmlreader.h"
#include "xmlwriter.h"
#include <QMessageBox>

bool Delegate::modified;
bool Dialog::file_arleady_created = false;

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    Delegate::modified = false;
    //file_arleady_created = false;

    ui->setupUi(this);

    delegate = new Delegate(this);

    model = new QStandardItemModel(0,9,this);

    ui->tableView->setItemDelegate(delegate);

    //set dirs to comboBox
    QDir dir;

    foreach(QFileInfo fi, dir.entryInfoList())
    {
        if (fi.suffix() == "xml")
        {
            ui->comboBox->addItem(fi.fileName());
        }
    }

    //set table header
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::setComboBoxText(QString text)
{
    on_comboBox_currentTextChanged(text);
    on_buttonBox_accepted();
}

void Dialog::saveFile(QString filename)
{
    QString tmp_header = header_labels.join(';');
    tmp_header.remove(' ');
    XmlWriter::get()->writeModel(filename, model, tmp_header);
    Delegate::modified = false;
    QMessageBox::information(this, "Information", "Current database saved to " + filename);
}

void Dialog::addItemToCombo(QString txt)
{
    qDebug() << "txt";
    ui->comboBox->addItem(txt);
}

void Dialog::on_comboBox_currentTextChanged(const QString &arg1)
{
    if(file_arleady_created == true)
    {
        file_arleady_created = false;
        return;
    }
    header_labels = ( QStringList() << "First Name" << "Last Name" <<
        "Street Name" << "House Number" << "Apartment Number" <<
        "Postal Code" << "Phone Number" << "Day Of Birth" << "Age");
    model->setHorizontalHeaderLabels(header_labels);

    if(arg1 == "")
    {
        model->setHorizontalHeaderLabels(header_labels);
        ui->tableView->setModel(model);
        return;
    }

    Delegate::modified = false; // ? czy tutaj ???
    QString file_name = arg1;
    QStandardItemModel *tmp_model;
    QString tmp_header = header_labels.join(';');
    tmp_header.remove(' ');

    tmp_model = XmlReader::get()->getModel(this, file_name, "People", "Person", tmp_header);

    delete model;
    model = NULL;

    if (tmp_model != NULL)
    {
        model = tmp_model;
    }
    else
    {
        model = new QStandardItemModel(0,9,this);
    }
    model->setHorizontalHeaderLabels(header_labels);
    ui->tableView->setModel(model);
}

void Dialog::on_pushButton_clicked()
{
    /*
    if(ui->comboBox->currentText() == "")
    {
        on_comboBox_currentTextChanged("");
    }
    */

    QStringList str_row = ( QStringList() << ui->lineEdit->text() << ui->lineEdit_2->text() <<
        ui->lineEdit_3->text() << ui->lineEdit_4->text() << ui->lineEdit_5->text() <<
        ui->lineEdit_6->text() << ui->lineEdit_7->text() << ui->lineEdit_8->text() << "0" );

    bool flag = false;

    for(int i = 0; i < str_row.size() - 1; i++)
    {
        if(header_labels.at(i).endsWith("Number") == true)
        {
            str_row.replace(i,QString::number(str_row.at(i).toInt()));
            if (i == 4 && str_row.at(i) == "0")
            {
                str_row.replace(i,"");
            }
        }
        if( i!=4 && str_row.at(i) == "" || str_row.at(i) == "0" )
        {
            flag = true;
            i = str_row.size();
        }
    }

    if (flag)
    {
        QMessageBox::information(this,"Warning", "Entered data are incorrect.");
        return;
    }

    int row = model->rowCount();
    model->appendRow(NULL);
    for(int col = 0; col < model->columnCount() ; col++)
    {
        QModelIndex index = model->index(row, col, QModelIndex());
        model->setData(index, str_row.at(col));
    }

    ui->lineEdit->setText("");
    ui->lineEdit_2->setText("");
    ui->lineEdit_3->setText("");
    ui->lineEdit_4->setText("");
    ui->lineEdit_5->setText("");
    ui->lineEdit_6->setText("");
    ui->lineEdit_7->setText("");
    ui->lineEdit_8->setText("");

    Delegate::modified = true;
}


void Dialog::on_pushButton_2_clicked()
{
    if(model->rowCount() == 0)
    {
        return;
    }
    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();
    //qDebug() << "sel count" << selection.count();
    if(selection.count() != 0)
    {
        QModelIndex index = selection.at(0);
        model->removeRows(index.row(),selection.count(), QModelIndex());
        Delegate::modified = true;
    }
}

void Dialog::on_buttonBox_accepted()
{
    qDebug() << "on_but_acc";
    if(model->rowCount() == 0)
    {
        return;
    }
    if(ui->comboBox->currentText() == "")
    {
        DialogSave *dialog_save = new DialogSave(this);
        dialog_save->show();
        return;
    }

    if (Delegate::modified == true)
    {
        QString tmp_header = header_labels.join(';');
        tmp_header.remove(' ');
        XmlWriter::get()->writeModel(ui->comboBox->currentText(), model, tmp_header);
        Delegate::modified = false;
        QMessageBox::information(this, "Information", "Current database saved to " + ui->comboBox->currentText());
    }
    else
    {
        QMessageBox::information(this, "Information", "No changes were made - not saved");
    }
}

void Dialog::on_buttonBox_rejected()
{
    on_comboBox_currentTextChanged(ui->comboBox->currentText());
}
