#ifndef MANAGER_H
#define MANAGER_H
#include <QString>


class Manager
{
public:
    Manager();
    saveFileOrder(QString file_name);
    loadFileOrder(QString file_name);
    saveFile(QString file_name);
    loadFile(QString file_name);
};

#endif // MANAGER_H
