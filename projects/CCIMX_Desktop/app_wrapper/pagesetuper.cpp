#include "pagesetuper.h"
#include "appwidget.h"
#include "desktopmainwindow.h"
#include "downdockwidget.h"
#include <QGridLayout>
#include <QStackedWidget>
#define MAX_WIDTH   (4)
#define MAX_HEIGHT  (4)

/* create for a page append */
QList<AppWidget *>
PageSetuper::create_one_app_only_page_append(
    QStackedWidget *widget, DesktopMainWindow* mainWindow,
    const QList<PageSetupSessionRequest> &sessionRequest)
{
    QList<AppWidget*> appsWidgets;
    QWidget *page = new QWidget(mainWindow);
    QGridLayout *gridLayout = new QGridLayout(page);
    gridLayout->setSpacing(20);
    gridLayout->setContentsMargins(30, 30, 30, 30);
    int j = 0;
    for(const auto& session : sessionRequest)
    {
        AppWidget* app = new AppWidget(
            QPixmap(session.pixmap_addr).scaled(48, 48, Qt::KeepAspectRatio, Qt::SmoothTransformation), session.app_name, mainWindow);
        app->bindApp(session.app);
        appsWidgets << app;
        QObject::connect(app, &AppWidget::postAppStatus, mainWindow, &DesktopMainWindow::handle_app_status);
        gridLayout->addWidget(app, j / MAX_WIDTH, j % MAX_HEIGHT);
        j++;
    }

    page->setLayout(gridLayout);
    widget->addWidget(page);

    return appsWidgets;
}

void PageSetuper::add_to_dock(
    DownDockWidget *downdock,
    DesktopMainWindow* mainWindow,
    const QList<AppWidget *> &widgets)
{
    QList<AppWidget *> copys;
    for(const auto& each : widgets)
    {
        AppWidget* app = new AppWidget(each->icon(), each->app_name(), each->parentWidget());
        app->bindApp(each->get_app());
        copys << app;
        QObject::connect(app, &AppWidget::postAppStatus, mainWindow, &DesktopMainWindow::handle_app_status);
    }

    downdock->set_dock_apps(copys);
}
