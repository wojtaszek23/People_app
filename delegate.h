#ifndef DELEGATE_H
#define DELEGATE_H


//#include <QModelIndex>
#include <QItemDelegate>
#include <QSize>
#include <QObject>
#include <QTextEdit>
//#include "dialog.h"

class Delegate : public QItemDelegate
{
    //Q_OBJECT
public:
    explicit Delegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    static bool modified;

/*signals:
public slots:*/
};

#endif // DELEGATE_H
