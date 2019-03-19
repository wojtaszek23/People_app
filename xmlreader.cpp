#include "xmlreader.h"
#include <QMessageBox>
#include <QDebug>


QFile XmlReader::file;

bool XmlReader::store_to_model(QStandardItemModel *model, const QString &root_name,
    const QString &node_name, const QStringList &header_labels)
{
    QXmlStreamReader reader(&file);

    if(!reader.readNextStartElement())
    {
        file.close();
        return false;
    }
    if(reader.name() != root_name )
    {
        file.close();
        return false;
    }

    reader.readNext();
    int row = 0;

    while(reader.readNextStartElement())
    {
        if(reader.name().startsWith(node_name) != true)
        {
            reader.skipCurrentElement();
            continue;
        }
        model->appendRow(NULL);

        for(int col = 0; col < header_labels.size(); col++)
        {
            reader.readNextStartElement();
            QModelIndex index = model->index(row, col, QModelIndex());

            if(reader.name() == header_labels.at(col))
            {
                model->setData(index, reader.readElementText());
            }
            else
            {
                model->setData(index,"");
                reader.skipCurrentElement();
                //qDebug() << "failed to read properly: " << header_labels.at(col) << reader.name();
            }
        }

        reader.skipCurrentElement();
        row++;
    }

    file.close();
    return true;
}

QStandardItemModel *XmlReader::getModel(QWidget *widget, const QString &file_name,
    const QString &root_name, const QString &node_name, const QStringList &header_labels)
{
    QStandardItemModel *model = new QStandardItemModel(0,header_labels.size(),widget);
    model->setHorizontalHeaderLabels(header_labels);
    file.setFileName(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        delete model;
        QMessageBox::warning(widget, "Error", file_name + QString(" - could not open file."));
        return NULL;
    }
    if(!store_to_model(model, root_name, node_name,header_labels))
    {
        delete model;
        QMessageBox::warning(widget, "Error", file_name + QString(" - incorrect structure of file."));
        return NULL;
    }
    return model;
}

