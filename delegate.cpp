#include "delegate.h"


Delegate::Delegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget *Delegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==8)
    {
        return NULL;
    }
    QTextEdit *editor = new QTextEdit (parent);
    return editor;
}

void Delegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    QString value = index.model()->data(index,Qt::EditRole).toString();
    value.remove('\n');
    QTextEdit *textedit = static_cast <QTextEdit*>(editor);
    textedit->setText(value);
}

void Delegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    QTextEdit *textedit = static_cast <QTextEdit*>(editor);
    QString value = textedit->toPlainText();
    value.remove('\n');
    if(index.column() == 7)
    {
        QString date = Date::countStringAge(value);
        if (date != "-1")
        {
            model->setData(index,value,Qt::EditRole);
            model->setData(index.sibling(index.row(), 8), date, Qt::EditRole);
        }
        else
        {
            model->setData(index, "", Qt::EditRole);
            model->setData(index.sibling(index.row(), 8), "", Qt::EditRole);
            return;
        }
    }
    else if ( (index.column()==3 || index.column()==4 || index.column()==6) && (value != "") )
    {
        int value2 = value.toInt();
        value = QString::number(value2);
    }
    if (value != index.model()->data(index,Qt::DisplayRole).toString())
    {
        ModelManager::get()->modified = true;
    }
    if (value.remove(' ') == "")
    {
        model->setData(index,"",Qt::EditRole);
    }
    else
    {
        model->setData(index,value,Qt::EditRole);
        if(index.row() == model->rowCount() - 1)
        {
            model->insertRow(model->rowCount());
        }
    }
}
