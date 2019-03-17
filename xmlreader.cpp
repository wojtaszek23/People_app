#include "xmlreader.h"
#include <QMessageBox>
#include <QDebug>

XmlReader* XmlReader::instance = NULL;

XmlReader::XmlReader()
{

}


bool XmlReader::store_to_model(QString root_name, QString node_name)
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

        for(int col = 0; col < attr_names.size(); col++)
        {
            reader.readNextStartElement();
            QModelIndex index = model->index(row, col, QModelIndex());

            if(reader.name() == attr_names.at(col))
            {
                model->setData(index, reader.readElementText());
            }
            else
            {
                model->setData(index,"");
                reader.skipCurrentElement();
                //qDebug() << "failed to read properly: " << attr_names.at(col) << reader.name();
            }
        }

        reader.skipCurrentElement();
        row++;
    }

    file.close();
    return true;
}

void XmlReader::parse_header(QString header)
{
    attr_names.clear();
    attr_names = header.split(";");
}

XmlReader *XmlReader::get()
{
    if (instance == NULL)
    {
        instance = new XmlReader();
    }
    return instance;
}

QStandardItemModel *XmlReader::getModel(Dialog *dialog, QString file_name, QString root_name, QString node_name, QString header)
{
    parse_header(header);
    model = NULL;
    model = new QStandardItemModel(0,9,dialog);
    file.setFileName(file_name);
    if(!file.open(QFile::ReadOnly | QFile::Text))
    {
        QMessageBox::information(dialog, "Error", file_name + QString(" - could not open file."));
        return NULL;
    }
    if(!store_to_model(root_name, node_name))
    {
        QMessageBox::information(dialog, "Error", file_name + QString(" - incorrect structure of file."));
        return NULL;
    }
    return model;
}

