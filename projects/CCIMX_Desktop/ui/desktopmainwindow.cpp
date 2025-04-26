#include <QGridLayout>
#include <QLabel>
#include <QMouseEvent>
#include "desktopmainwindow.h"
#include "ui_desktopmainwindow.h"
#include "app_wrapper/applicationwrapper.h"
#include "ui/desktoptoast.h"
#include "ui/stackpage_switcher_animation.h"
#include "app_wrapper/pagesetuper.h"
DesktopMainWindow::DesktopMainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::DesktopMainWindow)
{
    ui->setupUi(this);
    post_setupui();
    setup_apps();
}


void DesktopMainWindow::post_setupui()
{
    toast = new DesktopToast(this);
    setup_bg_image();
}

void DesktopMainWindow::setup_bg_image()
{
    wallpaperLabel = new QLabel(this);
    wallpaperLabel->setScaledContents(true);
    wallpaperLabel->lower();
    wallpaperLabel->setGeometry(0, 0, width(), height());

    QPixmap wallpaper(":/icons/sources/bg.png");
    wallpaperLabel->setPixmap(wallpaper);
}

DesktopMainWindow::~DesktopMainWindow()
{
    delete ui;
}

void DesktopMainWindow::setup_apps()
{
    /* app page 1 */
    QList<PageSetuper::PageSetupSessionRequest> req;
    QString     pdf_path;
#ifdef ARM_BUILD
    pdf_path = "./pdfReader";
#else
    pdf_path = "/home/charliechen/imx6ull/qt683_project/CCIMX_Desktop/build/pdfReader";
#endif
    ApplicationWrapper* wrapper = new ApplicationWrapper(this, this);
    wrapper->set_app_path(pdf_path);
    app_wrapper << wrapper;
    req.push_back({":/icons/sources/pdf_browser.png", "PDF Browser", wrapper});
    app_widgets << PageSetuper::create_one_app_only_page_append(ui->stackedWidget, this, req);

    req.clear();
    for(int i = 0; i < 9; i++){
        req.push_back({":/icons/sources/def_icon.png", QString::number(i), nullptr});
    }

    app_widgets << PageSetuper::create_one_app_only_page_append(ui->stackedWidget, this, req);

    req.clear();
    for(int i = 0; i < 9; i++){
        req.push_back({":/icons/sources/def_icon2.png", QString::number(i), nullptr});
    }

    app_widgets << PageSetuper::create_one_app_only_page_append(ui->stackedWidget, this, req);

    QList<AppWidget*> docks;
    docks << app_widgets[0] << app_widgets[11];
    PageSetuper::add_to_dock(ui->downdock, this, docks);

}

void DesktopMainWindow::handle_app_status(AppWidget::AppStatus status)
{
    switch(status)
    {
    case AppWidget::AppStatus::AppNonExsits:
        showToast("App is Not binded! bind the app first!");
    break;
    default:
    break;
    }
}

void DesktopMainWindow::showToast(const QString& message)
{
    toast->set_message(message);
}

void DesktopMainWindow::set_bg_image(const QPixmap &pixmap)
{
    wallpaperLabel->setPixmap(pixmap);
}

void DesktopMainWindow::mousePressEvent(QMouseEvent *event)
{
    records.press = event->pos();
}

void DesktopMainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    records.release = event->pos();
    int move_range = records.press.x() - records.release.x();

    if(qAbs(move_range) < 50){return;}

    move_range < 0 ? to_next_page() : to_prev_page();
}


void DesktopMainWindow::to_next_page()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    if(currentIndex <= 0){
        return;
    }
    StackpageSwitcherAnimation::AnimationInfo info;
    info.new_index = currentIndex - 1;
    info.toLeft = false;
    StackpageSwitcherAnimation::process_animations(ui->stackedWidget, &info);

}

void DesktopMainWindow::to_prev_page()
{
    int currentIndex = ui->stackedWidget->currentIndex();
    if(currentIndex >= ui->stackedWidget->count() - 1){
        return;
    }
    StackpageSwitcherAnimation::AnimationInfo info;
    info.new_index = currentIndex + 1;
    info.toLeft = true;
    StackpageSwitcherAnimation::process_animations(ui->stackedWidget, &info);
}

void DesktopMainWindow::resizeEvent(QResizeEvent *event)
{
    QMainWindow::resizeEvent(event);
    if (wallpaperLabel) {
        wallpaperLabel->setGeometry(0, 0, width(), height());
    }
}

