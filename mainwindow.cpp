#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mytablemodel.h"
#include "xmlprocess.h"
#include "dbprocess.h"
#include "progress.h"
#include "QFileDialog"
#include "QObject"
#include "thread"

void MainWindow::to_log(QString text) {
    ui->log->setText(ui->log->toPlainText() + "\n" + text);
}

void MainWindow::set_model(myTableModel* model) {
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->resizeColumnsToContents();
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    Progress progress;
    QObject::connect(&progress, SIGNAL(msgChanged(QString)), this, SLOT(to_log(QString)));
    QObject::connect(&progress, SIGNAL(modelChanged(myTableModel*)), this, SLOT(set_model(myTableModel*)));

    std::thread thread(dbRead, std::ref(progress));
    thread.join();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadButton_clicked()
{
    QString path = ui->filename->text();

    Progress progress;
    QObject::connect(&progress, SIGNAL(valueChanged(int)), ui->progressBar, SLOT(setValue(int)));
    QObject::connect(&progress, SIGNAL(msgChanged(QString)), this, SLOT(to_log(QString)));
    QObject::connect(&progress, SIGNAL(modelChanged(myTableModel*)), this, SLOT(set_model(myTableModel*)));
    std::thread thread(readXml, std::ref(path), std::ref(progress));
    thread.join();
}

void MainWindow::on_exploreButton_clicked()
{
    QString file = QFileDialog::getExistingDirectory(nullptr, "Выберите папку с xml-файлами", "");
    ui->filename->setText(file);
}

void MainWindow::on_removeRecord_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    if (selection->hasSelection()) {
         QModelIndexList selected = selection->selectedRows();
         for(int i=0; i< selected.count(); i++)
         {
            QModelIndex index = selected.at(i);
            myTableModel *model = static_cast <myTableModel *> (ui->tableView->model());
            model->removeSelected(index.row());
         }
    }
}

void MainWindow::on_saveButton_clicked()
{
    QItemSelectionModel *selection = ui->tableView->selectionModel();
    QModelIndexList selected = selection->selectedRows();
    if (selection->hasSelection() && !selected.isEmpty()) {
         QAbstractItemModel *model = ui->tableView->model();
         Progress progress;
         QObject::connect(&progress, SIGNAL(msgChanged(QString)), this, SLOT(to_log(QString)));
         writeXml(model, selected.first().row(), progress);
    }
    else
        to_log("Выберите строку для сохранения!\n");
}

void MainWindow::on_clearButton_clicked()
{
    for(int i=ui->tableView->model()->rowCount(); i >= 0; i--) {
        myTableModel *model = static_cast <myTableModel *> (ui->tableView->model());
        model->removeSelected(i);
    }
}
