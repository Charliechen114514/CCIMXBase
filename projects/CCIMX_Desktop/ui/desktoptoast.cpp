#include <QLabel>
#include <QGuiApplication>
#include <QPropertyAnimation>
#include <QScreen>
#include <QTimer>
#include "desktoptoast.h"

DesktopToast::DesktopToast(QWidget *parent)
    : QWidget{parent}
{
    setWindowFlags(Qt::FramelessWindowHint | Qt::Tool | Qt::WindowStaysOnTopHint);
    setAttribute(Qt::WA_TranslucentBackground);
    setAttribute(Qt::WA_ShowWithoutActivating);

    label = new QLabel(this);

    label->setStyleSheet("QLabel { background-color: rgba(0, 0, 0, 160); color: white; padding: 8px 16px; border-radius: 10px; }");
}

void DesktopToast::start_animation()
{
    if(moveAnimation){
        moveAnimation->stop();
        moveAnimation->deleteLater();
    }

    moveAnimation = new QPropertyAnimation(this, "pos");
    moveAnimation->setDuration(animation_maintain_msec);
    moveAnimation->setStartValue(startPos);
    moveAnimation->setEndValue(endPos);
    moveAnimation->setEasingCurve(QEasingCurve::OutCubic);
    moveAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void DesktopToast::start_close_animation()
{
    if (isClosing) {
        return;
    }
    isClosing = true;

    fadeAnimation = new QPropertyAnimation(this, "pos");
    fadeAnimation->setDuration(animation_maintain_msec);
    fadeAnimation->setStartValue(endPos);
    fadeAnimation->setEndValue(startPos);
    connect(fadeAnimation, &QPropertyAnimation::finished, this, [this]() {
        close();
        isClosing = false;
    });

    fadeAnimation->start(QAbstractAnimation::DeleteWhenStopped);
}

void DesktopToast::adjust_place()
{
    QWidget* referenceWidget = parentWidget();
    if (referenceWidget) {
        QRect parentRect = referenceWidget->rect();
        QPoint topCenter(parentRect.width() / 2 - width() / 2, 30);
        endPos = referenceWidget->mapToGlobal(topCenter);
    } else {
#if QT_VERSION >= QT_VERSION_CHECK(5, 10, 0)
        QRect screenGeometry = QGuiApplication::primaryScreen()->availableGeometry();
#else
        QRect screenGeometry = QApplication::desktop()->availableGeometry();
#endif
        int screenWidth = screenGeometry.width();
        int screenX = screenGeometry.x();
        QPoint topCenter(screenX + (screenWidth - width()) / 2, screenGeometry.top() + 30);
        endPos = topCenter;
    }

    startPos = QPoint(endPos.x(), endPos.y() - 50);
    move(startPos);
}

void DesktopToast::set_message(const QString& message)
{
    label->setText(message);
    label->adjustSize();
    resize(label->size());
    adjust_place();
    show();
    /* forced to repaint */
    raise();
    start_animation();
    repaint();
    QTimer::singleShot(1950, this, &DesktopToast::start_close_animation); // 2秒后关闭
}
