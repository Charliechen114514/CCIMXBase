#include "coretools.h"
#include <QDir>

QStringList CoreTools::
enumeratefiles(
const QString &path, const QStringList &nameFilters)
{
    QDir dir(path);

    QFileInfoList fileInfoList = dir.entryInfoList(
        nameFilters,
        QDir::Files | QDir::NoSymLinks | QDir::Readable
        );

    QStringList filePaths;
    for (const QFileInfo& fileInfo : fileInfoList) {
        filePaths << fileInfo.absoluteFilePath();
    }

    return filePaths;
}
