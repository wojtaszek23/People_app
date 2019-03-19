#include "xmlwriter.h"
#include <QMessageBox>
#include <QDebug>
//#include <QString>


QFile XmlWriter::file;

bool XmlWriter::store_to_xml(QStandardItemModel *model, const QString &root_name, const QString &node_name,
    const QStringList &header_labels, const bool * const opt_tab)
{
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement(root_name);
    QString error_list = "";

    for(int row = 0; row < model->rowCount(); row++)
    {
        xmlWriter.writeStartElement(node_name+QString::number(row+1));
        for(int col = 0; col < model->columnCount(); col++)
        {
            QModelIndex index = model->index(row,col,QModelIndex());
            QString value = model->data(index,Qt::EditRole).toString();

            if(value == "")
            {
                if ( opt_tab[col] == false )
                    error_list += QString::number(row) + "," + QString::number(col) + "; ";
            }

            xmlWriter.writeTextElement(header_labels.at(col), value);

        }
            xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    if(error_list != "")
    {
        QMessageBox errorMsg;
        errorMsg.setText("The table is incorrect!");
        errorMsg.setInformativeText("Following cells do not have data:\n"
            + error_list + "\nDo You want to save the table anyway?");
        errorMsg.setStandardButtons(QMessageBox::Save | QMessageBox::Cancel);
        errorMsg.setDefaultButton(QMessageBox::Cancel);
        errorMsg.setIcon(QMessageBox::Warning);
        int result = errorMsg.exec();
        if(result == 0x00400000)
        {
            file.remove();
            return false;
        }
    }
    return true;
}

void XmlWriter::writeModel(const QString &file_name, QStandardItemModel *model, const QString &root_name,
    const QString &node_name, const QStringList &header_labels, const bool * const opt_tab)
{
    file.setFileName(file_name+"_temporary_^r^_-_-_file");
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    if ( store_to_xml(model, root_name, node_name, header_labels, opt_tab) == true )
    {
        if(QFile::exists(file_name))
        {
            QFile::remove(file_name);
        }
        file.rename(file_name);
    }
}
