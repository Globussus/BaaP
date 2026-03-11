#ifndef FILE_FUNCTIONS_H
#define FILE_FUNCTIONS_H

#include "student.h"
#include <QVector>
#include <QString>
#include <QFile>
#include <QDataStream>

void saveStudents(const QString &fileName, const QVector<Student*> &list);
QVector<Student*> loadStudents(const QString &fileName);

void sortByAverage(QVector<Student*> &list);
void sortByAverageInGroup(QVector<Student*> &list);
QVector<Student*> findByFio(const QVector<Student*> &list, const QString &name);
QVector<Student*> getSuccessfulStudents(const QVector<Student*> &list);

#endif
