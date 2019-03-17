#include "delegate.h"
//#include <QString>
#include <QDebug>

Delegate::Delegate(QObject *parent) :
    QItemDelegate(parent)
{
    modified = false;
}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    static int abc=0;
    qDebug() << "createEditor" <<abc++;
    if(index.column()==8)
    {
        return NULL;
    }
    QTextEdit *editor = new QTextEdit (parent);
    return editor;
}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    static int abc=0;
    qDebug() << "setEditorData"<<abc++;
    QString value = index.model()->data(index,Qt::EditRole).toString();

    QTextEdit *textedit = static_cast <QTextEdit*>(editor);
    textedit->setText(value);
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    static int abc=0;
    qDebug() << "setModelData"<<abc++;
    QTextEdit *textedit = static_cast <QTextEdit*>(editor);
    QString value = textedit->toPlainText();
    if ( (index.column()==3 || index.column()==4 || index.column()==6) && (value != "") )
    {
        int value2 = value.toInt();
        value = QString::number(value2);
    }
    if (value != index.model()->data(index,Qt::DisplayRole).toString())
    {
        modified = true;
    }
    model->setData(index,value,Qt::EditRole);
}
