#ifndef DATE_H
#define DATE_H
#include <QString>
#include <QDate>


class Date
{
public:
    virtual void abstractMethod() = 0;
    static int StringToInt(QString date);
    static int calcDiffYears(int date1_i, int date2_i);
    static int calcDiffYears(QString date1_s, QString date2_s);
    static bool checkFormat(int date);
    static bool checkFormat(QString date_s);
    static int countAge(QString date_s);
    static QString countStringAge(QString date);
private:
    static void swap(QString &str, int pos1, int pos2);
};

#endif // DATE_H
