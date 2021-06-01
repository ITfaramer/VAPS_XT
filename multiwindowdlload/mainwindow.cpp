#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_SmallBtn_clicked()
{
    ui->widget_1->setMode(1);
}

void MainWindow::on_StdBtn_clicked()
{
    ui->widget_1->setMode(2);
}

void MainWindow::on_MaxBtn_clicked()
{
    ui->widget_1->setMode(3);
}

void MainWindow::on_ExtendBtn_clicked()
{
    ui->widget_1->setMode(4);
}
