#include "desktopmainwindow.h"
#include "builtin/page/homepage.h"
#include "pagefactory.h"
#include "app_wrapper/pagesetuper.h"
/* create a homepage */
QWidget *PageFactory::build_home_page(DesktopMainWindow *mainWindow)
{
    HomePage*   homePage = new HomePage(mainWindow);
    return      homePage;
}

QList<AppWidget *> PageFactory::build_pesudo_page(
    const QString &pixpath, int how_many, DesktopMainWindow *mainWindow)
{
    QList<PageSetuper::PageSetupSessionRequest> req;
    for(int i = 0; i < how_many; i++)
    {
        req.push_back({pixpath, QString::number(i), nullptr});
    }

    return PageSetuper::create_one_app_only_page_append(
        mainWindow->stackedWidget(), mainWindow, req);
}



