#ifndef DELEGATE_H
#define DELEGATE_H


#include <QItemDelegate>
#include <QObject>
#include <QTextEdit>
#include "modelmanager.h"
#include "date.h"

class Delegate : public QItemDelegate
{
public:
    explicit Delegate(QObject *parent = 0);
    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

/*signals:
public slots:*/
};

#endif // DELEGATE_H
