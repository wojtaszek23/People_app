#ifndef XMLREADER_H
#define XMLREADER_H
#include "dialog.h"

class XmlReader
{
private:
    static XmlReader *instance;
    QFile file;
    QStandardItemModel *model;
    QStringList attr_names;

    XmlReader();
    bool store_to_model(QString root_name, QString node_name);
    void parse_header(QString header);

public:
    static XmlReader* get();
    QStandardItemModel* getModel(Dialog *dialog, QString file_name, QString root_name, QString node_name, QString header);

};

#endif // XMLREADER_H
