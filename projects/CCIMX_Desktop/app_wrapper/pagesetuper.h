#ifndef PAGESETUPER_H
#define PAGESETUPER_H

/* page setuper helps setup the page quickly */
#include <QList>
class QStackedWidget;
class DesktopMainWindow;
class ApplicationWrapper;
class AppWidget;
class DownDockWidget;

namespace PageSetuper
{

/* sessions required */
struct PageSetupSessionRequest{
    QString                 pixmap_addr{};
    QString                 app_name{};
    ApplicationWrapper*     app{nullptr};
};



/* shell make a page request */
QList<AppWidget*>   create_one_app_only_page_append(
    QStackedWidget* widget, DesktopMainWindow *mainWindow,
    const QList<PageSetupSessionRequest>& sessionRequest);

void   add_to_dock(DownDockWidget* downdock, DesktopMainWindow *mainWindow, const QList<AppWidget*>& widgets);
};

#endif // PAGESETUPER_H
