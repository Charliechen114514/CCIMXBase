#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFile>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile f;
    f.setFileName(":/radiobutton.qss");
    qDebug() << f.exists();
    f.open(QIODevice::ReadOnly);
    if(f.isOpen()){
        QString qss = f.readAll();
        setStyleSheet(qss);
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
