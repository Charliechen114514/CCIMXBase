#ifndef DESKTOPMAINWINDOW_H
#define DESKTOPMAINWINDOW_H

#include <QMainWindow>
#include "ui/appwidget.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class DesktopMainWindow;
}
QT_END_NAMESPACE
/* App layouts */
class QGridLayout;
class QLabel;
class DesktopToast;
class ApplicationWrapper;

class DesktopMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    DesktopMainWindow(QWidget *parent = nullptr);
    /* for mainWindow, this is the global messages */
    void showToast(const QString& message);
    void set_bg_image(const QPixmap& pixmap);
    void to_next_page();
    void to_prev_page();
    ~DesktopMainWindow();
    void handle_app_status(AppWidget::AppStatus status);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::DesktopMainWindow *ui;
    DesktopToast*               toast;
    QList<ApplicationWrapper*>  app_wrapper;
    QList<AppWidget*>           app_widgets;
    QLabel*                     wallpaperLabel{nullptr};
    void                        post_setupui();
    void                        setup_bg_image();
    void                        setup_apps();
    void                        slideToPage(int newIndex, bool toLeft);
    struct {
        QPoint                  press;
        QPoint                  release;
    }records;
};
#endif // DESKTOPMAINWINDOW_H
