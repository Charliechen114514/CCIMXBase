#include <QHBoxLayout>
#include "downdockwidget.h"
#include <QGraphicsDropShadowEffect>
#include "ui_downdockwidget.h"
#include "appwidget.h"


DownDockWidget::DownDockWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::DownDockWidget)
{
    ui->setupUi(this);
    setAttribute(Qt::WA_StyledBackground, true);
    setObjectName("DockCard");
    // setStyleSheet(
    //     "QWidget#DockCard {"
    //     "background: rgba(255, 255, 255, 220);"
    //     "border: 1px solid rgba(0, 0, 0, 30);"
    //     "border-radius: 16px;"
    //     "padding: 12px;"
    //     "}"
    // );

    setStyleSheet("QWidget#DockCard { background-color: rgba(255, 0, 0, 255) !important; }");
    // setStyleSheet("QWidget#DockCard { background: rgb(0, 0, 255); }");
    qDebug() << "Current style sheet: " << styleSheet();
    // QGraphicsDropShadowEffect* shadow = new QGraphicsDropShadowEffect(this);
    // shadow->setBlurRadius(20);
    // shadow->setOffset(0, 4);
    // shadow->setColor(QColor(0, 0, 0, 50));
    // setGraphicsEffect(shadow);
}

void DownDockWidget::set_dock_apps(const QList<AppWidget *> &apps)
{
    dock_apps = apps;
    replace_docks();
}

void DownDockWidget::replace_docks()
{
    for(const auto& each_app : std::as_const(dock_apps)){
        /* dock apps */
        layout()->addWidget(each_app);
    }
    adjustSize();
}

DownDockWidget::~DownDockWidget()
{
    delete ui;
}


