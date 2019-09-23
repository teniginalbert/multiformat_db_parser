#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <mytablemodel.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_loadButton_clicked();

    void on_exploreButton_clicked();

    void on_removeRecord_clicked();

    void on_saveButton_clicked();

    void on_clearButton_clicked();

    void to_log(QString text);

    void set_model(myTableModel *model);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
