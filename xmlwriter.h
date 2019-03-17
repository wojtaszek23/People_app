#ifndef XMLWRITER_H
#define XMLWRITER_H
#include "dialog.h"

class XmlWriter
{
private:
    static XmlWriter *instance;
    QFile file;
    QStringList attr_names;

    XmlWriter();
    void store_to_xml(QStandardItemModel *model);
    void parse_header(QString header);

public:
    static XmlWriter *get();
    void writeModel(QString file_name, QStandardItemModel *model, QString header);
};

#endif // XMLWRITER_H
