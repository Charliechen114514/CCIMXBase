#ifndef CORETOOLS_H
#define CORETOOLS_H
#include <QStringList>

namespace CoreTools
{

QStringList     enumeratefiles(const QString& path, const QStringList& nameFilters);

}

#endif // CORETOOLS_H
