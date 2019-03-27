#ifndef XMLREADER_H
#define XMLREADER_H

#include <QWidget>
#include <QStandardItemModel>
#include <QFile>
#include <QtCore>

class XmlReader
{
private:
    static QFile file;
    virtual void abstractMethod() = 0;
    static bool store_to_model(QStandardItemModel *model, const QString &root_name,
        const QString &node_name, const QStringList &header_labels);

public:
    static QStandardItemModel* getModel(QWidget* dialog, const QString &file_name,
        const QString &root_name, const QString &node_name, const QStringList &header_labels, const QStringList &header_labels2);

};

#endif // XMLREADER_H
