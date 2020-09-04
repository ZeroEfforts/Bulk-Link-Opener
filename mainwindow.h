#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void run();
    ~MainWindow();

private slots:
    void on_browse_button_clicked();
    void readFileData(const QString file);
    void on_file_path_textChanged(const QString &arg1);

    void on_radioButton_clicked();

    void on_radioButton_2_clicked();

    void on_spinBox_valueChanged(int arg1);

    void on_run_clicked();

    void on_actionOpen_Links_File_triggered();

    void on_actionExit_triggered();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;
    int perBatch;
    string specificbrowser;
    vector<string> links;
    int indexx=0, totalsize=0;
};
#endif // MAINWINDOW_H
