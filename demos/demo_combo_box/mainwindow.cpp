#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setText(QString(
        "你选择了: %1").arg(QString(ui->comboBox->currentText())));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->label->setText(QString(
                           "你选择了: %1").arg(QString(ui->comboBox->currentText())));
}

