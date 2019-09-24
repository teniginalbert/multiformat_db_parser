#include "mainwindow.h"
#include "progress.h"
#include "thread"
#include "dbprocess.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    Progress progress;
    QObject::connect(&progress, SIGNAL(msgChanged(QString)), w.window(), SLOT(to_log(QString)));
    QObject::connect(&progress, SIGNAL(modelChanged(myTableModel*)), w.window(), SLOT(set_model(myTableModel*)));
    std::thread thread(dbRead, std::ref(progress));
    thread.join();
    return a.exec();
}
