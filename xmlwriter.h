#ifndef XMLWRITER_H
#define XMLWRITER_H

#include <QWidget>
#include <QStandardItemModel>
#include <QFile>
#include <QtCore>

class XmlWriter
{
private:
    static QFile file;
    virtual void abstractMethod() = 0;
    static bool store_to_xml(QStandardItemModel *model, const QString &root_name, const QString &node_name,
        const QStringList &header_labels, const bool * const opt_tab);

public:
    static void writeModel(const QString &file_name, QStandardItemModel *model, const QString &root_name,
        const QString &node_name, const QStringList &header_labels, const bool * const opt_tab);
};

#endif // XMLWRITER_H
