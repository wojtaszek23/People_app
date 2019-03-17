#include "xmlwriter.h"
#include <QMessageBox>
#include <QDebug>

XmlWriter* XmlWriter::instance = NULL;

XmlWriter::XmlWriter()
{

}

void XmlWriter::store_to_xml(QStandardItemModel *model)
{
    QXmlStreamWriter xmlWriter(&file);
    xmlWriter.setAutoFormatting(true);
qDebug() <<"hej";
    xmlWriter.writeStartDocument();
    xmlWriter.writeStartElement("People");

    /*QStringList header = ( QStringList() << model->horizontalHeaderItem(0)->text() <<
    model->horizontalHeaderItem(1)->text() << model->horizontalHeaderItem(2)->text() <<
    model->horizontalHeaderItem(3)->text() << model->horizontalHeaderItem(4)->text() <<
    model->horizontalHeaderItem(5)->text() << model->horizontalHeaderItem(6)->text() <<
    model->horizontalHeaderItem(7)->text() << model->horizontalHeaderItem(8)->text());
*/
    qDebug() << attr_names.at(5) <<"ho";

    for(int row = 0; row < model->rowCount(); row++)
    {
        xmlWriter.writeStartElement("Person_"+QString::number(row+1));
        for(int col = 0; col < model->columnCount(); col++)
        {
            QString value = model->item(row,col)->text();//data(index,Qt::EditRole).toString();
            qDebug() << attr_names.at(col)<< value;
            xmlWriter.writeTextElement(attr_names.at(col), value);
        }
        xmlWriter.writeEndElement();
    }
    xmlWriter.writeEndElement();
    file.close();
}

void XmlWriter::parse_header(QString header)
{
    qDebug() <<header;
    attr_names.clear();
    attr_names = header.split(";");
    for(int i=0;i<attr_names.size();i++)
    {
        qDebug() << attr_names.at(i);
    }
}

XmlWriter *XmlWriter::get()
{
    if ( instance == NULL )
    {
        instance = new XmlWriter();
    }
    return instance;
}

void XmlWriter::writeModel(QString file_name, QStandardItemModel *model, QString header)
{
    parse_header(header);
    file.setFileName(file_name);
    if(!file.open(QFile::WriteOnly | QFile::Text))
    {
        return;
    }
    store_to_xml(model);
}

