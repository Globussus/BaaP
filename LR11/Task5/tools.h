#ifndef TOOLS_H
#define TOOLS_H

#include <QString>

struct Stats {
    int files = 0;
    int directories = 0;
};

void countFilesAndDirectories(const QString &dirPath, Stats &stats);

#endif
