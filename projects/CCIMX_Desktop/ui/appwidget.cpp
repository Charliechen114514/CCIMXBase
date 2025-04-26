#include "app_wrapper/applicationwrapper.h"
#include "appwidget.h"
#include "ui_appwidget.h"

AppWidget::AppWidget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppWidget)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->icon_label->setAlignment(Qt::AlignCenter);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background: transparent;");
}

/* oh, kotlin do a good job then :) */
AppWidget::AppWidget(const QPixmap &icon, const QString &name, QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::AppWidget)
{
    ui->setupUi(this);
    ui->label->setAlignment(Qt::AlignCenter);
    ui->icon_label->setAlignment(Qt::AlignCenter);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setStyleSheet("background: transparent;");
    setIcon(icon);
    setAppName(name);

    ui->icon_label->installEventFilter(this);
}


void AppWidget::setIcon(const QPixmap &icon) noexcept
{
    ui->icon_label->setPixmap(icon);
}

void AppWidget::setAppName(const QString &name) noexcept
{
    ui->label->setText(name);
}

QPixmap AppWidget::icon() const
{
    return ui->icon_label->pixmap();
}

QString AppWidget::app_name() const
{
    return ui->label->text();
}

AppWidget::~AppWidget()
{
    delete ui;
}

bool AppWidget::eventFilter(QObject* watched, QEvent* event)
{
    if (watched == ui->icon_label) {
        if (event->type() == QEvent::MouseButtonPress) {
            do_daptch();
            return true;
        }
    }
    return QWidget::eventFilter(watched, event);
}

void AppWidget::do_daptch()
{
    if(!app_internal){
        qDebug() << "app is not binded, check the path";
        emit postAppStatus(AppStatus::AppNonExsits);
        return;
    }else{
        qDebug() << "about depatch the app " << app_internal->get_app_path();
        app_internal->depatch_app();
        emit postAppStatus(AppStatus::AppOk);
    }
}
