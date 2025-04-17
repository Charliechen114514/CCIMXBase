#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void switch_background_color(const std::vector<int> &color_value);
    ~MainWindow();

public slots:
    void switch_red();
    void switch_blue();
private:
    Ui::MainWindow *ui;
    // functions process the init issue
    void process_init();
};
#endif // MAINWINDOW_H
