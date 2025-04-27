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
class QTimer;
class QStackedWidget;
class DesktopMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    struct WallPaperGroup{
        QWidget*                shoule_be_lower;
        /* wall paper label is using in display the current */
        QLabel*                 wallpaperLabel{nullptr};
        /* bufferpaperLabel helps the animations */
        QLabel*                 bufferpaperLabel{nullptr};
        QTimer*                 invoke_switch_timer;
    };

    DesktopMainWindow(QWidget *parent = nullptr);
    /* for mainWindow, this is the global messages */
    void showToast(const QString& message);
    void to_next_page();
    void to_prev_page();
    ~DesktopMainWindow();
    void invoke_switch_bgpage();
    void handle_app_status(AppWidget::AppStatus status);
    QStackedWidget* stackedWidget() const;
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
private:
    Ui::DesktopMainWindow *ui;
    DesktopToast*               toast;
    QList<ApplicationWrapper*>  app_wrapper;
    QList<AppWidget*>           app_widgets;
    void                        post_setupui();
    void                        setup_bg_image();
    void                        setup_apps();
    void                        slideToPage(int newIndex, bool toLeft);

    /* wall paper struct */
    WallPaperGroup wallPaperGroup;
    /* using in the image lists */
    QStringList                 image_lists;

    /* using in detect the mouse pos, and shell be used in <- -> */
    struct {
        QPoint                  press;
        QPoint                  release;
    }records;

    static constexpr const unsigned int switch_bg_time = 20000;

};
#endif // DESKTOPMAINWINDOW_H
