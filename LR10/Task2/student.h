#ifndef STUDENT_H
#define STUDENT_H

#include <QString>
#include <QVector>

class Student
{
public:
    QString speciality;
    QString groupNumber;
    QString fio;
    QVector<int>grades;
    double average;

    Student();
    Student(QString s, QString g, QString f, QVector<int>gr);
    void calculateAverage();
};

#endif
