#include "date.h"


int Date::StringToInt(QString date)
{
    if( date[2] == '.' || date[5] == '.' || date.size() != 10 )
    {
        swap(date, 6, 0);
        swap(date, 7, 1);
        swap(date, 8, 2);
        swap(date, 9, 3);
        swap(date, 4, 5);
        swap(date, 5, 9);
        swap(date, 6, 9);
        swap(date, 7, 8);
        swap(date, 8, 9);
    }
    else if( date[4] != '.' || date[7] != '.' || date.size() != 10 )
    {
        return -1;
    }
    date = date.remove('.');
    return date.toInt();
}

int Date::calcDiffYears(int date1_i, int date2_i)
{
    int day1 = date1_i % 10000;
    int day2 = date2_i % 10000;
    int year1 = date1_i / 10000;
    int year2 = date2_i / 10000;
    bool later_days = ( day1 < day2 );
    return year1 - year2 - later_days;
}

int Date::calcDiffYears(QString date1_s, QString date2_s)
{
    int date1_i = StringToInt(date1_s);
    int date2_i = StringToInt(date2_s);
    return calcDiffYears(date1_i, date2_i);
}

bool Date::checkFormat(int date)
{
    int day = date % 100;
    date = date / 100;
    int month = date %100;
    date = date / 100;
    int year = date;
    return QDate::isValid (year, month, day);
}

bool Date::checkFormat(QString date_s)
{
    int date_i = StringToInt(date_s);
    return checkFormat(date_i);
}

int Date::countAge(QString date_s)
{
    int date_i = StringToInt(date_s);
    if (checkFormat(date_i) == false)
    {
        return -1;
    }
    QString current_s = QDate::currentDate().toString("yyyy.MM.dd");
    int current_i = StringToInt(current_s);
    return calcDiffYears(current_i, date_i);
}

QString Date::countStringAge(QString date)
{
    return QString::number(countAge(date));
}

void Date::swap(QString &str, int pos1, int pos2)
{
    QChar tmp;
    tmp = str[pos1];
    str[pos1] = str[pos2];
    str[pos2] = tmp;
}
