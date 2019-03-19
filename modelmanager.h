#ifndef MODEL_MANAGER_H
#define MODEL_MANAGER_H
#include <QString>
#include <QStringList>
#include <QStandardItemModel>
#include <QModelIndexList>
#include <QWidget>
#include <QSettings>
#include "xmlreader.h"
#include "xmlwriter.h"

class Dialog;

class ModelManager
{
private:
    static ModelManager *instance;
    static int error_state;
    ModelManager();
    void initModel();
    QString root_name;
    QString node_name;
    QStringList header_labels;
    QStringList header_labels2;
    bool *opt_tab;
    static QWidget* widget;
public:
    QStandardItemModel *model;
    static bool modified;
    QString last_file_name;
    static ModelManager *get();
    static void setWidget(QWidget* m_widget);
    bool saveFileOrder(const QString &file_name);
    bool loadFileOrder(const QString &file_name);
    bool saveFile(const QString &file_name);
    bool loadFile(const QString &file_name);
    bool deleteRecordsOrder(const QModelIndexList &selection);
    bool deleteRecords(const QModelIndexList &selection);
    void removeEmptyRows();
    void removeNotFullRows();
};

#endif // MODEL_MANAGER_H
