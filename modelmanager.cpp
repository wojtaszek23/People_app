#include "modelmanager.h"
#include <QModelIndexList>
#include <QtAlgorithms>

ModelManager* ModelManager::instance = NULL;

int ModelManager::error_state = 0;

bool ModelManager::modified = false;

QWidget* ModelManager::widget = NULL;



ModelManager::ModelManager()
{
    initModel();
    last_file_name = "";

    header_labels2.append(header_labels);
    model = new QStandardItemModel(1,header_labels.size(),widget);

    model->setHorizontalHeaderLabels(header_labels);
    for(int i = 0; i < header_labels.size() ; i++)
    {
        QString tmp_string = header_labels2.at(i);
        tmp_string = tmp_string.remove(' ');
        header_labels2.replace(i, tmp_string);
    }
}

void ModelManager::initModel()
{
    QSettings settings("model-skeleton.ini", QSettings::IniFormat);

    root_name = settings.value("RootName").toString();
    node_name = settings.value("NodeName").toString();

    int attr_nums = settings.value("AttributesNumber").toInt();
    opt_tab = new bool[attr_nums];

    for (int i = 0; i < attr_nums; i++)
    {
        header_labels.push_back(settings.value("Attribute"+QString::number(i)).toString());
        opt_tab[i] = false;
    }

    int opt_num = settings.value("OptionalNumber").toInt();
    for(int i = 0; i < opt_num; i++)
    {
        opt_tab[settings.value("OptAttrId"+QString::number(i)).toInt()] = true;
    }
}

ModelManager *ModelManager::get()
{
    if(instance == NULL)
    {
        instance = new ModelManager();
    }
    return instance;
}

void ModelManager::setWidget(QWidget *m_widget)
{
    widget = m_widget;
}

bool ModelManager::saveFileOrder(const QString &file_name)
{
    if (modified == true)
    {
        return saveFile(file_name);
    }
}

bool ModelManager::loadFileOrder(const QString &file_name)
{
    if(file_name == "" && model->rowCount())
    {
        model->appendRow(NULL);
        return true;
    }
    else if(last_file_name == file_name && modified == false)
    {
        return false;
    }
    else
    {
        return loadFile(file_name);
    }
}

bool ModelManager::saveFile(const QString &file_name)
{
    removeEmptyRows();
    if (XmlWriter::writeModel(file_name, model, root_name, node_name, header_labels2, opt_tab) == false)
    {
        if(isEmptyRow(model->rowCount()-1) == false) // The last one row isn't empty - should be empty for adding new record
        {
            model->appendRow(NULL);
        }
        return false;
    }
    modified = false;
    if(isEmptyRow(model->rowCount()-1) == false) // The last one row isn't empty - should be empty for adding new record
    {
        model->appendRow(NULL);
    }
    return true;
}

bool ModelManager::loadFile(const QString &file_name)
{
    QStandardItemModel *tmp_model;
    tmp_model = XmlReader::getModel(widget, file_name, root_name, node_name, header_labels2);

    if (tmp_model != NULL)
    {
        delete model;
        model = NULL;
        model = tmp_model;
    }
    last_file_name = file_name;

    if(isEmptyRow(model->rowCount()-1) == false) // The last one row isn't empty - should be empty for adding new record
    {
        model->appendRow(NULL);
    }

    return true;
}

bool ModelManager::deleteRecordsOrder(QModelIndexList &selection)
{
    if(selection.size() == 0)
    {
        return false;
    }
    else
    {
        return deleteRecords(selection);
    }
}

bool ModelManager::deleteRecords(QModelIndexList &selection)
{
    qSort(selection.begin(), selection.end(), qGreater<QModelIndex>());

    foreach (QModelIndex index, selection) {
        model->removeRow(index.row(),QModelIndex());
    }
    modified = true;
    if(isEmptyRow (model->rowCount()-1) == false )
    {
        model->appendRow(NULL);
    }
    return true;
}

void ModelManager::clearSelected(QItemSelection selection)
{
    QModelIndexList index_list = selection.indexes(); //ui->tableView->selectedIndexes;
    for(int i = 0; i < index_list.size(); i++)
    {
        QModelIndex index = index_list.at(i);
        ModelManager::get()->model->setData(index, "", Qt::EditRole);
        modified = true;
    }
}

bool ModelManager::isEmptyRow(int row)
{
    if (model->rowCount() == 0)
    {
        return false; // isn't empty, cause doesn't exist
    }

    for(int col = 0; col < model->columnCount(); col++)
    {
        QModelIndex index = model->index(row,col,QModelIndex());
        QString value = model->data(index,Qt::EditRole).toString();

        if (value != "")
        {
            return false;
        }
    }

    return true;
}

void ModelManager::removeEmptyRows()
{
    for(int i = 0; i < model->rowCount(); i++)
    {
        bool empty_row = true;
        for(int j = 0; j < model->columnCount(); j++)
        {
            QModelIndex index = model->index(i,j,QModelIndex());
            QString value = model->data(index,Qt::EditRole).toString();
            if (value != "")
            {
                empty_row = false;
                j = model->columnCount();
            }
        }
        if (empty_row == true)
        {
            model->removeRow(i, QModelIndex());
            i--;
        }
    }
}
