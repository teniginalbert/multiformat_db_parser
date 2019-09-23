#include "mytablemodel.h"
#include "progress.h"
#include "QDir"
#include "QFile"
#include "QtSql/QSqlDatabase"
#include "QtSql/QSqlQuery"

void dbRead(Progress &progress) {
    QString databaseName = QDir::currentPath() + "/database.db";
    QFileInfo checkFile(databaseName);

    myTableModel *model = new myTableModel;

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(databaseName);
    db.open();
    QSqlQuery query;

    if(checkFile.exists() && checkFile.isFile()) {

        query.exec("SELECT name, texteditor, fileformats, encoding, hasintellisense, hasplugins, cancompile FROM xmls");

        while (query.next()) {
            QString name = query.value(0).toString();
            QString texteditor = query.value(1).toString();
            QString fileformats = query.value(2).toString();
            QString encoding = query.value(3).toString();
            bool hasintellisense = query.value(4).toBool();
            bool hasplugins = query.value(5).toBool();
            bool cancompile = query.value(6).toBool();
            model->appendRecord(name,
                                texteditor,
                                fileformats,
                                encoding,
                                hasintellisense,
                                hasplugins,
                                cancompile);
            progress.setMsg("База данных была успешно прочитана из файла!\n");
        }
    }
    else
    {
        query.exec("CREATE TABLE xmls "
                   "(name text primary key not null, "
                   "texteditor text not null, "
                   "fileformats text not null, "
                   "encoding text not null,"
                   "hasintellisense blob not null,"
                   "hasplugins blob not null,"
                   "cancompile blob not null)");
        progress.setMsg("База данных была создана!\n");
    }

    progress.setModel(model);
}
