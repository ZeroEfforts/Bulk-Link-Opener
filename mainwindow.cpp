#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->run->setEnabled(false);
    //connect(ui->label_5, SIGNAL(valueChanged(int)),ui->progressBar, SLOT(setValue(int)));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::readFileData(const QString path)
{
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    QTextStream in(&file);
    links.clear();
    while(!in.atEnd())
    {
        links.push_back((in.readLine()).toStdString());
    }
    QString data;
    totalsize=links.size();
    for(auto i=0;i<links.size();i++)
    {
        cout<<links[i]<<endl;
        data+=(links[i]+"\n").c_str();
    }
    ui->textBrowser->setText(data);
}

void MainWindow::on_browse_button_clicked()
{
    ui->file_path->setText(
                QFileDialog::getOpenFileName(this, "Open a file", "directoryToOpen",
                                             "Images (*.png *.xpm *.jpg);;Text files (*.txt);;XML files (*.xml)"));
    if(QFile::exists(ui->file_path->text()))
    {
        ui->statusbar->showMessage("File opened successfully!", 5000);
        readFileData(ui->file_path->text());
    }
    else
        ui->statusbar->showMessage("File error!", 5000);

}

void MainWindow::on_file_path_textChanged(const QString &arg1)
{
    if(QFile::exists(ui->file_path->text()))
    {
        ui->statusbar->showMessage("File opened successfully!", 5000);
        readFileData(ui->file_path->text());
        ui->run->setEnabled(true);
    }
    else
    {
        ui->statusbar->showMessage("File error!", 5000);
        ui->run->setEnabled(false);
    }
}

void MainWindow::on_radioButton_clicked()
{
    ui->spinBox->hide();
    ui->label_4->hide();
    //ui->label_5->hide();
    ui->progressBar->hide();
    //ui->next_batch->hide();
    perBatch=INT_MAX;
}


void MainWindow::on_radioButton_2_clicked()
{
    ui->spinBox->show();
    ui->label_4->show();
    //ui->label_5->show();
    ui->progressBar->show();
    //ui->next_batch->show();
    perBatch=ui->spinBox->value();
}

void MainWindow::run()
{
    for(int i=0;i<perBatch && !links.empty() && indexx<links.size();i++)
    {
        string link;
        link="start "+links[indexx];
        //links.erase(links.begin());
        system(link.c_str());
        indexx++;
        ui->progressBar->setValue(indexx*100/totalsize);
        //ui->label_5->setNum(indexx);
    }
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{
    perBatch=arg1;
}

void MainWindow::on_run_clicked()
{
    run();
}

void MainWindow::on_actionOpen_Links_File_triggered()
{
    on_browse_button_clicked();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_actionAbout_triggered()
{
    QMessageBox::information(this, "About", "By Hunzlah Malik");
}
