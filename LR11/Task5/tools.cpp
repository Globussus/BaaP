#include "tools.h"
#include <QDir>
#include <QFileInfoList>

void countFilesAndDirectories(const QString &dirPath, Stats &stats) {
    QDir dir(dirPath);
    if (!dir.exists()) { 
        return;
    }
    QFileInfoList list = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot | QDir::Hidden);
    for (const QFileInfo &fileInfo : list) {
        if (fileInfo.isDir()) {
            stats.directories++;
            countFilesAndDirectories(fileInfo.absoluteFilePath(), stats);
        } else {
            stats.files++;
        }
    }
}