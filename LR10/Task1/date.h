#ifndef DATE_H
#define DATE_H

#include <string>

class Date
{
private:
    static constexpr int maxValues[12] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int day;
    int month;
    int year;
public:
    Date(int day, int month, int year);
    static bool validateDate(int day, int month, int year);
    bool isLeap();
    static bool isLeapYear(int year);
    Date nextDay();
    Date previousDay();
    int duration(Date date);
    static int daysTillYourBirthday(Date date);
    static Date currentDate();
    int weekNumber();
    std::string toString() const;
};

#endif
