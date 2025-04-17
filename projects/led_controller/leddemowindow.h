#ifndef LEDDEMOWINDOW_H
#define LEDDEMOWINDOW_H

#include <QMainWindow>
#include <memory>
#include "led_app_adapter.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class LEDDemoWindow;
}
QT_END_NAMESPACE

class LEDDemoWindow : public QMainWindow
{
    Q_OBJECT

public:
    LEDDemoWindow(QWidget *parent = nullptr);
    ~LEDDemoWindow();
    void set_ui_status(const LEDHandle::status st);
private slots:
    void on_pushButton_clicked();

private:
    Ui::LEDDemoWindow *ui;
    std::unique_ptr<LEDHandle> handle;
};
#endif // LEDDEMOWINDOW_H
