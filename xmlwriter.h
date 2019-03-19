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
    static bool store_to_xml(const QStandardItemModel * const model, const QString &root_name, const QString &node_name,
        const QStringList &header_labels, const bool * const opt_tab);
    static bool isEmptyRow(const QStandardItemModel *const model, int row);

public:
    static bool writeModel(const QString &file_name, const QStandardItemModel * const model, const QString &root_name,
        const QString &node_name, const QStringList &header_labels, const bool * const opt_tab);
};

#endif // XMLWRITER_H
