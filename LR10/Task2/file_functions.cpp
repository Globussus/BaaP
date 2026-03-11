#include "file_functions.h"
#include <QFile>
#include <QDataStream>
#include <algorithm>

void saveStudents(const QString &fileName, const QVector<Student*> &list) {
    QFile file(fileName);
    if (file.open(QIODevice::WriteOnly)) {
        QDataStream out(&file);
        out << (int)list.size();
        for (Student* s : list) {
            out << s->speciality << s->groupNumber << s->fio << s->grades << s->average;
        }
    }
}

QVector<Student*> loadStudents(const QString &fileName) {
    QVector<Student*> list;
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly)) {
        QDataStream in(&file);
        int size; in >> size;
        for (int i = 0; i < size; ++i) {
            Student* s = new Student();
            in >> s->speciality >> s->groupNumber >> s->fio >> s->grades >> s->average;
            list.append(s);
        }
    }
    return list;
}

void sortByAverage(QVector<Student*> &list) {
    std::sort(list.begin(), list.end(), [](Student* a, Student* b) {
        return a->average > b->average;
    });
}

void sortByAverageInGroup(QVector<Student*> &list) {
    std::sort(list.begin(), list.end(), [](Student* a, Student* b) {
        if (a->groupNumber == b->groupNumber) return a->average > b->average;
        return a->groupNumber < b->groupNumber;
    });
}

QVector<Student*> findByFio(const QVector<Student*> &list, const QString &name) {
    QVector<Student*> found;
    for (Student* s : list) {
        if (s->fio.contains(name, Qt::CaseInsensitive)) found.append(s);
    }
    return found;
}

QVector<Student*> getSuccessfulStudents(const QVector<Student*> &list) {
    QVector<Student*> result;
    for (Student* s : list) {
        bool ok = true;
        for (int g : s->grades) if (g < 4) ok = false;
        if (ok) result.append(s);
    }
    return result;
}
