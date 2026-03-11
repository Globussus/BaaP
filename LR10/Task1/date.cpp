#include "date.h"
#include <stdexcept>
#include <ctime>

Date::Date(int day, int month, int year) {
    if (!validateDate(day, month, year)) {
        throw std::invalid_argument("Invalid date");
    }
    this->day = day;
    this->month = month;
    this->year = year;
}

bool Date::validateDate(int day, int month, int year) {
    if (year < 1 || month < 1 || month > 12 || day < 1) {
        return false;
    }
    int maxDay = maxValues[month - 1];
    if (month == 2 && !isLeapYear(year)) {
        maxDay = 28;
    }
    return day <= maxDay;
}

bool Date::isLeap() {
    return isLeapYear(year);
}

bool Date::isLeapYear(int year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

Date Date::nextDay() {
    int newDay = day + 1;
    int newMonth = month;
    int newYear = year;
    int maxDay = maxValues[month - 1];
    if (month == 2 && !isLeap()) {
        maxDay = 28;
    }
    if (newDay > maxDay) {
        newDay = 1;
        newMonth++;
        if (newMonth > 12) {
            newMonth = 1;
            newYear++;
        }
    }
    return Date(newDay, newMonth, newYear);
}

Date Date::previousDay() {
    int newDay = day - 1;
    int newMonth = month;
    int newYear = year;
    if (newDay < 1) {
        newMonth--;
        if (newMonth < 1) {
            newMonth = 12;
            newYear--;
            if (newYear < 1) {
                throw std::invalid_argument("Invalid previous day");
            }
        }
        newDay = maxValues[newMonth - 1];
        if (newMonth == 2 && !isLeapYear(newYear)) {
            newDay = 28;
        }
    }
    return Date(newDay, newMonth, newYear);
}

int Date::duration(Date date) {
    long long days1 = year * 365LL + day;
    for (int m = 1; m < month; m++) {
        days1 += maxValues[m - 1];
        if (m == 2 && !isLeapYear(year)) {
            days1--;
        }
    }
    days1 += (year - 1) / 4 - (year - 1) / 100 + (year - 1) / 400;

    long long days2 = date.year * 365LL + date.day;
    for (int m = 1; m < date.month; m++) {
        days2 += maxValues[m - 1];
        if (m == 2 && !isLeapYear(date.year)) {
            days2--;
        }
    }
    days2 += (date.year - 1) / 4 - (date.year - 1) / 100 + (date.year - 1) / 400;

    return static_cast<int>(days2 > days1 ? days2 - days1 : days1 - days2);
}

int Date::daysTillYourBirthday(Date date) {
    Date today = currentDate();
    int currentYear = today.year;
    Date nextBirthday(date.day, date.month, currentYear);
    if (today.duration(nextBirthday) < 0 || (today.day == nextBirthday.day && today.month == nextBirthday.month)) {
        nextBirthday = Date(date.day, date.month, currentYear + 1);
    }
    return today.duration(nextBirthday);
}

Date Date::currentDate() {
    time_t now = time(0);
    tm* ltm = localtime(&now);
    return Date(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
}

int Date::weekNumber() {
    Date firstDay(1, 1, year);
    int dayOfWeek = 0;
    Date temp(1, 1, 1);
    long long days = temp.duration(firstDay);
    dayOfWeek = (days % 7 + 6) % 7;
    int dayOfYear = 1;
    Date janFirst(1, 1, year);
    dayOfYear = janFirst.duration(*this) + 1;
    int week = (dayOfYear + dayOfWeek - 1) / 7 + 1;
    if (dayOfWeek <= 3) {
        week = (dayOfYear + dayOfWeek - 1) / 7 + 1;
    } else {
        week = (dayOfYear + dayOfWeek - 1) / 7;
    }
    if (week < 1) week = 1;
    return week;
}

std::string Date::toString() const {
    char buffer[11];
    sprintf(buffer, "%02d.%02d.%04d", day, month, year);
    return std::string(buffer);
}
