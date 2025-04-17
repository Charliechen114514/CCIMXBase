#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    process_init();
}

void MainWindow::process_init()
{
    connect(ui->pushButton_switchred, &QPushButton::clicked,
            this, &MainWindow::switch_red);
    connect(ui->pushButton_switchblue, &QPushButton::clicked,
            this, &MainWindow::switch_blue);
}

void MainWindow::switch_background_color(
    const std::vector<int>& color_value)
{
    QString bk_format_str = "QMainWindow { background-color: rgba(%1, %2, %3, 100%); }";
    QString impl_bk = QString(bk_format_str).arg(color_value[0]).arg(color_value[1]).arg(color_value[2]);
    setStyleSheet(impl_bk);
}

void MainWindow::switch_red()
{
    std::vector<int> red {255, 0, 0};
    switch_background_color(red);
}

void MainWindow::switch_blue()
{
    std::vector<int> red {0, 0, 255};
    switch_background_color(red);
}

MainWindow::~MainWindow()
{
    delete ui;
}
