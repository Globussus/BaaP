#include "student.h"

Student::Student() : average{0} {}

Student::Student(QString s, QString g, QString f, QVector<int> gr)
    : speciality{s}, groupNumber{g}, fio{f}, grades{gr} {
    calculateAverage();
}

void Student::calculateAverage() {
    if (this->grades.isEmpty()) {
        average = 0;
        return;
    }
    double sum = 0;
    for (int grade : grades) {
        sum += grade;
    }
    this->average = sum / grades.length();
}
