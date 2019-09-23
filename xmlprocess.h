#ifndef XMLPROCESS_H
#define XMLPROCESS_H

#include <mytablemodel.h>
#include <progress.h>

void readXml(QString path, Progress &progress);

void writeXml(QAbstractItemModel *model, int row, Progress &progress);

#endif // XMLPROCESS_H
